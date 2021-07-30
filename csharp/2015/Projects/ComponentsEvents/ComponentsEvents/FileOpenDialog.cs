using SampleUmlForComponents;
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
    public partial class FileOpenDialog : Form
    {
        private string folder;
        private string currentFolder;
        private string selectedFile;
        private bool submitting;
        public FileOpenDialog()
        {
            submitting = false;
            InitializeComponent();
        }
        public void setupFolder(string _folder, Form _form)
        {
            folder = _folder.Replace("\\", "/");
            Text = folder;
            currentFolder = folder;
            //treeView1.Nodes.Clear();
            //treeView1.Visible = true;
            //folders.Nodes.Add(folder.Substring(folder.LastIndexOf("/") + 1));
            folders.Nodes.Add(folder);
            foreach (string d in Directory.GetDirectories(folder))
            {
                folders.Nodes[0].Nodes.Add(d.Substring(folder.Count() + 1));
            }
            files.Rows.Clear();
            foreach (string f in Directory.GetFiles(folder))
            {
                FileInfo f_ = new FileInfo(f);
                files.Rows.Add(new object[] { f_.Name, f_.LastWriteTime, f_.Length, f_.FullName.Replace("\\", "/") });
            }
            ShowDialog(_form);
        }

        private void selectFile(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex < 0)
            {
                return;
            }
            DataGridViewRow r_ = files.Rows[e.RowIndex];
            DataGridViewCell c_ = r_.Cells[0];
            object o_ = c_.Value;
            if (o_ is string)
            {
                fileName.Text = o_ as string;
            }
            else
            {
                fileName.Text = "";
            }
            c_ = r_.Cells[3];
            o_ = c_.Value;
            if (o_ is string)
            {
                selectedFile = o_ as string;
            }
            else
            {
                selectedFile = "";
            }
        }

        private void searchingFile(object sender, MouseEventArgs e)
        {
            DirectoryInfo currentFolder_ = new DirectoryInfo(currentFolder);
            if (!Directory.Exists(currentFolder_.FullName))
            {
                TreeNode selected_ = folders.SelectedNode;
                if (selected_ == null)
                {
                    return;
                }
                selected_.Remove();
                return;
            }
            MyList<FileSystemInfo> results_;
            results_ = new MyList<FileSystemInfo>();
            MyList<FileSystemInfo> current_;
            current_ = new MyList<FileSystemInfo>(currentFolder_);
            MyList<FileSystemInfo> next_;
            next_ = new MyList<FileSystemInfo>();
            while (true)
            {
                foreach (FileSystemInfo d in current_)
                {
                    foreach (string s in Directory.GetDirectories(d.FullName))
                    {
                        next_.Add(new DirectoryInfo(s));
                    }
                    foreach (string s in Directory.GetFiles(d.FullName))
                    {
                        FileInfo f_ = new FileInfo(s);
                        if (StringList.match(f_.Name, fileContent.Text))
                        {
                            results_.Add(f_);
                        }
                    }
                }
                if (next_.isEmpty())
                {
                    break;
                }
                current_ = new MyList<FileSystemInfo>(next_);
                next_ = new MyList<FileSystemInfo>();
            }
            files.Rows.Clear();
            foreach (FileSystemInfo f in results_)
            {
                FileInfo f_ = f as FileInfo;
                files.Rows.Add(new object[] { f_.Name, f_.LastWriteTime, f_.Length, f_.FullName.Replace("\\", "/") });
            }
        }

        private void typing(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                submit();
            }
        }

        private void submit()
        {
            if (selectedFile.isEmpty())
            {
                return;
            }
            submitting = true;
            Close();
        }

        private void cancelOpen(object sender, FormClosingEventArgs e)
        {
            if (!submitting)
            {
                selectedFile = "";
            }
        }
        public string getSelectedFile()
        {
            return selectedFile;
        }

        private void seeNode(object sender, TreeViewEventArgs e)
        {
            TreeNode node_ = folders.SelectedNode;
            string fullPath_ = folder + "/" + node_.FullPath + "/";
            fullPath_ = node_.FullPath;
            if (!Directory.Exists(fullPath_))
            {
                node_.Remove();
                return;
            }
            currentFolder = fullPath_;
            Text = currentFolder;
            node_.Nodes.Clear();
            foreach (string d in Directory.GetDirectories(currentFolder))
            {
                node_.Nodes.Add(d.Substring(currentFolder.Count()+1));
            }
            files.Rows.Clear();
            foreach (string f in Directory.GetFiles(currentFolder))
            {
                FileInfo f_ = new FileInfo(f);
                files.Rows.Add(new object[] { f_.Name, f_.LastWriteTime, f_.Length, f_.FullName.Replace("\\", "/") });
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (folderName.Text.isEmpty())
            {
                return;
            }
            TreeNode node_ = folders.SelectedNode;
            string str_ = node_.FullPath;
            Directory.CreateDirectory(str_ + "/" + folderName.Text);
            node_.Nodes.Clear();
            foreach (string d in Directory.GetDirectories(str_))
            {
                node_.Nodes.Add(d.Substring(str_.Count() + 1));
            }
        }
    }
}
