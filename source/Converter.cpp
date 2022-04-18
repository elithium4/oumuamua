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


//Интерполяция положения Хаббла
ObservatoryCartesianFrame Converter::interpolation_hubble_data(Date date, std::vector<InterpolationHubbleFrame> interpolation_data){
    for (int i = 0; i < interpolation_data.size() - 1; i++){
        if ((interpolation_data[i].get_date() < date) and (interpolation_data[i+1].get_date() > date)){
            ObservatoryCartesianFrame new_frame;

            double x = interpolation_data[i].get_data().get_x() + (interpolation_data[i+1].get_data().get_x()
            - interpolation_data[i+1].get_data().get_x())*(date.get_MJD() - interpolation_data[i].get_date().get_MJD());

            double y = interpolation_data[i].get_data().get_y() + (interpolation_data[i+1].get_data().get_y()
            - interpolation_data[i+1].get_data().get_y())*(date.get_MJD() - interpolation_data[i].get_date().get_MJD());

            double z = interpolation_data[i].get_data().get_z() + (interpolation_data[i+1].get_data().get_z()
            - interpolation_data[i+1].get_data().get_z())*(date.get_MJD() - interpolation_data[i].get_date().get_MJD());

            new_frame.set_x(x);
            new_frame.set_y(y);
            new_frame.set_z(z);
            return new_frame;
        }
    }
};

//Транспонирование матрицы 3х3
void Converter::transpose(double mtr[3][3]){
    double tmp[3][3];
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            tmp[i][j] = mtr[i][j];
        }
    }
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            mtr[j][i] = tmp[i][j];
        }
    }
}

//Перевод из земных координат в геоцентрические небесные
ObservatoryGeocentricFrame Converter::cartesian_to_geocentric(ObservatoryCartesianFrame frame, Date date){
    double transition_matrix[3][3];

    double x, y;
    iauXy06(date.get_TT(), 0, &x, &y);

    iauC2t06a(date.get_TT(), 0, date.get_JD(), 0, x, y, transition_matrix);

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            std::cout<<transition_matrix[i][j] << " ";
        }
        std::cout<<"\n";
    }

    transpose(transition_matrix);

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            std::cout<<transition_matrix[i][j] << " ";
        }
        std::cout<<"\n";
    }

    double geo_x = transition_matrix[0][0] * frame.get_x() + transition_matrix[0][1] * frame.get_y() + transition_matrix[0][2] * frame.get_z();
    double geo_y = transition_matrix[1][0] * frame.get_x() + transition_matrix[1][1] * frame.get_y() + transition_matrix[1][2] * frame.get_z();
    double geo_z = transition_matrix[2][0] * frame.get_x() + transition_matrix[2][1] * frame.get_y() + transition_matrix[2][2] * frame.get_z();

    ObservatoryGeocentricFrame new_frame;
    new_frame.set_x(geo_x);
    new_frame.set_y(geo_y);
    new_frame.set_z(geo_z);
    return new_frame;

};