#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Car {
private:
    std::string brand;
    std::string model;
    std::string plateNumber;
    std::vector<std::string> trunkItems;

public:
    Car();
    Car(const std::string& br, const std::string& mdl, const std::string& plate, const std::vector<std::string>& items);
    Car(const Car& other);

    ~Car();

    Car& operator=(const Car& other);

    Car operator+(const Car& other) const;
    Car operator-(const Car& other) const;
    Car operator/(const Car& other) const;

    std::string getBrand() const;
    std::string getModel() const;
    std::string getPlateNumber() const;
    std::vector<std::string> getTrunkItems() const;

    void setPlateNumber(const std::string& plate);

    void addItemToTrunk(const std::string& item);
    void removeItemFromTrunk(const std::string& item);
    void clearTrunk();

    void viewInfo() const;

private:
    bool isValidPlateNumber(const std::string& plate) const;
    std::string generateRandomPlateNumber(const Car& other) const;
};
