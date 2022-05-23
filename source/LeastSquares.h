#include "Observation.h"
#include "StateVector.h"
#include <vector>

//МНК
class LeastSquares{
    public:
        std::vector<SphericalFrame> calculate_wmrs(std::vector<StateVector>, std::vector<Observation>, double* long_wmrs, double* lat_mwrs);
        IntegrationVector gauss_newton(std::vector<StateVector>, std::vector<SphericalFrame>);
};