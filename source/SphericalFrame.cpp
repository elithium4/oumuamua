#include "SphericalFrame.h"

void SphericalFrame::set_ascension(double ascension){
    this->ascension = ascension;
}

void SphericalFrame::set_declination(double declination){
    this->declination = declination;
}

double SphericalFrame::get_ascension(){
    return ascension;
}

double SphericalFrame::get_declination(){
    return declination;
}