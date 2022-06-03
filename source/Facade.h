#include "DataHandler.h"
#include "Converter.h"
#include "OrbitalIntegration.h"
#include "LeastSquares.h"

//Класс, вызывающий методы других классов
class Facade{
    private:
        Converter cnv;
        DataHandler dhand;
        
        IntegrationVector x0;
        OrbitalIntegration integration;

        LeastSquares least_sq;

        std::vector<IntegrationVector> earth_orbit;
        std::map<std::string, std::vector<IntegrationVector>> map_planets;
        std::vector<IntegrationVector> base_measures;

        int counter = 0;

        double wrms_asc;
        double wrms_dec;

    public:
        Facade();
        void read_data();
        void convert_observations();
        void convert_observatory();
        void convert_interpolation_data();
        void integrate();
        void least_squares(std::vector<StateVector>);
        void write_to_file(std::vector<StateVector>);
        double get_wrms_asc();
        double get_wrms_dec();
        IntegrationVector get_x0();
};