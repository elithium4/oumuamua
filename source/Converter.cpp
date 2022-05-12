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


//Gереводит в TT
void Converter::julian_date_to_tt(Date* date){
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

//Интерполяция времени в TDB
void Converter::interpolation_to_tdb(Date* date, std::vector<InterpolationTimeFrame> interpolation_time) {
    double delta;

    for (int j = 0; j < interpolation_time.size(); j++){
        if (date->get_MJD() < interpolation_time[j].get_julian_date().get_MJD()){
                delta = interpolation_time[j - 1].get_TT_TDB() + (interpolation_time[j].get_TT_TDB() - interpolation_time[j - 1].get_TT_TDB()) / (interpolation_time[j].get_julian_date().get_MJD() - interpolation_time[j - 1].get_julian_date().get_MJD()) * (date->get_MJD() - interpolation_time[j - 1].get_julian_date().get_MJD());
                date->set_TT_TDB(delta);
                break;
        }
    }
}

//Интерполяция положения Хаббла
GeocentricFrame Converter::interpolation_hubble_data(Date date, std::vector<InterpolationHubbleFrame> interpolation_data){
    for (int i = 0; i < interpolation_data.size() - 1; i++){
        if ((interpolation_data[i].get_date() < date) and (interpolation_data[i+1].get_date() > date)){
            GeocentricFrame new_frame;

            double x = interpolation_data[i].get_geocentric().get_x() + (interpolation_data[i+1].get_geocentric().get_x()
            - interpolation_data[i+1].get_geocentric().get_x())*(date.get_MJD() - interpolation_data[i].get_date().get_MJD());

            double y = interpolation_data[i].get_geocentric().get_y() + (interpolation_data[i+1].get_geocentric().get_y()
            - interpolation_data[i+1].get_geocentric().get_y())*(date.get_MJD() - interpolation_data[i].get_date().get_MJD());

            double z = interpolation_data[i].get_geocentric().get_z() + (interpolation_data[i+1].get_geocentric().get_z()
            - interpolation_data[i+1].get_geocentric().get_z())*(date.get_MJD() - interpolation_data[i].get_date().get_MJD());
            std::cout<<"Good i: "<<i<<" "<<i+1<<"\n";

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

    transpose(transition_matrix);

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
        if (date.get_MJD() < interpolation_earth[j].get_julian_date()->get_MJD()) {
                delta_x = interpolation_earth[j - 1].get_position().get_x() + (interpolation_earth[j].get_position().get_x() - interpolation_earth[j - 1].get_position().get_x()) / ((*interpolation_earth[j].get_julian_date()).get_MJD() - (*interpolation_earth[j - 1].get_julian_date()).get_MJD()) * (date.get_MJD() - (*interpolation_earth[j - 1].get_julian_date()).get_MJD());
                delta_y = interpolation_earth[j - 1].get_position().get_y() + (interpolation_earth[j].get_position().get_y() - interpolation_earth[j - 1].get_position().get_y()) / ((*interpolation_earth[j].get_julian_date()).get_MJD() - (*interpolation_earth[j - 1].get_julian_date()).get_MJD()) * (date.get_MJD() - (*interpolation_earth[j - 1].get_julian_date()).get_MJD());
                delta_z = interpolation_earth[j - 1].get_position().get_z() + (interpolation_earth[j].get_position().get_z() - interpolation_earth[j - 1].get_position().get_z()) / ((*interpolation_earth[j].get_julian_date()).get_MJD() - (*interpolation_earth[j - 1].get_julian_date()).get_MJD()) * (date.get_MJD() - (*interpolation_earth[j - 1].get_julian_date()).get_MJD());
                BarycentricFrame new_frame;
                new_frame.set_x(frame.get_x() + delta_x);
                new_frame.set_y(frame.get_y() + delta_y);
                new_frame.set_z(frame.get_z() + delta_z);
                return new_frame;
               
        }
    }
    //std::cout<<"EEEEE\n";
}

//Интерполяция координат центра Земли для численного интегрирования
std::map<std::string, std::vector<IntegrationVector>> Converter::interpolation_center_planet(double h, Date* date_start, Date* date_finish, std::map<std::string, std::vector<IntegrationVector>> interpolation_planets) {
    double delta_x;
    double delta_y;
    double delta_z;
    std::map<std::string, std::vector<IntegrationVector>> new_interpolation_planet;
    for (auto interpolation_planet : interpolation_planets) {
        int last_min = 0;
        double flag = 1;
        Date current_date = *date_start;
        int count = 0;
        std::vector<IntegrationVector> new_center_planet;
        while (current_date.get_MJD() < date_finish->get_MJD() + 0.5) {
            int j = last_min;
            for (j; j < interpolation_planet.second.size(); j++) {
                if (current_date.get_MJD() < (*interpolation_planet.second[j].get_julian_date()).get_MJD()) {
                    
                    last_min = j - 1;
                    if (current_date.get_MJD() == (*interpolation_planet.second[last_min].get_julian_date()).get_MJD()) // проверить какая дата у current_date get+MJD/TDB
                        flag = 0;
                    IntegrationVector new_vector;

                    //std::cout<<"int "<<(*interpolation_planet.second[j].get_julian_date()).get_TDB()<<"\n";

                    delta_x = interpolation_planet.second[last_min].get_position().get_x() + flag * (interpolation_planet.second[j].get_position().get_x() - interpolation_planet.second[last_min].get_position().get_x()) / (*interpolation_planet.second[j].get_julian_date()).get_MJD() - (*interpolation_planet.second[last_min].get_julian_date()).get_MJD() * (current_date.get_MJD() - (*interpolation_planet.second[last_min].get_julian_date()).get_MJD());
                    delta_y = interpolation_planet.second[last_min].get_position().get_y() + flag * (interpolation_planet.second[j].get_position().get_y() - interpolation_planet.second[last_min].get_position().get_y()) / (*interpolation_planet.second[j].get_julian_date()).get_MJD() - (*interpolation_planet.second[last_min].get_julian_date()).get_MJD() * (current_date.get_MJD() - (*interpolation_planet.second[last_min].get_julian_date()).get_MJD());
                    delta_z = interpolation_planet.second[last_min].get_position().get_z() + flag * (interpolation_planet.second[j].get_position().get_z() - interpolation_planet.second[last_min].get_position().get_z()) / (*interpolation_planet.second[j].get_julian_date()).get_MJD() - (*interpolation_planet.second[last_min].get_julian_date()).get_MJD() * (current_date.get_MJD() - (*interpolation_planet.second[last_min].get_julian_date()).get_MJD());
                    flag = 1;
                    new_vector.set_julian_date(current_date);
                    new_vector.set_position(delta_x, delta_y, delta_z);
                    new_center_planet.push_back(new_vector);
                    current_date.set_MJD(current_date.get_MJD()+h);

                    break;
                }
            }
        }
        new_interpolation_planet[interpolation_planet.first] = new_center_planet;
    }
    return new_interpolation_planet;
}

//Перевод сферических координат из "часы-минуты-секунды" в радианы
void Converter::celestial_to_spherical(Observation* observation){
    double degrees_AD = 15.0 * observation->get_ascension().get_h();
    double arcminutes_AD = 0.25 * observation->get_ascension().get_m();
    double arcseconds_AD = 0.25 * observation->get_ascension().get_s();
    double delta_min = (int)arcminutes_AD;
    double delta_sec = (int)arcseconds_AD;
    degrees_AD += delta_min;
    arcminutes_AD = (arcminutes_AD - delta_min)*60 + delta_sec;
    arcseconds_AD = (arcseconds_AD - delta_sec)*60;
    double AD = NULL;
    double DEC = NULL;
    iauAf2a('+', degrees_AD, arcminutes_AD, arcseconds_AD, &AD);
    iauAf2a('+', observation->get_declination().get_h(), observation->get_declination().get_m(), observation->get_declination().get_s(), &DEC);
    /*while (abs(AD) > M_PI){
        if (AD > 0){
            AD -= 2*M_PI;
        }
        else {
            AD += 2*M_PI;
        }
    }*/
    observation->set_spherical(AD, DEC);
}

void Converter::spherical_to_geocentric(Observation* observation) {
    double cart_coord[3];
    iauS2c(observation->get_spherical_position().get_longitude() , observation->get_spherical_position().get_latitude(), cart_coord);
    observation->set_geocentric(cart_coord[0] * 6378.140, cart_coord[1] * 6378.140, cart_coord[2] * 6378.140);
}

void Converter::geocentric_to_spherical(IntegrationVector* vector){
    double geo[3] = {vector->get_position().get_x(), vector->get_position().get_y(), vector->get_position().get_z()};
    double longitude;
    double latitude;
    iauC2s(geo, &longitude, &latitude);
    vector->set_spherical_position(longitude, latitude);
}

//Перевод барицентрических координат в сферические
void Converter::barycentric_to_spherical_for_observations(Observation* vector){
    double bary[3] = {vector->get_barycentric().get_x(), vector->get_barycentric().get_y(), vector->get_barycentric().get_z()};
    double longitude;
    double latitude;
    iauC2s(bary, &longitude, &latitude);
    vector->set_spherical(longitude, latitude);
}

void Converter::geocentric_to_barycentric(std::vector<Observation>* observations, std::map<std::string, ObservatoryData>* observatory, std::vector<InterpolationHubbleFrame> hubble_map, std::vector<IntegrationVector> earth_position) {
    double ind = 0;
    for (int i = 0; i < observations->size(); i++) {
        BarycentricFrame observation_position;
        BarycentricFrame observatory_position;
        if (observations->at(i).get_code() != "250") {
            std::string code = observations->at(i).get_code();
            ObservatoryData cur_obs = observatory->at(code);
            GeocentricFrame geo_obs = cartesian_to_geocentric(cur_obs.get_cartesian(), *observations->at(i).get_julian_date());
            observatory_position = interpolation_center_of_earth_for_observatory(*observations->at(i).get_julian_date(), geo_obs, earth_position);
            //  std::cout << "IN " <<ind <<" "<< code << " " << map_observatory->at(*observations[i].get_julian_date()).get_x()<< " "<< map_observatory->at(*observations[i].get_julian_date()).get_y() << " " << map_observatory->at(*observations[i].get_julian_date()).get_z() << std::endl;        }
        }
        else {
            GeocentricFrame tmp_position = interpolation_hubble_data(*observations->at(i).get_julian_date(), hubble_map);
            observatory_position = interpolation_center_of_earth_for_observatory(*observations->at(i).get_julian_date(), tmp_position, earth_position);
        }
        observation_position.set_x(observatory_position.get_x() + observations->at(i).get_geocentric().get_x());
        observation_position.set_y(observatory_position.get_y() + observations->at(i).get_geocentric().get_y());
        observation_position.set_z(observatory_position.get_z() + observations->at(i).get_geocentric().get_z());
        //std::cout << "GEO "<<observations->at(i).get_geocentric().get_x() << " " << observations->at(i).get_geocentric().get_y() << " " << observations->at(i).get_geocentric().get_z() << std::endl;
        //std::cout << "OBS" << observatory_position.get_x() << " " << observatory_position.get_y() << " " << observatory_position.get_z() << std::endl;
        observations->at(i).set_barycentric(observation_position.get_x(), observation_position.get_y(), observation_position.get_z());
        //std::cout << "Bar" << observations->at(i).get_barycentric().get_x() << " " << observations->at(i).get_barycentric().get_y() << " " << observations->at(i).get_barycentric().get_z() << std::endl;

    }
}


//Интерполяция для выявления смоделированных значений с нужными датами
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
            if (vector[i].get_julian_date()->get_MJD() < interpolation_orbits[j].get_julian_date()->get_MJD()) {
                last_min = j - 1;
                double t;
                delta_x = interpolation_orbits[j - 1].get_position().get_x() + (interpolation_orbits[j].get_position().get_x() - interpolation_orbits[j - 1].get_position().get_x()) / ((*interpolation_orbits[j].get_julian_date()).get_MJD() - (*interpolation_orbits[j - 1].get_julian_date()).get_MJD()) * (vector[i].get_julian_date()->get_MJD() - (*interpolation_orbits[j - 1].get_julian_date()).get_MJD());
                delta_y = interpolation_orbits[j - 1].get_position().get_y() + (interpolation_orbits[j].get_position().get_y() - interpolation_orbits[j - 1].get_position().get_y()) / ((*interpolation_orbits[j].get_julian_date()).get_MJD() - (*interpolation_orbits[j - 1].get_julian_date()).get_MJD()) * (vector[i].get_julian_date()->get_MJD() - (*interpolation_orbits[j - 1].get_julian_date()).get_MJD());
                delta_z = interpolation_orbits[j - 1].get_position().get_z() + (interpolation_orbits[j].get_position().get_z() - interpolation_orbits[j - 1].get_position().get_z()) / ((*interpolation_orbits[j].get_julian_date()).get_MJD() - (*interpolation_orbits[j - 1].get_julian_date()).get_MJD()) * (vector[i].get_julian_date()->get_MJD() - (*interpolation_orbits[j - 1].get_julian_date()).get_MJD());
                Date new_data = *vector[i].get_julian_date();
                new_vector.set_julian_date(new_data);
                new_vector.set_position(delta_x, delta_y, delta_z);
                new_vector.set_velocity(0, 0, 0);
                result.push_back(new_vector);
                break;
            }
        }
    }
    return result;
}

