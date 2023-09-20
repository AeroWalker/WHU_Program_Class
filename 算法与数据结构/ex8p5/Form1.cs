using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Linq;
using System.Xml.Serialization;
using System.IO;

namespace ex8p5
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            
        }

        public Robots getrobot()
        {
            string xml = File.ReadAllText("Robot.xml");
            using (StringReader sr = new StringReader(xml))
            {
                XmlSerializer serializer = new XmlSerializer(typeof(Robots));
                var rbts = serializer.Deserialize(sr);
                return rbts as Robots;
            }
            
        }

        private void lin2ObjToolStripMenuItem_Click(object sender, EventArgs e)
        {
            textBox1.BringToFront();
            Robots robots = getrobot();
            foreach(Robot robot in robots.RobotList)
            {
                textBox1.Text = textBox1.Text + "ID: " + robot.ID + "\t";
                textBox1.Text = textBox1.Text + "Name: " +  robot.Name + "\t";
                textBox1.Text = textBox1.Text + "IQ: " + robot.IQ + "\t";
                textBox1.Text = textBox1.Text + "\r\n";
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            textBox1.BringToFront();
            Robots robots = getrobot();
            var SearchList = from cust in robots.RobotList
                                       where cust.Name == textBox2.Text
                                       select cust;
            textBox1.Text = "";
            foreach(Robot robot in SearchList)
            {
                textBox1.Text = textBox1.Text + "ID: " + robot.ID + "\t";
                textBox1.Text = textBox1.Text + "Name: " + robot.Name + "\t";
                textBox1.Text = textBox1.Text + "IQ: " + robot.IQ + "\t";
                textBox1.Text = textBox1.Text + "\r\n";
            }
        }

        private void linq2XMLToolStripMenuItem_Click(object sender, EventArgs e)
        {
            textBox1.BringToFront();
            XmlSerializer serializer = new XmlSerializer(typeof(Robots));
            StringWriter sw = new StringWriter();
            serializer.Serialize(sw,getrobot());
            textBox1.Text = sw.ToString();
        }

        private void linq2DataSetToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Robots robots = getrobot();
            dataGridView1.BringToFront();
            dataGridView1.DataSource = robots.RobotList;
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }
    }

    [XmlRoot("Robots")]
    public class Robots
    {
        [XmlElement("Robot")]
        public List<Robot> RobotList { get; set; }
    }

    public class Robot
    {
        [XmlElement("ID")]
        public int ID { get; set; }

        [XmlElement("Name")]
        public string Name { get; set; }

        [XmlElement("IQ")]
        public int IQ { get; set; }
    }
}
