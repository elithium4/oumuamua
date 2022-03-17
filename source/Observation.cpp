#include "Observation.h"    

Date Observation::get_julian_date() {
    return julian_date;
}

std::string Observation::get_code() {
    return code;
}

CelestialCoord Observation::get_ascension() {
    return ascension;
}

CelestialCoord Observation::get_declination() {
    return declination;
}

void Observation::set_julian_date(Date value) {
    julian_date = value;
}

void Observation::set_code(std::string value) {
    code = value;
}

void Observation::set_ascension(CelestialCoord value) {
    ascension = value;
}

void Observation::set_declination(CelestialCoord value) {
    declination = value;
}

void Observation::set_ascension_from_string(std::string value) {
    ascension.set_from_string(value);
}

void Observation::set_declination_from_string(std::string value) {
    declination.set_from_string(value);
}