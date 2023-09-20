﻿//----------------------------------------------------------------------------
//
//  Copyright (C) 2004-2023 by EMGU Corporation. All rights reserved.
//
//  Vector of VectorOfDMatch
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
   /// Wrapped class of the C++ standard vector of VectorOfDMatch.
   /// </summary>
   [Serializable]
   [DebuggerTypeProxy(typeof(VectorOfVectorOfDMatch.DebuggerProxy))]
   public partial class VectorOfVectorOfDMatch : Emgu.CV.Util.UnmanagedVector
#if true
      , IInputOutputArray
#endif
   {
      private readonly bool _needDispose;
   
      static VectorOfVectorOfDMatch()
      {
         CvInvoke.Init();
      }

      /// <summary>
      /// Create an empty standard vector of VectorOfDMatch
      /// </summary>
      public VectorOfVectorOfDMatch()
         : this(VectorOfVectorOfDMatchCreate(), true)
      {
      }

      internal VectorOfVectorOfDMatch(IntPtr ptr, bool needDispose)
      {
         _ptr = ptr;
         _needDispose = needDispose;
      }

      /// <summary>
      /// Create an standard vector of VectorOfDMatch of the specific size
      /// </summary>
      /// <param name="size">The size of the vector</param>
      public VectorOfVectorOfDMatch(int size)
         : this( VectorOfVectorOfDMatchCreateSize(size), true)
      {
      }

      /// <summary>
      /// Create an standard vector of VectorOfDMatch with the initial values
      /// </summary>
      /// <param name="values">The initial values</param>
      public VectorOfVectorOfDMatch(params VectorOfDMatch[] values)
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
            return VectorOfVectorOfDMatchGetSize(_ptr);
         }
      }
	  
	  /// <summary>
      /// The pointer to the first element on the vector. In case of an empty vector, IntPtr.Zero will be returned.
      /// </summary>
      public override IntPtr StartAddress
      {
         get
         {
            return VectorOfVectorOfDMatchGetStartAddress(_ptr);
         }
      }
	  
	  
	  /// <summary>
      /// The size of memory in bytes, that is needed to hold all the items in this vector
      /// </summary>
      public override long Length
      {
         get
         {
            return VectorOfVectorOfDMatchGetMemorySize(_ptr);
         }
      }
	  

      /// <summary>
      /// Clear the vector
      /// </summary>
      public void Clear()
      {
         VectorOfVectorOfDMatchClear(_ptr);
      }

      /// <summary>
      /// Push a value into the standard vector
      /// </summary>
      /// <param name="value">The value to be pushed to the vector</param>
      public void Push(VectorOfDMatch value)
      {
         VectorOfVectorOfDMatchPush(_ptr, value.Ptr);
      }

      /// <summary>
      /// Push multiple values into the standard vector
      /// </summary>
      /// <param name="values">The values to be pushed to the vector</param>
      public void Push(VectorOfDMatch[] values)
      {
         foreach (VectorOfDMatch value in values)
            Push(value);
      }

      /// <summary>
      /// Push multiple values from the other vector into this vector
      /// </summary>
      /// <param name="other">The other vector, from which the values will be pushed to the current vector</param>
      public void Push(VectorOfVectorOfDMatch other)
      {
         VectorOfVectorOfDMatchPushVector(_ptr, other);
      }
      
      /// <summary>
      /// Get the item in the specific index
      /// </summary>
      /// <param name="index">The index</param>
      /// <returns>The item in the specific index</returns>
      public VectorOfDMatch this[int index]
      {
         get
         {
            IntPtr itemPtr = IntPtr.Zero;
            VectorOfVectorOfDMatchGetItemPtr(_ptr, index, ref itemPtr);
            return new VectorOfDMatch(itemPtr, false);
         }
      }

      /// <summary>
      /// Release the standard vector
      /// </summary>
      protected override void DisposeObject()
      {
         if (_needDispose && _ptr != IntPtr.Zero)
            VectorOfVectorOfDMatchRelease(ref _ptr);
      }

