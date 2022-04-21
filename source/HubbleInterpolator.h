#include <string>
#include <map>

#include "CartesianFrame.h"
#include "Date.h"

class HubbleInterpolator{
    private:
        std::map<Date, CartesianFrame> interpolation_data;
    public:
        CartesianFrame interpolate(Date date);
        void set_dataframe(Date, CartesianFrame);
};