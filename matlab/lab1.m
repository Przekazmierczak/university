clc
a = 6;
b = 5.5;
s = 'informatyka';
A = [1, 2, 3, 4]; % wektor wierszowy
%A = [1; 2; 3; 4]; % wektor kolumnowy
%B = [ -12 , -11 , -10 , -9; 8 , 7, 6, 5; 1 , 2, 3, 4]; % macierz
% lub
B = [-12, -11, -10,-9
       8,   7,   6, 5
       1,   2,   3, 4]; % mozna takze pominac przecinki

%length (A) % dlugosc wektora
%length (B) % zwrocony zostanie wiekszy z wymiarow
%size (B) % wymiary macierzy
%size (B,1) % liczba wierszy macierzy
%size (B,2) % liczba kolumn macierzy
%numel (A) % liczba elementow wektora
%numel (B) % liczba elementow w macierzy
%sum (A) % suma elementow
%sum (B) % wektor sum elementow dla kazdej kolumny
%sum(sum(B)) % suma wszystkich elementow macierzy

%Zadanie 1
zad1 = sum(B, 2);

%Zadanie 2
zad2 = min(B(:));

%Zadanie 3
%zad31 = A * B; - nie wykona
%zad32 = B * A; - nie wykona
zad33 = A * B';
zad34 = B * A';

%Zadanie 4
zad4 = B([1, 3], :);

%Zadanie 5
zad5 = [A 5,6,7];

%Zadanie 6
zad6 = [B sum(B, 2)];

%Zadanie 7
C = randi(10 , 5, 4);
for i = 1:size(C,1)
    for j = 1:size(C, 2)
        if mod(C(i, j), 2) == 0
            C(i, j) = 0;
        else
            C(i, j) = 100;
        end
    end
end

%Zadanie 8
D = randi(10 , 5, 4);
D(mod(D, 2) == 0) = 0;
D(mod(D, 2) == 1) = 100;

%Zadanie 9
n = 4;
L = Lucas(n);

%Zadanie 10
n = 5693;
mirrored = mirror(n);

