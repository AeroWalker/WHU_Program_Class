using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Emgu.CV;
using Emgu.CV.CvEnum;
using Emgu.CV.Structure;
using System;
using System.Drawing;
using System.Timers;
using Emgu.CV;
using Emgu.CV.CvEnum;
using Emgu.CV.Structure;
using Emgu.CV.Util;
using OpenCvSharp;
using Emgu.CV.Reg;
using Emgu.CV.Legacy;

namespace WindowsFormsApp7
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        Emgu.CV.VideoCapture videoCapture = new Emgu.CV.VideoCapture();

        private void Form1_Load(object sender, EventArgs e)
        {
        }
        
        private void button1_Click(object sender, EventArgs e)
        {
            

            // 打开默认摄像头（通常是索引为 0 的摄像头）
            videoCapture.Get((CapProp)10);


            // 确保视频捕获对象已经打开
            if (!videoCapture.IsOpened)
            {
                MessageBox.Show("无法打开摄像头。");
                return;
            }

            // 创建定时器

            // 释放资源
            Emgu.CV.Mat frame = videoCapture.QueryFrame();
            Rectangle initialRegion = new Rectangle(Convert.ToInt32(frame.Width * 0.4), Convert.ToInt32(frame.Height * 0.4), Convert.ToInt32(frame.Width * 0.6), Convert.ToInt32(frame.Height * 0.4));
            tracker.Init(frame, initialRegion);

            timer1.Enabled = true;
        }


        Emgu.CV.Tracker tracker = new TrackerKCF();
        private void timer1_Tick(object sender, EventArgs e)
        {

            // 读取当前帧
            
            Emgu.CV.Mat frame = videoCapture.QueryFrame();

            // 检查帧是否为空
            if (frame == null)
                    return;

            // 将帧转换为 Bitmap

            // 在 PictureBox 中显示图像
            bool success = tracker.Update(frame, out Rectangle trackedRegion);
            Bitmap bitmap = Emgu.CV.BitmapExtension.ToBitmap(frame);
            Graphics graphics = Graphics.FromImage(bitmap);
            Pen pen = new Pen(Color.Red, 2);
            graphics.DrawRectangle(pen, trackedRegion);

            pictureBox1.Image = bitmap;
            
        }

        private void button2_Click(object sender, EventArgs e)
        {
            
        }
    }
}
