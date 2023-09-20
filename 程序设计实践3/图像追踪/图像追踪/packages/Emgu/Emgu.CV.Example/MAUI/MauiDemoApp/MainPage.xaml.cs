﻿//----------------------------------------------------------------------------
//  Copyright (C) 2004-2023 by EMGU Corporation. All rights reserved.       
//----------------------------------------------------------------------------

using Emgu.CV;
using Emgu.CV.CvEnum;
using Emgu.CV.Dnn;
using Emgu.CV.Models;
using Emgu.CV.Platform.Maui.UI;

namespace MauiDemoApp
{
    public partial class MainPage : ContentPage
    {
        //int count = 0;

        public MainPage()
        {
            InitializeComponent();

            Emgu.CV.Platform.Maui.MauiInvoke.Init();

            String aboutIcon = null;


            ToolbarItem aboutItem = new ToolbarItem("About", aboutIcon,
                () =>
                {
                    this.Navigation.PushAsync(new AboutPage());
                    //page.DisplayAlert("Emgu CV Examples", "App version: ...", "Ok");
                }
            );
            this.ToolbarItems.Add(aboutItem);

            Button helloWorldButton = new Button();
            helloWorldButton.Text = "Hello world";

            Button planarSubdivisionButton = new Button();
            planarSubdivisionButton.Text = "Planar Subdivision";

            Button sceneTextDetectionButton = new Button();
            sceneTextDetectionButton.Text = "Scene Text detection (DNN Module)";

            Button featureDetectionButton = new Button();
            featureDetectionButton.Text = "Feature Matching";

            Button shapeDetectionButton = new Button();
            shapeDetectionButton.Text = "Shape Detection";

            Button maskRcnnButton = new Button();
            maskRcnnButton.Text = "Mask RCNN (DNN module)";

            Button yoloButton = new Button();
            yoloButton.Text = "Yolo (DNN module)";

            Button stopSignDetectionButton = new Button();
            stopSignDetectionButton.Text = "Stop Sign Detection (DNN module)";

            Button licensePlateRecognitionButton = new Button();
            licensePlateRecognitionButton.Text = "License Plate Recognition (DNN Module)";

            List<View> buttonList = new List<View>()
            {
                helloWorldButton,
                planarSubdivisionButton,
                sceneTextDetectionButton,
                featureDetectionButton,
                shapeDetectionButton,
                maskRcnnButton,
                stopSignDetectionButton,
                yoloButton,
                licensePlateRecognitionButton
            };

            var openCVConfigDict = CvInvoke.ConfigDict;
            bool haveViz = (openCVConfigDict["HAVE_OPENCV_VIZ"] != 0);
            bool haveDNN = (openCVConfigDict["HAVE_OPENCV_DNN"] != 0);
            bool haveFreetype = (openCVConfigDict["HAVE_OPENCV_FREETYPE"] != 0);
            bool haveFace = (openCVConfigDict["HAVE_OPENCV_FACE"] != 0);
            bool haveWechatQRCode = (openCVConfigDict["HAVE_OPENCV_WECHAT_QRCODE"] != 0);
            bool haveBarcode = (openCVConfigDict["HAVE_OPENCV_BARCODE"] != 0);
            bool haveObjdetect = (openCVConfigDict["HAVE_OPENCV_OBJDETECT"] != 0);
            bool haveTesseract = (openCVConfigDict["HAVE_EMGUCV_TESSERACT"] != 0);
            bool haveFeatures2D = (openCVConfigDict["HAVE_OPENCV_FEATURES2D"] != 0);
            bool haveVideo = (openCVConfigDict["HAVE_OPENCV_VIDEO"] != 0);
            bool haveOptFlow = (openCVConfigDict["HAVE_OPENCV_OPTFLOW"] != 0);


            bool hasInferenceEngine = false;
            if (haveDNN)
            {
                var dnnBackends = DnnInvoke.AvailableBackends;
                hasInferenceEngine = Array.Exists(dnnBackends, dnnBackend =>
                    (dnnBackend.Backend == Emgu.CV.Dnn.Backend.InferenceEngine
                     || dnnBackend.Backend == Emgu.CV.Dnn.Backend.InferenceEngineNgraph
                     || dnnBackend.Backend == Emgu.CV.Dnn.Backend.InferenceEngineNnBuilder2019));
            }

            bool haveCamera = true;

            /*
            if (haveOptFlow && haveCamera)
            {
#if !(__MACCATALYST__ || __ANDROID__ || __IOS__ || NETFX_CORE)
                Button motionDetectionButton = new Button();
                motionDetectionButton.Text = "Motion Detection";
                buttonList.Add(motionDetectionButton);
                motionDetectionButton.Clicked += (sender, args) =>
                {
                    ProcessAndRenderPage motionDetectionPage = new ProcessAndRenderPage(
                        new MotionDetectionModel(),
                        "Open Camera",
                        null,
                        "This demo use MotionHistory for motion detection. The 3 images shown once it is up and running: 1. original image; 2. Foreground image; 3. Motion history");
                    MainPage.Navigation.PushAsync(motionDetectionPage);
                };
#endif
            }*/

            helloWorldButton.Clicked += (sender, args) =>
            {
                this.Navigation.PushAsync(new HelloWorldPage());
            };

            
            planarSubdivisionButton.Clicked += (sender, args) =>
            {
                this.Navigation.PushAsync(new PlanarSubdivisionPage());
            };


            
            shapeDetectionButton.Clicked += (sender, args) =>
            {
                ProcessAndRenderPage shapeDetectionPage = new ProcessAndRenderPage(
                    new ShapeDetector(),
                    "Shape detection",
                    "pic3.png",
                    "Shape detection");
                this.Navigation.PushAsync(shapeDetectionPage);
            };

            
            featureDetectionButton.Clicked += (sender, args) =>
            {
                this.Navigation.PushAsync(new FeatureMatchingPage());
            };

            
            licensePlateRecognitionButton.Clicked += (sender, args) =>
            {
                ProcessAndRenderPage vehicleLicensePlateDetectorPage = new ProcessAndRenderPage(
                    new VehicleLicensePlateDetector(),
                    "Perform License Plate Recognition",
                    "cars_license_plate.png",
                    "This demo is based on the security barrier camera demo in the OpenVino model zoo. The models is trained with BIT-vehicle dataset. License plate is trained based on Chinese license plate that has white character on blue background. You will need to re-train your own model if you intend to use this in other countries.");
                Picker p = vehicleLicensePlateDetectorPage.Picker;
                p.IsVisible = true;
                p.Title = "Preferred DNN backend & target";

                foreach (String option in GetDnnBackends(DnnBackendType.InferenceEngineOnly))
                {
                    p.Items.Add(option);
                }
                this.Navigation.PushAsync(vehicleLicensePlateDetectorPage);
            };

            maskRcnnButton.Clicked += (sender, args) =>
            {
                ProcessAndRenderPage maskRcnnPage = new ProcessAndRenderPage(
                    new MaskRcnn(),
                    "Mask-rcnn Detection",
                    "dog416.png",
                    "");
                Picker p = maskRcnnPage.Picker;
                p.IsVisible = true;
                p.Title = "Preferred DNN backend & target";

                foreach (String option in GetDnnBackends())
                {
                    p.Items.Add(option);
                }

                this.Navigation.PushAsync(maskRcnnPage);
            };


            sceneTextDetectionButton.Clicked += (sender, args) =>
            {
                ProcessAndRenderPage sceneTextDetectionPage = new ProcessAndRenderPage(
                    new SceneTextDetector(),
                    "Perform Scene Text Detection",
                    "cars_license_plate.png",
                    "This model is trained on MSRA-TD500, so it can detect both English and Chinese text instances.");
                this.Navigation.PushAsync(sceneTextDetectionPage);
            };
            stopSignDetectionButton.Clicked += (sender, args) =>
            {
                MaskRcnn model = new MaskRcnn();
                model.ObjectsOfInterest = new string[] { "stop sign" };
                ProcessAndRenderPage stopSignDetectionPage = new ProcessAndRenderPage(
                    model,
                    "Mask-rcnn Detection",
                    "stop-sign.jpg",
                    "Stop sign detection using Mask RCNN");
                Picker p = stopSignDetectionPage.Picker;
                p.IsVisible = true;
                p.Title = "Preferred DNN backend & target";

                foreach (String option in GetDnnBackends())
                {
                    p.Items.Add(option);
                }
                this.Navigation.PushAsync(stopSignDetectionPage);
            };
            yoloButton.Clicked += (sender, args) =>
            {
                ProcessAndRenderPage yoloPage = new ProcessAndRenderPage(
                    new Yolo(),
                    "Yolo Detection",
                    "dog416.png",
                    "");
                Picker p = yoloPage.Picker;
                p.Title = "Yolo model version";
                p.IsVisible = true;
                p.Items.Add("YoloV4");
                p.Items.Add("YoloV4Tiny");
                p.Items.Add("YoloV3");
                p.Items.Add("YoloV3Spp");
                p.Items.Add("YoloV3Tiny");
                this.Navigation.PushAsync(yoloPage);
            };



            maskRcnnButton.IsVisible = haveDNN;
            //faceLandmarkDetectionButton.IsVisible = haveDNN;
            stopSignDetectionButton.IsVisible = haveDNN;
            yoloButton.IsVisible = haveDNN;
            sceneTextDetectionButton.IsVisible = haveDNN && haveFreetype;
            licensePlateRecognitionButton.IsVisible = hasInferenceEngine;
            featureDetectionButton.IsVisible = haveFeatures2D;
            
            
            if (haveTesseract)
            {
                Button ocrButton = new Button();
                ocrButton.Text = "Tesseract OCR";
                buttonList.Add(ocrButton);

                ocrButton.Clicked += (sender, args) =>
                {
                    ProcessAndRenderPage ocrPage = new ProcessAndRenderPage(
                        new TesseractModel(),
                        "Perform Text Detection",
                        "test_image.png",
                        "");
                    ocrPage.HasCameraOption = false;
                    this.Navigation.PushAsync(ocrPage);
                };
            } 

            if (haveVideo && haveCamera)
            {
                Button videoSurveillanceButton = new Button();
                videoSurveillanceButton.Text = "Video Surveillance";
                buttonList.Add(videoSurveillanceButton);

                videoSurveillanceButton.Clicked += (sender, args) =>
                {
                    ProcessAndRenderPage videoPage = new ProcessAndRenderPage(
                        new VideoSurveillanceModel(),
                        "Open Camera",
                        null,
                        "");
                    videoPage.HasCameraOption = true;
                    this.Navigation.PushAsync(videoPage);
                };
            }

            
            if (haveObjdetect)
            {
                Button faceDetectionButton = new Button();
                faceDetectionButton.Text = "Face Detection (CascadeClassifier)";
                buttonList.Add(faceDetectionButton);

                faceDetectionButton.Clicked += (sender, args) =>
                {
                    ProcessAndRenderPage faceAndEyeDetectorPage = new ProcessAndRenderPage(
                        new CascadeFaceAndEyeDetector(),
                        "Face and eye detection (Cascade classifier)",
                        "lena.jpg",
                        "Cascade classifier");
                    this.Navigation.PushAsync(faceAndEyeDetectorPage);
                };

                if (haveDNN)
                {
                    Button faceDetectionYNButton = new Button();
                    faceDetectionYNButton.Text = "FaceDetection Yunet";
                    buttonList.Add(faceDetectionYNButton);

                    faceDetectionYNButton.Clicked += (sender, args) =>
                    {
                        ProcessAndRenderPage faceDetectionYNPage = new ProcessAndRenderPage(
                            new FaceDetectorYNModel(),
                            "Face detection Yunet",
                            "lena.jpg",
                            "Face detection (Yunet)");
                        this.Navigation.PushAsync(faceDetectionYNPage);
                    };
                }

                Button pedestrianDetectionButton = new Button();
                pedestrianDetectionButton.Text = "Pedestrian Detection";
                buttonList.Add(pedestrianDetectionButton);

                pedestrianDetectionButton.Clicked += (sender, args) =>
                {
                    ProcessAndRenderPage pedestrianDetectorPage = new ProcessAndRenderPage(
                        new PedestrianDetector(),
                        "Pedestrian detection",
                        "pedestrian.png",
                        "HOG pedestrian detection");
                    this.Navigation.PushAsync(pedestrianDetectorPage);
                };

            }

            
            if (haveFace && haveDNN)
            {
                Button faceLandmarkDetectionButton = new Button();
                faceLandmarkDetectionButton.Text = "Face Landmark Detection (DNN Module)";
                buttonList.Add(faceLandmarkDetectionButton);
                faceLandmarkDetectionButton.Clicked += (sender, args) =>
                {
                    ProcessAndRenderPage faceLandmarkDetectionPage = new ProcessAndRenderPage(
                        new FaceAndLandmarkDetector(),
                        "Perform Face Landmark Detection",
                        "lena.jpg",
                        "");
                    this.Navigation.PushAsync(faceLandmarkDetectionPage);
                };
            }

            
            if (haveWechatQRCode && haveBarcode
              //TODO: WeChatQRCode detector doesn't work on iOS, probably a bug in iOS
              //Will need to figure out why.
              && (Microsoft.Maui.Devices.DeviceInfo.Platform != DevicePlatform.iOS)
              )
            {
                Button barcodeQrcodeDetectionButton = new Button();
                barcodeQrcodeDetectionButton.Text = "Barcode and QRCode Detection";
                buttonList.Add(barcodeQrcodeDetectionButton);
                barcodeQrcodeDetectionButton.Clicked += (sender, args) =>
                {
                    BarcodeDetectorModel barcodeDetector = new BarcodeDetectorModel();
                    WeChatQRCodeDetector qrcodeDetector = new WeChatQRCodeDetector();
                    CombinedModel combinedModel = new CombinedModel(barcodeDetector, qrcodeDetector);

                    ProcessAndRenderPage barcodeQrcodeDetectionPage = new ProcessAndRenderPage(
                        combinedModel,
                        "Perform Barcode and QRCode Detection",
                        "qrcode_barcode.png",
                        "");
                    this.Navigation.PushAsync(barcodeQrcodeDetectionPage);
                };
            }

            if (haveViz)
            {
                Button viz3dButton = new Button();
                viz3dButton.Text = "Simple 3D reconstruction";

                buttonList.Add(viz3dButton);

                viz3dButton.Clicked += (sender, args) =>
                {
                    using (Mat left = CvInvoke.Imread("imL.png", ImreadModes.Color))
                    using (Mat right = CvInvoke.Imread("imR.png", ImreadModes.Color))
                    using (Mat points = new Mat())
                    using (Mat colors = new Mat())
                    {
                        Simple3DReconstruct.GetPointAndColor(left, right, points, colors);
                        Viz3d v = Simple3DReconstruct.GetViz3d(points, colors);
                        v.Spin();
                    }
                };
            }

            if (haveFreetype)
            {
                Button freetypeButton = new Button();
                freetypeButton.Text = "Free Type";

                buttonList.Add(freetypeButton);

                freetypeButton.Clicked += (sender, args) =>
                {
                    this.Navigation.PushAsync(new FreetypePage());
                };
            }
            
            StackLayout buttonsLayout = new StackLayout
            {
                VerticalOptions = LayoutOptions.Start,
            };

            foreach (View b in buttonList)
                buttonsLayout.Children.Add(b);

            this.Content = new ScrollView()
            {
                Content = buttonsLayout,
            };
        }

        private enum DnnBackendType
        {
            Default,
            InferenceEngineOnly
        }

        private String[] GetDnnBackends(DnnBackendType backendType = DnnBackendType.Default)
        {
            var openCVConfigDict = CvInvoke.ConfigDict;
            bool haveDNN = (openCVConfigDict["HAVE_OPENCV_DNN"] != 0);

            if (haveDNN)
            {
                var dnnBackends = DnnInvoke.AvailableBackends;
                List<String> dnnBackendsText = new List<string>();
                foreach (var dnnBackend in dnnBackends)
                {
                    if (backendType == DnnBackendType.InferenceEngineOnly &&
                        !((dnnBackend.Backend == Emgu.CV.Dnn.Backend.InferenceEngine)
                          || (dnnBackend.Backend == Emgu.CV.Dnn.Backend.InferenceEngineNgraph)
                          || (dnnBackend.Backend == Emgu.CV.Dnn.Backend.InferenceEngineNnBuilder2019)))
                        continue;
                    dnnBackendsText.Add(String.Format("{0};{1}", dnnBackend.Backend, dnnBackend.Target));
                }

                return dnnBackendsText.ToArray();
            }
            else
            {
                return new string[0];
            }
        }

    }
}