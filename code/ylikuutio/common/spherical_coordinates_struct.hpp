// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef __SPHERICAL_COORDNATES_STRUCT_HPP_INCLUDED
#define __SPHERICAL_COORDNATES_STRUCT_HPP_INCLUDED

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow

namespace yli
{
    namespace common
    {
        struct SphericalCoordinatesStruct
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
        };
    }
}

#endif
