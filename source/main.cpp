#include "Observation.h"

#include "Facade.h"

int main(){
    Facade f;
    f.read_data();
    f.convert_observations();
    f.integrate();
    return 0;
}