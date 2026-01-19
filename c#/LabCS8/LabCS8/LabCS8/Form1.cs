using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LabCS8
{
    public partial class Form1 : Form
    {
        private List<Osoba> listaOsob = new List<Osoba>();

        public Form1()
        {
            InitializeComponent();
        }

        private void AktualizujListBox()
        {
            lstRekordy.DataSource = null;
            lstRekordy.DataSource = listaOsob;
        }

        private void WyczyscPola()
        {
            txtImie.Clear();
            txtNazwisko.Clear();
            dtpDataUrodzenia.Value = DateTime.Today;
            rbKobieta.Checked = false;
            rbMezczyzna.Checked = false;
        }


        private void btnDodaj_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(txtImie.Text) ||
                string.IsNullOrWhiteSpace(txtNazwisko.Text) ||
                (!rbKobieta.Checked && !rbMezczyzna.Checked))
            {
                MessageBox.Show("Wszystkie pola są wymagane!");
                return;
            }

            string plec = rbKobieta.Checked ? "Kobieta" : "Mężczyzna";

            Osoba nowaOsoba = new Osoba()
            {
                Imie = txtImie.Text,
                Nazwisko = txtNazwisko.Text,
                DataUrodzenia = dtpDataUrodzenia.Value,
                Plec = plec
            };

            listaOsob.Add(nowaOsoba);

            AktualizujListBox();

            WyczyscPola();
        }

        private void lstRekordy_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (lstRekordy.SelectedItem is Osoba wybranaOsoba)
            {
                txtImie.Text = wybranaOsoba.Imie;
                txtNazwisko.Text = wybranaOsoba.Nazwisko;
                dtpDataUrodzenia.Value = wybranaOsoba.DataUrodzenia;
                rbKobieta.Checked = wybranaOsoba.Plec == "Kobieta";
                rbMezczyzna.Checked = wybranaOsoba.Plec == "Mężczyzna";
            }
        }

        private void btnUsun_Click(object sender, EventArgs e)
        {
            if (lstRekordy.SelectedItem is Osoba wybranaOsoba)
            {
                listaOsob.Remove(wybranaOsoba);
                AktualizujListBox();
                WyczyscPola();
            }
        }

        private void btnAktualizuj_Click(object sender, EventArgs e)
        {
            if (lstRekordy.SelectedItem is Osoba wybranaOsoba)
            {
                if (string.IsNullOrWhiteSpace(txtImie.Text) ||
                    string.IsNullOrWhiteSpace(txtNazwisko.Text) ||
                    (!rbKobieta.Checked && !rbMezczyzna.Checked))
                {
                    MessageBox.Show("Wszystkie pola są wymagane!");
                    return;
                }

                wybranaOsoba.Imie = txtImie.Text;
                wybranaOsoba.Nazwisko = txtNazwisko.Text;
                wybranaOsoba.DataUrodzenia = dtpDataUrodzenia.Value;
                wybranaOsoba.Plec = rbKobieta.Checked ? "Kobieta" : "Mężczyzna";

                AktualizujListBox();
                WyczyscPola();
            }
        }
    }
}
