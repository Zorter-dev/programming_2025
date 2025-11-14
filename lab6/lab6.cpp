#include <iostream>
#include <cstdlib>
// Вариант 2

int* findZeroRows(int** matrix, int rows, int cols, int& zeroCount) {
    int* zeroRows = nullptr;
    zeroCount = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 0) {
                zeroCount++;
                break;
            }
        }
    }

    if (zeroCount > 0) {
        zeroRows = (int*)malloc(zeroCount * sizeof(int));
        if (zeroRows == nullptr) {
            std::cout << "Ошибка выделения памяти" << std::endl;
            return nullptr;
        }

        int index = 0;
        for (int i =0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (matrix[i][j] == 0) {
                    zeroRows[index++] = i;
                    break;
                }
            }
        }
    }

    return zeroRows;
}

int** removeRows(int** matrix, int rows, int cols, int* zeroRows, int zeroCount, int& newRows) {
    if (zeroCount == 0) {
        newRows = rows;
        return matrix;
    }

    newRows = rows - zeroCount;
    if (newRows <= 0) {
        std::cout << "Все строки были удалены" << std::endl;
        return nullptr;
    }

    int** newMatrix = (int**)malloc(newRows * sizeof(int*));
    if (newMatrix == nullptr) {
        std::cout << "Ошибка выделения памяти" << std::endl;
        return nullptr;
    }
    for (int i = 0; i < newRows; i++) {
        newMatrix[i] = (int*)malloc(cols * sizeof(int));
        if (newMatrix[i] == nullptr) {
            std::cout << "Ошибка выделения памяти" <<std::endl;
            for (int j = 0; j < i; j++) {
                free(newMatrix[j]);
            }
            free(newMatrix);
            return nullptr;
        }
    }

    int newIndex = 0;
    for (int i = 0; i < rows; i++) {
        bool ifZeroRow = false;
        for (int j = 0; j < zeroCount; j++) {
            if (i == zeroRows[j]) {
                ifZeroRow = true;
                break;
            }
        }
        if (!ifZeroRow) {
            for (int j = 0; j < cols; j++) {
                newMatrix[newIndex][j] = matrix[i][j];
            }
            newIndex++;
        }
    }

    return newMatrix;
}

void printMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << matrix[i][j] << '\t';
        }
        std::cout << std::endl;
    }
}

int main() {
    int A;
    int B;
    int C;
    int D;

}

