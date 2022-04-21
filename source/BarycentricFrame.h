#pragma once
#include <cstddef>

class BarycentricFrame {
private:
    double x = NULL;
    double y = NULL;
    double z = NULL;
public:
    BarycentricFrame(){};

    double get_x();
    double get_y();
    double get_z();
    void set_x(double value);
    void set_y(double value);
    void set_z(double value);

    void increase(double);
    void multiply(double);

    friend BarycentricFrame operator+(BarycentricFrame, BarycentricFrame);

    BarycentricFrame(const BarycentricFrame& other);
    BarycentricFrame& operator=(const BarycentricFrame& other);
    BarycentricFrame(const BarycentricFrame&& other);
    BarycentricFrame& operator=(const BarycentricFrame&& other);
};