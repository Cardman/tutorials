namespace ComponentsEvents
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
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.seeFile = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.selectFile = new System.Windows.Forms.Button();
            this.helpButton = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.cities1 = new ComponentsEvents.Cities(this.components);
            this.selectedRadio = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.radioButton4 = new System.Windows.Forms.RadioButton();
            this.radioButton3 = new System.Windows.Forms.RadioButton();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.radioButton2 = new System.Windows.Forms.RadioButton();
            this.radioButton1 = new System.Windows.Forms.RadioButton();
            this.testComponents = new System.Windows.Forms.Button();
            this.tabs = new System.Windows.Forms.Button();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.addCity = new ComponentsEvents.PaintedButton();
            this.cityName = new System.Windows.Forms.TextBox();
            this.numericUpDown1 = new System.Windows.Forms.NumericUpDown();
            this.helpProvider1 = new System.Windows.Forms.HelpProvider();
            this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            this.imageList1 = new System.Windows.Forms.ImageList(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).BeginInit();
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
            this.splitContainer1.Panel1.Controls.Add(this.textBox1);
            this.splitContainer1.Panel1.Controls.Add(this.seeFile);
            this.splitContainer1.Panel1.Controls.Add(this.label2);
            this.splitContainer1.Panel1.Controls.Add(this.selectFile);
            this.splitContainer1.Panel1.Controls.Add(this.helpButton);
            this.splitContainer1.Panel1.Controls.Add(this.button1);
            this.splitContainer1.Panel1.Controls.Add(this.label1);
            this.splitContainer1.Panel1.Controls.Add(this.cities1);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.AutoScroll = true;
            this.splitContainer1.Panel2.Controls.Add(this.selectedRadio);
            this.splitContainer1.Panel2.Controls.Add(this.groupBox2);
            this.splitContainer1.Panel2.Controls.Add(this.groupBox1);
            this.splitContainer1.Panel2.Controls.Add(this.testComponents);
            this.splitContainer1.Panel2.Controls.Add(this.tabs);
            this.splitContainer1.Panel2.Controls.Add(this.checkBox1);
            this.splitContainer1.Panel2.Controls.Add(this.addCity);
            this.splitContainer1.Panel2.Controls.Add(this.cityName);
            this.splitContainer1.Panel2.Controls.Add(this.numericUpDown1);
            this.splitContainer1.Panel2.Paint += new System.Windows.Forms.PaintEventHandler(this.splitContainer1_Panel2_Paint);
            this.splitContainer1.Size = new System.Drawing.Size(412, 335);
            this.splitContainer1.SplitterDistance = 209;
            this.splitContainer1.TabIndex = 0;
            // 
            // textBox1
            // 
            this.textBox1.AutoCompleteMode = System.Windows.Forms.AutoCompleteMode.SuggestAppend;
            this.textBox1.AutoCompleteSource = System.Windows.Forms.AutoCompleteSource.CustomSource;
            this.textBox1.Location = new System.Drawing.Point(42, 188);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(100, 20);
            this.textBox1.TabIndex = 7;
            this.textBox1.TextChanged += new System.EventHandler(this.changedTxt);
            // 
            // seeFile
            // 
            this.seeFile.Location = new System.Drawing.Point(42, 142);
            this.seeFile.Name = "seeFile";
            this.seeFile.Size = new System.Drawing.Size(75, 23);
            this.seeFile.TabIndex = 6;
            this.seeFile.Text = "see file";
            this.seeFile.UseVisualStyleBackColor = true;
            this.seeFile.Click += new System.EventHandler(this.seeFile_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(39, 168);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(37, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "No file";
            // 
            // selectFile
            // 
            this.selectFile.Location = new System.Drawing.Point(42, 113);
            this.selectFile.Name = "selectFile";
            this.selectFile.Size = new System.Drawing.Size(75, 23);
            this.selectFile.TabIndex = 4;
            this.selectFile.Text = "files";
            this.selectFile.UseVisualStyleBackColor = true;
            this.selectFile.Click += new System.EventHandler(this.button2_Click);
            // 
            // helpButton
            // 
            this.helpButton.Location = new System.Drawing.Point(42, 84);
            this.helpButton.Name = "helpButton";
            this.helpButton.Size = new System.Drawing.Size(75, 23);
            this.helpButton.TabIndex = 3;
            this.helpButton.Text = "see help";
            this.helpButton.UseVisualStyleBackColor = true;
            this.helpButton.MouseUp += new System.Windows.Forms.MouseEventHandler(this.openHelp);
            // 
            // button1
            // 
            this.button1.Cursor = System.Windows.Forms.Cursors.Hand;
            this.button1.Location = new System.Drawing.Point(42, 55);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 2;
            this.button1.Text = "see sports";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.MouseClick += new System.Windows.Forms.MouseEventHandler(this.seeSports);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(39, 36);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(88, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "No data selected";
            // 
            // cities1
            // 
            this.cities1.FormattingEnabled = true;
            this.cities1.Location = new System.Drawing.Point(12, 12);
            this.cities1.Name = "cities1";
            this.cities1.Size = new System.Drawing.Size(121, 21);
            this.cities1.TabIndex = 0;
            this.cities1.SelectedIndexChanged += new System.EventHandler(this.changingState);
            // 
            // selectedRadio
            // 
            this.selectedRadio.AutoSize = true;
            this.selectedRadio.Location = new System.Drawing.Point(93, 283);
            this.selectedRadio.Name = "selectedRadio";
            this.selectedRadio.Size = new System.Drawing.Size(90, 13);
            this.selectedRadio.TabIndex = 10;
            this.selectedRadio.Text = "No selected radio";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.radioButton4);
            this.groupBox2.Controls.Add(this.radioButton3);
            this.groupBox2.Location = new System.Drawing.Point(12, 114);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(173, 67);
            this.groupBox2.TabIndex = 9;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "PPDA";
            // 
            // radioButton4
            // 
            this.radioButton4.AutoSize = true;
            this.radioButton4.Location = new System.Drawing.Point(18, 42);
            this.radioButton4.Name = "radioButton4";
            this.radioButton4.Size = new System.Drawing.Size(88, 17);
            this.radioButton4.TabIndex = 8;
            this.radioButton4.TabStop = true;
            this.radioButton4.Text = "France Bleue";
            this.radioButton4.UseVisualStyleBackColor = true;
            this.radioButton4.CheckedChanged += new System.EventHandler(this.commonOne);
            this.radioButton4.MouseUp += new System.Windows.Forms.MouseEventHandler(this.water);
            // 
            // radioButton3
            // 
            this.radioButton3.AutoSize = true;
            this.radioButton3.Location = new System.Drawing.Point(18, 19);
            this.radioButton3.Name = "radioButton3";
            this.radioButton3.Size = new System.Drawing.Size(49, 17);
            this.radioButton3.TabIndex = 7;
            this.radioButton3.TabStop = true;
            this.radioButton3.Text = "RMC";
            this.radioButton3.UseVisualStyleBackColor = true;
            this.radioButton3.CheckedChanged += new System.EventHandler(this.commonOne);
            this.radioButton3.MouseUp += new System.Windows.Forms.MouseEventHandler(this.rock);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.radioButton2);
            this.groupBox1.Controls.Add(this.radioButton1);
            this.groupBox1.Location = new System.Drawing.Point(12, 188);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(173, 60);
            this.groupBox1.TabIndex = 8;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Fogiel";
            // 
            // radioButton2
            // 
            this.radioButton2.AutoSize = true;
            this.radioButton2.Location = new System.Drawing.Point(18, 37);
            this.radioButton2.Name = "radioButton2";
            this.radioButton2.Size = new System.Drawing.Size(46, 17);
            this.radioButton2.TabIndex = 5;
            this.radioButton2.TabStop = true;
            this.radioButton2.Text = "RTL";
            this.radioButton2.UseVisualStyleBackColor = true;
            this.radioButton2.CheckedChanged += new System.EventHandler(this.commonTwo);
            this.radioButton2.Enter += new System.EventHandler(this.flyBis);
            // 
            // radioButton1
            // 
            this.radioButton1.AutoSize = true;
            this.radioButton1.Location = new System.Drawing.Point(18, 14);
            this.radioButton1.Name = "radioButton1";
            this.radioButton1.Size = new System.Drawing.Size(68, 17);
            this.radioButton1.TabIndex = 4;
            this.radioButton1.TabStop = true;
            this.radioButton1.Text = "Europe 1";
            this.radioButton1.UseVisualStyleBackColor = true;
            this.radioButton1.CheckedChanged += new System.EventHandler(this.commonTwo);
            this.radioButton1.Enter += new System.EventHandler(this.fly);
            // 
            // testComponents
            // 
            this.testComponents.Location = new System.Drawing.Point(12, 283);
            this.testComponents.Name = "testComponents";
            this.testComponents.Size = new System.Drawing.Size(75, 23);
            this.testComponents.TabIndex = 7;
            this.testComponents.Text = "tests";
            this.testComponents.UseVisualStyleBackColor = true;
            this.testComponents.Click += new System.EventHandler(this.testComponents_Click);
            // 
            // tabs
            // 
            this.tabs.Location = new System.Drawing.Point(12, 254);
            this.tabs.Name = "tabs";
            this.tabs.Size = new System.Drawing.Size(75, 23);
            this.tabs.TabIndex = 6;
            this.tabs.Text = "tabs";
            this.tabs.UseVisualStyleBackColor = true;
            this.tabs.MouseUp += new System.Windows.Forms.MouseEventHandler(this.seeTabs);
            // 
            // checkBox1
            // 
            this.checkBox1.AutoSize = true;
            this.checkBox1.Location = new System.Drawing.Point(12, 90);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(64, 17);
            this.checkBox1.TabIndex = 3;
            this.checkBox1.Text = "Validate";
            this.checkBox1.UseVisualStyleBackColor = true;
            this.checkBox1.CheckedChanged += new System.EventHandler(this.validateData);
            // 
            // addCity
            // 
            this.addCity.Cursor = System.Windows.Forms.Cursors.Hand;
            this.addCity.Location = new System.Drawing.Point(12, 64);
            this.addCity.Name = "addCity";
            this.addCity.Size = new System.Drawing.Size(75, 23);
            this.addCity.TabIndex = 2;
            this.addCity.Text = "add city";
            this.addCity.UseVisualStyleBackColor = true;
            this.addCity.MouseDown += new System.Windows.Forms.MouseEventHandler(this.clickBegin);
            this.addCity.MouseUp += new System.Windows.Forms.MouseEventHandler(this.addingCity);
            // 
            // cityName
            // 
            this.cityName.Location = new System.Drawing.Point(12, 38);
            this.cityName.Name = "cityName";
            this.cityName.Size = new System.Drawing.Size(100, 20);
            this.cityName.TabIndex = 1;
            this.cityName.TextChanged += new System.EventHandler(this.typedString);
            // 
            // numericUpDown1
            // 
            this.numericUpDown1.Location = new System.Drawing.Point(12, 12);
            this.numericUpDown1.Name = "numericUpDown1";
            this.numericUpDown1.Size = new System.Drawing.Size(120, 20);
            this.numericUpDown1.TabIndex = 0;
            this.numericUpDown1.ValueChanged += new System.EventHandler(this.testSelectedValue);
            // 
            // imageList1
            // 
            this.imageList1.ColorDepth = System.Windows.Forms.ColorDepth.Depth8Bit;
            this.imageList1.ImageSize = new System.Drawing.Size(16, 16);
            this.imageList1.TransparentColor = System.Drawing.Color.Transparent;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(412, 335);
            this.Controls.Add(this.splitContainer1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel1.PerformLayout();
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.Panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.HelpProvider helpProvider1;
        private System.ComponentModel.BackgroundWorker backgroundWorker1;
        private Cities cities1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.NumericUpDown numericUpDown1;
        private System.Windows.Forms.TextBox cityName;
        private PaintedButton addCity;
        private System.Windows.Forms.RadioButton radioButton1;
        private System.Windows.Forms.CheckBox checkBox1;
        private System.Windows.Forms.RadioButton radioButton2;
        private System.Windows.Forms.Button helpButton;
        private System.Windows.Forms.Button selectFile;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button seeFile;
        private System.Windows.Forms.Button tabs;
        private System.Windows.Forms.Button testComponents;
        private System.Windows.Forms.RadioButton radioButton3;
        private System.Windows.Forms.RadioButton radioButton4;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label selectedRadio;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.ImageList imageList1;
        //private System.Windows.Forms.SplitContainer splitContainer2;
    }
}