#if true
      /// <summary>
      /// Get the pointer to cv::_InputArray
      /// </summary>
      /// <returns>The input array</returns>
      public InputArray GetInputArray()
      {
        return new InputArray( cveInputArrayFromVectorOfVectorOfDMatch(_ptr), this );
      }

      /// <summary>
      /// Get the pointer to cv::_OutputArray
      /// </summary>
      /// <returns>The output array</returns>
      public OutputArray GetOutputArray()
      {
         return new OutputArray( cveOutputArrayFromVectorOfVectorOfDMatch(_ptr), this );
      }

      /// <summary>
      /// Get the pointer to cv::_InputOutputArray
      /// </summary>
      /// <returns>The input output array</returns>
      public InputOutputArray GetInputOutputArray()
      {
         return new InputOutputArray( cveInputOutputArrayFromVectorOfVectorOfDMatch(_ptr), this );
      }
#endif
      
      /// <summary>
      /// The size of the item in this Vector, counted as size in bytes.
      /// </summary>
      public static int SizeOfItemInBytes
      {
         get { return VectorOfVectorOfDMatchSizeOfItemInBytes(); }
      }

#if true
      /// <summary>
      /// Create the standard vector of VectorOfDMatch 
      /// </summary>
      /// <param name="values">The values to be pushed to the vector</param>
      public VectorOfVectorOfDMatch(MDMatch[][] values)
         : this()
      {
         using (VectorOfDMatch v = new VectorOfDMatch())
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
      /// Convert the standard vector to arrays of arrays of MDMatch
      /// </summary>
      /// <returns>Arrays of arrays of the MDMatch</returns>
      public MDMatch[][] ToArrayOfArray()
      {
         int size = Size;
         MDMatch[][] res = new MDMatch[size][];
         for (int i = 0; i < size; i++)
         {
            using (VectorOfDMatch v = this[i])
            {
               res[i] = v.ToArray();
            }
         }
         return res;
      }
#endif

      internal class DebuggerProxy
      {
         private VectorOfVectorOfDMatch _v;

         public DebuggerProxy(VectorOfVectorOfDMatch v)
         {
            _v = v;
         }

#if true
         public MDMatch[][] Values
         {
            get { return _v.ToArrayOfArray(); }
         }
#else
         public VectorOfDMatch[] Values
         {
            get
            {
               VectorOfDMatch[] result = new VectorOfDMatch[_v.Size];
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
      internal static extern IntPtr VectorOfVectorOfDMatchCreate();

      [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern IntPtr VectorOfVectorOfDMatchCreateSize(int size);

      [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern void VectorOfVectorOfDMatchRelease(ref IntPtr v);

      [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern int VectorOfVectorOfDMatchGetSize(IntPtr v);

      [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern IntPtr VectorOfVectorOfDMatchGetStartAddress(IntPtr v);
	  
	  [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern long VectorOfVectorOfDMatchGetMemorySize(IntPtr v);
	  
      [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern void VectorOfVectorOfDMatchPush(IntPtr v, IntPtr value);

      [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern void VectorOfVectorOfDMatchPushVector(IntPtr ptr, IntPtr otherPtr);
      
      [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern void VectorOfVectorOfDMatchClear(IntPtr v);

      [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern void VectorOfVectorOfDMatchGetItemPtr(IntPtr vec, int index, ref IntPtr element);

      [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern int VectorOfVectorOfDMatchSizeOfItemInBytes();

#if true
      [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern IntPtr cveInputArrayFromVectorOfVectorOfDMatch(IntPtr vec);

      [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern IntPtr cveOutputArrayFromVectorOfVectorOfDMatch(IntPtr vec);

      [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
      internal static extern IntPtr cveInputOutputArrayFromVectorOfVectorOfDMatch(IntPtr vec);
#endif
   }
}


