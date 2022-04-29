#pragma once
#include <cstddef>
#include <string>

//Класс геоцентрических координат
class GeocentricFrame{
    private:
        double x = NULL;
        double y = NULL;
        double z = NULL;
    public:
        GeocentricFrame() {};
        void set_from_string(std::string);
        double get_x();
        double get_y();
        double get_z();
        void set_x(double value);
        void set_y(double value);
        void set_z(double value);
        GeocentricFrame(const GeocentricFrame& other);
        GeocentricFrame& operator=(const GeocentricFrame& other);
        GeocentricFrame(const GeocentricFrame&& other);
        GeocentricFrame& operator=(const GeocentricFrame&& other);
};