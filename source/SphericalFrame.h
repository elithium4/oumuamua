#pragma once

class SphericalFrame{
    private:
        double longitude;
        double latitude;
    public:
        void set_longitude(double);
        void set_latitude(double);
        double get_longitude();
        double get_latitude();
};