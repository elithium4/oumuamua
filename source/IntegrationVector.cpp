#include "IntegrationVector.h"


void IntegrationVector::set_position(double x, double y, double z){
    this->position.set_x(x);
    this->position.set_y(y);
    this->position.set_z(z);
}

void IntegrationVector::set_spherical_position(double longitude, double latitude){
    this->spherical_position.set_longitude(longitude);
    this->spherical_position.set_latitude(latitude);
}

void IntegrationVector::set_geocentric_position(double x, double y, double z){
    this->geocentric_position.set_x(x);
    this->geocentric_position.set_y(y);
    this->geocentric_position.set_z(z);
}

void IntegrationVector::set_velocity(double vx, double vy, double vz){
    this->velocity.set(vx, vy, vz);
}

void IntegrationVector::set_julian_date(Date date){
    julian_date = date;
}

BarycentricFrame IntegrationVector::get_position(){
    return position;
}

GeocentricFrame IntegrationVector::get_geocentric_position(){
    return geocentric_position;
}

SphericalFrame IntegrationVector::get_spherical_position(){
    return spherical_position;
}

Velocity IntegrationVector::get_velocity(){
    return velocity;
}

Date* IntegrationVector::get_julian_date(){
    return &julian_date;
}

IntegrationVector operator+(IntegrationVector vector, double delta){
    IntegrationVector result;
    double x = vector.get_position().get_x() + delta;
    double y = vector.get_position().get_y() + delta;
    double z = vector.get_position().get_z() + delta;
    result.set_position(x, y, z);
    double vx = vector.get_velocity().get_vx() + delta;
    double vy = vector.get_velocity().get_vy() + delta;
    double vz = vector.get_velocity().get_vz() + delta;
    result.set_velocity(vx, vy, vz);
    //result.position.increase(delta);
    //result.velocity.increase(delta);
    return result;
}

IntegrationVector operator+(IntegrationVector vector, IntegrationVector delta){
    //IntegrationVector result;

    IntegrationVector result;
    /*double x = vector.get_position().get_x() + delta.get_position().get_x();
    double y = vector.get_position().get_y() + delta.get_position().get_y();
    double z = vector.get_position().get_z() + delta.get_position().get_z();
    result.set_position(x, y, z);
    double vx = vector.get_velocity().get_vx() + delta.get_velocity().get_vx();
    double vy = vector.get_velocity().get_vy() + delta.get_velocity().get_vy();
    double vz = vector.get_velocity().get_vz() + delta.get_velocity().get_vz();
    result.set_velocity(vx, vy, vz);*/

    result.position = vector.position + delta.position;
    result.velocity = vector.velocity + delta.velocity;
    return result;
}

IntegrationVector operator*(double delta, IntegrationVector vector){
    //IntegrationVector result = vector;
    IntegrationVector result;
    double x = vector.get_position().get_x() * delta;
    double y = vector.get_position().get_y() * delta;
    double z = vector.get_position().get_z() * delta;
    result.set_position(x, y, z);
    double vx = vector.get_velocity().get_vx() * delta;
    double vy = vector.get_velocity().get_vy() * delta;
    double vz = vector.get_velocity().get_vz() * delta;
    result.set_velocity(vx, vy, vz);
    return result;
}

IntegrationVector::IntegrationVector(const IntegrationVector& other){
    this->position = other.position;
    this->velocity = other.velocity;
    this->spherical_position = other.spherical_position;
    this->julian_date = other.julian_date;
    this->geocentric_position = other.geocentric_position;
}

IntegrationVector& IntegrationVector::operator=(const IntegrationVector& other){
    this->position = other.position;
    this->velocity = other.velocity;
    this->spherical_position = other.spherical_position;
    this->geocentric_position = other.geocentric_position;
    this->julian_date = other.julian_date;
    return *this;
}

IntegrationVector::IntegrationVector(const IntegrationVector&& other){
    this->position = other.position;
    this->velocity = other.velocity;
    this->spherical_position = other.spherical_position;
    this->geocentric_position = other.geocentric_position;
    this->julian_date = other.julian_date;
}

IntegrationVector& IntegrationVector::operator=(const IntegrationVector&& other){
    this->position = other.position;
    this->velocity = other.velocity;
    this->spherical_position = other.spherical_position;
    this->geocentric_position = other.geocentric_position;
    this->julian_date = other.julian_date;
    return *this;
}