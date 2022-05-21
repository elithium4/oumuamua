#pragma once
#include "Date.h"
#include "Matrix.h"
#include "IntegrationVector.h"

class StateVector {
private:
    IntegrationVector state;
    Matrix dX_dX0 = Matrix(6, 6);
    Matrix dF_dX = Matrix(6, 6);
    Matrix dG_dX = Matrix(6, 2);
public:
    StateVector() {};

    StateVector(const StateVector& other);
    StateVector& operator=(const StateVector& other);
    StateVector(const StateVector&& other);
    StateVector& operator=(const StateVector&& other);
    void set_state(IntegrationVector);
    void set_dX_dX0(Matrix);
    void set_dF_dX(Matrix);
    void set_dG_dX(Matrix);
    IntegrationVector get_state();
    Matrix get_dX_dX0();
    Matrix get_dF_dX();
    Matrix get_dG_dX();

};