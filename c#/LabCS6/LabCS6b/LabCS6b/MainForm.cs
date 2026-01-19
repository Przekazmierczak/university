using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LabCS6b
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }

        private void btnBrowseSource_Click(object sender, EventArgs e)
        {
            if (folderBrowserDialog1.ShowDialog() == DialogResult.OK)
            {
                txtSource.Text = folderBrowserDialog1.SelectedPath;
            }
        }

        private void btnBrowseTarget_Click(object sender, EventArgs e)
        {
            if (folderBrowserDialog1.ShowDialog() == DialogResult.OK)
            {
                txtTarget.Text = folderBrowserDialog1.SelectedPath;
            }
        }

        private void btnCopy_Click(object sender, EventArgs e)
        {
            string sourceDir = txtSource.Text;
            string targetDir = txtTarget.Text;

            if (!Directory.Exists(sourceDir))
            {
                MessageBox.Show("Nieprawidłowy folder źródłowy");
                return;
            }

            if (!Directory.Exists(targetDir))
            {
                Directory.CreateDirectory(targetDir);
            }

            CopyJpgFilesRecursive(sourceDir, targetDir);

            MessageBox.Show("Kopiowanie zakończone");
        }

        private void CopyJpgFilesRecursive(string sourceDir, string targetDir)
        {
            foreach (string file in Directory.GetFiles(sourceDir, "*.jpg"))
            {
                DateTime creationTime = File.GetCreationTime(file);
                string folderName = new DirectoryInfo(sourceDir).Name;
                string fileName = Path.GetFileName(file);

                string newFileName = $"{creationTime:yyyyMMddHHmmss}_{folderName}_{fileName}";
                string targetPath = Path.Combine(targetDir, newFileName);

                File.Copy(file, targetPath);
            }

            foreach (string dir in Directory.GetDirectories(sourceDir))
            {
                CopyJpgFilesRecursive(dir, targetDir);
            }
        }
    }
}
