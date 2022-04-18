#include "HubbleInterpolator.h"


void HubbleInterpolator::set_dataframe(Date date, ObservatoryCartesianFrame frame){
    interpolation_data[date] = frame;
}

ObservatoryCartesianFrame HubbleInterpolator::interpolate(Date date){
    
    for (int frame_index = 0; frame_index < interpolation_data.size(); frame_index++){
        
    }
}