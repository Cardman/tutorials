using SampleUmlForComponents;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ComponentsEvents
{
    public partial class DialogSports : Form
    {
        public DialogSports(City _city)
        {
            InitializeComponent();
            StringList list_ = new StringList();
            Text = _city.getName() + " " + _city.getBeginBuildingDate();
            int len_ = _city.getSportsCount();
            for (int i_ = 0; i_ < len_; i_++)
            {
                list_.Add(_city.getSport(i_));
            }
            /*for (int i_ = 0; i_ < len_; i_++)
            {
                Label l_ = new Label();
                l_.Text = _city.getSport(i_);
                listBox1.Items.Add(_city.getSport(i_));
                l_.Dispose();
                //_city.getSport(i_)
            }*/
            listBox1.DataSource = list_;
            //listBox1.DataSource 
            listBox1.DrawItem += drawIt;
        }

        private void drawIt(object sender, DrawItemEventArgs e)
        {
            Console.WriteLine(e.Index + " draw");
            //MyListBoxItem item = listBox1.Items[e.Index] as MyListBoxItem; // Get the current item and cast it to MyListBoxItem
            string item = listBox1.Items[e.Index] as string; // Get the current item and cast it to MyListBoxItem
            if (item != null)
            {
                Console.WriteLine(e.State);
                Graphics g_ = e.Graphics;
                if (e.State.getFullName().Contains(DrawItemState.Selected.getFullName()))
                {
                    g_.DrawRectangle( // Draw the appropriate text in the ListBox
                        new Pen(Color.Red), // Set the color 
                        //new Rectangle(0, e.Index * listBox1.ItemHeight, listBox1.Width, 10)
                        e.Bounds
                    );
                } else
                {
                    g_.DrawRectangle( // Draw the appropriate text in the ListBox
                        new Pen(Color.White), // Set the color 
                        //new Rectangle(0, e.Index * listBox1.ItemHeight, listBox1.Width, 10)
                        e.Bounds
                    );
                }

                g_.DrawString( // Draw the appropriate text in the ListBox
                                       //item.Message, // The message linked to the item
                    item, // The message linked to the item
                    listBox1.Font, // Take the font from the listbox
                                   //new SolidBrush(item.ItemColor), // Set the color 
                    new SolidBrush(Color.Black), // Set the color 
                    0, // X pixel coordinate
                    e.Index * listBox1.ItemHeight // Y pixel coordinate.  Multiply the index by the ItemHeight defined in the listbox.
                );
            }
            else
            {
                // The item isn't a MyListBoxItem, do something about it
            }
        }

        public DialogSports(IContainer container)
        {
            container.Add(this);

            InitializeComponent();
        }

        private void selectSport(object sender, EventArgs e)
        {
            nbSports.Text = "-1";
            ListBox.SelectedIndexCollection indexes_ = listBox1.SelectedIndices;
            string text_ = "";
            foreach (int i in indexes_)
            {
                text_ += i + ";";
            }
            if (text_.Length == 0)
            {
                text_ = "-1";
            }
            nbSports.Text = text_;
        }

        private void clearSportsSelection(object sender, MouseEventArgs e)
        {
            //This method call the "event" method "select index" with no selected indexes
            //Like JAVA
            listBox1.ClearSelected();
        }
    }
}
