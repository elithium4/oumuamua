#include "Observation.h"

#include "Facade.h"

int main(){
    Facade f;
    f.read_data();
    f.convert_observations();
    f.convert_observatory();
    f.convert_interpolation_data();
    f.integrate();
    f.test_reading();
    return 0;
}