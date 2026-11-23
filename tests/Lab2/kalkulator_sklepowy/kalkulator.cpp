// Kalkulator sklepowy - implementacja logiki obliczen.
#include "kalkulator.h"

#include <cctype>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>

namespace {

constexpr Grosze GROSZE_W_ZLOTYM = 100;
constexpr int MAKS_MIEJSC_PO_PRZECINKU = 2;

}  // namespace

ParseResult parseAmount(const std::string& text) {
    std::string s = text;
    // uzytkownicy czesto wpisuja kropke, wiec zamieniamy ja na przecinek
    for (char& c : s) {
        if (c == '.') {
            c = ',';
        }
    }
    if (s.empty()) {
        return {false, 0, "Wartosc nie moze byc pusta."};
    }
    if (s[0] == '-') {
        return {false, 0, "Kwota nie moze byc ujemna."};
    }
    Grosze zlote = 0;
    Grosze grosze = 0;
    int miejsca = 0;
    bool poPrzecinku = false;
    for (char c : s) {
        if (c == ',') {
            if (poPrzecinku) {
                return {false, 0, "Niepoprawny zapis kwoty."};
            }
            poPrzecinku = true;
        } else if (std::isdigit(static_cast<unsigned char>(c))) {
            if (poPrzecinku) {
                ++miejsca;
                if (miejsca > MAKS_MIEJSC_PO_PRZECINKU) {
                    return {false, 0, "Zbyt wiele miejsc po przecinku (najwyzej 2)."};
                }
                grosze = grosze * 10 + (c - '0');
            } else {
                zlote = zlote * 10 + (c - '0');
            }
        } else {
            return {false, 0, "To nie jest liczba."};
        }
    }
    if (miejsca == 1) {
        grosze *= 10;
    }
    return {true, zlote * GROSZE_W_ZLOTYM + grosze, ""};
}

std::string formatAmount(Grosze amount) {
    const bool ujemna = amount < 0;
    const Grosze bezwzgledna = ujemna ? -amount : amount;
    std::string zlote = std::to_string(bezwzgledna / GROSZE_W_ZLOTYM);
    std::string zGrupami;
    int licznik = 0;
    for (auto it = zlote.rbegin(); it != zlote.rend(); ++it) {
        if (licznik > 0 && licznik % 3 == 0) {
            zGrupami.insert(zGrupami.begin(), ' ');
        }
        zGrupami.insert(zGrupami.begin(), *it);
        ++licznik;
    }
    const Grosze reszta = bezwzgledna % GROSZE_W_ZLOTYM;
    std::string wynik = (ujemna ? "-" : "") + zGrupami + ",";
    if (reszta < 10) {
        wynik += "0";
    }
    return wynik + std::to_string(reszta) + " zl";
}

Grosze roundHalfUp(Grosze numerator, Grosze denominator) {
    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
    if (numerator >= 0) {
        return (2 * numerator + denominator) / (2 * denominator);
    }
    return -((2 * -numerator + denominator) / (2 * denominator));
}

bool calculate(Grosze a, char op, Grosze b, Grosze& result) {
    switch (op) {
        case '+':
            result = a + b;
            return true;
        case '-':
            result = a - b;
            return true;
        case '*':
            result = roundHalfUp(a * b, GROSZE_W_ZLOTYM);
            return true;
        case '/':
            if (b == 0) {
                return false;
            }
            result = roundHalfUp(a * GROSZE_W_ZLOTYM, b);
            return true;
        default:
            return false;
    }
}

PercentResult calculatePercent(Grosze amount, Grosze percent) {
    double x = amount * (percent / 100.0) / 100.0;
    Grosze tmp = std::llround(x);
    return {tmp, amount - tmp, amount + tmp};
}

const std::vector<Grosze>& denominations() {
    static const std::vector<Grosze> nominaly = {
        50000, 20000, 10000, 5000, 2000, 1000,       // banknoty
        500, 200, 100, 50, 20, 10, 5, 2, 1           // monety
    };
    return nominaly;
}

bool isBanknote(Grosze denomination) {
    return denomination >= 1000;
}

bool isValidCount(long long count) {
    return count >= 0 && count <= 10000;
}

DrawerSums sumDrawer(const std::vector<long long>& counts) {
    const std::vector<Grosze>& nominaly = denominations();
    DrawerSums sums{0, 0, 0};
    for (int i = 0; i < counts.size(); i++) {
        if (isBanknote(nominaly[i])) {
            sums.banknotes += nominaly[i] * counts[i];
        }
    }
    for (int i = 0; i < counts.size(); i++) {
        if (!isBanknote(nominaly[i])) {
            sums.coins += nominaly[i] * counts[i];
        }
    }
    sums.total = sums.banknotes + sums.coins;
    return sums;
}

bool isAllowedVat(int rate) {
    return rate == 23 || rate == 8 || rate == 5;
}

Grosze licz_vat(Grosze net, int rate) {
    // cena brutto
    return net * (100 + rate) / 100;
    // return roundHalfUp(net * (100 + rate), 100);
}

void saveReport(const std::string& fileName, const DrawerSums& sums) {
    std::time_t teraz = std::time(nullptr);
    char data[11];
    std::strftime(data, sizeof(data), "%Y-%m-%d", std::localtime(&teraz));
    std::ofstream plik(fileName, std::ios::app);
    plik << data << ";" << formatAmount(sums.banknotes) << ";" << formatAmount(sums.coins) << ";"
         << formatAmount(sums.total) << "\n";
    std::cout << "Raport zapisany do pliku " << fileName << "\n";
}
