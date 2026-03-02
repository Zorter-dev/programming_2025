#include <iostream>
#include "Car.h"
#include <vector>
#include "Radio.hpp"
#include "AutoWorkshop.hpp"

void printLabReview() {
    std::cout << "ЛАБОРАТОРНАЯ РАБОТА" << std::endl;
    std::cout << "ИНТЕРЕС 7/10 - Интересно, но много писать" << std::endl;
    std::cout << "НАПОЛНЕННОСТЬ 9/10" << std::endl;
    std::cout << "СЛОЖНОСТЬ 7/10 - Я плохо понимаю последние темы, так ещё и постоянные ошибки из-за большого количества строк" << std::endl; 
}

int main () {
    std::cout << "СОЗДАНИЕ АВТОМОБИЛЕЙ" << std::endl;

    std::vector<std::string> items1 = {"a", "б", "в"};
    Car car1("Toyota", "Camry", "JTNBK44K12345678", "A777AA", 150000, items1);
    car1.viewInfo();

    std::vector<std::string> items2 = {"в", "т", "к"};
    Car car2("Honda", "Accord", "JHMCM12345678901", "B888BB", 120000, items2);
    car2.viewInfo();

std::cout << "--- СОЗДАНИЕ МАГНИТОЛ ---" << std::endl;
    
    Radio radio1("Sony", "XM-DSX700", "Цифровая медиа-станция с Bluetooth", 15000.0);
    Radio radio2("Pioneer", "DEH-S420BT", "CD-ресивер с Bluetooth", 12000.0);
    Radio radio3("JVC", "KD-X371BT", "Цифровой медиа-ресивер", 9000.0);
    
    std::cout << "Магнитолы:" << std::endl;
    radio1.viewInfo();
    radio2.viewInfo();
    radio3.viewInfo();
    
    // Работа с мастерской
    std::cout << "--- СОЗДАНИЕ АВТОМАСТЕРСКОЙ ---" << std::endl;
    
    AutoWorkshop workshop("ул. Ленина, д. 10, г. Москва");
    workshop.viewInfo();
    
    // Добавляем мГАнитолы в мастерскую
    std::cout << "--- ДОБАВЛЕНИЕ МАГНИТОЛ В МАСТЕРСКУЮ ---" << std::endl;
    workshop.addRadio(radio1);
    workshop.addRadio(radio2);
    workshop.addRadio(radio3);
    
    workshop.viewAvailableRadios();
    
    // Прикрепляем автомобили к мастерской
    std::cout << "--- ПРИКРЕПЛЕНИЕ АВТОМОБИЛЕЙ К МАСТЕРСКОЙ ---" << std::endl;
    workshop.attachCar(&car1);
    workshop.attachCar(&car2);
    
    workshop.viewAttachedCars();
    
    // Прикручиваем магнитолы к автомобилям
    std::cout << "--- ПРИКРУЧИВАНИЕ МАГНИТОЛ К АВТОМОБИЛЯМ ---" << std::endl;
    workshop.attachRadioToCar("A777AA", "Sony", "XM-DSX700");
    workshop.attachRadioToCar("B888BB", "Pioneer", "DEH-S420BT");
    
    std::cout << "Информация об автомобилях после установки магнитол:" << std::endl;
    car1.viewInfo();
    car2.viewInfo();
    
    std::cout << "--- ПОИСК АВТОМОБИЛЯ ПО НОМЕРУ ---" << std::endl;
    Car* foundCar = workshop.findCarByPlate("A777AA");
    if (foundCar) {
        std::cout << "Автомобиль найден: " << foundCar->getBrand() << " " << foundCar->getModel() << std::endl;
    }
    
    // Демонстрация открепления
    std::cout << "--- ОТКРЕПЛЕНИЕ АВТОМОБИЛЯ ---" << std::endl;
    workshop.detachCar("B888BB");
    workshop.viewAttachedCars();
    
    // Демонстрация удаления магнитолы из мастерской
    std::cout << "--- УДАЛЕНИЕ МАГНИТОЛЫ ИЗ МАСТЕРСКОЙ ---" << std::endl;
    workshop.removeRadio("JVC", "KD-X371BT");
    workshop.viewAvailableRadios();
    
    // Демонстрация скручивания пробега
    std::cout << "--- СКРУЧИВАНИЕ ПРОБЕГА ---" << std::endl;
    std::cout << "Текущий пробег car1: " << car1.getMileage() << " км" << std::endl;
    car1.rollbackMileage(20000);
    std::cout << "Пробег после скручивания: " << car1.getMileage() << " км" << std::endl;
    
    // Демонстрация операторов
    std::cout << "--- ДЕМОНСТРАЦИЯ ОПЕРАТОРОВ ---" << std::endl;
    Car car3 = car1 + car2;
    std::cout << "Результат car1 + car2:" << std::endl;
    car3.viewInfo();
    
    Car car4 = car1 - car2;
    std::cout << "Результат car1 - car2:" << std::endl;
    car4.viewInfo();
    
    Car car5 = car1 / car2;
    std::cout << "Результат car1 / car2:" << std::endl;
    car5.viewInfo();

    printLabReview();
    std::cout << "===== КОНЕЦ ПРОГРАММЫ =====\n" << std::endl;
    return 0;
}