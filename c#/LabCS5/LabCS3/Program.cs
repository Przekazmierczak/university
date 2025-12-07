using ObjectConsoleApp.Samochody;
using System;
using System.Collections.Generic;

namespace LabCS3
{
    class Program
    {
        public static void JazdaTestowa(ISamochod s)
        {
            Console.WriteLine("=== Jazda testowa ===");

            // Tankuję *** 
            s.Tankuj();
            // Samochód już zatankowany ***
            s.Tankuj();
            // Samochód nie jest uruchomiony
            s.Jedz();
            // Uruchamiam samochód
            s.Uruchom();
            // Samochód jest już uruchomiony
            s.Uruchom();
            // Jadę na ***
            s.Jedz();
            // Brak * **zatankuj
            s.Jedz();
            // Wyłączam silnik
            s.Wyłącz();
            // Silnik jest wyłączony
            s.Wyłącz();

            Console.WriteLine();
        }

        static void Main(string[] args)
        {
            List<ISamochod> auta = new List<ISamochod>()
            {
                new SamochodBenzyna(),
                new SamochodGaz(),
                new SamochodPrad()
            };

            foreach (var auto in auta)
            {
                JazdaTestowa(auto);
            }

            var car = new SamochodBenzynaPrad();
            car.Uruchom();
            ((ISamochod)car).Uruchom();
            ((ISamochodPrad)car).Uruchom();
            ((ISamochodBenzyna)car).Uruchom();

            car.Tankuj();

            car.Jedz();
            ((ISamochod)car).Jedz();
            ((ISamochodPrad)car).Jedz();
            ((ISamochodBenzyna)car).Jedz();

            var car2 = new SamochodBenzynaGaz();
            car2.Uruchom();
            ((ISamochod)car2).Uruchom();
            ((ISamochodGaz)car2).Uruchom();
            ((ISamochodBenzyna)car2).Uruchom();

            car2.Tankuj();

            car2.Jedz();
            ((ISamochod)car2).Jedz();
            ((ISamochodGaz)car2).Jedz();
            ((ISamochodBenzyna)car2).Jedz();


        }
    }
}
