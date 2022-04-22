#include "SphericalFrame.h"

void SphericalFrame::set_longitude(double longitude){
    this->longitude = longitude;
}

void SphericalFrame::set_latitude(double latitude){
    this->latitude = latitude;
}

double SphericalFrame::get_longitude(){
    return longitude;
}

double SphericalFrame::get_latitude(){
    return latitude;
}