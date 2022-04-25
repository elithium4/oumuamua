#include "CartesianFrame.h"

void CartesianFrame::set_from_string(std::string coord){
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

double CartesianFrame::get_x() {
        return x;
}

double CartesianFrame::get_y() {
    return y;
}

double CartesianFrame::get_z() {
    return z;
}

void CartesianFrame::set_x(double value) {
    x = value;
}

void CartesianFrame::set_y(double value) {
    y = value;
}

void CartesianFrame::set_z(double value) {
    z = value;
}

CartesianFrame::CartesianFrame(const CartesianFrame & other){
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
}

CartesianFrame& CartesianFrame::operator=(const CartesianFrame & other){
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    
    return *this;
}

CartesianFrame::CartesianFrame(const CartesianFrame && other){
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
}

CartesianFrame& CartesianFrame::operator=(const CartesianFrame&& other){
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    
    return *this;
}