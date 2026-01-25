#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    short a;// Создание целого числа с помощью short
    short b;// Создание целого числа с помощью short
    short h;// Создание числа с плавающей точкой с помощью short
    float S;// Создание числа с плавающей точкой с помощью float
    cin >> a >> b >> h;// input
    S = h * 0.5 * (a + b);// Вычисление площади трапеции
    cout << "Площадь трапеции: " << S << " float" << endl;// Вывод переменных
    cout << "short " << sizeof(short) << " байта, " << numeric_limits<short>::min() << " " << numeric_limits<short>::max() << endl;
    cout << "float " << sizeof(float) << " байта, " << numeric_limits<float>::lowest() << " " << numeric_limits<float>::max() << endl;
    return 0;
}