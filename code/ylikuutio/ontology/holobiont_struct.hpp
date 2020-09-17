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

#ifndef __YLIKUUTIO_ONTOLOGY_HOLOBIONT_STRUCT_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_HOLOBIONT_STRUCT_HPP_INCLUDED

#ifndef PI
#define PI 3.14159265359f
#endif

#include "entity_struct.hpp"
#include "code/ylikuutio/data/spherical_coordinates_struct.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath> // NAN, std::isnan, std::pow
#include <vector> // std::vector

namespace yli::ontology
{
    class Symbiosis;
    class Brain;

    struct HolobiontStruct: public yli::ontology::EntityStruct
    {
        HolobiontStruct()
            : original_scale_vector(glm::vec3(1.0f, 1.0f, 1.0f)),
            cartesian_coordinates(glm::vec3(NAN, NAN, NAN)),
            spherical_coordinates(NAN, NAN, NAN),
            symbiosis_parent(nullptr),
            brain(nullptr),
            yaw(0.0f),
            pitch(0.0f)
        {
            // constructor.
        }

        std::vector<glm::vec3> initial_rotate_vectors; // initial rotate vector.
        std::vector<float> initial_rotate_angles;      // initial rotate angle.

        glm::vec3 original_scale_vector;            // original scale vector.
        glm::vec3 cartesian_coordinates;            // coordinate vector.
        yli::data::SphericalCoordinatesStruct spherical_coordinates;
        yli::ontology::Symbiosis* symbiosis_parent; // pointer to the `Symbiosis`.
        yli::ontology::Brain* brain;                // pointer to the `Brain` (not a parent!).
        float yaw;                                  // yaw in radians.
        float pitch;                                // pitch in radians.
    };
}

#endif
