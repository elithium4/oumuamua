#pragma once
#include <cstddef>

class ObservatoryCartesianFrame {
private:
    double x = NULL;
    double y = NULL;
    double z = NULL;
public:
    double get_x();
    double get_y();
    double get_z();
    void set_x(double value);
    void set_y(double value);
    void set_z(double value);
};