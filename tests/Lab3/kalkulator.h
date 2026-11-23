// Kalkulator sklepowy - logika obliczen.
// Specyfikacja: laboratorium_01_specyfikacja_wzorcowa.docx, program "Kalkulator sklepowy".
#ifndef KALKULATOR_H
#define KALKULATOR_H

#include <cstdint>
#include <string>
#include <vector>

// Kwota w groszach.
using Grosze = std::int64_t;

// Wynik parsowania kwoty wpisanej przez uzytkownika.
struct ParseResult {
    bool ok;
    Grosze value;
    std::string error;
};

// Parsuje kwote zapisana z przecinkiem dziesietnym, np. "12,50" (BR-2, UC-8).
ParseResult parseAmount(const std::string& text);

// Formatuje kwote do postaci "1 728,49 zl" (BR-1).
std::string formatAmount(Grosze amount);

// Zaokraglenie ilorazu do grosza, polowkowe w gore (BR-4).
Grosze roundHalfUp(Grosze numerator, Grosze denominator);

// Dzialanie na dwoch kwotach: '+', '-', '*', '/' (UC-2).
// Zwraca false przy dzieleniu przez zero.
bool calculate(Grosze a, char op, Grosze b, Grosze& result);

// Wynik obliczenia procentu (UC-3).
struct PercentResult {
    Grosze percentValue;
    Grosze afterDiscount;
    Grosze afterIncrease;
};

// Oblicza procent od kwoty; procent podany w setnych czesciach (10,00 % = 1000).
PercentResult calculatePercent(Grosze amount, Grosze percent);

// Nominaly w kolejnosci, w jakiej program o nie pyta (UC-4).
const std::vector<Grosze>& denominations();

// Czy nominal jest banknotem.
bool isBanknote(Grosze denomination);

// Czy liczba sztuk nominalu jest poprawna (BR-5).
bool isValidCount(long long count);

// Sumy liczenia szuflady (UC-4).
struct DrawerSums {
    Grosze banknotes;
    Grosze coins;
    Grosze total;
};

DrawerSums sumDrawer(const std::vector<long long>& counts);

// Czy stawka VAT jest dozwolona (BR-6).
bool isAllowedVat(int rate);

// Cena brutto z ceny netto i stawki VAT w procentach (BR-6).
Grosze licz_vat(Grosze net, int rate);

// Zapis raportu dnia do pliku tekstowego (UC-7).
void saveReport(const std::string& fileName, const DrawerSums& sums);

#endif
