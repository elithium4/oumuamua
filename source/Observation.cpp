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

double Observation::get_x() {
    return x;
}

double Observation::get_y() {
    return y;
}

double Observation::get_z() {
    return z;
}

void Observation::set_x(double value) {
    x = value;
}

void Observation::set_y(double value) {
    y = value;
}

void Observation::set_z(double value) {
    z = value;
}