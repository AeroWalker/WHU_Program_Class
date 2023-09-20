﻿//----------------------------------------------------------------------------
//  Copyright (C) 2004-2023 by EMGU Corporation. All rights reserved.       
//----------------------------------------------------------------------------

using System;
using System.Collections;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Emgu.CV;
using Emgu.CV.CvEnum;
using Emgu.CV.Dnn;
using Emgu.CV.Face;
using Emgu.CV.Structure;
using Emgu.CV.Util;
using Emgu.Util;

namespace Emgu.CV.Models
{
    /// <summary>
    /// Process and render model
    /// </summary>
    public interface IProcessAndRenderModel : IDisposable
    {
        /// <summary>
        /// Clear and reset the model. Required Init function to be called again before calling ProcessAndRender.
        /// </summary>
        void Clear();

        /// <summary>
        /// Return true if the model is initialized
        /// </summary>
        bool Initialized { get; }

        /// <summary>
        /// Download and initialize the model
        /// </summary>
        /// <param name="onDownloadProgressChanged">Callback when download progress has been changed</param>
        /// <param name="initOptions">Initialization options</param>
        /// <returns>Async task</returns>
#if UNITY_EDITOR || UNITY_IOS || UNITY_ANDROID || UNITY_STANDALONE || UNITY_WEBGL
        IEnumerator Init(FileDownloadManager.DownloadProgressChangedEventHandler onDownloadProgressChanged, Object initOptions);
#else
        Task Init(FileDownloadManager.DownloadProgressChangedEventHandler onDownloadProgressChanged, Object initOptions);
#endif

        /// <summary>
        /// Process the input image and render into the output image
        /// </summary>
        /// <param name="imageIn">The input image</param>
        /// <param name="imageOut">
        /// The output image, can be the same as <paramref name="imageIn"/>, in which case we will render directly into the input image.
        /// Note that if no object is detected, <paramref name="imageOut"/> will remain unchanged.
        /// If objects are detected, we will draw the label and (rectangle) regions on top of the existing pixels of <paramref name="imageOut"/>.
        /// If the <paramref name="imageOut"/> is not the same object as <paramref name="imageIn"/>, it is a good idea to copy the pixels over from the input image before passing it to this function.
        /// </param>
        /// <returns>The messages that we want to display.</returns>
        String ProcessAndRender(IInputArray imageIn, IInputOutputArray imageOut);
    }
}
