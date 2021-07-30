using SampleUmlForComponents;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ComponentsEvents
{
    public partial class Form1 : Form
    {
        private bool addToCombobox;
        private string contentFile = "";
        private string[] tabWords = new string[] {
            "mais heu",
            "mai",
            "may",
            "zlatan",
            "zidane",
            "francois",
            "giroud",
            "cadre"};

        public Form1()
        {
            addToCombobox = true;
            InitializeComponent();
            //radioButton1.
            addToCombobox = false;
            MyList<string> l_ = new MyList<string>();
            Console.WriteLine(l_ is IEnumerable<object>);
            //Console.WriteLine(l_ is MyList<object>);//False
            //Console.WriteLine(l_ is IList<object>);//False
            Map<string, int> map_ = new Map<string, int>();
            map_.put("hello", 1);
            showEntries(map_);
            //ListableEntries<object, object> le_ = map_ as ListableEntries<object, object>;
            foreach (Type t in map_.GetType().GetInterfaces())
                Console.WriteLine(t);
            IEnumerable<IEntry<object, object>> ie_;
            ie_ = map_ as IEnumerable<IEntry<object, object>>;
            Console.WriteLine(ie_.getValue("hello"));
            foreach (object o in ie_.getKeys())
            {
                Console.WriteLine(o);
            }
            Console.WriteLine(map_.getKeys() is MyIList<object>);
            this.textBox1.AutoCompleteCustomSource.AddRange(tabWords);
            Assembly a_ = Assembly.GetAssembly(typeof(Form1));
            /*string[] files = Assembly.GetAssembly(typeof(MyLabel)).GetManifestResourceNames();
            foreach (string s in files)
            {
            }*/
            Image imgOne_ = null;
            Image imgTwo_ = null;
            using (Stream stream = a_.GetManifestResourceStream("ComponentsEvents.myresources.trs.imgs.MAGICARPE.txt"))
            {
                using (StreamReader reader = new StreamReader(stream))
                {
                    string result = reader.ReadToEnd();
                    imgOne_ = Base64ToImage(result);
                    imageList1.Images.Add(imgOne_);
                    //textContainer.Text += result + "\n";
                }
            }
            using (Stream stream = a_.GetManifestResourceStream("ComponentsEvents.myresources.trs.imgs.LEVIATOR.txt"))
            {
                using (StreamReader reader = new StreamReader(stream))
                {
                    string result = reader.ReadToEnd();
                    imgTwo_ = Base64ToImage(result);
                    imageList1.Images.Add(imgTwo_);
                    //textContainer.Text += result + "\n";
                }
            }
            //Console.WriteLine(HobbiesExt.randomHobby().getFullName());
        }
        public static Image Base64ToImage(string base64String)
        {
            // Convert Base64 String to byte[]
            byte[] imageBytes = Convert.FromBase64String(base64String);
            MemoryStream ms = new MemoryStream(imageBytes, 0,
              imageBytes.Length);

            // Convert byte[] to Image
            ms.Write(imageBytes, 0, imageBytes.Length);
            Image image = Image.FromStream(ms, true);
            return image;
        }
        private void showEntries(IEnumerable<IEntry<string,object>> _map)
        {
            Console.WriteLine(_map.GetType());
            foreach (IEntry<string, object> e in _map)
            {
                Console.WriteLine(e.getKey()+" "+e.getValue());
                Console.WriteLine(e.getKey().GetType() + " " + e.getValue().GetType());
                foreach (Type t in e.GetType().GetGenericArguments())
                {
                    Console.WriteLine(t);
                }
            }
            object o = Hobbies.AIKIDO;
            bool is_ = o is Enum;
            Enum h_ = o as Enum;
            Console.WriteLine(h_.getFullName()+" "+ is_);
            Console.WriteLine(ExtensionsEnum.getFullName(h_) + " " + is_);
            //_map.getKeys();
            Console.WriteLine(_map is IEnumerable<IEntry<object,object>>);
        }
        private void changingState(object sender, EventArgs e)
        {
            if (addToCombobox)
            {
                Console.WriteLine("adding an item...");
                return;
            }
            label1.Text = cities1.SelectedItem.ToString();
            //Form sports_ = new Form();
            //sports_.
            //Console.WriteLine(e.GetType()+" ");
            //Console.WriteLine("changing index to ");
        }

        private void seeSports(object sender, MouseEventArgs e)
        {
            object selectedItem_ = cities1.SelectedItem;
            if (selectedItem_ == null)
            {
                return;
            }
            City city_ = cities1.SelectedItem as City;
            DialogSports dialog_ = new DialogSports(city_);
            DialogResult results_ = dialog_.ShowDialog(this);
            Console.WriteLine(results_+" %%%");
        }

        private void testSelectedValue(object sender, EventArgs e)
        {
            Console.WriteLine(numericUpDown1.Value);
        }

        private void addingCity(object sender, MouseEventArgs e)
        {
            addToCombobox = true;
            cities1.Items.Add(new City(cityName.Text, numericUpDown1.Value.ToString()));
            addToCombobox = false;
            addCity.setClicked(false);
            //addCity.BackColor = Color.FromArgb(0, 0, 255);
            //addCity.ForeColor = Color.FromArgb(0, 255, 255);
        }

        private void clickBegin(object sender, MouseEventArgs e)
        {
            addCity.setClicked(true);
            //addCity.BackColor = Color.FromArgb(255, 0, 0);
            //addCity.ForeColor = Color.FromArgb(255, 255, 0);
        }

        private void validateData(object sender, EventArgs e)
        {
            if (checkBox1.Checked)
            {
                checkBox1.BackColor = Color.FromArgb(255, 0, 0);
            } else
            {
                checkBox1.BackColor = Color.FromArgb(0, 0, 255);
            }
        }

        private void fly(object sender, EventArgs e)
        {
            if (sender is RadioButton)
            {
                RadioButton o_ = sender as RadioButton;
                if (o_.Checked)
                {
                    o_.BackColor = Color.FromArgb(255, 0, 0);
                }
                else
                {
                    o_.BackColor = Color.FromArgb(0, 0, 255);
                }
            }
        }

        private void flyBis(object sender, EventArgs e)
        {
            if (sender is RadioButton)
            {
                RadioButton o_ = sender as RadioButton;
                if (o_.Checked)
                {
                    o_.BackColor = Color.FromArgb(255, 255, 0);
                }
                else
                {
                    o_.BackColor = Color.FromArgb(0, 255, 255);
                }
            }
        }

        /*private void splitContainer2_Panel2_Paint(object sender, PaintEventArgs e)
        {

        }*/

        private void splitContainer1_Panel2_Paint(object sender, PaintEventArgs e)
        {

        }

        private void typedString(object sender, EventArgs e)
        {
            Console.WriteLine(cityName.Text);
        }

        private void openHelp(object sender, MouseEventArgs e)
        {
            HelpForm h_ = new HelpForm();
            h_.ShowDialog(this);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            /*FileDialog f_ = new FileDialog(Directory.GetCurrentDirectory());
            f_.ShowDialog(this);
            label2.Text = f_.getSelectedFile();*/
            //OpenFileDialog other_ = new OpenFileDialog();
            //other_.
            FileOpenDialogBis f_ = new FileOpenDialogBis();
            f_.setupFolder(Directory.GetCurrentDirectory(), this);
            string read_ = f_.getSelectedFile();
            if (read_.isEmpty())
            {
                return;
            }
            contentFile = "";
            label2.Text = read_;
            FileStream fileStream_ = new FileStream(read_, FileMode.Open, FileAccess.Read);
            // read from file
            using (StreamReader reader_ = new StreamReader(fileStream_))
            {
                contentFile = reader_.ReadToEnd();
            }
            fileStream_.Dispose();
            /*try
            {
                byte[] imageBytes = Convert.FromBase64String(contentFile);
                File.WriteAllBytes("C:/Users/mercierdesrochettesf/Documents/Visual Studio 2015/Projects/ComponentsEvents/ComponentsEvents/bin/Debug/filename.mp4", imageBytes);
                const int arrayLength = 1000000000;
                //Open a FileStream in Read mode
                FileStream fin = new FileStream("", FileMode.Open,
                FileAccess.Read, FileShare.ReadWrite);

                //Create a BinaryReader from the FileStream
                BinaryReader br = new BinaryReader(fin);

                //Seek to the start of the file
                br.BaseStream.Seek(0, SeekOrigin.Begin);

                byte[] verifyArray = br.ReadBytes(arrayLength);

                //Close the stream and free the resources
                br.Close();

                string s = Convert.ToBase64String(verifyArray);
                //The fact that it's XML is basically irrelevant. You can save any text to a file very simply with File.WriteAllText:
                File.WriteAllText("filename2.xml", s);
                Console.WriteLine("OK");
            }
            catch (Exception e2)
            {
                Console.WriteLine(e2.StackTrace);
            }*/

        }

        private void seeFile_Click(object sender, EventArgs e)
        {
            SeeFile s_ = new SeeFile();
            s_.setup(label2.Text, contentFile, this);
        }

        private void seeTabs(object sender, MouseEventArgs e)
        {
            Tabs t_ = new Tabs();
            t_.ShowDialog(this);
        }

        private void testComponents_Click(object sender, EventArgs e)
        {
            /*BoxForm box_ = new BoxForm();
            box_.ShowDialog(this);*/
            SplitForm s_ = new SplitForm();
            s_.ShowDialog(this);
        }

        private void rock(object sender, MouseEventArgs e)
        {
            if (sender is RadioButton)
            {
                RadioButton o_ = sender as RadioButton;
                if (o_.Checked)
                {
                    o_.BackColor = Color.FromArgb(255, 0, 255);
                }
                else
                {
                    o_.BackColor = Color.FromArgb(0, 255, 0);
                }
            }
        }

        private void water(object sender, MouseEventArgs e)
        {
            if (sender is RadioButton)
            {
                RadioButton o_ = sender as RadioButton;
                if (o_.Checked)
                {
                    o_.BackColor = Color.FromArgb(0, 255, 255);
                }
                else
                {
                    o_.BackColor = Color.FromArgb(255, 255, 0);
                }
            }
        }

        private void commonOne(object sender, EventArgs e)
        {
            if (sender is RadioButton)
            {
                selectedRadio.Text = (sender as RadioButton).Text+" obi";
            } else
            {
                selectedRadio.Text = "Vador";
            }
        }

        private void commonTwo(object sender, EventArgs e)
        {
            if (sender is RadioButton)
            {
                selectedRadio.Text = (sender as RadioButton).Text+" to";
            }
            else
            {
                selectedRadio.Text = "Luke";
            }
        }

        private void changedTxt(object sender, EventArgs e)
        {
            /*TextBox t = sender as TextBox;
            if (t != null)
            {
                //say you want to do a search when user types 3 or more chars
                if (t.Text.Length >= 3)
                {
                    //SuggestStrings will have the logic to return array of strings either from cache/db
                    string[] arr = SuggestStrings(t.Text);

                    AutoCompleteStringCollection collection = new AutoCompleteStringCollection();
                    collection.AddRange(arr);

                    this.textBox1.AutoCompleteCustomSource = collection;
                    //this.textBox1.AutoCompleteMode = AutoCompleteMode.SuggestAppend;
                    //this.textBox1.AutoCompleteSource = AutoCompleteSource.CustomSource;
                }
                else
                {
                    AutoCompleteStringCollection collection = new AutoCompleteStringCollection();

                    this.textBox1.AutoCompleteCustomSource = collection;
                }
            }*/
        }

        private string[] SuggestStrings(string text)
        {
            MyList<string> words_ = new MyList<string>();
            Regex r_ = new Regex("\\W");
            Match m_ = r_.Match(text);
            int index_ = m_.Index;
            while (m_.Success)
            {
                index_ = m_.Index;
                m_ = m_.NextMatch();
            }
            foreach (string w in tabWords)
            {
                if (w.StartsWith(text.Substring(index_ + 1)))
                {
                    words_.Add(w);
                }
            }
            return words_.ToArray();
        }
    }
}
