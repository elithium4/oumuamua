#pragma once
#include <cstddef>
#include <string>

//Класс цилиндрических координат
class CylindricalFrame {
private:
    double longitude = NULL;
    double cos = NULL;
    double sin = NULL;
public:
    double get_longitude();
    double get_cos();
    double get_sin();

    bool is_empty(std::string value);

    void set_longitude_from_string(std::string value);
    void set_cos_from_string(std::string value);
    void set_sin_from_string(std::string value);
};