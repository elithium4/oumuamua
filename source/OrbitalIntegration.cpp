#include "OrbitalIntegration.h"
#include <iomanip>

std::ofstream debug;

OrbitalIntegration::OrbitalIntegration(){
    for (auto pair: GM){
        GM[pair.first] = pair.second * 86400 * 86400;
    }
}

IntegrationVector OrbitalIntegration::diff(double t, IntegrationVector asteroid, std::map<std::string, std::vector<IntegrationVector>> planets){
    IntegrationVector d_vector;
    BarycentricFrame dx;
    BarycentricFrame dv;

    int num;
    for (int i = 0; i < planets["earth"].size(); i++) {
        if (planets["earth"][i].get_julian_date()->get_MJD() > t) {
            i = i-1;
            d_vector.set_julian_date(*planets["earth"][i].get_julian_date());
            dv = (GM["sun"] * ((planets["sun"][i].get_position() - asteroid.get_position()) / (pow((planets["sun"][i].get_position() - asteroid.get_position()).len(),3))))
            + (GM["jupiter"] * ((planets["jupiter"][i].get_position() - asteroid.get_position()) / (pow((planets["jupiter"][i].get_position() - asteroid.get_position()).len(), 3))) )
            + (GM["earth"] * ((planets["earth"][i].get_position() - asteroid.get_position()) / (pow((planets["earth"][i].get_position() - asteroid.get_position()).len(), 3))))
            + (GM["mercury"] * ((planets["mercury"][i].get_position() - asteroid.get_position()) / (pow((planets["mercury"][i].get_position() - asteroid.get_position()).len(), 3))) )
            + (GM["venus"] * ((planets["venus"][i].get_position() - asteroid.get_position()) / (pow((planets["venus"][i].get_position() - asteroid.get_position()).len(), 3))) )
            + (GM["mars"] * ((planets["mars"][i].get_position() - asteroid.get_position()) / (pow((planets["mars"][i].get_position() - asteroid.get_position()).len(), 3))) )
            + (GM["saturn"] * ((planets["saturn"][i].get_position() - asteroid.get_position()) / (pow((planets["saturn"][i].get_position() - asteroid.get_position()).len(), 3))) )
            + (GM["moon"] * ((planets["moon"][i].get_position() - asteroid.get_position()) / (pow((planets["moon"][i].get_position() - asteroid.get_position()).len(), 3))));
            break;
        }
    }

    d_vector.set_position(asteroid.get_velocity().get_vx(), asteroid.get_velocity().get_vy(), asteroid.get_velocity().get_vz());
    d_vector.set_velocity(dv.get_x(), dv.get_y(), dv.get_z());
    return d_vector;
};

//Метод Дормана-Принса 5-го порядка
std::vector<IntegrationVector> OrbitalIntegration::dormand_prince(IntegrationVector y, Date* start, Date* end, double h, std::map<std::string, std::vector<IntegrationVector>> planets){
    IntegrationVector k1, k2, k3, k4, k5, k6, k7;
    std::vector<IntegrationVector> result;


    debug.open("./debug/params.txt");

    IntegrationVector new_y = y;

    for (double t = start->get_MJD(); t <= end->get_MJD() + h; t += h){

        std::ofstream out;
        k1 = diff(t,  new_y, planets);
        k2 = diff(t + c2*h, new_y+h*(a21*k1), planets);
        k3 = diff(t + c3*h, new_y+h*(a31*k1+a32*k2), planets);
        k4 = diff(t + c4*h, new_y+h*(a41*k1+a42*k2+a43*k3), planets);
        k5 = diff(t + c5*h, new_y+h*(a51*k1+a52*k2+a53*k3+a54*k4), planets);
        k6 = diff(t + c6*h, new_y+h*(a61*k1+a62*k2+a63*k3+a64*k4+a65*k5), planets);
        k7 = diff(t + c7*h, new_y+h*(a71*k1+a72*k2+a73*k3+a74*k4+a75*k5+a76*k6), planets);
        
        new_y = new_y + h * (b1 * k1 + b3 * k3 + b4 * k4 + b5 * k5 + b6 * k6);

        Date date;
        date.set_MJD(t);
        new_y.set_julian_date(date);
        result.push_back(new_y);
    }

    debug.close();

    return result;
};

BarycentricFrame OrbitalIntegration::sqrt(BarycentricFrame frame) {
    BarycentricFrame result;
    result.set_x(std::sqrt(frame.get_x()));
    result.set_y(std::sqrt(frame.get_y()));
    result.set_z(std::sqrt(frame.get_z()));
    return result;
}