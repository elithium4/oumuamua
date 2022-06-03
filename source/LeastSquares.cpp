#include "LeastSquares.h"
#include <iostream>
#include <fstream>


std::vector<SphericalFrame> LeastSquares::calculate_wmrs(std::vector<StateVector> model, std::vector<Observation> measure, std::vector<SphericalFrame>* delta, double* ra_wmrs, double* dec_mwrs){
    double wrms_ascension = 0;
    double wrms_declination = 0;

    double asc_det = 0;
    double dec_det = 0;

    std::vector<SphericalFrame> var_i_vec;

    for (int i = 0; i < model.size(); i++){

        SphericalFrame var_i;

        var_i.set_ascension(measure[i].get_asc_var());
        var_i.set_declination(measure[i].get_dec_var());

        var_i_vec.push_back(var_i);

        SphericalFrame delta_i;

        double delta_asc = measure[i].get_spherical_position().get_ascension() - model[i].get_state()->get_spherical_position().get_ascension();
        double delta_dec = measure[i].get_spherical_position().get_declination()- model[i].get_state()->get_spherical_position().get_declination();

        while ((delta_asc > M_PI) or (delta_asc < -M_PI)){
            int sign = delta_asc > M_PI ? -1 : 1;
            delta_asc = delta_asc + sign*2*M_PI;
        }

        delta_i.set_ascension(delta_asc);
        delta_i.set_declination(delta_dec);
        delta->push_back(delta_i);


        wrms_ascension += measure[i].get_asc_var()*pow(delta_asc, 2);
        asc_det += (measure[i].get_asc_var()*measure[i].get_asc_var());
        wrms_declination += pow(delta_dec, 2)* measure[i].get_dec_var();
        dec_det += measure[i].get_dec_var(); 

        //wrms_ascension += pow(delta_asc, 2)/ (measure[i].get_asc_var()*measure[i].get_asc_var());
        //wrms_declination += pow(delta_dec, 2) / (measure[i].get_dec_var()*measure[i].get_dec_var()); 
    
    }


    //(*ra_wmrs) = wrms_ascension/222;
    //(*dec_mwrs) = wrms_declination/222;

    (*ra_wmrs) = sqrt(wrms_ascension/asc_det);
    (*dec_mwrs) = sqrt(wrms_declination/dec_det);

    return var_i_vec;
}


IntegrationVector LeastSquares::gauss_newton(std::vector<StateVector> model, std::vector<SphericalFrame> var, std::vector<SphericalFrame> r, IntegrationVector b_q){
    Matrix A(444, 6);
    Matrix W(444, 444);
    Matrix R_b(444, 1);
    int line_id = 0;


    for (int i = 0; i < model.size(); i++){
        Matrix tmp = model[i].get_dR_dX0();
        for (int j = 0; j < tmp.columns(); j++){
            A[line_id][j] = -tmp[0][j];
            A[line_id + 1][j] = -tmp[1][j];
            W[line_id][line_id] = 1.0/(var[i].get_ascension()*var[i].get_ascension());
            W[line_id + 1][line_id + 1] = 1.0/(var[i].get_declination()*var[i].get_declination());
            R_b[line_id][0] = r[i].get_ascension();
            R_b[line_id + 1][0] = r[i].get_declination();
        }
        line_id += 2;
    }


    Matrix A_t = A.transpose();
    Matrix grad_f = A_t * W * A;

    Matrix b = A_t * W * R_b;

    Matrix L = cholesky(grad_f);

    Matrix y_res = solve_lower_sle(L, b);

    Matrix L_t = L.transpose();

    Matrix x_res = solve_upper_sle(L_t, y_res);

    double x, y, z, vx, vy, vz;
    x = b_q.get_position().get_x() - x_res[0][0];
    y = b_q.get_position().get_y() - x_res[1][0];
    z = b_q.get_position().get_z() - x_res[2][0];
    vx = b_q.get_velocity().get_vx() - x_res[3][0];
    vy = b_q.get_velocity().get_vy() - x_res[4][0];
    vz = b_q.get_velocity().get_vz() - x_res[5][0];

    IntegrationVector b_next;
    b_next.set_position(x, y, z);
    b_next.set_velocity(vx, vy, vz);
    return b_next;

}

Matrix LeastSquares::cholesky(Matrix A){
    Matrix L(A.rows(), A.columns());

    for (int i = 0; i < A.columns(); i++){
        for (int j = 0; j <= i; j++){
            double sum = 0;
            if (j == i){
                for (int k = 0; k < j; k++){
                    sum += (L[j][k]*L[j][k]);
                }
                L[j][j] = sqrt(A[j][j] - sum);
            } else {
                for (int k = 0; k < j; k++){
                    sum += (L[i][k]*L[j][k]);
                }
                if (L[j][j] != 0){
                    L[i][j] = (A[i][j] - sum) / L[j][j];
                }
            }
        }
    }

    return L;
};

Matrix LeastSquares::solve_lower_sle(Matrix A, Matrix b){
    Matrix y(A.rows(), b.columns());

    for (int i = 0; i < A.rows(); i++){
        double sum = 0;
        for (int j = 0; j < i; j++){
            sum += A[i][j]*y[j][0];
        }
        if (A[i][i] == 0){
            y[i][0] = 0;
        } else {
            y[i][0] = (b[i][0] - sum)/A[i][i];
        }
    }
    return y;
}

Matrix LeastSquares::solve_upper_sle(Matrix A, Matrix b){
    Matrix y(A.rows(), b.columns());

    for (int i = A.rows()-1; i > -1; i--){
        double sum = 0;
        for (int j = i; j < A.rows(); j++){
            sum += A[i][j]*y[j][0];
        }
        if (A[i][i] == 0){
            y[i][0] = 0;
        } else {
            y[i][0] = (b[i][0] - sum)/A[i][i];
        }
    }
    return y;
}
