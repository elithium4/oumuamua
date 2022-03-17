#include "ObservatoryCylindricalFrame.h"

double ObservatoryCylindricalFrame::get_longitude() {
        return longitude;
}

double ObservatoryCylindricalFrame::get_cos() {
        return cos;
}

double ObservatoryCylindricalFrame::get_sin() {
        return sin;
}

bool ObservatoryCylindricalFrame::is_empty(std::string value){
        for (char c: value){
                if (c != ' '){
                        return true;
                }
        }
        return false;
}

void ObservatoryCylindricalFrame::set_longitude_from_string(std::string value) {
        longitude = is_empty(value) ? stod(value) : NULL;
}

void ObservatoryCylindricalFrame::set_cos_from_string(std::string value) {
        cos = is_empty(value) ? stod(value) : NULL;;
}

void ObservatoryCylindricalFrame::set_sin_from_string(std::string value) {
        sin = is_empty(value) ? stod(value) : NULL;;
}