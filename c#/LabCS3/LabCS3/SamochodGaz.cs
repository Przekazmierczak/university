using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ObjectConsoleApp.Samochody
{
    public class SamochodGaz : Samochod
    {
        private bool butla { get; set; }
        private bool uruchomiony { get; set; }

        public override void Tankuj()
        {
            if (butla)
            {
                Console.WriteLine("SamochodGaz butla pełna.");
            }
            else
            {
                butla = true;
                Console.WriteLine("SamochodGaz zatankowałem");
            }
        }

        public override void Uruchom()
        {
            if (uruchomiony)
                Console.WriteLine("SamochodGaz jest już uruchomiony");
            else
            {
                uruchomiony = true;
                Console.WriteLine("Uruchamiam SamochodGaz");
            }
        }

        public override void Wyłącz()
        {
            if (!uruchomiony)
                Console.WriteLine("Silnik na gaz jest wyłączony");
            else
            {
                uruchomiony = false;
                Console.WriteLine("Wyłączam silnik na gaz");
            }
        }

        public override void Jedz()
        {
            if (!butla)
            {
                Console.WriteLine("Pusta butla — uzupelnij");
                return;
            }

            if (!uruchomiony)
            {
                Console.WriteLine("SamochodGaz nie jest uruchomiony");
                return;
            }

            Console.WriteLine("Jadę...");
            butla = false;
        }
    }
}
