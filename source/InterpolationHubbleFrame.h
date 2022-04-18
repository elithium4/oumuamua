#include "Date.h"
#include "ObservatoryCartesianFrame.h"

class InterpolationHubbleFrame{
    private:
        ObservatoryCartesianFrame position_data;
        Date date;
    public:
        void set_date(Date);
        void set_data(ObservatoryCartesianFrame);

        Date get_date();
        ObservatoryCartesianFrame get_data();
};