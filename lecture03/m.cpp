#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h> // M_PI
#include <numbers> // std::numbers::pi
#include <bitset>
#include <iomanip>

int main()
{
	int r;
	std::cin >> r;
	std::cout << r << std::endl;
	//std::cout << INT_MAX << std::endl;
	//std::cout << std::numeric_limits<int>::max() << std::endl;
	int x = 10;
	int y = (x >> 1); // x * 2^1
	// 0b0100
	int x1 = 0b0011; // -> 0b0001
	std::cout << (x1 >> 1) << std::endl;

	// битовое &
	int a = 0b0010;
	int b = 0b1110;
	std::cout << (a & b) << std::endl;
	int c = 11;
	std::cout << (c & 1) << std::endl;
	//битовое | (дизъюнкция)
	int a = 0b0010;
	int b = 0b1110;
	// 0b1110;
	//битовая инверсия
	int d = 0b1010;
	std::cout << ~d << std::endl;// 0b0101
	//битовый xor (^)
	int a = 0b1010;
	int b = 0b1110;
	// 0b0101

	// 0b'0000'0000;
	char lamp_status = 0b0000'0000;
	// 0b00000010
	std::cout << (lamp_status | (1<<1)) << std::endl;
	// 0b00000001 = 1
	// 0b00000010 = (1 << 1)
	// 0b00000000 | 0b00000010
	int i = 5;
	std::cout << (lamp_status | (1<<i)) << std::endl;
	// 0b00000001 = 1
	// 0b00000010 = (1 << 1)
	// 0b00000000 | 0b00000010

	lamp_status = 0b00101010;
	i = 3;
	std::cout << (lamp_status & ~(1 << i));
	// 0b00000001 = 1
	// 0b00001000 = (1 << i)
	// 0b11110111 = ~(1<<i)
	// 0b00101010
	// 0b00100010

	int x = 11;
	bool isEven = x % 2;
	std::cout << isEven << std::endl;

	// Логические операторы
	// ==, !=, !, <, >, <=, >=, 
	int a = 10;
	int b = 11;
	std::cout << (a == b) << std::endl;
	std::cout << ((a < b) && (b & 1 == 0)) << std::endl; // вместо b & 1 == 0 можно написать b % 2 == 0, четность
	// && - логическое И
	// || - логическое ИЛИ
	// ! - логическое НЕ
	int x = 10;
	bool f = ((x == 10) || (x++));
	//short-curcuit evaluation
	std::cout << x << std::endl;

	int x = 11;
	bool isEven = (x % 2 == 0);
	if (isEven == true)
	{
		std::cout << "Even" << std::endl;
	}
	else if (x == 12)
	{
		std::cout << "X == 12" << std::endl;
	}
	else
	{
		std::cout << "Odd" << std::endl;
	}

	//switch
	int monthNumber = 0;
	switch(monthNumber)
	{
		case 0: std::cout << "January" << std::endl;
		case 1: std::cout << "Fabruary" << std::endl;

		default: std::cout << "Unknow month" << std::endl;

	}

	// Тернарный
	int x = 11;
	std::cout << (x % 2 == 0 ? "Even" : "Odd");

	int x = 10;
	// std::bitset
	std::cout << x << std::endl;

	return 0;
}

// cpp referance - функции C++