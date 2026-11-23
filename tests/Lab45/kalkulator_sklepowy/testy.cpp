// Laboratorium 4 - testy modulowe kalkulatora sklepowego.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "kalkulator.h"

// Zadanie 2
TEST_CASE("UC-2: 12,50 + 7,30 = 19,80 zl") {
    Grosze wynik = 0;
    CHECK(oblicz(1250, '+', 730, wynik) == StatusDzialania::Poprawne);
    CHECK(wynik == 1980);
}

TEST_CASE("UC-2: 12,50 - 7,30 = 5,20 zl") {
    Grosze wynik = 0;
    CHECK(oblicz(1250, '-', 730, wynik) == StatusDzialania::Poprawne);
    CHECK(wynik == 520);
}

TEST_CASE("UC-2: 12,50 * 7,30 = 91,25 zl") {
    Grosze wynik = 0;
    CHECK(oblicz(1250, '*', 730, wynik) == StatusDzialania::Poprawne);
    CHECK(wynik == 9125);
}

TEST_CASE("UC-3: 100 * 0,23 = 23 zl, 100 + 23 = 123 zl, 100 - 23 = 77 zl") {
    WynikProcentu wynik;
    CHECK(obliczProcent(100, 2300, wynik) == true);
    CHECK(wynik.wartoscProcentu == 23);
    CHECK(wynik.poPodwyzce == 123);
    CHECK(wynik.poObnizce == 77);
}

TEST_CASE("UC-3: Przekroczenie max wartości") {
    WynikProcentu wynik;
    CHECK(obliczProcent(std::numeric_limits<std::int64_t>::max(), 100, wynik) == false);
}

TEST_CASE("UC-4: Wprowadzono 0 wartości ") {
    std::vector<long long> liczbySztuk = {};
    SumySzuflady sumy = sumujSzuflade(liczbySztuk);
    CHECK(sumy.banknoty == 0);
    CHECK(sumy.bilon == 0);
    CHECK(sumy.razem == 0);
}

