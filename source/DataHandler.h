#include "Observation.h"
#include "ObservatoryCylindricalFrame.h"
#include "InterpolationTimeFrame.h"

#include "HubbleInterpolator.h"

#include <iostream>
#include <fstream>
#include <vector>


//Класс, читающий данные из файлов
class DataHandler{
    private:
    std::vector<Observation> observations;
    std::vector<ObservatoryCylindricalFrame> observatory;
    std::vector<InterpolationTimeFrame> interpolation_time;
    HubbleInterpolator hubble;
    public:
        void read_observations(std::string filename="./data/observations.txt");
        void read_observatory_data(std::string filename="./data/observatory.txt");
        void read_hubble_data(std::string filename="./data/hubble_data.txt");
        void read_interpolation_time_data(std::string filename="./data/interpolation_time_data.txt");
        std::vector<InterpolationTimeFrame> get_interpolation_time();
        std::vector<Observation> get_observations();
};