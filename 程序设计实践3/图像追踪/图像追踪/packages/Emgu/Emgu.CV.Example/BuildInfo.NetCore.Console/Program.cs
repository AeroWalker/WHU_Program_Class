﻿//----------------------------------------------------------------------------
//  Copyright (C) 2004-2023 by EMGU Corporation. All rights reserved.       
//----------------------------------------------------------------------------

using System;
using Emgu.CV;
using Emgu.CV.Dnn;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Text;
using Emgu.CV.Cuda;
using Emgu.CV.CvEnum;
using Emgu.Util;

namespace BuildInfo.NetCore.Console
{
    class Program
    {
        static void Main(string[] args)
        {
            CvInvoke.LogLevel = LogLevel.Verbose;

            System.Console.WriteLine(CvInvoke.BuildInformation);

            System.Console.WriteLine(GetDnnInfo() + System.Environment.NewLine);

            System.Console.WriteLine(GetOpenCLInfo() + System.Environment.NewLine);

            System.Console.WriteLine(GetCudaInfo() + System.Environment.NewLine);

            System.Console.WriteLine(GetCaptureInfo() + System.Environment.NewLine);

            System.Console.WriteLine(GetRuntimeInfo() + System.Environment.NewLine);

            System.Console.WriteLine(GetParallelBackendInfo() + System.Environment.NewLine);

            System.Console.WriteLine(GetDepthAIInfo() + System.Environment.NewLine);
        }

        private static String GetDnnInfo()
        {
            var openCVConfigDict = CvInvoke.ConfigDict;
            bool haveDNN = (openCVConfigDict["HAVE_OPENCV_DNN"] != 0);
            String dnnText;
            if (haveDNN)
            {
                var dnnBackends = DnnInvoke.AvailableBackends;
                List<String> dnnBackendsText = new List<string>();
                foreach (var dnnBackend in dnnBackends)
                {
                    dnnBackendsText.Add(String.Format("{0} - {1}", dnnBackend.Backend, dnnBackend.Target));
                }

                dnnText = String.Format("DNN backends: {0}{1}", System.Environment.NewLine, String.Join(System.Environment.NewLine, dnnBackendsText.ToArray()));
            }
            else
            {
                dnnText = "DNN module not available.";
            }

            return dnnText;
        }

        private static String GetOpenCLInfo()
        {
            String openCLText = String.Format("Has OpenCL: {0}", CvInvoke.HaveOpenCL);

            String lineBreak = System.Environment.NewLine;
            if (CvInvoke.HaveOpenCL)
            {
                openCLText = String.Format("{0}{1}Use OpenCL: {2}{1}{3}{1}",
                    openCLText, lineBreak,
                    CvInvoke.UseOpenCL,
                    CvInvoke.OclGetPlatformsSummary());
            }

            return openCLText;
        }

        private static String GetBackendInfo(Emgu.CV.Backend[] backends)
        {
            List<String> backendsText = new List<string>();
            foreach (var backend in backends)
            {
                backendsText.Add(String.Format("{0} - {1}", backend.ID, backend.Name));
            }

            return String.Join(System.Environment.NewLine, backendsText.ToArray());
        }

