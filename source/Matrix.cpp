#include "Matrix.h"
#include <iostream>

Matrix::Matrix(int n, int m){
    mtr = new double* [n];
    this->n = n;
    this->m = m;
    for (int i = 0; i < n; i++){
        mtr[i] = new double[m];
        for (int j = 0; j < m; j++){
            mtr[i][j] = 0;
        }
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

Matrix::Matrix(const Matrix& other){
    if ((this->n != other.n) or (this->m != other.m)){
        for (int i = 0; i < this->n; i++){
            delete mtr[i];
        }
        mtr = new double*[other.n];
        for (int i = 0; i < other.n; i++){
            mtr[i] = new double[other.m];
        }
    }

    this->n = other.n;
    this->m = other.m;


    for (int i = 0; i < this->n; i++){
        for (int j = 0; j < this->m; j++){
            mtr[i][j] = other[i][j];
        }
    }
}

Matrix& Matrix::operator=(const Matrix& other){
    if ((this->n != other.n) or (this->m != other.m)){
        for (int i = 0; i < this->n; i++){
            delete mtr[i];
        }
        mtr = new double*[other.n];
        for (int i = 0; i < other.n; i++){
            mtr[i] = new double[other.m];
        }
    }

    this->n = other.n;
    this->m = other.m;

    for (int i = 0; i < this->n; i++){
        for (int j = 0; j < this->m; j++){
            mtr[i][j] = other[i][j];
        }
    }
    return *this;
}

Matrix::Matrix(const Matrix&& other){
        if ((this->n != other.n) or (this->m != other.m)){
        for (int i = 0; i < this->n; i++){
            delete mtr[i];
        }
        mtr = new double*[other.n];
        for (int i = 0; i < other.n; i++){
            mtr[i] = new double[other.m];
        }
    }

    this->n = other.n;
    this->m = other.m;

    for (int i = 0; i < this->n; i++){
        for (int j = 0; j < this->m; j++){
            mtr[i][j] = other[i][j];
        }
    }
}

Matrix& Matrix::operator=(const Matrix&& other){
        if ((this->n != other.n) or (this->m != other.m)){
        for (int i = 0; i < this->n; i++){
            delete mtr[i];
        }
        mtr = new double*[other.n];
        for (int i = 0; i < other.n; i++){
            mtr[i] = new double[other.m];
        }
    }

    this->n = other.n;
    this->m = other.m;

    for (int i = 0; i < this->n; i++){
        for (int j = 0; j < this->m; j++){
            mtr[i][j] = other[i][j];
        }
    }
    return *this;
}


Matrix::Row Matrix::operator[](int i) const{
    return Row(mtr[i]);
}


Matrix operator+(Matrix const A, Matrix const B){
    if ((A.columns() != B.columns()) or (A.rows() != B.rows())){
        throw std::invalid_argument("Different matrix size\n");
        return Matrix(1,1);
    }

    Matrix C(A.rows(), A.columns());

    for (int i = 0; i < A.rows(); i++){
        for (int j = 0; j < A.columns(); j++){
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

Matrix operator-(Matrix const A, Matrix const B){
    if ((A.columns() != B.columns()) or (A.rows() != B.rows())){
        throw std::invalid_argument("Diffferent matrix size\n");
        return Matrix(1,1);
    }

    Matrix C(A.rows(), A.columns());

    for (int i = 0; i < A.rows(); i++){
        for (int j = 0; j < A.columns(); j++){
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

Matrix operator*(Matrix const A, Matrix const B){
    if (A.columns() != B.rows()){
        return Matrix(1,1);
    }

    Matrix C(A.rows(), B.columns());

    for (int i = 0; i < A.rows(); i++){
        for (int j = 0; j < B.columns(); j++){
            for (int k = 0; k < B.rows(); k++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

Matrix operator*(double const k, Matrix const A){
    Matrix C(A.n, A.m);
    for (int i = 0; i < A.n; i++){
        for (int j = 0; j < A.m; j++){
            C[i][j] = A[i][j]*k;
        }
    }
    return C;
}

Matrix operator*(Matrix const A, double const k){
    Matrix C(A.n, A.m);
    for (int i = 0; i < A.n; i++){
        for (int j = 0; j < A.m; j++){
            C[i][j] = A[i][j]*k;
        }
    }
    return C;
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


std::ostream& operator<<(std::ostream& strm, Matrix mtr)
{
    for (int i = 0; i < mtr.rows(); i++){
        for (int j = 0; j < mtr.columns(); j++){
            
            strm<<mtr[i][j]<<" ";
        }
        strm<<"\n";
    }
    return strm;
}

void Matrix::make_unit(){
    int k = std::min(n, m);
    for (int i = 0; i < k; i++){
        for (int j = 0; j < k; j++){
            if (i == j){
                mtr[i][j] = 1;
            } else {
                mtr[i][j] = 0;
            }
        }
    }
}

Matrix Matrix::transpose(){
    Matrix result(m, n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            result[j][i] = mtr[i][j];
        }
    }
    return result;
}