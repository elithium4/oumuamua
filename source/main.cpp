#include "Observation.h"

#include "Facade.h"
#include "Matrix.h"


int main(){
    Facade f;
    f.read_data();
    f.convert_observations();
    f.convert_observatory();
    f.integrate();
    //f.integrate();
    //f.integrate();
    //f.integrate();
    //f.test_reading();

  /* LeastSquares sq;

    Matrix A(3, 3, {
        {4e-3, 12e-4, -16},
        {12, 37,-435e-5},
        {-16, -43, 98}
    });
    Matrix b(3, 1, {
        {1},
        {3},
        {4}
    });
    Matrix C = sq.cholesky(A);

    std::cout<<C;*/

    return 0;
}