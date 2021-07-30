using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ComponentsEvents
{
    public partial class HelpForm : Form
    {
        public HelpForm()
        {
            InitializeComponent();
            treeHelp.Nodes.Add("one");
            treeHelp.Nodes[0].Nodes.Add("one one");
            treeHelp.Nodes[0].Nodes.Add("one two");
            treeHelp.Nodes.Add("two");
            treeHelp.Nodes[1].Nodes.Add("two one");
            treeHelp.Nodes[1].Nodes.Add("two two");
            //treeHelp.
            //treeHelp.Scrollable = true;
        }

        private void seeNode(object sender, TreeViewEventArgs e)
        {
            TreeNode node_ = treeHelp.SelectedNode;
            List<int> indexes_ = new List<int>();
            TreeNode currentNode_ = node_;
            while (currentNode_ != null)
            {
                indexes_.Insert(0, currentNode_.Index);
                currentNode_ = currentNode_.Parent;
            }
            string text_ = node_.FullPath + " ";
            text_ += node_.Index + " ";
            text_ += e.Node.FullPath + " ";
            foreach(int i in indexes_)
            {
                text_ += i + "%%";
            }
            pathTwo.Text = text_;
            //node_.Nodes.
            //node_.L
        }
    }
}
