namespace HelloWorld
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
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.domicile = new System.Windows.Forms.Label();
            this.exterieur = new System.Windows.Forms.Label();
            this.ptsLocal = new System.Windows.Forms.NumericUpDown();
            this.ptsVisiteurs = new System.Windows.Forms.NumericUpDown();
            this.button1 = new System.Windows.Forms.Button();
            this.resultat = new System.Windows.Forms.Label();
            this.nbInstanciations = new System.Windows.Forms.Label();
            this.tableLayoutPanel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ptsLocal)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ptsVisiteurs)).BeginInit();
            this.SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.Controls.Add(this.domicile, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.exterieur, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.ptsLocal, 1, 0);
            this.tableLayoutPanel1.Controls.Add(this.ptsVisiteurs, 1, 1);
            this.tableLayoutPanel1.Controls.Add(this.button1, 0, 2);
            this.tableLayoutPanel1.Controls.Add(this.resultat, 0, 3);
            this.tableLayoutPanel1.Controls.Add(this.nbInstanciations, 0, 4);
            this.tableLayoutPanel1.Location = new System.Drawing.Point(12, 12);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 5;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 26F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 72F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 81F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(260, 224);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // domicile
            // 
            this.domicile.AutoSize = true;
            this.domicile.Location = new System.Drawing.Point(3, 0);
            this.domicile.Name = "domicile";
            this.domicile.Size = new System.Drawing.Size(47, 13);
            this.domicile.TabIndex = 0;
            this.domicile.Text = "Domicile";
            // 
            // exterieur
            // 
            this.exterieur.AutoSize = true;
            this.exterieur.Location = new System.Drawing.Point(3, 22);
            this.exterieur.Name = "exterieur";
            this.exterieur.Size = new System.Drawing.Size(48, 13);
            this.exterieur.TabIndex = 1;
            this.exterieur.Text = "Exterieur";
            // 
            // ptsLocal
            // 
            this.ptsLocal.Location = new System.Drawing.Point(133, 3);
            this.ptsLocal.Name = "ptsLocal";
            this.ptsLocal.Size = new System.Drawing.Size(120, 20);
            this.ptsLocal.TabIndex = 2;
            // 
            // ptsVisiteurs
            // 
            this.ptsVisiteurs.Location = new System.Drawing.Point(133, 25);
            this.ptsVisiteurs.Name = "ptsVisiteurs";
            this.ptsVisiteurs.Size = new System.Drawing.Size(120, 20);
            this.ptsVisiteurs.TabIndex = 3;
            // 
            // button1
            // 
            this.tableLayoutPanel1.SetColumnSpan(this.button1, 2);
            this.button1.Location = new System.Drawing.Point(3, 47);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(250, 20);
            this.button1.TabIndex = 4;
            this.button1.Text = "Afficher score";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.afficherScore);
            // 
            // resultat
            // 
            this.resultat.AutoSize = true;
            this.resultat.Location = new System.Drawing.Point(3, 70);
            this.resultat.Name = "resultat";
            this.resultat.Size = new System.Drawing.Size(35, 13);
            this.resultat.TabIndex = 5;
            this.resultat.Text = "label1";
            // 
            // nbInstanciations
            // 
            this.nbInstanciations.AutoSize = true;
            this.nbInstanciations.Location = new System.Drawing.Point(3, 142);
            this.nbInstanciations.Name = "nbInstanciations";
            this.nbInstanciations.Size = new System.Drawing.Size(35, 13);
            this.nbInstanciations.TabIndex = 6;
            this.nbInstanciations.Text = "label1";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 261);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ptsLocal)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ptsVisiteurs)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.Label domicile;
        private System.Windows.Forms.Label exterieur;
        private System.Windows.Forms.NumericUpDown ptsLocal;
        private System.Windows.Forms.NumericUpDown ptsVisiteurs;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label resultat;
        private System.Windows.Forms.Label nbInstanciations;
    }
}

