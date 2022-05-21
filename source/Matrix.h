#pragma once
#include <vector>
#include <ostream>

class Matrix{
	private:
		class Row{
			private:
				double* row;
			public:
				Row(double* row){
                	this->row = row;
            	};
				double& operator[](int j){
                	return row[j];
            	};
				const double& operator[](int j) const{
					return row[j];
				}
		};
		int n = 0;
		int m = 0;
		double** mtr = nullptr;
	public:
		Matrix(int n, int m);
        Matrix(int n, int m, std::vector<std::vector<double>>);

		Matrix(const Matrix& other);
    	Matrix& operator=(const Matrix& other);
    	Matrix(const Matrix&& other);
    	Matrix& operator=(const Matrix&& other);


        Row operator[](int i) const;
		
		Matrix transpose(Matrix& A);
		friend Matrix operator+(Matrix& A, Matrix& B);
		friend Matrix operator-(Matrix& A, Matrix& B);
		friend Matrix operator*(Matrix& A, Matrix& B);
		~Matrix();

        int rows() const;
        int columns() const;
        bool is_empty();
};

std::ostream& operator<<(std::ostream& strm, Matrix& mtr);
