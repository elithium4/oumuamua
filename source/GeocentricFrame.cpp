#include "GeocentricFrame.h"

void GeocentricFrame::set_from_string(std::string coord){
    int prev = 0;
    for (int i = 0; i < 4; i++){
        for (int j = prev; j < coord.length()+1; j++){
            if ((coord[j] == ' ') or (coord[j] == '\0')){
                switch (i){
                    case 0:
                        x = std::stod(coord.substr(prev, j-prev));
                        break;
                    case 1:
                        y = std::stod(coord.substr(prev, j-prev));
                        break;
                    case 2:
                        z = std::stod(coord.substr(prev, j-prev));
                        break;
                    default:
                        break;
                }
                prev = j+1;
                break;
            }
        }
    }
}

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

double GeocentricFrame::len() {
    return sqrt(x * x + y * y + z * z);
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