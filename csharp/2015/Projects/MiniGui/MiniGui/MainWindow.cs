using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing;

namespace MiniGui
{
    partial class MainWindow : Form
    {
        private MyGroupBox group;
        private Button backButton = new Button();
        public MainWindow()
        {
            SuspendLayout();
            backButton.Text = "go back";
            backButton.MouseUp += new MouseEventHandler(backButton_MouseUp);
            group = new MyGroupBox(this);
            Controls.Add(group);
            ClientSize = new Size(200, 200);
            ResumeLayout(false);
            PerformLayout();
        }

        private void backButton_MouseUp(object sender, MouseEventArgs e)
        {
            mainMenu();
        }

        public void mainMenu()
        {
            SuspendLayout();
            Controls.Clear();
            Controls.Add(group);
            ResumeLayout(false);
            PerformLayout();
        }
        public void subMenuOne()
        {
            SuspendLayout();
            Controls.Clear();
            Label l_ = new Label();
            l_.Text = "Hello one";
            l_.ForeColor = Color.FromArgb(0, 0, 64);
            l_.BackColor = Color.FromArgb(228,228,0);
            Controls.Add(l_);
            backButton.Location = new Point(0, l_.Height);
            Controls.Add(backButton);
            ResumeLayout(false);
            PerformLayout();
        }
        public void subMenuTwo()
        {
            SuspendLayout();
            Controls.Clear();
            Label l_ = new Label();
            l_.Text = "Hello two";
            l_.ForeColor = Color.FromArgb(64, 0, 0);
            l_.BackColor = Color.FromArgb(0, 228, 228);
            Controls.Add(l_);
            backButton.Location = new Point(0, l_.Height);
            Controls.Add(backButton);
            ResumeLayout(false);
            PerformLayout();
        }
    }
}
