#include <iostream>
// Вариант 2

// превращаем код лабы 1 в функцию
void lab1() {
    short a;// создание переменной с помощью short
    short b;// создание переменной с помощью short
    short h;// создание переменной с помощью short
    float S;// создание переменной с плавающей точкой с помощью float
    std::cin >> a >> b >> h;// input
    S = h * 0.5 * (a + b);// Вычисление площади трапеции
    std::cout << "Площадь трапеции: " << S << " float" << std::endl;// вывод результата
    std::cout << "short " << sizeof(short) << " бита, " << std::numeric_limits<short>::min() << " " << std::numeric_limits<short>::max() << std::endl;
    std::cout << "float " << sizeof(float) << " бита, " << std::numeric_limits<float>::lowest() << " " << std::numeric_limits<float>::max() << std::endl;
}

// функция для суммы цифр двух чисел
int sumOfDigits(int num1, int num2) {
    std::cout << "Использована функция суммы цифр 2х чисел" << std::endl;
    int sum = 0;

    int temp1 = abs(num1);
    while (temp1 > 0) {
        sum += temp1 % 10;
        temp1 /= 10;
    }

    int temp2 = abs(num2);
    while (temp2 > 0) {
        sum += temp2 % 10;
        temp2 /= 10;
    }
    return sum;
}

// функция для нахождения наибольшого значения среди 3 чисел и числа 25
int maxOfThree(int num1, int num2, int num3) {
    std::cout << "Использована функция наибольшего значения из 3х чисел и 25" << std::endl;
    int maxNum = num1;

    if (num2 > maxNum) {
        maxNum = num2;
    }

    if (num3 > maxNum) {
        maxNum = num3;
    }
    if (25 > maxNum) {
        maxNum = 25;
    }
    return maxNum;
}

int main() {
    short choice;
    int num1, num2, num3;

    std::cout << "Выбирите пункт (1 или 2): " << std::endl;
    std::cin >> choice;

    // проверяем, какая функция была выбрана
    if (choice == 1) {
        int result;

        std::cout << "Введите 3 числа: " << std::endl;
        std::cin >> num1 >> num2 >> num3;

        // находим количество введенных чисел
        short cnt = 0;
        if (num1 != 0) cnt++;
        if (num2 != 0) cnt++;
        if (num3 != 0) cnt++;

        std::cout << "Количество чисел (не 0): " << cnt << std::endl;

        // если среди 3 чисел одно было равно 0, записываем в переменные 2 оставшихся
        if (cnt == 2) {
            int a, b;
            if (num1 != 0 && num2 != 0) {
                a = num1;
                b = num2;
            }
            else if (num1 != 0 && num3 != 0) {
                a = num1;
                b = num3;
            }
            else {
                a = num2;
                b = num3;
            }
            result = sumOfDigits(a, b);
            std::cout << "Сумма цифр двух чисел: " << result << std::endl;
        }
        else if (cnt == 3) {
            result = maxOfThree(num1, num2, num3);
            std::cout << "Наибольшее значение: " << result << std::endl;
        }
        else {
            std::cout << "Ошибка, нужно 2 или 3" << std::endl;
        }
    }
    else if (choice == 2) {
        lab1();
    }
    else {
        std::cout << "Команды с таким номером нет" << std::endl;
    }

    return 0;
}

