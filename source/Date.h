#include <string>


//Класс даты в формате "год месяц день.доля дня"
class Date{
    private:
        int year;
        int month;
        int day;

        int hours;
        int minutes;
        int seconds;

        double day_fraction;

        double JD;
        double MJD;
        double TT;
        double TBD;
    public:
        Date(){};
        Date(std::string);

        int get_year();
        int get_month();
        int get_day();
        double get_day_fraction();
        double get_JD();
        double get_MJD();
        double get_TT();
        double get_TBD();

        void set_TT(double TT);
        void set_TBD(double TT);
};