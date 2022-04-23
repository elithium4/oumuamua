#include "DataHandler.h"


//Считывание данных наблюдений
void DataHandler::read_observations(std::string filename){
    std::ifstream file(filename);
    std::string data_line;

    if (!file.is_open())
        std::cout << "Файл с данными наблюдений не может быть открыт!\n";
    else
    {
        while (getline(file, data_line)) {
            if (data_line[14] != 's'){

                Observation data_frame;
                Date observation_date(data_line.substr(15, 17));
                observation_date.set_time_from_fraction();
                observation_date.set_JD();
                data_frame.set_julian_date(observation_date);
                data_frame.set_code(data_line.substr(77, 3));
                data_frame.set_ascension_from_string(data_line.substr(32, 12));
                data_frame.set_declination_from_string(data_line.substr(44, 12));

                observations.push_back(data_frame);
            }
        }
    }
    file.close();
    std::cout<<"Считано: " << observations.size()<<" ";
}


//Считывание данных местоположений обсерваторий
void DataHandler::read_observatory_data(std::string filename){
    std::ifstream file(filename);
    std::string data_line;
    if (!file.is_open())
         std::cout << "Файл с данными обсерваторий не может быть открыт!\n";
    else
    {
         while (getline(file, data_line)) {
             std::string code = data_line.substr(0, 3);
             observatory[code] = ObservatoryData();

             CylindricalFrame data_frame;
             data_frame.set_longitude_from_string(data_line.substr(4, 10));
             data_frame.set_cos_from_string(data_line.substr(13, 8));
             data_frame.set_sin_from_string(data_line.substr(21, 9));

             observatory[code].set_cylindrical(data_frame);
         }
    }
    file.close();
}

//Считывание данных для интерполяции положения Хаббла
void DataHandler::read_hubble_data(std::string filename){
    std::ifstream file(filename);
    std::string data_line;
    if (!file.is_open())
        std::cout << "Файл с данными Хаббла не может быть открыт!\n";
    else
    {
         while (getline(file, data_line)) {
            CartesianFrame data_frame;
            data_frame.set_from_string(data_line.substr(25, data_line.length() - 25));
            Date hubble_date(data_line.substr(0, 10));
            hubble_date.set_time_from_string(data_line.substr(0, 18));
            hubble.set_dataframe(hubble_date, data_frame);
            interpolation_hubble[hubble_date] = data_frame;
         }
    }
    file.close();
}

//Считывание данных для интерполяции
void DataHandler::read_interpolation_time_data(std::string filename) {
    std::ifstream file(filename);
    std::string data_line;
    int ind = 0;
    if (!file.is_open())
        std::cout << "Файл с данными для интерполяции даты не может быть открыт!\n";
    else
    {
        while (getline(file, data_line)) {
            ind++;
            InterpolationTimeFrame data_frame;
            Date observation_date(data_line.substr(0, 12));
            observation_date.set_time_from_fraction();
            observation_date.set_JD();
          //  std::cout << "READ "<<observation_date.get_MJD()<<std::endl;
            data_frame.set_julian_date(observation_date);
            data_frame.set_TT_TDB(data_line.substr(13, 9));
            interpolation_time.push_back(data_frame);
        }
    }
    file.close();
}

void DataHandler::read_interpolation_center_planet(std::string filename, std::string name) {
    std::ifstream file(filename);
    std::string data_line;
    double x;
    double y;
    double z;

    if (!file.is_open())
        std::cout << "Файл с данными для интерполяции центра Земли не может быть открыт!\n";
    else
    {
        std::vector<IntegrationVector> planet;
        while (getline(file, data_line)) {
            IntegrationVector data_frame;
            Date observation_date(data_line.substr(0, 13));
            observation_date.set_time_from_fraction();
            observation_date.set_JD();
            data_frame.set_julian_date(observation_date);
            
            int prev = 14;
            bool flag = false;
            int last = 0;

            for (int i = 0; i < 3; i++) {
                for (int j = prev; j < data_line.length() + 1; j++) {
                    if (data_line[j] != ' ' and data_line[j] != '\0') {
                        flag = true;
                    }
                    if (((data_line[j] == ' ' and data_line[j + 1] != ' ') or (data_line[j] == '\0')) and flag) {
                        last = j;
                        while (data_line[last - 1] == ' ') {
                            last--;
                        }
                        switch (i) {
                        case 0:
                            x = std::stod(data_line.substr(prev, last - prev));
                            break;
                        case 1:
                            y = std::stod(data_line.substr(prev, last - prev));
                            break;
                        case 2:
                            z = std::stod(data_line.substr(prev, last - prev));
                            break;
                        default:
                            break;
                        }
                        data_frame.set_position(x, y, z);
                        planet.push_back(data_frame);
                        prev = j + 1;
                        flag = false;
                        break;
                    }

                }
            }
        }
        InterpolationPlanets[name] = planet;
    }
    file.close();
}


std::vector<InterpolationTimeFrame> DataHandler::get_interpolation_time() {
    return interpolation_time;
}

std::vector<IntegrationVector> DataHandler::get_interpolation_earth() {
    return InterpolationPlanets["earth"];
}

std::vector<Observation>* DataHandler::get_observations() {
    return &observations;
}

std::map<std::string, std::vector<IntegrationVector>> DataHandler::get_interpolation_planets() {
    return InterpolationPlanets;
}

Observation* DataHandler::get_observation(int ind){
    return &observations[ind];
}

std::vector<Observation> DataHandler::get_observations_vector() {
    return observations;
}

std::map<std::string, ObservatoryData> DataHandler::get_observatory() {
    return observatory;
}
