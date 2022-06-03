#include "Observation.h"

#include "Facade.h"
#include "Matrix.h"


int main(){
    Facade f;
    f.read_data();
    f.convert_observations();
    f.convert_observatory();

    f.integrate();
    double old_wrms_asc;
    double old_wrms_dec;

    int iteration_number = 1;

    do {
        std::cout<<"________Iteration #"<<iteration_number<<"________"<<"\n";
        std::cout<<"WRMS RA: "<<std::setprecision(11)<<f.get_wrms_asc()<<"\n";
        std::cout<<"WRMS DEC: "<<std::setprecision(11)<<f.get_wrms_dec()<<"\n"; 
        iteration_number++;
        old_wrms_asc = f.get_wrms_asc();
        old_wrms_dec = f.get_wrms_dec();
        f.integrate();

    } while ((abs(old_wrms_asc - f.get_wrms_asc()) > 0.00000000001) or (abs(old_wrms_dec - f.get_wrms_dec()) > 0.00000000001));
    
    return 0;
}