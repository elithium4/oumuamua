#pragma once
#include "Date.h"
#include "Matrix.h"
#include "IntegrationVector.h"

class StateVector {
private:
    IntegrationVector state;
    Matrix dX_dX0 = Matrix(6, 6);
    Matrix dF_dX = Matrix(6, 6);
    Matrix dg_dX = Matrix(6, 2);
    Matrix dF_dX0 = Matrix(6, 6);
    Matrix dR_dX0 = Matrix(6, 1);
public:
    StateVector() {};

    StateVector(const StateVector& other);
    StateVector& operator=(const StateVector& other);
    StateVector(const StateVector&& other);
    StateVector& operator=(const StateVector&& other);

    friend StateVector operator*(double k, StateVector vec);
    friend StateVector operator+(StateVector v1, StateVector v2);

    void set_state(IntegrationVector);
    void set_dX_dX0(Matrix);
    void set_dF_dX(Matrix);
    void set_dg_dX(Matrix);
    void set_dF_dX0(Matrix);
    void set_dR_dX0(Matrix);

    IntegrationVector get_state();
    Matrix* get_dX_dX0();
    Matrix* get_dF_dX();
    Matrix get_dg_dX();
    Matrix get_dF_dX0();
    Matrix get_dR_dX0();
};