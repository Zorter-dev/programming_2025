#include <iostream>
// Вариант 2
int main()
{
     
    // 1 задание
    
    int x[5];
    std::cout <<"Введите элементы последовательности: ";

    // Добавление элементов в массив
    for (int i = 0; i < 5; i++)
    {
        std::cin >> x[i];
    }
    
    // Проверка на наличие 2 чисел, сумма цифр которых превышает 25
    int sum = 0;
    short cnt = 0;
    for (int i = 0; i < 5; i++)
    {
        int num = abs(x[i]);
        while (num > 0)
        {
            sum += num % 10;
            num /= 10;
        }
        if (sum > 25)
        {
            cnt++;
        }
        sum = 0;
    }
    
    // Упорядочиваем массив и выводим его элементы
    if (cnt >= 2)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (x[i] > x[j])
                {
                    std::swap(x[i], x[j]);
                }
            }
        }
        for (int i = 0; i < 5; ++i) 
        {
        std::cout << x[i] << std::endl;
        }
    }
    
    else
    {
        std::cout << "В массиве нет 2 чисел, сумма цифр которых превышает 25" << std::endl;
    }
    
    // 2 задание
    
    int M[3][4];
    std::cout << "Введите 12 элементов матрицы: " << std::endl;
    // Добавление элементов в матрицу
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            std::cin >> M[i][j];
        }
    }
    // Вывод матрицы
    for (int i = 0; i < 3; ++i) 
    {
        for (int j = 0; j < 4; ++j) 
        {
            std::cout << M[i][j] << " ";
        }
        std::cout << std::endl;
    }
    // Поиск столбца с максимальным количество отрицательных чисел
    short cnt = 0;
    short ncnt = -1;
    int clm = 0;
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            if (M[i][j] < 0)
            {
                ++cnt;
            }
        }
        if (cnt > ncnt)
        {
            ncnt = cnt;
            clm = j;
        }
        cnt = 0;
    }
    // Вывод  найденного столбца
    std::cout << (clm + 1) << std::endl;
    // Замена элементов столбца на число 100 и вывод матрицы
    for (int i = 0; i < 3; ++i) 
    {
        M[i][clm] = 100;
    }

    for (int i = 0; i < 3; ++i) 
    {
        for (int j = 0; j < 4; ++j) 
        {
            std::cout << M[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
