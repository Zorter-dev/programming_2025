#include <iostream>

int main() {
	// "Сырой указатель" - raw pointer
	int x = 1000;
	int y = 1;
	// x = a*256^0 + b*256^1 + c*256^2 + d*256^3
	// a = (1000 / 256^0) % 256 = 232
	// b = (1000 / 256^1) % 256 = 3
	// c = (1000 / 256^2) % 256 = 0
	// d = (1000 / 256^3) % 256 = 0

	// Указатель - переменная, хранящая адрес и тип другой переменной
	// Размер указателя - 8 байтов (64-битная система), 4 байта (32-битная система), 2 байта (16-битная система), 1 байт (8-битная система)
	int* px = &x;
	int* py = &y;

	// Операция взятия адреса
	std::cout << &x << std::endl;
	std::cout << &y << std::endl;
	std::cout << &px << std::endl;
	std::cout << &py << std::endl;
	std::cout << px << std::endl;
	std::cout << py << std::endl;

	// Разыменование
	std::cout << *px << std::endl;
	std::cout << *py << std::endl;

	// Выделение памяти
	int* pz;
	pz = new int; // дай место под тип int
	std::cout << &pz << std::endl;
	std::cout << pz << std::endl;
	delete pz;

	/*char* pc = (char*)pz; // Memory leak
	delete pc;
	// some code
	delete pc; // double free*/

	int* ptr = new int;
	*ptr = 2;
	std::cout << ptr << std::endl;
	std::cout << *ptr << std::endl;
	delete ptr;
	std::cout << ptr << std::endl;
	std::cout << *ptr << std::endl;

	std::cout << "Finish" << std::endl;
}