using System;
using System.Windows.Forms;
using System.Windows;
using System.Windows.Controls;
using System.Collections.Generic;
using System.IO;
using System.ComponentModel;

namespace Launcher
{
    partial class Form1
    {
        /// <summary>
        /// Variable nécessaire au concepteur.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Nettoyage des ressources utilisées.
        /// </summary>
        /// <param name="disposing">true si les ressources managées doivent être supprimées ; sinon, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Code généré par le Concepteur Windows Form

        /// <summary>
        /// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
        /// le contenu de cette méthode avec l'éditeur de code.
        /// </summary>
        public void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.label1 = new System.Windows.Forms.Label();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.radioButton1 = new System.Windows.Forms.RadioButton();
            this.radioButton2 = new System.Windows.Forms.RadioButton();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.radioButton3 = new System.Windows.Forms.RadioButton();
            this.radioButton4 = new System.Windows.Forms.RadioButton();
            this.imageList1 = new System.Windows.Forms.ImageList(this.components);
            this.label2 = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.treeView1 = new System.Windows.Forms.TreeView();
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.nom = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Taille = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.modification = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.chemin = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.tableLayoutPanel1.SuspendLayout();
            this.tableLayoutPanel2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(94, 305);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(101, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "<html>Texte</html>";
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.Controls.Add(this.radioButton1, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.radioButton2, 0, 1);
            this.tableLayoutPanel1.Location = new System.Drawing.Point(276, 255);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 2;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(200, 47);
            this.tableLayoutPanel1.TabIndex = 3;
            // 
            // radioButton1
            // 
            this.radioButton1.AutoSize = true;
            this.radioButton1.Location = new System.Drawing.Point(3, 3);
            this.radioButton1.Name = "radioButton1";
            this.radioButton1.Size = new System.Drawing.Size(85, 17);
            this.radioButton1.TabIndex = 0;
            this.radioButton1.TabStop = true;
            this.radioButton1.Text = "radioButton1";
            this.radioButton1.UseVisualStyleBackColor = true;
            // 
            // radioButton2
            // 
            this.radioButton2.AutoSize = true;
            this.radioButton2.Location = new System.Drawing.Point(3, 26);
            this.radioButton2.Name = "radioButton2";
            this.radioButton2.Size = new System.Drawing.Size(85, 17);
            this.radioButton2.TabIndex = 1;
            this.radioButton2.TabStop = true;
            this.radioButton2.Text = "radioButton2";
            this.radioButton2.UseVisualStyleBackColor = true;
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.ColumnCount = 2;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel2.Controls.Add(this.radioButton3, 0, 0);
            this.tableLayoutPanel2.Controls.Add(this.radioButton4, 0, 1);
            this.tableLayoutPanel2.Location = new System.Drawing.Point(276, 305);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 2;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel2.Size = new System.Drawing.Size(200, 47);
            this.tableLayoutPanel2.TabIndex = 4;
            // 
            // radioButton3
            // 
            this.radioButton3.AutoSize = true;
            this.radioButton3.Location = new System.Drawing.Point(3, 3);
            this.radioButton3.Name = "radioButton3";
            this.radioButton3.Size = new System.Drawing.Size(85, 17);
            this.radioButton3.TabIndex = 0;
            this.radioButton3.TabStop = true;
            this.radioButton3.Text = "radioButton3";
            this.radioButton3.UseVisualStyleBackColor = true;
            // 
            // radioButton4
            // 
            this.radioButton4.AutoSize = true;
            this.radioButton4.Location = new System.Drawing.Point(3, 26);
            this.radioButton4.Name = "radioButton4";
            this.radioButton4.Size = new System.Drawing.Size(85, 17);
            this.radioButton4.TabIndex = 1;
            this.radioButton4.TabStop = true;
            this.radioButton4.Text = "radioButton4";
            this.radioButton4.UseVisualStyleBackColor = true;
            // 
            // imageList1
            // 
            this.imageList1.ColorDepth = System.Windows.Forms.ColorDepth.Depth8Bit;
            this.imageList1.ImageSize = new System.Drawing.Size(16, 16);
            this.imageList1.TransparentColor = System.Drawing.Color.Transparent;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(98, 233);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(35, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "label2";
            // 
            // textBox1
            // 
            this.textBox1.CausesValidation = false;
            this.textBox1.Location = new System.Drawing.Point(95, 332);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(100, 20);
            this.textBox1.TabIndex = 7;
            textBox1.KeyDown += downText;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(97, 253);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(36, 13);
            this.label3.TabIndex = 6;
            this.label3.Text = "Focus";
            this.label3.KeyDown += new System.Windows.Forms.KeyEventHandler(this.downKey);
            this.label3.Click += new System.EventHandler(this.label3_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(97, 270);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(26, 13);
            this.label4.TabIndex = 8;
            this.label4.Text = "Res";
            // 
            // treeView1
            // 
            this.treeView1.Location = new System.Drawing.Point(12, 12);
            this.treeView1.Name = "treeView1";
            this.treeView1.Size = new System.Drawing.Size(263, 218);
            this.treeView1.TabIndex = 9;
            treeView1.NodeMouseClick += this.ProcessNode;
            string[] drives = System.IO.Directory.GetLogicalDrives();
            foreach(string d in drives)
            {
                treeView1.Nodes.Add(d);
            }
            // 
            // dataGridView1
            // 
            this.dataGridView1.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Columns.AddRange(new DataGridViewColumn[] {
            this.nom,
            this.Taille,
            this.modification,
            this.chemin});
            this.dataGridView1.Location = new System.Drawing.Point(315, 40);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.Size = new System.Drawing.Size(240, 150);
            this.dataGridView1.TabIndex = 10;
            // 
            // nom
            // 
            this.nom.HeaderText = "Nom";
            this.nom.Name = "nom";
            // 
            // Taille
            // 
            this.Taille.HeaderText = "Taille";
            this.Taille.Name = "Taille";
            // 
            // modification
            // 
            this.modification.HeaderText = "Modification";
            this.modification.Name = "modification";
            // 
            // chemin
            // 
            this.chemin.HeaderText = "Chemin";
            this.chemin.Name = "chemin";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(567, 354);
            this.Controls.Add(this.dataGridView1);
            this.Controls.Add(this.treeView1);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.tableLayoutPanel2);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Controls.Add(this.label1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.tableLayoutPanel2.ResumeLayout(false);
            this.tableLayoutPanel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        /*private void CreateFolder(object sender, CancelEventArgs e)
        {
            Console.WriteLine(textBox1.Text);
        }*/

        private void ProcessNode(object sender, TreeNodeMouseClickEventArgs e)
        {
            /*TreeNode node = treeView1.SelectedNode;
            if (node == null)
            {
                return;
            }
            string fullPath = node.FullPath;
            if (!Directory.Exists(fullPath) && node.Parent != null)
            {
                TreeNode parent = node.Parent;
                if (parent != null) {
                    parent.Nodes.Remove(node);
                }
                return;
            }
            List<string> folders = new List<string>();
            List<string> files = new List<string>();
            if (node.Parent == null)
            {
                DriveInfo di = new DriveInfo(fullPath);
                foreach (FileInfo f in di.RootDirectory.GetFiles())
                {
                    FileAttributes attr = File.GetAttributes(f.FullName);
                    Console.WriteLine(f.FullName);
                    if (attr.HasFlag(FileAttributes.Directory))
                    {
                        folders.Add(f.Name);
                    }
                    else
                    {
                        files.Add(f.Name);
                    }
                }
                foreach (DirectoryInfo f in di.RootDirectory.GetDirectories())
                {
                    FileAttributes attr = File.GetAttributes(f.FullName);
                    Console.WriteLine(f.FullName);
                    if (attr.HasFlag(FileAttributes.Directory))
                    {
                        folders.Add(f.Name);
                    }
                    else
                    {
                        files.Add(f.Name);
                    }
                }
            } else
            {
                foreach (string f in Directory.GetFiles(fullPath))
                {
                    FileAttributes attr = File.GetAttributes(f);
                    if (attr.HasFlag(FileAttributes.Directory))
                    {
                        folders.Add(f);
                    }
                    else
                    {
                        files.Add(f);
                    }
                }
            }
            folders.Sort();
            node.Nodes.Clear();
            foreach (string f in folders)
            {
                node.Nodes.Add(f);
            }*/
            //node.Expand();
            //node.TreeView.EndUpdate();
            update(e.Node);
        }
        void update(TreeNode node)
        {
            string fullPath = node.FullPath;
            if (!Directory.Exists(fullPath) && node.Parent != null)
            {
                TreeNode parent = node.Parent;
                if (parent != null)
                {
                    parent.Nodes.Remove(node);
                }
                return;
            }
            List<string> folders = new List<string>();
            List<string> files = new List<string>();
            if (node.Parent == null)
            {
                DriveInfo di = new DriveInfo(fullPath);
                foreach (FileInfo f in di.RootDirectory.GetFiles())
                {
                    FileAttributes attr = File.GetAttributes(f.FullName);
                    Console.WriteLine(f.FullName);
                    if (attr.HasFlag(FileAttributes.Directory))
                    {
                        folders.Add(f.Name);
                    }
                    else
                    {
                        files.Add(f.Name);
                    }
                }
                foreach (DirectoryInfo f in di.RootDirectory.GetDirectories())
                {
                    FileAttributes attr = File.GetAttributes(f.FullName);
                    Console.WriteLine(f.FullName);
                    if (attr.HasFlag(FileAttributes.Directory))
                    {
                        folders.Add(f.Name);
                    }
                    else
                    {
                        files.Add(f.Name);
                    }
                }
            }
            else
            {
                foreach (DirectoryInfo f in new DirectoryInfo(fullPath).GetDirectories())
                {
                    FileAttributes attr = File.GetAttributes(f.FullName);
                    if (attr.HasFlag(FileAttributes.Directory))
                    {
                        folders.Add(f.Name);
                    }
                    else
                    {
                        files.Add(f.Name);
                    }
                }
                foreach (string f in Directory.GetFiles(fullPath))
                {
                    FileAttributes attr = File.GetAttributes(f);
                    if (attr.HasFlag(FileAttributes.Directory))
                    {
                        folders.Add(f);
                    }
                    else
                    {
                        files.Add(f);
                    }
                }
            }
            folders.Sort();
            node.Nodes.Clear();
            foreach (string f in folders)
            {
                node.Nodes.Add(f);
            }
            node.TreeView.EndUpdate();
        }
        private void downKey(object sender, KeyEventArgs e)
        {
            label4.Text = ""+e.Modifiers;
        }

        private void downText(object sender, KeyEventArgs e)
        {
            Keys o = e.KeyCode;
            if (e.KeyCode != Keys.Enter)
            {
                return;
            }
            TreeNode currentNode = treeView1.SelectedNode;
            if (currentNode == null)
            {
                return;
            }
            Directory.CreateDirectory(currentNode.FullPath + "\\" + textBox1.Text);
            update(currentNode);
            //Console.WriteLine("res down:" + currentNode.FullPath + "\\" + textBox1.Text);
        }
        private void down(object sender, KeyEventArgs e)
        {
            Keys o = e.KeyCode;
            Console.WriteLine("res down:" + o);
            Console.WriteLine("res down int:" + (int)o);
        }

        private void up(object sender, KeyEventArgs e)
        {
            Keys o = e.KeyCode;
            Console.WriteLine("res up:" + o);
            Console.WriteLine("res up int:" + (int)o);
        }

        private void evenement(object sender, KeyPressEventArgs e)
        {
            Keys o = ConvertCharToVirtualKey(e.KeyChar);
            Console.WriteLine("res pr:"+ o);
            Console.WriteLine("res pr int:" + (int)o);
        }

        #endregion
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.RadioButton radioButton1;
        private System.Windows.Forms.RadioButton radioButton2;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.RadioButton radioButton3;
        private System.Windows.Forms.RadioButton radioButton4;
        private System.Windows.Forms.ImageList imageList1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TreeView treeView1;
        private DataGridView dataGridView1;
        private DataGridViewTextBoxColumn nom;
        private DataGridViewTextBoxColumn Taille;
        private DataGridViewTextBoxColumn modification;
        private DataGridViewTextBoxColumn chemin;
        ////private System.Windows.Controls.DockPanel panel1;
        //private System.Windows.Forms.Panel panel1;
    }
}

