#include <iostream>
#include "Car.h"
#include <vector>

int main () {
    std::cout << "СОЗДАНИЕ АВТОМОБИЛЕЙ" << std::endl;

    std::vector<std::string> items1 = {"a", "б", "в"};
    Car car1("A", "ModelA", "А777АА", items1);
    car1.viewInfo();

    std::vector<std::string> items2 = {"в", "т", "к"};
    Car car2("B", "ModelB", "Б777ББ", items2);
    car2.viewInfo();

    std::cout << "КОНСТРУКТОР КОПИРОВАНИЯ" << std::endl;
    Car car3(car1);
    car3.viewInfo();

    std::cout << "ОПЕРАТОР ПРИСВАИВАНИЯ" << std::endl;
    Car car4;
    car4 = car2;
    car4.viewInfo();

    std::cout << "ОПЕРАТОР +" << std::endl;
    Car carP = car1 + car2;
    carP.viewInfo();

    std::cout << "ОПЕРАТОР -" << std::endl;
    Car carM = car1 - car2;
    carM.viewInfo();

    std::cout << "ОПЕРАТОР /" << std::endl;
    Car carD = car1 / car2;
    carD.viewInfo();

    std::cout << "БАГАЖНИК" << std::endl;
    Car testCar("Test", "Car", "Т123ТТ", {"запаска", "насос"});
    testCar.viewInfo();
    testCar.addItemToTrunk("книга");
    testCar.viewInfo();
    testCar.removeItemFromTrunk("запаска");
    testCar.viewInfo();
    testCar.clearTrunk();
    testCar.viewInfo();
}