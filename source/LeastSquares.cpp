#include "LeastSquares.h"
#include <iostream>
#include <fstream>

std::vector<SphericalFrame> LeastSquares::calculate_wmrs(std::vector<StateVector> model, std::vector<Observation> measure, double* long_wmrs, double* lat_mwrs){
    double wrms_longitude = 0;
    double wrms_latitude = 0;

    std::vector<SphericalFrame> result;

    for (int i = 0; i < model.size(); i++){

        SphericalFrame r_i;

        r_i.set_ascension(measure[i].get_spherical_position().get_ascension() - model[i].get_state()->get_spherical_position().get_ascension());
        r_i.set_declination(measure[i].get_spherical_position().get_declination() - model[i].get_state()->get_spherical_position().get_declination());

        result.push_back(r_i);

        double var_asc = model[i].get_state()->get_spherical_position().get_ascension() - (int)model[i].get_state()->get_spherical_position().get_ascension();
        var_asc = 0.001*((int)std::trunc(var_asc*1000)%10);
        if (var_asc == 0){
            var_asc = 0.0005;
        } else {
            var_asc /= 2;
        }

        double var_dec = model[i].get_state()->get_spherical_position().get_declination() - (int)model[i].get_state()->get_spherical_position().get_declination();
        var_dec = 0.001*((int)std::trunc(var_dec*1000)%10);

        if (var_dec == 0){
            var_dec = 0.0005;
        } else {
            var_dec /= 2;
        }

        wrms_longitude += pow(model[i].get_state()->get_spherical_position().get_ascension() - measure[i].get_spherical_position().get_ascension(), 2) / var_asc;
        wrms_latitude += pow(model[i].get_state()->get_spherical_position().get_declination() - measure[i].get_spherical_position().get_declination(), 2) / var_dec; 
    }

    (*long_wmrs) = wrms_longitude;
    (*lat_mwrs) = wrms_latitude;

    return result;
}


IntegrationVector LeastSquares::gauss_newton(std::vector<StateVector> model, std::vector<SphericalFrame> r){
    Matrix A(444, 6);
    Matrix W(444, 444);
    int line_id = 0;


    for (int i = 0; i < model.size(); i++){
        Matrix tmp = model[i].get_dR_dX0();
        for (int j = 0; j < tmp.columns(); j++){
            A[line_id][j] = -tmp[0][j];
            A[line_id + 1][j] = -tmp[1][j];
            W[line_id][line_id] = r[i].get_ascension();
            W[line_id + 1][line_id + 1] = r[i].get_declination();
        }
        line_id += 2;
    }

    Matrix A_t = A.transpose();
    Matrix grad_f = A_t * W * A;
    std::ofstream filee;
    filee.open("./debug/gradf.txt");
    filee<<grad_f;
    filee.close();

    Matrix L = cholesky(grad_f);
    std::cout<<"Grad f:\n";
    std::cout<<grad_f;
    std::cout<<"\nL:\n";
    std::cout<<L;
}

Matrix LeastSquares::cholesky(Matrix A){
    Matrix L(A.rows(), A.columns());

    for (int i = 0; i < A.columns(); i++) {
        for (int j = 0; j <= i; j++) {
            double sum = 0;
            if (j == i){

                for (int k = 0; k < j; k++)
                    sum += L[j][k]*L[j][k];

                L[j][j] = sqrt(A[j][j] - sum);
            } else {

                for (int k = 0; k < j; k++)
                    sum += L[i][k] * L[j][k];

                L[i][j] = (A[i][j] - sum) / L[j][j];
            }
        }
    } 
    return L;
};