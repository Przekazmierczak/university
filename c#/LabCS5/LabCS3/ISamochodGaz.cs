using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ObjectConsoleApp.Samochody
{
    interface ISamochodGaz
    {
        bool SilnikSpalinowy { get; }
        bool Butla { get; }

        void Tankuj();
        void Uruchom();
        void Wyłącz();
        void Jedz();
    }
}