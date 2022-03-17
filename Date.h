#include <string>


//Класс даты в формате "год месяц день.доля дня"
class Date{
    private:
        int year;
        int month;
        int day;
        double day_fraction;
    public:
        Date(){};
        Date(std::string);
};