﻿//----------------------------------------------------------------------------
//  Copyright (C) 2004-2023 by EMGU Corporation. All rights reserved.       
//----------------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Text;
using Emgu.CV;
using Emgu.CV.Structure;
using Emgu.Util;
using System.Runtime.InteropServices;

namespace Emgu.CV.Flann
{
    internal static partial class FlannInvoke
    {
        static FlannInvoke()
        {
            CvInvoke.Init();
        }

        [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
        internal static extern IntPtr cveFlannIndexCreate(IntPtr features, IntPtr ip, Emgu.CV.Flann.DistType distType);

        //[DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
        //internal static extern IntPtr CvFlannIndexCreateComposite(IntPtr features, int numberOfKDTrees, int branching, int iterations, Flann.CenterInitType centersInitType, float cbIndex);

        //[DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
        //internal static extern IntPtr CvFlannIndexCreateAutotuned(IntPtr features, float targetPrecision, float buildWeight, float memoryWeight, float sampleFraction);

        [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
        internal static extern void cveFlannIndexRelease(ref IntPtr index);

        [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
        internal static extern void cveFlannIndexKnnSearch(
            IntPtr index,
            IntPtr queries,
            IntPtr indices,
            IntPtr dists,
            int knn,
            int checks,
            float eps,
            [MarshalAs(UnmanagedType.Bool)]
            bool sorted);

        [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
        internal static extern int cveFlannIndexRadiusSearch(
            IntPtr index,
            IntPtr queries,
            IntPtr indices,
            IntPtr dists,
            double radius,
            int maxResults,
            int checks,
            float eps,
            [MarshalAs(UnmanagedType.Bool)]
            bool sorted);


        [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
        internal static extern IntPtr cveLinearIndexParamsCreate(ref IntPtr ip);

        [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
        internal static extern void cveLinearIndexParamsRelease(ref IntPtr p);

        [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
        internal static extern IntPtr cveKDTreeIndexParamsCreate(ref IntPtr ip, int trees);

        [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
        internal static extern void cveKDTreeIndexParamsRelease(ref IntPtr p);

        [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
        internal static extern IntPtr cveLshIndexParamsCreate(ref IntPtr ip, int tableNumber, int keySize, int multiProbeLevel);

        [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
        internal static extern void cveLshIndexParamsRelease(ref IntPtr p);

        [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
        internal static extern IntPtr cveKMeansIndexParamsCreate(ref IntPtr ip, int branching, int iterations, Flann.CenterInitType centersInit, float cbIndex);

        [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
        internal static extern void cveKMeansIndexParamsRelease(ref IntPtr p);

        [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
        internal static extern IntPtr cveCompositeIndexParamsCreate(ref IntPtr ip, int trees, int branching, int iterations, Flann.CenterInitType centersInit, float cbIndex);

        [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
        internal static extern void cveCompositeIndexParamsRelease(ref IntPtr p);

        [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
        internal static extern IntPtr cveAutotunedIndexParamsCreate(ref IntPtr ip, float targetPrecision, float buildWeight, float memoryWeight, float sampleFraction);
        [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
        internal static extern void cveAutotunedIndexParamsRelease(ref IntPtr p);

        [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
        internal static extern IntPtr cveHierarchicalClusteringIndexParamsCreate(ref IntPtr ip, int branching, Flann.CenterInitType centersInit, int trees, int leafSize);
        [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
        internal static extern void cveHierarchicalClusteringIndexParamsRelease(ref IntPtr p);

        [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
        internal static extern IntPtr cveSearchParamsCreate(
            ref IntPtr ip, int checks, float eps,
            [MarshalAs(CvInvoke.BoolMarshalType)]
            bool sorted);

        [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
        internal static extern void cveSearchParamsRelease(ref IntPtr p);
    }
}