        private static String GetVideoWriterFFMPEGInfo()
        {
            if (Emgu.Util.Platform.OperationSystem == Platform.OS.Windows)
            {
                Emgu.CV.Backend[] backends = CvInvoke.WriterBackends;
                int backend_idx = 0; //any backend;
                String backendName = String.Empty;
                foreach (Emgu.CV.Backend be in backends)
                {
                    if (be.Name.Equals("FFMPEG"))
                    {
                        backend_idx = be.ID;
                        backendName = be.Name;
                        break;
                    }
                }

                if (backend_idx > 0) //FFMPEG backend is available
                {
                    try
                    {
                        //Environment.SetEnvironmentVariable("OPENCV_FFMPEG_WRITER_OPTIONS", "hw_encoders_any;cuda");
                        using (VideoWriter writer = new VideoWriter(
                            "tmp.avi",
                            backend_idx,
                            VideoWriter.Fourcc('H', '2', '6', '3'), //VideoWriter.Fourcc('X', 'V', 'I', 'D'),
                            25,
                            new Size(704, 576),
                            new Tuple<VideoWriter.WriterProperty, int>[]
                            {
                                new Tuple<VideoWriter.WriterProperty, int>(VideoWriter.WriterProperty.IsColor, 1),
                                new Tuple<VideoWriter.WriterProperty, int>(VideoWriter.WriterProperty.HwAcceleration, (int) VideoAccelerationType.Any)
                            }))
                        {

                            VideoAccelerationType hwAcceleration =
                                (VideoAccelerationType)writer.Get(VideoWriter.WriterProperty.HwAcceleration);
                            return String.Format("{0}Trying to create H263 video writer with FFMPEG backend...{0}H263 VideoWriter successfully created with backend: {1} (hw acceleration: {2})", System.Environment.NewLine, backendName, hwAcceleration);
                        }
                    }
                    catch (Exception e)
                    {
                        return $"{Environment.NewLine}Failed to create H263 VideoWriter with FFMPEG backend: {e.Message}";
                    }
                }
                else
                {
                    return $"{Environment.NewLine}FFMPEG backend not found.";
                }
            }

            return String.Empty;
        }

        private static String GetVideoWriterIntelMfxInfo()
        {
            if (Emgu.Util.Platform.OperationSystem == Platform.OS.Windows)
            {
                Emgu.CV.Backend[] backends = CvInvoke.WriterBackends;
                int backend_idx = 0; //any backend;
                String backendName = String.Empty;
                foreach (Emgu.CV.Backend be in backends)
                {
                    if (be.Name.Equals("INTEL_MFX"))
                    {
                        backend_idx = be.ID;
                        backendName = be.Name;
                        break;
                    }
                }

                if (backend_idx > 0) //Intel MFX backend is available
                {
                    try
                    {
                        using (VideoWriter writer = new VideoWriter(
                            "tmp.avi",
                            backend_idx,
                            VideoWriter.Fourcc('H', '2', '6', '4'),
                            25,
                            new Size(640, 480),
                            new Tuple<VideoWriter.WriterProperty, int>[]
                            {
                                new Tuple<VideoWriter.WriterProperty, int>(VideoWriter.WriterProperty.IsColor, 1),
                                new Tuple<VideoWriter.WriterProperty, int>(VideoWriter.WriterProperty.HwAcceleration, (int) VideoAccelerationType.Any)
                            }))
                        {

                            VideoAccelerationType hwAcceleration =
                                (VideoAccelerationType)writer.Get(VideoWriter.WriterProperty.HwAcceleration);
                            return String.Format("{0}Trying to create H264 video writer with Intel MFX backend...{0}VideoWriter successfully created with backend: {1} (hw acceleration: {2})", System.Environment.NewLine, backendName, hwAcceleration);
                        }
                    }
                    catch (Exception e)
                    {
                        return $"{Environment.NewLine}Failed to create VideoWriter with Intel MFX backend: {e.Message}";
                    }
                }
                else
                {
                    return Environment.NewLine + "Intel MFX backend not found.";
                }
            }
            return String.Empty;
        }

