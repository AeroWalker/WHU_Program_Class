﻿//----------------------------------------------------------------------------
//  Copyright (C) 2004-2023 by EMGU Corporation. All rights reserved.       
//----------------------------------------------------------------------------
using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;
using System.Drawing;
using Emgu.CV.Structure;
using Emgu.CV.Util;
using Emgu.Util;

namespace Emgu.CV.Stitching
{
    /// <summary>
    /// Simple blender which mixes images at its borders.
    /// </summary>
    public class FeatherBlender : Blender
    {
        /// <summary>
        /// Create a simple blender which mixes images at its borders
        /// </summary>
        /// <param name="sharpness">Sharpness</param>
        public FeatherBlender(float sharpness = 0.02f)
        {
            _ptr = StitchingInvoke.cveFeatherBlenderCreate(sharpness, ref _blenderPtr);
        }

        /// <summary>
        /// Release all the unmanaged memory associated with this blender
        /// </summary>
        protected override void DisposeObject()
        {
            base.DisposeObject();
            if (_ptr != IntPtr.Zero)
            {
                StitchingInvoke.cveFeatherBlenderRelease(ref _ptr);
            }
        }
    }

 
    public static partial class StitchingInvoke
    {

        [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
        internal static extern IntPtr cveFeatherBlenderCreate(float sharpness, ref IntPtr blender);
        [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
        internal static extern void cveFeatherBlenderRelease(ref IntPtr blender);

    }
}
