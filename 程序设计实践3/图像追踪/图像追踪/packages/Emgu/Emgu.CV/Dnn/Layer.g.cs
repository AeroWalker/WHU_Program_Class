//----------------------------------------------------------------------------
//  This file is automatically generated, do not modify.      
//----------------------------------------------------------------------------



using System;
using System.Runtime.InteropServices;
using Emgu.CV;
using Emgu.CV.Structure;
using Emgu.Util;

namespace Emgu.CV.Dnn
{
   public static partial class DnnInvoke
   {

     [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)] 
     internal static extern void cveLayerGetName(IntPtr obj, IntPtr str);
     
     [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)] 
     internal static extern void cveLayerGetType(IntPtr obj, IntPtr str);
     
     [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)] 
     internal static extern Target cveLayerGetPreferableTarget(IntPtr obj);
     
   }

   public partial class Layer
   {

     /// <summary>
     /// The name of the layer
     /// </summary>
     public String Name
     {
        get 
        { 
           using (CvString s = new CvString())
           {  
              DnnInvoke.cveLayerGetName(_ptr, s); 
              return s.ToString();
           }
        }
     }
     
     /// <summary>
     /// The layer type
     /// </summary>
     public String Type
     {
        get 
        { 
           using (CvString s = new CvString())
           {  
              DnnInvoke.cveLayerGetType(_ptr, s); 
              return s.ToString();
           }
        }
     }
     
     /// <summary>
     /// The preferable target
     /// </summary>
     public Target PreferableTarget
     {
        get { return DnnInvoke.cveLayerGetPreferableTarget(_ptr); } 
     }
     
   }
}
