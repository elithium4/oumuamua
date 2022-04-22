#include "DataHandler.h"
#include "Converter.h"
#include "OrbitalIntegration.h"
//#include "IntegrationVector.h"

class Facade{
    private:
        Converter cnv;
        DataHandler dhand;

        IntegrationVector x0;
        OrbitalIntegration integration;

    public:
        Facade();
        void read_data();
        void convert_observations();
        void convert_observatory();
        void integrate();
};