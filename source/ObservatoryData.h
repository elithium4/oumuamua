#pragma once
#include "CartesianFrame.h"
#include "CylindricalFrame.h"
#include "GeocentricFrame.h"
#include "BarycentricFrame.h"

//Класс для хранения данных обсерватории
class ObservatoryData{
    private:
        CartesianFrame cartesian_frame;
        CylindricalFrame cylindrical_frame;
        GeocentricFrame geocentric_frame;
        BarycentricFrame barycentric_frame;
    public:
        void set_cartesian(CartesianFrame);
        void set_cylindrical(CylindricalFrame);
        void set_geocentric(GeocentricFrame);
        void set_barycentric(BarycentricFrame);

        CartesianFrame get_cartesian();
        CylindricalFrame get_cylindric();
        GeocentricFrame get_geocentric();
        BarycentricFrame get_barycentric();
};