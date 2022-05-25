#include "Observation.h"
#include "StateVector.h"
#include <vector>

//МНК
class LeastSquares{
    public:
        std::vector<SphericalFrame> calculate_wmrs(std::vector<StateVector>, std::vector<Observation>, std::vector<SphericalFrame>*, double* long_wmrs, double* lat_mwrs);
        IntegrationVector gauss_newton(std::vector<StateVector>, std::vector<SphericalFrame>, std::vector<SphericalFrame>, IntegrationVector);
        Matrix cholesky(Matrix);
        Matrix ldl(Matrix, Matrix*);
        Matrix solve_lower_sle(Matrix, Matrix);
        Matrix solve_upper_sle(Matrix, Matrix);
};