//Поправка за световой промежуток
std::vector<IntegrationVector> Converter::light_time_correction(std::map<std::string, ObservatoryData> observatory, std::vector<IntegrationVector> model, std::vector< Observation> observations, std::vector<InterpolationHubbleFrame> hubble_map, std::vector<IntegrationVector> earth_position) {
    std::vector<IntegrationVector> result;
    for (int i = 0; i < model.size(); i++) {
        IntegrationVector new_vector;
        double delta_t = (*model[i].get_julian_date()).get_MJD();
        double delta = 0;
        for (int j = 0; j < 3; j++) {
            BarycentricFrame observatory_position;
            if (observations[i].get_code() != "250") {
                std::string code = observations[i].get_code();
                ObservatoryData cur_obs = observatory[code];
                GeocentricFrame geo_obs = cartesian_to_geocentric(cur_obs.get_cartesian(), *observations[i].get_julian_date());
                observatory_position = interpolation_center_of_earth_for_observatory(*observations[i].get_julian_date(), geo_obs, earth_position);
                //  std::cout << "IN " <<ind <<" "<< code << " " << map_observatory->at(*observations[i].get_julian_date()).get_x()<< " "<< map_observatory->at(*observations[i].get_julian_date()).get_y() << " " << map_observatory->at(*observations[i].get_julian_date()).get_z() << std::endl;        }
            }
            else {
                GeocentricFrame tmp_position = interpolation_hubble_data(*observations[i].get_julian_date(), hubble_map);
                observatory_position = interpolation_center_of_earth_for_observatory(*observations[i].get_julian_date(), tmp_position, earth_position);
            }
            delta = n_abs(model[i].get_position() - observatory_position).len() / (1079252848.8 * 3600.0);
            delta_t -= delta;
        }
        new_vector.set_julian_date(*model[i].get_julian_date());
        BarycentricFrame position = interpolation_orbits(delta_t, model);
        new_vector.set_position(position.get_x(), position.get_y(), position.get_z());
        new_vector.set_velocity(0, 0, 0);
        result.push_back(new_vector);
    }
    return result;
};

