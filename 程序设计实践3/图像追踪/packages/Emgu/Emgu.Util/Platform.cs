//----------------------------------------------------------------------------
//  Copyright (C) 2004-2023 by EMGU Corporation. All rights reserved.       
//----------------------------------------------------------------------------
using System;
using System.IO;
using System.Runtime.InteropServices;
using Emgu.Util.TypeEnum;

namespace Emgu.Util
{
    /// <summary>
    /// Provide information for the platform which is using. 
    /// </summary>
    public static class Platform
    {
        private static readonly OS _os;
        private static readonly Clr _runtime;

        static Platform()
        {
#if UNITY_IPHONE
            _os = OS.IOS;
            _runtime = Clr.Unity;
#elif UNITY_ANDROID
            _os = OS.Android;
            _runtime = Clr.Unity;
#else
            if (RuntimeInformation.FrameworkDescription.ToLower().StartsWith(".net native"))
                _runtime = Clr.DotNetNative;
            else if (RuntimeInformation.FrameworkDescription.ToLower().StartsWith(".net core"))
                _runtime = Clr.DotNet;
            else if (RuntimeInformation.FrameworkDescription.ToLower().StartsWith(".net ")) // "e.g. .NET 5.0.6
                _runtime = Clr.DotNet;

            if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
            {
                _os = OS.Windows;
            }
            else if (Emgu.Util.Toolbox.FindAssembly("Mono.Android.dll") != null)
            {
                //Xamarin Android
                _os = OS.Android;
                _runtime = Clr.Mono;
            }
            else if (Emgu.Util.Toolbox.FindAssembly("Microsoft.Android.dll") != null)
            {
                //MAUI Android
                _os = OS.Android;
                _runtime = Clr.DotNet;
            }
            else if (Emgu.Util.Toolbox.FindAssembly("Xamarin.iOS.dll") != null)
            {   
                //Xamarin iOS
                _os = OS.IOS;
                _runtime = Clr.Mono;
            }
            else if (Emgu.Util.Toolbox.FindAssembly("Microsoft.iOS.dll") != null)
            {
                //MAUI iOS
                _os = OS.IOS;
                _runtime = Clr.DotNet;
            }
            else if (RuntimeInformation.IsOSPlatform(OSPlatform.OSX))
            {
                _os = OS.MacOS;
            }
            else if (RuntimeInformation.IsOSPlatform(OSPlatform.Linux))
            {
                _os = OS.Linux;
            }
            else
            {
                _os = OS.Unknown;
                _runtime = Clr.Unknown;
            }
#endif
        }

        /// <summary>
        /// Get the type of the current operating system
        /// </summary>
        public static OS OperationSystem
        {
            get { return _os; }
        }

        /// <summary>
        /// Get the type of the current runtime environment
        /// </summary>
        public static Clr ClrType
        {
            get { return _runtime; }
        }

        /// <summary>
        /// Type of operating system
        /// </summary>
        public enum OS
        {
            /// <summary>
            /// Unknown
            /// </summary>
            Unknown,
            /// <summary>
            /// Windows
            /// </summary>
            Windows,
            /// <summary>
            /// Linux
            /// </summary>
            Linux,
            /// <summary>
            /// Mac OS
            /// </summary>
            MacOS,
            /// <summary>
            /// iOS devices. iPhone, iPad, iPod Touch
            /// </summary>
            IOS,
            /// <summary>
            /// Android devices
            /// </summary>
            Android
        }

        /// <summary>
        /// The runtime environment
        /// </summary>
        public enum Clr
        {
            /// <summary>
            /// Unknown
            /// </summary>
            Unknown,
            /// <summary>
            /// .Net runtime
            /// </summary>
            DotNet,
            /// <summary>
            /// Windows Store app runtime
            /// </summary>
            DotNetNative,
            /// <summary>
            /// Mono runtime
            /// </summary>
            Mono,
            /// <summary>
            /// Unity runtime
            /// </summary>
            Unity
        }
    }


}

