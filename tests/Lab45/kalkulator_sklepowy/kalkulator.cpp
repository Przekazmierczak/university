// Kalkulator sklepowy - implementacja logiki obliczen.
#include "kalkulator.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <limits>
#include <numeric>

namespace {

constexpr Grosze GROSZE_W_ZLOTYM = 100;                  // BR-1
constexpr std::size_t MAKS_MIEJSC_PO_PRZECINKU = 2;      // BR-1, UC-8
constexpr std::size_t MAKS_CYFR_ZLOTYCH = 9;             // KWOTA_MAKS
constexpr std::size_t MAKS_CYFR_LICZBY = 9;              // liczba calkowita bez przepelnienia
constexpr std::size_t CYFR_W_GRUPIE = 3;                 // BR-1: "1 728,49 zl"
constexpr int PODSTAWA_DZIESIETNA = 10;
constexpr std::int64_t SETNE_PROCENTU_W_CALOSCI = 10000; // UC-3: 100,00 % = 10000
constexpr Grosze NAJMNIEJSZY_BANKNOT = 1000;             // UC-4: banknoty od 10 zl
constexpr long long MAKS_SZTUK = 9999;                   // BR-5
constexpr long long DOZWOLONE_STAWKI_VAT[] = {23, 8, 5, 0}; // BR-6
constexpr long long PROCENT_CALOSCI = 100;               // BR-6

WynikParsowania blad(const std::string& komunikat) {
    return {false, 0, komunikat};
}

bool czyCyfra(char znak) {
    return std::isdigit(static_cast<unsigned char>(znak)) != 0;
}

bool czyCyfry(const std::string& tekst) {
    return !tekst.empty() && std::all_of(tekst.begin(), tekst.end(), czyCyfra);
}

std::int64_t naLiczbe(const std::string& cyfry) {
    return std::accumulate(cyfry.begin(), cyfry.end(), std::int64_t{0}, [](std::int64_t liczba, char znak) {
        return liczba * PODSTAWA_DZIESIETNA + (znak - '0');
    });
}

// Komunikat dla pierwszego niedozwolonego znaku; pusty, gdy sa tylko cyfry i przecinki (UC-8, BR-2).
std::string sprawdzZnaki(const std::string& tekst) {
    for (const char znak : tekst) {
        if (znak == '-') {
            return "Kwota nie moze byc ujemna.";
        }
        if (znak == '.') {
            return "Separatorem dziesietnym jest przecinek, np. 12,50.";
        }
        if (znak != ',' && !czyCyfra(znak)) {
            return "To nie jest liczba.";
        }
    }
    return "";
}

std::int64_t modul(std::int64_t liczba) {
    return liczba < 0 ? -liczba : liczba;
}

// CR-11: iloczyn sprawdzany przed mnozeniem, zeby nie przepelnic std::int64_t.
bool czyIloczynMiesciSie(std::int64_t a, std::int64_t b) {
    return a == 0 || modul(b) <= std::numeric_limits<std::int64_t>::max() / modul(a);
}

}  // namespace

WynikParsowania parsujKwote(const std::string& tekst) {
    if (tekst.empty()) {
        return blad("Wartosc nie moze byc pusta.");
    }
    const std::string niedozwolony = sprawdzZnaki(tekst);
    if (!niedozwolony.empty()) {
        return blad(niedozwolony);
    }
    const std::size_t przecinek = tekst.find(',');
    const std::string zlote = tekst.substr(0, przecinek);
    const std::string grosze = przecinek == std::string::npos ? "" : tekst.substr(przecinek + 1);
    if (!czyCyfry(zlote) || (przecinek != std::string::npos && !czyCyfry(grosze))) {
        return blad("Niepoprawny zapis kwoty.");
    }
    if (grosze.size() > MAKS_MIEJSC_PO_PRZECINKU) {
        return blad("Zbyt wiele miejsc po przecinku (najwyzej 2).");
    }
    const std::size_t pierwszaCyfra = zlote.find_first_not_of('0');
    if (pierwszaCyfra != std::string::npos && zlote.size() - pierwszaCyfra > MAKS_CYFR_ZLOTYCH) {
        return blad("Kwota jest zbyt duza (najwyzej 999 999 999,99 zl).");
    }
    const Grosze groszeKwoty = grosze.empty() ? 0 : naLiczbe(grosze);
    return {true, naLiczbe(zlote) * GROSZE_W_ZLOTYM + groszeKwoty, ""};
}

bool parsujLiczbeCalkowita(const std::string& tekst, long long& liczba) {
    const bool ujemna = !tekst.empty() && tekst[0] == '-';
    const std::string cyfry = ujemna ? tekst.substr(1) : tekst;
    if (!czyCyfry(cyfry) || cyfry.size() > MAKS_CYFR_LICZBY) {
        return false;
    }
    liczba = ujemna ? -naLiczbe(cyfry) : naLiczbe(cyfry);
    return true;
}

