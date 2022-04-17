#include "ObservatoryCartesianFrame.h"

void ObservatoryCartesianFrame::set_from_string(std::string coord){
    int prev = 0;
    for (int i = 0; i < 4; i++){
        for (int j = prev; j < coord.length()+1; j++){
            if ((coord[j] == ' ') or (coord[j] == '\0')){
                switch (i){
                    case 0:
                        x = std::stod(coord.substr(prev, j-prev));
                        break;
                    case 1:
                        y = std::stod(coord.substr(prev, j-prev));
                        break;
                    case 2:
                        z = std::stod(coord.substr(prev, j-prev));
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

double ObservatoryCartesianFrame::get_x() {
        return x;
}

double ObservatoryCartesianFrame::get_y() {
    return y;
}

double ObservatoryCartesianFrame::get_z() {
    return z;
}

void ObservatoryCartesianFrame::set_x(double value) {
    x = value;
}

void ObservatoryCartesianFrame::set_y(double value) {
    y = value;
}

void ObservatoryCartesianFrame::set_z(double value) {
    z = value;
}