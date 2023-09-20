﻿//----------------------------------------------------------------------------
//
//  Copyright (C) 2004-2023 by EMGU Corporation. All rights reserved.
//
//  Vector of Pose3D
//
//  This file is automatically generated, do not modify.
//----------------------------------------------------------------------------



using System;
using System.Drawing;
using System.Diagnostics;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Runtime.Serialization;
using Emgu.CV.Structure;

namespace Emgu.CV.PpfMatch3d
{
   /// <summary>
   /// Wrapped class of the C++ standard vector of Pose3D.
   /// </summary>
   [Serializable]
   [DebuggerTypeProxy(typeof(VectorOfPose3D.DebuggerProxy))]
   public partial class VectorOfPose3D : Emgu.CV.Util.UnmanagedVector
#if false
      , IInputOutputArray
#endif
   {
      private readonly bool _needDispose;
   
      static VectorOfPose3D()
      {
         CvInvoke.Init();
      }

      /// <summary>
      /// Create an empty standard vector of Pose3D
      /// </summary>
      public VectorOfPose3D()
         : this(VectorOfPose3DCreate(), true)
      {
      }

      internal VectorOfPose3D(IntPtr ptr, bool needDispose)
      {
         _ptr = ptr;
         _needDispose = needDispose;
      }

      /// <summary>
      /// Create an standard vector of Pose3D of the specific size
      /// </summary>
      /// <param name="size">The size of the vector</param>
      public VectorOfPose3D(int size)
         : this( VectorOfPose3DCreateSize(size), true)
      {
      }

      /// <summary>
      /// Create an standard vector of Pose3D with the initial values
      /// </summary>
      /// <param name="values">The initial values</param>
      public VectorOfPose3D(params Pose3D[] values)
        : this()
      {
        Push(values);
      }

      /// <summary>
      /// Get the size of the vector
      /// </summary>
      public override int Size
      {
         get
         {
            return VectorOfPose3DGetSize(_ptr);
         }
      }
	  
	  /// <summary>
      /// The pointer to the first element on the vector. In case of an empty vector, IntPtr.Zero will be returned.
      /// </summary>
      public override IntPtr StartAddress
      {
         get
         {
            return VectorOfPose3DGetStartAddress(_ptr);
         }
      }
	  
	  
	  /// <summary>
      /// The size of memory in bytes, that is needed to hold all the items in this vector
      /// </summary>
      public override long Length
      {
         get
         {
            return VectorOfPose3DGetMemorySize(_ptr);
         }
      }
	  

      /// <summary>
      /// Clear the vector
      /// </summary>
      public void Clear()
      {
         VectorOfPose3DClear(_ptr);
      }

      /// <summary>
      /// Push a value into the standard vector
      /// </summary>
      /// <param name="value">The value to be pushed to the vector</param>
      public void Push(Pose3D value)
      {
         VectorOfPose3DPush(_ptr, value.Ptr);
      }

      /// <summary>
      /// Push multiple values into the standard vector
      /// </summary>
      /// <param name="values">The values to be pushed to the vector</param>
      public void Push(Pose3D[] values)
      {
         foreach (Pose3D value in values)
            Push(value);
      }

      /// <summary>
      /// Push multiple values from the other vector into this vector
      /// </summary>
      /// <param name="other">The other vector, from which the values will be pushed to the current vector</param>
      public void Push(VectorOfPose3D other)
      {
         VectorOfPose3DPushVector(_ptr, other);
      }
      
      /// <summary>
      /// Get the item in the specific index
      /// </summary>
      /// <param name="index">The index</param>
      /// <returns>The item in the specific index</returns>
      public Pose3D this[int index]
      {
         get
         {
            IntPtr itemPtr = IntPtr.Zero;
            VectorOfPose3DGetItemPtr(_ptr, index, ref itemPtr);
            return new Pose3D(itemPtr, false);
         }
      }

      /// <summary>
      /// Release the standard vector
      /// </summary>
      protected override void DisposeObject()
      {
         if (_needDispose && _ptr != IntPtr.Zero)
            VectorOfPose3DRelease(ref _ptr);
      }

#if false
      /// <summary>
      /// Get the pointer to cv::_InputArray
      /// </summary>
      /// <returns>The input array</returns>
      public InputArray GetInputArray()
      {
        return new InputArray( cveInputArrayFromVectorOfPose3D(_ptr), this );
      }

      /// <summary>
      /// Get the pointer to cv::_OutputArray
      /// </summary>
      /// <returns>The output array</returns>
      public OutputArray GetOutputArray()
      {
         return new OutputArray( cveOutputArrayFromVectorOfPose3D(_ptr), this );
      }

      /// <summary>
      /// Get the pointer to cv::_InputOutputArray
      /// </summary>
      /// <returns>The input output array</returns>
      public InputOutputArray GetInputOutputArray()
      {
         return new InputOutputArray( cveInputOutputArrayFromVectorOfPose3D(_ptr), this );
      }
#endif
      
      /// <summary>
      /// The size of the item in this Vector, counted as size in bytes.
      /// </summary>
      public static int SizeOfItemInBytes
      {
         get { return VectorOfPose3DSizeOfItemInBytes(); }
      }

#if false
      /// <summary>
      /// Create the standard vector of Pose3D 
      /// </summary>
      /// <param name="values">The values to be pushed to the vector</param>
      public VectorOfPose3D(Rectangle[][] values)
         : this()
      {
         using (Pose3D v = new Pose3D())
         {
            for (int i = 0; i < values.Length; i++)
            {
               v.Push(values[i]);
               Push(v);
               v.Clear();
            }
         }
      }

      /// <summary>
      /// Convert the standard vector to arrays of arrays of Rectangle
      /// </summary>
      /// <returns>Arrays of arrays of the Rectangle</returns>
      public Rectangle[][] ToArrayOfArray()
      {
         int size = Size;
         Rectangle[][] res = new Rectangle[size][];
         for (int i = 0; i < size; i++)
         {
            using (Pose3D v = this[i])
            {
               res[i] = v.ToArray();
            }
         }
         return res;
      }
#endif

      internal class DebuggerProxy
      {
         private VectorOfPose3D _v;

         public DebuggerProxy(VectorOfPose3D v)
         {
            _v = v;
         }

#if false
         public Rectangle[][] Values
         {
            get { return _v.ToArrayOfArray(); }
         }
#else
         public Pose3D[] Values
         {
            get
            {
               Pose3D[] result = new Pose3D[_v.Size];
               for (int i = 0; i < result.Length; i++)
               {
                  result[i] = _v[i];
               }
               return result;
            }
         }
#endif
      }


      [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern IntPtr VectorOfPose3DCreate();

      [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern IntPtr VectorOfPose3DCreateSize(int size);

      [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern void VectorOfPose3DRelease(ref IntPtr v);

      [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern int VectorOfPose3DGetSize(IntPtr v);

      [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern IntPtr VectorOfPose3DGetStartAddress(IntPtr v);
	  
	  [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern long VectorOfPose3DGetMemorySize(IntPtr v);
	  
      [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern void VectorOfPose3DPush(IntPtr v, IntPtr value);

      [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern void VectorOfPose3DPushVector(IntPtr ptr, IntPtr otherPtr);
      
      [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern void VectorOfPose3DClear(IntPtr v);

      [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern void VectorOfPose3DGetItemPtr(IntPtr vec, int index, ref IntPtr element);

      [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern int VectorOfPose3DSizeOfItemInBytes();

#if false
      [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern IntPtr cveInputArrayFromVectorOfPose3D(IntPtr vec);

      [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern IntPtr cveOutputArrayFromVectorOfPose3D(IntPtr vec);

      [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern IntPtr cveInputOutputArrayFromVectorOfPose3D(IntPtr vec);
#endif
   }
}


