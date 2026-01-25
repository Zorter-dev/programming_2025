#include <iostream>

// 1 принцип - Абстракция
// 2 принцип - Инкапсулляция
// x, y
// struct - хранение
// class - хранение, описание поведения

class Car {
public:
    /*Car () {
        std::cerr << "ctor" << std::endl;
    }
    ~Car () {
        std::cerr << "dtor" << std::endl;
    }*/
        // Метод
        void move() {
        x_ += 10;
        y_ += 10;
    }

    // сеттер
    void set_r(float r) {
        if (r < 0.01) {
            throw std::invalid_argument("Radius have to be positive");
        }
        r_ = r;
    }
private:
    int x_; // Поле 
    int y_;
    float r_;

};

int main() {
    try {
        Car car; // объект экземпляр
        std::cerr << "===" << std::endl;
        car.set_r(-10.0f);
        car.set_r(1);
        std::cerr << "===" << std::endl;
    } catch(const std::invalid_argument& ex) {
        std::cerr << ex.what() << std::endl;
    }
    
    /*int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int y2 = 0;
    move(x1, y1);
    move(x2, y2);*/
}