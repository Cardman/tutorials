using SampleUmlForComponents;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ComponentsEvents
{
    public partial class SeeFile : Form
    {
        public SeeFile()
        {
            InitializeComponent();
            Button b_;
            b_ = new Button();
            b_.Text = "one";
            b_.Dock = DockStyle.Fill;
            myDockPanel1.getPanelOne().Controls.Add(b_);
            b_ = new Button();
            b_.Text = "two";
            b_.Dock = DockStyle.Fill;
            myDockPanel1.getPanelTwo().Controls.Add(b_);
            b_ = new Button();
            b_.Text = "three";
            b_.Dock = DockStyle.Fill;
            myDockPanel1.getPanelThree().Controls.Add(b_);
            b_ = new Button();
            b_.Text = "four";
            b_.Dock = DockStyle.Fill;
            myDockPanel1.getPanelFour().Controls.Add(b_);
            b_ = new Button();
            b_.Text = "five";
            b_.Dock = DockStyle.Fill;
            myDockPanel1.getPanelFive().Controls.Add(b_);
        }
        public void setup(string _title, string _text, Form _parent)
        {
            Text = _title;
            fileContent.Text = _text;
            ShowDialog(_parent);
        }

        private void saveFile(object sender, MouseEventArgs e)
        {
            FileStream fileStream_;
            if (!addedFile.Text.isEmpty())
            {
                string end_ = addedFile.Text;
                end_ = new Regex("([^/]*)$").Replace(end_, "$1");
                string begin_ = new FileInfo(Text).DirectoryName;
                fileStream_ = new FileStream(begin_ +"/"+end_, FileMode.Create, FileAccess.Write);
                // read from file
                using (StreamWriter writer_ = new StreamWriter(fileStream_))
                {
                    foreach (string l_ in fileContent.Lines)
                    {
                        writer_.WriteLine(l_);
                    }
                }
                fileStream_.Dispose();
                return;
            }
            fileStream_ = new FileStream(Text, FileMode.Open, FileAccess.Write);
            // read from file
            using (StreamWriter writer_ = new StreamWriter(fileStream_))
            {
                foreach (string l_ in fileContent.Lines)
                {
                    writer_.WriteLine(l_);
                }
            }
            fileStream_.Dispose();
        }

        private void selectMenu(object sender, MouseEventArgs e)
        {
            Console.WriteLine("Hello from sub menu");
        }

        private void seeMenuBis(object sender, MouseEventArgs e)
        {            
            Console.WriteLine(Directory.GetDirectoryRoot(Directory.GetCurrentDirectory()));
        }
    }
}
