#include <iostream>
#include <vector>
#include <random>

struct MatrixGenerator {
    int ROWS;
    int COLS;

    std::vector<std::vector<int>> matrix;

    MatrixGenerator(int rowSize, int colSize, int minVal, int maxVal) {
        ROWS = rowSize;
        COLS = colSize;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(minVal, maxVal);

        for (int i = 0; i < ROWS; i++) {
            std::vector<int> newRow;
            
            for (int j = 0; j < COLS; j++) {
                newRow.push_back(dist(gen));
            }

            matrix.push_back(newRow);
        }
    }

    void print() {
        for (std::vector<int> row : matrix) {
            for (int val : row) {
                std::cout << val << ", ";
            }
            std::cout << std::endl;
        }
    }

};

int main() {
    MatrixGenerator matrix(10, 10, -3, 10);
    matrix.print();

    return 0;
}