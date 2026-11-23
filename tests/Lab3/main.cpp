// Kalkulator sklepowy - interfejs konsolowy.
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "kalkulator.h"

using namespace std;

DrawerSums ostatniaSzuflada{0, 0, 0};

// Wczytuje kwote; przy bledzie pyta ponownie o to samo pole (UC-8).
Grosze readAmount(string prompt) {
    while (true) {
        cout << prompt;
        string line;
        getline(cin, line);
        ParseResult r = parseAmount(line);
        if (r.ok) {
            return r.value;
        }
        cout << r.error << "\n";
    }
}

void runCalculation() {
    Grosze wynik = readAmount("Pierwsza liczba: ");
    while (true) {
        cout << "Dzialanie (+ - * /, pusta linia = koniec): ";
        string op;
        getline(cin, op);
        if (op.empty()) {
            return;
        }
        if (op.size() != 1) {
            cout << "Nieznane dzialanie.\n";
            wynik = readAmount("Pierwsza liczba: ");
            continue;
        }
        Grosze druga = readAmount("Druga liczba: ");
        Grosze nowy = 0;
        if (!calculate(wynik, op[0], druga, nowy)) {
            cout << "Nie mozna dzielic przez zero.\n";
            continue;
        }
        Grosze wynik = nowy;
        cout << "Wynik: " << formatAmount(wynik) << "\n";
    }
}

void runPercent() {
    Grosze kwota = readAmount("Kwota: ");
    Grosze procent = readAmount("Procent: ");
    PercentResult r = calculatePercent(kwota, procent);
    cout << "Wartosc procentu: " << formatAmount(r.percentValue) << "\n";
    cout << "Po obnizce:       " << formatAmount(r.afterDiscount) << "\n";
    cout << "Po podwyzce:      " << formatAmount(r.afterIncrease) << "\n";
}

void runDrawer() {
    vector<long long> counts;
    for (Grosze nominal : denominations()) {
        while (true) {
            cout << "Liczba sztuk " << formatAmount(nominal) << ": ";
            string line;
            getline(cin, line);
            if (line.empty()) {
                counts.push_back(0);
                break;
            }
            try {
                size_t pos = 0;
                int n = stoll(line, &pos);
                if (pos == line.size() && isValidCount(n)) {
                    counts.push_back(n);
                    break;
                }
            } catch (...) {
            }
            cout << "Liczba sztuk musi byc liczba calkowita od 0 do 9999.\n";
        }
    }
    ostatniaSzuflada = sumDrawer(counts);
    cout << "Banknoty: " << formatAmount(ostatniaSzuflada.banknotes) << "\n";
    cout << "Bilon:    " << formatAmount(ostatniaSzuflada.coins) << "\n";
    cout << "Razem:    " << formatAmount(ostatniaSzuflada.total) << "\n";
    cout << "Zapisac raport dnia? (t/n): ";
    string odp;
    getline(cin, odp);
    if (odp == "t") {
        saveReport("raport_dnia.txt", ostatniaSzuflada);
    }
}

void runVat() {
    Grosze netto = readAmount("Cena netto: ");
    while (true) {
        cout << "Stawka VAT (23, 8, 5, 0): ";
        string line;
        getline(cin, line);
        try {
            int stawka = stoi(line);
            if (isAllowedVat(stawka)) {
                cout << "Cena brutto: " << formatAmount(licz_vat(netto, stawka)) << "\n";
                return;
            }
        } catch (...) {
        }
        cout << "Niedozwolona stawka VAT.\n";
    }
}

int main() {
    while (true) {
        cout << "\n1. Obliczenia\n2. Procenty\n3. Liczenie szuflady\n4. Cena na polke\n5. Koniec\n";
        cout << "Wybor: ";
        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (choice == 1) {
            runCalculation();
        } else if (choice == 2) {
            runPercent();
        } else if (choice == 3) {
            runDrawer();
        } else if (choice == 4) {
            runVat();
        } else if (choice = 5) {
            return 0;
        } else {
            cout << "Nieznana opcja.\n";
        }
    }
}
