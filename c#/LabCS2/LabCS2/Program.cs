using System;
using System.IO;

namespace LabCS2
{
    class Program
    {
        static void Main(string[] args)
        {
            string inputFile = args[0];

            string outputFile = "C:\\Users\\kp15319\\Desktop\\web.html";

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
