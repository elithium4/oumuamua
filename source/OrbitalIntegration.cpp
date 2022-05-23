#include "OrbitalIntegration.h"
#include <iomanip>

std::ofstream debug;
std::ofstream matrix;

OrbitalIntegration::OrbitalIntegration(){
    for (auto pair: GM){
        GM[pair.first] = pair.second * 86400 * 86400;
    }
}

IntegrationVector OrbitalIntegration::diff(double t, IntegrationVector asteroid, std::map<std::string, std::vector<IntegrationVector>> planets, Converter cnv){
    IntegrationVector d_vector;
    BarycentricFrame dx;
    BarycentricFrame dv;


    for (int pl_id = 0; pl_id < planet_list.size(); pl_id++){
        BarycentricFrame pl_frame = cnv.interpolation_orbits(t, planets[planet_list[pl_id]]);
        dv = dv + (GM[planet_list[pl_id]] * (pl_frame - asteroid.get_position()) / pow((pl_frame - asteroid.get_position()).len(), 3));
    }

    Date int_date;
    int_date.set_MJD(t);
    d_vector.set_julian_date(int_date);
    d_vector.set_position(asteroid.get_velocity().get_vx(), asteroid.get_velocity().get_vy(), asteroid.get_velocity().get_vz());
    d_vector.set_velocity(dv.get_x(), dv.get_y(), dv.get_z());

    d_vector.set_position(asteroid.get_velocity().get_vx(), asteroid.get_velocity().get_vy(), asteroid.get_velocity().get_vz());
    d_vector.set_velocity(dv.get_x(), dv.get_y(), dv.get_z());
    return d_vector;
};

void OrbitalIntegration::diff_for_G_matrix(double t, Matrix* mtr, IntegrationVector r, std::map<std::string,                      std::vector<IntegrationVector>> planets, Converter cnv){
     double daX_dX, daX_dY, daX_dZ,
            daY_dX, daY_dY, daY_dZ,
            daZ_dX, daZ_dY, daZ_dZ;
    
    std::map<std::string, BarycentricFrame> planet_positions = {};
    
    for (int pl_id = 0; pl_id < planet_list.size(); pl_id++){
        planet_positions[planet_list[pl_id]] = cnv.interpolation_orbits(t, planets[planet_list[pl_id]]);
    }
    
    for (int pl_id = 0; pl_id < planet_list.size(); pl_id++){

        daX_dX = daX_dX + -GM[planet_list[pl_id]]/pow((planet_positions[planet_list[pl_id]] - r.get_position()).len(), 3) + 3*GM[planet_list[pl_id]] * pow(planet_positions[planet_list[pl_id]].get_x() - r.get_position().get_x(), 2)/pow((planet_positions[planet_list[pl_id]] - r.get_position()).len(), 5);

        daX_dY = daX_dY + 3*GM[planet_list[pl_id]] * (planet_positions[planet_list[pl_id]].get_x() - r.get_position().get_x())*(planet_positions[planet_list[pl_id]].get_y() - r.get_position().get_y())/pow((planet_positions[planet_list[pl_id]] - r.get_position()).len(), 5);

        daX_dZ = daX_dZ + 3*GM[planet_list[pl_id]] * (planet_positions[planet_list[pl_id]].get_x() - r.get_position().get_x())*(planet_positions[planet_list[pl_id]].get_z() - r.get_position().get_z())/pow((planet_positions[planet_list[pl_id]] - r.get_position()).len(), 5);

        daY_dX = daY_dX + 3*GM[planet_list[pl_id]] * (planet_positions[planet_list[pl_id]].get_y() - r.get_position().get_y())*(planet_positions[planet_list[pl_id]].get_x() - r.get_position().get_x())/pow((planet_positions[planet_list[pl_id]] - r.get_position()).len(), 5);

        daY_dY = daY_dY + -GM[planet_list[pl_id]]/pow((planet_positions[planet_list[pl_id]] - r.get_position()).len(), 3) + 3*GM[planet_list[pl_id]] * pow(planet_positions[planet_list[pl_id]].get_y() - r.get_position().get_y(), 2)/pow((planet_positions[planet_list[pl_id]] - r.get_position()).len(), 5);

        daY_dZ = daY_dZ + 3*GM[planet_list[pl_id]] * (planet_positions[planet_list[pl_id]].get_y() - r.get_position().get_y())*(planet_positions[planet_list[pl_id]].get_z() - r.get_position().get_z())/pow((planet_positions[planet_list[pl_id]] - r.get_position()).len(), 5);

        daZ_dX = daZ_dX + 3*GM[planet_list[pl_id]] * (planet_positions[planet_list[pl_id]].get_z() - r.get_position().get_z())*(planet_positions[planet_list[pl_id]].get_x() - r.get_position().get_x())/pow((planet_positions[planet_list[pl_id]] - r.get_position()).len(), 5);

        daZ_dY = daZ_dY + 3*GM[planet_list[pl_id]] * (planet_positions[planet_list[pl_id]].get_z() - r.get_position().get_z())*(planet_positions[planet_list[pl_id]].get_y() - r.get_position().get_y())/pow((planet_positions[planet_list[pl_id]] - r.get_position()).len(), 5);

        daZ_dZ = daZ_dZ + -GM[planet_list[pl_id]]/pow((planet_positions[planet_list[pl_id]] - r.get_position()).len(), 3) + 3*GM[planet_list[pl_id]] * pow(planet_positions[planet_list[pl_id]].get_z() - r.get_position().get_z(), 2)/pow((planet_positions[planet_list[pl_id]] - r.get_position()).len(), 5);
    }

    (*mtr)[3][0] = daX_dX;
    (*mtr)[3][1] = daX_dY;
    (*mtr)[3][2] = daX_dZ;

    (*mtr)[4][0] = daY_dX;
    (*mtr)[4][1] = daY_dY;
    (*mtr)[4][2] = daY_dZ;

    (*mtr)[5][0] = daZ_dX;
    (*mtr)[5][1] = daZ_dY;
    (*mtr)[5][2] = daZ_dZ;
}


