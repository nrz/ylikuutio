// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2019 Antti Nuortimo.
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

#ifndef __HOLOBIONT_STRUCT_HPP_INCLUDED
#define __HOLOBIONT_STRUCT_HPP_INCLUDED

#ifndef PI
#define PI 3.14159265359f
#endif

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
        class Symbiosis;

        struct HolobiontStruct
        {
            HolobiontStruct()
                : original_scale_vector(glm::vec3(1.0f, 1.0f, 1.0f)),
                cartesian_coordinates(glm::vec3(NAN, NAN, NAN)),
                rotate_vector(glm::vec3(0.0f, 0.0f, 0.0f)),
                initial_rotate_vector(glm::vec3(0.0f, 1.0f, 1.0f)),
                translate_vector(glm::vec3(0.0f, 0.0f, 0.0f)),
                symbiosis_parent(nullptr),
                rotate_angle(0.0f),
                initial_rotate_angle(PI),
                quaternions_in_use(false)
            {
                // constructor.
            }

            glm::vec3 original_scale_vector;            // original scale vector.
            glm::vec3 cartesian_coordinates;            // coordinate vector.
            glm::vec3 rotate_vector;                    // rotate vector.
            glm::vec3 initial_rotate_vector;            // initial rotate vector.
            glm::vec3 translate_vector;                 // translate vector.
            yli::ontology::Symbiosis* symbiosis_parent; // pointer to the `Symbiosis`.
            float rotate_angle;                         // rotate angle.
            float initial_rotate_angle;                 // initial rotate angle.
            bool quaternions_in_use;
        };
    }
}

#endif
