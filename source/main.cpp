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
                    {3, 4, 5}});
    
    Matrix b(3, 2, {
        {3, 2},
        {4, 1},
        {2, 5}
    });

    std::cout<<a;

    Matrix c(2, 2);
    c = (a*b);
    std::cout<<c;
    return 0;
}