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