#include <iostream>
#include <vector>
#include <random>


std::vector<std::vector<int>> randomMatrixGenerator(int rowSize, int colSize, int minVal, int maxVal) {

    std::vector<std::vector<int>> matrix;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(minVal, maxVal);

    for (int i = 0; i < rowSize; i++) {
        std::vector<int> newRow;
        
        for (int j = 0; j < colSize; j++) {
            newRow.push_back(dist(gen));
        }

        matrix.push_back(newRow);
    }

    return matrix;
}

std::vector<std::vector<int>> matrixMultiplication(std::vector<std::vector<int>> matrix1, std::vector<std::vector<int>> matrix2) {
    int ROWS1 = matrix1.size();
    int COLS1 = matrix1[0].size();

    int ROWS2 = matrix2.size();
    int COLS2 = matrix2[0].size();

    std::vector<std::vector<int>> resMatrix;


    for (int i = 0; i < ROWS1; i++) {
        std::vector<int> resMatrixRow;

        for (int j = 0; j < COLS1; j++) {
            int newRowVal = 0;

            for (int k = 0; k < COLS1; k++) {
                newRowVal += matrix1[i][k] * matrix2[k][j];
            }
            resMatrixRow.push_back(newRowVal);
        }
        resMatrix.push_back(resMatrixRow);
    }

    return resMatrix;
};

void print(std::vector<std::vector<int>> matrix) {
    for (std::vector<int> row : matrix) {
        for (int val : row) {
            std::cout << val << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
};

int main() {
    std::vector<std::vector<int>> matrix1 = randomMatrixGenerator(3, 3, -3, 10);
    std::vector<std::vector<int>> matrix2 = randomMatrixGenerator(3, 3, -3, 10);
    
    print(matrix1);
    print(matrix2);

    std::vector<std::vector<int>> newMatrix = matrixMultiplication(matrix1, matrix2);

    print(newMatrix);

    return 0;
}