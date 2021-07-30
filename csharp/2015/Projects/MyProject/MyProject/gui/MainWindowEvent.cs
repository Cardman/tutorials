
using System;
using System.IO;
using System.Reflection;
using System.Windows.Forms;

namespace MyProject.gui
{
    public partial class MainWindow
    {
        private string htmlText = "";
        private void button1_MouseUp(object sender, MouseEventArgs e)
        {
            //Event
            textContainer.Text = "";
            Assembly assembly = Assembly.GetExecutingAssembly();
            //assembly.
            /*foreach (FileStream s in assembly.GetFiles())
            {
                if (s != null)
                {
                    using (StreamReader reader = new StreamReader(s))
                    {
                        string result = reader.ReadToEnd();
                        textContainer.Text += result + "\n";
                    }
                }
                else
                {
                    textContainer.Text += " bug";
                }
                s.Close();
            }*/
            string[] files = assembly.GetManifestResourceNames();
            foreach (string s in files)
            {
                /*using (Stream stream = assembly.GetManifestResourceStream(s))
                //using (Stream stream = asm.GetManifestResourceStream(asm.GetName().Name.ToString() + resourceName))
                {
                    if (stream != null)
                    {
                        using (StreamReader reader = new StreamReader(stream))
                        {
                            string result = reader.ReadToEnd();
                            textContainer.Text += result + "\n";
                        }
                    }
                    else
                    {
                        textContainer.Text += " bug";
                    }
                }*/
                textContainer.Text += s + "\n";
            }
            //textContainer.Text = "";
            textContainer.Text += label.getWidth(textBox1.Text) + "\n";
            label.setColorText(textBox1.Text);
        }
        private void webBrowser1_Navigating(object sender, WebBrowserNavigatingEventArgs e)
        {
            HtmlDocument document =
                    this.webBrowser1.Document;
            if (document == null)
            {
                return;
            }
            //e.Cancel = true;
            HtmlElement e_ = document.ActiveElement;
            //e_ is submit input or anchor
            bool process_ = false;
            while (true)
            {
                if (e_ == null)
                {
                    break;
                }
                Console.WriteLine(e_.TagName + "%%");
                if ("FORM".Equals(e_.TagName) || "A".Equals(e_.TagName))
                {
                    process_ = true;
                    break;
                }
                e_ = e_.Parent;
            }
            if (document.ActiveElement != null)
            {
                Console.WriteLine("end with: " + document.ActiveElement.TagName);
            }

            if (!process_)
            {
                Console.WriteLine(this.webBrowser1.DocumentText);
                return;
            }
            //
            htmlText = "<html><head><style>.excuse{color:blue;}</style></head><body><a href=\"hurlement2\">Hello 2!!</a><br/>";
            //retrieve data by e_.GetElementsByTagName("INPUT");
            HtmlElementCollection c_ = e_.GetElementsByTagName("INPUT");

            foreach (HtmlElement element_ in c_)
            {
                if (element_.GetAttribute("name").Equals("prenom"))
                {
                    htmlText += element_.GetAttribute("value") + "<br/>";
                }
            }
            //retrieve href by GetAttribute
            htmlText += e_.GetAttribute("href");
            htmlText += "<img src=\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAcAAAAHCAIAAABLMMCEAAAAEUlEQVR42mN4K6OCiRgGgSgAfEs5nifMv08AAAAASUVORK5CYII=\"/>";
            htmlText += "<form action=\"theatre\" name=\"mar\" method=\"post\"><input name=\"prenom\"/><input name=\"validate\" type=\"submit\" value=\"OK\"/></form>";
            htmlText += "<br/>";
            htmlText += "<span class=\"excuse\">Tarot</span><br/>";
            htmlText += "<a href=\"chien\">here</a>";
            htmlText += "</body></html>";//

            this.webBrowser1.Navigate("about:blank");
            HtmlDocument doc = this.webBrowser1.Document;
            doc.Write(string.Empty);
            Console.WriteLine("HERE");
            this.webBrowser1.DocumentText = htmlText;
            //mshtml.IHTMLDocument2 h_;
            //h_ = this.webBrowser1.Document.DomDocument as mshtml.IHTMLDocument2;
            //h_.body.innerHTML = htmlText;
            //Console.WriteLine();
            //this.webBrowser1.Document.DomDocument.GetType();
            //webBrowser1.DocumentText = htmlText;
            //webBrowser1.Invalidate();
        }
    }
}