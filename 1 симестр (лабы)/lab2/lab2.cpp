// Вариант 2
#include <iostream>
#include <bitset>

using namespace std;
// 1 пункт
int main() 
{
    setlocale(LC_ALL, "Russian");
    short A;
    cout << "Число: ";
    cin >> A;
    short i;
    cout << "Бит: ";
    cin >> i;
    if ((i < 0 ) || (i > 7)) 
    {
        cout << "Ошибка, введите i от 0 до 7" << endl;
        return 1;
    }
    bitset <8> b = A;
    cout << "Двоичное представление числа A: " << b << endl;
    int bitA = (A >> i) & 1;
    cout << "i элемент: " << bitA << endl;
    if (bitA == 1)
    {
        cout << "1 Сдвиг: " << (b >> 1) << endl;
        cout << "2 Сдвиг: " << (b >> 2) << endl;
        cout << "3 Сдвиг: " << (b >> 3) << endl;
    }
    else 
    {
        short M;
        cout << "Введите число: ";
        cin >> M;
        if (M > 5)
        {
            cout << M << " больше 5 на " << (M - 5) << endl;
        }
        else if (M < 5)
        {
            cout << M << " меньше 5 на " << (5 - M) << endl;
        }
        else
        {
            cout << M << " равно 5" << endl;
        }
    }

}
// 2 пункт
/*
int main()
{   
    setlocale(LC_ALL, "Russian");
    short weekNumber;
    cout << "Введите день недели ";
    cin >> weekNumber;
    switch (weekNumber)
    {
        case 1: cout << "Понедельник" << endl; break;
        case 2: cout << "Вторник" << endl; break;
        case 3: cout << "Среда" << endl; break;
        case 4: cout << "Четверг" << endl; break;
        case 5: cout << "Пятница" << endl; break;
        case 6: cout << "Суббота" << endl; break;
        case 7: cout << "Воскресенье" << endl; break;
        default: cout << "Неверный день недели" << endl; break;
    }
}
*/