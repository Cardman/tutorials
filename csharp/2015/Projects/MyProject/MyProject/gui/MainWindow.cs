using MyLibrary;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MyProject.gui
{
    public partial class MainWindow : Form
    {
        private Button button1;
        private RichTextBox textContainer;
        private TextBox textBox1;
        private WebBrowser webBrowser1;
        private MyLabel label;

        public MainWindow()
        {
            button1 = new Button();
            textContainer = new RichTextBox();
            textBox1 = new TextBox();
            webBrowser1 = new WebBrowser();
            label = new MyLabel();
            SuspendLayout();

            //button1.Location = new System.Drawing.Point(379, 272);
            //button1.Name = "button1";
            button1.Size = new Size(139, 20);
            //button1.TabIndex = 0;
            button1.Text = "button1";
            button1.UseVisualStyleBackColor = true;
            button1.MouseUp += new MouseEventHandler(button1_MouseUp);

            textBox1.Size = new Size(361, 20);
            //textBox1.TabIndex = 2;

            webBrowser1.Size = new Size(505, 163);
            textContainer.Width = webBrowser1.Width;
            //webBrowser1.TabIndex = 3;
            webBrowser1.Navigate("about:blank");
            HtmlDocument doc = this.webBrowser1.Document;
            doc.Write(string.Empty);
            htmlText = "<html><body><a href=\"hurlement2\">Hello 2!!</a>";
            htmlText += "<img src=\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAcAAAAHCAIAAABLMMCEAAAAEUlEQVR42mN4K6OCiRgGgSgAfEs5nifMv08AAAAASUVORK5CYII=\"/>";
            htmlText += "<form action=\"theatre\" name=\"mar\" method=\"post\"><input name=\"prenom\"/><input name=\"validate\" type=\"submit\" value=\"OK\"/></form></body></html>";
            webBrowser1.WebBrowserShortcutsEnabled = true;
            webBrowser1.DocumentText = htmlText;
            webBrowser1.Navigating += new WebBrowserNavigatingEventHandler(webBrowser1_Navigating);

            AutoScaleDimensions = new SizeF(6F, 13F);
            AutoScaleMode = AutoScaleMode.Font;
            BackColor = SystemColors.Control;
            //ClientSize = new System.Drawing.Size(530, 307);
            Controls.Add(webBrowser1);
            textContainer.Location = new Point(0, webBrowser1.Height);
            Controls.Add(textContainer);
            textBox1.Location = new Point(0, webBrowser1.Height + textContainer.Height);
            Controls.Add(textBox1);
            button1.Location = new Point(textBox1.Width, webBrowser1.Height + textContainer.Height);
            Controls.Add(button1);
            label.Location = new Point(20, webBrowser1.Height + textContainer.Height + textBox1.Height);
            Console.WriteLine(webBrowser1.Height + textContainer.Height + textBox1.Height);
            //label.Location = new Point(0, 280);
            label.Size = new Size(200, 150);
            //label.Invalidate();
            //label.Update();
            Controls.Add(label);
            //Paint += new PaintEventHandler(label.OnPaint);
            ClientSize = new Size(webBrowser1.Width, webBrowser1.Height + textContainer.Height + button1.Height + label.Height);
            //Controls.Add(new Label());
            //label.Update();
            ResumeLayout(false);
            PerformLayout();
            label.Invalidate();
            label.Update();
            try
            {
                //Controls.
                //MyClass c_;
                foreach (Assembly b in AppDomain.CurrentDomain.GetAssemblies())
                {
                    Console.WriteLine(b.GetName().Name);
                }
                Assembly a_ = Assembly.GetExecutingAssembly();
                //a_.
                foreach (AssemblyName n in a_.GetReferencedAssemblies())
                {
                    Console.WriteLine(n.Name);
                }
                Console.WriteLine("%%%%%");
                foreach (Module n in a_.GetModules())
                {
                    //n.
                    Console.WriteLine(n.Name);
                }
                Console.WriteLine("%%%%%");
                string[] str_ = new string[] {"souli"};
                string input_ = "le souligneur";
                foreach (string s in input_.Split(str_, StringSplitOptions.None))
                {
                    Console.WriteLine(s);
                }
                foreach (string s in Regex.Split(input_, "\\s+souli"))
                {
                    Console.WriteLine(s);
                }
            } catch (Exception e)
            {

            }
        }
    }
}
