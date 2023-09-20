//----------------------------------------------------------------------------
//  Copyright (C) 2004-2023 by EMGU Corporation. All rights reserved.       
//----------------------------------------------------------------------------

using System;
using System.Diagnostics;
using System.IO;
using System.Runtime.InteropServices;
using Emgu.CV;
using Emgu.CV.Structure;
using Emgu.CV.Util;
using Emgu.Util;

namespace Emgu.CV.Quality
{
    /// <summary>
    /// Mean square error algorithm
    /// </summary>
    public class QualityMSE : SharedPtrObject, IQualityBase
    {
        private IntPtr _qualityBasePtr;
        private IntPtr _algorithmPtr;

        /// <summary>
        /// Pointer to the native QualityBase object
        /// </summary>
        public IntPtr QualityBasePtr
        {
            get { return _qualityBasePtr; }
        }

        /// <summary>
        /// Pointer to the native algorithm object
        /// </summary>
        public IntPtr AlgorithmPtr
        {
            get { return _algorithmPtr; }
        }

        /// <summary>
        /// Create a new instance of MSE quality measurement.
        /// </summary>
        /// <param name="refImgs">vector of reference images, converted to internal type</param>
        public QualityMSE(IInputArrayOfArrays refImgs)
        {
            using (InputArray iaRefImgs = refImgs.GetInputArray())
                _ptr = QualityInvoke.cveQualityMSECreate(
                    iaRefImgs,
                    ref _qualityBasePtr,
                    ref _algorithmPtr,
                    ref _sharedPtr);
        }

        /// <summary>
        /// Release the unmanaged memory associated with this object
        /// </summary>
        protected override void DisposeObject()
        {
            if (_sharedPtr != IntPtr.Zero)
            {
                QualityInvoke.cveQualityMSERelease(ref _sharedPtr);
                _ptr = IntPtr.Zero;
                _algorithmPtr = IntPtr.Zero;
                _qualityBasePtr = IntPtr.Zero;
            }
        }

    }


    /// <summary>
    /// Class that contains entry points for the Quality module.
    /// </summary>
    public static partial class QualityInvoke
    {

        [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
        internal static extern IntPtr cveQualityMSECreate(
            IntPtr refImgs,
            ref IntPtr qualityBase,
            ref IntPtr algorithm,
            ref IntPtr sharedPtr);

        [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
        internal static extern void cveQualityMSERelease(ref IntPtr sharedPtr);
    }


}
