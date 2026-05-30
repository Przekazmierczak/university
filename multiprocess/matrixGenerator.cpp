#include <vector>
#include <fstream>
#include <iostream>

struct Matrix {
    std::vector<std::vector<int> > val;
    int ROWS;
    int COLS;

    Matrix(int row, int col)
        : val(row, std::vector<int>(col, 0)),
          ROWS(row),
          COLS(col) {}

    void fillOnes() {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                val[i][j] = 1;
            }
        }
    }

    bool saveToFile(const std::string& filename) const {
        std::ofstream file(filename);

        if (!file.is_open()) return false;

        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                file << val[i][j] << " ";
            }
            file << "\n";
        }

        return true;
    }

    bool operator==(const Matrix& other) const {
        if (ROWS != other.ROWS || COLS != other.COLS) return false;

        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (val[i][j] != other.val[i][j]) return false;
            }
        }
        return true;
    }
};

int main() {
    int N = 800;

    Matrix A(N, N);
    A.fillOnes();

    if (A.saveToFile("matrix2.txt")) {
        std::cout << "Zapisano macierz do pliku\n";
    } else {
        std::cout << "Blad zapisu\n";
    }

    return 0;
}