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
    public:
        Facade();
        void read_data();
        void convert_observations();
        void convert_observatory();
        void integrate();
        void least_squares(std::vector<IntegrationVector>);
        void write_to_file(std::vector<IntegrationVector>);
};