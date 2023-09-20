﻿//----------------------------------------------------------------------------
//  Copyright (C) 2004-2023 by EMGU Corporation. All rights reserved.       
//----------------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Data.SqlTypes;
using System.Diagnostics;
using System.Text;
using System.IO;
using System.Drawing;
using System.Net;
using System.Threading.Tasks;

using Emgu.CV;
using Emgu.CV.CvEnum;
using Emgu.CV.Structure;
using Emgu.Util;
using Emgu.CV.Util;

namespace Emgu.CV.Models
{
    public class ShapeDetector : DisposableObject, IProcessAndRenderModel
    {
        private Mat _gray = new Mat();
        private Mat _cannyEdges = new Mat();

        /// <summary>
        /// Clear and reset the model. Required Init function to be called again before calling ProcessAndRender.
        /// </summary>
        public void Clear()
        {

        }

        public bool Initialized
        {
            get
            {
                return true;
            }
        }

        protected override void DisposeObject()
        {
            if (_gray != null)
            {
                _gray.Dispose();
                _gray = null;
            }

            if (_cannyEdges != null)
            {
                _cannyEdges.Dispose();
                _cannyEdges = null;
            }
        }

        public string ProcessAndRender(IInputArray imageIn, IInputOutputArray imageOut)
        {
            Stopwatch watch = Stopwatch.StartNew();

            #region Pre-processing
            //Convert the image to grayscale and filter out the noise
            CvInvoke.CvtColor(imageIn, _gray, ColorConversion.Bgr2Gray);
            //Remove noise
            CvInvoke.GaussianBlur(_gray, _gray, new Size(3, 3), 1);
            double cannyThreshold = 180.0;
            double cannyThresholdLinking = 120.0;
            CvInvoke.Canny(_gray, _cannyEdges, cannyThreshold, cannyThresholdLinking);
            #endregion

            #region circle detection
            double circleAccumulatorThreshold = 120;
            CircleF[] circles = CvInvoke.HoughCircles(_gray, HoughModes.Gradient, 2.0, 20.0, cannyThreshold,
                circleAccumulatorThreshold, 5);
            #endregion

            #region Edge detection
            LineSegment2D[] lines = CvInvoke.HoughLinesP(
                _cannyEdges,
                1, //Distance resolution in pixel-related units
                Math.PI / 45.0, //Angle resolution measured in radians.
                20, //threshold
                30, //min Line width
                10); //gap between lines
            #endregion

            #region Find triangles and rectangles
            List<Triangle2DF> triangleList = new List<Triangle2DF>();
            List<RotatedRect> boxList = new List<RotatedRect>(); //a box is a rotated rectangle
            using (VectorOfVectorOfPoint contours = new VectorOfVectorOfPoint())
            {
                CvInvoke.FindContours(_cannyEdges, contours, null, RetrType.List,
                    ChainApproxMethod.ChainApproxSimple);
                int count = contours.Size;
                for (int i = 0; i < count; i++)
                {
                    using (VectorOfPoint contour = contours[i])
                    using (VectorOfPoint approxContour = new VectorOfPoint())
                    {
                        CvInvoke.ApproxPolyDP(contour, approxContour, CvInvoke.ArcLength(contour, true) * 0.05,
                            true);
                        if (CvInvoke.ContourArea(approxContour, false) > 250
                        ) //only consider contours with area greater than 250
                        {
                            if (approxContour.Size == 3) //The contour has 3 vertices, it is a triangle
                            {
                                Point[] pts = approxContour.ToArray();
                                triangleList.Add(new Triangle2DF(
                                    pts[0],
                                    pts[1],
                                    pts[2]
                                ));
                            }
                            else if (approxContour.Size == 4) //The contour has 4 vertices.
                            {
                                #region determine if all the angles in the contour are within [80, 100] degree

                                bool isRectangle = true;
                                Point[] pts = approxContour.ToArray();
                                LineSegment2D[] edges = PointCollection.PolyLine(pts, true);

                                for (int j = 0; j < edges.Length; j++)
                                {
                                    double angle = Math.Abs(
                                        edges[(j + 1) % edges.Length].GetExteriorAngleDegree(edges[j]));
                                    if (angle < 80 || angle > 100)
                                    {
                                        isRectangle = false;
                                        break;
                                    }
                                }

                                #endregion

                                if (isRectangle) boxList.Add(CvInvoke.MinAreaRect(approxContour));
                            }
                        }
                    }
                }
            }
            #endregion

            watch.Stop();

            using (Mat triangleRectangleImage = new Mat(_gray.Size, DepthType.Cv8U, 3)) //image to draw triangles and rectangles on
            using (Mat circleImage = new Mat(_gray.Size, DepthType.Cv8U, 3)) //image to draw circles on
            using (Mat lineImage = new Mat(_gray.Size, DepthType.Cv8U, 3)) //image to draw lines on
            {
                #region draw triangles and rectangles

                triangleRectangleImage.SetTo(new MCvScalar(0));
                foreach (Triangle2DF triangle in triangleList)
                {
                    CvInvoke.Polylines(triangleRectangleImage,
                        Array.ConvertAll(triangle.GetVertices(), Point.Round),
                        true, new Bgr(Color.DarkBlue).MCvScalar, 2);
                }

                foreach (RotatedRect box in boxList)
                {
                    CvInvoke.Polylines(triangleRectangleImage, Array.ConvertAll(box.GetVertices(), Point.Round),
                        true,
                        new Bgr(Color.DarkOrange).MCvScalar, 2);
                }

                //Drawing a light gray frame around the image
                CvInvoke.Rectangle(triangleRectangleImage,
                    new Rectangle(Point.Empty,
                        new Size(triangleRectangleImage.Width - 1, triangleRectangleImage.Height - 1)),
                    new MCvScalar(120, 120, 120));
                //Draw the labels
                CvInvoke.PutText(triangleRectangleImage, "Triangles and Rectangles", new Point(20, 20),
                    FontFace.HersheyDuplex, 0.5, new MCvScalar(120, 120, 120));

                #endregion

                #region draw circles

                circleImage.SetTo(new MCvScalar(0));
                foreach (CircleF circle in circles)
                    CvInvoke.Circle(circleImage, Point.Round(circle.Center), (int)circle.Radius,
                        new Bgr(Color.Brown).MCvScalar, 2);

                //Drawing a light gray frame around the image
                CvInvoke.Rectangle(circleImage,
                    new Rectangle(Point.Empty, new Size(circleImage.Width - 1, circleImage.Height - 1)),
                    new MCvScalar(120, 120, 120));
                //Draw the labels
                CvInvoke.PutText(circleImage, "Circles", new Point(20, 20), FontFace.HersheyDuplex, 0.5,
                    new MCvScalar(120, 120, 120));

                #endregion

                #region draw lines

                lineImage.SetTo(new MCvScalar(0));
                foreach (LineSegment2D line in lines)
                    CvInvoke.Line(lineImage, line.P1, line.P2, new Bgr(Color.Green).MCvScalar, 2);
                //Drawing a light gray frame around the image
                CvInvoke.Rectangle(lineImage,
                    new Rectangle(Point.Empty, new Size(lineImage.Width - 1, lineImage.Height - 1)),
                    new MCvScalar(120, 120, 120));
                //Draw the labels
                CvInvoke.PutText(lineImage, "Lines", new Point(20, 20), FontFace.HersheyDuplex, 0.5,
                    new MCvScalar(120, 120, 120));

                #endregion


                using (InputArray iaImageIn = imageIn.GetInputArray())
                using (Mat imageInMat = iaImageIn.GetMat())
                    CvInvoke.VConcat(new Mat[] { imageInMat, triangleRectangleImage, circleImage, lineImage }, imageOut);

            }
            return String.Format("Detected in {0} milliseconds.", watch.ElapsedMilliseconds);

        }

        public async Task Init(FileDownloadManager.DownloadProgressChangedEventHandler onDownloadProgressChanged = null, Object initOptions = null)
        {
            //do nothing, no need to initialize
            await Task.Delay(0);
        }


    }
}
