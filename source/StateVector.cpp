#include "StateVector.h"

void StateVector::set_dX_dX0(Matrix other) {
	dX_dX0 = other;
}

void StateVector::set_dF_dX(Matrix other) {
	dF_dX = other;
}
void StateVector::set_dG_dX(Matrix other) {
	dG_dX = other;
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