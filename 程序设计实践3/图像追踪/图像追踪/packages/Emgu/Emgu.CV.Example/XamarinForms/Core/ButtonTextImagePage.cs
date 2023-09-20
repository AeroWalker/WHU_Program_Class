﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Xamarin.Forms;
using Emgu.CV;
using Emgu.CV.Util;
using Emgu.CV.CvEnum;
using Emgu.CV.Structure;
using Emgu.Util.TypeEnum;

#if __MACOS__
using AppKit;
using CoreGraphics;
using Xamarin.Forms.Platform.MacOS;
#elif __IOS__
using UIKit;
using CoreGraphics;
using Xamarin.Forms.Platform.iOS;
#elif __ANDROID__
using Android.Graphics;
using Android.Views;
using Android.Widget;
using Xamarin.Forms.Platform.Android;
#elif NETFX_CORE
using Xamarin.Forms.Platform.UWP;
#endif

namespace Emgu.CV.XamarinForms
{
    public class ButtonTextImagePage
#if __IOS__
        : Emgu.Util.AvCaptureSessionPage
#else
        : ContentPage
#endif
    {
        private Picker _picker = new Picker();

        public Picker Picker
        {
            get { return _picker; }
        }

        private Xamarin.Forms.Button _topButton = new Xamarin.Forms.Button();
        public Xamarin.Forms.Button TopButton
        {
            get { return _topButton; }
        }

        private Label _messageLabel = new Label();
        public Label MessageLabel
        {
            get { return _messageLabel; }
        }
		
		private Editor _logEditor = new Editor();
        public Editor LogEditor
        {
            get { return _logEditor; }
        }

        private Image _displayImage = new Image();

        public Image DisplayImage
        {
            get { return _displayImage; }
            //set { _displayImage = value; }
        }

        private StackLayout _mainLayout = new StackLayout();

        public StackLayout MainLayout
        {
            get { return _mainLayout; }
        }

#if __MACOS__
        public NSImageView NSImageView { get; set; }
#elif __IOS__
      public UIImageView UIImageView { get; set; }
#elif __ANDROID__
        public ImageView ImageView { get; set; }
#elif NETFX_CORE
       public Windows.UI.Xaml.Controls.Image ImageView { get; set; }
#endif

        private Xamarin.Forms.Button[] _additionalButtons;

        public Xamarin.Forms.Button[] AdditionalButtons
        {
            get
            {
                return _additionalButtons;
            }
        }


        public ButtonTextImagePage(Xamarin.Forms.Button[] additionalButtons=null)
        {
            var horizontalLayoutOptions = LayoutOptions.Center;

            TopButton.Text = "Click me";
            TopButton.IsEnabled = true;
            TopButton.HorizontalOptions = horizontalLayoutOptions;

            MessageLabel.Text = "";
            MessageLabel.HorizontalOptions = horizontalLayoutOptions;


            //DisplayImage.HeightRequest = 100;
            //DisplayImage.WidthRequest = 100;
            //DisplayImage.MinimumHeightRequest = 10;

            //StackLayout mainLayout = new StackLayout();
            _mainLayout.Children.Add(Picker);
            Picker.IsVisible = false;

            _mainLayout.Children.Add(TopButton);
            if (additionalButtons != null)
            {
                foreach (Xamarin.Forms.Button button in additionalButtons)
                {
                    button.HorizontalOptions = horizontalLayoutOptions;
                    _mainLayout.Children.Add(button);
                }
            }

            _additionalButtons = additionalButtons;

            _mainLayout.Children.Add(MessageLabel);


            //MessageLabel.BackgroundColor = Color.AliceBlue;
            //DisplayImage.BackgroundColor = Color.Aqua;
            //_mainLayout.BackgroundColor = Color.Blue;

#if __MACOS__
            NSImageView = new NSImageView();
            NSImageView.ImageScaling = NSImageScale.None;
            _mainLayout.Children.Add(NSImageView.ToView());
#elif __IOS__
            UIImageView = new UIImageView ();
            UIImageView.ContentMode = UIViewContentMode.ScaleAspectFit;
            _mainLayout.Children.Add (UIImageView.ToView ());
#elif __ANDROID__
            ImageView = new ImageView(Android.App.Application.Context);
            _mainLayout.Children.Add(ImageView.ToView());
#elif NETFX_CORE
            this.ImageView = new Windows.UI.Xaml.Controls.Image();
            _mainLayout.Children.Add(this.ImageView.ToView());
            //this.ImageView.Stretch = Windows.UI.Xaml.Media.Stretch.Uniform;
            this.ImageView.Stretch = Windows.UI.Xaml.Media.Stretch.None;
#endif
            _mainLayout.Children.Add(DisplayImage);

            //_mainLayout.Children.Add(MessageLabel);
			
			LogEditor.Text = "";
            LogEditor.HorizontalOptions = LayoutOptions.Center;
            LogEditor.VerticalOptions = LayoutOptions.Center;
            LogEditor.FontSize = LogEditor.FontSize / 2;
			_mainLayout.Children.Add(LogEditor);
			
			SetLog(null);
			
            _mainLayout.Padding = new Thickness(10, 10, 10, 10);

            Content = new Xamarin.Forms.ScrollView()
            {
                Content = _mainLayout
            };
        }

        public bool HasCameraOption { get; set; }

        public virtual async Task<Mat[]> LoadImages(String[] imageNames, String[] labels = null)
        {
            Mat[] mats = new Mat[imageNames.Length];

            for (int i = 0; i < mats.Length; i++)
            {
                String pickImgString = "Use Image from";
                if (labels != null && labels.Length > i)
                    pickImgString = labels[i];

                bool captureSupported;

                if (Device.RuntimePlatform == Device.WPF
                    || Device.RuntimePlatform == Device.macOS)
                {
                    //Pick image from camera is not implemented on WPF.
                    captureSupported = false;
                }
                else
                {
                    captureSupported = Xamarin.Essentials.MediaPicker.IsCaptureSupported;
                }

                String action;
                List<String> options = new List<string>();
                options.Add("Default");

                options.Add("Photo Library");

                if (captureSupported)
                    options.Add("Photo from Camera");

                if (this.HasCameraOption)
                {
                    if (Device.RuntimePlatform == Device.Android
                        || Device.RuntimePlatform == Device.iOS
                        || Device.RuntimePlatform == Device.UWP)
                    {
                        if (captureSupported)
                            options.Add("Camera");
                    }
                    else if (Device.RuntimePlatform == Device.WPF
                          || Device.RuntimePlatform == Device.macOS)
                    {
                        var openCVConfigDict = CvInvoke.ConfigDict;
                        bool haveVideoio = (openCVConfigDict["HAVE_OPENCV_VIDEOIO"] != 0);
                        if (haveVideoio)
                            options.Add("Camera");
                    }
                }


                if (options.Count == 1)
                {
                    action = "Default";
                }
                else
                {
                    action = await DisplayActionSheet(pickImgString, "Cancel", null, options.ToArray());
                    if (
                        action == null //user clicked outside of action sheet
                        || action.Equals("Cancel") // user cancel
                    )
                        return null;
                }

                if (action.Equals("Default"))
                {
#if __ANDROID__
                    mats[i] = Android.App.Application.Context.Assets.GetMat( imageNames[i] );
#else
                    if (!File.Exists(imageNames[i]))
                        throw new FileNotFoundException(String.Format("File {0} do not exist.", imageNames[i]));
                    mats[i] = CvInvoke.Imread(imageNames[i], ImreadModes.Color);
#endif
                }
                else if (action.Equals("Photo Library"))
                {
                    if (Device.RuntimePlatform == Device.WPF)
                    {
#if !(__MACOS__ || __ANDROID__ || __IOS__ || NETFX_CORE)
                        Microsoft.Win32.OpenFileDialog dialog = new Microsoft.Win32.OpenFileDialog();
                        dialog.Multiselect = false;
                        dialog.Title = "Select an Image File";
                        dialog.Filter = "Image | *.jpg;*.jpeg;*.png;*.bmp;*.gif | All Files | *";
                        if (dialog.ShowDialog() == false)
                            return null;
                        mats[i] = CvInvoke.Imread(dialog.FileName, ImreadModes.AnyColor);
#endif
                    }
                    else
                    {
                        var fileResult = await Xamarin.Essentials.FilePicker.PickAsync(Xamarin.Essentials.PickOptions.Images);
                        if (fileResult == null) //canceled
                            return null;
                        using (Stream s = await fileResult.OpenReadAsync())
                            mats[i] = await ReadStream(s);
                    }
                }
                else if (action.Equals("Photo from Camera"))
                {
                    var takePhotoResult = await Xamarin.Essentials.MediaPicker.CapturePhotoAsync();

                    if (takePhotoResult == null) //canceled
                        return null;
                    using (Stream stream = await takePhotoResult.OpenReadAsync())
                        mats[i] = await ReadStream(stream);
                }
                else if (action.Equals("Camera"))
                {
                    mats = new Mat[0];
                }
            }

            return mats;
        }

        private static async Task<Mat> ReadStream(Stream stream)
        {
            using (MemoryStream ms = new MemoryStream())
            {
                await stream.CopyToAsync(ms);
                byte[] data = ms.ToArray();
                Mat m = new Mat();
                CvInvoke.Imdecode(data, ImreadModes.Color, m);
                return m;
            }
        }

        private VectorOfByte _imageStream = new VectorOfByte();
        private static Mutex _imageStreamMutex = new Mutex();

        public virtual void SetImage(IInputArray image)
        {
#if __IOS__
         UIImage uiimage;
         if (image == null)
            uiimage = null;
         else
            uiimage = image.ToUIImage ();
         Xamarin.Forms.Device.BeginInvokeOnMainThread (
            () => {
               UIImage oldImage = UIImageView.Image;
               UIImageView.Image = uiimage;
               if (oldImage != null)
                  oldImage.Dispose ();
               if ((uiimage != null) && (UIImageView.Frame.Size != uiimage.Size))
                  UIImageView.Frame = new CGRect (CGPoint.Empty, uiimage.Size);
               UIImageView.Hidden = false;
               DisplayImage.IsVisible = false;
            });
#elif __ANDROID__
            Android.Graphics.Bitmap bitmap;
            if (image == null)
                bitmap = null;
            else
                bitmap = image.ToBitmap();
            Xamarin.Forms.Device.BeginInvokeOnMainThread(
                () =>
                {
                    ImageView.SetImageBitmap(bitmap);
                    ImageView.Visibility = ViewStates.Visible;
                    DisplayImage.IsVisible = false;
                    if (bitmap != null)
                        bitmap.Dispose();
                });
#elif __MACOS__
            
            NSImage nsimage;
            if (image == null)
                nsimage = null;
            else
                nsimage = image.ToNSImage();
            Xamarin.Forms.Device.BeginInvokeOnMainThread(
               () => {

                   NSImage oldImage = NSImageView.Image;
                   NSImageView.Image = nsimage;
                   if (oldImage != null)
                       oldImage.Dispose();
                   if ((nsimage != null) && (NSImageView.Frame.Size != nsimage.Size))
                       NSImageView.Frame = new CGRect(CGPoint.Empty, nsimage.Size);
                   NSImageView.Hidden = false;
                   DisplayImage.IsVisible = false;
               });
#elif NETFX_CORE
         Xamarin.Forms.Device.BeginInvokeOnMainThread(
            () => {
               if (image == null)
               {
                  this.ImageView.Source = null;
                  this.ImageView.Visibility = Windows.UI.Xaml.Visibility.Collapsed;
               }
               else
               {
                  this.ImageView.Source = image.ToWritableBitmap();
                  //this.ImageView.InvalidateMeasure();
                  this.ImageView.Visibility = Windows.UI.Xaml.Visibility.Visible;
                    //this.ImageView.Parent.
                }
            });
#else
            if (image == null)
            {
                Xamarin.Forms.Device.BeginInvokeOnMainThread(
                    () =>
                    {
                        this.DisplayImage.Source = null;
                        this.DisplayImage.IsVisible = false;
                    });
                return;
            }

            int width = 0;
            int height = 0;
            using (InputArray iaImage = image.GetInputArray())
            {
                System.Drawing.Size s = iaImage.GetSize();
                width = s.Width;
                height = s.Height;
            }

            _imageStreamMutex.WaitOne();
            CvInvoke.Imencode(
                ".png",
                image,
                _imageStream,
                new KeyValuePair<ImwriteFlags, int>(ImwriteFlags.PngCompression, 0));
            _imageStreamMutex.ReleaseMutex();

            Xamarin.Forms.Device.BeginInvokeOnMainThread(
                () =>
                {
                    this.DisplayImage.IsVisible = true;
                    this.DisplayImage.Source = ImageSource.FromStream(() =>
                    {
                        MemoryStream ms = new MemoryStream();
                        _imageStreamMutex.WaitOne();
                        _imageStream.Position = 0;
                        _imageStream.CopyTo(ms);
                        _imageStreamMutex.ReleaseMutex();
                        return ms;
                    });

                    this.DisplayImage.WidthRequest = Math.Min(this.Width, width);
                    this.DisplayImage.HeightRequest = height;

                });
            //}
#endif
        }

        public Label GetLabel()
        {
            //return null;
            return this.MessageLabel;
        }

        public void SetMessage(String message)
        {
            Xamarin.Forms.Device.BeginInvokeOnMainThread(
                () =>
                {
                    Label label = GetLabel();
                    label.Text = message;

                    label.LineBreakMode = LineBreakMode.WordWrap;
                 //label.WidthRequest = this.Width;
             }
            );
        }

        private String _log = String.Empty;

        public void ClearLog()
        {
            SetLog(String.Empty);
        }

        public void SetLog(String log)
        {
            _log = log;
            RenderLog(_log);
        }

        public void AppendLog(String log)
        {
            if (!String.IsNullOrEmpty(_log))
                _log = log + _log;
            RenderLog(_log);
        }

        private void RenderLog(String log)
        {
            Xamarin.Forms.Device.BeginInvokeOnMainThread(
                () =>
                {
                    if (String.IsNullOrEmpty(log))
                    {
                        this.LogEditor.IsVisible = false;
                    }
                    else
                    {
                        this.LogEditor.IsVisible = true;
                    }

                    this.LogEditor.Text = log;
                    this.LogEditor.WidthRequest = this.Width;
                    this.LogEditor.HeightRequest = 120;

                    //this.LogLabel.LineBreakMode = LineBreakMode.WordWrap;
                    this.LogEditor.Focus();
                }
            );
        }

        public Xamarin.Forms.Button GetButton()
        {
            //return null;
            return this.TopButton;
        }

    }
}
