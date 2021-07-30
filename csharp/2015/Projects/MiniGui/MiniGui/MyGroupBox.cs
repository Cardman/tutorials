using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MiniGui
{
    class MyGroupBox : GroupBox
    {
        private MainWindow window;
        private Button buttonOne;
        private Button buttonTwo;
        public MyGroupBox(MainWindow _window)
        {
            window = _window;
            buttonOne = new Button();
            buttonOne.MouseUp += new MouseEventHandler(buttonOne_MouseUp);
            buttonOne.Text = "one";
            buttonTwo = new Button();
            buttonTwo.MouseUp += new MouseEventHandler(buttonTwo_MouseUp);
            buttonTwo.Text = "two";
            Controls.Add(buttonOne);
            buttonTwo.Location = new Point(0, buttonOne.Height);
            Controls.Add(buttonTwo);
            Size = new Size(buttonOne.Width, buttonOne.Height + buttonTwo.Height);
        }

        private void buttonTwo_MouseUp(object sender, MouseEventArgs e)
        {
            window.subMenuTwo();
        }

        private void buttonOne_MouseUp(object sender, MouseEventArgs e)
        {
            window.subMenuOne();
        }
    }
}