// DEFEKT: 500 * 1 + 200 * 2 + 100 * 3 + 50 * 4 + 20 * 5 + 10 * 6 -> oczekiwano 1500, jest 1560
// DEFEKT: 5 * 1 + 2 * 2 + 1 * 3 + 0,5 * 4 + 0,2 * 5 + 0,1 * 6 + 0,05 * 7 + 0,02 * 8 + 0,01 * 9 -> oczekiwano 162, jest 762
TEST_CASE("UC-4: Wprowadzono 15 wartości ") {
    std::vector<long long> liczbySztuk = {1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int banknoty = 50000 * 1 + 20000 * 2 + 10000 * 3 + 5000 * 4 + 2000 * 5 + 1000 * 6;
    int bilony = 500 * 1 + 200 * 2 + 100 * 3 + 50 * 4 + 20 * 5 + 10 * 6 + 5 * 7 + 2 * 8 + 1 * 9;
    int razem = banknoty + bilony;
    SumySzuflady sumy = sumujSzuflade(liczbySztuk);
    CHECK(sumy.banknoty == banknoty);
    CHECK(sumy.bilon == bilony);
    CHECK(sumy.razem == razem);
}

TEST_CASE("UC-4: Wprowadzono banknot o nominale 100 zl == True") {
    CHECK(czyBanknot(10000) == true);
}

// DEFEKT: 1000 -> oczekiwano true, jest false
TEST_CASE("UC-4: Wprowadzono banknot o nominale 10 zl == True") {
    CHECK(czyBanknot(1000) == true);
}

TEST_CASE("UC-4: Wprowadzono liczę sztuk 9999 == True") {
    CHECK(czyPoprawnaLiczbaSztuk(999) == true);
}

// DEFEKT: 0 -> oczekiwano true, jest false
TEST_CASE("UC-4: Wprowadzono liczę sztuk 0 == True") {
    CHECK(czyPoprawnaLiczbaSztuk(0) == true);
}

TEST_CASE("UC-6: 10 zl + 10 zl * 23% = 12,3 zl") {
    CHECK(cenaBrutto(1000, 23) == 1230);
}

TEST_CASE("UC-6: 10 zl + 10 zl * 8% = 10,8 zl") {
    CHECK(cenaBrutto(1000, 8) == 1080);
}

TEST_CASE("UC-6: 10 zl + 10 zl * 5% = 10,5 zl") {
    CHECK(cenaBrutto(1000, 5) == 1050);
}

TEST_CASE("UC-6: 100 zl + 100 zl * 0% = 100 zl") {
    CHECK(cenaBrutto(10000, 0) == 10000);
}

TEST_CASE("UC-6: Stawka vat 0% = true") {
    CHECK(czyDozwolonaStawkaVat(0) == true);
}

TEST_CASE("UC-6: Stawka vat 4% = false") {
    CHECK(czyDozwolonaStawkaVat(4) == false);
}

// DEFEKT: 12,5 -> oczekiwano 1250, jest 1205 - chyba ze takie jest zalozenie
TEST_CASE("UC-8: Wprowadzona wartośc 12,5 -> poprawny = true, kwota = 1250, komunikat = "" ") {
    WynikParsowania wynik = parsujKwote("12,5");
    CHECK(wynik.poprawny == true);
    CHECK(wynik.kwota == 1250);
    CHECK(wynik.komunikat == "");
}

TEST_CASE("UC-8: Wprowadzona wartośc 12.5 -> poprawny = false, kwota = 0, komunikat != "" ") {
    WynikParsowania wynik = parsujKwote("12.5");
    CHECK(wynik.poprawny == false);
    CHECK(wynik.kwota == 0);
    CHECK(wynik.komunikat != "");
}

TEST_CASE("UC-8: -12 = true") {
    long long wynik;
    CHECK(parsujLiczbeCalkowita("-12", wynik) == true);
    CHECK(wynik == -12);
}

TEST_CASE("UC-8: +12 = false") {
    long long wynik;
    long long wynikPrzedZmiana = wynik;
    CHECK(parsujLiczbeCalkowita("+12", wynik) == false);
    CHECK(wynik == wynikPrzedZmiana);
}

TEST_CASE("UC-8: 12,5 = false") {
    long long wynik;
    long long wynikPrzedZmiana = wynik;
    CHECK(parsujLiczbeCalkowita("12,5", wynik) == false);
    CHECK(wynik == wynikPrzedZmiana);
}

TEST_CASE("BR-1: 1250 = 12,50 zl") {
    CHECK(formatujKwote(1250) == "12,50 zl");
}

TEST_CASE("BR-1: -1250 = -12,50 zl") {
    CHECK(formatujKwote(-1250) == "-12,50 zl");
}

TEST_CASE("BR-1: 0 = 0,00 zl") {
    CHECK(formatujKwote(0) == "0,00 zl");
}

// DEFEKT: 0,01 / 2,00 -> oczekiwano 0,01, jest 0,00
TEST_CASE("BR-4: 0,01 zl / 2,00 zl = 0,01 zl") {
    Grosze wynik = 0;
    CHECK(oblicz(1, '/', 200, wynik) == StatusDzialania::Poprawne);
    CHECK(wynik == 1);
}

// DEFEKT: 50, 2300 -> oczekiwano 12, jest 11; oczekiwano 62, jest 61; oczekiwano 38, jest 39
TEST_CASE("BR-4: 0,50 * 0,23 ~= 0,12 zl, 0,50 + 0,12 ~= 62 zl, 50 - 0,12 = 38 zl") {
    WynikProcentu wynik;
    CHECK(obliczProcent(50, 2300, wynik) == true);
    CHECK(wynik.wartoscProcentu == 12);
    CHECK(wynik.poPodwyzce == 62);
    CHECK(wynik.poObnizce == 38);
}

// DEFEKT: 50, 23 -> oczekiwano 62, jest 61
TEST_CASE("BR-4: 0,50 zl + 0,50 zl * 23% ~= 0,62 zl") {
    CHECK(cenaBrutto(50, 23) == 62);
}

// Zadanie 3
TEST_CASE("parsujKwote: Pusty") {
    WynikParsowania wynik = parsujKwote("");
    CHECK(wynik.poprawny == false);
}

TEST_CASE("parsujKwote: Znak minus") {
    WynikParsowania wynik = parsujKwote("-");
    CHECK(wynik.poprawny == false);
}

TEST_CASE("parsujKwote: Z kropką") {
    WynikParsowania wynik = parsujKwote("12.50");
    CHECK(wynik.poprawny == false);
}

TEST_CASE("parsujKwote: Z literami") {
    WynikParsowania wynik = parsujKwote("abc");
    CHECK(wynik.poprawny == false);
}

TEST_CASE("parsujKwote: ,50") {
    WynikParsowania wynik = parsujKwote(",50");
    CHECK(wynik.poprawny == false);
}

TEST_CASE("parsujKwote: ,50") {
    WynikParsowania wynik = parsujKwote("12,");
    CHECK(wynik.poprawny == false);
}

TEST_CASE("parsujKwote: trzy cyfry groszy") {
    WynikParsowania wynik = parsujKwote("12,555");
    CHECK(wynik.poprawny == false);
}

TEST_CASE("parsujKwote: za duza kwota") {
    WynikParsowania wynik = parsujKwote("99999999999999");
    CHECK(wynik.poprawny == false);
}

TEST_CASE("parsujLiczbeCalkowita: pusty string") {
    long long wynik;
    long long wynikPrzedZmiana = wynik;
    CHECK(parsujLiczbeCalkowita("", wynik) == false);
    CHECK(wynik == wynikPrzedZmiana);
}

TEST_CASE("parsujLiczbeCalkowita: minus") {
    long long wynik;
    long long wynikPrzedZmiana = wynik;
    CHECK(parsujLiczbeCalkowita("-", wynik) == false);
    CHECK(wynik == wynikPrzedZmiana);
}

TEST_CASE("parsujLiczbeCalkowita: plus przed liczba") {
    long long wynik;
    long long wynikPrzedZmiana = wynik;
    CHECK(parsujLiczbeCalkowita("+5", wynik) == false);
    CHECK(wynik == wynikPrzedZmiana);
}

TEST_CASE("parsujLiczbeCalkowita: pusty znak przed liczba") {
    long long wynik;
    long long wynikPrzedZmiana = wynik;
    CHECK(parsujLiczbeCalkowita(" 5", wynik) == false);
    CHECK(wynik == wynikPrzedZmiana);
}

TEST_CASE("parsujLiczbeCalkowita: przecinek") {
    long long wynik;
    long long wynikPrzedZmiana = wynik;
    CHECK(parsujLiczbeCalkowita("2,5", wynik) == false);
    CHECK(wynik == wynikPrzedZmiana);
}

TEST_CASE("parsujLiczbeCalkowita: zbyt duza liczba") {
    long long wynik;
    long long wynikPrzedZmiana = wynik;
    CHECK(parsujLiczbeCalkowita("1234567890", wynik) == false);
    CHECK(wynik == wynikPrzedZmiana);
}

// DEFEKT: 5, 10 -> oczekiwano 1, jest 0
TEST_CASE("zaokraglijPolowkowoWGore: 5 / 10 = 1") {
    CHECK(zaokraglijPolowkowoWGore(5, 10) == 1);
}

// DEFEKT: -5, 10 -> oczekiwano -1, jest 0
TEST_CASE("zaokraglijPolowkowoWGore: -5 / 10 = -1") {
    CHECK(zaokraglijPolowkowoWGore(-5, 10) == -1);
}

TEST_CASE("zaokraglijPolowkowoWGore: -4 / 10 = 0") {
    CHECK(zaokraglijPolowkowoWGore(-4, 10) == 0);
}

TEST_CASE("oblicz: Inny znak") {
    Grosze wynik = 0;
    CHECK(oblicz(1250, '@', 730, wynik) == StatusDzialania::NieznaneDzialanie);
    CHECK(wynik == 0);
}

TEST_CASE("oblicz: Dzielenie przez 0") {
    Grosze wynik = 0;
    CHECK(oblicz(1250, '/', 0, wynik) == StatusDzialania::DzieleniePrzezZero);
    CHECK(wynik == 0);
}

TEST_CASE("oblicz: zbyt duza kwota a") {
    Grosze wynik = 0;
    CHECK(oblicz(KWOTA_MAKS + 1, '*', 1, wynik) == StatusDzialania::ZbytDuzaKwota);
    CHECK(wynik == 0);
}

TEST_CASE("oblicz: zbyt duza kwota b") {
    Grosze wynik = 0;
    CHECK(oblicz(1, '*', KWOTA_MAKS + 1, wynik) == StatusDzialania::ZbytDuzaKwota);
    CHECK(wynik == 0);
}

TEST_CASE("oblicz: zbyt duza kwota wynik") {
    Grosze wynik = 0;
    CHECK(oblicz(KWOTA_MAKS, '+', 1, wynik) == StatusDzialania::ZbytDuzaKwota);
    CHECK(wynik == 0);
}

TEST_CASE("obliczProcent: kwota po podwyzce przekracza max") {
    WynikProcentu wynik;
    CHECK(obliczProcent(KWOTA_MAKS, 2300, wynik) == false);
    CHECK(wynik.wartoscProcentu == 0);
    CHECK(wynik.poObnizce == 0);
    CHECK(wynik.poPodwyzce == 0);
}

// DEFEKT: Poprzedni defekt pozostaje bez zmian - nadmiarowa wartosc jest pomijana prawidlowo
TEST_CASE("sumujSzuflade: Wprowadzono 16 wartości ") {
    std::vector<long long> liczbySztuk = {1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 7, 8, 9, 9};
    int banknoty = 50000 * 1 + 20000 * 2 + 10000 * 3 + 5000 * 4 + 2000 * 5 + 1000 * 6;
    int bilony = 500 * 1 + 200 * 2 + 100 * 3 + 50 * 4 + 20 * 5 + 10 * 6 + 5 * 7 + 2 * 8 + 1 * 9;
    int razem = banknoty + bilony;
    SumySzuflady sumy = sumujSzuflade(liczbySztuk);
    CHECK(sumy.banknoty == banknoty);
    CHECK(sumy.bilon == bilony);
    CHECK(sumy.razem == razem);
}

TEST_CASE("sumujSzuflade: Wprowadzono 5 wartości ") {
    std::vector<long long> liczbySztuk = {1, 2, 3, 4, 5};
    int banknoty = 50000 * 1 + 20000 * 2 + 10000 * 3 + 5000 * 4 + 2000 * 5;
    int bilony = 0;
    int razem = banknoty + bilony;
    SumySzuflady sumy = sumujSzuflade(liczbySztuk);
    CHECK(sumy.banknoty == banknoty);
    CHECK(sumy.bilon == bilony);
    CHECK(sumy.razem == razem);
}

// Zadanie 4

TEST_CASE("formatujKwote: 125000 = 1 250,00 zl") {
    CHECK(formatujKwote(125000) == "1 250,00 zl");
}

TEST_CASE("oblicz: zbyt duza kwota przy mnozeniu") {
    Grosze wynik = 0;
    CHECK(oblicz(KWOTA_MAKS - 1, '*', KWOTA_MAKS - 1, wynik) == StatusDzialania::ZbytDuzaKwota);
    CHECK(wynik == 0);
}

TEST_CASE("zapiszRaport: poprawna nazwa pliku") {
    SumySzuflady sumy;
    CHECK(zapiszRaport("fajnyPlik", "14, 11, 2026", sumy));
}

TEST_CASE("zapiszRaport: recznie ustalona suma") {
    SumySzuflady sumy;
    sumy.banknoty = 1000000;
    sumy.bilon = 1000000;
    sumy.razem = 2000000;
    CHECK(zapiszRaport("fajnyPlik", "14, 11, 2026", sumy));
}

TEST_CASE("zapiszRaport: nie poprawna nazwa pliku") {
    SumySzuflady sumy;
    CHECK(!zapiszRaport("nie/fajnyPlik", "14, 11, 2026", sumy));
}

TEST_CASE("oblicz: zbyt duza kwota przy mnozeniu, a == 0") {
    Grosze wynik = 0;
    CHECK(oblicz(0, '*', 12, wynik) == StatusDzialania::Poprawne);
    CHECK(wynik == 0);
}