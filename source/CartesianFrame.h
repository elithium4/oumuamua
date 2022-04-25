#pragma once
#include <cstddef>
#include <string>


//Класс декартовых координат относительно центра Земли
class CartesianFrame {
private:
    double x = NULL;
    double y = NULL;
    double z = NULL;
public:
    CartesianFrame() {};
    void set_from_string(std::string);
    double get_x();
    double get_y();
    double get_z();
    void set_x(double value);
    void set_y(double value);
    void set_z(double value);

    CartesianFrame(const CartesianFrame& other);
    CartesianFrame& operator=(const CartesianFrame& other);
    CartesianFrame(const CartesianFrame&& other);
    CartesianFrame& operator=(const CartesianFrame&& other);
};