namespace ComponentsEvents
{
    partial class DialogSports
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

        #region Code généré par le Concepteur de composants

        /// <summary>
        /// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
        /// le contenu de cette méthode avec l'éditeur de code.
        /// </summary>
        private void InitializeComponent()
        {
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.nbSports = new System.Windows.Forms.Label();
            this.clearSelection = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // listBox1
            // 
            this.listBox1.DrawMode = System.Windows.Forms.DrawMode.OwnerDrawFixed;
            this.listBox1.FormattingEnabled = true;
            this.listBox1.Location = new System.Drawing.Point(70, 56);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(120, 95);
            this.listBox1.TabIndex = 0;
            this.listBox1.SelectedValueChanged += new System.EventHandler(this.selectSport);
            // 
            // nbSports
            // 
            this.nbSports.AutoSize = true;
            this.nbSports.Location = new System.Drawing.Point(70, 173);
            this.nbSports.Name = "nbSports";
            this.nbSports.Size = new System.Drawing.Size(16, 13);
            this.nbSports.TabIndex = 1;
            this.nbSports.Text = "-1";
            // 
            // clearSelection
            // 
            this.clearSelection.Location = new System.Drawing.Point(70, 200);
            this.clearSelection.Name = "clearSelection";
            this.clearSelection.Size = new System.Drawing.Size(120, 23);
            this.clearSelection.TabIndex = 2;
            this.clearSelection.Text = "Clear selection";
            this.clearSelection.UseVisualStyleBackColor = true;
            this.clearSelection.MouseUp += new System.Windows.Forms.MouseEventHandler(this.clearSportsSelection);
            // 
            // DialogSports
            // 
            this.ClientSize = new System.Drawing.Size(284, 262);
            this.Controls.Add(this.clearSelection);
            this.Controls.Add(this.nbSports);
            this.Controls.Add(this.listBox1);
            this.Name = "DialogSports";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox listBox1;
        private System.Windows.Forms.Label nbSports;
        private System.Windows.Forms.Button clearSelection;
    }
}
