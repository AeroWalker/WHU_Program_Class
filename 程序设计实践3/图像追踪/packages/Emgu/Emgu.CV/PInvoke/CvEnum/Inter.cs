//----------------------------------------------------------------------------
//  Copyright (C) 2004-2023 by EMGU Corporation. All rights reserved.       
//----------------------------------------------------------------------------

using System;

namespace Emgu.CV.CvEnum
{
    /// <summary>
    /// Interpolation types
    /// </summary>
    public enum Inter
    {
        /// <summary>
        /// Nearest-neighbor interpolation
        /// </summary>
        Nearest = 0,

        /// <summary>
        /// Bilinear interpolation
        /// </summary>
        Linear = 1,

        /// <summary>
        /// Bicubic interpolation
        /// </summary>
        Cubic = 2,

        /// <summary>
        /// Resampling using pixel area relation. It is the preferred method for image decimation that gives moire-free results. In case of zooming it is similar to CV_INTER_NN method
        /// </summary>
        Area = 3,

        /// <summary>
        /// Lanczos interpolation over 8x8 neighborhood
        /// </summary>
        Lanczos4 = 4,

        /// <summary>
        /// Bit exact bilinear interpolation
        /// </summary>
        LinearExact = 5,

        /// <summary>
        /// Bit exact nearest neighbor interpolation. This will produce same results as
        /// the nearest neighbor method in PIL, scikit-image or Matlab.
        /// </summary>
        NearestExact = 6,
    }
}
