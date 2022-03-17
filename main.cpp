#include "ObservatoryCartesianFrame.h"
#include "ObservatoryCylindricalFrame.h"
#include "Observation.h"

#include "Converter.h"
#include "DataHandler.h"


int main(){
    Converter cnv;
    DataHandler dhand;
    dhand.read_observations();
    dhand.read_observatory_data();
    return 0;
}