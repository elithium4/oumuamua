#include "ObservatoryData.h"

void ObservatoryData::set_cartesian(CartesianFrame frame){
    cartesian_frame = frame;
}

void ObservatoryData::set_cylindrical(CylindricalFrame frame){
    cylindrical_frame = frame;
}

void ObservatoryData::set_geocentric(GeocentricFrame frame){
    geocentric_frame = frame;
}

void ObservatoryData::set_barycentric(BarycentricFrame frame){
    barycentric_frame = frame;
}

CartesianFrame ObservatoryData::get_cartesian(){
    return cartesian_frame;
}

CylindricalFrame ObservatoryData::get_cylindric(){
    return cylindrical_frame;
}

GeocentricFrame ObservatoryData::get_geocentric(){
    return geocentric_frame;
}

BarycentricFrame ObservatoryData::get_barycentric(){
    return barycentric_frame;
}

ObservatoryData::ObservatoryData(const ObservatoryData & other){
    this->cartesian_frame = other.cartesian_frame;
    this->cylindrical_frame = other.cylindrical_frame;
    this->geocentric_frame = other.geocentric_frame;
    this->barycentric_frame = other.barycentric_frame;
}

ObservatoryData& ObservatoryData::operator=(const ObservatoryData & other){
    this->cartesian_frame = other.cartesian_frame;
    this->cylindrical_frame = other.cylindrical_frame;
    this->geocentric_frame = other.geocentric_frame;
    this->barycentric_frame = other.barycentric_frame;
    
    return *this;
}

ObservatoryData::ObservatoryData(const ObservatoryData && other){
    this->cartesian_frame = other.cartesian_frame;
    this->cylindrical_frame = other.cylindrical_frame;
    this->geocentric_frame = other.geocentric_frame;
    this->barycentric_frame = other.barycentric_frame;
}

ObservatoryData& ObservatoryData::operator=(const ObservatoryData&& other){
    this->cartesian_frame = other.cartesian_frame;
    this->cylindrical_frame = other.cylindrical_frame;
    this->geocentric_frame = other.geocentric_frame;
    this->barycentric_frame = other.barycentric_frame;
    
    return *this;
}