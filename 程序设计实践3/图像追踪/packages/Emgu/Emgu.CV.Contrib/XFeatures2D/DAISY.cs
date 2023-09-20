﻿//----------------------------------------------------------------------------
//  Copyright (C) 2004-2023 by EMGU Corporation. All rights reserved.       
//----------------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Text;
using Emgu.CV;
using Emgu.CV.CvEnum;
using Emgu.CV.Structure;
using Emgu.CV.Util;
using Emgu.Util;
using Emgu.CV.Features2D;

namespace Emgu.CV.XFeatures2D
{
    /// <summary>
    /// DAISY descriptor.
    /// </summary>
    public class DAISY : Feature2D
    {
        /// <summary>
        /// Create DAISY descriptor extractor
        /// </summary>
        /// <param name="radius">Radius of the descriptor at the initial scale.</param>
        /// <param name="qRadius">Amount of radial range division quantity.</param>
        /// <param name="qTheta">Amount of angular range division quantity.</param>
        /// <param name="qHist">Amount of gradient orientations range division quantity.</param>
        /// <param name="norm">Descriptors normalization type.</param>
        /// <param name="H">optional 3x3 homography matrix used to warp the grid of daisy but sampling keypoints remains unwarped on image</param>
        /// <param name="interpolation">Switch to disable interpolation for speed improvement at minor quality loss</param>
        /// <param name="useOrientation">Sample patterns using keypoints orientation, disabled by default.</param>
        public DAISY(float radius = 15, int qRadius = 3, int qTheta = 8,
           int qHist = 8, NormalizationType norm = NormalizationType.None, IInputArray H = null,
           bool interpolation = true, bool useOrientation = false)
        {
            using (InputArray iaH = H == null ? InputArray.GetEmpty() : H.GetInputArray())
                _ptr = XFeatures2DInvoke.cveDAISYCreate(radius, qRadius, qTheta, qHist, norm, iaH, interpolation, useOrientation,
                   ref _feature2D, ref _sharedPtr);
        }

        /// <summary>
        /// Normalization type
        /// </summary>
        public enum NormalizationType
        {
            /// <summary>
            /// Will not do any normalization (default)
            /// </summary>
            None = 100,

            /// <summary>
            /// Histograms are normalized independently for L2 norm equal to 1.0
            /// </summary>
            Partial = 101,

            /// <summary>
            /// Descriptors are normalized for L2 norm equal to 1.0
            /// </summary>
            Full = 102,

            /// <summary>
            /// Descriptors are normalized for L2 norm equal to 1.0 but no individual one is bigger than 0.154 as in SIFT
            /// </summary>
            SIFT = 103
        }

        /// <summary>
        /// Release all the unmanaged resource associated with DAISY
        /// </summary>
        protected override void DisposeObject()
        {
            if (_sharedPtr != IntPtr.Zero)
            {
                XFeatures2DInvoke.cveDAISYRelease(ref _sharedPtr);
            }
            base.DisposeObject();
        }
    }

    public static partial class XFeatures2DInvoke
    {
        [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
        internal static extern IntPtr cveDAISYCreate(
           float radius, 
           int qRadius, 
           int qTheta,
           int qHist, 
           XFeatures2D.DAISY.NormalizationType norm, 
           IntPtr H,
           [MarshalAs(CvInvoke.BoolMarshalType)]
           bool interpolation,
           [MarshalAs(CvInvoke.BoolMarshalType)]
           bool useOrientation,
           ref IntPtr daisy,
           ref IntPtr sharedPtr);

        [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
        internal static extern void cveDAISYRelease(ref IntPtr shared);
    }
}