#include "Facade.h"
#include <iomanip>

Facade::Facade(){
    x0.set_position(1.452674920249709E+08, 7.476202044529255E+07, -1.071281870835046E+07);
    x0.set_velocity(4.483537051060935E+01, 1.039892688333976E+01, 1.433813590588367E+01);
}

//Считывание данных
void Facade::read_data(){
    dhand.read_observations();
    dhand.read_observatory_data();
    dhand.read_hubble_data();

    dhand.read_interpolation_time_data();

    dhand.read_interpolation_center_planet("./data/interpolation_center_earth.txt", "earth");
    dhand.read_interpolation_center_planet("./data/interpolation_center_sun.txt", "sun");
    dhand.read_interpolation_center_planet("./data/interpolation_center_jupiter.txt", "jupiter");

    std::cout<<"Data reading done.\n";
}

//Перевод времени наблюдений
void Facade::convert_observations(){
    std::vector<Observation>* data = dhand.get_observations();
    for (int ind = 0; ind < data->size(); ind++){
        cnv.julian_date_to_tt(data->at(ind).get_julian_date());
    }
    cnv.interpolation_date_to_tt_tdb(data, dhand.get_interpolation_time());
    std::cout<<"Observation convertion done.\n";
}

//Перевод положения обсерваторий
void Facade::convert_observatory(){
    std::map<std::string, ObservatoryData> data = dhand.get_observatory();
    for(auto& item : data) {
        ObservatoryData* cur_obs = dhand.get_observatory_data_by_code(item.first);
        cur_obs->set_cartesian(cnv.cylindrical_to_cartesian(cur_obs->get_cylindric()));
    }
    std::cout<<"Observatory convertion done.\n";
}


void Facade::convert_interpolation_data(){
    std::vector<IntegrationVector>* pl_data = dhand.get_planet_by_name("earth");
    for (int ind = 0; ind < pl_data->size(); ind++){
        cnv.julian_date_to_tt(pl_data->at(ind).get_julian_date());
        cnv.interpolation_to_tdb(pl_data->at(ind).get_julian_date(), dhand.get_interpolation_time());
    }
    pl_data = dhand.get_planet_by_name("sun");
    for (int ind = 0; ind < pl_data->size(); ind++){
        cnv.julian_date_to_tt(pl_data->at(ind).get_julian_date());
        cnv.interpolation_to_tdb(pl_data->at(ind).get_julian_date(), dhand.get_interpolation_time());
    }
    pl_data = dhand.get_planet_by_name("jupiter");
    for (int ind = 0; ind < pl_data->size(); ind++){
        cnv.julian_date_to_tt(pl_data->at(ind).get_julian_date());
        cnv.interpolation_to_tdb(pl_data->at(ind).get_julian_date(), dhand.get_interpolation_time());
    }
    std::cout<<"Interpolation convertion done.\n";
}

//Численное интегрирование
void Facade::integrate(){
    std::vector<IntegrationVector> model_measures;
    std::vector<IntegrationVector> base_measures;
    std::vector<IntegrationVector> model_orbits;

    //std::vector<Observation>* data = dhand.get_observations();
    //for (int i = 0; i < data->size(); i++){
    //    std::cout<<"TDB: "<<data->at(i).get_julian_date()->get_TDB()<<"\n";
    //}

    std::map<std::string, std::vector<IntegrationVector>> map_planets = cnv.interpolation_center_planet(0.1, dhand.get_observations()->at(0).get_julian_date(), dhand.get_observations()->at(221).get_julian_date(), dhand.get_interpolation_planets());
    model_orbits = integration.dormand_prince(x0, dhand.get_observations()->at(0).get_julian_date(), dhand.get_observations()->at(221).get_julian_date(), 0.2, map_planets);
    model_measures = cnv.interpolation_to_observation(dhand.get_observations_vector(), model_orbits);
    //model_measures = cnv.light_time_correction(model_measures, dhand.get_observatory(), dhand.get_observations_vector(), model_orbits, dhand.get_interpolation_hubble() ,map_planets["earth"]);
    //model_measures = cnv.gravitational_deflection(model_measures, dhand.get_observatory(), dhand.get_observations_vector(), model_orbits, dhand.get_interpolation_hubble(), map_planets["earth"]);
    //model_measures = cnv.aberration(model_measures, dhand.get_observatory(), dhand.get_observations_vector(), model_orbits, dhand.get_interpolation_hubble(), map_planets["earth"]);
    
    least_squares(model_measures);
}

//МНК (пока в процессе)
void Facade::least_squares(std::vector<IntegrationVector> model){

    for (int i = 0; i < model.size(); i++){
        cnv.barycentric_to_spherical(&model[i]);
        cnv.celestial_to_spherical(dhand.get_observation(i));
    }

    double wrms_longitude;
    double wrms_latitude;

    write_to_file(model);

    least_sq.calculate_wmrs(model, *dhand.get_observations(), &wrms_longitude, &wrms_latitude);

}

//Запись полученных модельных данных в файл
void Facade::write_to_file(std::vector<IntegrationVector> model){
    std::ofstream model_out;
    model_out.open("./data/model_measure.txt");
    if (model_out.is_open()){
        for (int ind = 0; ind < model.size(); ind++){
           model_out<<std::setprecision(9)<<model[ind].get_julian_date()->get_MJD()<<" "<<model[ind].get_spherical_position().get_longitude()<<" "<<model[ind].get_spherical_position().get_latitude()<<"\n";
        }
        model_out.close();
    } else {
        std::cout<<"Что-то пошло не так.\n";
    }

    std::ofstream base_out;
    base_out.open("./data/base_measure.txt");
    if (base_out.is_open()){
            for (int ind = 0; ind < dhand.get_observations()->size(); ind++){
                base_out<<std::setprecision(9)<<dhand.get_observation(ind)->get_julian_date()->get_MJD()<<" "<<dhand.get_observation(ind)->get_spherical_position().get_longitude()<<" "<<dhand.get_observation(ind)->get_spherical_position().get_latitude()<<"\n";
            }
        base_out.close();
    } else {
        std::cout<<"Что-то пошло не так.\n";
    }

    std::ofstream codes;
    codes.open("./data/code.txt");
    for (int ind = 0; ind < dhand.get_observations()->size(); ind++){
        codes<<dhand.get_observation(ind)->get_code()<<"\n";
    }
    codes.close();
}

void Facade::test_reading(){
    std::ifstream data;
    data.open("./data/horizon.txt");
    std::string data_line;
    std::vector<Observation> cel;
    while (getline(data, data_line)){
        
            Observation data_frame;
            Date observation_date(data_line.substr(0, 10));
            observation_date.set_time_from_fraction();
            observation_date.set_JD();
            data_frame.set_julian_date(observation_date);
            data_frame.set_ascension_from_string(data_line.substr(11, 12));
            data_frame.set_declination_from_string(data_line.substr(23, 11));
            cel.push_back(data_frame);
    }
    data.close();
    for (int i = 0; i < cel.size(); i++){
        cnv.celestial_to_spherical(&cel[i]);
    }

    std::ofstream model_out;
    model_out.open("./data/horizon_measure.txt");
    if (model_out.is_open()){
        for (int ind = 0; ind < cel.size(); ind++){
           model_out<<std::setprecision(9)<<cel[ind].get_julian_date()->get_MJD()<<" "<<cel[ind].get_spherical_position().get_longitude()<<" "<<cel[ind].get_spherical_position().get_latitude()<<"\n";
        }
        model_out.close();
    } else {
        std::cout<<"Что-то пошло не так.\n";
    }
}