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

    return 0;
}