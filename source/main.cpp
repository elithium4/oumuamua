#include "Observation.h"

#include "Facade.h"
#include "Matrix.h"


int main(){
    Facade f;
    f.read_data();
    f.convert_observations();
    f.convert_observatory();
    for (int i = 0; i < 10; i++){
        f.integrate();
    }
    //f.integrate();
    //f.integrate();
    //f.integrate();
    //f.integrate();
    //f.test_reading();
    return 0;
}