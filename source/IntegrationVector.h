#pragma once
#include "BarycentricFrame.h"
#include "Velocity.h"
#include "Date.h"

class IntegrationVector{
    private:
        BarycentricFrame position;
        Velocity velocity;
        Date julian_date;
    public:
        IntegrationVector(){};

        void set_position(double, double, double);
        void set_velocity(double, double, double);
        void set_julian_date(Date);

        BarycentricFrame get_position();
        Velocity get_velocity();
        Date get_julian_date();

        IntegrationVector(const IntegrationVector& other);
        IntegrationVector& operator=(const IntegrationVector& other);
        IntegrationVector(const IntegrationVector&& other);
        IntegrationVector& operator=(const IntegrationVector&& other);

        friend IntegrationVector operator+(IntegrationVector, double);
        friend IntegrationVector operator+(IntegrationVector, IntegrationVector);
        friend IntegrationVector operator*(double, IntegrationVector);
};