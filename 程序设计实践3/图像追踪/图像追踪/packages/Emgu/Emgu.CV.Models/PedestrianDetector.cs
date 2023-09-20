﻿//----------------------------------------------------------------------------
//  Copyright (C) 2004-2023 by EMGU Corporation. All rights reserved.       
//----------------------------------------------------------------------------

using System;
using System.Collections;
using System.Collections.Generic;
using Emgu.CV;
using Emgu.CV.CvEnum;
using Emgu.CV.Structure;
using System.Drawing;
using System.Diagnostics;
using Emgu.CV.Util;
#if !(UNITY_EDITOR || UNITY_IOS || UNITY_ANDROID || UNITY_STANDALONE || UNITY_WEBGL)
using Emgu.CV.Cuda;
#endif
using System.Threading.Tasks;
using System.Net;
using Emgu.Util;

namespace Emgu.CV.Models
{
    /// <summary>
    /// Pedestrian detector
    /// </summary>
    public class PedestrianDetector : DisposableObject, IProcessAndRenderModel
    {
#if !(UNITY_EDITOR || UNITY_IOS || UNITY_ANDROID || UNITY_STANDALONE || UNITY_WEBGL)
        private CudaHOG _hogCuda;
#endif
        private HOGDescriptor _hog;

        /// <summary>
        /// Clear and reset the model. Required Init function to be called again before calling ProcessAndRender.
        /// </summary>
        public void Clear()
        {
            if (_hog != null)
            {
                _hog.Dispose();
                _hog = null;
            }

#if !(UNITY_EDITOR || UNITY_IOS || UNITY_ANDROID || UNITY_STANDALONE || UNITY_WEBGL)
            if (_hogCuda != null)
            {
                _hogCuda.Dispose();
                _hog = null;
            }
#endif
        }

        /// <summary>
        /// Release the memory associated with this pedestrian detector
        /// </summary>
        protected override void DisposeObject()
        {
            Clear();
        }

        /// <summary>
        /// Find the pedestrian in the image
        /// </summary>
        /// <param name="image">The image</param>
        /// <returns>The region where pedestrians are detected</returns>
        public Rectangle[] Find(IInputArray image)
        {
            Rectangle[] regions;

            using (InputArray iaImage = image.GetInputArray())
            {
#if !(UNITY_EDITOR || UNITY_IOS || UNITY_ANDROID || UNITY_STANDALONE || UNITY_WEBGL)
                //if the input array is a GpuMat
                //check if there is a compatible Cuda device to run pedestrian detection
                if (iaImage.Kind == InputArray.Type.CudaGpuMat && _hogCuda != null)
                {
                    //this is the Cuda version
                    using (GpuMat cudaBgra = new GpuMat())
                    using (VectorOfRect vr = new VectorOfRect())
                    {
                        CudaInvoke.CvtColor(image, cudaBgra, ColorConversion.Bgr2Bgra);
                        _hogCuda.DetectMultiScale(cudaBgra, vr);
                        regions = vr.ToArray();
                    }
                }
                else
#endif
                {
                    //this is the CPU/OpenCL version
                    MCvObjectDetection[] results = _hog.DetectMultiScale(image);
                    regions = new Rectangle[results.Length];
                    for (int i = 0; i < results.Length; i++)
                        regions[i] = results[i].Rect;
                }

                return regions;
            }
        }

        /// <summary>
        /// Return true if the model is initialized
        /// </summary>
        public bool Initialized
        {
            get
            {
                if (_hog == null)
                    return false;
#if !(UNITY_EDITOR || UNITY_IOS || UNITY_ANDROID || UNITY_STANDALONE || UNITY_WEBGL)
                if (CudaInvoke.HasCuda)
                {
                    if (_hogCuda == null)
                        return false;
                }
#endif
                return true;
            }
        }

        /// <summary>
        /// Initialize the pedestrian detection model
        /// </summary>
        /// <param name="onDownloadProgressChanged">Call back method during download</param>
        /// <param name="initOptions">Initialization options. None supported at the moment, any value passed will be ignored.</param>
        /// <returns>Asyn task</returns>
#if UNITY_EDITOR || UNITY_IOS || UNITY_ANDROID || UNITY_STANDALONE || UNITY_WEBGL
        public IEnumerator Init(FileDownloadManager.DownloadProgressChangedEventHandler onDownloadProgressChanged = null, Object initOptions = null)
#else
        public async Task Init(FileDownloadManager.DownloadProgressChangedEventHandler onDownloadProgressChanged = null, Object initOptions = null)
#endif
        {
            _hog = new HOGDescriptor();
            _hog.SetSVMDetector(HOGDescriptor.GetDefaultPeopleDetector());

#if UNITY_EDITOR || UNITY_IOS || UNITY_ANDROID || UNITY_STANDALONE || UNITY_WEBGL
            yield return null;
#else
            if (CudaInvoke.HasCuda)
            {
                _hogCuda = new CudaHOG(
                    new Size(64, 128),
                    new Size(16, 16),
                    new Size(8, 8),
                    new Size(8, 8));
                _hogCuda.SetSVMDetector(_hogCuda.GetDefaultPeopleDetector());
            }

            await Task.Delay(1);
#endif
        }

        private MCvScalar _renderColor = new MCvScalar(0, 0, 255);

        /// <summary>
        /// Get or Set the color used in rendering the rectangle around the object.
        /// </summary>
        public MCvScalar RenderColor
        {
            get
            {
                return _renderColor;
            }
            set
            {
                _renderColor = value;
            }
        }

        /// <summary>
        /// Process the input image and render into the output image
        /// </summary>
        /// <param name="imageIn">The input image</param>
        /// <param name="imageOut">
        /// The output image, can be the same as <paramref name="imageIn"/>, in which case we will render directly into the input image.
        /// Note that if no pedestrian is detected, <paramref name="imageOut"/> will remain unchanged.
        /// If a pedestrian is detected, we will draw the (rectangle) region on top of the existing pixels of <paramref name="imageOut"/>.
        /// If the <paramref name="imageOut"/> is not the same object as <paramref name="imageIn"/>, it is a good idea to copy the pixels over from the input image before passing it to this function.
        /// </param>
        /// <returns>The messages that we want to display.</returns>
        public string ProcessAndRender(IInputArray imageIn, IInputOutputArray imageOut)
        {
            Stopwatch watch = Stopwatch.StartNew();
            Rectangle[] pedestrians = Find(imageIn);
            watch.Stop();

            foreach (Rectangle rect in pedestrians)
            {
                CvInvoke.Rectangle(imageOut, rect, RenderColor, 2);
            }

            return String.Format("Detected in {0} milliseconds.", watch.ElapsedMilliseconds);
        }
    }
}
