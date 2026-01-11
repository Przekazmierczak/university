function [X] = gauss(A, B)
    if size(A, 1) ~= size(B, 1)
        error('Bledny rozmiar macierzy')
    end

    A = [A, B];
    ROWS = size(A, 1);
    COLS = size(A, 2);
    X = zeros(ROWS, 1);
    
    % eliminacja do przodu
    for col = 1:COLS - 1
        % max index
        [maxValue, index] = max(abs(A(col:end, col)));
        index = index + col - 1;

        if (maxValue) == 0
            disp('Macierz jest osobliwa');
            return
        end

        % swap
        A([col index], :) = A([index col], :);
    
        for row = col + 1:ROWS
            a = -A(row, col) / A(col, col);
            % obliczanie pozostalych kolumn
            A(row, col:COLS) = A(row, col:COLS) + a * A(col, col:COLS);
        end
    end
    
    % podstawianie wsteczne
    for row = ROWS:-1:1
        res = A(row, COLS);
        for col = row + 1:ROWS
            res = res - A(row, col) * X(col, 1);
        end
        X(row, 1) = res / A(row, row);
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
        A = [1 1 2; 2 -1 2; 4 1 4];
        B = [-1 ; -4; 2];
    case 3
        A = [1 1 1 0; 2 2 1 -1; 0 3 1 2; 1 2 2 1];
        B = [3; 4; -1; 4];
    otherwise
        A = [0 3 1; 2 1 -1; -2 1 4];
        B = [-2; 4; -4];
end

disp('Rozwiazanie X:');
X = gauss(A, B);
disp(X);