namespace ObjectConsoleApp.Samochody
{
    interface ISamochodBenzyna
    {
        bool SilnikSpalinowy { get; }
        bool Bak { get; }

        void Tankuj();
        void Uruchom();
        void Wyłącz();
        void Jedz();
    }
}