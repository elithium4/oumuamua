#pragma once

//Класс для сферических координат (в радианах)
class SphericalFrame{
    private:
        double ascension;
        double declination;
    public:
        void set_ascension(double);
        void set_declination(double);
        double get_ascension();
        double get_declination();
};