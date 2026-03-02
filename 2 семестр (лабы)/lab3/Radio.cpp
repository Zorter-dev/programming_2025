#include "Radio.hpp"

Radio::Radio(): brand("Unknown"), model("Unknown"), description("Нет описания"), price(0.0) {
    std::cout << "Конструктор по умолчанию вызван" << std::endl;
}

Radio::Radio(const std::string& br, const std::string& mdl, const std::string& desc, double pr): brand(br), model(mdl), description(desc), price(pr) {
    std::cout << "Конструктор полного заполнения вызван" << std::endl;
}

Radio::Radio(const Radio& other): brand(other.brand), model(other.model), description(other.description), price(other.price) {
    std::cout << "Интсруктор копирования вызван" << std::endl;
}

Radio::~Radio() {
    std::cout << "Деструктор вызван" << std::endl;
}

Radio& Radio::operator=(const Radio& other) {
    std::cout << "Оператор присваивания вызван" << std::endl;
    if (this != &other) {
        brand = other.brand;
        model = other.model;
        description = other.description;
        price = other.price;
    }
    return *this;
}

std::string Radio::getBrand() const {return brand;}
std::string Radio::getModel() const {return model;}
std::string Radio::getDescription() const {return description;}
double Radio::getPrice() const {return price;}

void Radio::setBrand(const std::string& br) {brand = br;}
void Radio::setModel(const std::string& mdl) {model = mdl;}
void Radio::setDescription(const std::string& desc) {description = desc;}
void Radio::setPrice(double pr) {price = pr;}

void Radio::viewInfo() const {
    std::cout << "==== МАГНИТОЛА ====" << std::endl;
    std::cout << "Бренд: " << brand << std::endl;
    std::cout << "Модель: " << model << std::endl;
    std::cout << "Описание: " << description << std::endl;
    std::cout << "Цена: " << price << " руб." << std::endl;
    std::cout << "===================" << std::endl;
}