        private static String GetVideoWriterMSMFInfo()
        {
            if (Emgu.Util.Platform.OperationSystem == Platform.OS.Windows)
            {
                Emgu.CV.Backend[] backends = CvInvoke.WriterBackends;
                int backend_idx = 0; //any backend;
                String backendName = String.Empty;
                foreach (Emgu.CV.Backend be in backends)
                {
                    if (be.Name.Equals("MSMF"))
                    {
                        backend_idx = be.ID;
                        backendName = be.Name;
                        break;
                    }
                }

                if (backend_idx > 0) //MSMF backend is available
                {
                    try
                    {

                        using (VideoWriter writer = new VideoWriter(
                            "tmp.mp4",
                            backend_idx,
                            VideoWriter.Fourcc('H', '2', '6', '4'),
                            30,
                            new Size(640, 480),
                            new Tuple<VideoWriter.WriterProperty, int>[]
                            {
                                new Tuple<VideoWriter.WriterProperty, int>(VideoWriter.WriterProperty.IsColor, 1),
                                new Tuple<VideoWriter.WriterProperty, int>(VideoWriter.WriterProperty.HwAcceleration, (int) VideoAccelerationType.Any)
                            }))
                        {

                            VideoAccelerationType hwAcceleration =
                                (VideoAccelerationType)writer.Get(VideoWriter.WriterProperty.HwAcceleration);
                            return String.Format("{0}Trying to create H264 video writer with MSMF backend...{0}H264 VideoWriter successfully created with backend: {1} (hw acceleration: {2})", System.Environment.NewLine, backendName, hwAcceleration);
                        }
                    }
                    catch (Exception e)
                    {
                        return $"{Environment.NewLine}Failed to create H264 VideoWriter with MSMF backend: {e.Message}";
                    }
                }
                else
                {
                    return $"{Environment.NewLine}MSMF backend not found.";
                }
            }
            return String.Empty;
        }

        private static String GetVideoWriterInfo()
        {
            if (Emgu.Util.Platform.OperationSystem == Platform.OS.Windows)
            {

                try
                {
                    
                    using (VideoWriter writer = new VideoWriter(
                        "tmp.avi",
                        0,
                        VideoWriter.Fourcc('H', '2', '6', '3'),
                        30,
                        new Size(704, 576),
                        new Tuple<VideoWriter.WriterProperty, int>[]
                        {
                                new Tuple<VideoWriter.WriterProperty, int>(VideoWriter.WriterProperty.IsColor, 1),
                                new Tuple<VideoWriter.WriterProperty, int>(VideoWriter.WriterProperty.HwAcceleration, (int) VideoAccelerationType.Any)
                        }))
                    {

                        VideoAccelerationType hwAcceleration =
                            (VideoAccelerationType)writer.Get(VideoWriter.WriterProperty.HwAcceleration);
                        return String.Format("{0}Trying to create H263 video writer with default backend...{0}H263 VideoWriter successfully created with default backend: {1} (hw acceleration: {2})", System.Environment.NewLine, writer.BackendName, hwAcceleration);
                    }
                }
                catch (Exception e)
                {
                    return $"{Environment.NewLine}Failed to create H263 VideoWriter with default backend: {e.Message}";
                }

            }
            return String.Empty;
        }

        private static String GetVideoCaptureInfo()
        {
            if (Emgu.Util.Platform.OperationSystem == Platform.OS.Windows)
            {

                String captureText = String.Empty;
                try
                {
                    using (VideoCapture cap = new VideoCapture(0, VideoCapture.API.Any,
                        new Tuple<CapProp, int>(CapProp.HwAcceleration, (int)VideoAccelerationType.Any)))
                    {
                        if (cap.IsOpened)
                        {

                            VideoAccelerationType hwAcceleration = (VideoAccelerationType)cap.Get(CapProp.HwAcceleration);
                            captureText +=
                                $"{System.Environment.NewLine}VideoCapture device successfully opened with backend: {cap.BackendName} (hw acceleration: {hwAcceleration})";
                        }
                        else
                        {
                            captureText +=
                                $"{System.Environment.NewLine}VideoCapture device failed to opened.";
                        }
                    }
                }
                catch (Emgu.CV.Util.CvException e)
                {
                    captureText += $"{System.Environment.NewLine}No capture device found: {e.ErrorMessage}";
                }
                return captureText;

            }
            return String.Empty;
        }

