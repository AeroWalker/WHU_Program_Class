//----------------------------------------------------------------------------
//  Copyright (C) 2004-2023 by EMGU Corporation. All rights reserved.       
//----------------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
using Emgu.CV.Structure;
using Emgu.CV.Text;
using Emgu.CV.Util;
using Emgu.Util;
using System.Diagnostics;

namespace Emgu.CV.ImgHash
{
    /// <summary>
    /// The module brings implementation of the image processing algorithms based on fuzzy mathematics.
    /// </summary>
    internal static partial class ImgHashInvoke
    {
        static ImgHashInvoke()
        {
            CvInvoke.Init();
        }

        [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
        internal static extern void cveImgHashBaseCompute(IntPtr imgHash, IntPtr inputArr, IntPtr outputArr);
        [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
        internal static extern double cveImgHashBaseCompare(IntPtr imgHash, IntPtr hashOne, IntPtr hashTwo);

    }
}