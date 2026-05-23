#include <iostream>
#include <vector>
#include <random>

#include <omp.h>

#include <cassert>
#include <stdexcept>

#include <chrono>

struct Matrix {
    std::vector<std::vector<int>> val;
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

    void print() {
        for (std::vector<int> row : val) {
            for (int val : row) {
                std::cout << val << ", ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    };
};

Matrix randomMatrixGenerator(int rowSize, int colSize, int minVal, int maxVal) {

    Matrix matrix(rowSize, colSize);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(minVal, maxVal);

    for (int i = 0; i < matrix.ROWS; i++) {
        for (int j = 0; j < matrix.COLS; j++) {
            matrix.val[i][j] = dist(gen);
        }
    }

    return matrix;
}

Matrix matrixMultiplication(const Matrix& matrix1, const Matrix& matrix2, bool parallel) {

    if (matrix1.COLS != matrix2.ROWS) throw std::runtime_error("Incorrect matrix size");

    Matrix resMatrix(matrix1.ROWS, matrix2.COLS);

    if (!parallel) {
        for (int i = 0; i < matrix1.ROWS; i++) {
            for (int j = 0; j < matrix2.COLS; j++) {
    
                for (int k = 0; k < matrix1.COLS; k++) {
                    resMatrix.val[i][j] += matrix1.val[i][k] * matrix2.val[k][j];
                }
            }
        }
    } else {
        #pragma omp parallel for collapse(2)
        for (int i = 0; i < matrix1.ROWS; i++) {
            for (int j = 0; j < matrix2.COLS; j++) {

                for (int k = 0; k < matrix1.COLS; k++) {
                    resMatrix.val[i][j] += matrix1.val[i][k] * matrix2.val[k][j];
                }
            }
        }
    }

    return resMatrix;
};

int main() {
    Matrix matrix1 = randomMatrixGenerator(1000, 1000, -1000, 1000);
    Matrix matrix2 = randomMatrixGenerator(1000, 1000, -1000, 1000);
    
    // matrix1.print();
    // matrix2.print();

    auto start = std::chrono::high_resolution_clock::now();
    Matrix nonparallel = matrixMultiplication(matrix1, matrix2, false);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Time non parallel: " << duration.count() << " ms" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    Matrix parallel = matrixMultiplication(matrix1, matrix2, true);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Time parallel: " << duration.count() << " ms" << std::endl;

    assert(nonparallel == parallel);

    // nonparallel.print();
    // parallel.print();

    return 0;
}