#include "Observation.h"
#include "IntegrationVector.h"
#include <vector>

class LeastSquares{
    public:
        void calculate_wmrs(std::vector<IntegrationVector>, std::vector<Observation>, double* long_wmrs, double* lat_mwrs);
};