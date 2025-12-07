using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ObjectConsoleApp.Samochody
{
    public class SamochodBenzyna : ISamochod, ISamochodBenzyna
    {
        public bool SilnikSpalinowy { get; private set; }
        public bool Bak { get; private set; }

        public void Tankuj()
        {
            if (Bak)
            {
                Console.WriteLine("SamochodBenzyna bak pełny.");
            }
            else
            {
                Bak = true;
                Console.WriteLine("SamochodBenzyna zatankowałem");
            }
        }

        public void Uruchom()
        {
            if (SilnikSpalinowy)
                Console.WriteLine("SamochodBenzyna jest już uruchomiony");
            else
            {
                SilnikSpalinowy = true;
                Console.WriteLine("Uruchamiam SamochodBenzyna");
            }
        }

        public void Wyłącz()
        {
            if (!SilnikSpalinowy)
                Console.WriteLine("Silnik spalinowy jest wyłączony");
            else
            {
                SilnikSpalinowy = false;
                Console.WriteLine("Wyłączam silnik spalinowy");
            }
        }

        public void Jedz()
        {
            if (!Bak)
            {
                Console.WriteLine("Pusty bak — uzupelnij");
                return;
            }

            if (!SilnikSpalinowy)
            {
                Console.WriteLine("SamochodBenzyna nie jest uruchomiony");
                return;
            }

            Console.WriteLine("Jadę...");
            Bak = false;
        }
    }
}
