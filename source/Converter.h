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

#include "ObservatoryCartesianFrame.h"
#include "ObservatoryCylindricalFrame.h"
#include "Observation.h"

#include "../sofa/sofa.h"

//Класс для разных переводов систем
class Converter{
    public:
    ObservatoryCartesianFrame cylindrical_to_cartesian(ObservatoryCylindricalFrame measure);
    void julian_date_to_tdb(Date);
};