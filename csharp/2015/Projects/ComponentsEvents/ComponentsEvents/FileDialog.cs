using SampleUmlForComponents;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ComponentsEvents
{
    public class FileDialog : Form
    {
        private DataGridViewTextBoxColumn NameCol;
        private DataGridViewTextBoxColumn Date;
        private DataGridViewTextBoxColumn SizeCol;
        private DataGridViewTextBoxColumn Path;
        private SplitContainer splitContainer1;
        private TreeView treeView1;
        private Panel panel1;
        private Panel panel2;
        private Panel panel3;
        private Button search;
        private TextBox fileContent;
        private TextBox fileName;
        private DataGridView dataGridView1;
        private string folder;
        private string currentFolder;
        private string selectedFile;
        private bool submitting;
        public FileDialog(string _folder)
        {
            submitting = false;
            InitializeComponent();
            NameCol.ValueType = typeof(string);
            Date.ValueType = typeof(DateTime);
            SizeCol.ValueType = typeof(long);
            Path.ValueType = typeof(string);
            dataGridView1.ColumnHeaderMouseClick += dataGridView1_ColumnHeaderMouseClick;
            dataGridView1.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            dataGridView1.CellClick += selectFile;
            folder = _folder.Replace("\\", "/");
            Text = folder;
            currentFolder = folder;
            selectedFile = "";
            //treeView1.Nodes.Clear();
            //treeView1.Visible = true;
            treeView1.Nodes.Add(folder.Substring(folder.LastIndexOf("/") + 1));
            foreach (string d in Directory.GetDirectories(folder))
            {
                treeView1.Nodes[0].Nodes.Add(d.Substring(folder.Count() + 1));
            }
            dataGridView1.Rows.Clear();
            foreach (string f in Directory.GetFiles(folder))
            {
                FileInfo f_ = new FileInfo(f);
                dataGridView1.Rows.Add(new object[] { f_.Name, f_.LastWriteTime, f_.Length, f_.FullName.Replace("\\", "/") });
            }
            //splitContainer1.Panel2.Controls.Add(dataGridView1);
            //dataGridView1.Rows.Add()
        }

        private void selectFile(object sender, DataGridViewCellEventArgs e)
        {
            DataGridViewRow r_ = dataGridView1.Rows[e.RowIndex];
            DataGridViewCell c_ = r_.Cells[0];
            object o_ = c_.Value;
            if (o_ is string)
            {
                fileName.Text = o_ as string;
            } else
            {
                fileName.Text = "%%%%%";
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

        private void seeNode(object sender, TreeViewEventArgs e)
        {
            TreeNode node_ = treeView1.SelectedNode;
            string fullPath_ = folder + "/" + node_.FullPath + "/";
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
                node_.Nodes.Add(d.Substring(currentFolder.Count()));
            }
            dataGridView1.Rows.Clear();
            foreach (string f in Directory.GetFiles(currentFolder))
            {
                FileInfo f_ = new FileInfo(f);
                dataGridView1.Rows.Add(new object[] { f_.Name, f_.LastWriteTime, f_.Length, f_.FullName.Replace("\\", "/") });
            }
        }

        private void InitializeComponent()
        {
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.NameCol = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Date = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.SizeCol = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Path = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.treeView1 = new System.Windows.Forms.TreeView();
            this.panel1 = new System.Windows.Forms.Panel();
            this.panel2 = new System.Windows.Forms.Panel();
            this.panel3 = new System.Windows.Forms.Panel();
            this.fileName = new System.Windows.Forms.TextBox();
            this.fileContent = new System.Windows.Forms.TextBox();
            this.search = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.panel1.SuspendLayout();
            this.panel2.SuspendLayout();
            this.panel3.SuspendLayout();
            this.SuspendLayout();
            // 
            // dataGridView1
            // 
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.NameCol,
            this.Date,
            this.SizeCol,
            this.Path});
            this.dataGridView1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dataGridView1.Location = new System.Drawing.Point(0, 0);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.Size = new System.Drawing.Size(232, 229);
            this.dataGridView1.TabIndex = 0;
            // 
            // NameCol
            // 
            this.NameCol.HeaderText = "Name";
            this.NameCol.Name = "NameCol";
            this.NameCol.ReadOnly = true;
            this.NameCol.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Programmatic;
            // 
            // Date
            // 
            this.Date.HeaderText = "Date";
            this.Date.Name = "Date";
            this.Date.ReadOnly = true;
            this.Date.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Programmatic;
            // 
            // SizeCol
            // 
            this.SizeCol.HeaderText = "Size";
            this.SizeCol.Name = "SizeCol";
            this.SizeCol.ReadOnly = true;
            this.SizeCol.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Programmatic;
            // 
            // Path
            // 
            this.Path.HeaderText = "Path";
            this.Path.Name = "Path";
            this.Path.ReadOnly = true;
            this.Path.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Programmatic;
            // 
            // splitContainer1
            // 
            this.splitContainer1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.splitContainer1.Location = new System.Drawing.Point(3, 29);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.AutoScroll = true;
            this.splitContainer1.Panel1.Controls.Add(this.treeView1);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.AutoScroll = true;
            this.splitContainer1.Panel2.Controls.Add(this.dataGridView1);
            this.splitContainer1.Size = new System.Drawing.Size(358, 233);
            this.splitContainer1.SplitterDistance = 118;
            this.splitContainer1.TabIndex = 1;
            // 
            // treeView1
            // 
            this.treeView1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.treeView1.Location = new System.Drawing.Point(0, 0);
            this.treeView1.Name = "treeView1";
            this.treeView1.Size = new System.Drawing.Size(114, 229);
            this.treeView1.TabIndex = 0;
            treeView1.PathSeparator = "/";
            treeView1.AfterSelect += new TreeViewEventHandler(seeNode);
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.panel3);
            this.panel1.Controls.Add(this.panel2);
            this.panel1.Controls.Add(this.splitContainer1);
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(364, 290);
            this.panel1.TabIndex = 0;
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.fileName);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.panel2.Location = new System.Drawing.Point(0, 266);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(364, 24);
            this.panel2.TabIndex = 2;
            // 
            // panel3
            // 
            this.panel3.Controls.Add(this.search);
            this.panel3.Controls.Add(this.fileContent);
            this.panel3.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel3.Location = new System.Drawing.Point(0, 0);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(364, 25);
            this.panel3.TabIndex = 3;
            // 
            // fileName
            // 
            this.fileName.Location = new System.Drawing.Point(5, 3);
            this.fileName.Name = "fileName";
            this.fileName.Size = new System.Drawing.Size(151, 20);
            this.fileName.TabIndex = 0;
            this.fileName.KeyUp += new System.Windows.Forms.KeyEventHandler(this.typing);
            // 
            // fileContent
            // 
            this.fileContent.Location = new System.Drawing.Point(5, 3);
            this.fileContent.Name = "fileContent";
            this.fileContent.Size = new System.Drawing.Size(151, 20);
            this.fileContent.TabIndex = 0;
            // 
            // search
            // 
            this.search.Location = new System.Drawing.Point(162, 2);
            this.search.Name = "search";
            this.search.Size = new System.Drawing.Size(106, 23);
            this.search.TabIndex = 1;
            this.search.Text = "Search";
            this.search.UseVisualStyleBackColor = true;
            this.search.MouseUp += new System.Windows.Forms.MouseEventHandler(this.fileSearching);
            // 
            // FileDialog
            // 
            this.ClientSize = new System.Drawing.Size(366, 302);
            this.Controls.Add(this.panel1);
            this.Name = "FileDialog";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.cancelOpen);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.panel1.ResumeLayout(false);
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.panel3.ResumeLayout(false);
            this.panel3.PerformLayout();
            this.ResumeLayout(false);

        }
        private void dataGridView1_ColumnHeaderMouseClick(
            object sender, DataGridViewCellMouseEventArgs e)
        {
            //dataGridView1.Sort(dataGridView1.Columns[e.ColumnIndex], System.ComponentModel.ListSortDirection.Ascending);
        }
        private void fileSearching(object sender, MouseEventArgs e)
        {
            DirectoryInfo currentFolder_ = new DirectoryInfo(currentFolder);
            if (!Directory.Exists(currentFolder_.FullName))
            {
                TreeNode selected_ = treeView1.SelectedNode;
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
                    foreach (string s in  Directory.GetDirectories(d.FullName))
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
            dataGridView1.Rows.Clear();
            foreach (FileSystemInfo f in results_)
            {
                FileInfo f_ = f as FileInfo;
                dataGridView1.Rows.Add(new object[] { f_.Name, f_.LastWriteTime, f_.Length, f_.FullName.Replace("\\", "/") });
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
    }
}
