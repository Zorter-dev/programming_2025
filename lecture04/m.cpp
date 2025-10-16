#include <iostream>

int main()
{
	//Алгоритм распаковки натурального числа
	//123 -> 1 2 3
	// int x = 123;
	// std::cout << x % 10 << std::endl; // 3
	// std::cout << (x / 10) % 10 << std::endl; // 2
	/*
	int sum = 0;
	int mult = 1;
	int min_d = 9;
	int max_d = 0;
	while (x > 0)
	{
		std::cout << (x % 10 ) << std::endl;
		int d = x % 10;
		sum += d;
		mult *= d;
		min_d = std::min(min_d, d);
		max_d = std::max(max_d, d);
		x /= 10;
	}
	std::cout << "Sum = " << sum << std::endl;
	std::cout << "Mult = " << mult << std::endl;
	std::cout << "Min_d = " << min_d << std::endl;
	std::cout << "Max_d = " << max_d << std::endl;
	*/

	// Найти часто встречающуюся цифру
	/*
	int x = 1231;
	int most_frequently = 0;
	int max_cnt = 0;
	for (int d = 0; d < 10; ++d)
	{
		int cnt = 0;
		int tmp = x;
		while (tmp > 0)
		{
			int digit = tmp % 10;
			if (digit == d)
				++cnt;
			tmp /= 10;
		}
		if (max_cnt < cnt)
		{
			max_cnt = cnt;
			most_frequently = d;
		}
	}
	std::cout << "most_frequently = " << most_frequently << std::endl;
	*/
	
	//---------------------------------
	// Области видимости
	//---------------------------------
	/*
	// int x = 1;

	{
		int y = x;
		y = 10;
	}

	// x = y;
	//--------------------------------
	int x = 123;
	
	{
		int x = 10;
		x = 1;
		std::cout << x << std::endl;
	}

	{
		int x = 20;
		x = 2;
		std::cout << x << std:: endl;
	}
	//--------------------------------
	for (int i = 0; i < 10; ++i)
	{
		if (i == 5)
		{
			break;
		}
	}
	*/
	//-----------------------
	// Масивы
	//-----------------------
	int x1 = 5;
	int x2 = 1;
	int x3 = 2;
	int x4 = 50;
	int x5 = 10;

	const int NMax = 5;
	int x[NMax];
	x[0] = 5;
	x[1] = 1;
	x[2] = 2;
	x[3] = 50;
	x[4] = 10;

	for (int i = 0; i < NMax - 1; i++)
	{
		for(int j = i + 1; j < NMax; ++j)
		{
			if (x[i] > x[j])
			{
				//std::swap(x[i], x[j]);
				int tmp = x[i];
				x[i] = x[j];
				x[j] = tmp;
			}
		}
	}

	for (int i = 0; i < 5; i++)
	{
		std::cout << x[i] << std::endl;
	}

	// Многомерный массив (2x мерный)
	const int MMax = 10;

	int matrix[MMax][MMax] = 
	{
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}

	};

	std::cout << matrix[1][0] << std::endl;

	for (int i = 0; i < MMax; i++)
	{
		for(int j = 0; j < MMax; j++)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}

	

}