StateVector OrbitalIntegration::diff(double t, StateVector s_vector, std::map<std::string , std::vector<IntegrationVector>> planets, Converter cnv){
    StateVector new_s_vector;
    IntegrationVector new_y;
    new_y = diff(t, s_vector.get_state(), planets, cnv);

    Matrix G(6, 6);

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            G[i][j] = 0;
            G[6-i - 1][6-j-1] = 0;
            G[i][j+3] = 0;
            if (j == i){
                G[i][j+3] = 1;
            }
        }
    }

    diff_for_G_matrix(t, &G, new_y, planets, cnv);

    matrix<<"G: \n"<<G<<"\n";

    matrix<<"old: \n"<<*s_vector.get_dX_dX0()<<"\n";

    Matrix newdx = G*(*s_vector.get_dX_dX0());

    matrix<<"new:\n"<<newdx<<"\n";

    new_s_vector.set_dX_dX0(newdx);

    matrix<<"dx\dx0: \n"<<*new_s_vector.get_dX_dX0()<<"\n";

    matrix<<"____________________\n";

    new_s_vector.set_dF_dX(G);
    new_s_vector.set_state(new_y);

    return new_s_vector;
}
        

//Метод Дормана-Принса 5-го порядка
std::vector<IntegrationVector> OrbitalIntegration::dormand_prince(IntegrationVector y, Date* start, Date* end, double h, std::map<std::string, std::vector<IntegrationVector>> planets, Converter cnv){
    IntegrationVector k1, k2, k3, k4, k5, k6, k7;
    std::vector<IntegrationVector> result;

    IntegrationVector new_y = y;

    for (double t = start->get_MJD(); t <= end->get_MJD() + h; t += h){

        std::ofstream out;
        k1 = diff(t,  new_y, planets, cnv);
        k2 = diff(t + c2*h, new_y+h*(a21*k1), planets, cnv);
        k3 = diff(t + c3*h, new_y+h*(a31*k1+a32*k2), planets, cnv);
        k4 = diff(t + c4*h, new_y+h*(a41*k1+a42*k2+a43*k3), planets, cnv);
        k5 = diff(t + c5*h, new_y+h*(a51*k1+a52*k2+a53*k3+a54*k4), planets, cnv);
        k6 = diff(t + c6*h, new_y+h*(a61*k1+a62*k2+a63*k3+a64*k4+a65*k5), planets, cnv);
        k7 = diff(t + c7*h, new_y+h*(a71*k1+a72*k2+a73*k3+a74*k4+a75*k5+a76*k6), planets, cnv);
        
        new_y = new_y + h * (b1 * k1 + b3 * k3 + b4 * k4 + b5 * k5 + b6 * k6);

        Date date;
        date.set_MJD(t);
        new_y.set_julian_date(date);
        result.push_back(new_y);
    }

    return result;
};

std::vector<StateVector> OrbitalIntegration::dormand_prince(StateVector y, Date* start, Date* end, double h, std::map<std::string, std::vector<IntegrationVector>> planets, Converter cnv){
    StateVector k1, k2, k3, k4, k5, k6, k7;
    std::vector<StateVector> result;

    matrix.open("./debug/mtr.txt");

    StateVector new_y = y;
    new_y.get_dX_dX0()->make_unit();


    for (double t = start->get_MJD(); t <= end->get_MJD() + h; t += h){

        std::ofstream out;
        k1 = diff(t,  new_y, planets, cnv);
        k2 = diff(t + c2*h, new_y+h*(a21*k1), planets, cnv);
        k3 = diff(t + c3*h, new_y+h*(a31*k1+a32*k2), planets, cnv);
        k4 = diff(t + c4*h, new_y+h*(a41*k1+a42*k2+a43*k3), planets, cnv);
        k5 = diff(t + c5*h, new_y+h*(a51*k1+a52*k2+a53*k3+a54*k4), planets, cnv);
        k6 = diff(t + c6*h, new_y+h*(a61*k1+a62*k2+a63*k3+a64*k4+a65*k5), planets, cnv);
        k7 = diff(t + c7*h, new_y+h*(a71*k1+a72*k2+a73*k3+a74*k4+a75*k5+a76*k6), planets, cnv);
        
        new_y = new_y + h * (b1 * k1 + b3 * k3 + b4 * k4 + b5 * k5 + b6 * k6);

        Date date;
        date.set_MJD(t);
        IntegrationVector new_v = new_y.get_state();
        new_v.set_julian_date(date);
        new_y.set_state(new_v);

        result.push_back(new_y);
    }

    matrix.close();
    return result;
};

BarycentricFrame OrbitalIntegration::sqrt(BarycentricFrame frame) {
    BarycentricFrame result;
    result.set_x(std::sqrt(frame.get_x()));
    result.set_y(std::sqrt(frame.get_y()));
    result.set_z(std::sqrt(frame.get_z()));
    return result;
}