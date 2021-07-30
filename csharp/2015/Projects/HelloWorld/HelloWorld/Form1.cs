using HelloWorld;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace HelloWorld
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void afficherScore(object sender, EventArgs e)
        {
            int loc_ = (int)ptsLocal.Value;
            int ext_ = (int)ptsVisiteurs.Value;
            Score score_;
            score_ = new Score(loc_, ext_);
            resultat.Text = score_.getCommentaire();
            nbInstanciations.Text = "Nb instances: " + Score.getNbInstances();
            Nullable<Card> c = null;
            c = Card.ACE;
            Card man_ = Card.JACK;
            Enum d = Card.KING;
            d = null;
            d = c as Enum;
            d = man_ as Enum;
            /*string str_ = "";
            foreach (Type t in Card.ACE.GetType().BaseType)
            {
                str_ += t.Name + ";";
            }*/
            nbInstanciations.Text += " "+ Card.KING.ordinal();
            Enums.getEnum<Card>("ACE");
            EnumList<int> angry;
            angry = new EnumList<int>();
            //Card.ACE.ordinal();
            //Enums.getEnum<int>("ACE");
            //EnumList<Card> hand_;
        }
    }
}
