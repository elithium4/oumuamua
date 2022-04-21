#include "CylindricalFrame.h"

double CylindricalFrame::get_longitude() {
        return longitude;
}

double CylindricalFrame::get_cos() {
        return cos;
}

double CylindricalFrame::get_sin() {
        return sin;
}

bool CylindricalFrame::is_empty(std::string value){
        for (char c: value){
                if (c != ' '){
                        return true;
                }
        }
        return false;
}

void CylindricalFrame::set_longitude_from_string(std::string value) {
        longitude = is_empty(value) ? stod(value) : NULL;
}

void CylindricalFrame::set_cos_from_string(std::string value) {
        cos = is_empty(value) ? stod(value) : NULL;;
}

void CylindricalFrame::set_sin_from_string(std::string value) {
        sin = is_empty(value) ? stod(value) : NULL;;
}