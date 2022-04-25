#include "HubbleInterpolator.h"


void HubbleInterpolator::set_dataframe(Date date, CartesianFrame frame){
    interpolation_data[date] = frame;
}

