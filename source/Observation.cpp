#include "Observation.h"

Date* Observation::get_julian_date() {
    return &julian_date;
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

#include <iostream>

void Observation::set_ascension_from_string(std::string value) {
    ascension.set_from_string(value);
    int dot_pos = value.find(".");
    for (int i = dot_pos + 1; i < value.length() + 1; i++){
        if ((value[i] == '\0') or (value[i] == ' ')){
            asc_var = pow(0.1, i-dot_pos-1) * 15.0 / 2.0;
            //asc_var = (asc_var * 15.0);// * M_PI/648000;
            //asc_var = pow(asc_var, 2);
            break;
        }
    }
}

void Observation::set_declination_from_string(std::string value) {
    declination.set_from_string(value);
    int dot_pos = value.find(".");
    for (int i = dot_pos + 1; i < value.length() + 1; i++){
        if ((value[i] == '\0') or (value[i] == ' ')){
            dec_var = pow(0.1, i-dot_pos-1) / 2.0;
            //dec_var = dec_var * M_PI/648000;
            //dec_var =pow(dec_var, 2);
            break;
        }
    }
}

void Observation::set_spherical(double longitude, double latitude){
    spherical_position.set_declination(latitude);
    spherical_position.set_ascension(longitude);
}

void Observation::set_barycentric(double x, double y, double z) {
    barycentric_position.set_x(x);
    barycentric_position.set_y(y);
    barycentric_position.set_z(z);
}

void Observation::set_geocentric(double x, double y, double z) {
    geocentric_position.set_x(x);
    geocentric_position.set_y(y);
    geocentric_position.set_z(z);
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

SphericalFrame Observation::get_spherical_position(){
    return spherical_position;
}

GeocentricFrame Observation::get_geocentric() {
    return geocentric_position;
}

BarycentricFrame Observation::get_barycentric() {
    return barycentric_position;
}

double Observation::get_asc_var(){
    return asc_var;
}

double Observation::get_dec_var(){
    return dec_var;
}