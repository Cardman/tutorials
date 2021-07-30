using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication3
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            object ev_ = null;
            ev_ = new System.EventHandler(this.button1_Click);
            button1.Click += (System.EventHandler)ev_;
            ev_ = new System.EventHandler(this.button1_Click);
            button2.Click += (System.EventHandler)ev_;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Button but = (Button)sender;
            MouseEventArgs m = (MouseEventArgs)e;
            System.Console.WriteLine("OK " + but.Text + " " + m);
        }
    }
    /*public class MyEvt : System.EventHandler {
    }*/

}
