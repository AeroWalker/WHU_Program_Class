using OpenCvSharp;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System;
using OpenCvSharp;
using System.IO;
using OpenCvSharp.Extensions;
using System.IO.Pipes;
using System.Windows.Forms.VisualStyles;
using static System.Net.Mime.MediaTypeNames;
using System.Security.Cryptography;

namespace WindowsFormsApp7
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        
        List<PictureBox> piclist = new List<PictureBox>();
        List<string> filelist = new List<string>();

        public string ExtractTextBetweenKeywords(string text, string keyword1, string keyword2)
        {
            int startIndex = text.IndexOf(keyword1) + keyword1.Length;
            int endIndex = text.IndexOf(keyword2);

            if (startIndex >= 0 && endIndex >= 0 && endIndex > startIndex)
            {
                return text.Substring(startIndex, endIndex - startIndex);
            }

            return string.Empty;
        }

        static string ReadTextFromSpecificValueToEnd(string text, string specificValue)
        {
            int startIndex = text.IndexOf(specificValue);

            if (startIndex >= 0)
            {
                startIndex += specificValue.Length;
                return text.Substring(startIndex);
            }

            return string.Empty;
        }

        public Mat ReadMatrixFromTextFile_HOMOMATRIX(string filePath)
        {
            // 读取文件内容
            //string[] lines = System.IO.File.ReadAllLines(filePath);

            string initext =File.ReadAllText(filePath);

            string HOMOMATRIX = ExtractTextBetweenKeywords(initext, "[HOMOMATRIX]", "[WHOMOMATRIX]").Trim();

            string[] lines = HOMOMATRIX.Split('\n');

            // 构建矩阵
            Mat matrix = new Mat(3, 3, MatType.CV_64F);


            for (int i = 0; i < lines.Length; i++)
            {
                string[] values = lines[i].Split('=');
                int col = int.Parse(values[0].Trim().Substring(2)) - 1;
                double value = double.Parse(values[1].Trim());
                matrix.Set<double>(i / 3, col, value);
            }

            return matrix;
        }

        public Mat ReadMatrixFromTextFile_WHOMOMATRIX(string filePath)
        {
            // 读取文件内容
            //string[] lines = System.IO.File.ReadAllLines(filePath);

            string initext = File.ReadAllText(filePath);

            string HOMOMATRIX = ReadTextFromSpecificValueToEnd(initext, "[WHOMOMATRIX]").Trim();

            string[] lines = HOMOMATRIX.Split('\n');

            // 构建矩阵
            Mat matrix = new Mat(3, 3, MatType.CV_64F);


            for (int i = 0; i < lines.Length; i++)
            {
                string[] values = lines[i].Split('=');
                int col = int.Parse(values[0].Trim().Substring(2)) - 1;
                double value = double.Parse(values[1].Trim());
                matrix.Set<double>(i / 3, col, value);
            }

            return matrix;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            
            piclist.Add(pictureBox1);
            piclist.Add(pictureBox2);
            piclist.Add(pictureBox3);

            piclist.Add(pictureBox4);
            piclist.Add(pictureBox5);
            piclist.Add(pictureBox6);

            piclist.Add(pictureBox7);
            piclist.Add(pictureBox8);
            piclist.Add(pictureBox9);

        }


        int PhotoStart = 1; //从第几张图开始读取
        int PhotoEnd = 10; //从读取到第几张图+1

        List<Mat> homographyMatrix = new List<Mat>();
        List<Mat> whomoMatrix = new List<Mat>();
        private void button1_Click(object sender, EventArgs e)
        {
            string filepath1 = "./steelimg/20070728_170425_0";
            string filepath2 = ".bmp";
            //MessageBox.Show(Convert.ToString( piclist.Count));

            string filepath3 = "./calibrate_para_hot/CalibResults333-image";
            string filepath4 = ".ini";

            for (int i = PhotoStart; i < PhotoEnd; i++)
            {
                piclist[i - PhotoStart].Image = System.Drawing.Image.FromFile(filepath1 +  Convert.ToString (i) + filepath2);
                filelist.Add(filepath1 + Convert.ToString(i) + filepath2);

                homographyMatrix.Add(ReadMatrixFromTextFile_WHOMOMATRIX(filepath3 + Convert.ToString(i) + filepath4));
                whomoMatrix.Add(ReadMatrixFromTextFile_WHOMOMATRIX(filepath3 + Convert.ToString(i) + filepath4));

            }
        }
        void ShowImageInPictureBox(Mat image)
        {
            // 将OpenCV的Mat转换为Bitmap
            Bitmap bitmap = BitmapConverter.ToBitmap(image);

            // 创建PictureBox控件并显示图像
            pictureBox1.Image = bitmap;

            // 创建一个新的窗体，并将PictureBox控件添加到窗体上

            // 启动应用程序主消息循环
        }

        private void button2_Click(object sender, EventArgs e)
        {
            int totalLong = 0;
            int totalweight = 0;
            double totalAera = 0;

            double RealtotalLong = 0;
            double Realtotalweight = 0;
            double RealtotalAera = 0;
            for (int indexs = 0; indexs < 9; indexs++)
            {
                Mat cameraMatrix = new Mat();
                Mat distortionCoefficients = new Mat();
                string calibrationFile = "path_to_calibration_file.xml";




                Mat image = Cv2.ImRead(filelist[indexs], ImreadModes.Grayscale);

                Mat correctedImage = new Mat();
                Cv2.WarpPerspective(image, correctedImage, homographyMatrix[indexs], new OpenCvSharp.Size(image.Width, image.Height), InterpolationFlags.Linear, OpenCvSharp.BorderTypes.Constant, new Scalar(255, 255, 255));
                Cv2.WarpPerspective(correctedImage, correctedImage, whomoMatrix[indexs], new OpenCvSharp.Size(correctedImage.Width, correctedImage.Height), InterpolationFlags.Linear, OpenCvSharp.BorderTypes.Constant, new Scalar(255, 255, 255));

                Mat binaryImage = new Mat();
                Cv2.Threshold(image, binaryImage, 170, 255, ThresholdTypes.Binary);

                //// 边缘检测
                Mat edges = new Mat();
                Cv2.Canny(binaryImage, edges, 110, 150);

                //// 寻找轮廓

                OpenCvSharp.Point[][] contours;
                HierarchyIndex[] hierarchy;
                Cv2.FindContours(edges, out contours, out hierarchy, RetrievalModes.External, ContourApproximationModes.ApproxSimple);

                //// 输出轮廓
                Console.WriteLine("Number of contours: " + contours.Length);
                for (int i = 0; i < contours.Length; i++)
                {
                    Console.WriteLine("Contour " + i + ": " + contours[i].Length + " points");
                    // 输出每个点的坐标
                    for (int j = 0; j < contours[i].Length; j++)
                    {

                        Console.WriteLine("Point " + j + ": (" + contours[i][j].X + ", " + contours[i][j].Y + ")");
                    }
                    Console.WriteLine();
                }
               
                    // 设置标记点的颜色和大小

                    // 遍历每个轮廓
                    double maxArea = 0;
                    int maxWidth = 0;
                    int maxHeight = 0;

                    Mat drawing = Mat.Zeros(image.Size(), MatType.CV_8UC3);
                    foreach (var contour in contours)
                    {
                     
                        double area = Cv2.ContourArea(contour);
                        Rect boundingRect = Cv2.BoundingRect(contour);
                        int width = boundingRect.Width;
                        int height = boundingRect.Height;

                        if (area > maxArea)
                        {
                            maxArea = area;
                            maxWidth = width;
                            maxHeight = height;
                        }
                        // 遍历每个轮廓的点
                        //foreach (var point in contour)
                        //{
                        //    // 在图像上绘制点
                        //    //g.DrawEllipse(pen, point.X, point.Y, 2, 2);
                        //}

                        

                        // 遍历每个轮廓


 
                    }
                for (int i = 0; i < contours.Length; i++)
                {
                    // 在绘制容器上绘制轮廓线
                    Cv2.DrawContours(drawing, contours, i, Scalar.Red, 2);
                }
                piclist[indexs].Image = BitmapConverter.ToBitmap(drawing);
                totalLong = totalLong + maxWidth;
                totalweight = totalweight > maxWidth ? totalweight : maxWidth;
                totalAera = totalAera + maxArea;
                RealtotalLong = RealtotalLong + Long_ReSize(maxWidth, homographyMatrix[indexs]);
                Realtotalweight = Realtotalweight > Long_ReSize(maxWidth, homographyMatrix[indexs]) ? Realtotalweight : Long_ReSize(maxWidth, homographyMatrix[indexs]);
                RealtotalAera = RealtotalAera + Aera_Resize(maxArea, homographyMatrix[indexs]);

            }
            textBox1.Text ="长：" +  Convert.ToString(totalLong);
            textBox2.Text = "宽：" + Convert.ToString(totalweight);
            textBox3.Text = "面积：" + Convert.ToString(totalAera);

            textBox4.Text = "真实长：" + Convert.ToString(RealtotalLong);
            textBox5.Text = "真实宽：" + Convert.ToString(Realtotalweight);
            textBox6.Text = "真实面积：" + Convert.ToString(RealtotalAera);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            for(int indexs = 0; indexs < 9; indexs++)
            {
                Mat image = Cv2.ImRead(filelist[indexs], ImreadModes.Grayscale);

                Mat correctedImage = new Mat();
                Cv2.WarpPerspective(image, correctedImage, homographyMatrix[indexs], new OpenCvSharp.Size(image.Width, image.Height), InterpolationFlags.Linear, OpenCvSharp.BorderTypes.Constant, new Scalar(255, 255, 255));
                Cv2.WarpPerspective(correctedImage, correctedImage, whomoMatrix[indexs], new OpenCvSharp.Size(correctedImage.Width, correctedImage.Height), InterpolationFlags.Linear, OpenCvSharp.BorderTypes.Constant, new Scalar(255, 255, 255));

                Bitmap bitmap = BitmapConverter.ToBitmap(image);
                piclist[indexs].Image = bitmap;

            }
            

        }

        private void button5_Click(object sender, EventArgs e)
        {

        }

        public double Long_ReSize(double originalLength, Mat mat)
        {
            double transformedLength = Math.Sqrt(Math.Pow(mat.Get<double>(0,0) * originalLength, 2) + Math.Pow(mat.Get<double>(1, 0) * originalLength, 2) + Math.Pow(mat.Get<double>(2, 0) * originalLength, 2));
            return transformedLength;
        }

        public double Aera_Resize(double originalArea, Mat mat)
        {
            double transformedArea = Math.Abs(mat.Get<double>(0, 0) * mat.Get<double>(1, 1) - mat.Get<double>(0, 1) * mat.Get<double>(1, 0)) * originalArea;
            return transformedArea;
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Form2 form2 = new Form2();
            form2.Show();


        }
    }
}


