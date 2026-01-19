using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LabCS7
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void txtDisplay_TextChanged(object sender, EventArgs e)
        {

        }

        private void btnNumber_Click(object sender, EventArgs e)
        {
            Button btn = sender as Button;

            if (btn.Text == ",")
            {
                if (!txtDisplay.Text.Contains(","))
                    txtDisplay.Text += ",";
            }
            else
            {
                if (txtDisplay.Text == "0")
                    txtDisplay.Text = btn.Text;
                else
                    txtDisplay.Text += btn.Text;
            }
        }

        string operation = "";
        double firstNumber = 0;

        private void btnOperator_Click(object sender, EventArgs e)
        {
            Button btn = sender as Button;

            switch (btn.Text)
            {
                case "+":
                case "-":
                case "*":
                case "/":
                    firstNumber = double.Parse(txtDisplay.Text);
                    operation = btn.Text;
                    txtDisplay.Text = "0";
                    break;

                case "=":
                    double secondNumber = double.Parse(txtDisplay.Text);
                    double result = 0;
                    switch (operation)
                    {
                        case "+": result = firstNumber + secondNumber; break;
                        case "-": result = firstNumber - secondNumber; break;
                        case "*": result = firstNumber * secondNumber; break;
                        case "/": result = firstNumber / secondNumber; break;
                    }
                    txtDisplay.Text = result.ToString();
                    break;

                case "C":
                    txtDisplay.Text = "0";
                    firstNumber = 0;
                    operation = "";
                    break;

                case "CE":
                    txtDisplay.Text = "0";
                    break;

                case "<-":
                    if (txtDisplay.Text.Length > 1)
                        txtDisplay.Text = txtDisplay.Text.Substring(0, txtDisplay.Text.Length - 1);
                    else
                        txtDisplay.Text = "0";
                    break;
            }

        }

        private void btnAdvanced_Click(object sender, EventArgs e)
        {
            Button btn = sender as Button;
            double number;

            if (!double.TryParse(txtDisplay.Text, out number))
                return;

            switch (btn.Text)
            {
                case "+/-":
                    number = -number;
                    txtDisplay.Text = number.ToString();
                    break;

                case "%":
                    number = number / 100;
                    txtDisplay.Text = number.ToString();
                    break;

                case "1/x":
                    if (number != 0)
                        txtDisplay.Text = (1 / number).ToString();
                    else
                        txtDisplay.Text = "Nie dziel przez 0";
                    break;

                case "x²":
                    txtDisplay.Text = (number * number).ToString();
                    break;

                case "√x":
                    if (number >= 0)
                        txtDisplay.Text = Math.Sqrt(number).ToString();
                    else
                        txtDisplay.Text = "Błąd";
                    break;
            }
        }
    }
}