        private static String GetCaptureInfo()
        {
            String captureText =
                $"Capture Backends (VideoCapture from device):{System.Environment.NewLine}{GetBackendInfo(CvInvoke.Backends)}";

            /*
                //We don't want to create VideoCapture on Mac OS unless we have requested camera permission
                if (Emgu.Util.Platform.OperationSystem != Platform.OS.MacOS)
                {
                try {
                      using (VideoCapture cap = new VideoCapture(0, VideoCapture.API.Any,
                          new Tuple<CapProp, int>(CapProp.HwAcceleration, (int)VideoAccelerationType.Any)))
                      {
                          if (cap.IsOpened)
                          {
                              String backendName = cap.BackendName;
                              VideoAccelerationType hwAcceleration = (VideoAccelerationType)cap.Get(CapProp.HwAcceleration);
                              captureText +=
                                  String.Format(
                                      "{0}VideoCapture device successfully opened with default backend: {1} (hw acceleration: {2})",
                                      System.Environment.NewLine, backendName, hwAcceleration);
                          } else
                          {
                              captureText +=
                                  String.Format(
                                      "{0}VideoCapture device failed to opened with default backend: {1}",
                                      System.Environment.NewLine, cap.BackendName);
                          }
                      }
            } catch (Emgu.CV.Util.CvException e)
            {
                    //System.Console.WriteLine(">>>>>>>>>>>>>>>>>>>>>");
                captureText += String.Format("{0}No capture device found.", System.Environment.NewLine);
            }
                }*/

            captureText +=
                $"{System.Environment.NewLine}{System.Environment.NewLine}Stream Backends (VideoCapture from file/Stream): {System.Environment.NewLine}{GetBackendInfo(CvInvoke.StreamBackends)}";

            captureText +=
                $"{Environment.NewLine}{Environment.NewLine}VideoWriter backends: {Environment.NewLine}{GetBackendInfo(CvInvoke.WriterBackends)}{Environment.NewLine}";

            captureText += GetVideoWriterFFMPEGInfo();
            captureText += GetVideoWriterMSMFInfo();
            //captureText += GetVideoWriterIntelMfxInfo();
            captureText += GetVideoWriterInfo();
            captureText += Environment.NewLine + Environment.NewLine;
            captureText += GetVideoCaptureInfo();
            return captureText;
        }

        private static String GetRuntimeInfo()
        {
            StringBuilder runtimeStringBuilder = new StringBuilder();
            runtimeStringBuilder.Append(
                $"Runtime info: {System.Environment.NewLine}");
            runtimeStringBuilder.Append(
                $"OS Architecture: {RuntimeInformation.OSArchitecture}{System.Environment.NewLine}");
            runtimeStringBuilder.Append(
                $"Framework Description: {RuntimeInformation.FrameworkDescription}{System.Environment.NewLine}");
            runtimeStringBuilder.Append(
                $"Process Architecture: {RuntimeInformation.ProcessArchitecture}{System.Environment.NewLine}");
            runtimeStringBuilder.Append(
                $"OS Description: {RuntimeInformation.OSDescription}{System.Environment.NewLine}");
            return runtimeStringBuilder.ToString();
        }

        private static String GetCudaInfo()
        {
            StringBuilder cudaStringBuilder = new StringBuilder();

            cudaStringBuilder.Append(
                String.Format("Has Cuda: {0}{1}", CudaInvoke.HasCuda, System.Environment.NewLine));
            if (CudaInvoke.HasCuda)
            {
                cudaStringBuilder.Append(CudaInvoke.GetCudaDevicesSummary());
            }

            return cudaStringBuilder.ToString();
        }

        private static String GetParallelBackendInfo()
        {
            StringBuilder parallelBackendStringBuilder = new StringBuilder();

            String[] availableParallelBackends = CvInvoke.AvailableParallelBackends;
            parallelBackendStringBuilder.Append(String.Format("Available Parallel backends:{0}", Environment.NewLine));
            parallelBackendStringBuilder.Append(String.Join(Environment.NewLine, availableParallelBackends));

            return parallelBackendStringBuilder.ToString();
        }

        private static String GetDepthAIInfo()
        {
            var openCVConfigDict = CvInvoke.ConfigDict;
            bool haveDepthAI = (openCVConfigDict["HAVE_DEPTHAI"] != 0);
            String depthAIText;
            if (haveDepthAI)
            {
                depthAIText = "DepthAI module available.";
            }
            else
            {
                depthAIText = "DNN module not available.";
            }

            return depthAIText;
        }
    }
}
