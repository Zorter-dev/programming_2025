#include "Car.h"
#include <cstdlib>
#include <ctime>

int getRandomNumber(int min, int max) {
    static bool seeded = false;
    if (!seeded) {
        srand(time(nullptr));
        seeded = true;
    }
    return min + rand() % (max - min + 1);
}

Car::Car(): brand("Unknown"), model("Unknown"), plateNumber("Unknown") {
    std::cout << "Конструктор по умолчанию вызван" << std::endl;
}

Car::Car(const std::string& br, const std::string& mdl, const std::string& plate, const std::vector<std::string>& items): brand(br), model(mdl), trunkItems(items) {
    std::cout << "Конструктор полного заполнения вызван" << std::endl;

    if (isValidPlateNumber(plate)) {
        plateNumber = plate;
    }
    else {
        plateNumber = "Unknown";
        std::cout << "Невалидный государственный номер. Установлен 'Unknown'." << std::endl;
    }
}

Car::Car(const Car& other): brand(other.brand), model(other.model), plateNumber(other.plateNumber), trunkItems(other.trunkItems) {
    std::cout << "Конструктор копирования вызван" << std::endl;
}

Car::~Car() {
    std::cout << "Деструктор вызван" << std::endl;
}

Car& Car::operator=(const Car& other) {
    std::cout << "Оператор присваивания вызван" << std::endl;

    if (this != &other) {
        brand = other.brand;
        model = other.model;
        plateNumber = other.plateNumber;
        trunkItems = other.trunkItems;
    }
    return *this;
}

Car Car::operator+(const Car& other) const {
    std::cout << "Оператор '+' вызван" << std::endl;
    Car result;
    result.brand = (this->brand != "Unknown") ? this->brand: other.brand;
    result.plateNumber = generateRandomPlateNumber();
    result.trunkItems = this->trunkItems;
    for (const auto& item: other.trunkItems) {
        result.trunkItems.push_back(item);
    }
    result.model = (this->model != "Unknown") ? this->model: "Unknown";
    return result;
}

Car Car::operator-(const Car& other) const {
    std::cout << "Оператор '-' вызван" << std::endl;
    Car result;
    result.brand = (this->brand != "Unknown") ? this->brand: other.brand;
    result.plateNumber = generateRandomPlateNumber();
    result.trunkItems = this->trunkItems;
    for (const auto& item: other.trunkItems) {
        if (std::find(result.trunkItems.begin(), result.trunkItems.end(), item) == result.trunkItems.end()) {
            result.trunkItems.push_back(item);
        }
    }

    result.model = (this->model != "Unknown") ? this->model: "Unknown";
    return result;
}

Car Car::operator/(const Car& other) const {
    std::cout << "Оператор '/' вызван" << std::endl;
    Car result;
    result.brand = other.brand;
    result.plateNumber = generateRandomPlateNumber();
    for (const auto& item1: this->trunkItems) {
        for(const auto& item2: other.trunkItems) {
            if (item1 == item2) {
                if (std::find(result.trunkItems.begin(), result.trunkItems.end(), item1) == result.trunkItems.end()) {
                    result.trunkItems.push_back(item1);
                }
                break;
            }
        }
    }

    result.model = other.model;
    return result;
}

std::string Car::getBrand() const {return brand;}
std::string Car::getModel() const {return model;}
std::string Car::getPlateNumber() const {return plateNumber;}
std::vector<std::string> Car::getTrunkItems() const {return trunkItems;}

void Car::setPlateNumber(const std::string& plate) {
    if (isValidPlateNumber(plate)) {
        plateNumber = plate;
        std::cout << "Государственный номер изменен на: " << plate << std::endl;
    }
    else {
        std::cout << "Ошибка. Невалидный государственный номер" << std::endl;
    }
}

void Car::addItemToTrunk(const std::string& item) {
    trunkItems.push_back(item);
    std::cout << "Вещь " << item << " добавлена в багажник" << std::endl;
}

void Car::removeItemFromTrunk(const std::string& item) {
    auto it = std::find(trunkItems.begin(), trunkItems.end(), item);
    if (it != trunkItems.end()) {
        trunkItems.erase(it);
        std::cout << "Вещь " << item << " удалена из багажника" << std::endl;
    }
    else {
        std::cout << "Вещь " << item << " не найдена в багажнике" << std::endl;
    }
}

void Car::clearTrunk() {
    trunkItems.clear();
    std::cout << "Багажник очищен" << std::endl;
}

void Car::viewInfo() const {
    std::cout << "=== ИНФОРМАЦИЯ ===" << std::endl;
    std::cout << "Марка: " << brand << std::endl;
    std::cout << "Модель: " << model << std::endl;
    std::cout << "Государственный номер: " << plateNumber << std::endl;
    std::cout << "Вещи в багажнике (" << trunkItems.size() << "): ";
    if (trunkItems.empty()) {
        std::cout << "Ничего нет";
    }
    else {
        std::cout << "[";
        for (size_t i = 0; i  < trunkItems.size(); i++) {
            std::cout << trunkItems[i];
            if (i < trunkItems.size() - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
    std::cout << "==================" << std::endl;
}

bool Car::isValidPlateNumber(const std::string& plate) const {
    if (plate.length() != 6) return false;
    if (plate[0] < 'А' || plate[0] > 'Я') return false;
    for (int i = 1; i <= 3; i++) {
        if (plate[i] < '0' || plate[i] > '9') return false;
    }
    if (plate[4] < 'А' || plate[4] > 'Я') return false;
    if (plate[5] < 'А' || plate[5] > 'Я') return false;
    return true;
}

std::string Car::generateRandomPlateNumber() const {
    std::string plate;
    plate += static_cast<char>('А' + getRandomNumber(0, 32));
    plate += std::to_string(getRandomNumber(0, 9));
    plate += std::to_string(getRandomNumber(0, 9));
    plate += std::to_string(getRandomNumber(0, 9));
    plate += static_cast<char>('А' + getRandomNumber(0, 32));
    plate += static_cast<char>('А' + getRandomNumber(0, 32));
    if (plate == plateNumber) {
        return generateRandomPlateNumber();
    }
    return plate;
}