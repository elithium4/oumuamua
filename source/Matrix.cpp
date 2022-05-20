#include "Matrix.h"
#include <iostream>

Matrix::Matrix(int n, int m){
    mtr = new double* [n];
    for (int i = 0; i < n; i++){
        mtr[i] = new double[m];
    }
}

Matrix::Matrix(int n, int m, std::vector<std::vector<double>> filler){
    mtr = new double* [n];
    for (int i = 0; i < n; i++){
        mtr[i] = new double[m];
    }
    
    if (n == filler.size()){
        for (int i = 0; i < n; i++){
            if (filler[i].size() == m){
                for (int j = 0; j < m; j++){
                    mtr[i][j] = filler[i][j];
                }
            } else {
                throw std::invalid_argument("Inner vector size doesn't match\n");
                return;
            }
        }
        this->n = n;
        this->m = m;
    } else {
        throw std::invalid_argument("Vector size doesn't match\n");
    }
}

Matrix::Row Matrix::operator[](int i) const{
    return Row(mtr[i]);
}

Matrix::~Matrix(){
    if (mtr != nullptr){
        for (int i = 0; i < n; i++){
            delete[] mtr[i];
        }
    }
}

bool Matrix::is_empty(){
    return mtr == nullptr;
}

int Matrix::rows() const{
    return n;
}

int Matrix::columns() const{
    return m;
}


std::ostream& operator<<(std::ostream& strm, Matrix& mtr)
{
    for (int i = 0; i < mtr.rows(); i++){
        for (int j = 0; j < mtr.columns(); j++){
            strm<<mtr[i][j]<<" ";
        }
        strm<<"\n";
    }
    return strm;
}