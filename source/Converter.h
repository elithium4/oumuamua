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
#include "StateVector.h"
#include <iomanip>      // std::setprecision

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

    std::vector<IntegrationVector> interpolation_to_observation(std::vector<Observation> vector, std::vector<IntegrationVector> interpolation_orbits);
    BarycentricFrame interpolation_orbits(double date, std::vector<IntegrationVector> interpolation_orbits);
    BarycentricFrame n_abs(BarycentricFrame);


    void barycentric_to_geocentric(IntegrationVector*, std::vector<IntegrationVector>);
    void geocentric_to_barycentric(IntegrationVector*, std::vector<IntegrationVector>);
    void celestial_to_spherical(Observation*);
    void geocentric_to_spherical(IntegrationVector*);
    void spherical_to_geocentric(Observation*);

    void barycentric_to_spherical_for_observations(Observation*);

    std::vector<StateVector> interpolation_to_observation(std::vector<Observation> vector, std::vector<StateVector> interpolation_orbits);
    IntegrationVector interpolation_state(IntegrationVector, IntegrationVector, double);
    Matrix interpolation_matrix(Matrix, Matrix, double, double, double);

    StateVector light_time_correction(std::map<std::string, ObservatoryData>, StateVector,  std::vector< Observation>, std::vector<InterpolationHubbleFrame>, std::vector<IntegrationVector> earth_position);
    StateVector gravitational_deflection(std::map<std::string, ObservatoryData>, StateVector,  std::vector< Observation>, std::vector<IntegrationVector>, std::vector<InterpolationHubbleFrame>, std::vector<IntegrationVector> earth_position);
    StateVector aberration(std::map<std::string, ObservatoryData>, StateVector, std::vector< Observation>, std::vector<IntegrationVector>, std::vector<InterpolationHubbleFrame>, std::vector<IntegrationVector> earth_position);
    BarycentricFrame interpolation_orbits(double date, std::vector<StateVector> interpolation_orbits);
    BarycentricFrame interpolation_orbits(double date, StateVector interpolation_orbits);

    std::vector<IntegrationVector> celestial_to_spherical(std::vector<Observation>);

};