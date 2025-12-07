using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ObjectConsoleApp.Samochody
{
    public class SamochodPrad : Samochod
    {
        private bool akumulator { get; set; }
        private bool uruchomiony { get; set; }

        public override void Tankuj()
        {
            if (akumulator)
            {
                Console.WriteLine("SamochodPrad akumulator pełny.");
            }
            else
            {
                akumulator = true;
                Console.WriteLine("SamochodPrad naładowany");
            }
        }

        public override void Uruchom()
        {
            if (uruchomiony)
                Console.WriteLine("SamochodPrad jest już uruchomiony");
            else
            {
                uruchomiony = true;
                Console.WriteLine("Uruchamiam SamochodPrad");
            }
        }

        public override void Wyłącz()
        {
            if (!uruchomiony)
                Console.WriteLine("Silnik elektryczny jest wyłączony");
            else
            {
                uruchomiony = false;
                Console.WriteLine("Wyłączam silnik elektryczny");
            }
        }

        public override void Jedz()
        {
            if (!akumulator)
            {
                Console.WriteLine("Akumulator nie naladowany — naladuj");
                return;
            }

            if (!uruchomiony)
            {
                Console.WriteLine("SamochodPrad nie jest uruchomiony");
                return;
            }

            Console.WriteLine("Jadę...");
            akumulator = false;
        }
    }
}
