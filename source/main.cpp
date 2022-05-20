#include "Observation.h"

#include "Facade.h"
#include "Matrix.h"


int main(){
    Facade f;
    /*f.read_data();
    f.convert_observations();
    f.convert_observatory();
    f.integrate();
    f.test_reading();*/
    Matrix a(3, 3, {{1, 2, 5},
                    {3, 4, 6},
                    {5, 7, 8}});
    std::cout<<a;
    return 0;
}