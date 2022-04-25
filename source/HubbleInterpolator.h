#include <string>
#include <map>

#include "CartesianFrame.h"
#include "Date.h"

//Класс для интерполяции положения Хаббла
class HubbleInterpolator{
    private:
        std::map<Date, CartesianFrame> interpolation_data;
    public:
        void set_dataframe(Date, CartesianFrame);
};