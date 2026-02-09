function [x, n] = bisekcja(f, a, b, tol, ftol)
    if f(a) * f(b) > 0
        error ('Funkcja posiada ten sam znak na obu koncach przedzialu')
    end
    
    x = (a + b) / 2;
    n = 0;
    while (abs(f(x)) > ftol && abs(a - x) > tol)
        if f(a) * f(x) < 0
            b = x;
        else
            a = x;
        end
        x = (a + b) / 2;
        n = n + 1;
    end
end

function [x, n] = falsi(f, a, b, tol, ftol)
    if f(a) * f(b) > 0
        error ('Funkcja posiada ten sam znak na obu koncach przedzialu')
    end
    
    h = 10^(-5);
    drugaPochodna = (f(a + h) - 2 * f(a) + f(a - h)) / h ^ 2;
    if f(a) * drugaPochodna > 0
        xs = a;
        x0 = b;
    else
        xs = b;
        x0 = a;
    end

    x0 = xs - (f(xs) / (f(x0) - f(xs))) * (x0 - xs);
    n = 0;

    while (abs(f(x0)) > ftol && abs(x0 - xs) > tol)
        x0 = xs - (f(xs) / (f(x0) - f(xs))) * (x0 - xs);
        n = n + 1;
    end
    x = x0;
end

clc
close all

wybor = 1;

switch wybor
    case 1
        f = @(x) cos(x);
        a = 0;
        b = 2;
    case 2
        f = @(x) 2.^(-x) + exp(x) + 2*cos(x) - 6;
        a = 1;
        b = 3;
    otherwise
        f = @(x) power(x + 2, 5);
        a = -3;
        b = 0;
end

tol = 10^(-5);
ftol = 10^(-4);

% do zmierzenia czasu wykorzystaj polecenia tic i toc
tic
[xb, nb] = bisekcja(f, a, b, tol, ftol);
disp('Bisekcja:')
fprintf('Wartosc: %f\n', xb)
fprintf('Liczba iteracji : %i\n', nb)
fprintf('Czas obliczen: %fs\n', toc)

% do zmierzenia czasu wykorzystaj polecenia tic i toc
tic
[xf, nf] = falsi(f, a, b, tol, ftol);
disp('Falsi:')
fprintf('Wartosc: %f\n', xf)
fprintf('Liczba iteracji : %i\n', nf)
fprintf('Czas obliczen: %fs\n', toc)

% rysowanie wykresu funkcji f na przedzial [a,b] i zaznaczenie na nich znalezionych miejsc zerowych
t = a:0.01:b;
plot(t, f(t))
hold on;
plot(xb, f(xb), 'ro')
plot(xf, f(xf), 'rx')