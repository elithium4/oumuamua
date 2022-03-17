#pragma once

#include "CelestialCoord.h"
#include "Date.h"

#include <string>

class Observation {
private:
    Date julian_date;
    std::string code;
    CelestialCoord ascension;
    CelestialCoord declination;
public:
    Date get_julian_date();
    std::string get_code();
    CelestialCoord get_ascension();
    CelestialCoord get_declination();
    void set_julian_date(Date value);
    void set_code(std::string value);
    void set_ascension(CelestialCoord value);
    void set_declination(CelestialCoord value);
    void set_ascension_from_string(std::string value);
    void set_declination_from_string(std::string value);
};