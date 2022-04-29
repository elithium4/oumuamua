#pragma once
#define EARTH_RADIUS 6378.140

#include<stdlib.h>
#include <iostream>
#include <cmath>
#include <string>
#include <cctype>
#include <fstream>
#include <algorithm>
#include <functional>
#include <locale>
#include <string>
#include <vector>

#include "CartesianFrame.h"
#include "ObservatoryData.h"
#include "Observation.h"

#include "InterpolationTimeFrame.h"
#include "InterpolationHubbleFrame.h"

#include "IntegrationVector.h"

#include "../sofa/sofa.h"

#include <map>

//Класс для разных переводов систем
class Converter{
    public:

    CartesianFrame cylindrical_to_cartesian(CylindricalFrame measure);
    void julian_date_to_tt(Date*);
    void interpolation_date_to_tt_tdb(std::vector<Observation>* observations, std::vector<InterpolationTimeFrame> interpolation_time);
    void interpolation_to_tdb(Date*, std::vector<InterpolationTimeFrame>);


    GeocentricFrame interpolation_hubble_data(Date date, std::vector<InterpolationHubbleFrame> interpolation_data);
    GeocentricFrame cartesian_to_geocentric(CartesianFrame, Date);
    BarycentricFrame interpolation_center_of_earth_for_observatory(Date date, GeocentricFrame frame, std::vector<IntegrationVector> interpolation_earth);
    std::map<std::string, std::vector<IntegrationVector>> interpolation_center_planet(double h, Date* date_start, Date* date_finish, std::map<std::string, std::vector<IntegrationVector>> interpolation_planet);
    void geocentric_to_barycentric(std::vector<Observation>*, std::map<std::string, ObservatoryData>*, std::vector<InterpolationHubbleFrame>, std::vector<IntegrationVector>);

    
    void transpose(double mtr[3][3]);

    std::vector<IntegrationVector> light_time_correction(std::vector<IntegrationVector>, std::map<std::string, ObservatoryData>, std::vector< Observation>, std::vector<IntegrationVector>, std::vector<InterpolationHubbleFrame>, std::vector<IntegrationVector> earth_position);
    std::vector<IntegrationVector> interpolation_to_observation(std::vector<Observation> vector, std::vector<IntegrationVector> interpolation_orbits);
    BarycentricFrame interpolation_orbits(double date, std::vector<IntegrationVector> interpolation_orbits);
    BarycentricFrame n_abs(BarycentricFrame);
    std::vector<IntegrationVector> gravitational_deflection(std::vector<IntegrationVector>, std::map<std::string, ObservatoryData>, std::vector< Observation>, std::vector<IntegrationVector>, std::vector<InterpolationHubbleFrame>, std::vector<IntegrationVector> earth_position);
    std::vector<IntegrationVector> aberration(std::vector<IntegrationVector>, std::map<std::string, ObservatoryData>, std::vector< Observation>, std::vector<IntegrationVector>, std::vector<InterpolationHubbleFrame>, std::vector<IntegrationVector> earth_position);

    void celestial_to_spherical(Observation*);
    void barycentric_to_spherical(IntegrationVector*);
    void spherical_to_geocentric(Observation*);

    void barycentric_to_spherical_for_observations(Observation*);
};