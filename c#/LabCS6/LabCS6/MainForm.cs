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

namespace LabCS6
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void btnBrowseInput_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                txtInput.Text = openFileDialog1.FileName;

                txtOutput.Text = Path.ChangeExtension(
                    openFileDialog1.FileName,
                    ".html"
                );
            }
        }

        private void btnBrowseOutput_Click(object sender, EventArgs e)
        {
            saveFileDialog1.FileName = Path.GetFileName(txtOutput.Text);
            saveFileDialog1.InitialDirectory = Path.GetDirectoryName(txtOutput.Text);

            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                txtOutput.Text = saveFileDialog1.FileName;
            }
        }

        private void btnConvert_Click(object sender, EventArgs e)
        {
            if (!File.Exists(txtInput.Text))
            {
                MessageBox.Show("Nie wybrano poprawnego pliku CSV");
                return;
            }

            ConvertCsvToHtml(txtInput.Text, txtOutput.Text);

            MessageBox.Show("Konwersja zakończona");
        }

        static void ConvertCsvToHtml(string inputFile, string outputFile)
        {
            using (FileStream fs = new FileStream(outputFile, FileMode.Create, FileAccess.Write))
            {
            }

            using (StreamWriter writer = new StreamWriter(outputFile, true))
            {

                string tableName = "Company";
                string html = "";

                bool firstLine = true;

                writer.WriteLine("<html>");
                Header(writer);
                writer.WriteLine("<body>");
                Table(writer, tableName);

                using (StreamReader reader = new StreamReader(inputFile))
                {
                    string line;
                    while ((line = reader.ReadLine()) != null)
                    {
                        if (firstLine == true)
                        {
                            TableHeader(writer, line);
                            firstLine = false;
                        }
                        else
                        {
                            TableData(writer, line);
                        }
                    }
                }

                writer.WriteLine("</table>");
                writer.WriteLine("</body>");
                Footer(html);
                writer.WriteLine("</html>");
            }
        }

        static void Header(StreamWriter writer)
        {
            writer.WriteLine("<style>");
            writer.WriteLine("table, th, td {");
            writer.WriteLine("border: 1px solid black;");
            writer.WriteLine("}");
            writer.WriteLine("</style>");
        }

        static void Table(StreamWriter writer, string tableName)
        {
            writer.WriteLine("<h2>" + tableName + "</h2>");
            writer.WriteLine("<table style=\"width: 100%\">");
        }

        static void TableHeader(StreamWriter writer, string line)
        {
            writer.WriteLine("<tr>");

            var headerCols = line.Split(",");
            foreach (var header in headerCols)
            {
                writer.WriteLine("<th>" + header + "</th>");
            }

            writer.WriteLine("</tr>");
        }

        static void TableData(StreamWriter writer, string lines)
        {
            writer.WriteLine("<tr>");
            var cols = lines.Split(",");
            foreach (var col in cols)
            {
                writer.WriteLine("<td>" + col + "</td>");
            }
            writer.WriteLine("</tr>");
        }

        static void Footer(string html)
        {

        }
    }
}
