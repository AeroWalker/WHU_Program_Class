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

namespace Emgu.CV.Face
{
    /// <summary>
    /// Face Recognizer
    /// </summary>
    public abstract class FaceRecognizer : SharedPtrObject
    {
        /// <summary>
        /// The native pointer to the FaceRecognizer object 
        /// </summary>
        protected IntPtr _faceRecognizerPtr;

        /// <summary>
        /// Train the face recognizer with the specific images and labels
        /// </summary>
        /// <param name="images">The images used in the training. This can be a VectorOfMat</param>
        /// <param name="labels">The labels of the images. This can be a VectorOfInt</param>
        public void Train(IInputArrayOfArrays images, IInputArray labels)
        {
            using (InputArray iaImage = images.GetInputArray())
            using (InputArray iaLabels = labels.GetInputArray())
                FaceInvoke.cveFaceRecognizerTrain(_faceRecognizerPtr, iaImage, iaLabels);
        }

        /// <summary>
        /// Train the face recognizer with the specific images and labels
        /// </summary>
        /// <param name="images">The images used in the training.</param>
        /// <param name="labels">The labels of the images.</param>
        public void Train(Mat[] images, int[] labels)
        {
            using (VectorOfMat imgVec = new VectorOfMat())
            using (VectorOfInt labelVec = new VectorOfInt(labels))
            {
                imgVec.Push(images);
                Train(imgVec, labelVec);
            }
        }

        /// <summary>
        /// Predict the label of the image
        /// </summary>
        /// <param name="image">The image where prediction will be based on</param>
        /// <returns>The prediction label</returns>
        public PredictionResult Predict(IInputArray image)
        {
            int label = -1;
            double distance = -1;
            using (InputArray iaImage = image.GetInputArray())
                FaceInvoke.cveFaceRecognizerPredict(_faceRecognizerPtr, iaImage, ref label, ref distance);
            return new PredictionResult() { Label = label, Distance = distance };
        }

        /// <summary>
        /// The prediction result
        /// </summary>
        public struct PredictionResult
        {
            /// <summary>
            /// The label
            /// </summary>
            public int Label;

            /// <summary>
            /// The distance
            /// </summary>
            public double Distance;
        }

        /// <summary>
        /// Save the FaceRecognizer to a file
        /// </summary>
        /// <param name="fileName">The file name to be saved to</param>
        public void Write(String fileName)
        {
            using (CvString s = new CvString(fileName))
                FaceInvoke.cveFaceRecognizerWrite(_faceRecognizerPtr, s);
        }

        /// <summary>
        /// Load the FaceRecognizer from the file
        /// </summary>
        /// <param name="fileName">The file where the FaceRecognizer will be loaded from</param>
        public void Read(String fileName)
        {
            using (CvString s = new CvString(fileName))
                FaceInvoke.cveFaceRecognizerRead(_faceRecognizerPtr, s);
        }

        /// <summary>
        /// Sets string info for the specified model's label.
        /// </summary>
        /// <param name="label">The label</param>
        /// <param name="strInfo">The string info</param>
        /// <remarks>The string info is replaced by the provided value if it was set before for the specified label.</remarks>
        public void SetLabelInfo(int label, String strInfo)
        {
            using (CvString csStrInfo = new CvString(strInfo))
            {
                FaceInvoke.cveFaceRecognizerSetLabelInfo(_faceRecognizerPtr, label, csStrInfo);
            }
        }

        /// <summary>
        /// Gets string information by label. If an unknown label id is provided or there is no label information associated with the specified label id the method returns an empty string.
        /// </summary>
        /// <param name="label">The label</param>
        /// <returns>The string associated with this label.</returns>
        public String GetLabelInfo(int label)
        {
            using (CvString csStrInfo = new CvString())
            {
                FaceInvoke.cveFaceRecognizerGetLabelInfo(_faceRecognizerPtr, label, csStrInfo);
                return csStrInfo.ToString();
            }
        }

        /// <summary>
        /// Release the unmanaged memory associated with this FaceRecognizer
        /// </summary>
        protected override void DisposeObject()
        {
            _faceRecognizerPtr = IntPtr.Zero;
        }
    }

    /// <summary>
    /// Class that contains entry points for the Face module.
    /// </summary>
    public static partial class FaceInvoke
    {
        static FaceInvoke()
        {
            CvInvoke.Init();
        }

        [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
        internal static extern void cveFaceRecognizerTrain(IntPtr recognizer, IntPtr images, IntPtr labels);

        [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
        internal static extern void cveFaceRecognizerPredict(IntPtr recognizer, IntPtr image, ref int label, ref double distance);
        [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
        internal static extern void cveFaceRecognizerWrite(
           IntPtr recognizer,
           IntPtr fileName);
        [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
        internal static extern void cveFaceRecognizerRead(
           IntPtr recognizer,
           IntPtr fileName);


        [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
        internal static extern void cveFaceRecognizerUpdate(IntPtr recognizer, IntPtr images, IntPtr labels);

        [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
        internal static extern void cveFaceRecognizerSetLabelInfo(IntPtr recognizer, int label, IntPtr strInfo);

        [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
        internal static extern void cveFaceRecognizerGetLabelInfo(IntPtr recognizer, int label, IntPtr strInfo);
    }


}
