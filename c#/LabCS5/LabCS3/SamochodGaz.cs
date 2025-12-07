using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ObjectConsoleApp.Samochody
{
    public class SamochodGaz : ISamochod, ISamochodGaz
    {
        public bool SilnikSpalinowy { get; private set; }
        public bool Butla { get; private set; }

        public void Tankuj()
        {
            if (Butla)
            {
                Console.WriteLine("SamochodGaz butla pełna.");
            }
            else
            {
                Butla = true;
                Console.WriteLine("SamochodGaz zatankowałem");
            }
        }

        public void Uruchom()
        {
            if (SilnikSpalinowy)
                Console.WriteLine("SamochodGaz jest już uruchomiony");
            else
            {
                SilnikSpalinowy = true;
                Console.WriteLine("Uruchamiam SamochodGaz");
            }
        }

        public void Wyłącz()
        {
            if (!SilnikSpalinowy)
                Console.WriteLine("Silnik na gaz jest wyłączony");
            else
            {
                SilnikSpalinowy = false;
                Console.WriteLine("Wyłączam silnik na gaz");
            }
        }

        public void Jedz()
        {
            if (!Butla)
            {
                Console.WriteLine("Pusta butla — uzupelnij");
                return;
            }

            if (!SilnikSpalinowy)
            {
                Console.WriteLine("SamochodGaz nie jest uruchomiony");
                return;
            }

            Console.WriteLine("Jadę...");
            Butla = false;
        }
    }
}
