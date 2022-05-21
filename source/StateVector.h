#pragma once
#include "Date.h"
#include "Matrix.h"


class StateVector {
private:
    Matrix dX_dX0 = Matrix(6, 6);
    Matrix dF_dX = Matrix(6, 6);
    Matrix dG_dX = Matrix(6, 2);
public:
    StateVector() {};

    void set_dX_dX0(Matrix);
    void set_dF_dX(Matrix);
    void set_dG_dX(Matrix);
    Matrix get_dX_dX0();
    Matrix get_dF_dX();
    Matrix get_dG_dX();
};