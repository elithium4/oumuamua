#include "Observation.h"

#include "Facade.h"
#include "Matrix.h"


int main(){
    Facade f;
    f.read_data();
    f.convert_observations();
    f.convert_observatory();
    f.integrate();
    //f.test_reading();

    return 0;
}