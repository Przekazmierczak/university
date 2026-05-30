#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <sstream>

#include <omp.h>

#include <cassert>
#include <stdexcept>

#include <chrono>

struct Matrix {
    std::vector<std::vector<int> > val;
    int ROWS;
    int COLS;

    Matrix(int row, int col)
        : val(row, std::vector<int>(col, 0)),
          ROWS(row),
          COLS(col) {}

    bool operator==(const Matrix& other) const {
        if (val.size() != other.val.size()) return 0;
        if (val[0].size() != other.val[0].size()) return 0;

        for (int i = 0; i < val.size(); i++) {
            for (int j = 0; j < val[0].size(); j++) {
                if (val[i][j] != other.val[i][j]) return 0;
            }
        }
        return 1;
    }

    bool saveToFile(const std::string& filename) const {
        std::ofstream file(filename);

        if (!file.is_open()) {
            return false;
        }

        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                file << val[i][j];

                if (j < COLS - 1) {
                    file << ' ';
                }
            }
            file << '\n';
        }

        return true;
    }
};

Matrix loadMatrix(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Nie mozna otworzyc pliku");
    }

    std::vector<std::vector<int> > temp;
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::vector<int> row;
        int value;

        while (ss >> value) {
            row.push_back(value);
        }

        if (!row.empty()) {
            temp.push_back(row);
        }
    }

    if (temp.empty()) {
        throw std::runtime_error("Plik jest pusty");
    }

    int rows = temp.size();
    int cols = temp[0].size();

    for (const auto& r : temp) {
        if (r.size() != cols) {
            throw std::runtime_error("Niespojny rozmiar macierzy w pliku");
        }
    }

    Matrix M(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            M.val[i][j] = temp[i][j];
        }
    }

    return M;
}

Matrix matrixMultiplication(const Matrix& matrix1, const Matrix& matrix2) {

    if (matrix1.COLS != matrix2.ROWS) throw std::runtime_error("Incorrect matrix size");

    Matrix resMatrix(matrix1.ROWS, matrix2.COLS);

    #pragma omp parallel for collapse(2) schedule(guided, 200)
    for (int i = 0; i < matrix1.ROWS; i++) {
        for (int j = 0; j < matrix2.COLS; j++) {
            int sum = 0;

            for (int k = 0; k < matrix1.COLS; k++) {
                sum += matrix1.val[i][k] * matrix2.val[k][j];
            }

            resMatrix.val[i][j] = sum;
        }
    }

    return resMatrix;
};

int main() {
    omp_set_num_threads(8);

    auto start1 = std::chrono::high_resolution_clock::now();
    Matrix matrix1 = loadMatrix("matrix1.txt");
    Matrix matrix2 = loadMatrix("matrix2.txt");
    auto end1 = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1);
    std::cout << "Time read: " << duration1.count() << " ms" << std::endl;

    auto start2 = std::chrono::high_resolution_clock::now();
    Matrix parallel = matrixMultiplication(matrix1, matrix2);
    auto end2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);
    std::cout << "Time para multi: " << duration2.count() << " ms" << std::endl;

    auto start3 = std::chrono::high_resolution_clock::now();
    parallel.saveToFile("result.txt");
    auto end3 = std::chrono::high_resolution_clock::now();
    auto duration3 = std::chrono::duration_cast<std::chrono::milliseconds>(end3 - start3);
    std::cout << "Time write: " << duration3.count() << " ms" << std::endl;

    std::cout << "Total parallel: " << duration1.count() + duration2.count() + duration3.count() << " ms" << std::endl;

    return 0;
}