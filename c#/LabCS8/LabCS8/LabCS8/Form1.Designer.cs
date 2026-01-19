
namespace LabCS8
{
    partial class Form1
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
            this.label1 = new System.Windows.Forms.Label();
            this.txtImie = new System.Windows.Forms.TextBox();
            this.txtNazwisko = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.dtpDataUrodzenia = new System.Windows.Forms.DateTimePicker();
            this.label4 = new System.Windows.Forms.Label();
            this.rbKobieta = new System.Windows.Forms.RadioButton();
            this.rbMezczyzna = new System.Windows.Forms.RadioButton();
            this.btnDodaj = new System.Windows.Forms.Button();
            this.btnUsun = new System.Windows.Forms.Button();
            this.btnAktualizuj = new System.Windows.Forms.Button();
            this.lstRekordy = new System.Windows.Forms.ListBox();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(46, 64);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(26, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Imie";
            // 
            // txtImie
            // 
            this.txtImie.Location = new System.Drawing.Point(49, 80);
            this.txtImie.Name = "txtImie";
            this.txtImie.Size = new System.Drawing.Size(100, 20);
            this.txtImie.TabIndex = 1;
            // 
            // txtNazwisko
            // 
            this.txtNazwisko.Location = new System.Drawing.Point(183, 80);
            this.txtNazwisko.Name = "txtNazwisko";
            this.txtNazwisko.Size = new System.Drawing.Size(100, 20);
            this.txtNazwisko.TabIndex = 3;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(180, 64);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(53, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Nazwisko";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(312, 62);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(79, 13);
            this.label3.TabIndex = 4;
            this.label3.Text = "Data urodzenia";
            // 
            // dtpDataUrodzenia
            // 
            this.dtpDataUrodzenia.Location = new System.Drawing.Point(315, 80);
            this.dtpDataUrodzenia.Name = "dtpDataUrodzenia";
            this.dtpDataUrodzenia.Size = new System.Drawing.Size(200, 20);
            this.dtpDataUrodzenia.TabIndex = 5;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(545, 62);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(28, 13);
            this.label4.TabIndex = 6;
            this.label4.Text = "Plec";
            // 
            // rbKobieta
            // 
            this.rbKobieta.AutoSize = true;
            this.rbKobieta.Location = new System.Drawing.Point(548, 77);
            this.rbKobieta.Name = "rbKobieta";
            this.rbKobieta.Size = new System.Drawing.Size(61, 17);
            this.rbKobieta.TabIndex = 7;
            this.rbKobieta.TabStop = true;
            this.rbKobieta.Text = "Kobieta";
            this.rbKobieta.UseVisualStyleBackColor = true;
            // 
            // rbMezczyzna
            // 
            this.rbMezczyzna.AutoSize = true;
            this.rbMezczyzna.Location = new System.Drawing.Point(548, 100);
            this.rbMezczyzna.Name = "rbMezczyzna";
            this.rbMezczyzna.Size = new System.Drawing.Size(78, 17);
            this.rbMezczyzna.TabIndex = 8;
            this.rbMezczyzna.TabStop = true;
            this.rbMezczyzna.Text = "Mezczyzna";
            this.rbMezczyzna.UseVisualStyleBackColor = true;
            // 
            // btnDodaj
            // 
            this.btnDodaj.Location = new System.Drawing.Point(49, 142);
            this.btnDodaj.Name = "btnDodaj";
            this.btnDodaj.Size = new System.Drawing.Size(75, 23);
            this.btnDodaj.TabIndex = 9;
            this.btnDodaj.Text = "Dodaj";
            this.btnDodaj.UseVisualStyleBackColor = true;
            this.btnDodaj.Click += new System.EventHandler(this.btnDodaj_Click);
            // 
            // btnUsun
            // 
            this.btnUsun.Location = new System.Drawing.Point(130, 142);
            this.btnUsun.Name = "btnUsun";
            this.btnUsun.Size = new System.Drawing.Size(75, 23);
            this.btnUsun.TabIndex = 10;
            this.btnUsun.Text = "Usun";
            this.btnUsun.UseVisualStyleBackColor = true;
            this.btnUsun.Click += new System.EventHandler(this.btnUsun_Click);
            // 
            // btnAktualizuj
            // 
            this.btnAktualizuj.Location = new System.Drawing.Point(211, 142);
            this.btnAktualizuj.Name = "btnAktualizuj";
            this.btnAktualizuj.Size = new System.Drawing.Size(75, 23);
            this.btnAktualizuj.TabIndex = 11;
            this.btnAktualizuj.Text = "Aktualizuj";
            this.btnAktualizuj.UseVisualStyleBackColor = true;
            this.btnAktualizuj.Click += new System.EventHandler(this.btnAktualizuj_Click);
            // 
            // lstRekordy
            // 
            this.lstRekordy.FormattingEnabled = true;
            this.lstRekordy.Location = new System.Drawing.Point(49, 198);
            this.lstRekordy.Name = "lstRekordy";
            this.lstRekordy.Size = new System.Drawing.Size(621, 212);
            this.lstRekordy.TabIndex = 12;
            this.lstRekordy.Click += new System.EventHandler(this.lstRekordy_SelectedIndexChanged);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(725, 450);
            this.Controls.Add(this.lstRekordy);
            this.Controls.Add(this.btnAktualizuj);
            this.Controls.Add(this.btnUsun);
            this.Controls.Add(this.btnDodaj);
            this.Controls.Add(this.rbMezczyzna);
            this.Controls.Add(this.rbKobieta);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.dtpDataUrodzenia);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.txtNazwisko);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.txtImie);
            this.Controls.Add(this.label1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtImie;
        private System.Windows.Forms.TextBox txtNazwisko;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.DateTimePicker dtpDataUrodzenia;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.RadioButton rbKobieta;
        private System.Windows.Forms.RadioButton rbMezczyzna;
        private System.Windows.Forms.Button btnDodaj;
        private System.Windows.Forms.Button btnUsun;
        private System.Windows.Forms.Button btnAktualizuj;
        private System.Windows.Forms.ListBox lstRekordy;
    }
}

