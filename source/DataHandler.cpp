#include "DataHandler.h"


//Считывание данных наблюдений
void DataHandler::read_observations(std::string filename){
    std::ifstream file(filename);
    std::string data_line;

    int ind = 0;
    if (!file.is_open())
        std::cout << "Файл с данными наблюдений не может быть открыт!\n";
    else
    {
        while (getline(file, data_line)) {
            if (data_line[14] != 's'){
            Observation data_frame;
            data_frame.set_julian_date(Date(data_line.substr(15, 17)));
            data_frame.set_code(data_line.substr(77, 3));
            data_frame.set_ascension_from_string(data_line.substr(32, 12));
            data_frame.set_declination_from_string(data_line.substr(44, 12));
            
            observations.push_back(data_frame);
            }
            ind++;
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
             ObservatoryCylindricalFrame data_frame;
             data_frame.set_longitude_from_string(data_line.substr(5, 8));
             data_frame.set_cos_from_string(data_line.substr(13, 8));
             data_frame.set_sin_from_string(data_line.substr(21, 9));
             observatory.push_back(data_frame);
         }
    }
    file.close();
}