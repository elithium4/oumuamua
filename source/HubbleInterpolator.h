#include <string>
#include <map>

#include "ObservatoryCartesianFrame.h"
#include "Date.h"

class HubbleInterpolator{
    private:
        std::map<Date, ObservatoryCartesianFrame> interpolation_data;
    public:
        ObservatoryCartesianFrame interpolate(Date date);
        void set_dataframe(Date, ObservatoryCartesianFrame);
};