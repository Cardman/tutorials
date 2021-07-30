using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ThreadsPoolGui
{
    public class MessageDialog : Form
    {
        private static MessageDialog dialog = new MessageDialog("Want to exit?", "Closing window");
        private bool ok = false;
        public static MessageDialog getDialog(Form _form)
        {
            dialog.ok = false;
            dialog.ShowDialog(_form);
            return dialog;
        }
        private MessageDialog(string _text, string _caption)
        {
            Width = 500;
            Height = 150;
            Text = _caption;
            Label textLabel = new Label() { Left = 50, Top = 20, Text = _text };
            //NumericUpDown inputBox = new NumericUpDown () { Left = 50, Top=50, Width=400 };
            Button confirmation = new Button() { Text = "Ok", Left = 50, Width = 100, Top = 70 };
            confirmation.Click += (sender, e) => { ok = true; Hide(); };
            Controls.Add(confirmation);
            Button cancel_ = new Button() { Text = "Cancel", Left = 350, Width = 100, Top = 70 };
            cancel_.Click += (sender, e) => { ok = false; Hide(); };
            Controls.Add(cancel_);
            Controls.Add(textLabel);
            //Controls.Add(inputBox);
            //ShowDialog();
            //return (int)inputBox.Value;
        }
        public bool isOk()
        {
            return ok;
        }
    }
}
