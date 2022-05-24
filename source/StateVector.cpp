#include "StateVector.h"

StateVector::StateVector(const StateVector & other){
	this->dX_dX0 = other.dX_dX0;
    this->dF_dX = other.dF_dX;
    this->dg_dX = other.dg_dX;
    this->state = other.state;
    this->dF_dX0 = other.dF_dX0;
    this->dR_dX0 = other.dR_dX0;
}

StateVector& StateVector::operator=(const StateVector & other){
	this->dX_dX0 = other.dX_dX0;
    this->dF_dX = other.dF_dX;
    this->dg_dX = other.dg_dX;
    this->state = other.state;
    this->dF_dX0 = other.dF_dX0;
    this->dR_dX0 = other.dR_dX0;
    return *this;
}

StateVector::StateVector(const StateVector && other){
	this->dX_dX0 = other.dX_dX0;
    this->dF_dX = other.dF_dX;
    this->dg_dX = other.dg_dX;
    this->state = other.state;
    this->dF_dX0 = other.dF_dX0;
    this->dR_dX0 = other.dR_dX0;
}

StateVector& StateVector::operator=(const StateVector&& other){
	this->dX_dX0 = other.dX_dX0;
    this->dF_dX = other.dF_dX;
    this->dg_dX = other.dg_dX;
    this->state = other.state;
    this->dF_dX0 = other.dF_dX0;
    this->dR_dX0 = other.dR_dX0;
    
    return *this;
}

void StateVector::set_state(IntegrationVector other) {
    state = other;
}

void StateVector::set_dX_dX0(Matrix other) {
	dX_dX0 = other;
}

void StateVector::set_dF_dX(Matrix other) {
	dF_dX = other;
}
void StateVector::set_dg_dX(Matrix other) {
	dg_dX = other;
}

void StateVector::set_dF_dX0(Matrix other) {
    dF_dX0 = other;
}

void StateVector::set_dR_dX0(Matrix other) {
    dR_dX0 = other;
}

IntegrationVector* StateVector::get_state() {
    return &state;
}

Matrix* StateVector::get_dX_dX0() {
	return &dX_dX0;
}

Matrix* StateVector::get_dF_dX() {
	return &dF_dX;
}

Matrix StateVector::get_dg_dX() {
	return dg_dX;
}

Matrix StateVector::get_dF_dX0() {
    return dF_dX0;
}

Matrix StateVector::get_dR_dX0() {
    return dR_dX0;
}

StateVector operator*(double k, StateVector vec){
	StateVector result;
    result.state = k*vec.state;
	result.dF_dX0 = k*vec.dF_dX0;
    result.dF_dX = k*vec.dF_dX;
	result.dg_dX = k*vec.dg_dX;
	result.dR_dX0 = k*vec.dR_dX0;
	result.dX_dX0 = k*vec.dX_dX0;
	return result;
}

/*StateVector operator*(StateVector v1, StateVector v2){
	StateVector result;
	result.dF_dX0 = v1.dF_dX0*v2.dF_dX0;
    result.dF_dX = v1.dF_dX*v2.dF_dX;
	result.dg_dX = v1.dg_dX*v2.dg_dX;
	result.dR_dX0 = v1.dR_dX0*v2.dR_dX0;
	result.dX_dX0 = v1.dX_dX0*v2.dX_dX0;
	return result;
}*/

StateVector operator+(StateVector v1, StateVector v2){
	StateVector result;
    result.state = v1.state + v2.state;
	result.dF_dX0 = v1.dF_dX0+v2.dF_dX0;
    result.dF_dX = v1.dF_dX+v2.dF_dX;
	result.dg_dX = v1.dg_dX+v2.dg_dX;
	result.dR_dX0 = v1.dR_dX0+v2.dR_dX0;
	result.dX_dX0 = v1.dX_dX0+v2.dX_dX0;
	return result;
}

void StateVector::calculate_dR_dX0(){
    dR_dX0 = (dg_dX * dX_dX0);
}