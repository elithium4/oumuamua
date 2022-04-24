#include "Converter.h"

//Функция, переводащая цилиндрические координаты в декартовы
CartesianFrame Converter::cylindrical_to_cartesian(CylindricalFrame measure) {
    CartesianFrame cartesian_data;
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
void Converter::julian_date_to_tdb(Date* date){
    //Перевод в TAI
    double deltat;
    int status = iauDat(date->get_year(), date->get_month(), date->get_day(), date->get_day_fraction(),
        &deltat);

    if (status){
        std::cout<<"Что-то пошло не так\n";
        return;
    }

    //Перевод в TT
    date->set_TT(date->get_MJD() + deltat + 32.184);
};

//Интерполяция времени в TDB
void Converter::interpolation_date_to_tt_tdb(std::vector<Observation> *observations, std::vector<InterpolationTimeFrame> interpolation_time) {
    double delta;
    int last_min = 0;
    for (int i = 0; i < observations->size(); i++) {
        int j = last_min;
        for (j; j < interpolation_time.size(); j++) {
            if ((observations->at(i)).get_julian_date()->get_MJD() < interpolation_time[j].get_julian_date().get_MJD()) {
                last_min = j - 1;
                delta = interpolation_time[j - 1].get_TT_TDB() + (interpolation_time[j].get_TT_TDB() - interpolation_time[j - 1].get_TT_TDB()) / (interpolation_time[j].get_julian_date().get_MJD() - interpolation_time[j - 1].get_julian_date().get_MJD()) * ((observations->at(i)).get_julian_date()->get_MJD() - interpolation_time[j - 1].get_julian_date().get_MJD());
                (observations->at(i)).get_julian_date()->set_TT_TDB(delta);
                break;
            }
        }
    }
}


//Интерполяция положения Хаббла
CartesianFrame Converter::interpolation_hubble_data(Date date, std::vector<InterpolationHubbleFrame> interpolation_data){
    for (int i = 0; i < interpolation_data.size() - 1; i++){
        if ((interpolation_data[i].get_date() < date) and (interpolation_data[i+1].get_date() > date)){
            CartesianFrame new_frame;

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
GeocentricFrame Converter::cartesian_to_geocentric(CartesianFrame frame, Date date){
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

    GeocentricFrame new_frame;
    new_frame.set_x(geo_x);
    new_frame.set_y(geo_y);
    new_frame.set_z(geo_z);
    return new_frame;

};

//Интерполяция центра Земли
BarycentricFrame Converter::interpolation_center_of_earth_for_observatory(Date date, GeocentricFrame frame, std::vector<IntegrationVector> interpolation_earth) {
    double delta_x;
    double delta_y;
    double delta_z;
    for (int j = 0; j < interpolation_earth.size(); j++) {
        if (date.get_MJD() < interpolation_earth[j].get_julian_date().get_MJD()) {
                delta_x = interpolation_earth[j - 1].get_position().get_x() + (interpolation_earth[j].get_position().get_x() - interpolation_earth[j - 1].get_position().get_x()) / (interpolation_earth[j].get_julian_date().get_MJD() - interpolation_earth[j - 1].get_julian_date().get_MJD()) * (date.get_MJD() - interpolation_earth[j - 1].get_julian_date().get_MJD());
                delta_x = interpolation_earth[j - 1].get_position().get_y() + (interpolation_earth[j].get_position().get_y() - interpolation_earth[j - 1].get_position().get_y()) / (interpolation_earth[j].get_julian_date().get_MJD() - interpolation_earth[j - 1].get_julian_date().get_MJD()) * (date.get_MJD() - interpolation_earth[j - 1].get_julian_date().get_MJD());
                delta_x = interpolation_earth[j - 1].get_position().get_z() + (interpolation_earth[j].get_position().get_z() - interpolation_earth[j - 1].get_position().get_z()) / (interpolation_earth[j].get_julian_date().get_MJD() - interpolation_earth[j - 1].get_julian_date().get_MJD()) * (date.get_MJD() - interpolation_earth[j - 1].get_julian_date().get_MJD());
                BarycentricFrame new_frame;
                new_frame.set_x(frame.get_x() + delta_x);
                new_frame.set_y(frame.get_y() + delta_y);
                new_frame.set_z(frame.get_z() + delta_z);
                return new_frame;
        }
    }
}

std::map<std::string, std::vector<IntegrationVector>> Converter::interpolation_center_planet(double h, Date* date_start, Date* date_finish, std::map<std::string, std::vector<IntegrationVector>> interpolation_planets) {
    double delta_x;
    double delta_y;
    double delta_z;
    std::map<std::string, std::vector<IntegrationVector>> new_interpolation_planet;
    for (auto interpolation_planet : interpolation_planets) {
      //  std::count << interpolation_planet.first << std::endl;
        int last_min = 0;
        double flag = 1;
        Date current_date = *date_start;
        int count = 0;
        std::vector<IntegrationVector> new_center_planet;
        while (current_date.get_TDB() < date_finish->get_MJD()) {
            int j = last_min;
            for (j; j < interpolation_planet.second.size(); j++) {
                std::cout << interpolation_planet.second[j].get_julian_date().get_MJD() << std::endl;
                if (current_date.get_TDB() < interpolation_planet.second[j].get_julian_date().get_MJD()) {
                    if (count < 5) {
                        std::cout << current_date.get_TDB() << std::endl;
                        count++;
                    }
                    last_min = j - 1;
                    if (current_date.get_TDB() == interpolation_planet.second[last_min].get_julian_date().get_MJD()) // проверить какая дата у current_date get+MJD/TDB
                        flag = 0;
                    IntegrationVector new_vector;
                    delta_x = interpolation_planet.second[last_min].get_position().get_x() + flag * (interpolation_planet.second[j].get_position().get_x() - interpolation_planet.second[last_min].get_position().get_x()) / (interpolation_planet.second[j].get_julian_date().get_TDB() - interpolation_planet.second[last_min].get_julian_date().get_MJD()) * (current_date.get_MJD() - interpolation_planet.second[last_min].get_julian_date().get_MJD());
                    delta_y = interpolation_planet.second[last_min].get_position().get_y() + flag * (interpolation_planet.second[j].get_position().get_y() - interpolation_planet.second[last_min].get_position().get_y()) / (interpolation_planet.second[j].get_julian_date().get_TDB() - interpolation_planet.second[last_min].get_julian_date().get_MJD()) * (current_date.get_MJD() - interpolation_planet.second[last_min].get_julian_date().get_MJD());
                    delta_z = interpolation_planet.second[last_min].get_position().get_z() + flag * (interpolation_planet.second[j].get_position().get_z() - interpolation_planet.second[last_min].get_position().get_z()) / (interpolation_planet.second[j].get_julian_date().get_TDB() - interpolation_planet.second[last_min].get_julian_date().get_MJD()) * (current_date.get_MJD() - interpolation_planet.second[last_min].get_julian_date().get_MJD());
                    flag = 1;
                    new_vector.set_julian_date(current_date);
                    new_vector.set_position(delta_x, delta_y, delta_z);
                    new_center_planet.push_back(new_vector);
                    current_date.set_MJD(current_date.get_TDB() + h);
                    break;
                }
            }
        }
        new_interpolation_planet[interpolation_planet.first] = new_center_planet;
    }

    return interpolation_planets;
}

void Converter::celestial_to_spherical(Observation* observation){
    double AD = NULL;
    double DEC = NULL;
    iauAf2a('+', 360 / 24 * observation->get_ascension().get_h(), observation->get_ascension().get_m(), observation->get_ascension().get_s(), &AD);
    iauAf2a('+', observation->get_declination().get_h(), observation->get_declination().get_m(), observation->get_declination().get_s(), &DEC);
    observation->set_spherical(AD, DEC);
}

void Converter::barycentric_to_spherical(IntegrationVector* vector){
    double bary[3] = {vector->get_position().get_x(), vector->get_position().get_y(), vector->get_position().get_z()};
    double longitude;
    double latitude;
    iauC2s(bary, &longitude, &latitude);
    vector->set_spherical_position(longitude, latitude);
}


std::vector<IntegrationVector> Converter::interpolation_to_observation(std::vector<Observation> vector, std::vector<IntegrationVector> interpolation_orbits) {
    double delta_x;
    double delta_y;
    double delta_z;
    int last_min = 0;
    std::vector<IntegrationVector> result;
    for (int i = 0; i < vector.size(); i++) {
        IntegrationVector new_vector;
        int j = last_min;
        int count = 0;
        for (j; j < interpolation_orbits.size(); j++) {
            count++;
            if (vector[i].get_julian_date()->get_MJD() < interpolation_orbits[j].get_julian_date().get_MJD()) {
                last_min = j - 1;
                double t;
                delta_x = interpolation_orbits[j - 1].get_position().get_x() + (interpolation_orbits[j].get_position().get_x() - interpolation_orbits[j - 1].get_position().get_x()) / (interpolation_orbits[j].get_julian_date().get_MJD() - interpolation_orbits[j - 1].get_julian_date().get_MJD()) * (vector[i].get_julian_date()->get_MJD() - interpolation_orbits[j - 1].get_julian_date().get_MJD());
                delta_y = interpolation_orbits[j - 1].get_position().get_y() + (interpolation_orbits[j].get_position().get_y() - interpolation_orbits[j - 1].get_position().get_y()) / (interpolation_orbits[j].get_julian_date().get_MJD() - interpolation_orbits[j - 1].get_julian_date().get_MJD()) * (vector[i].get_julian_date()->get_MJD() - interpolation_orbits[j - 1].get_julian_date().get_MJD());
                delta_z = interpolation_orbits[j - 1].get_position().get_z() + (interpolation_orbits[j].get_position().get_z() - interpolation_orbits[j - 1].get_position().get_z()) / (interpolation_orbits[j].get_julian_date().get_MJD() - interpolation_orbits[j - 1].get_julian_date().get_MJD()) * (vector[i].get_julian_date()->get_MJD() - interpolation_orbits[j - 1].get_julian_date().get_MJD());
                new_vector.set_julian_date(interpolation_orbits[j].get_julian_date());
                new_vector.set_position(delta_x, delta_y, delta_z);
                new_vector.set_velocity(0, 0, 0);
                result.push_back(new_vector);
            }
        }
    }
    return result;
}

std::vector<IntegrationVector> Converter::light_time_correction(std::vector<IntegrationVector> vector, std::map<std::string, ObservatoryData> observatory, std::vector< Observation> observations, std::vector<IntegrationVector> modal_vector) {
    std::vector<IntegrationVector> result;
    for (int i = 0; i < vector.size(); i++) {
        IntegrationVector new_vector;
        double delta_t = vector[i].get_julian_date().get_MJD();
        double delta = 0;
        for (int j = 0; j < 3; j++) {
            delta = n_abs(vector[i].get_position() - observatory[observations[i].get_code()].get_barycentric()).len() / (1079252848.8 * 3600.0);
            delta_t -= delta;
        }
        new_vector.set_julian_date(vector[i].get_julian_date());
        BarycentricFrame position = interpolation_orbits(delta_t, modal_vector);
        new_vector.set_position(position.get_x(), position.get_y(), position.get_z());
        new_vector.set_velocity(vector[i].get_velocity().get_vx(), vector[i].get_velocity().get_vy(), vector[i].get_velocity().get_vz());
        result.push_back(new_vector);
    }
    return result;
};


BarycentricFrame Converter::interpolation_orbits(double date, std::vector<IntegrationVector> interpolation_orbits) {
    double delta_x;
    double delta_y;
    double delta_z;
    for (int j = 0; j < interpolation_orbits.size(); j++) {
        if (date < interpolation_orbits[j].get_julian_date().get_MJD()) {
            delta_x = interpolation_orbits[j - 1].get_position().get_x() + (interpolation_orbits[j].get_position().get_x() - interpolation_orbits[j - 1].get_position().get_x()) / (interpolation_orbits[j].get_julian_date().get_MJD() - interpolation_orbits[j - 1].get_julian_date().get_MJD()) * (date - interpolation_orbits[j - 1].get_julian_date().get_MJD());
            delta_y = interpolation_orbits[j - 1].get_position().get_y() + (interpolation_orbits[j].get_position().get_y() - interpolation_orbits[j - 1].get_position().get_y()) / (interpolation_orbits[j].get_julian_date().get_MJD() - interpolation_orbits[j - 1].get_julian_date().get_MJD()) * (date - interpolation_orbits[j - 1].get_julian_date().get_MJD());
            delta_z = interpolation_orbits[j - 1].get_position().get_z() + (interpolation_orbits[j].get_position().get_z() - interpolation_orbits[j - 1].get_position().get_z()) / (interpolation_orbits[j].get_julian_date().get_MJD() - interpolation_orbits[j - 1].get_julian_date().get_MJD()) * (date - interpolation_orbits[j - 1].get_julian_date().get_MJD());
            BarycentricFrame new_frame;
            new_frame.set_x(delta_x);
            new_frame.set_y(delta_y);
            new_frame.set_z(delta_z);
            return new_frame;
        }
    }
};

BarycentricFrame Converter::n_abs(BarycentricFrame frame) {
    BarycentricFrame result;
    result.set_x(std::abs(frame.get_x()));
    result.set_y(std::abs(frame.get_y()));
    result.set_z(std::abs(frame.get_z()));
    return result;
};

std::vector<IntegrationVector> Converter::gravitational_deflection(std::vector<IntegrationVector> model_position, std::map<std::string, ObservatoryData> observatory, std::vector< Observation> observations, std::vector<IntegrationVector> sun_observations) {
    double mass_sun = 1.989e30;
    double new_direction[3];
    BarycentricFrame tmp;
    std::vector<IntegrationVector> result;
    std::vector<IntegrationVector>  sun_interpolation = interpolation_to_observation(observations, sun_observations);
    for (int i = 0; i < model_position.size(); i++) {
        IntegrationVector frame;
        tmp = model_position[i].get_position() - observatory[observations[i].get_code()].get_barycentric();
        double direction_observatory_to_asteroid[3] = { tmp.get_x(), tmp.get_y(), tmp.get_z() };
        tmp = model_position[i].get_position() - sun_interpolation[i].get_position();
        double direction_sun_to_asteroid[3] = { tmp.get_x(), tmp.get_y(), tmp.get_z() };
        tmp = observatory[observations[i].get_code()].get_barycentric() - sun_interpolation[i].get_position();
        double direction_sun_to_observatory[3] = { tmp.get_x(), tmp.get_y(), tmp.get_z() };
        double distance_sun_observatory = tmp.len();
        iauLd(mass_sun, direction_observatory_to_asteroid, direction_sun_to_asteroid, direction_sun_to_observatory, distance_sun_observatory, 0, new_direction);
        frame.set_position(new_direction[0], new_direction[1], new_direction[2]);
        frame.set_julian_date(model_position[i].get_julian_date());
        frame.set_velocity(0, 0, 0);
        result.push_back(frame);
    }
    return result;
};

std::vector<IntegrationVector> Converter::aberration(std::vector<IntegrationVector> model_position, std::map<std::string, ObservatoryData> observatory, std::vector< Observation> observations, std::vector<IntegrationVector> sun_observations) {
    std::vector<IntegrationVector> result;
    double new_direction[3];
    double velocity[3] = { 0, 0, 0 };
    BarycentricFrame tmp;
    std::vector<IntegrationVector>  sun_interpolation = interpolation_to_observation(observations, sun_observations);
    for (int i = 0; i < model_position.size(); i++) {
        IntegrationVector frame;
        tmp = model_position[i].get_position() - observatory[observations[i].get_code()].get_barycentric();
        double direction_observatory_to_asteroid[3] = { tmp.get_x(), tmp.get_y(), tmp.get_z() };
        tmp = observatory[observations[i].get_code()].get_barycentric() - sun_interpolation[i].get_position();
        double distance_sun_observatory = tmp.len();
        iauAb(direction_observatory_to_asteroid, velocity, distance_sun_observatory, 1, new_direction);
        frame.set_position(new_direction[0], new_direction[1], new_direction[2]);
        frame.set_julian_date(model_position[i].get_julian_date());
        frame.set_velocity(0, 0, 0);
        result.push_back(frame);

    }
    return result;
}