#include "Date.h"


Date::Date(std::string date){
    int prev = 0;
    for (int i = 0; i < 4; i++){
        for (int j = prev; j < date.length()+1; j++){
            if ((date[j] == ' ') or (date[j] == '\0')){
                switch (i){
                    case 0:
                        year = std::stoi(date.substr(prev, j-prev));
                        break;
                    case 1:
                        month = std::stoi(date.substr(prev, j-prev));
                        break;
                    case 2:
                        day = std::stoi(date.substr(prev, j-prev));
                        day_fraction = std::stod(date.substr(prev, j-prev)) - day;
                        break;
                    default:
                        break;
                }
                prev = j+1;
                break;
            }
        }
    }
}

void Date::set_time_from_fraction(){
    double deltat = day_fraction*24;
    hours = (int) deltat;
    deltat = (deltat - hours) * 60;
    minutes = (int) deltat;
    deltat = (deltat - minutes) * 60;
    seconds = (int) deltat;
}

void Date::set_time_from_string(std::string time){
    
}

void Date::set_JD(){
    double JDN = 367 * year - (7 * (year + 5001 + (month - 9) / 7)) / 4 + (275 * month) / 9 + day + 1729777;
    JD = JDN + (hours - 12) / 24.0 + minutes / 1440.0 + seconds / 86400.0;
    MJD = JD - 2400000.5;
}

int Date::get_year(){
    return year;
};

int Date::get_month(){
    return month;
};

int Date::get_day(){
    return day;
};

double Date::get_day_fraction(){
    return day_fraction;
};

double Date::get_JD(){
    return JD;
};

double Date::get_MJD(){
    return MJD;
};

double Date::get_TT(){
    return TT;
};

double Date::get_TDB(){
    return TDB;
};

double Date::get_TT_TDB() {
    return TT_TDB;
};

void Date::set_TT(double TT){
    this->TT = TT;
};

void Date::set_TT_TDB(double TT_TDB) {
    this->TT_TDB = TT_TDB;
    TDB = TT + TT_TDB;
};