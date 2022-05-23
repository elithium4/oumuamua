#include "LeastSquares.h"
#include <iostream>

std::vector<SphericalFrame> LeastSquares::calculate_wmrs(std::vector<StateVector> model, std::vector<Observation> measure, double* long_wmrs, double* lat_mwrs){
    double wrms_longitude = 0;
    double wrms_latitude = 0;

    std::vector<SphericalFrame> result;

    for (int i = 0; i < model.size(); i++){

        SphericalFrame r_i;

        r_i.set_longitude(measure[i].get_spherical_position().get_longitude() - model[i].get_state()->get_spherical_position().get_longitude());
        r_i.set_latitude(measure[i].get_spherical_position().get_latitude() - model[i].get_state()->get_spherical_position().get_latitude());

        result.push_back(r_i);

        double var_asc = model[i].get_state()->get_spherical_position().get_longitude() - (int)model[i].get_state()->get_spherical_position().get_longitude();
        var_asc = 0.001*((int)std::trunc(var_asc*1000)%10);
        if (var_asc == 0){
            var_asc = 0.0001;
        } else {
            var_asc /= 2;
        }

        double var_dec = model[i].get_state()->get_spherical_position().get_latitude() - (int)model[i].get_state()->get_spherical_position().get_latitude();
        var_dec = 0.001*((int)std::trunc(var_dec*1000)%10);

        if (var_dec == 0){
            var_dec = 0.0001;
        } else {
            var_dec /= 2;
        }

        wrms_longitude += pow(model[i].get_state()->get_spherical_position().get_longitude() - measure[i].get_spherical_position().get_longitude(), 2) / var_asc;
        wrms_latitude += pow(model[i].get_state()->get_spherical_position().get_latitude() - measure[i].get_spherical_position().get_latitude(), 2) / var_dec; 
 
    }

    (*long_wmrs) = wrms_longitude;
    (*lat_mwrs) = wrms_latitude;

    return result;
}


IntegrationVector LeastSquares::gauss_newton(std::vector<StateVector>, std::vector<SphericalFrame>){
    
}