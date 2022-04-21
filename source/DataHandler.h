#include "Observation.h"
#include "ObservatoryData.h"
#include "InterpolationTimeFrame.h"
//#include "InterpolationCenterEarth.h"
#include "IntegrationVector.h"

#include "HubbleInterpolator.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <map>


//Класс, читающий данные из файлов
class DataHandler{
    private:
        std::vector<Observation> observations;
    //std::vector<CylindricalFrame> observatory;

    std::map<std::string,ObservatoryData> observatory;

    std::vector<InterpolationTimeFrame> interpolation_time;
    std::map<std::string, std::vector<IntegrationVector>> InterpolationPlanets;

    std::map<Date, CartesianFrame> interpolation_hubble;
    //std::map<Date, CartesianFrame> interpolation_hubble;
    HubbleInterpolator hubble;
    public:
        void read_observations(std::string filename="./data/observations.txt");
        void read_observatory_data(std::string filename="./data/observatory.txt");
        void read_hubble_data(std::string filename="./data/hubble_data.txt");
        void read_interpolation_time_data(std::string filename="./data/interpolation_time_data.txt");
        void read_interpolation_center_planet(std::string filename, std::string name);
        std::vector<InterpolationTimeFrame> get_interpolation_time();
        std::vector<IntegrationVector> get_interpolation_earth();
        std::vector<Observation> get_observations();
};