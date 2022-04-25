#include "Observation.h"
#include "IntegrationVector.h"
#include <vector>

//МНК
class LeastSquares{
    public:
        void calculate_wmrs(std::vector<IntegrationVector>, std::vector<Observation>, double* long_wmrs, double* lat_mwrs);
};