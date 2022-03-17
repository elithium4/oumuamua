#include "CelestialCoord.h"

CelestialCoord::CelestialCoord(double h, double m, double s): h(h), m(m), s(s){
}

CelestialCoord::CelestialCoord(const CelestialCoord & other){
    this->h = other.h;
    this->m = other.m;
    this->s = other.s;
}

CelestialCoord& CelestialCoord::operator=(const CelestialCoord & other){
    this->h = other.h;
    this->m = other.m;
    this->s = other.s;
    return *this;
}

CelestialCoord::CelestialCoord(const CelestialCoord && other){
    this->h = other.h;
    this->m = other.m;
    this->s = other.s;
}

CelestialCoord& CelestialCoord::operator=(const CelestialCoord && other){
    this->h = other.h;
    this->m = other.m;
    this->s = other.s;
    return *this;
}

//Получение координат из строки
void CelestialCoord::set_from_string(std::string params){
    char param;
    int prev = 0;
    for (int i = 0; i < 3; i++){
        for (int j = prev; j < params.length()+1; j++){
            if ((params[j] == ' ') or (params[j] == '\0')){
                switch (i){
                    case 0:
                        h = std::stod(params.substr(prev, j-prev));
                        break;
                    case 1:
                        m = std::stod(params.substr(prev, j-prev));
                        break;
                    case 2:
                        s = std::stod(params.substr(prev, j-prev));
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

double CelestialCoord::get_h(){
    return h;
}

double CelestialCoord::get_m(){
    return m;
}

double CelestialCoord::get_s(){
    return s;
}
