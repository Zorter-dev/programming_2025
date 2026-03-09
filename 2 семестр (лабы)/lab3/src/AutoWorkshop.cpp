#include "AutoWorkshop.hpp"
#include "Car.h"

AutoWorkshop::AutoWorkshop(): address("Unknown") {
    std::cout << "Конструктор по умолчанию вызван" << std::endl;
}
AutoWorkshop::AutoWorkshop(const std::string& addr): address(addr) {
    std::cout << "Конструктор с адресом вызван" << std::endl;
}
AutoWorkshop::AutoWorkshop(const AutoWorkshop& other): address(other.address), availableRadios(other.availableRadios) {
    std::cout << "Конструктор копирования вызван" << std::endl;
}
AutoWorkshop::~AutoWorkshop() {
    std::cout << "Деструктор вызван" << std::endl;
}
AutoWorkshop& AutoWorkshop::operator=(const AutoWorkshop& other) {
    std::cout << "Оператор присваивания вызван" << std::endl;
    if (this != &other) {
        address = other.address;
        availableRadios = other.availableRadios;
    }
    return *this;
}

std::string AutoWorkshop::getAddres() const {return address;}
std::vector<Radio> AutoWorkshop::getAvailableRadios() const {return availableRadios;}
std::vector<Car*> AutoWorkshop::getAttachedCars() const {return attachedCars;}

void AutoWorkshop::setAddress(const std::string& addr) {address = addr;}

bool AutoWorkshop::addRadio(const Radio& radio) {
    for (const auto& exRadio : availableRadios) {
        if (exRadio == radio) {
            std::cout << "Магнитола уже есть в мастерской" << std::endl;
            return false;
        }
    }
    availableRadios.push_back(radio);
    std::cout << "Магнитола " << radio.getBrand() << " " << radio.getModel() << " добавлена в мастерскую" << std::endl;
    return true;
}

bool AutoWorkshop::removeRadio(const Radio& radio) {
    for (auto i = availableRadios.begin(); i != availableRadios.end(); ++i) {
        if (*i == radio) {
           std::cout << "Магнитола " << radio.getBrand() << " " << radio.getModel() << " удалена из мастерской" << std::endl;
        availableRadios.erase(i);
        return true; 
        }
    }
    std::cout << "Магнитола " << radio.getBrand() << " " << radio.getModel() << " не найдена в мастерской" << std::endl;
    return false;
}

Radio* AutoWorkshop::findRadio(const Radio& radio) {
    for (auto& exRadio: availableRadios) {
        if (exRadio == radio) {
            return &exRadio;
        }
    }
    return nullptr;
}

bool AutoWorkshop::attachCar(Car* car) {
    if (!car) {
        std::cout << "Передан нулевой указатель на автомобиль" << std::endl;
        return false;
    }
    for (auto* attachCar: attachedCars) {
        if (attachCar == car) {
            std::cout << "Автомобиль уже прикреплен к мастерской" << std::endl;
            return false;
        }
    }
    attachedCars.push_back(car);
    std::cout << "Автомобиль " << car->getBrand() << " " << car->getPlateNumber() << " прикреплен к мастерской по адресу: " << address << std::endl;
    return true;
}

bool AutoWorkshop::detachCar(const std::string& plateNumber) {
    for (auto i = attachedCars.begin(); i != attachedCars.end(); ++i) {
        if ((*i)->getPlateNumber() == plateNumber) {
            std::cout << "Автомобиль " << (*i)->getBrand() << " " << plateNumber << " откреплен от мастерской" << std::endl;
            attachedCars.erase(i);
            return true;
        }
    }
    std::cout << "Автомобиль не найден в мастерской" << std::endl;
    return false;
}

Car* AutoWorkshop::findCarByPlate(const std::string& plateNumber) {
    for (auto* car: attachedCars) {
        if (car->getPlateNumber() == plateNumber) {
            return car;
        }
    }
    std::cout << "Автомобиль не найден в мастерской" << std::endl;
    return nullptr;
}

bool AutoWorkshop::attachRadioToCar(const std::string& plateNumebr, const Radio& radio) {
    Car* car = findCarByPlate(plateNumebr);
    if (!car) {
        return false;
    }
    Radio* foundRadio = findRadio(radio);
    if (!foundRadio) {
        std::cout << "магнитола не найдена в мастерской" << std::endl;
        return false;
    }
    car->installRadio(foundRadio);
    return true;
}

void AutoWorkshop::viewInfo() const {
    std::cout << "**** АВТОМАСТЕРСКАЯ ****" << std::endl;
    std::cout << "Адрес: " << address << std::endl;
    std::cout << "Магнитол в наличии: " << availableRadios.size() << std::endl;
    std::cout << "Автомобилей в обслуживании: " << attachedCars.size() << std::endl;
    std::cout << "****************************" << std::endl;
}

void AutoWorkshop::viewAttachedCars() const {
    std::cout << "^^^^ АВВТОМОБИЛИ В МАСТЕРСКОЙ ^^^^" << std::endl;
    if (attachedCars.empty()) {
        std::cout << "Нет автомобиля в обслуживании" << std::endl;
    }
    else {
        for (size_t i = 0; i < attachedCars.size(); i++) {
            std::cout << i + 1;
            std::cout << attachedCars[i]->getBrand() << " " << attachedCars[i]->getModel() << ", государственный номер: " << attachedCars[i]->getPlateNumber() << std::endl;
        }
    }
    std::cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << std::endl;
}

void AutoWorkshop::viewAvailableRadios() const {
    std::cout << "---- ДОСТУПНЫЕ МАГНИТОЛЫ ----" << std::endl;
    if (availableRadios.empty()) {
        std::cout << "Нет в наличии" << std::endl;
    }
    else {
        for (size_t i = 0; i < availableRadios.size(); i++) {
            std::cout << i + 1;
            std::cout << availableRadios[i].getBrand() << " " << availableRadios[i].getModel() << ", цена: " << availableRadios[i].getPrice() << " руб." << std::endl;
        }
    }
    std::cout << "-----------------------------" << std::endl;
}