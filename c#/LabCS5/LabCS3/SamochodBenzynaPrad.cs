using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ObjectConsoleApp.Samochody
{
    class SamochodBenzynaPrad : ISamochod, ISamochodBenzyna, ISamochodPrad
    {
        public bool SilnikSpalinowy { get; private set; }
        public bool Bak { get; private set; }

        public bool SilnikElektryczny { get; private set; }
        public bool Akumulator { get; private set; }

        // ================ TANKOWANIE ================

        public void Tankuj()
        {
            ((ISamochodBenzyna)this).Tankuj();
            ((ISamochodPrad)this).Tankuj();
        }

        void ISamochodBenzyna.Tankuj()
        {
            if (Bak)
                Console.WriteLine("Bak pełny.");
            else
            {
                Bak = true;
                Console.WriteLine("Zatankowano benzynę.");
            }
        }

        void ISamochodPrad.Tankuj()
        {
            if (Akumulator)
                Console.WriteLine("Akumulator pełny.");
            else
            {
                Akumulator = true;
                Console.WriteLine("Naładowano akumulator.");
            }
        }

        // ================ URUCHAMIANIE ================

        public void Uruchom()
        {
            ((ISamochodBenzyna)this).Uruchom();
            ((ISamochodPrad)this).Uruchom();
        }

        void ISamochodBenzyna.Uruchom()
        {
            SilnikSpalinowy = true;
            Console.WriteLine("Uruchamiam silnik benzynowy.");
        }

        void ISamochodPrad.Uruchom()
        {
            SilnikElektryczny = true;
            Console.WriteLine("Uruchamiam silnik elektryczny.");
        }

        // ================ WYŁĄCZANIE ================

        public void Wyłącz()
        {
            ((ISamochodBenzyna)this).Wyłącz();
            ((ISamochodPrad)this).Wyłącz();
            Console.WriteLine("Wyłączam oba silniki.");
        }

        void ISamochodBenzyna.Wyłącz()
        {
            SilnikSpalinowy = false;
            Console.WriteLine("Wyłączam silnik benzynowy.");
        }

        void ISamochodPrad.Wyłącz()
        {
            SilnikElektryczny = false;
            Console.WriteLine("Wyłączam silnik elektryczny.");
        }



        public void Jedz()
        {
            if (SilnikElektryczny && Akumulator)
            {
                Console.WriteLine("Jadę na prąd.");
                Akumulator = false;
                return;
            }

            else if (SilnikElektryczny && Bak)
            {
                Console.WriteLine("Jadę na benzynę.");
                Bak = false;
                return;
            }

            Console.WriteLine("Brak energii lub paliwa!");
        }
    }
}
