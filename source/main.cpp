#include "Observation.h"

#include "Facade.h"
#include "Matrix.h"


int main(){
    Facade f;
    f.read_data();
    f.convert_observations();
    f.convert_observatory();
    f.integrate();
    f.integrate();
    //f.integrate();
    //f.integrate();
    //f.test_reading();

   /* LeastSquares sq;

    Matrix A(3, 3, {
        {1, 2, 3},
        {0, 7, 5},
        {0, 0, 20}
    });
    Matrix b(3, 1, {
        {1},
        {3},
        {4}
    });
    Matrix C = sq.solve_upper_sle(A, b);

    std::cout<<C;*/

    return 0;
}