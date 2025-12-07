using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ObjectConsoleApp.Samochody
{
    public class SamochodPrad : ISamochod, ISamochodPrad
    {
        public bool SilnikElektryczny { get; private set; }
        public bool Akumulator { get; private set; }

        public void Tankuj()
        {
            if (Akumulator)
            {
                Console.WriteLine("SamochodPrad akumulator pełny.");
            }
            else
            {
                Akumulator = true;
                Console.WriteLine("SamochodPrad naładowany");
            }
        }

        public void Uruchom()
        {
            if (SilnikElektryczny)
                Console.WriteLine("SamochodPrad jest już uruchomiony");
            else
            {
                SilnikElektryczny = true;
                Console.WriteLine("Uruchamiam SamochodPrad");
            }
        }

        public void Wyłącz()
        {
            if (!SilnikElektryczny)
                Console.WriteLine("Silnik elektryczny jest wyłączony");
            else
            {
                SilnikElektryczny = false;
                Console.WriteLine("Wyłączam silnik elektryczny");
            }
        }

        public void Jedz()
        {
            if (!Akumulator)
            {
                Console.WriteLine("Akumulator nie naladowany — naladuj");
                return;
            }

            if (!SilnikElektryczny)
            {
                Console.WriteLine("SamochodPrad nie jest uruchomiony");
                return;
            }

            Console.WriteLine("Jadę...");
            Akumulator = false;
        }
    }
}
