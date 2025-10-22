using System;
using System.IO;

namespace LabCS1
{
    class Program
    {
        static void Main(string[] args)
        {
            string tableName = "Company";
            string html = "<html>\n<style>\ntable, th, td {\nborder: 1px solid black;\n}\n</style>\n<body>\n\n<h2>"
                + tableName +
                "</h2>\n<table style=\"width: 100%\">\n<tr>";

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

            html += "</table>\n</body>\n</html>";

            File.WriteAllText("C:\\Users\\kp15319\\Desktop\\test.html", html);
        }
    }
}
