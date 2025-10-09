#include <iostream>
using namespace std;

int main()
{
    //Пункт 1
    int N;
    cout << "Введите количество чисел в последовательности: " << endl;
    cin >> N;

    if (N <= 0)
    {
        cout << "Последовательность пуста" << endl;
    }
    else
    {
        long product = 1; // Произведение
        int minNumber = 1'000'000; // Минимальное число
        int minIndex = 0; // Номер минимального числа
        bool found = false; // Проверка на наличие чисел, оканчивающихся на 3
    
        cout << "Введите " << N << " чисел:" << endl;

        for (int i = 1; i <= N; i++)
        {
            int num;
            cin >> num;
            if (abs(num) % 10 == 3)
            {
                product *= num;
                found = true;
                if (num < minNumber)
                {
                    minNumber = num;
                    minIndex = i;
                }
            }
        }

        if (found)
        {
            cout << "Произведение чисел, оканчивающихся на 3: " << product << endl;
            cout << "Минимальное число: " << minNumber << endl;
            cout << "Номер минимального числа в последовательности: " << minIndex << endl;
        } 
        else 
        {
            cout << "В последовательности нет чисел, оканчивающихся на 3" << endl;
        }
    }

    // Пункт 2
    int X;
    cout << "Введите целое число X (|X| < 1000): ";
    cin >> X;
    
    if (abs(X) >= 1000) 
    {
        cout << "|X| должен быть меньше 1000" << endl;
    } 
    else 
    {
        int sum = 0;
        int temp = abs(X);
        while (temp > 0) 
        {
            sum += temp % 10;
            temp /= 10;
        }
        
        cout << "Сумма цифр числа " << X << ": " << sum << endl;
    }
    
    return 0;
}