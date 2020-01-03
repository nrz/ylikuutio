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

#ifndef __MOVABLE_STRUCT_HPP_INCLUDED
#define __MOVABLE_STRUCT_HPP_INCLUDED

#include "code/ylikuutio/common/spherical_coordinates_struct.hpp"
#include "code/ylikuutio/input/input.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath> // NAN, std::isnan, std::pow

namespace yli
{
    namespace ontology
    {
        class Brain;

        struct MovableStruct
        {
            MovableStruct()
                : input_method(yli::input::InputMethod::AI),
                brain(nullptr),
                cartesian_coordinates(glm::vec3(NAN, NAN, NAN)),
                spherical_coordinates(NAN, NAN, NAN),
                horizontal_angle(0.0),
                vertical_angle(0.0)
            {
                // constructor.
            }

            MovableStruct(
                    yli::ontology::Brain* const brain,
                    const glm::vec3& cartesian_coordinates,
                    yli::common::SphericalCoordinatesStruct spherical_coordinates,
                    const double horizontal_angle,
                    const double vertical_angle)
                : brain(brain),
                cartesian_coordinates(cartesian_coordinates),
                spherical_coordinates(spherical_coordinates),
                horizontal_angle(horizontal_angle),
                vertical_angle(vertical_angle)
            {
            }

            yli::input::InputMethod input_method;
            yli::ontology::Brain* brain;     // brain.
            glm::vec3 cartesian_coordinates; // coordinate vector.
            yli::common::SphericalCoordinatesStruct spherical_coordinates;
            double horizontal_angle;
            double vertical_angle;
        };
    }
}

#endif
