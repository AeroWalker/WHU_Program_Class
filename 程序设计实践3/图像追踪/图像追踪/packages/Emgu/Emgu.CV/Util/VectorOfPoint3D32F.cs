﻿//----------------------------------------------------------------------------
//
//  Copyright (C) 2004-2023 by EMGU Corporation. All rights reserved.
//
//  Vector of Point3D32F
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

namespace Emgu.CV.Util
{
   /// <summary>
   /// Wrapped class of the C++ standard vector of Point3D32F.
   /// </summary>
   [Serializable]
   [DebuggerTypeProxy(typeof(VectorOfPoint3D32F.DebuggerProxy))]
   public partial class VectorOfPoint3D32F : Emgu.CV.Util.UnmanagedVector, ISerializable
#if true
      , IInputOutputArray
#endif
   {
      private readonly bool _needDispose;
   
      static VectorOfPoint3D32F()
      {
         CvInvoke.Init();
         Debug.Assert(Emgu.Util.Toolbox.SizeOf<MCvPoint3D32f>() == SizeOfItemInBytes, "Size do not match");
      }

      /// <summary>
      /// Constructor used to deserialize runtime serialized object
      /// </summary>
      /// <param name="info">The serialization info</param>
      /// <param name="context">The streaming context</param>
      public VectorOfPoint3D32F(SerializationInfo info, StreamingContext context)
         : this()
      {
         Push((MCvPoint3D32f[])info.GetValue("Point3D32FArray", typeof(MCvPoint3D32f[])));
      }
	  
      /// <summary>
      /// A function used for runtime serialization of the object
      /// </summary>
      /// <param name="info">Serialization info</param>
      /// <param name="context">Streaming context</param>
      public void GetObjectData(SerializationInfo info, StreamingContext context)
      {
         info.AddValue("Point3D32FArray", ToArray());
      }

      /// <summary>
      /// Create an empty standard vector of Point3D32F
      /// </summary>
      public VectorOfPoint3D32F()
         : this(VectorOfPoint3D32FCreate(), true)
      {
      }
	  
      internal VectorOfPoint3D32F(IntPtr ptr, bool needDispose)
      {
         _ptr = ptr;
         _needDispose = needDispose;
      }

      /// <summary>
      /// Create an standard vector of Point3D32F of the specific size
      /// </summary>
      /// <param name="size">The size of the vector</param>
      public VectorOfPoint3D32F(int size)
         : this( VectorOfPoint3D32FCreateSize(size), true)
      {
      }
	  
      /// <summary>
      /// Create an standard vector of Point3D32F with the initial values
      /// </summary>
      /// <param name="values">The initial values</param>
      public VectorOfPoint3D32F(MCvPoint3D32f[] values)
         :this()
      {
         Push(values);
      }
	  
      /// <summary>
      /// Push an array of value into the standard vector
      /// </summary>
      /// <param name="value">The value to be pushed to the vector</param>
      public void Push(MCvPoint3D32f[] value)
      {
         if (value.Length > 0)
         {
            GCHandle handle = GCHandle.Alloc(value, GCHandleType.Pinned);
            VectorOfPoint3D32FPushMulti(_ptr, handle.AddrOfPinnedObject(), value.Length);
            handle.Free();
         }
      }
      
      /// <summary>
      /// Push multiple values from the other vector into this vector
      /// </summary>
      /// <param name="other">The other vector, from which the values will be pushed to the current vector</param>
      public void Push(VectorOfPoint3D32F other)
      {
         VectorOfPoint3D32FPushVector(_ptr, other);
      }
	  
      /// <summary>
      /// Convert the standard vector to an array of Point3D32F
      /// </summary>
      /// <returns>An array of Point3D32F</returns>
      public MCvPoint3D32f[] ToArray()
      {
         MCvPoint3D32f[] res = new MCvPoint3D32f[Size];
         if (res.Length > 0)
         {
            GCHandle handle = GCHandle.Alloc(res, GCHandleType.Pinned);
            VectorOfPoint3D32FCopyData(_ptr, handle.AddrOfPinnedObject());
            handle.Free();
         }
         return res;
      }

      /// <summary>
      /// Get the size of the vector
      /// </summary>
      public override int Size
      {
         get
         {
            return VectorOfPoint3D32FGetSize(_ptr);
         }
      }

      /// <summary>
      /// Clear the vector
      /// </summary>
      public void Clear()
      {
         VectorOfPoint3D32FClear(_ptr);
      }

      /// <summary>
      /// The pointer to the first element on the vector. In case of an empty vector, IntPtr.Zero will be returned.
      /// </summary>
      public override IntPtr StartAddress
      {
         get
         {
            return VectorOfPoint3D32FGetStartAddress(_ptr);
         }
      }

	  /// <summary>
      /// The size of memory in bytes, that is needed to hold all the items in this vector
      /// </summary>
      public override long Length
      {
         get
         {
            return VectorOfPoint3D32FGetMemorySize(_ptr);
         }
      }

      /// <summary>
      /// Get the item in the specific index
      /// </summary>
      /// <param name="index">The index</param>
      /// <returns>The item in the specific index</returns>
      public MCvPoint3D32f this[int index]
      {
         get
         {
            MCvPoint3D32f result = new MCvPoint3D32f();
            VectorOfPoint3D32FGetItem(_ptr, index, ref result);
            return result;
         }
      }

      /// <summary>
      /// Release the standard vector
      /// </summary>
      protected override void DisposeObject()
      {
         if (_needDispose && _ptr != IntPtr.Zero)
            VectorOfPoint3D32FRelease(ref _ptr);
      }

#if true
      /// <summary>
      /// Get the data as InputArray
      /// </summary>
      /// <returns>The input array </returns>
      public InputArray GetInputArray()
      {
         return new InputArray( cveInputArrayFromVectorOfPoint3D32F(_ptr), this );
      }
	  
      /// <summary>
      /// Get the data as OutputArray
      /// </summary>
      /// <returns>The output array </returns>
      public OutputArray GetOutputArray()
      {
         return new OutputArray( cveOutputArrayFromVectorOfPoint3D32F(_ptr), this );
      }

      /// <summary>
      /// Get the data as InputOutputArray
      /// </summary>
      /// <returns>The input output array </returns>
      public InputOutputArray GetInputOutputArray()
      {
         return new InputOutputArray( cveInputOutputArrayFromVectorOfPoint3D32F(_ptr), this );
      }
#endif
      
      /// <summary>
      /// The size of the item in this Vector, counted as size in bytes.
      /// </summary>
      public static int SizeOfItemInBytes
      {
         get { return VectorOfPoint3D32FSizeOfItemInBytes(); }
      }
	  
      internal class DebuggerProxy
      {
         private VectorOfPoint3D32F _v;

         public DebuggerProxy(VectorOfPoint3D32F v)
         {
            _v = v;
         }

         public MCvPoint3D32f[] Values
         {
            get { return _v.ToArray(); }
         }
      }

      [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern IntPtr VectorOfPoint3D32FCreate();

      [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern IntPtr VectorOfPoint3D32FCreateSize(int size);

      [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern void VectorOfPoint3D32FRelease(ref IntPtr v);

      [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern int VectorOfPoint3D32FGetSize(IntPtr v);

      [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern void VectorOfPoint3D32FCopyData(IntPtr v, IntPtr data);

      [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern IntPtr VectorOfPoint3D32FGetStartAddress(IntPtr v);
	  
	  [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern long VectorOfPoint3D32FGetMemorySize(IntPtr v);

      [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern void VectorOfPoint3D32FPushMulti(IntPtr v, IntPtr values, int count);

      [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern void VectorOfPoint3D32FPushVector(IntPtr ptr, IntPtr otherPtr);
      
      [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern void VectorOfPoint3D32FClear(IntPtr v);

      [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern void VectorOfPoint3D32FGetItem(IntPtr vec, int index, ref MCvPoint3D32f element);

      [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern int VectorOfPoint3D32FSizeOfItemInBytes();

#if true      
      [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern IntPtr cveInputArrayFromVectorOfPoint3D32F(IntPtr vec);

      [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern IntPtr cveOutputArrayFromVectorOfPoint3D32F(IntPtr vec);

      [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern IntPtr cveInputOutputArrayFromVectorOfPoint3D32F(IntPtr vec);
#endif
   }
}


