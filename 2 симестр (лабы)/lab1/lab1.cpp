#include <iostream>

class Car {
private:
    std::string brand;
    std::string model;
    std::string bodyNumber;
    std::string plateNumber;
    int mileage;

public:
    Car(): brand("Unknown"), model("Unknown"), bodyNumber("Unknown"), plateNumber("Unknown"), mileage(1) {
        std::cout << "Конструктор по умолчанию вызван" << std::endl;
    }

    Car(std::string br, std::string mdl, std::string body, std::string plate, int mil): brand(br), model(mdl), bodyNumber(body), plateNumber(plate) {
        std::cout << "Конструктор полного заполнения вызван" << std::endl;

        if (!isValidPlateNumber(plateNumber)) {
            std::cout << "Невалидный государственный номер. Установлен 'Unknown'." << std::endl;
            plateNumber = "Unknown";
        }
    }

    Car(const Car& other): brand(other.brand), model(other.model), bodyNumber(other.bodyNumber), plateNumber(other.plateNumber), mileage(other.mileage) {
        std::cout << "Конструктор копирования вызван" << std::endl;
    }

    ~Car() {
        std::cout << "Деструктор вызван" << std::endl;
    }

    // ГЕТТЕРЫ

    std::string getBrand() const {return brand;}
    std::string getModel() const {return model;}
    std::string getBodyNumber() const {return bodyNumber;}
    std::string getPlateNumber() const {return plateNumber;}
    int getMileage() const {return mileage;}

    // СЕТТЕРЫ

    void setPlateNumber(const std::string& plate) {
        if (isValidPlateNumber(plate)) {
            plateNumber = plate;
            std::cout << "Государственный номер изменен на: " << plate << std::endl;
        }
        else {
            std::cout << "Ошибка. Невалидный государственный номер." << std::endl;
        }
    }

    void setBodyNumber(const std::string& body) {
        if (body.length() >= 5 && body.length() <= 17) {
            bodyNumber = body;
            std::cout << "Номер кузова успешно изменен на: " << body << std::endl;
        }
        else {
            std::cout << "Ошибка. Номер кузова должен содержать от 5 до 17 символов." << std::endl;
        }
    }

    void viewInfo() const {
        std::cout << "=== ИНФОРМАЦИЯ ===" << std::endl;
        std::cout << "Марка: " << brand << std::endl;
        std::cout << "Модель: " << model << std::endl;
        std::cout << "Номер кузова: " << bodyNumber << std::endl;
        std::cout << "Государственный номер: " << plateNumber << std::endl;
        std::cout << "Пробег: " << mileage << "км" << std::endl;
        std::cout << "==================" << std::endl;
    }

    void rollbackMileage() {
        int reduction = 1000;
        if (mileage > reduction) {
            mileage -= reduction;
            std::cout << "Пробег уменьшен на 1000км. " << "Новый пробег: " << mileage << "км" << std::endl; 
        }
        else {
            std::cout << "Ошибка. Пробег слишком маленький." << std::endl;
        }
    }

    void rollbackMileage(int reduction) {
        if (reduction > 0) {

            if (mileage > reduction) {
            mileage -= reduction;
            std::cout << "Пробег уменьшен на " << reduction << ". Новый пробег: " << mileage << "км" << std::endl; 
            }
            else {
            std::cout << "Ошибка. Пробег слишком маленький." << std::endl;
            }
        }
        else {
            std::cout << "Ошибка. Значение уменьшения должно быть положительным." << std::endl;
        }
    }

private:
    bool isValidPlateNumber(const std::string& plate) const {
        if (plate.length() != 6) {
            return false;
        }

        if (plate[0] < 'A' || plate[0] > 'Я') {
            return false;
        }

        for (int i = 1; i <= 3; i++) {
            if (plate[i] < '0' || plate[i] > '9') {
                return false;
            }
        }

        if (plate[4] < 'А' || plate[4] > 'Я') {
            return false;
        }
        if (plate[5] < 'А' || plate[5] > 'Я') {
            return false;
        }

        return true;
    }
};

int main() {

    std::cout << "ДЕМОНСТРАЦИЯ КЛАССА CAR" << std::endl;

    // 1. Создание объектов разными конструкторами
    std::cout << "1. Создание автомобилей:" << std::endl;
    Car car1;
    Car car2("Toyota", "Camry", "JTNBE46KX00123456", "В777ВВ", 15000);
    Car car3(car2);

    // 2. Вывод информации
    std::cout << "Информация об автомобилях:" << std::endl;
    car1.viewInfo();
    car2.viewInfo();
    car3.viewInfo();

    // 3. Тестирование геттеров
    std::cout << "Тестирование геттеров:" << std::endl;
    std::cout << "car2 Марка: " << car2.getBrand() << std::endl;
    std::cout << "car2 Модель: " << car2.getModel() << std::endl;
    std::cout << "car2 Пробег: " << car2.getMileage() << "км" << std::endl;

    // 4. Тестирвоание сеттеров
    std::cout << "Тестирование сеттеров" << std::endl;

    std::cout << "Установка номера 'А123АА' для car1" << std::endl;
    car1.setPlateNumber("А123АА");

    std::cout << "Установка номера 'АААААА' для car1" << std::endl;
    car1.setPlateNumber("АААААА");

    std::cout << "Установка номера кузова для car1" << std::endl;
    car1.setBodyNumber("VIN12345678901234");

    // 5. Тестирование скручивания пробега
    std::cout << "Тестирование скручивания пробега:" << std::endl;

    std::cout << "Скручивание без параметра (на 1000км):" << std::endl;
    car2.rollbackMileage();

    std::cout << "Скручивание с параметром (на 5000км)" << std::endl;
    car2.rollbackMileage(5000);

    std::cout << "=== КОНЕЦ ПРОГРАММЫ (деструкторы) ===" << std::endl;

    return 0;
}