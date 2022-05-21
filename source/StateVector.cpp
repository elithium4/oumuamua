#include "StateVector.h"

StateVector::StateVector(const StateVector & other){
	this->dX_dX0 = other.dX_dX0;
    this->dF_dX = other.dF_dX;
    this->dG_dX = other.dG_dX;
    this->state = other.state;
}

StateVector& StateVector::operator=(const StateVector & other){
	this->dX_dX0 = other.dX_dX0;
    this->dF_dX = other.dF_dX;
    this->dG_dX = other.dG_dX;
    this->state = other.state;
    return *this;
}

StateVector::StateVector(const StateVector && other){
	this->dX_dX0 = other.dX_dX0;
    this->dF_dX = other.dF_dX;
    this->dG_dX = other.dG_dX;
    this->state = other.state;
}

StateVector& StateVector::operator=(const StateVector&& other){
	this->dX_dX0 = other.dX_dX0;
    this->dF_dX = other.dF_dX;
    this->dG_dX = other.dG_dX;
    this->state = other.state;
    
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
void StateVector::set_dG_dX(Matrix other) {
	dG_dX = other;
}

IntegrationVector StateVector::get_state() {
    return state;
}

Matrix StateVector::get_dX_dX0() {
	return dX_dX0;
}

Matrix StateVector::get_dF_dX() {
	return dF_dX;
}

Matrix StateVector::get_dG_dX() {
	return dG_dX;
}