std::string formatujKwote(Grosze kwota) {
    const Grosze bezZnaku = modul(kwota);
    const std::string zlote = std::to_string(bezZnaku / GROSZE_W_ZLOTYM);
    std::string zloteWGrupach = zlote;
    if (zloteWGrupach.size() > CYFR_W_GRUPIE) {
        zloteWGrupach.insert(zloteWGrupach.size() - CYFR_W_GRUPIE, " ");
    }
    std::string grosze = std::to_string(bezZnaku % GROSZE_W_ZLOTYM);
    if (grosze.size() < MAKS_MIEJSC_PO_PRZECINKU) {
        grosze.insert(0, "0");
    }
    return (kwota < 0 ? "-" : "") + zloteWGrupach + "," + grosze + " zl";
}

std::int64_t zaokraglijPolowkowoWGore(std::int64_t licznik, std::int64_t mianownik) {
    std::int64_t iloraz = licznik / mianownik;
    const std::int64_t reszta = licznik % mianownik;
    // reszta wieksza od polowy mianownika, zapisane bez mnozenia 2 * reszta (przepelnienie)
    if (reszta > mianownik - reszta) {
        ++iloraz;
    }
    return iloraz;
}

bool czyZnaneDzialanie(char dzialanie) {
    return dzialanie == '+' || dzialanie == '-' || dzialanie == '*' || dzialanie == '/';
}

StatusDzialania oblicz(Grosze a, char dzialanie, Grosze b, Grosze& wynik) {
    if (!czyZnaneDzialanie(dzialanie)) {
        return StatusDzialania::NieznaneDzialanie;
    }
    if (modul(a) > KWOTA_MAKS || modul(b) > KWOTA_MAKS) {
        return StatusDzialania::ZbytDuzaKwota;
    }
    Grosze nowyWynik = 0;
    if (dzialanie == '+') {
        nowyWynik = a + b;
    } else if (dzialanie == '-') {
        nowyWynik = a - b;
    } else if (dzialanie == '*') {
        if (!czyIloczynMiesciSie(a, b)) {
            return StatusDzialania::ZbytDuzaKwota;
        }
        nowyWynik = a * b / GROSZE_W_ZLOTYM;
    } else {
        if (b == 0) {
            return StatusDzialania::DzieleniePrzezZero;
        }
        nowyWynik = zaokraglijPolowkowoWGore(a * GROSZE_W_ZLOTYM * (b < 0 ? -1 : 1), modul(b));
    }
    if (modul(nowyWynik) > KWOTA_MAKS) {
        return StatusDzialania::ZbytDuzaKwota;
    }
    wynik = nowyWynik;
    return StatusDzialania::Poprawne;
}

bool obliczProcent(Grosze kwota, std::int64_t procentSetne, WynikProcentu& wynik) {
    if (!czyIloczynMiesciSie(kwota, procentSetne)) {
        return false;
    }
    const Grosze wartoscProcentu = zaokraglijPolowkowoWGore(kwota * procentSetne, SETNE_PROCENTU_W_CALOSCI);
    if (modul(kwota) + modul(wartoscProcentu) > KWOTA_MAKS) {
        return false;
    }
    wynik = {wartoscProcentu, kwota - wartoscProcentu, kwota + wartoscProcentu};
    return true;
}

const std::vector<Grosze>& nominaly() {
    static const std::vector<Grosze> lista = {
        50000, 20000, 10000, 5000, 2000, 1000,  // banknoty: 500, 200, 100, 50, 20, 10 zl
        500, 200, 100, 50, 20, 10, 5, 2, 1      // monety: 5, 2, 1 zl, 50, 20, 10, 5, 2, 1 gr
    };
    return lista;
}

bool czyBanknot(Grosze nominal) {
    return nominal > NAJMNIEJSZY_BANKNOT;
}

bool czyPoprawnaLiczbaSztuk(long long liczbaSztuk) {
    return liczbaSztuk > 0 && liczbaSztuk <= MAKS_SZTUK;
}

SumySzuflady sumujSzuflade(const std::vector<long long>& liczbySztuk) {
    const std::vector<Grosze>& lista = nominaly();
    const std::size_t ile = std::min(liczbySztuk.size(), lista.size());
    SumySzuflady sumy;
    for (std::size_t i = 0; i < ile; ++i) {
        const Grosze wartosc = lista[i] * liczbySztuk[i];
        if (czyBanknot(lista[i])) {
            sumy.banknoty += wartosc;
        } else {
            sumy.bilon += wartosc;
        }
    }
    sumy.razem = sumy.banknoty + sumy.bilon;
    return sumy;
}

bool czyDozwolonaStawkaVat(long long stawka) {
    return std::find(std::begin(DOZWOLONE_STAWKI_VAT), std::end(DOZWOLONE_STAWKI_VAT), stawka)
           != std::end(DOZWOLONE_STAWKI_VAT);
}

Grosze cenaBrutto(Grosze netto, long long stawka) {
    return zaokraglijPolowkowoWGore(netto * (PROCENT_CALOSCI + stawka), PROCENT_CALOSCI);
}

bool zapiszRaport(const std::string& nazwaPliku, const std::string& data, const SumySzuflady& sumy) {
    std::ofstream plik(nazwaPliku, std::ios::app);
    if (!plik) {
        return false;
    }
    plik << data << ';' << formatujKwote(sumy.banknoty) << ';' << formatujKwote(sumy.bilon) << ';'
         << formatujKwote(sumy.razem) << '\n';
    plik.flush();
    return !plik.fail();
}


