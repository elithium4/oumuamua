#include "Observation.h"
#include "ObservatoryCylindricalFrame.h"

#include <iostream>
#include <fstream>
#include <vector>


//Класс, читающие данные из файлов
class DataHandler{
    private:
    std::vector<Observation> observations;
    std::vector<ObservatoryCylindricalFrame> observatory;
    public:
        void read_observations(std::string filename="./data/observations.txt");
        void read_observatory_data(std::string filename="./data/observatory.txt");
};