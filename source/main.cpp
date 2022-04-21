#include "Observation.h"

#include "Converter.h"
#include "DataHandler.h"


int main(){
    Converter cnv;
    DataHandler dhand;
    dhand.read_observations();
    dhand.read_observatory_data();
    dhand.read_hubble_data();

    dhand.read_interpolation_time_data();

    dhand.read_interpolation_center_planet("./data/interpolation_center_earth.txt", "earth");


    dhand.read_interpolation_center_planet("./data/interpolation_center_sun.txt", "sun");
    dhand.read_interpolation_center_planet("./data/interpolation_center_jupiter.txt", "jupiter");

    cnv.interpolation_date_to_tt_tdb(dhand.get_observations(), dhand.get_interpolation_time());
    std::cout<<"Done!!!";

    IntegrationVector x0;
    x0.set_position(1.452674920249709E+08, 7.476202044529255E+07, -1.071281870835046E+07);
    x0.set_velocity(4.483537051060935E+01, 1.039892688333976E+01, 1.433813590588367E+01);

    return 0;
}