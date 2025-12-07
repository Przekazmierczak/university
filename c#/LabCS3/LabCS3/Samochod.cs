using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ObjectConsoleApp.Samochody
{
    public abstract class Samochod
    {
        public abstract void Tankuj();

        public abstract void Uruchom();

        public abstract void Wyłącz();

        public abstract void Jedz();
    }

}
