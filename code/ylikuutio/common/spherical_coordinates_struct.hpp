#ifndef __SPHERICAL_COORDNATES_STRUCT_HPP_INCLUDED
#define __SPHERICAL_COORDNATES_STRUCT_HPP_INCLUDED

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow

typedef struct SphericalCoordinatesStruct
{
    SphericalCoordinatesStruct()
        : rho(NAN), theta(NAN), phi(NAN)
    {
        // constructor.
    }

    SphericalCoordinatesStruct(float rho, float theta, float phi)
        : rho(rho), theta(theta), phi(phi)
    {
        // constructor.
    }
    double rho;
    double theta;
    double phi;
} SphericalCoordinatesStruct;

#endif
