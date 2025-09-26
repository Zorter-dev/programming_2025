#include <iostream>

using namespace std;

int main() {
    short a;// Создание целого числа с помощью short
    short b;// Создание целого числа с помощью short
    float h;// Создание числа с плавующей точкой с помощью float
    float S;// Создание числа с плавующей точкой с помощью float
    cin >> a >> b >> h;//input
    S = h / 2 * (a + b);// Вычисляем площадь трапеции
    cout << "Площадь трапеции: " << S << " float" << endl;// Вывод переменных
    cout << "short " << "16 бит, " << -32768 << " " << 32767 << endl;
    cout << "float " << "32 бита, " << -3.4E+38 << " " << 3.4E+38 << endl;
    return 0;
}