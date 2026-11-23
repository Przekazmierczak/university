// Kalkulator sklepowy - logika obliczen (bez wejscia i wyjscia konsoli, CR-1).
// Specyfikacja: laboratorium_01_specyfikacja_wzorcowa.docx, program "Kalkulator sklepowy".
// Komentarze przy funkcjach sa ich kontraktem: opisuja dane, wynik i przypadki brzegowe,
// takze te, ktorych specyfikacja nie rozstrzyga.
#ifndef KALKULATOR_H
#define KALKULATOR_H

#include <cstdint>
#include <string>
#include <vector>

// Kwota w groszach (BR-3).
using Grosze = std::int64_t;

// Najwieksza kwota przyjmowana i wyswietlana przez program: 999 999 999,99 zl.
constexpr Grosze KWOTA_MAKS = 99999999999;

// Wynik parsowania kwoty wpisanej przez uzytkownika (UC-8).
struct WynikParsowania {
    bool poprawny = false;
    Grosze kwota = 0;
    std::string komunikat;
};

// Parsuje nieujemna kwote z przecinkiem dziesietnym (BR-2, UC-8).
// Poprawny zapis: cyfry zlotych, opcjonalnie przecinek i 1 albo 2 cyfry groszy, np. "12", "12,5"
// (= 12,50 zl), "12,05". Kwota najwyzej KWOTA_MAKS. Kazdy inny zapis (pusty, ze znakiem minus,
// z kropka, z literami, ",50", "12,", z 3 cyframi groszy, za duza kwota) daje poprawny == false,
// kwote 0 i komunikat dla uzytkownika.
WynikParsowania parsujKwote(const std::string& tekst);

// Parsuje liczbe calkowita zapisana w calej linii (UC-1, UC-4, UC-6, UC-8).
// Poprawny zapis: opcjonalny minus i od 1 do 9 cyfr, np. "7", "-1", "0009999".
// Kazdy inny zapis ("", "-", "+5", " 5", "2,5", "1234567890") daje false; liczba sie wtedy nie zmienia.
bool parsujLiczbeCalkowita(const std::string& tekst, long long& liczba);

// Formatuje kwote do postaci "1 728,49 zl" (BR-1): zlote w grupach po 3 cyfry oddzielonych spacja,
// przecinek, zawsze 2 cyfry groszy, " zl". Kwota ujemna ma na poczatku minus, np. "-0,50 zl".
std::string formatujKwote(Grosze kwota);

// Iloraz licznik / mianownik zaokraglony do calosci polowkowo w gore (BR-4); mianownik > 0.
// Liczby ujemne zaokraglane symetrycznie (polowka od zera): 5 / 10 = 1, -5 / 10 = -1, -4 / 10 = 0.
std::int64_t zaokraglijPolowkowoWGore(std::int64_t licznik, std::int64_t mianownik);

// Wynik dzialania na dwoch kwotach (UC-2).
enum class StatusDzialania { Poprawne, NieznaneDzialanie, DzieleniePrzezZero, ZbytDuzaKwota };

// Czy znak oznacza jedno z dzialan '+', '-', '*', '/' (UC-2).
bool czyZnaneDzialanie(char dzialanie);

// Wykonuje dzialanie na kwotach a i b; wynik zaokraglony do grosza (UC-2, BR-4).
// Status: NieznaneDzialanie dla znaku innego niz + - * /; DzieleniePrzezZero dla b == 0 przy '/';
// ZbytDuzaKwota, gdy |a|, |b| albo |wynik| przekracza KWOTA_MAKS.
// Wynik jest zapisywany tylko wtedy, gdy status to Poprawne; inaczej zostaje bez zmian.
StatusDzialania oblicz(Grosze a, char dzialanie, Grosze b, Grosze& wynik);

// Wynik obliczenia procentu (UC-3).
struct WynikProcentu {
    Grosze wartoscProcentu = 0;
    Grosze poObnizce = 0;
    Grosze poPodwyzce = 0;
};

// Oblicza procent od kwoty (UC-3, BR-4); procent w setnych czesciach procentu (10,00 % = 1000).
// wartoscProcentu jest zaokraglana do grosza; poObnizce = kwota - wartoscProcentu,
// poPodwyzce = kwota + wartoscProcentu. Zwraca false, gdy kwota po podwyzce przekracza KWOTA_MAKS;
// wynik zostaje wtedy bez zmian.
bool obliczProcent(Grosze kwota, std::int64_t procentSetne, WynikProcentu& wynik);

// Nominaly w groszach w kolejnosci, w jakiej program o nie pyta (UC-4): 15 nominalow od 500 zl do 1 gr.
const std::vector<Grosze>& nominaly();

// Czy nominal jest banknotem, czyli wynosi co najmniej 10 zl (UC-4).
bool czyBanknot(Grosze nominal);

// Czy liczba sztuk nominalu jest poprawna: od 0 do 9999 (BR-5).
bool czyPoprawnaLiczbaSztuk(long long liczbaSztuk);

// Sumy liczenia szuflady (UC-4).
struct SumySzuflady {
    Grosze banknoty = 0;
    Grosze bilon = 0;
    Grosze razem = 0;
};

// Sumuje szuflade; liczbySztuk[i] dotyczy nominaly()[i] (UC-4, UC-5).
// Brakujace pozycje (wektor krotszy niz 15) licza sie jako 0 sztuk, nadmiarowe sa pomijane.
SumySzuflady sumujSzuflade(const std::vector<long long>& liczbySztuk);

// Czy stawka VAT w procentach jest dozwolona: 23, 8, 5 albo 0 (BR-6).
bool czyDozwolonaStawkaVat(long long stawka);

// Cena brutto z ceny netto i dozwolonej stawki VAT w procentach (UC-6, BR-6, BR-4).
Grosze cenaBrutto(Grosze netto, long long stawka);

// Dopisuje na koncu pliku tekstowego linie raportu dnia "data;banknoty;bilon;razem", np.
// "2026-10-14;1 630,00 zl;98,49 zl;1 728,49 zl" (UC-7); kwoty jak w formatujKwote.
// Data i nazwa pliku sa parametrami (CR-17). Zwraca false, gdy pliku nie da sie otworzyc albo zapisac.
bool zapiszRaport(const std::string& nazwaPliku, const std::string& data, const SumySzuflady& sumy);

#endif
