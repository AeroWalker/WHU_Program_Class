//----------------------------------------------------------------------------
//  Copyright (C) 2004-2023 by EMGU Corporation. All rights reserved.       
//----------------------------------------------------------------------------

using System;

namespace Emgu.CV
{

   /// <summary>
   /// An interface for the convex polygon
   /// </summary>
   public interface IConvexPolygonF
   {
      /// <summary>
      /// Get the vertices of this convex polygon
      /// </summary>
      /// <returns>The vertices of this convex polygon</returns>
      System.Drawing.PointF[] GetVertices();
   }
}