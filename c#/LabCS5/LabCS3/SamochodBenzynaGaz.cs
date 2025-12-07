using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ObjectConsoleApp.Samochody
{
    class SamochodBenzynaGaz : ISamochod, ISamochodBenzyna, ISamochodGaz
    {
        public bool SilnikSpalinowy { get; private set; }
        public bool Bak { get; private set; }
        public bool Butla { get; private set; }

        // ================ TANKOWANIE ================

        public void Tankuj()
        {
            ((ISamochodBenzyna)this).Tankuj();
            ((ISamochodGaz)this).Tankuj();
        }

        void ISamochodBenzyna.Tankuj()
        {
            if (Bak)
                Console.WriteLine("Bak benzyny jest pełny.");
            else
            {
                Bak = true;
                Console.WriteLine("Zatankowano benzynę.");
            }
        }

        void ISamochodGaz.Tankuj()
        {
            if (Butla)
                Console.WriteLine("Butla jest pełna.");
            else
            {
                Butla = true;
                Console.WriteLine("Zatankowano gaz.");
            }
        }

        // ================ URUCHAMIANIE ================

        public void Uruchom()
        {
            SilnikSpalinowy = true;

            Console.WriteLine("Uruchamiam silnik spalinowy.");
        }

        // ================ WYŁĄCZANIE ================

        public void Wyłącz()
        {
            SilnikSpalinowy = false;

            Console.WriteLine("Wyłączam silnik spalinowy.");
        }

        public void Jedz()
        {
            if (SilnikSpalinowy && Bak)
            {
                Console.WriteLine("Jadę na benzynę.");
                Bak = false;
                return;
            }

            else if (SilnikSpalinowy && Butla)
            {
                Console.WriteLine("Jadę na gaz.");
                Butla = false;
                return;
            }

            Console.WriteLine("Brak paliwa albo silniki wyłączone!");
        }
    }
}

