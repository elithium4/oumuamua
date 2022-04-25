#pragma once
#include "Date.h"
#include "CartesianFrame.h"

//Класс для хранения данных интерполяции Хаббла
class InterpolationHubbleFrame{
    private:
        CartesianFrame position_data;
        Date date;
    public:
        void set_date(Date);
        void set_data(CartesianFrame);

        Date get_date();
        CartesianFrame get_data();
};