#include "GeocentricFrame.h"

double GeocentricFrame::get_x() {
        return x;
}

double GeocentricFrame::get_y() {
    return y;
}

double GeocentricFrame::get_z() {
    return z;
}

void GeocentricFrame::set_x(double value) {
    x = value;
}

void GeocentricFrame::set_y(double value) {
    y = value;
}

void GeocentricFrame::set_z(double value) {
    z = value;
}

GeocentricFrame::GeocentricFrame(const GeocentricFrame & other){
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
}

GeocentricFrame& GeocentricFrame::operator=(const GeocentricFrame & other){
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    
    return *this;
}

GeocentricFrame::GeocentricFrame(const GeocentricFrame && other){
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
}

GeocentricFrame& GeocentricFrame::operator=(const GeocentricFrame&& other){
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    
    return *this;
}