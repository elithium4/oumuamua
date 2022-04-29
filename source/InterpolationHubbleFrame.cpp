#include "InterpolationHubbleFrame.h"

void InterpolationHubbleFrame::set_date(Date date){
    this->date = date;
}

void InterpolationHubbleFrame::set_geocentric(GeocentricFrame frame){
    this->position_data = frame;
}

void InterpolationHubbleFrame::set_barycentric(BarycentricFrame frame) {
    this->barycentric_frame = frame;
}

Date InterpolationHubbleFrame::get_date(){
    return date;
}

GeocentricFrame InterpolationHubbleFrame::get_geocentric(){
    return position_data;
}

BarycentricFrame InterpolationHubbleFrame::get_barycentric() {
    return barycentric_frame;
}