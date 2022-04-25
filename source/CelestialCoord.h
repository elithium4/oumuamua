#include <string>
#include <cstring>

//Класс небесной координаты - часы, минуты, секунды
class CelestialCoord{
    private:
        double h;
        double m;
        double s;
    public:
        CelestialCoord() {};
        CelestialCoord(double, double, double);
        CelestialCoord(const CelestialCoord& other);
        CelestialCoord& operator=(const CelestialCoord& other);
        CelestialCoord(const CelestialCoord&& other);
        CelestialCoord& operator=(const CelestialCoord&& other);
        
        void set_from_string(std::string);
        double get_h();
        double get_m();
        double get_s();
};
