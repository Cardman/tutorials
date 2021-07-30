using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Launcher
{
    public partial class Form1 : Form
    {
        //public Label Sample;
        public Action del2;
        public Form mainForm;

        private void button1_Click(object sender, EventArgs e)
        {
            
        }

        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                mainForm.Invoke(del2);
            }
            catch (Exception e0)
            {
                Console.WriteLine(e0);
            }
        }

        /*private void radioButton5_CheckedChanged(object sender, EventArgs e)
        {
            radioButton6.Checked = false;
            radioButton5.Checked = true;
        }

        private void radioButton6_CheckedChanged(object sender, EventArgs e)
        {
            radioButton5.Checked = false;
            radioButton6.Checked = true;
        }*/
        public static Keys ConvertCharToVirtualKey(char ch)
        {
            short vkey = VkKeyScan(ch);
            Keys retval = (Keys)(vkey & 0xff);
            int modifiers = vkey >> 8;
            if ((modifiers & 1) != 0) retval |= Keys.Shift;
            if ((modifiers & 2) != 0) retval |= Keys.Control;
            if ((modifiers & 4) != 0) retval |= Keys.Alt;
            return retval;
        }
        [System.Runtime.InteropServices.DllImport("user32.dll")]
        private static extern short VkKeyScan(char ch);

        private void label3_Click(object sender, EventArgs e)
        {
            //textBox1.Focusable = false;
            label3.Focus();
        }
    }
}
