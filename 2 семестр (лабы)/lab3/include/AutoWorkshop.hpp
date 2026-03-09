#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Radio.hpp"
class Car;

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

    bool hasRadio(const Radio& radio);
    bool addRadio(const Radio& radio);
    bool removeRadio(const Radio& radio);
    Radio* findRadio(const Radio& radio);

    bool attachCar(Car* car);
    bool detachCar(const std::string& plateNumber);
    Car* findCarByPlate(const std::string& plateNumber);
    bool attachRadioToCar(const std::string& plateNumebr, const Radio& radio);

    void viewInfo() const;
    void viewAttachedCars() const;
    void viewAvailableRadios() const;
};