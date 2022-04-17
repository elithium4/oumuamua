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

//Интерполяция времени в TDB
void Converter::interpolation_date_to_tt_tdb(std::vector<Observation> observations, std::vector<InterpolationTimeFrame> interpolation_time) {
    double delta;
    int last_min = 0;
    for (int i = 0; i < observations.size(); i++) {
        int j = last_min;
        for (j; j < interpolation_time.size(); j++) {
            if (observations[i].get_julian_date().get_MJD() < interpolation_time[j].get_julian_date().get_MJD()) {
                last_min = j - 1;
                delta = interpolation_time[j - 1].get_TT_TDB() + (interpolation_time[j].get_TT_TDB() - interpolation_time[j - 1].get_TT_TDB()) / (interpolation_time[j].get_julian_date().get_MJD() - interpolation_time[j - 1].get_julian_date().get_MJD()) * (observations[i].get_julian_date().get_MJD() - interpolation_time[j - 1].get_julian_date().get_MJD());
                observations[i].get_julian_date().set_TT_TDB(delta);
                break;
            }
        }
    }
}