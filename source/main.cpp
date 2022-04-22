#include "Observation.h"

#include "Facade.h"

int main(){
    Facade f;
    f.read_data();
    f.convert_observations();
    f.integrate();
    /*
    //integration.dormand_prince(x0, dhand.get_observations()[0].get_julian_date(), dhand.get_observations()[-1].get_julian_date(), 10, cnv.interpolation_center_planet(0.1, dhand.get_observations()[0].get_julian_date(), dhand.get_observations()[-1].get_julian_date(), dhand.get_interpolation_planets()));

    std::cout<<"TT: "<<dhand.get_observation(0)->get_julian_date()->get_TT()<<"\n";
    cnv.julian_date_to_tdb((dhand.get_observation(0)->get_julian_date()));
    std::cout<<"TT: "<<dhand.get_observation(0)->get_julian_date()->get_TT()<<"\n";
    */
    return 0;
}