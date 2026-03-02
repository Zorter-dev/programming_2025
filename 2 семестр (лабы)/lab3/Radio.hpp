#pragma once

#include <iostream>
#include <string>

class Radio {
private:
    std::string brand;
    std::string model;
    std::string description;
    double price;

public:
    Radio();
    Radio(const std::string& br, const std::string& mdl, const std::string& desc, double pr);
    Radio(const Radio& other);

    ~Radio();

    Radio& operator=(const Radio& other);

    std::string getBrand() const;
    std::string getModel() const;
    std::string getDescription() const;
    double getPrice() const;

    void setBrand(const std::string& br);
    void setModel(const std::string& mdl);
    void setDescription(const std::string& desc);
    void setPrice(double pr);

    void viewInfo() const;
};