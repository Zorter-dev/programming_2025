#include <iostream>
#include <cstdlib>

using namespace std;

// Функция для создания и заполнения исходной матрицы 2x2
int** createInitialMatrix() {
    int** matrix = (int**)malloc(2 * sizeof(int*));
    for (int i = 0; i < 2; i++) {
        matrix[i] = (int*)malloc(2 * sizeof(int));
    }
    
    cout << "Введите элементы матрицы 2x2:" << endl;
    
    // Заполняем матрицу с проверкой на отрицательные числа
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            int value;
            do {
                cout << "Элемент [" << i << "][" << j << "]: ";
                cin >> value;
                if (value < 0) {
                    cout << "Ошибка! Введите неотрицательное число." << endl;
                }
            } while (value < 0);
            matrix[i][j] = value;
        }
    }
    
    return matrix;
}

// Функция для расширения матрицы (базовая матрица остается в правом нижнем углу без изменений)
int** expandMatrix(int** original, int A, int B, int C, int D) {
    int newRows = 2 + A;
    int newCols = 2 + B;
    
    // Создаем новую расширенную матрицу
    int** expanded = (int**)malloc(newRows * sizeof(int*));
    for (int i = 0; i < newRows; i++) {
        expanded[i] = (int*)malloc(newCols * sizeof(int));
    }
    
    // Копируем базовую матрицу в правый нижний угол
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            expanded[newRows - 2 + i][newCols - 2 + j] = original[i][j];
        }
    }
    
    // Заполняем только добавленные области по формуле
    // Заполняем добавленные строки сверху
    for (int i = 0; i < A; i++) {
        for (int j = 0; j < newCols; j++) {
            expanded[i][j] = i * C + j * D;
        }
    }
    
    // Заполняем добавленные столбцы слева в оставшихся строках
    for (int i = A; i < newRows; i++) {
        for (int j = 0; j < B; j++) {
            expanded[i][j] = i * C + j * D;
        }
    }
    
    return expanded;
}

// Функция для поиска строк с нулевыми значениями
int* findZeroRows(int** matrix, int rows, int cols, int& count) {
    // Сначала подсчитаем количество строк с нулями
    count = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 0) {
                count++;
                break; // Переходим к следующей строке
            }
        }
    }
    
    if (count == 0) return nullptr;
    
    // Создаем массив для индексов строк
    int* zeroRows = (int*)malloc(count * sizeof(int));
    int index = 0;
    
    // Заполняем массив индексами строк с нулями
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 0) {
                zeroRows[index++] = i;
                break; // Переходим к следующей строке
            }
        }
    }
    
    return zeroRows;
}

// Функция для удаления строк (возвращает новую матрицу)
int** removeRows(int** matrix, int& rows, int cols, int* rowsToRemove, int removeCount) {
    if (removeCount == 0 || rowsToRemove == nullptr) return matrix;
    
    // Создаем временную матрицу без удаляемых строк
    int newRows = rows - removeCount;
    int** temp = (int**)malloc(newRows * sizeof(int*));
    
    int tempIndex = 0;
    for (int i = 0; i < rows; i++) {
        bool shouldRemove = false;
        for (int j = 0; j < removeCount; j++) {
            if (i == rowsToRemove[j]) {
                shouldRemove = true;
                break;
            }
        }
        
        if (!shouldRemove) {
            temp[tempIndex] = (int*)malloc(cols * sizeof(int));
            for (int j = 0; j < cols; j++) {
                temp[tempIndex][j] = matrix[i][j];
            }
            tempIndex++;
        }
    }
    
    // Освобождаем старую память
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    
    rows = newRows;
    return temp;
}

// Функция для вывода матрицы
void printMatrix(int** matrix, int rows, int cols) {
    cout << "Матрица " << rows << "x" << cols << ":" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

// Основная функция
int main() {
    // Создаем и заполняем исходную матрицу 2x2
    int** initialMatrix = createInitialMatrix();
    
    // Получаем A, B, C, D из матрицы
    int A = initialMatrix[0][0];
    int B = initialMatrix[0][1];
    int C = initialMatrix[1][0];
    int D = initialMatrix[1][1];
    
    cout << "\nA = " << A << " (строк добавить сверху)" << endl;
    cout << "B = " << B << " (столбцов добавить слева)" << endl;
    cout << "C = " << C << " (коэффициент для строк)" << endl;
    cout << "D = " << D << " (коэффициент для столбцов)" << endl;
    
    // Расширяем матрицу (базовая остается в правом нижнем углу без изменений)
    int expandedRows = 2 + A;
    int expandedCols = 2 + B;
    int** expandedMatrix = expandMatrix(initialMatrix, A, B, C, D);
    
    cout << "\nРасширенная матрица " << expandedRows << "x" << expandedCols << ":" << endl;
    cout << "(Базовая матрица в правом нижнем углу без изменений)" << endl;
    printMatrix(expandedMatrix, expandedRows, expandedCols);
    
    // Находим строки с нулевыми значениями
    int zeroRowsCount;
    int* zeroRows = findZeroRows(expandedMatrix, expandedRows, expandedCols, zeroRowsCount);
    
    cout << "\nНайдено строк с нулями: " << zeroRowsCount << endl;
    if (zeroRowsCount > 0) {
        cout << "Индексы строк с нулями: ";
        for (int i = 0; i < zeroRowsCount; i++) {
            cout << zeroRows[i] << " ";
        }
        cout << endl;
    }
    
    // Удаляем строки с нулями
    int** finalMatrix = removeRows(expandedMatrix, expandedRows, expandedCols, zeroRows, zeroRowsCount);
    
    cout << "\nФинальная матрица после удаления строк с нулями:" << endl;
    printMatrix(finalMatrix, expandedRows, expandedCols);
    
    // Освобождаем память
    for (int i = 0; i < 2; i++) {
        free(initialMatrix[i]);
    }
    free(initialMatrix);
    
    if (zeroRowsCount > 0) {
        free(zeroRows);
    }
    
    for (int i = 0; i < expandedRows; i++) {
        free(finalMatrix[i]);
    }
    free(finalMatrix);
    
    return 0;
}
