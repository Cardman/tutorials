namespace ComponentsEvents
{
    partial class SeeFile
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
            this.components = new System.ComponentModel.Container();
            this.fileContent = new System.Windows.Forms.TextBox();
            this.save = new System.Windows.Forms.Button();
            this.addedFile = new System.Windows.Forms.TextBox();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.file = new System.Windows.Forms.ToolStripMenuItem();
            this.open = new System.Windows.Forms.ToolStripMenuItem();
            this.saveMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.groupToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.oneToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.twoToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.edit = new System.Windows.Forms.ToolStripMenuItem();
            this.panel1 = new System.Windows.Forms.Panel();
            this.button5 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.myDockPanel1 = new ComponentsEvents.MyDockPanel(this.components);
            this.menuStrip1.SuspendLayout();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // fileContent
            // 
            this.fileContent.AcceptsReturn = true;
            this.fileContent.AcceptsTab = true;
            this.fileContent.AllowDrop = true;
            this.fileContent.Location = new System.Drawing.Point(24, 45);
            this.fileContent.MaxLength = 1073676289;
            this.fileContent.Multiline = true;
            this.fileContent.Name = "fileContent";
            this.fileContent.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.fileContent.Size = new System.Drawing.Size(288, 95);
            this.fileContent.TabIndex = 0;
            // 
            // save
            // 
            this.save.Location = new System.Drawing.Point(25, 318);
            this.save.Name = "save";
            this.save.Size = new System.Drawing.Size(75, 23);
            this.save.TabIndex = 1;
            this.save.Text = "set file";
            this.save.UseVisualStyleBackColor = true;
            this.save.MouseUp += new System.Windows.Forms.MouseEventHandler(this.saveFile);
            // 
            // addedFile
            // 
            this.addedFile.Location = new System.Drawing.Point(107, 318);
            this.addedFile.Name = "addedFile";
            this.addedFile.Size = new System.Drawing.Size(100, 20);
            this.addedFile.TabIndex = 2;
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.file,
            this.edit});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(339, 24);
            this.menuStrip1.TabIndex = 3;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // file
            // 
            this.file.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.open,
            this.saveMenu,
            this.groupToolStripMenuItem});
            this.file.Name = "file";
            this.file.Size = new System.Drawing.Size(35, 20);
            this.file.Text = "file";
            // 
            // open
            // 
            this.open.Name = "open";
            this.open.Size = new System.Drawing.Size(152, 22);
            this.open.Text = "open";
            this.open.MouseUp += new System.Windows.Forms.MouseEventHandler(this.selectMenu);
            // 
            // saveMenu
            // 
            this.saveMenu.Name = "saveMenu";
            this.saveMenu.Size = new System.Drawing.Size(152, 22);
            this.saveMenu.Text = "save";
            // 
            // groupToolStripMenuItem
            // 
            this.groupToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.oneToolStripMenuItem,
            this.twoToolStripMenuItem});
            this.groupToolStripMenuItem.Name = "groupToolStripMenuItem";
            this.groupToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.groupToolStripMenuItem.Text = "group";
            // 
            // oneToolStripMenuItem
            // 
            this.oneToolStripMenuItem.Name = "oneToolStripMenuItem";
            this.oneToolStripMenuItem.Size = new System.Drawing.Size(97, 22);
            this.oneToolStripMenuItem.Text = "One";
            // 
            // twoToolStripMenuItem
            // 
            this.twoToolStripMenuItem.Name = "twoToolStripMenuItem";
            this.twoToolStripMenuItem.Size = new System.Drawing.Size(97, 22);
            this.twoToolStripMenuItem.Text = "Two";
            // 
            // edit
            // 
            this.edit.Name = "edit";
            this.edit.Size = new System.Drawing.Size(39, 20);
            this.edit.Text = "edit";
            this.edit.MouseUp += new System.Windows.Forms.MouseEventHandler(this.seeMenuBis);
            // 
            // panel1
            // 
            this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel1.AutoScroll = true;
            this.panel1.AutoSize = true;
            this.panel1.Controls.Add(this.button5);
            this.panel1.Controls.Add(this.button4);
            this.panel1.Controls.Add(this.button3);
            this.panel1.Controls.Add(this.button2);
            this.panel1.Controls.Add(this.button1);
            this.panel1.Location = new System.Drawing.Point(24, 147);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(288, 106);
            this.panel1.TabIndex = 5;
            // 
            // button5
            // 
            this.button5.AutoSize = true;
            this.button5.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.button5.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.button5.Location = new System.Drawing.Point(53, 83);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(182, 23);
            this.button5.TabIndex = 4;
            this.button5.Text = "button5";
            this.button5.UseVisualStyleBackColor = true;
            // 
            // button4
            // 
            this.button4.AutoSize = true;
            this.button4.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.button4.Dock = System.Windows.Forms.DockStyle.Right;
            this.button4.Location = new System.Drawing.Point(235, 23);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(53, 83);
            this.button4.TabIndex = 3;
            this.button4.Text = "button4";
            this.button4.UseVisualStyleBackColor = true;
            // 
            // button3
            // 
            this.button3.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.button3.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.button3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.button3.Location = new System.Drawing.Point(53, 23);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(235, 83);
            this.button3.TabIndex = 2;
            this.button3.Text = "button3";
            this.button3.UseVisualStyleBackColor = true;
            // 
            // button2
            // 
            this.button2.AutoSize = true;
            this.button2.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.button2.Dock = System.Windows.Forms.DockStyle.Left;
            this.button2.Location = new System.Drawing.Point(0, 23);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(53, 83);
            this.button2.TabIndex = 1;
            this.button2.Text = "button2";
            this.button2.UseVisualStyleBackColor = true;
            // 
            // button1
            // 
            this.button1.AutoSize = true;
            this.button1.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.button1.Dock = System.Windows.Forms.DockStyle.Top;
            this.button1.Location = new System.Drawing.Point(0, 0);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(288, 23);
            this.button1.TabIndex = 0;
            this.button1.Text = "button1";
            this.button1.UseVisualStyleBackColor = true;
            // 
            // myDockPanel1
            // 
            this.myDockPanel1.Location = new System.Drawing.Point(24, 259);
            this.myDockPanel1.Name = "myDockPanel1";
            this.myDockPanel1.Size = new System.Drawing.Size(288, 53);
            this.myDockPanel1.TabIndex = 4;
            this.myDockPanel1.Text = "myDockPanel1";
            // 
            // SeeFile
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.ClientSize = new System.Drawing.Size(339, 350);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.myDockPanel1);
            this.Controls.Add(this.addedFile);
            this.Controls.Add(this.save);
            this.Controls.Add(this.fileContent);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "SeeFile";
            this.Text = "SeeFile";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox fileContent;
        private System.Windows.Forms.Button save;
        private System.Windows.Forms.TextBox addedFile;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem file;
        private System.Windows.Forms.ToolStripMenuItem open;
        private System.Windows.Forms.ToolStripMenuItem saveMenu;
        private System.Windows.Forms.ToolStripMenuItem edit;
        private System.Windows.Forms.ToolStripMenuItem groupToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem oneToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem twoToolStripMenuItem;
        private MyDockPanel myDockPanel1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button1;
    }
}