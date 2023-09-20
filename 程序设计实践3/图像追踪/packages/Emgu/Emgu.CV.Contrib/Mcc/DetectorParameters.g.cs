//----------------------------------------------------------------------------
//  This file is automatically generated, do not modify.      
//----------------------------------------------------------------------------



using System;
using System.Runtime.InteropServices;
using Emgu.CV;
using Emgu.CV.Structure;
using Emgu.Util;

namespace Emgu.CV.Mcc
{
   public static partial class MccInvoke
   {

     [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)] 
     internal static extern int cveDetectorParametersGetAdaptiveThreshWinSizeMin(IntPtr obj);
     [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
     internal static extern void cveDetectorParametersSetAdaptiveThreshWinSizeMin(
        IntPtr obj,  
        int val);
     
     [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)] 
     internal static extern int cveDetectorParametersGetAdaptiveThreshWinSizeMax(IntPtr obj);
     [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
     internal static extern void cveDetectorParametersSetAdaptiveThreshWinSizeMax(
        IntPtr obj,  
        int val);
     
     [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)] 
     internal static extern int cveDetectorParametersGetAdaptiveThreshWinSizeStep(IntPtr obj);
     [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
     internal static extern void cveDetectorParametersSetAdaptiveThreshWinSizeStep(
        IntPtr obj,  
        int val);
     
     [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)] 
     internal static extern double cveDetectorParametersGetAdaptiveThreshConstant(IntPtr obj);
     [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
     internal static extern void cveDetectorParametersSetAdaptiveThreshConstant(
        IntPtr obj,  
        double val);
     
     [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)] 
     internal static extern double cveDetectorParametersGetMinContoursAreaRate(IntPtr obj);
     [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
     internal static extern void cveDetectorParametersSetMinContoursAreaRate(
        IntPtr obj,  
        double val);
     
     [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)] 
     internal static extern double cveDetectorParametersGetMinContoursArea(IntPtr obj);
     [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
     internal static extern void cveDetectorParametersSetMinContoursArea(
        IntPtr obj,  
        double val);
     
     [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)] 
     internal static extern double cveDetectorParametersGetConfidenceThreshold(IntPtr obj);
     [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
     internal static extern void cveDetectorParametersSetConfidenceThreshold(
        IntPtr obj,  
        double val);
     
     [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)] 
     internal static extern double cveDetectorParametersGetMinContourSolidity(IntPtr obj);
     [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
     internal static extern void cveDetectorParametersSetMinContourSolidity(
        IntPtr obj,  
        double val);
     
     [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)] 
     internal static extern double cveDetectorParametersGetFindCandidatesApproxPolyDPEpsMultiplier(IntPtr obj);
     [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
     internal static extern void cveDetectorParametersSetFindCandidatesApproxPolyDPEpsMultiplier(
        IntPtr obj,  
        double val);
     
     [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)] 
     internal static extern int cveDetectorParametersGetBorderWidth(IntPtr obj);
     [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
     internal static extern void cveDetectorParametersSetBorderWidth(
        IntPtr obj,  
        int val);
     
     [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)] 
     internal static extern float cveDetectorParametersGetB0factor(IntPtr obj);
     [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
     internal static extern void cveDetectorParametersSetB0factor(
        IntPtr obj,  
        float val);
     
     [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)] 
     internal static extern float cveDetectorParametersGetMaxError(IntPtr obj);
     [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
     internal static extern void cveDetectorParametersSetMaxError(
        IntPtr obj,  
        float val);
     
     [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)] 
     internal static extern int cveDetectorParametersGetMinContourPointsAllowed(IntPtr obj);
     [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
     internal static extern void cveDetectorParametersSetMinContourPointsAllowed(
        IntPtr obj,  
        int val);
     
     [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)] 
     internal static extern int cveDetectorParametersGetMinContourLengthAllowed(IntPtr obj);
     [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
     internal static extern void cveDetectorParametersSetMinContourLengthAllowed(
        IntPtr obj,  
        int val);
     
     [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)] 
     internal static extern int cveDetectorParametersGetMinInterContourDistance(IntPtr obj);
     [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
     internal static extern void cveDetectorParametersSetMinInterContourDistance(
        IntPtr obj,  
        int val);
     
     [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)] 
     internal static extern int cveDetectorParametersGetMinInterCheckerDistance(IntPtr obj);
     [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
     internal static extern void cveDetectorParametersSetMinInterCheckerDistance(
        IntPtr obj,  
        int val);
     
     [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)] 
     internal static extern int cveDetectorParametersGetMinImageSize(IntPtr obj);
     [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
     internal static extern void cveDetectorParametersSetMinImageSize(
        IntPtr obj,  
        int val);
     
     [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)] 
     internal static extern uint cveDetectorParametersGetMinGroupSize(IntPtr obj);
     [DllImport(CvInvoke.ExternLibrary, CallingConvention = CvInvoke.CvCallingConvention)]
     internal static extern void cveDetectorParametersSetMinGroupSize(
        IntPtr obj,  
        uint val);
     
   }

   public partial class DetectorParameters
   {

     /// <summary>
     /// AdaptiveThreshold minimum window size
     /// </summary>
     public int AdaptiveThreshWinSizeMin
     {
        get { return MccInvoke.cveDetectorParametersGetAdaptiveThreshWinSizeMin(_ptr); } 
        set { MccInvoke.cveDetectorParametersSetAdaptiveThreshWinSizeMin(_ptr, value); }
     }
     
     /// <summary>
     /// AdaptiveThreshold maximum window size
     /// </summary>
     public int AdaptiveThreshWinSizeMax
     {
        get { return MccInvoke.cveDetectorParametersGetAdaptiveThreshWinSizeMax(_ptr); } 
        set { MccInvoke.cveDetectorParametersSetAdaptiveThreshWinSizeMax(_ptr, value); }
     }
     
     /// <summary>
     /// AdaptiveThreshold window size step
     /// </summary>
     public int AdaptiveThreshWinSizeStep
     {
        get { return MccInvoke.cveDetectorParametersGetAdaptiveThreshWinSizeStep(_ptr); } 
        set { MccInvoke.cveDetectorParametersSetAdaptiveThreshWinSizeStep(_ptr, value); }
     }
     
     /// <summary>
     /// AdaptiveThreshold constant
     /// </summary>
     public double AdaptiveThreshConstant
     {
        get { return MccInvoke.cveDetectorParametersGetAdaptiveThreshConstant(_ptr); } 
        set { MccInvoke.cveDetectorParametersSetAdaptiveThreshConstant(_ptr, value); }
     }
     
     /// <summary>
     /// Minimum Contours Area Rate
     /// </summary>
     public double MinContoursAreaRate
     {
        get { return MccInvoke.cveDetectorParametersGetMinContoursAreaRate(_ptr); } 
        set { MccInvoke.cveDetectorParametersSetMinContoursAreaRate(_ptr, value); }
     }
     
     /// <summary>
     /// Minimum Contours Area
     /// </summary>
     public double MinContoursArea
     {
        get { return MccInvoke.cveDetectorParametersGetMinContoursArea(_ptr); } 
        set { MccInvoke.cveDetectorParametersSetMinContoursArea(_ptr, value); }
     }
     
     /// <summary>
     /// Confidence Threshold
     /// </summary>
     public double ConfidenceThreshold
     {
        get { return MccInvoke.cveDetectorParametersGetConfidenceThreshold(_ptr); } 
        set { MccInvoke.cveDetectorParametersSetConfidenceThreshold(_ptr, value); }
     }
     
     /// <summary>
     /// Minimum Contour Solidity
     /// </summary>
     public double MinContourSolidity
     {
        get { return MccInvoke.cveDetectorParametersGetMinContourSolidity(_ptr); } 
        set { MccInvoke.cveDetectorParametersSetMinContourSolidity(_ptr, value); }
     }
     
     /// <summary>
     /// Find Candidates Approx Poly DP Eps Multiplier
     /// </summary>
     public double FindCandidatesApproxPolyDPEpsMultiplier
     {
        get { return MccInvoke.cveDetectorParametersGetFindCandidatesApproxPolyDPEpsMultiplier(_ptr); } 
        set { MccInvoke.cveDetectorParametersSetFindCandidatesApproxPolyDPEpsMultiplier(_ptr, value); }
     }
     
     /// <summary>
     /// Border Width
     /// </summary>
     public int BorderWidth
     {
        get { return MccInvoke.cveDetectorParametersGetBorderWidth(_ptr); } 
        set { MccInvoke.cveDetectorParametersSetBorderWidth(_ptr, value); }
     }
     
     /// <summary>
     /// B0factor
     /// </summary>
     public float B0factor
     {
        get { return MccInvoke.cveDetectorParametersGetB0factor(_ptr); } 
        set { MccInvoke.cveDetectorParametersSetB0factor(_ptr, value); }
     }
     
     /// <summary>
     /// Max Error
     /// </summary>
     public float MaxError
     {
        get { return MccInvoke.cveDetectorParametersGetMaxError(_ptr); } 
        set { MccInvoke.cveDetectorParametersSetMaxError(_ptr, value); }
     }
     
     /// <summary>
     /// Minimum Contour Points Allowed
     /// </summary>
     public int MinContourPointsAllowed
     {
        get { return MccInvoke.cveDetectorParametersGetMinContourPointsAllowed(_ptr); } 
        set { MccInvoke.cveDetectorParametersSetMinContourPointsAllowed(_ptr, value); }
     }
     
     /// <summary>
     /// Minimum Contour Length Allowed
     /// </summary>
     public int MinContourLengthAllowed
     {
        get { return MccInvoke.cveDetectorParametersGetMinContourLengthAllowed(_ptr); } 
        set { MccInvoke.cveDetectorParametersSetMinContourLengthAllowed(_ptr, value); }
     }
     
     /// <summary>
     /// Minimum InterContour Distance
     /// </summary>
     public int MinInterContourDistance
     {
        get { return MccInvoke.cveDetectorParametersGetMinInterContourDistance(_ptr); } 
        set { MccInvoke.cveDetectorParametersSetMinInterContourDistance(_ptr, value); }
     }
     
     /// <summary>
     /// Minimum InterChecker Distance
     /// </summary>
     public int MinInterCheckerDistance
     {
        get { return MccInvoke.cveDetectorParametersGetMinInterCheckerDistance(_ptr); } 
        set { MccInvoke.cveDetectorParametersSetMinInterCheckerDistance(_ptr, value); }
     }
     
     /// <summary>
     /// Minimum Image Size
     /// </summary>
     public int MinImageSize
     {
        get { return MccInvoke.cveDetectorParametersGetMinImageSize(_ptr); } 
        set { MccInvoke.cveDetectorParametersSetMinImageSize(_ptr, value); }
     }
     
     /// <summary>
     /// Minimum Group Size
     /// </summary>
     public uint MinGroupSize
     {
        get { return MccInvoke.cveDetectorParametersGetMinGroupSize(_ptr); } 
        set { MccInvoke.cveDetectorParametersSetMinGroupSize(_ptr, value); }
     }
     
   }
}
