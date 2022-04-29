#pragma once
#include "Date.h"
#include "GeocentricFrame.h"

//Класс для хранения данных интерполяции Хаббла
class InterpolationHubbleFrame{
    private:
        GeocentricFrame position_data;
        Date date;
    public:
        void set_date(Date);
        void set_data(GeocentricFrame);

        Date get_date();
        GeocentricFrame get_data();
};