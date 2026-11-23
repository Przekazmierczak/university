// Kalkulator sklepowy - interfejs konsolowy: wczytuje dane, wywoluje logike i wypisuje wyniki (CR-1).
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include "kalkulator.h"

namespace {

const std::string PLIK_RAPORTU = "raport_dnia.txt";  // UC-7
constexpr std::size_t DLUGOSC_DATY = 11;             // "RRRR-MM-DD" i znak konca napisu

constexpr long long OPCJA_OBLICZENIA = 1;            // UC-1
constexpr long long OPCJA_PROCENTY = 2;
constexpr long long OPCJA_SZUFLADA = 3;
constexpr long long OPCJA_CENA_NA_POLKE = 4;
constexpr long long OPCJA_KONIEC = 5;

// Koniec danych wejsciowych (EOF) konczy program zamiast petli bez konca (CR-13).
struct KoniecDanych {};

// Niezatwierdzone liczenie szuflady przetrwa powrot do menu (UC-5, UC-9).
struct LiczenieSzuflady {
    bool trwa = false;
    std::vector<long long> liczbySztuk;
};

std::string wczytajLinie(const std::string& pytanie) {
    std::cout << pytanie;
    std::string linia;
    if (!std::getline(std::cin, linia)) {
        throw KoniecDanych{};
    }
    return linia;
}

// UC-8: przy blednej wartosci komunikat i ponowne pytanie o to samo pole.
Grosze wczytajKwote(const std::string& pytanie) {
    while (true) {
        const WynikParsowania wynik = parsujKwote(wczytajLinie(pytanie));
        if (wynik.poprawny) {
            return wynik.kwota;
        }
        std::cout << wynik.komunikat << "\n";
    }
}

// UC-8: liczba calkowita spelniajaca warunek; pusta linia oznacza 0, jesli pustaToZero (UC-4).
long long wczytajLiczbeCalkowita(const std::string& pytanie, bool (*czyPoprawna)(long long),
                                 const std::string& komunikat, bool pustaToZero) {
    while (true) {
        const std::string linia = wczytajLinie(pytanie);
        if (pustaToZero && linia.empty()) {
            return 0;
        }
        long long liczba = 0;
        if (parsujLiczbeCalkowita(linia, liczba) && czyPoprawna(liczba)) {
            return liczba;
        }
        std::cout << komunikat << "\n";
    }
}

// UC-2: przy dzieleniu przez zero albo zbyt duzym wyniku ponowne pytanie o druga liczbe.
Grosze wykonajDzialanie(Grosze a, char dzialanie) {
    while (true) {
        const Grosze b = wczytajKwote("Druga liczba: ");
        Grosze wynik = 0;
        const StatusDzialania status = oblicz(a, dzialanie, b, wynik);
        if (status == StatusDzialania::Poprawne) {
            return wynik;
        }
        if (status == StatusDzialania::DzieleniePrzezZero) {
            std::cout << "Nie mozna dzielic przez zero.\n";
        } else {
            std::cout << "Wynik przekracza " << formatujKwote(KWOTA_MAKS) << ".\n";
        }
    }
}

void obsluzObliczenia() {
    Grosze wynik = wczytajKwote("Pierwsza liczba: ");
    while (true) {
        const std::string dzialanie = wczytajLinie("Dzialanie (+ - * /, pusta linia = powrot do menu): ");
        if (dzialanie.empty()) {
            return;
        }
        if (dzialanie.size() != 1 || !czyZnaneDzialanie(dzialanie[0])) {
            std::cout << "Nieznane dzialanie.\n";
            continue;
        }
        wynik = wykonajDzialanie(wynik, dzialanie[0]);
        std::cout << "Wynik: " << formatujKwote(wynik) << "\n";
    }
}

void obsluzProcenty() {
    const Grosze kwota = wczytajKwote("Kwota: ");
    while (true) {
        const Grosze procent = wczytajKwote("Procent: ");
        WynikProcentu wynik;
        if (obliczProcent(kwota, procent, wynik)) {
            std::cout << "Wartosc procentu: " << formatujKwote(wynik.wartoscProcentu) << "\n";
            std::cout << "Po obnizce:       " << formatujKwote(wynik.poObnizce) << "\n";
            std::cout << "Po podwyzce:      " << formatujKwote(wynik.poPodwyzce) << "\n";
            return;
        }
        std::cout << "Wynik przekracza " << formatujKwote(KWOTA_MAKS) << ".\n";
    }
}

long long wczytajLiczbeSztuk(Grosze nominal) {
    return wczytajLiczbeCalkowita("Liczba sztuk " + formatujKwote(nominal) + ": ", czyPoprawnaLiczbaSztuk,
                                  "Liczba sztuk musi byc liczba calkowita od 0 do 9999.", true);
}

bool czyNumerNominalu(long long numer) {
    return numer >= 1 && numer <= static_cast<long long>(nominaly().size());
}

// UC-5: poprawka liczby sztuk wybranego nominalu przed zatwierdzeniem liczenia.
void poprawNominal(std::vector<long long>& liczbySztuk) {
    const std::vector<Grosze>& lista = nominaly();
    for (std::size_t i = 0; i < lista.size(); ++i) {
        std::cout << i + 1 << ". " << formatujKwote(lista[i]) << ": " << liczbySztuk[i] << " szt.\n";
    }
    const long long numer =
        wczytajLiczbeCalkowita("Numer nominalu: ", czyNumerNominalu, "Nieznany numer nominalu.", false);
    const std::size_t indeks = static_cast<std::size_t>(numer - 1);
    liczbySztuk[indeks] = wczytajLiczbeSztuk(lista[indeks]);
}

// CR-17: data raportu pochodzi z zegara systemowego i jest przekazywana do logiki parametrem.
std::string dzisiejszaData() {
    const std::time_t teraz = std::time(nullptr);
    char data[DLUGOSC_DATY] = {};
    std::strftime(data, sizeof(data), "%Y-%m-%d", std::localtime(&teraz));
    return data;
}

// UC-7: zapis raportu dnia po zatwierdzeniu liczenia.
void zapytajORaport(const SumySzuflady& sumy) {
    if (wczytajLinie("Zapisac raport dnia? (t/n): ") != "t") {
        return;
    }
    if (zapiszRaport(PLIK_RAPORTU, dzisiejszaData(), sumy)) {
        std::cout << "Raport zapisany do pliku " << PLIK_RAPORTU << "\n";
    } else {
        std::cout << "Nie mozna zapisac pliku " << PLIK_RAPORTU << "\n";
    }
}

// UC-4, UC-5: wpisanie nominalow, poprawki i zatwierdzenie albo powrot do menu bez utraty danych.
void obsluzSzuflade(LiczenieSzuflady& liczenie) {
    if (!liczenie.trwa) {
        liczenie.liczbySztuk.clear();
        for (const Grosze nominal : nominaly()) {
            liczenie.liczbySztuk.push_back(wczytajLiczbeSztuk(nominal));
        }
        liczenie.trwa = true;
    }
    while (true) {
        const SumySzuflady sumy = sumujSzuflade(liczenie.liczbySztuk);
        std::cout << "Banknoty: " << formatujKwote(sumy.banknoty) << "\n";
        std::cout << "Bilon:    " << formatujKwote(sumy.bilon) << "\n";
        std::cout << "Razem:    " << formatujKwote(sumy.razem) << "\n";
        const std::string wybor = wczytajLinie("1. Popraw nominal  2. Zatwierdz  3. Powrot do menu: ");
        if (wybor == "1") {
            poprawNominal(liczenie.liczbySztuk);
        } else if (wybor == "2") {
            liczenie.trwa = false;
            zapytajORaport(sumy);
            return;
        } else if (wybor == "3") {
            return;
        } else {
            std::cout << "Nieznana opcja.\n";
        }
    }
}

void obsluzCeneNaPolke() {
    const Grosze netto = wczytajKwote("Cena netto: ");
    const long long stawka = wczytajLiczbeCalkowita("Stawka VAT (23, 8, 5, 0): ", czyDozwolonaStawkaVat,
                                                    "Niedozwolona stawka VAT.", false);
    std::cout << "Cena brutto: " << formatujKwote(cenaBrutto(netto, stawka)) << "\n";
}

// UC-9: przy niezatwierdzonym liczeniu szuflady pytanie o potwierdzenie zakonczenia.
bool czyZakonczyc(const LiczenieSzuflady& liczenie) {
    if (!liczenie.trwa) {
        return true;
    }
    return wczytajLinie("Liczenie szuflady nie jest zatwierdzone. Zakonczyc program? (t/n): ") == "t";
}

// UC-1: menu glowne; wybor spoza listy -> komunikat i ponowne menu.
void uruchomMenu() {
    LiczenieSzuflady liczenie;
    while (true) {
        std::cout << "\n1. Obliczenia\n2. Procenty\n3. Liczenie szuflady\n4. Cena na polke\n5. Koniec\n";
        long long opcja = 0;  // przy blednym zapisie zostaje 0, czyli nieznana opcja
        parsujLiczbeCalkowita(wczytajLinie("Wybor: "), opcja);
        if (opcja == OPCJA_OBLICZENIA) {
            obsluzObliczenia();
        } else if (opcja == OPCJA_PROCENTY) {
            obsluzProcenty();
        } else if (opcja == OPCJA_SZUFLADA) {
            obsluzSzuflade(liczenie);
        } else if (opcja == OPCJA_CENA_NA_POLKE) {
            obsluzCeneNaPolke();
        } else if (opcja == OPCJA_KONIEC) {
            if (czyZakonczyc(liczenie)) {
                return;
            }
        } else {
            std::cout << "Nieznana opcja.\n";
        }
    }
}

}  // namespace

int main() {
    try {
        uruchomMenu();
    } catch (const KoniecDanych&) {
        std::cout << "\n";
    }
    return 0;
}
