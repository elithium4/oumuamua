#include "Facade.h"

Facade::Facade(){
    x0.set_position(1.452674920249709E+08, 7.476202044529255E+07, -1.071281870835046E+07);
    x0.set_velocity(4.483537051060935E+01, 1.039892688333976E+01, 1.433813590588367E+01);
}

void Facade::read_data(){
    dhand.read_observations();
    dhand.read_observatory_data();
    dhand.read_hubble_data();

    dhand.read_interpolation_time_data();

    dhand.read_interpolation_center_planet("./data/interpolation_center_earth.txt", "earth");
    dhand.read_interpolation_center_planet("./data/interpolation_center_sun.txt", "sun");
    dhand.read_interpolation_center_planet("./data/interpolation_center_jupiter.txt", "jupiter");
}

void Facade::convert_observations(){
    std::vector<Observation>* data = dhand.get_observations();
    for (int ind = 0; ind < data->size(); ind++){
        if (ind == 0){
            std::cout<<"Before: "<<data->at(ind).get_julian_date()->get_TT();
        }
        cnv.julian_date_to_tdb(data->at(ind).get_julian_date());
        if (ind == 0){
            std::cout<<"After: "<<data->at(ind).get_julian_date()->get_TT();
        }
    }
    std::cout<<"\nBefore: "<<data->at(0).get_julian_date()->get_TDB();
    cnv.interpolation_date_to_tt_tdb(data, dhand.get_interpolation_time());
    std::cout<<"\nAfter: "<<data->at(0).get_julian_date()->get_TDB();
}

void Facade::convert_observatory(){
    
}

void Facade::integrate(){
    //integration.dormand_prince(x0, dhand.get_observations()[0].get_julian_date(), dhand.get_observations()[-1].get_julian_date(), 10, cnv.interpolation_center_planet(0.1, dhand.get_observations()[0].get_julian_date(), dhand.get_observations()[-1].get_julian_date(), dhand.get_interpolation_planets()));
}