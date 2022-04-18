#include "InterpolationHubbleFrame.h"

void InterpolationHubbleFrame::set_date(Date date){
    this->date = date;
}

void InterpolationHubbleFrame::set_data(ObservatoryCartesianFrame frame){
    this->position_data = frame;
}

Date InterpolationHubbleFrame::get_date(){
    return date;
}

ObservatoryCartesianFrame InterpolationHubbleFrame::get_data(){
    return position_data;
}