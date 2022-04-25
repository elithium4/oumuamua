#pragma once

#include "CelestialCoord.h"
#include "SphericalFrame.h"
#include "Date.h"

#include <string>

//Класс для хранения наблюдения
class Observation {
private:
    Date julian_date;
    std::string code;
    CelestialCoord ascension;
    CelestialCoord declination;
    SphericalFrame spherical_position;

    double x = NULL;
    double y = NULL;
    double z = NULL;
public:
    Date* get_julian_date();
    std::string get_code();
    CelestialCoord get_ascension();
    CelestialCoord get_declination();
    void set_julian_date(Date value);
    void set_code(std::string value);
    void set_ascension(CelestialCoord value);
    void set_declination(CelestialCoord value);
    void set_ascension_from_string(std::string value);
    void set_declination_from_string(std::string value);
    void set_spherical(double longitude, double latitude);

    double get_x();
    double get_y();
    double get_z();
    void set_x(double value);
    void set_y(double value);
    void set_z(double value);
    SphericalFrame get_spherical_position();
};