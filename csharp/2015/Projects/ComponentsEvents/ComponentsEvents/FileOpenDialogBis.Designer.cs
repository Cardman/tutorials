namespace ComponentsEvents
{
    partial class FileOpenDialogBis
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.flowLayoutPanel1 = new ComponentsEvents.MyFlowLayoutPanel();
            this.panel1 = new ComponentsEvents.MyPanel();
            this.folderName = new System.Windows.Forms.TextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.search = new System.Windows.Forms.Button();
            this.fileContent = new System.Windows.Forms.TextBox();
            this.fileFolders = new ComponentsEvents.MySpliterPane();
            this.folders = new System.Windows.Forms.TreeView();
            this.files = new System.Windows.Forms.DataGridView();
            this.NameCo = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Date = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.SizeCo = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Path = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.panel2 = new ComponentsEvents.MyPanel();
            this.fileName = new System.Windows.Forms.TextBox();
            this.flowLayoutPanel1.SuspendLayout();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.fileFolders)).BeginInit();
            this.fileFolders.Panel1.SuspendLayout();
            this.fileFolders.Panel2.SuspendLayout();
            this.fileFolders.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.files)).BeginInit();
            this.panel2.SuspendLayout();
            this.SuspendLayout();
            // 
            // flowLayoutPanel1
            // 
            this.flowLayoutPanel1.AutoSize = true;
            this.flowLayoutPanel1.Controls.Add(this.panel1);
            this.flowLayoutPanel1.Controls.Add(this.fileFolders);
            this.flowLayoutPanel1.Controls.Add(this.panel2);
            this.flowLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.flowLayoutPanel1.FlowDirection = System.Windows.Forms.FlowDirection.TopDown;
            this.flowLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.flowLayoutPanel1.Name = "flowLayoutPanel1";
            this.flowLayoutPanel1.Size = new System.Drawing.Size(490, 263);
            this.flowLayoutPanel1.TabIndex = 0;
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.folderName);
            this.panel1.Controls.Add(this.button1);
            this.panel1.Controls.Add(this.search);
            this.panel1.Controls.Add(this.fileContent);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(3, 3);
            this.panel1.MinimumSize = new System.Drawing.Size(0, 30);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(479, 30);
            this.panel1.TabIndex = 0;
            // 
            // folderName
            // 
            this.folderName.Location = new System.Drawing.Point(346, 6);
            this.folderName.Name = "folderName";
            this.folderName.Size = new System.Drawing.Size(100, 20);
            this.folderName.TabIndex = 3;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(265, 4);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 2;
            this.button1.Text = "Create folder";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // search
            // 
            this.search.Location = new System.Drawing.Point(13, 4);
            this.search.Name = "search";
            this.search.Size = new System.Drawing.Size(75, 23);
            this.search.TabIndex = 1;
            this.search.Text = "Search";
            this.search.UseVisualStyleBackColor = true;
            this.search.MouseUp += new System.Windows.Forms.MouseEventHandler(this.searchingFile);
            // 
            // fileContent
            // 
            this.fileContent.Location = new System.Drawing.Point(159, 4);
            this.fileContent.Name = "fileContent";
            this.fileContent.Size = new System.Drawing.Size(100, 20);
            this.fileContent.TabIndex = 0;
            // 
            // fileFolders
            // 
            this.fileFolders.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.fileFolders.Location = new System.Drawing.Point(3, 39);
            this.fileFolders.Name = "fileFolders";
            // 
            // fileFolders.Panel1
            // 
            this.fileFolders.Panel1.AutoScroll = true;
            this.fileFolders.Panel1.Controls.Add(this.folders);
            this.fileFolders.Panel1.RightToLeft = System.Windows.Forms.RightToLeft.No;
            // 
            // fileFolders.Panel2
            // 
            this.fileFolders.Panel2.AutoScroll = true;
            this.fileFolders.Panel2.Controls.Add(this.files);
            this.fileFolders.Panel2.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.fileFolders.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.fileFolders.Size = new System.Drawing.Size(479, 184);
            this.fileFolders.SplitterDistance = 139;
            this.fileFolders.TabIndex = 1;
            // 
            // folders
            // 
            this.folders.Dock = System.Windows.Forms.DockStyle.Fill;
            this.folders.Location = new System.Drawing.Point(0, 0);
            this.folders.Name = "folders";
            this.folders.PathSeparator = "/";
            this.folders.Size = new System.Drawing.Size(135, 180);
            this.folders.TabIndex = 0;
            this.folders.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.seeNode);
            // 
            // files
            // 
            this.files.AllowUserToAddRows = false;
            this.files.AllowUserToDeleteRows = false;
            this.files.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.files.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.files.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.NameCo,
            this.Date,
            this.SizeCo,
            this.Path});
            this.files.Dock = System.Windows.Forms.DockStyle.Fill;
            this.files.Location = new System.Drawing.Point(0, 0);
            this.files.Name = "files";
            this.files.ReadOnly = true;
            this.files.RowHeadersVisible = false;
            this.files.RowHeadersWidthSizeMode = System.Windows.Forms.DataGridViewRowHeadersWidthSizeMode.DisableResizing;
            this.files.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.files.Size = new System.Drawing.Size(332, 180);
            this.files.TabIndex = 0;
            this.files.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.selectFile);
            // 
            // NameCo
            // 
            this.NameCo.HeaderText = "Name";
            this.NameCo.Name = "NameCo";
            this.NameCo.ReadOnly = true;
            // 
            // Date
            // 
            this.Date.HeaderText = "Date";
            this.Date.Name = "Date";
            this.Date.ReadOnly = true;
            // 
            // SizeCo
            // 
            this.SizeCo.HeaderText = "Size";
            this.SizeCo.Name = "SizeCo";
            this.SizeCo.ReadOnly = true;
            // 
            // Path
            // 
            this.Path.HeaderText = "Path";
            this.Path.Name = "Path";
            this.Path.ReadOnly = true;
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.fileName);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel2.Location = new System.Drawing.Point(3, 229);
            this.panel2.MinimumSize = new System.Drawing.Size(0, 30);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(479, 30);
            this.panel2.TabIndex = 2;
            // 
            // fileName
            // 
            this.fileName.Location = new System.Drawing.Point(159, 7);
            this.fileName.Name = "fileName";
            this.fileName.Size = new System.Drawing.Size(100, 20);
            this.fileName.TabIndex = 0;
            this.fileName.KeyUp += new System.Windows.Forms.KeyEventHandler(this.typing);
            // 
            // FileOpenDialogBis
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(490, 263);
            this.Controls.Add(this.flowLayoutPanel1);
            this.Name = "FileOpenDialogBis";
            this.Text = "FileOpenDialog";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.cancelOpen);
            this.ResizeBegin += new System.EventHandler(this.changingPanels);
            this.ResizeEnd += new System.EventHandler(this.changedPanels);
            this.flowLayoutPanel1.ResumeLayout(false);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.fileFolders.Panel1.ResumeLayout(false);
            this.fileFolders.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.fileFolders)).EndInit();
            this.fileFolders.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.files)).EndInit();
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private MyFlowLayoutPanel flowLayoutPanel1;
        private MyPanel panel1;
        private MySpliterPane fileFolders;
        private MyPanel panel2;
        private System.Windows.Forms.TreeView folders;
        private System.Windows.Forms.DataGridView files;
        private System.Windows.Forms.TextBox fileName;
        private System.Windows.Forms.TextBox fileContent;
        private System.Windows.Forms.Button search;
        private System.Windows.Forms.DataGridViewTextBoxColumn NameCo;
        private System.Windows.Forms.DataGridViewTextBoxColumn Date;
        private System.Windows.Forms.DataGridViewTextBoxColumn SizeCo;
        private System.Windows.Forms.DataGridViewTextBoxColumn Path;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.TextBox folderName;
    }
}