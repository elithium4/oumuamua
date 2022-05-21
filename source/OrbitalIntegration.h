#include "IntegrationVector.h"
#include "DataHandler.h"
#include "Converter.h"
#include "StateVector.h"
#include <vector>
#include <map>
#include <math.h>
#include <string>

//Класс для численного интегрирования
class OrbitalIntegration{
    private:
        double c2 = (1.0/5.0);
        double c3 = (3.0/10.0);
        double c4 = (4.0/5.0);
        double c5 = (8.0/9.0);
        double c6 = 1.0;
        double c7 = 1.0;

        double b1 = (35.0/384.0);
        double b2 = 0;
        double b3 = (500.0/1113.0);
        double b4 = (125.0/192.0);
        double b5 = (-2187.0/6784.0);
        double b6 = (11.0/84.0);
        double b7 = 0;

        double a21  =  (1.0/5.0);
        double a31  = (3.0/40.0);
        double a32  = (9.0/40.0);
        double a41  = (44.0/45.0);
        double a42   = (-56.0/15.0);
        double a43   = (32.0/9.0);
        double a51  =  (19372.0/6561.0);
        double a52    =(-25360.0/2187.0);
        double a53   = (64448.0/6561.0);
        double a54   = (-212.0/729.0);
        double a61   = (9017.0/3168.0);
        double a62   = (-355.0/33.0);
        double a63   = (46732.0/5247.0);
        double a64  = (49.0/176.0);
        double a65  = (-5103.0/18656.0);
        double a71  = (35.0/384.0);
        double a72  = (0.0);
        double a73  = (500.0/1113.0);
        double a74  = (125.0/192.0);
        double a75  = (-2187.0/6784.0);
        double a76  = (11.0/84.0);

        std::map<std::string, double> GM = { {"sun", 132712440043.85333}, {"jupiter", 126712764.13345}, {"earth", 398600.43552}, {"mercury", 22031.78000}, {"venus", 324858.59200}, {"mars", 42828.37521}, {"saturn", 37940585.20000}, {"moon", 4902.80008}};
        std::vector<std::string> planet_list = {"sun", "jupiter", "earth", "mercury", "venus", "mars", "saturn", "moon"};
    public:
        OrbitalIntegration();
        IntegrationVector diff(double, IntegrationVector, std::map<std::string, std::vector<IntegrationVector>>, Converter);
        StateVector diff(double, StateVector, std::map<std::string, std::vector<IntegrationVector>>, Converter);
        std::vector<IntegrationVector> dormand_prince(IntegrationVector, Date*, Date*, double, std::map<std::string, std::vector<IntegrationVector>>, Converter);
        BarycentricFrame sqrt(BarycentricFrame);
};