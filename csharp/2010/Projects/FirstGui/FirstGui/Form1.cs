using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Reflection;
using System.IO;
using System.IO.Compression;
using System.Xml;
using MyLibrary;

namespace FirstGui
{
    public partial class Hello : Form
    {
        public Hello()
        {
            InitializeComponent();
            //Class1 cl_ = new Class1();
            textBox3.Text = Convert.ToString(Class1.SayHello(1,2));
            /*System.Type type_ = typeof(MyEnum);
            Array array_ = type_.GetEnumValues();
            foreach (object o in array_) {
                if (o.ToString() == "ONE")
                {
                    textBox3.Text = o.ToString()+" "+o.GetType();
                    break;
                }
            }*/
            try
            {
                //Type type_ = Type.GetType("FirstGui.MyEnum");
                //textBox3.Text = type_.ToString();
                textBox3.Text = valueOf("FirstGui.MyEnum", "ONE").ToString();
                MyEnum myEnum_ = valueOf2<MyEnum>(typeof(MyEnum), "TWO");
                textBox3.Text = myEnum_.ToString();
            }
            catch (Exception e)
            {

            }
            try
            {
                MyClassReflect myObject = new MyClassReflect();
                Type myType = typeof(MyClassReflect);
                FieldInfo myFieldInfo = myType.GetField("myField",
                    BindingFlags.NonPublic | BindingFlags.Instance);
                textBox3.AppendText("\r\nold:" + myFieldInfo.GetValue(myObject).ToString());
                myFieldInfo.SetValue(myObject, 6);
                textBox3.AppendText("\r\nnew:" + myFieldInfo.GetValue(myObject).ToString());
            }
            catch (Exception e)
            {
                textBox3.AppendText("\r\n" + e.ToString());
            }
            try
            {
                MyClassReflect myObject = new MyClassReflect();
                Type myType = typeof(MyClassReflect);
                //ConstructorInfo const_ = myType.GetConstructor(new Type[] { typeof(String) });
                ConstructorInfo constructorInfoObj = myType.GetConstructor(
                    BindingFlags.Instance | BindingFlags.NonPublic, null, new Type[] { typeof(String) }, null);
                object obj_ = constructorInfoObj.Invoke(new String[] { "7" });
                FieldInfo myFieldInfo = myType.GetField("myField",
                    BindingFlags.NonPublic | BindingFlags.Instance);
                textBox3.AppendText("\r\ninit:" + myFieldInfo.GetValue(obj_).ToString());
            }
            catch (Exception e)
            {
                textBox3.AppendText("\n" + e.ToString());
            }
            //myObject.setF(6);
            //MyEnum.
            //MessageBox.Show("du texte");
            try
            {
                // Create an XML document instance.
                // The same instance of DOM is used through out this code; this 
                // may or may not be the actual case.
                XmlDocument doc = new XmlDocument();

                // Load the XML data from a file.
                // This code assumes that the XML file is in the same folder.
                ///doc.Load("Q317662.xml");

                // Load the XML data from a file stream.
                // You can also use other I/O streams in the same way with the 
                // Load method.
                ///FileStream fileStrm = new FileStream("Q317662.xml", FileMode.Open);
                // New content replaces older content because the same DOM is 
                // used.
                ///doc.Load(fileStrm);
                // Use DOM to manipulate the XML data here.
                // Close any Streams once they are used.
                ///fileStrm.Close();

                // Load the XML data from a URL.
                // Make sure that the URL points to a correct XML resource.
                ///doc.Load("http://localhost/xmltest/Q317662.xml");

                // Load the XML data from a reader object.
                // Ignore the white spaces.
                ///doc.PreserveWhitespace = false;
                // Read the XML by using XmlTextReader.            
                ///XmlTextReader rdr = new XmlTextReader("Q317662.xml");
                ///rdr.MoveToContent();     // Move to the content nodes.
                ///rdr.Read();              // Start reading.
                ///rdr.Skip();              // Skip the root.
                ///rdr.Skip();              // Skip the first content node.
                ///doc.Load(rdr);           // Read the second node data into DOM.

                // To load the entire data, pass in the reader object when its
                // state is ReadState.Initial.
                // To do this in the aforementioned code section, comment out 
                // the Skip and MoveToContent method calls.

                // Load the XML strings.
                //doc.LoadXml("<Collection><Book><Title>Priciple of Relativity</Title>" +
                 //  "<Author>Albert Einstein</Author>" +
                 //  "<Genre>Physics</Genre></Book></Collection>");

                // Display the content of the DOM document.
                textBox3.AppendText("\r\n" + doc.OuterXml);
                //XmlDocument contactDoc = new XmlDocument();
                //FileStream docOut =
                //new FileStream("C:/Users/cardman/Documents/output_c_sharp/xml_test.xml", FileMode.Create, FileAccess.Write, FileShare.Write);
                //contactDoc.Save(docOut);
                Stream myStream = new FileStream("C:/Users/cardman/Documents/output_c_sharp/xml_test_2.xml", FileMode.Create);

                if (myStream != null)
                {
                    using (myStream)
                    {
                        using (StreamWriter writer = new StreamWriter(myStream, Encoding.UTF8))
                        {
                            writer.Write(doc.OuterXml);
                        }
                    }
                }
                //string zipPath = @"c:\example\start.zip";
                string zipPath = @"C:\Users\cardman\workspace_cleaned\gestiondatabasepokemon\tmp_copy\rom_test\rom_pk_38.zip";
                //
                //string extractPath = @"c:\example\extract";
                using (ZipArchive archive = ZipFile.OpenRead(zipPath))
                {
                    foreach (ZipArchiveEntry entry in archive.Entries)
                    {
                        if (entry.FullName.Contains("/")) {
                            continue;
                        }
                        if (entry.FullName.Contains("tm")) {
                            continue;
                        }
                        if (entry.FullName.Contains("storage"))
                        {
                            continue;
                        }
                        if (entry.FullName.EndsWith(".txt", StringComparison.OrdinalIgnoreCase))
                        {
                            DeflateStream read_ = entry.Open() as DeflateStream;
                            String str_ = "";
                            byte[] by_ = new byte[1024];
                            while (true) {
                                int nb_ = read_.Read(by_, 0, 1024);
                                if (nb_ <= 0)
                                {
                                    break;
                                }
                                str_ += System.Text.Encoding.UTF8.GetString(by_, 0, nb_);
                            }
                            str_ = str_.Replace("\n", "\r\n");
                            str_ = str_.Replace("\r\r\n", "\r\n");
                            //ZipArchiveEntry.
                            textBox3.AppendText("\r\n" + entry.FullName);
                            textBox3.AppendText("\r\n" + str_);
                            read_.Close();
                            //read_.rea
                            //entry.ExtractToFile(Path.Combine(extractPath, entry.FullName));
                        }
                    }
                }
                zipPath = @"C:\Users\cardman\Documents\output_c_sharp\zip_test.zip";
                using (ZipArchive archive = ZipFile.Open(zipPath, ZipArchiveMode.Create))
                {
                    ZipArchiveEntry readmeEntry = archive.CreateEntry("Readme.txt");
                    using (StreamWriter writer = new StreamWriter(readmeEntry.Open()))
                    {
                        writer.WriteLine("Information about this package.");
                        writer.WriteLine("========================");
                    }
                }
            }
            catch (XmlException xmlEx)   // Handle the XML exceptions here.   
            {
                textBox3.AppendText("\r\n" + xmlEx.Message);
            }
            catch (Exception ex)         // Handle the generic exceptions here.
            {
                textBox3.AppendText("\r\n" + ex.Message);
            }
            finally
            {
                // Finalize here.
            }
        }
        public static object valueOf(string _type,string _in)
        {
            Type type_ = Type.GetType(_type);
            type_.GetField("");
            Array array_ = type_.GetEnumValues();
            foreach (object o in array_) {
                if (o.ToString() == _in)
                {
                    return o;
                }
            }
            throw new Exception();
        }
        public static T valueOf2<T>(Type _type, string _in)
        {
            Array array_ = _type.GetEnumValues();
            foreach (object o in array_)
            {
                if (o.ToString() == _in)
                {
                    return (T)o;
                }
            }
            throw new Exception();
        }
        private void button1_Click(object sender, EventArgs e)
        {
            bool error_ = false;
            int first_ = 0;
            int second_ = 0;
            try
            {
                first_ = Convert.ToInt32(textBox1.Text);
                label5.Text = "";
            }
            catch (Exception ex) {
                label5.Text = "Error of typing";
                error_ = true;
            }
            try
            {
                second_ = Convert.ToInt32(textBox2.Text);
                label6.Text = "";
            }
            catch (Exception ex)
            {
                label6.Text = "Error of typing";
                error_ = true;
            }
            if (error_)
            {
                label4.Text = "Error(s) of typing";
                return;
            }
            label4.Text = Convert.ToString(first_ + second_);
            //button1.Text = "Bouton cliqué !";
        }

