//----------------------------------------------------------------------------
//  Copyright (C) 2004-2023 by EMGU Corporation. All rights reserved.       
//----------------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
using Emgu.CV.Structure;
using Emgu.CV.Util;
using Emgu.Util;
using System.Diagnostics;
using System.Drawing;

namespace Emgu.CV.Legacy
{
    /// <summary>
    /// This is a real-time object tracking based on a novel on-line version of the AdaBoost algorithm. 
    /// The classifier uses the surrounding background as negative examples in update step to avoid the drifting problem.
    /// </summary>
    public class TrackerBoosting : Tracker
    {
        private IntPtr _sharedPtr;

        /// <summary>
        /// Create a Boosting Tracker
        /// </summary>
        /// <param name="numClassifiers">The number of classifiers to use in a OnlineBoosting algorithm</param>
        /// <param name="samplerOverlap">Search region parameters to use in a OnlineBoosting algorithm</param>
        /// <param name="samplerSearchFactor">search region parameters to use in a OnlineBoosting algorithm</param>
        /// <param name="iterationInit">The initial iterations</param>
        /// <param name="featureSetNumFeatures">Number of features, a good value would be 10*numClassifiers + iterationInit</param>
        public TrackerBoosting(
            int numClassifiers = 100, 
            float samplerOverlap = 0.99f, 
            float samplerSearchFactor = 1.8f, 
            int iterationInit = 50, 
            int featureSetNumFeatures = 100*10+50)
        {
            TrackingInvoke.cveTrackerBoostingCreate(
                numClassifiers, 
                samplerOverlap, 
                samplerSearchFactor, 
                iterationInit, 
                featureSetNumFeatures, 
                ref _trackerPtr, 
                ref _sharedPtr);
        }

        /// <summary>
        /// Release all the unmanaged memory associated with this Boosting Tracker
        /// </summary>
        protected override void DisposeObject()
        {
            if (IntPtr.Zero != _ptr)
                TrackingInvoke.cveTrackerBoostingRelease(ref _ptr, ref _sharedPtr);
            base.DisposeObject();
            
        }
    }
}

namespace Emgu.CV
{
    public static partial class TrackingInvoke
    {

        [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
        internal static extern IntPtr cveTrackerBoostingCreate(int numClassifiers, float samplerOverlap, float samplerSearchFactor, int iterationInit, int featureSetNumFeatures, ref IntPtr tracker, ref IntPtr sharedPtr);

        [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
        internal static extern void cveTrackerBoostingRelease(ref IntPtr tracker, ref IntPtr sharedPtr);

    }
}

