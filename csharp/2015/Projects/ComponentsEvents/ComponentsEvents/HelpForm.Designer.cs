namespace ComponentsEvents
{
    partial class HelpForm
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
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.treeHelp = new System.Windows.Forms.TreeView();
            this.panel1 = new System.Windows.Forms.Panel();
            this.pathTwo = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // splitContainer1
            // 
            this.splitContainer1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.AutoScroll = true;
            this.splitContainer1.Panel1.Controls.Add(this.treeHelp);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.AutoScroll = true;
            this.splitContainer1.Size = new System.Drawing.Size(373, 290);
            this.splitContainer1.SplitterDistance = 223;
            this.splitContainer1.TabIndex = 0;
            // 
            // treeHelp
            // 
            this.treeHelp.Location = new System.Drawing.Point(3, 0);
            this.treeHelp.Name = "treeHelp";
            this.treeHelp.PathSeparator = "/";
            this.treeHelp.Size = new System.Drawing.Size(219, 285);
            this.treeHelp.TabIndex = 0;
            this.treeHelp.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.seeNode);
            // 
            // panel1
            // 
            this.panel1.AutoSize = true;
            this.panel1.Controls.Add(this.splitContainer1);
            this.panel1.Location = new System.Drawing.Point(3, 6);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(373, 290);
            this.panel1.TabIndex = 1;
            // 
            // pathTwo
            // 
            this.pathTwo.AutoSize = true;
            this.pathTwo.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.pathTwo.Location = new System.Drawing.Point(0, 315);
            this.pathTwo.Name = "pathTwo";
            this.pathTwo.Size = new System.Drawing.Size(66, 13);
            this.pathTwo.TabIndex = 1;
            this.pathTwo.Text = "Rebelle Leia";
            // 
            // HelpForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.AutoSize = true;
            this.ClientSize = new System.Drawing.Size(388, 328);
            this.Controls.Add(this.pathTwo);
            this.Controls.Add(this.panel1);
            this.Name = "HelpForm";
            this.Text = "Forme";
            this.splitContainer1.Panel1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.panel1.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.TreeView treeHelp;
        //private System.Windows.Forms.Label path;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label pathTwo;
    }
}