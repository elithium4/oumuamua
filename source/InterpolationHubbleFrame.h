#pragma once
#include "Date.h"
#include "GeocentricFrame.h"
#include "BarycentricFrame.h"

//Класс для хранения данных интерполяции Хаббла
class InterpolationHubbleFrame{
    private:
        GeocentricFrame position_data;
        Date date;
        BarycentricFrame barycentric_frame;
    public:
        void set_date(Date);
        void set_geocentric(GeocentricFrame);
        void set_barycentric(BarycentricFrame);

        Date get_date();
        GeocentricFrame get_geocentric();
        BarycentricFrame get_barycentric();
};