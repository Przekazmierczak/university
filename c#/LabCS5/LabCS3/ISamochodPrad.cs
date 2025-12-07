using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ObjectConsoleApp.Samochody
{
    interface ISamochodPrad
    {
        bool SilnikElektryczny { get; }
        bool Akumulator { get; }

        void Tankuj();
        void Uruchom();
        void Wyłącz();
        void Jedz();
    }
}