        private void button2_Click(object sender, EventArgs e)
        {
            string fileName;
            string fileContent;
            OpenFileDialog openFileDialog1 = new OpenFileDialog();
            // On interdit la sélection de plusieurs fichiers.
            openFileDialog1.Multiselect = false;

            // On supprime le nom de fichier, qui ici vaut "openFileDialog1" (avant sélection d'un fichier).
            openFileDialog1.FileName = string.Empty;

            // On met des filtres pour les types de fichiers : "Nom|*.extension|autreNom|*.autreExtension" (autant de filtres qu'on veut).
            openFileDialog1.Filter = "Fichiers texte|*.txt|Tous les fichiers|*.*";

            // Le filtre sélectionné : le 2e (là on ne commence pas à compter à 0).
            openFileDialog1.FilterIndex = 2;

            // On affiche le dernier dossier ouvert.
            openFileDialog1.RestoreDirectory = true;

            // Si l'utilisateur clique sur "Ouvrir"...
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    // On récupère le nom du fichier.
                    fileName = openFileDialog1.FileName;

                    // On lit le fichier.
                    fileContent = File.ReadAllText(fileName);
                    textBox3.Text = fileContent;
                }
                // En cas d'erreur...
                catch (Exception ex)
                {
                    MessageBox.Show("Une erreur est survenue lors de l'ouverture du fichier : {0}.", ex.Message);
                }
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileDialog1 = new SaveFileDialog();
            saveFileDialog1.Filter = "Fichiers texte|*.txt|Tous les fichiers|*.*";
            saveFileDialog1.FilterIndex = 2;
            saveFileDialog1.RestoreDirectory = true;

            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    Stream myStream = saveFileDialog1.OpenFile();

                    if (myStream != null)
                    {
                        using (myStream)
                        {
                            using (StreamWriter writer = new StreamWriter(myStream, Encoding.UTF8))
                            {
                                writer.Write(textBox3.Text);
                            }
                        }
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Une erreur est survenue lors de l'écriture du fichier: {0}.", ex.Message);
                }
            }
        }
    }
    public enum MyEnum { ONE,TWO }
    public class MyClassReflect {
        private int myField;
        public MyClassReflect() {
            myField = 5;
        }
        private MyClassReflect(string _input)
        {
            myField = Convert.ToInt32(_input);
        }
        public void setF(int _newField) {
            myField = _newField;
        }
    }
}