//Нахождение координат по измененной дате (для поправок за световой промежуток)
BarycentricFrame Converter::interpolation_orbits(double date, std::vector<IntegrationVector> interpolation_orbits) {
    double delta_x;
    double delta_y;
    double delta_z;
    for (int j = 0; j < interpolation_orbits.size(); j++) {
        if (date < (*interpolation_orbits[j].get_julian_date()).get_MJD()) {
            /*std::cout<<"I got date: "<<date<<"\n";
            std::cout<<"Match: "<<interpolation_orbits[j].get_julian_date()->get_MJD()<<"\n";
            std::cout<<"X next: "<<interpolation_orbits[j - 1].get_position().get_x()<<"\n";
            std::cout<<"Y next: "<<interpolation_orbits[j - 1].get_position().get_y()<<"\n";
            std::cout<<"Z next: "<<interpolation_orbits[j - 1].get_position().get_z()<<"\n";
            std::cout<<"X prev: "<<interpolation_orbits[j].get_position().get_x()<<"\n";
            std::cout<<"Y prev: "<<interpolation_orbits[j].get_position().get_y()<<"\n";
            std::cout<<"Z prev: "<<interpolation_orbits[j].get_position().get_z()<<"\n";
            */
            delta_x = interpolation_orbits[j - 1].get_position().get_x() + (interpolation_orbits[j].get_position().get_x() - interpolation_orbits[j - 1].get_position().get_x()) / ((*interpolation_orbits[j].get_julian_date()).get_MJD() - (*interpolation_orbits[j - 1].get_julian_date()).get_MJD()) * (date - (*interpolation_orbits[j - 1].get_julian_date()).get_MJD());
            delta_y = interpolation_orbits[j - 1].get_position().get_y() + (interpolation_orbits[j].get_position().get_y() - interpolation_orbits[j - 1].get_position().get_y()) / ((*interpolation_orbits[j].get_julian_date()).get_MJD() - (*interpolation_orbits[j - 1].get_julian_date()).get_MJD()) * (date - (*interpolation_orbits[j - 1].get_julian_date()).get_MJD());
            delta_z = interpolation_orbits[j - 1].get_position().get_z() + (interpolation_orbits[j].get_position().get_z() - interpolation_orbits[j - 1].get_position().get_z()) / ((*interpolation_orbits[j].get_julian_date()).get_MJD() - (*interpolation_orbits[j - 1].get_julian_date()).get_MJD()) * (date - (*interpolation_orbits[j - 1].get_julian_date()).get_MJD());
            
            /*
            std::cout<<"X result: "<<delta_x<<"\n";
            std::cout<<"Y result: "<<delta_y<<"\n";
            std::cout<<"Z result: "<<delta_z<<"\n";
            */

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

//Поправка на гравитационное отклонение света
std::vector<IntegrationVector> Converter::gravitational_deflection(std::map<std::string, ObservatoryData> observatory, std::vector<IntegrationVector> model, std::vector< Observation> observations, std::vector<IntegrationVector> sun_observations, std::vector<InterpolationHubbleFrame> hubble_map, std::vector<IntegrationVector> earth_position) {
    double mass_sun = 1.989e30;
    double new_direction[3];
    BarycentricFrame tmp;
    std::vector<IntegrationVector> result;
    std::vector<IntegrationVector>  sun_interpolation = interpolation_to_observation(observations, sun_observations);
    for (int i = 0; i < model.size(); i++) {
        BarycentricFrame observatory_position;
        if (observations[i].get_code() != "250") {
            std::string code = observations[i].get_code();
            ObservatoryData cur_obs = observatory[code];
            GeocentricFrame geo_obs = cartesian_to_geocentric(cur_obs.get_cartesian(), *observations[i].get_julian_date());
            observatory_position = interpolation_center_of_earth_for_observatory(*observations[i].get_julian_date(), geo_obs, earth_position);
            //  std::cout << "IN " <<ind <<" "<< code << " " << map_observatory->at(*observations[i].get_julian_date()).get_x()<< " "<< map_observatory->at(*observations[i].get_julian_date()).get_y() << " " << map_observatory->at(*observations[i].get_julian_date()).get_z() << std::endl;        }
        }
        else {
            GeocentricFrame tmp_position = interpolation_hubble_data(*observations[i].get_julian_date(), hubble_map);
            observatory_position = interpolation_center_of_earth_for_observatory(*observations[i].get_julian_date(), tmp_position, earth_position);
        }
        IntegrationVector frame;
        tmp = model[i].get_position() - observatory_position;
        double direction_observatory_to_asteroid[3] = { tmp.get_x(), tmp.get_y(), tmp.get_z() };
        tmp = model[i].get_position() - sun_interpolation[i].get_position();
        double direction_sun_to_asteroid[3] = { tmp.get_x(), tmp.get_y(), tmp.get_z() };
        tmp = observatory_position - sun_interpolation[i].get_position();
        double direction_sun_to_observatory[3] = { tmp.get_x(), tmp.get_y(), tmp.get_z() };
        double distance_sun_observatory = tmp.len();
        iauLd(mass_sun, direction_observatory_to_asteroid, direction_sun_to_asteroid, direction_sun_to_observatory, distance_sun_observatory, 0, new_direction);
       // std::cout<<new_direction[0]<<" "<<new_direction[1]<<" "<<new_direction[2]<<"\n";
        frame.set_position(new_direction[0], new_direction[1], new_direction[2]);
        frame.set_julian_date(*model[i].get_julian_date());
        frame.set_velocity(0, 0, 0);
        result.push_back(frame);
    }
    return result;
};

//Аберрация
std::vector<IntegrationVector> Converter::aberration(std::map<std::string, ObservatoryData> observatory, std::vector<IntegrationVector> model, std::vector< Observation> observations, std::vector<IntegrationVector> sun_observations, std::vector<InterpolationHubbleFrame> hubble_map, std::vector<IntegrationVector> earth_position) {
    std::vector<IntegrationVector> result;
    double new_direction[3];
    double velocity[3] = { 0, 0, 0 };
    BarycentricFrame tmp;
    std::vector<IntegrationVector>  sun_interpolation = interpolation_to_observation(observations, sun_observations);
    for (int i = 0; i < model.size(); i++) {
        BarycentricFrame observatory_position;
        if (observations[i].get_code() != "250") {
            std::string code = observations[i].get_code();
            ObservatoryData cur_obs = observatory[code];
            GeocentricFrame geo_obs = cartesian_to_geocentric(cur_obs.get_cartesian(), *observations[i].get_julian_date());
            observatory_position = interpolation_center_of_earth_for_observatory(*observations[i].get_julian_date(), geo_obs, earth_position);
        }
        else {
            GeocentricFrame tmp_position = interpolation_hubble_data(*observations[i].get_julian_date(), hubble_map);
            observatory_position = interpolation_center_of_earth_for_observatory(*observations[i].get_julian_date(), tmp_position, earth_position);
        }
        IntegrationVector frame;
        tmp = model[i].get_position() - observatory_position;
        double direction_observatory_to_asteroid[3] = { tmp.get_x(), tmp.get_y(), tmp.get_z() };
        tmp = observatory_position - sun_interpolation[i].get_position();
        double distance_sun_observatory = tmp.len();
        iauAb(direction_observatory_to_asteroid, velocity, distance_sun_observatory, 1, new_direction);
        frame.set_position(new_direction[0], new_direction[1], new_direction[2]);
        frame.set_julian_date(*model[i].get_julian_date());
        frame.set_velocity(0, 0, 0);
        result.push_back(frame);

    }
    return result;
}


void Converter::barycentric_to_geocentric(IntegrationVector* model, std::vector<IntegrationVector> earth_orbit){
    BarycentricFrame earth_bary = interpolation_orbits(model->get_julian_date()->get_MJD(), earth_orbit);


    //std::cout<<"Got X: "<<model->get_position().get_x()<<" minus "<<earth_bary.get_x()<<" resulted in ";
    double x = model->get_position().get_x() - earth_bary.get_x();
    //std::cout<<x<<"\n";

    //std::cout<<"Got Y: "<<model->get_position().get_y()<<" minus "<<earth_bary.get_y()<<" resulted in ";

    double y = model->get_position().get_y() - earth_bary.get_y();
    double z = model->get_position().get_z() - earth_bary.get_z();
    //std::cout<<y<<"\n";

    model->set_geocentric_position(x, y, z);
}