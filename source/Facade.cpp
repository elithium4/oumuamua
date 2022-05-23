#include "Facade.h"
#include <iomanip>

Facade::Facade(){
    x0.set_position(1.452674920249709E+08, 7.285412724042718E+07, 1.990980486534136E+07);
    x0.set_velocity((4.483537051060935E+01)*86400, (3.837445958225554E+00)*86400, (1.729143805755713E+01)*86400);
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
    //std::vector<IntegrationVector> model_measures;
    std::vector<IntegrationVector> base_measures;
    //std::vector<IntegrationVector> model_orbits;

    std::vector<StateVector> model_orbits;
    std::vector<StateVector> model_measures;

    std::map<std::string, std::vector<IntegrationVector>> map_planets = cnv.interpolation_center_planet(0.2, dhand.get_observations()->at(0).get_julian_date(), dhand.get_observations()->at(221).get_julian_date(), dhand.get_interpolation_planets());

    StateVector start;
    start.set_state(x0);

    model_orbits = integration.dormand_prince(start, dhand.get_observations()->at(0).get_julian_date(), dhand.get_observations()->at(221).get_julian_date(), 0.2, dhand.get_interpolation_planets(), cnv);
    
    std::ofstream orbit_out;
    orbit_out.open("./debug/orbit.txt");
    for (int i = 0; i < model_orbits.size(); i++){
        orbit_out<<std::setprecision(10)<<model_orbits[i].get_state().get_julian_date()->get_MJD()<<" "<<model_orbits[i].get_state().get_position().get_x()<<" "<<model_orbits[i].get_state().get_position().get_y()<<" "<<model_orbits[i].get_state().get_position().get_z()<<"\n";
    }
    orbit_out.close();

    for (int i = 0; i < dhand.get_observations()->size(); i++){
        IntegrationVector vec;
        cnv.celestial_to_spherical(dhand.get_observation(i));

        Observation* obs = dhand.get_observation(i);

        double asc_h = obs->get_ascension().get_h();
        double asc_m = obs->get_ascension().get_m();
        double asc_s = obs->get_ascension().get_s();

        double dec_d = obs->get_declination().get_h();
        double dec_m = obs->get_declination().get_m();
        double dec_s = obs->get_declination().get_s();

        vec.set_spherical_position(asc_h* (M_PI/12) + asc_m*(M_PI/720) + asc_s * (M_PI/43200),
            dec_d*(M_PI/180) + dec_m*(M_PI/720) + dec_s * (M_PI/43200));

        vec.set_spherical_position(dhand.get_observation(i)->get_spherical_position().get_longitude(), dhand.get_observation(i)->get_spherical_position().get_latitude());
        double date = dhand.get_observation(i)->get_julian_date()->get_MJD();
        (vec.get_julian_date())->set_MJD(date);
        base_measures.push_back(vec);
    }

    model_measures = cnv.interpolation_to_observation(dhand.get_observations_vector(), model_orbits);
   
    std::ofstream model_out;
    model_out.open("./data/model_bary.txt");

    //model_measures = cnv.light_time_correction(dhand.get_observatory(), model_measures, dhand.get_observations_vector(), dhand.get_interpolation_hubble(), map_planets["earth"]);
    //model_measures = cnv.aberration(dhand.get_observatory(), model_measures, dhand.get_observations_vector(), map_planets["sun"], dhand.get_interpolation_hubble(), map_planets["earth"]);
    //model_measures = cnv.gravitational_deflection(dhand.get_observatory(), model_measures, dhand.get_observations_vector(), map_planets["sun"], dhand.get_interpolation_hubble(), map_planets["earth"]);

    for (int i = 0; i < model_measures.size(); i++){
        //model_out<<std::setprecision(9)<<model_measures[i].get_state().get_julian_date()->get_MJD()<<" "<<model_measures[i].get_state().get_position().get_x()<<" "<<model_measures[i].get_state().get_position().get_y()<<" "<<model_measures[i].get_state().get_position().get_z()<<"\n";
        //cnv.barycentric_to_geocentric(&model_measures[i], map_planets["earth"]);
    }
    model_out.close();

    /*
    StateVector v;
    v.set_state(model_measures[0]);
    std::cout<<"Ill integrate dx/dx0\n";
    integration.dormand_prince(v, dhand.get_observation(0)->get_julian_date(), dhand.get_observation(221)->get_julian_date(), 0.2, dhand.get_interpolation_planets(), cnv);
    


    least_squares(model_measures, base_measures);
    std::cout<<"Fin\n";*/
}

