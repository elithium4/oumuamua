#include "InterpolationCenterEarth.h"

Date InterpolationCenterEarth::get_julian_date() {
    return julian_date;
}

double InterpolationCenterEarth::get_x() {
    return x;
}

double InterpolationCenterEarth::get_y() {
    return y;
}

double InterpolationCenterEarth::get_z() {
    return z;
}

void InterpolationCenterEarth::set_julian_date(Date value) {
    this->julian_date = value;
}

void InterpolationCenterEarth::set_x(std::string value) {
    x = is_empty(value) ? stod(value) : NULL;
}

void InterpolationCenterEarth::set_y(std::string  value) {
    y = is_empty(value) ? stod(value) : NULL;
}

void InterpolationCenterEarth::set_z(std::string  value) {
    z = is_empty(value) ? stod(value) : NULL;
}

bool InterpolationCenterEarth::is_empty(std::string value) {
    for (char c : value) {
        if (c != ' ') {
            return true;
        }
    }
    return false;
}