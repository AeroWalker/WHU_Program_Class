## About

This package is part of the 4.7.0 release of Emgu CV. 

For online documentation please visit
<https://www.emgu.com/wiki/files/4.7.0/document/index.html>

Release note can be found at
<https://www.emgu.com/wiki/index.php/Version_History#Emgu.CV-4.7.0>

## How to Use

```csharp
Bitmap bmp = ... //Some bitmap object
Mat mat = bmp.ToMat() //convert Bitmap to Mat
... // modify on your Mat
Bitmap otherBmp = mat.ToBitmap(); // convert Mat to Bitmap
```

## Supported platforms

* Windows
* Linux (require GDI+)
* Mac OS (require GDI+)

This package do not support mobile platforms. GDI+ is not available on iOS or Android
