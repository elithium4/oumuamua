#define EARTH_RADIUS 6378.140

#include<stdlib.h>
#include <iostream>
#include <cmath>
#include <string>
#include <cctype>
#include <fstream>
#include <algorithm>
#include <functional>
#include <locale>
#include <string>
#include <vector>

#include "CartesianFrame.h"
#include "ObservatoryData.h"
#include "Observation.h"

#include "InterpolationTimeFrame.h"
#include "InterpolationHubbleFrame.h"
#include "InterpolationCenterEarth.h"

#include "../sofa/sofa.h"

//Класс для разных переводов систем
class Converter{
    public:
    CartesianFrame cylindrical_to_cartesian(CylindricalFrame measure);
    void julian_date_to_tdb(Date);
    void interpolation_date_to_tt_tdb(std::vector<Observation> observations, std::vector<InterpolationTimeFrame> interpolation_time);
    
    CartesianFrame interpolation_hubble_data(Date date, std::vector<InterpolationHubbleFrame> interpolation_data);
    GeocentricFrame cartesian_to_geocentric(CartesianFrame, Date);
    BarycentricFrame interpolation_center_of_earth_for_observatory(Date date, GeocentricFrame frame, std::vector<InterpolationCenterEarth> interpolation_earth);

    void transpose(double mtr[3][3]);
};