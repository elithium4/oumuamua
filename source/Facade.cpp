#include "Facade.h"
#include <iomanip>

Facade::Facade(){
    x0.set_position(1.469662678584988E+08, 7.299822249002472E+07, 2.056575565443711E+07);
    x0.set_velocity((4.466861553600886E+01)*86400, (3.754895272084024E+00)*86400, (1.726865669233104E+01)*86400);
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

    dhand.read_interpolation_center_planet("./data/interpolation_center_mercury.txt", "mercury");
    dhand.read_interpolation_center_planet("./data/interpolation_center_venus.txt", "venus");
    dhand.read_interpolation_center_planet("./data/interpolation_center_mars.txt", "mars");
    dhand.read_interpolation_center_planet("./data/interpolation_center_saturn.txt", "saturn");
    dhand.read_interpolation_center_planet("./data/interpolation_center_moon.txt", "moon");

    std::cout<<"Data reading done.\n";
}

//Перевод времени наблюдений
void Facade::convert_observations(){
    std::vector<Observation>* data = dhand.get_observations();
    for (int ind = 0; ind < data->size(); ind++){
        cnv.julian_date_to_tt(data->at(ind).get_julian_date());
        cnv.celestial_to_spherical(dhand.get_observation(ind));
    }
    cnv.interpolation_date_to_tt_tdb(data, dhand.get_interpolation_time());
    std::cout<<"Observation convertion done.\n";

    map_planets = cnv.interpolation_center_planet(0.2, dhand.get_observations()->at(0).get_julian_date(), dhand.get_observations()->at(221).get_julian_date(), dhand.get_interpolation_planets());

    //Перевод данных из файлах в сферические
    for (int i = 0; i < dhand.get_observations()->size(); i++){
        IntegrationVector vec;
        vec.set_spherical_position(dhand.get_observation(i)->get_spherical_position().get_ascension(), dhand.get_observation(i)->get_spherical_position().get_declination());
        double date = dhand.get_observation(i)->get_julian_date()->get_MJD();
        (vec.get_julian_date())->set_MJD(date);
        base_measures.push_back(vec);
    }

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

//Численное интегрирование
void Facade::integrate(){
    std::vector<StateVector> model_orbits;
    std::vector<StateVector> model_measures;

    StateVector start;
    Date start_date("2017 10 14.43936");
    start_date.set_time_from_fraction();
    start_date.set_JD();
    x0.set_julian_date(start_date);
    start.set_state(x0);

    if (counter == 0){
        start = cnv.light_time_correction(dhand.get_observatory(), start, dhand.get_observations_vector(), dhand.get_interpolation_hubble(), map_planets["earth"]);
        start = cnv.aberration(dhand.get_observatory(), start, dhand.get_observations_vector(), map_planets["sun"], dhand.get_interpolation_hubble(), map_planets["earth"]);
        start = cnv.gravitational_deflection(dhand.get_observatory(), start, dhand.get_observations_vector(), map_planets["sun"], dhand.get_interpolation_hubble(), map_planets["earth"]);
    }

    model_orbits = integration.dormand_prince(start, dhand.get_observations()->at(0).get_julian_date(), dhand.get_observations()->at(221).get_julian_date(), 0.2, dhand.get_interpolation_planets(), cnv);

    model_measures = cnv.interpolation_to_observation(dhand.get_observations_vector(), model_orbits);

    earth_orbit = map_planets["earth"];



    std::ofstream model_out;
    model_out.open("./data/model_bary.txt");


    for (int i = 0; i < model_measures.size(); i++){
        model_out<<std::setprecision(9)<<model_measures[i].get_state()->get_julian_date()->get_MJD()<<" "<<model_measures[i].get_state()->get_position().get_x()<<" "<<model_measures[i].get_state()->get_position().get_y()<<" "<<model_measures[i].get_state()->get_position().get_z()<<"\n";
        cnv.barycentric_to_geocentric(model_measures[i].get_state(), map_planets["earth"]);
        integration.calculate_dg(&model_measures[i]);
        model_measures[i].calculate_dR_dX0();
    }
    model_out.close();

    write_to_file(model_measures);
    

    least_squares(model_measures);
}

//МНК
void Facade::least_squares(std::vector<StateVector> model){

    std::ofstream spherical;
    spherical.open("./data/spherical_model.txt");

    std::ofstream spherical_base;
    spherical_base.open("./data/spherical_base.txt");

    for (int i = 0; i < model.size(); i++){
        
        cnv.geocentric_to_spherical(model[i].get_state());

        spherical<<model[i].get_state()->get_julian_date()->get_MJD()<<" "<<model[i].get_state()->get_spherical_position().get_ascension()<<" "<<model[i].get_state()->get_spherical_position().get_declination()<<"\n";
        spherical_base<<base_measures[i].get_julian_date()->get_MJD()<<" "<<base_measures[i].get_spherical_position().get_ascension()<<" "<<base_measures[i].get_spherical_position().get_declination()<<"\n";
    }

    spherical.close();
    spherical_base.close();

    write_to_file(model);

    std::vector<SphericalFrame> r_i;
    std::vector<SphericalFrame> delta_i;


    r_i = least_sq.calculate_wmrs(model, *dhand.get_observations(), &delta_i, &wrms_asc, &wrms_dec);
    
    x0 = least_sq.gauss_newton(model, r_i, delta_i, x0);

    counter += 1;
}

//Запись полученных модельных данных в файл
void Facade::write_to_file(std::vector<StateVector> model){
    std::ofstream model_out;
    model_out.open("./data/model_geo.txt");

    if (model_out.is_open()){
        for (int ind = 0; ind < model.size(); ind++){
           model_out<<std::setprecision(9)<<model[ind].get_state()->get_julian_date()->get_MJD()<<" "<<model[ind].get_state()->get_geocentric_position().get_x()<<" "<<model[ind].get_state()->get_geocentric_position().get_y()<<" "<<model[ind].get_state()->get_geocentric_position().get_z()<<"\n";
        }
        model_out.close();
    } else {
        std::cout<<"Что-то пошло не так.\n";
    }

}

double Facade::get_wrms_asc(){
    return wrms_asc;
}

double Facade::get_wrms_dec(){
    return wrms_dec;
}

IntegrationVector Facade::get_x0(){
    return x0;
}