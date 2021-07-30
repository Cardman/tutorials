using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SimpleApplication
{
    public partial class Form1 : Form
    {
        private Button MyButton = new Button();
        public Form1()
        {
            InitializeComponent();
            MyButton.Text = "Click";
            MyButton.Size = new Size(256,32);
            MyEvent ev = new MyEvent();
            ev.Owner = this;
            ev.MyButton = MyButton;
            MyButton.MouseClick += ev.SendEvent;
            MyButton.MouseLeave += ev.ExitEvent;
            MyButton.MouseEnter += ev.EnterEvent;
            Controls.Add(MyButton);
        }
    }
    public class MyEvent {
        public Form Owner;
        public Button MyButton;
        public void SendEvent(object sender, MouseEventArgs ev) {
            MyButton.Text = "Click " + ev.Location.X + "," + ev.Location.Y;
        }
        public void EnterEvent(object sender, EventArgs ev)
        {
            MyButton.Text = "Entered " + (Cursor.Position.X- Owner.Location.X) + "," + (Cursor.Position.Y- Owner.Location.Y);
        }
        public void ExitEvent(object sender, EventArgs ev)
        {
            MyButton.Text = "Exit " + (Cursor.Position.X - Owner.Location.X) + "," + (Cursor.Position.Y - Owner.Location.Y);
        }
    }
}
