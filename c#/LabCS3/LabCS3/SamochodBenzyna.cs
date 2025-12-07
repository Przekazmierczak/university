using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ObjectConsoleApp.Samochody
{
    public class SamochodBenzyna : Samochod
    {
        private bool bak { get; set; }
        private bool uruchomiony { get; set; }

        public override void Tankuj()
        {
            if (bak)
            {
                Console.WriteLine("SamochodBenzyna bak pełny.");
            }
            else
            {
                bak = true;
                Console.WriteLine("SamochodBenzyna zatankowałem");
            }
        }

        public override void Uruchom()
        {
            if (uruchomiony)
                Console.WriteLine("SamochodBenzyna jest już uruchomiony");
            else
            {
                uruchomiony = true;
                Console.WriteLine("Uruchamiam SamochodBenzyna");
            }
        }
        public override void Wyłącz()
        {
            if (!uruchomiony)
                Console.WriteLine("Silnik spalinowy jest wyłączony");
            else
            {
                uruchomiony = false;
                Console.WriteLine("Wyłączam silnik spalinowy");
            }
        }

        public override void Jedz()
        {
            if (!bak)
            {
                Console.WriteLine("Pusty bak — uzupelnij");
                return;
            }

            if (!uruchomiony)
            {
                Console.WriteLine("SamochodBenzyna nie jest uruchomiony");
                return;
            }

            Console.WriteLine("Jadę...");
            bak = false;
        }
    }
}
