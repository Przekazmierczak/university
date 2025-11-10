using System;
using System.IO;

namespace LabCS1
{
    class Program
    {
        static void Main(string[] args)
        {
            string tableName = "Company";
            string html = "<html>\n";
            html += "<style>\n";
            html += "table, th, td {\n";
            html += "border: 1px solid black;\n";
            html += "}\n";
            html += "</style>\n";
            html += "<body>\n";
            html += "<h2>" + tableName + "</h2>\n";
            html += "<table style=\"width: 100%\">\n";

            html += "<tr>";

            var lines = File.ReadAllLines("C:\\Users\\kp15319\\Desktop\\uk.csv");
            var headerCols = lines[0].Split(",");
            foreach (var header in headerCols)
            {
                html += "<th>" + header + "</th>";
            }

            html += "</tr>\n";

            for (int i = 1; i < lines.Length; i++)
            {
                html += "<tr>";
                var cols = lines[i].Split(",");
                foreach (var col in cols)
                {
                    html += "<td>" + col + "</td>";
                }
                html += "</tr>\n";
            }

            html += "</table>\n";
            html += "</body>\n";
            html += "</html>";

            File.WriteAllText("C:\\Users\\kp15319\\Desktop\\test.html", html);
        }
    }
}
