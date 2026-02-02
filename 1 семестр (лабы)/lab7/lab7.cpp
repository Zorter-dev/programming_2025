#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
// Вариант 2
// Пункт 1

std::vector<int> arr;

//Просмотр массива
void viewArr() {
    if (arr.empty()) {
        std::cout << "Массив пустой" << std::endl;
        return;
    }

    std::cout << "[";
    for (size_t i = 0; i < arr.size(); i++) {
        std::cout << arr[i];
        if (i < arr.size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << "]" << std::endl;
}

// Добавление элемента в начало
void addToStart () {
    int val;
    std::cout << "Введите значение: ";
    std::cin >> val;

    arr.insert(arr.begin(), val);
    std::cout << "Итоговый массив: ";
    viewArr();
}

// Добавление элемента в конец
void addToEnd () {
    int val;
    std::cout << "Введите значение: ";
    std::cin >> val;
    
    arr.push_back(val);
    std::cout << "Итоговый массив: ";
    viewArr();
}

// Очистка массива
void clearArr () {
    arr.clear();
    std::cout << "Массив после очистки: ";
    viewArr();
}

// Поиск элемента в массиве
void searchInArr () {
    if (arr.empty()) {
        std::cout << "Массив пустой" << std::endl;
        return;
    }

    int val;
    std::cout << "Введите нужный элемент: ";
    std::cin >> val;
    std::cout << "Индекс элемента " << val << ": [";
    bool found = false;
    for(size_t i = 0; i < arr.size(); i++) {
        if (arr[i] == val) {
            if (found) {
                std::cout << ",";
            }
            std::cout << i;
            found = true;
        }
    }

    if (found == false) {
        std::cout << "Элемент не найден";
    }
    std::cout << "]" << std::endl;
}

// Выполнение задания из Вариант 2
void Task () {
    if (arr.empty()) {
        std::cout << "Массив пустой, ошибка выполнения" << std::endl;
        return;
    }

    if (arr.size() % 2 == 0) {
        if (!arr.empty()) {
            arr.erase(arr.begin());
            std::cout << "Удален первый элемент" << std::endl;
        }
    }
    else {
        if (arr.size() >= 4) {
            arr.erase(arr.end() - 4, arr.end());
            std::cout << "Удалены 4 последних элемента" << std::endl;
        }
        else {
            int size = arr.size();
            arr.clear();
            std::cout << "Удалены все элементы: " << size << std::endl;
        }
    }

    std::cout << "Итоговый массив: ";
    viewArr();
}

// Вывод меню
void Menu () {
    std::cout << "\n------ КОМАНДЫ ------\n";
    std::cout << "0) Выход" << std::endl;
    std::cout << "1) Просмотр массива" << std::endl;
    std::cout << "2) Добавить элемент в начало" << std::endl;
    std::cout << "3) Добавить элемент в конец" << std::endl;
    std::cout << "4) Очистка массива" << std::endl;
    std::cout << "5) Поиск элемента в масиве" << std::endl;
    std::cout << "6) Задание" << std::endl;
    std::cout << "---------------------" << std::endl;
    std::cout << "Выберите команду: ";
}

int main() {

    int choice;
    bool exitProgram = false;

    // Начальные значения для элементов
    arr = {1, 2, 3, 4, 5};

    // Цикл для работы с командами из меню
    while (!exitProgram) {
        Menu();
        std::cin >> choice;

        switch (choice) {
            case 0:
            exitProgram = true;
            std::cout << "Выход из программы" << std::endl;
            break;

            case 1:
            std::cout << "Массив: " << std::endl;
            viewArr();
            break;
            
            case 2:
            addToStart();
            break;

            case 3:
            addToEnd();
            break;

            case 4:
            clearArr();
            break;

            case 5:
            searchInArr();
            break;

            case 6:
            Task();
            break;

            default:
            std::cerr << "Неверный номер команды" << std::endl;
            break;
        }
    }
    return 0;
}


// Пункт 2

/*
const int Size = 10;
std::array <int, Size> arr;

// Вывод массива
void viewArr (const std::array <int, Size>& ar) {
    std::cout << "[";
    for (size_t i = 0; i < ar.size(); i++) {
        std::cout << ar[i];
        if (i < ar.size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << "]" << std::endl;
}

// Рандомное заполнение массива
void RandomFill () {
    srand(time(nullptr));
    for (int i = 0; i < Size; i++) {
        arr[i] = rand() % 21 - 10; // [-10; 10]
    }
}

// 1. Передача по значению
void sortByValue (std::array <int, Size> arrCopy, bool up) {
    if (up) {
        std::sort(arrCopy.begin(), arrCopy.end());
    }
    else {
        std::sort(arrCopy.begin(), arrCopy.end(), std::greater<int>());
    }

    std::cout << "После сортировки: ";
    viewArr(arrCopy);
}

// 2. Передача по ссылке
void sortByRef (std::array <int, Size>& arrRef, bool up) {
    if (up) {
        std::sort(arrRef.begin(), arrRef.end());
    }
    else {
        std::sort(arrRef.begin(), arrRef.end(), std::greater<int>());
    }

    std::cout << "После сортировки: ";
    viewArr(arrRef);
}

// 3. Передача по указателю
void sortByPtr (std::array <int, Size>* arrPtr, bool up) {
    if (up) {
        std::sort(arrPtr->begin(), arrPtr->end());
    }
    else {
        std::sort(arrPtr->begin(), arrPtr->end(), std::greater<int>());
    }

    std::cout << "После сортировки: ";
    viewArr(*arrPtr);
}

// Пример как они работают и описание к каждому
void differenceInMethods () {
    std::cout << "Три разных метода" << std::endl;

    std::array <int, Size> arrT = arr;

    std::cout << "\nЗНАЧЕНИЕ" << std::endl;
    //---
    std::cout << "\nПо значению (возрастание): \n" << std::endl;
    std::cout << "Оригинальный массив: ";
    viewArr(arrT);
    
    sortByValue(arrT, true);

    std::cout << "\nОригинальный масив (после): ";
    viewArr(arrT);
    //---
    std::cout << "\nПо значению (убывание): \n" << std::endl;
    std::cout << "Оригинальный массив: ";
    viewArr(arrT);
    
    sortByValue(arrT, false);

    std::cout << "\nОригинальный масив (после): ";
    viewArr(arrT);
    
    // ЗНАЧЕНИЕ
    // Создается копия массива
    // Изменения применяются только к копии
    // Используется дополнительная память для копии
    // Медленнее для больших масивов
    

    std::cout << "\nССЫЛКА" << std::endl;
    //---
    std::cout << "\nПо ссылке (возрастание): \n" << std::endl;
    std::cout << "Оригинальный массив: ";
    viewArr(arrT);
    
    sortByRef(arrT, true);

    std::cout << "\nОригинальный масив (после): ";
    viewArr(arrT);
    //---
    arrT = arr;
    std::cout << "\nПо ссылке (убывание): \n" << std::endl;
    std::cout << "Оригинальный массив: ";
    viewArr(arrT);
    
    sortByRef(arrT, false);

    std::cout << "\nОригинальный масив (после): ";
    viewArr(arrT);

    // ССЫЛКА
    // Передается оригинальынй массив
    // Изменения напрямую применяются к оригиналу
    // Копия не создается, память экономится
    // Быстрее для больших объектов

    arrT = arr;

    std::cout << "\nУКАЗАТЕЛЬ" << std::endl;
    //---
    std::cout << "\nПо указателю (возрастание): \n" << std::endl;
    std::cout << "Оригинальный массив: ";
    viewArr(arrT);
    
    sortByPtr(&arrT, true);

    std::cout << "\nОригинальный масив (после): ";
    viewArr(arrT);
    //---
    arrT = arr;
    std::cout << "\nПо указателю (убывание): \n" << std::endl;
    std::cout << "Оригинальный массив: ";
    viewArr(arrT);
    
    sortByPtr(&arrT, false);

    std::cout << "\nОригинальный масив (после): ";
    viewArr(arrT);

    // УКАЗАТЕЛЬ
    // Передается адрес памяти массива
    // Изменения напрямую применяются к оригиналу, можно передать nullptr
    // Копия не создается, память экономится
    // Быстрее для больших объектов, но более громоздкий в сравнении с ссылками

}

int main() {
    // Генератор случайных чисел
    srand(time(nullptr));

    // Заполнение начального массива
    RandomFill();

    differenceInMethods();

    return 0;
}
*/

// Пункт 3

/* В Первом пункте использовался std::vector (динамический массив), так как
по условию необходимо менять размер массива, а во Втором пункте использовался
std::array, так как массив оставался с фиксированной длинной. Они будут
работать одинаково, если массив не меняется, но std::array в этом случае будет быстрее. */