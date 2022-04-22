#include "LeastSquares.h"

void LeastSquares::calculate_wmrs(std::vector<IntegrationVector> model, std::vector<Observation> measure, double* long_wmrs, double* lat_mwrs){
    double wrms_longitude = 0;
    double wrms_latitude = 0;

    for (int i = 0; i < model.size(); i++){
        wrms_longitude += pow(model[i].get_spherical_position().get_longitude() - measure[i].get_spherical_position().get_longitude(), 2);
        wrms_latitude += pow(model[i].get_spherical_position().get_latitude() - measure[i].get_spherical_position().get_latitude(), 2);    
    }
    (*long_wmrs) = wrms_longitude;
    (*lat_mwrs) = wrms_latitude;
}
