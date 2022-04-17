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
    dhand.read_hubble_data();

    dhand.read_interpolation_time_data();
    cnv.interpolation_date_to_tt_tdb(dhand.get_observations(), dhand.get_interpolation_time());

    return 0;
}