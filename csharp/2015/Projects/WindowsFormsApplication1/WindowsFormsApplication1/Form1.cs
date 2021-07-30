using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml;
using System.Reflection;
using MyLibrary;
using System.IO;
using WindowsFormsApplication1.Properties;
using System.Resources;
using System.Collections;
using Microsoft.CSharp;
using System.CodeDom.Compiler;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        private string htmlText;
        public Form1()
        {
            InitializeComponent();
            //webBrowser1.AllowNavigation = true;
            this.webBrowser1.Navigate("about:blank");
            HtmlDocument doc = this.webBrowser1.Document;
            doc.Write(string.Empty);
            htmlText = "<html><body><a href=\"hurlement2\">Hello 2!!</a>";
            try
            {
                string fileName_ = "C:/Users/cardman/Documents/Visual Studio 2015/Projects/WindowsFormsApplication1/WindowsFormsApplication1/myresources/trs/ex.mp4";
                //string resourceName = "myresources.trs.ex.mp4";
                byte[] bytes_ = File.ReadAllBytes(fileName_);
                string s3 = Convert.ToBase64String(bytes_);
                //htmlText += "<br/>";
                //Console.WriteLine(s3.Substring(0, 32));
                //htmlText += "<video controls='controls'><source type='video/mp4' src='data:video/mp4;base64,"+s3+"'/></video>";//not supported
                //htmlText += "<br/>";
                //Assembly asm = Assembly.GetExecutingAssembly();
                //Stream stream = asm.GetManifestResourceStream(asm.GetName().Name.ToString() + ".Resources." + "testres.txt");
                //using (Stream stream = assembly.GetManifestResourceStream(resourceName))
                /*using (Stream stream = asm.GetManifestResourceStream(asm.GetName().Name.ToString() + ".Properties." + resourceName))
                //using (Stream stream = asm.GetManifestResourceStream(asm.GetName().Name.ToString() + resourceName))
                {
                    if (stream != null)
                    {
                        Stream reb_ = ConvertToBase64(stream);
                        using (StreamReader reader = new StreamReader(reb_))
                        {
                            Console.WriteLine(reader.ReadToEnd().Substring(0, 32));
                            //Stream reb_ = ConvertToBase64(stream);
                            //string result = reader.ReadToEnd();
                            //htmlContainer21.Text += result + "\n";
                        }
                    }
                    else
                    {
                        Console.WriteLine("KO wideo 1");
                        //htmlContainer21.Text += " bug";
                    }
                }*/
            }
            catch (Exception e)
            {
                Console.WriteLine("KO wideo 2");

            }
            htmlText += "<img src=\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAcAAAAHCAIAAABLMMCEAAAAEUlEQVR42mN4K6OCiRgGgSgAfEs5nifMv08AAAAASUVORK5CYII=\"/>";
            htmlText += "<a title=\"helper\">SOS</a>";
            htmlText += "<img src=\"data:image/gif;base64,R0lGODlhCgAKAPEAAAAAAAAAAP///wAAACH5BAFkAAAAIf8LTkVUU0NBUEUyLjADAQAAACwAAAAACgAKAEEILAAFCBw4EICAAAMRCjSo8GBBhwIbMkz48GCAhgImRnzYUCLEjwBCXgwQsmRAACH5BAFkAAAAIf8LTkVUU0NBUEUyLjADAQAAACwAAAAACgAKAEEILAAFCBw4EMDAAAQFGBSIkODCAA0LHky4UEBEgQYRXlQ40WHHggBCBghJEkBAACH5BAFkAAAAIf8LTkVUU0NBUEUyLjADAQAAACwAAAAACgAKAEEIKwAFCBw4EIDAAAQFGiSIUKGAhg8LMiS4MIBFigkhLjyIkSNFABZDAhgJICAAIfkEAWQAAAAh/wtORVRTQ0FQRTIuMAMBAAAALAAAAAAKAAoAQQgvAAUIHDgQgIAAAxEKNEhQoQCDDh0yTFhQYICLBCdarGjR4UOCBwsCAHAxwMiTAQEAIfkEAWQAAAAh/wtORVRTQ0FQRTIuMAMBAAAALAAAAAAKAAoAQQgvAAUIHDgQAMEABA0KQIiw4MAADQUabBhRgEKBFS9CTIhxIUeIIAsCGAkgAMmRAQEAIfkEAWQAAAAh/wtORVRTQ0FQRTIuMAMBAAAALAAAAAAKAAoAQQgqAAUIHDgQgIAAAxEKNBigocKFAh8WJHhw4kGHEyVmTGiR40IAAByCHBkQACH5BAFkAAAAIf8LTkVUU0NBUEUyLjADAQAAACwAAAAACgAKAEEIMAAFCBw4EICAAAMRCjSIMIDChQcTFowo8KHBgw4JMiQ4MSNFARsrFgQAwGEAkigDAgAh+QQBZAAAACH/C05FVFNDQVBFMi4wAwEAAAAsAAAAAAoACgBBCCwABQgcOBCAwAAEBRo8mHDhQIQKHzYUEKBixYIEIUZkSHChxoIAAAQISTJkQAAh+QQBZAAAACH/C05FVFNDQVBFMi4wAwEAAAAsAAAAAAoACgBBCCwABQgcOBCAgAADEQo0qPBgQYcCGzJM+PBggIYCJkaseBGjRogZAQDoKLJkQAAh+QQBZAAAACH/C05FVFNDQVBFMi4wAwEAAAAsAAAAAAoACgBBCC8ABQgcOBCAgAADEQo0qPBgQYcCGxo8iFBixAANBTBM+FAhxocEJQIAgDHAyJMBAQA7\"/>";
            //
            htmlText += "<form action=\"theatre\" name=\"mar\" method=\"post\"><input name=\"prenom\"/><input name=\"validate\" type=\"submit\" value=\"OK\"/></form></body></html>";
            Console.WriteLine(htmlText.Length+" chars");
            this.webBrowser1.WebBrowserShortcutsEnabled = true;
            webBrowser1.DocumentText = htmlText;
            setButtonText();
            Assembly assembly = Assembly.GetExecutingAssembly();
            //Assembly.get
            //string resourceName = "MyCompany.MyProduct.MyFile.txt";
            try
            {
                // Create a ResXResourceReader for the file items.resx.
                //ResXResourceReader rsxr = new ResXResourceReader("Resources.resx");
                // Iterate through the resources and display the contents to the console.
                /*foreach (DictionaryEntry d in rsxr)
                {
                    Console.WriteLine(d.Key.ToString() + ":\t" + d.Value.ToString());
                }*/
                //Close the reader.
                //rsxr.Close();
                //ResourceManager rm = new ResourceManager("WindowsFormsApplication1", Assembly.GetExecutingAssembly());
                //rm.GetString("testres.txt");
                string[] files = assembly.GetManifestResourceNames();
                foreach (string s in files)
                {
                    htmlContainer21.Text += s+"\n";
                }
                    // foreach (string s in files)
                    //{
                    // ResourceReader rr1 = new ResourceReader(s);
                    //IDictionaryEnumerator p = rr1.GetEnumerator();
                    //htmlContainer21.Text += p.Current.ToString();
                    /*foreach (Dictionary<string,string> d in rr1.GetEnumerator())
                    {

                    }*/
                    //}
                    /*foreach (FileStream s in assembly.GetFiles())
                    {
                        if (s != null)
                        {
                            using (StreamReader reader = new StreamReader(s))
                            {
                                string result = reader.ReadToEnd();
                                htmlContainer21.Text += result;
                            }
                            s.Close();
                        }
                        else
                        {
                            htmlContainer21.Text += " bug";
                        }
                        //htmlContainer21.Text += assembly.GetManifestResourceInfo(s). + "\n"; 
                    }*/
                    //assembly.GetManifestResourceInfo("");
                    //string resourceName = "WindowsFormsApplication1.myresources.trs.testres.txt";
                    //string resourceName = "WindowsFormsApplication1.myresources.trs.testres.txt";
                    string resourceName = "myresources.trs.testres.txt";
                //WindowsFormsApplication1.Properties.myresources.trs.testres.txt
                //ResourceReader rr1 = new ResourceReader(resourceName);
                //IDictionaryEnumerator p = rr1.GetEnumerator();
                //htmlContainer21.Text += p.Current.ToString();
                //resourceName = "WindowsFormsApplication1.testres.txt";
                //htmlContainer21.Text += Resources.ResourceManager.GetStream(resourceName);
                Assembly asm = Assembly.GetExecutingAssembly();
                //Stream stream = asm.GetManifestResourceStream(asm.GetName().Name.ToString() + ".Resources." + "testres.txt");
                //using (Stream stream = assembly.GetManifestResourceStream(resourceName))
                using (Stream stream = asm.GetManifestResourceStream(asm.GetName().Name.ToString() + ".Properties." + resourceName))
                //using (Stream stream = asm.GetManifestResourceStream(asm.GetName().Name.ToString() + resourceName))
                {
                    if (stream != null)
                    {
                        using (StreamReader reader = new StreamReader(stream))
                        {
                            string result = reader.ReadToEnd();
                            htmlContainer21.Text += result+"\n";
                        }
                    }
                    else
                    {
                        htmlContainer21.Text += " bug";
                    }
                }
                
                /*using (Stream stream = assembly.GetManifestResourceStream(resourceName))
                using (StreamReader reader = new StreamReader(stream))
                {
                    string result = reader.ReadToEnd();
                    htmlContainer21.Text = result;
                }*/
            }
            catch (Exception e)
            {
                Console.WriteLine(e.StackTrace);
            }
           
            string str_ = "<Names>";
            str_ += "<Name>";
            str_ += "<FirstName>John</FirstName>";
            str_ += "<LastName>Smith</LastName>";
            str_ += "</Name>";
            str_ += "<Name>";
            str_ += "<FirstName>James</FirstName>";
            str_ += "<LastName>White</LastName>";
            str_ += "</Name>";
            str_ += "</Names>";
            XmlDocument xml = new XmlDocument();
            xml.LoadXml(str_); // suppose that myXmlString contains "<Names>...</Names>"

            XmlNodeList xnList = xml.SelectNodes("/Names/Name");
            foreach (XmlNode xn in xnList)
            {
                string firstName = xn["FirstName"].InnerText;
                string lastName = xn["LastName"].InnerText;
                Console.WriteLine("Name: {0} {1}", firstName, lastName);
            }
            //SelectNodes is Case sensitive ==> no results
            xnList = xml.SelectNodes("/Names/name");
            foreach (XmlNode xn in xnList)
            {
                string firstName = xn["FirstName"].InnerText;
                string lastName = xn["LastName"].InnerText;
                Console.WriteLine("Name: {0} {1}", firstName, lastName);
            }
            try
            {
                // Get the type of a specified class.
                Type myType1 = Type.GetType("System.Int32");
                Console.WriteLine("The full name is {0}.\n", myType1.FullName);
            }
            catch (TypeLoadException e)
            {
                Console.WriteLine("{0}: Unable to load type System.Int32", e.GetType().Name);
            }
            try
            {
                // Get the type of a specified class.
                Type myType1 = Type.GetType("WindowsFormsApplication1.MyInteger");

                Console.WriteLine("The full name is {0}.\n", myType1.FullName);
                Console.WriteLine("The full name of the assembly is {0}.\n", myType1.Assembly.GetName().Name);
                foreach (FieldInfo p in myType1.GetFields(BindingFlags.NonPublic |
                         BindingFlags.Instance))
                {
                    Console.WriteLine("The type is {0} for {1}.\n", p.FieldType.ToString(), p.Name);
                }
                Console.WriteLine("SKIP LINE");
                foreach (PropertyInfo p in myType1.GetProperties(BindingFlags.Public | BindingFlags.NonPublic |
                         BindingFlags.Instance))
                {
                    Console.WriteLine("The type is {0} for {1}.\n", p.PropertyType.ToString(), p.Name);
                }
                object o_ = Activator.CreateInstance(myType1);
                PropertyInfo i_ = myType1.GetProperty("champ",
                         BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance);
                //i_.
                i_.SetValue(o_, 2);
                MyInteger m_ = o_ as MyInteger;
                //myType1.GetConstructors();
                Console.WriteLine("here is: " +m_);
                Console.WriteLine("here is: " + m_.name());
                m_.setChamp(3);
                Console.WriteLine("here is: " + m_);
                //Console.WriteLine("here is: " + m_.name<MyInteger>());//Does not compile
            }
            catch (Exception e)
            {
                Console.WriteLine("{0}: Unable to load type System.Int32", e.GetType().Name);
            }
            try
            {
                Assembly ass_ = Assembly.Load("MyLibrary");
                // Get the type of a specified class.
                //ass_.GetType()
                Type myType1 = ass_.GetType("MyLibrary.MyIntegerLib");
                Console.WriteLine("The full name is {0}.\n", myType1.FullName);
                foreach (PropertyInfo p in myType1.GetRuntimeProperties())
                {
                    Console.WriteLine("The type is {0} for {1}.\n", p.MemberType.ToString(), p.Name);
                }
                Console.WriteLine("SKIP LINE");
                foreach (PropertyInfo p in myType1.GetProperties(BindingFlags.NonPublic |
                         BindingFlags.Instance))
                {
                    Console.WriteLine("The type is {0} for {1}.\n", p.PropertyType.ToString(), p.Name);
                }
                object o_ = Activator.CreateInstance(myType1, 4);
                Console.WriteLine("here is: " + o_);
            }
            catch (Exception e)
            {
                Console.WriteLine("{0}: Unable to load type MyLibrary.MyIntegerLib", e.GetType().Name);
            }
            try
            {
                // Get the type of a specified class.
                Type myType1 = Type.GetType("Test Singe");
                Console.WriteLine("The full name is {0}.\n", myType1.FullName);
            }
            catch (Exception e)
            {
                //I am a complete beginner in the life
                Console.WriteLine("{0}: Unable to load type Test Singe", e.GetType().Name);
            }
            try
            {
                // Get the type of a specified class.
                Type myType1 = Type.GetType("System.int32");
                Console.WriteLine("The full name is {0}.\n", myType1.FullName);
            }
            catch (Exception e)
            {
                Console.WriteLine("{0}: Unable to load type System.int32", e.GetType().Name);
            }
            Console.WriteLine(Cards.EXCUSE.isTrump());
            Console.WriteLine(Cards.EXCUSE.name());
            Console.WriteLine(Cards.EXCUSE.ToFormattedString());
            Console.WriteLine(Cards.TRUMP_21.isTrump());
            Console.WriteLine(Cards.TRUMP_21.name());
            Console.WriteLine(Cards.TRUMP_21.ToFormattedString());
            Console.WriteLine(Cards.TRUMP_1.isTrump());
            Console.WriteLine(Cards.TRUMP_1.name());
            Console.WriteLine(Cards.TRUMP_1.ToFormattedString());
            Console.WriteLine("after %%");
            Type t_ = typeof(Cards);
            foreach (string s in t_.GetEnumNames())
            {
                Console.WriteLine(s);
            }
            foreach (object s in t_.GetEnumValues())
            {
                Console.WriteLine(s + " "+s.GetType());
            }
            Console.WriteLine("after %%");
            foreach (Cards s in ExtCards.getTrumps())
            {
                Console.WriteLine(s + " " + s.GetType());
            }
            Console.WriteLine("after %%");
            Console.WriteLine(t_.GetEnumName(Cards.TRUMP_21));
            Console.WriteLine(Cards.TRUMP_21.CompareTo(Cards.TRUMP_1));
            Console.WriteLine(Cards.TRUMP_1.CompareTo(Cards.TRUMP_21));
            Console.WriteLine(Cards.TRUMP_1.CompareTo(Cards.TRUMP_1));
            Console.WriteLine(t_ == Type.GetType("WindowsFormsApplication1.Cards"));
            Console.WriteLine(Cards.TRUMP_1.getFullName());
            //Console.WriteLine(t_.GetEnumName(null));//NullReferenceException
            /*try
            {
                Cards c_ = null;//Does not compile
                Console.WriteLine(c_);
            }
            catch (Exception e)
            {
                Console.WriteLine("{0}: Unable to load type System.int32", e.GetType().Name);
            }*/
            htmlContainer21.DetectUrls = true;
       }
        public Stream ConvertToBase64(Stream stream)
        {
            Byte[] inArray = new Byte[(int)stream.Length];
            Char[] outArray = new Char[(int)(stream.Length * 1.34)];
            stream.Read(inArray, 0, (int)stream.Length);
            Convert.ToBase64CharArray(inArray, 0, inArray.Length, outArray, 0);
            return new MemoryStream(Encoding.UTF8.GetBytes(outArray));
        }
        private void button1_Click(object sender, EventArgs e)
        {
            htmlContainer21.Text = textBox1.Text;
        }

        private void button1_MouseUp(object sender, MouseEventArgs e)
        {
            htmlContainer21.Text = textBox1.Text + " au contraire";
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
                Console.WriteLine(e_.TagName+"%%");
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

        private void htmlContainer21_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