//МНК (пока в процессе)
void Facade::least_squares(std::vector<IntegrationVector> model, std::vector<IntegrationVector> base_measures){

    std::ofstream spherical;
    spherical.open("./data/spherical_model.txt");

    std::ofstream spherical_base;
    spherical_base.open("./data/spherical_base.txt");

    for (int i = 0; i < model.size(); i++){
        cnv.geocentric_to_spherical(&model[i]);


        spherical<<model[i].get_julian_date()->get_MJD()<<" "<<model[i].get_spherical_position().get_longitude()<<" "<<model[i].get_spherical_position().get_latitude()<<"\n";
        spherical_base<<base_measures[i].get_julian_date()->get_MJD()<<" "<<base_measures[i].get_spherical_position().get_longitude()<<" "<<base_measures[i].get_spherical_position().get_latitude()<<"\n";
    }

    spherical.close();
    spherical_base.close();

    std::cout<< model.size()<<" "<<base_measures.size()<<"\n";

    double wrms_longitude;
    double wrms_latitude;

    write_to_file(model, base_measures);

    least_sq.calculate_wmrs(model, *dhand.get_observations(), &wrms_longitude, &wrms_latitude);

}

//Запись полученных модельных данных в файл
void Facade::write_to_file(std::vector<IntegrationVector> model, std::vector<IntegrationVector> base_measures){
    std::ofstream model_out;
    model_out.open("./data/model_geo.txt");

    if (model_out.is_open()){
        for (int ind = 0; ind < model.size(); ind++){
           model_out<<std::setprecision(9)<<model[ind].get_julian_date()->get_MJD()<<" "<<model[ind].get_geocentric_position().get_x()<<" "<<model[ind].get_geocentric_position().get_y()<<" "<<model[ind].get_geocentric_position().get_z()<<"\n";
        }
        model_out.close();
    } else {
        std::cout<<"Что-то пошло не так.\n";
    }

}

void Facade::test_reading(){
    std::ifstream data;

    data.open("./data/graph_bary_equatorial.txt");
    std::string data_line;
    std::vector<IntegrationVector> hor_data;
    while (getline(data, data_line)){
        int ind = 0;
        int prev = 0;
        IntegrationVector cur;
        Date cur_date;
        double x, y, z;
        for (int i =0; i < data_line.length()+1; i++){
            if ((data_line[i] == ' ') or (data_line[i] == '\0')){
                switch (ind){
                    case 0:
                    cur_date.set_MJD(std::stod(data_line.substr(prev, i - prev)));
                    cur.set_julian_date(cur_date);
                    break;
                    case 1:
                        x = std::stod(data_line.substr(prev, i - prev));
                        break;
                    case 2:
                        y = std::stod(data_line.substr(prev, i - prev));
                        break;
                    case 3:
                        z = std::stod(data_line.substr(prev, i - prev));
                        break;
                }
                ind++;
                prev = i+1;
            }
        }
        cur.set_position(x, y, z);
        hor_data.push_back(cur);
    }

    data.close();

    std::ofstream outp;

    outp.open("./debug/convert_result.txt");

    std::map<std::string, std::vector<IntegrationVector>> map_planets = cnv.interpolation_center_planet(0.2, hor_data[0].get_julian_date(), hor_data[hor_data.size()-1].get_julian_date(), dhand.get_interpolation_planets());


    for (int i = 0; i < hor_data.size(); i++){
        //model_out<<std::setprecision(9)<<model_measures[i].get_julian_date()->get_MJD()<<" "<<model_measures[i].get_position().get_x()<<" "<<model_measures[i].get_position().get_y()<<" "<<model_measures[i].get_position().get_z()<<"\n";
        cnv.barycentric_to_geocentric(&hor_data[i], map_planets["earth"]);
        //std::cout<<"Old: "<<hor_data[i].get_position().get_x()<<" New: "<<hor_data[i].get_geocentric_position().get_x()<<"\n";
        outp<<hor_data[i].get_julian_date()->get_MJD()<<" "<<hor_data[i].get_geocentric_position().get_x()<<" "<<hor_data[i].get_geocentric_position().get_y()<<" "<<hor_data[i].get_geocentric_position().get_z()<<"\n";
    }
    outp.close();

    outp.open("./debug/earth_for_graph.txt");

    std::vector<IntegrationVector> earthData = *dhand.get_planet_by_name("earth");

    for (int i = 0; i < earthData.size(); i++){
        outp<<std::setprecision(10)<<earthData[i].get_julian_date()->get_MJD()<<" "<<earthData[i].get_position().get_x()<<" "<<earthData[i].get_position().get_y()<<" "<<earthData[i].get_position().get_z()<<"\n";
    }

    outp.close();
}

void Facade::test_new_func(){
}