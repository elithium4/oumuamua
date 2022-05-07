#include "OrbitalIntegration.h"
#include <iomanip>

IntegrationVector OrbitalIntegration::diff(double t, IntegrationVector asteroid, std::map<std::string, std::vector<IntegrationVector>> planets){
    IntegrationVector d_vector;
    BarycentricFrame dx;
    BarycentricFrame dv;
    for (int i = 0; i < planets["earth"].size(); i++) {
        if (planets["earth"][i].get_julian_date()->get_MJD() == t) {
            d_vector.set_julian_date(*planets["earth"][i].get_julian_date());
            dv = (GM["sun"] * (planets["sun"][i].get_position() - asteroid.get_position()) / (pow((planets["sun"][i].get_position() - asteroid.get_position()).len(),3))) + (GM["jupiter"] * (planets["jupiter"][i].get_position() - asteroid.get_position()) / (pow((planets["jupiter"][i].get_position() - asteroid.get_position()).len(), 3)));
            break;
        }
    }
    d_vector.set_position(asteroid.get_velocity().get_vx(), asteroid.get_velocity().get_vy(), asteroid.get_velocity().get_vz());
    d_vector.set_velocity(dv.get_x(), dv.get_y(), dv.get_z());
    return d_vector;
};

std::vector<IntegrationVector> OrbitalIntegration::dormand_prince(IntegrationVector y, Date* start, Date* end, double h, std::map<std::string, std::vector<IntegrationVector>> planets){
    IntegrationVector k1, k2, k3, k4, k5, k6, k7;
    std::vector<IntegrationVector> result;

    IntegrationVector new_y = y;
    for (double t = start->get_MJD(); t <= end->get_MJD() + h; t += h){
        k1 = diff(t,  new_y, planets);
        k2 = diff(t + c2*h, new_y+h*(a21*k1), planets);
        k3 = diff(t + c3*h, new_y+h*(a31*k1+a32*k2), planets);
        k4 = diff(t + c4*h, new_y+h*(a41*k1+a42*k2+a43*k3), planets);
        k5 = diff(t + c5*h, new_y+h*(a51*k1+a52*k2+a53*k3+a54*k4), planets);
        k6 = diff(t +    h, new_y+h*(a61*k1+a62*k2+a63*k3+a64*k4+a65*k5), planets);
        k7 = diff(t +    h, new_y+h*(a71*k1+a72*k2+a73*k3+a74*k4+a75*k5+a76*k6), planets);
        new_y = new_y + h * (b1 * k1 + b3 * k3 + b4 * k4 + b5 * k5 + b6 * k6);


        Date date;
        date.set_MJD(t);
        new_y.set_julian_date(date);
     //   std::cout<<new_y.get_position().get_x()<<" "<<new_y.get_position().get_y()<<" "<<new_y.get_position().get_z()<<"\n";
        result.push_back(new_y);
    }
    return result;
};

BarycentricFrame OrbitalIntegration::sqrt(BarycentricFrame frame) {
    BarycentricFrame result;
    result.set_x(std::sqrt(frame.get_x()));
    result.set_y(std::sqrt(frame.get_y()));
    result.set_z(std::sqrt(frame.get_z()));
    return result;
}