#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Car.h"
#include "Radio.hpp"

class AutoWorkshop {
private:
    std::string address;
    std::vector<Radio> availableRadios;
    std::vector<Car*> attachedCars;
public:
    AutoWorkshop();
    AutoWorkshop(const std::string& addr);
    AutoWorkshop(const AutoWorkshop& other);

    ~AutoWorkshop();

    AutoWorkshop& operator=(const AutoWorkshop& other);

    std::string getAddres() const;
    std::vector<Radio> getAvailableRadios() const;
    std::vector<Car*> getAttachedCars() const;

    void setAddress(const std::string& addr);

    void addRadio(const Radio& radio);
    bool removeRadio(const std::string &brand, const std::string &model);
    Radio* findRadio(const std::string& brand, const std::string& model);

    bool attachCar(Car* car);
    bool detachCar(const std::string& plateNumber);
    Car* findCarByPlate(const std::string& palteNumber);
    bool attachRadioToCar(const std::string& palteNumebr, const std::string& radioBrand, const std::string& radioModel);

    void viewInfo() const;
    void viewAttachedCars() const;
    void viewAvailableRadios() const;
};