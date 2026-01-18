
namespace LabCS6b
{
    partial class MainForm
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.txtSource = new System.Windows.Forms.TextBox();
            this.btnBrowseSource = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.txtTarget = new System.Windows.Forms.TextBox();
            this.btnBrowseTarget = new System.Windows.Forms.Button();
            this.btnCopy = new System.Windows.Forms.Button();
            this.folderBrowserDialog1 = new System.Windows.Forms.FolderBrowserDialog();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(147, 76);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(42, 15);
            this.label1.TabIndex = 0;
            this.label1.Text = "Zrodlo";
            // 
            // txtSource
            // 
            this.txtSource.Location = new System.Drawing.Point(127, 112);
            this.txtSource.Name = "txtSource";
            this.txtSource.Size = new System.Drawing.Size(100, 23);
            this.txtSource.TabIndex = 1;
            // 
            // btnBrowseSource
            // 
            this.btnBrowseSource.Location = new System.Drawing.Point(137, 152);
            this.btnBrowseSource.Name = "btnBrowseSource";
            this.btnBrowseSource.Size = new System.Drawing.Size(75, 23);
            this.btnBrowseSource.TabIndex = 2;
            this.btnBrowseSource.Text = "...";
            this.btnBrowseSource.UseVisualStyleBackColor = true;
            this.btnBrowseSource.Click += new System.EventHandler(this.btnBrowseSource_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(457, 76);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(96, 15);
            this.label2.TabIndex = 3;
            this.label2.Text = "Folder wynikowy";
            // 
            // txtTarget
            // 
            this.txtTarget.Location = new System.Drawing.Point(453, 112);
            this.txtTarget.Name = "txtTarget";
            this.txtTarget.Size = new System.Drawing.Size(100, 23);
            this.txtTarget.TabIndex = 4;
            // 
            // btnBrowseTarget
            // 
            this.btnBrowseTarget.Location = new System.Drawing.Point(468, 152);
            this.btnBrowseTarget.Name = "btnBrowseTarget";
            this.btnBrowseTarget.Size = new System.Drawing.Size(75, 23);
            this.btnBrowseTarget.TabIndex = 5;
            this.btnBrowseTarget.Text = "...";
            this.btnBrowseTarget.UseVisualStyleBackColor = true;
            this.btnBrowseTarget.Click += new System.EventHandler(this.btnBrowseTarget_Click);
            // 
            // btnCopy
            // 
            this.btnCopy.Location = new System.Drawing.Point(308, 255);
            this.btnCopy.Name = "btnCopy";
            this.btnCopy.Size = new System.Drawing.Size(95, 23);
            this.btnCopy.TabIndex = 6;
            this.btnCopy.Text = "Kopiuj zdjęcia";
            this.btnCopy.UseVisualStyleBackColor = true;
            this.btnCopy.Click += new System.EventHandler(this.btnCopy_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.btnCopy);
            this.Controls.Add(this.btnBrowseTarget);
            this.Controls.Add(this.txtTarget);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.btnBrowseSource);
            this.Controls.Add(this.txtSource);
            this.Controls.Add(this.label1);
            this.Name = "MainForm";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtSource;
        private System.Windows.Forms.Button btnBrowseSource;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txtTarget;
        private System.Windows.Forms.Button btnBrowseTarget;
        private System.Windows.Forms.Button btnCopy;
        private System.Windows.Forms.FolderBrowserDialog folderBrowserDialog1;
    }
}

