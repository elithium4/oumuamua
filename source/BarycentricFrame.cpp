#include "BarycentricFrame.h"

double BarycentricFrame::get_x() {
    return x;
}

double BarycentricFrame::get_y() {
    return y;
}

double BarycentricFrame::get_z() {
    return z;
}

void BarycentricFrame::set_x(double value) {
    x = value;
}

void BarycentricFrame::set_y(double value) {
    y = value;
}

void BarycentricFrame::set_z(double value) {
    z = value;
}

void BarycentricFrame::increase(double delta){
    x += delta;
    y += delta;
    z += delta;
}

void BarycentricFrame::multiply(double delta){
    x *= delta;
    y *= delta;
    z *= delta;
}

double BarycentricFrame::len() {
    return sqrt(x * x + y * y + z * z);
}



BarycentricFrame::BarycentricFrame(const BarycentricFrame & other){
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
}

BarycentricFrame& BarycentricFrame::operator=(const BarycentricFrame & other){
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    
    return *this;
}

BarycentricFrame::BarycentricFrame(const BarycentricFrame && other){
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
}

BarycentricFrame& BarycentricFrame::operator=(const BarycentricFrame&& other){
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    
    return *this;
}

BarycentricFrame operator+(BarycentricFrame frame_1, BarycentricFrame frame_2){
    BarycentricFrame result;
    result.x = frame_1.x + frame_2.x;
    result.y = frame_1.y + frame_2.y;
    result.z = frame_1.z + frame_2.z;
    return result;
}

BarycentricFrame operator-(BarycentricFrame frame_1, BarycentricFrame frame_2) {
    BarycentricFrame result;
    result.x = frame_1.x - frame_2.x;
    result.y = frame_1.y - frame_2.y;
    result.z = frame_1.z - frame_2.z;
    return result;
}

BarycentricFrame operator*(const double& m, BarycentricFrame frame) {
    BarycentricFrame result;
    result.x = m * frame.x;
    result.y = m * frame.y;
    result.z = m * frame.z;
    return result;
}

BarycentricFrame operator*(BarycentricFrame frame, const double& m) {
    BarycentricFrame result;
    result.x = m * frame.x;
    result.y = m * frame.y;
    result.z = m * frame.z;
    return result;
}

BarycentricFrame operator/(BarycentricFrame frame_1, BarycentricFrame frame_2) {
    BarycentricFrame result;
    result.x = frame_1.x / frame_2.x;
    result.y = frame_1.y / frame_2.y;
    result.z = frame_1.z / frame_2.z;
    return result;
}

BarycentricFrame operator/(BarycentricFrame frame, const double& m) {
    BarycentricFrame result;
    result.x = frame.x / m;
    result.y = frame.y / m;
    result.z = frame.z / m;
    return result;
}