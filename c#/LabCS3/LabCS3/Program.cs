using ObjectConsoleApp.Samochody;
using System;
using System.Collections.Generic;

namespace LabCS3
{
    class Program
    {
        public static void JazdaTestowa(Samochod s)
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
            List<Samochod> auta = new List<Samochod>()
            {
                new SamochodBenzyna(),
                new SamochodGaz(),
                new SamochodPrad()
            };

            foreach (var auto in auta)
            {
                JazdaTestowa(auto);
            }

            Console.ReadKey();
        }
    }
}
