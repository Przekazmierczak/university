function [L, U] = doolittle(A)
    if size(A,1) ~= size(A,2)
        error('Bledny rozmiar macierzy')
    end

    SIZE = size(A, 1);
    L = eye(SIZE);
    U = zeros(SIZE);

    for i = 1:SIZE
        for j = i:SIZE
            sumU = 0;
            sumL = 0;
            for k = 1:i - 1
                sumU = sumU + (L(i, k) * U(k, j));
                sumL = sumL + (L(j, k) * U(k, i));
            end
            U(i, j) = A(i, j) - sumU;
            if j > i
                L(j, i) = (A(j, i) - sumL) / U(i, i);
            end
        end
    end
end

function [res] = solve(L, U, B)
    SIZE = size(L, 1);

    % L
    y = zeros(SIZE, 1);
    for row = 1:SIZE
        sum = B(row, 1);
        for col = 1:row - 1
            sum = sum - L(row, col) * y(col, 1);
        end
        y(row, 1) = sum;
    end
    
    % U
    res = zeros(SIZE, 1);
    for row = SIZE:-1:1
        sum = y(row, 1);
        for col = row + 1:SIZE
            sum = sum - U(row, col) * res(col, 1);
        end
        res(row, 1) = sum / U(row, row);
    end
end

clc
close all

p = 3;

switch p
    case 1
        A = [2 2 1; 1 4 1; 0 1 2];
        B = [3; -1; 1];
    case 2
        A = [4 1 4; 2 -1 2; 1 1 2];
        B = [2; -4; -1];
    case 3
        A = [2 2 1 -1; 0 3 2 2; 1 2 2 1; 1 1 1 0];
        B = [6; -1; 4; 4];
    otherwise
        A = [2 1 -1; 0 3 1; -2 1 4];
        B = [4; -2; -4];
end

% Zadanie 1
[L, U] = doolittle(A);
[L1, U1] = lu(A);

disp('Zadanie 1:')
disp('Rozwiazanie L:');
disp(L);
disp('Rozwiazanie U:');
disp(U);

disp('Rozwiazanie L1:');
disp(L1);
disp('Rozwiazanie U1:');
disp(U1);

% Zadanie 2
[res] = solve(L, U, B);

disp('Zadanie 2:')
disp('Rozwiazanie ukladu rownan:')
disp(res);