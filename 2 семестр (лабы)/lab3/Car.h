#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Radio.hpp"

class Car {
private:
    std::string brand;
    std::string model;
    std::string chassisNumber;
    std::string plateNumber;
    int mileage;
    std::vector<std::string> trunkItems;
    Radio* installedRadio;

public:
    Car();
    Car(const std::string& br, const std::string& mdl, const std::string& chassis, const std::string& plate, int mil, const std::vector<std::string>& items);
    Car(const Car& other);

    ~Car();

    Car& operator=(const Car& other);

    Car operator+(const Car& other) const;
    Car operator-(const Car& other) const;
    Car operator/(const Car& other) const;

    std::string getBrand() const;
    std::string getModel() const;
    std::string getChassisNumber() const;
    std::string getPlateNumber() const;
    int getMileage() const;
    std::vector<std::string> getTrunkItems() const;
    Radio* getInstalledRadio() const;

    void setBrand(const std::string& br);
    void setModel(const std::string& mdl);
    void setChassisNumber(const std::string& chassis);
    void setPlateNumber(const std::string& plate);
    void setMileage(int mil);
    void setTrunkItems(const std::vector<std::string>& items);

    void installRadio(Radio* radio);
    void removeRadio();

    void addItemToTrunk(const std::string& item);
    void removeItemFromTrunk(const std::string& item);
    void clearTrunk();
    void rollbackMileage(int reduction);

    void viewInfo() const;

private:
    bool isValidPlateNumber(const std::string& plate) const;
    std::string generateRandomPlateNumber(const Car& other) const;
};
