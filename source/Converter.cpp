#include "Converter.h"

//Функция, переводащая цилиндрические координаты в декартовы
ObservatoryCartesianFrame Converter::cylindrical_to_cartesian(ObservatoryCylindricalFrame measure) {
    ObservatoryCartesianFrame cartesian_data;
    if (measure.get_longitude() != NULL){
        if (measure.get_cos() != NULL){
            cartesian_data.set_x(cos(measure.get_longitude()) * measure.get_cos() * EARTH_RADIUS); // cartesian_data.set_x(cos(measure.get_longitude()) * 6378.140);
            cartesian_data.set_y(sin(measure.get_longitude()) * measure.get_cos() * EARTH_RADIUS); //cartesian_data.set_y(sin(measure.get_longitude()) * 6378.140);
        }
        if (measure.get_sin() != NULL)
            cartesian_data.set_z(measure.get_sin() * EARTH_RADIUS);
    }
    return cartesian_data;
}


//Эта функция должна переводить в TT
void Converter::julian_date_to_tdb(Date date){
    //Перевод в TAI
    double deltat;
    int status = iauDat(date.get_year(), date.get_month(), date.get_day(), date.get_day_fraction(),
        &deltat);

    if (status){
        std::cout<<"Что-то пошло не так\n";
        return;
    }

    //Перевод в TT
    date.set_TT(date.get_JD() + deltat + 32.184);
};