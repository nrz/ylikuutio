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

#ifndef __YLIKUUTIO_ONTOLOGY_TEXT3D_STRUCT_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_TEXT3D_STRUCT_HPP_INCLUDED

#include "entity_struct.hpp"
#include "code/ylikuutio/data/spherical_coordinates_struct.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <string>   // std::string

namespace yli::ontology
{
    class VectorFont;
    class Brain;

    struct Text3DStruct: public yli::ontology::EntityStruct
    {
        Text3DStruct()
            : original_scale_vector(glm::vec3(1.0f, 1.0f, 1.0f)),
            cartesian_coordinates(glm::vec3(NAN, NAN, NAN)),
            rotate_vector(glm::vec3(0.0f, 0.0f, 0.0f)),
            translate_vector(glm::vec3(0.0f, 0.0f, 0.0f)),
            text_string_char(nullptr),
            parent(nullptr),
            brain(nullptr),
            rotate_angle(NAN),
            yaw(0.0),
            pitch(0.0)
        {
            // constructor.
        }

        glm::vec3 original_scale_vector;   // original scale vector.
        glm::vec3 cartesian_coordinates;   // coordinate vector.
        glm::vec3 rotate_vector;           // rotate vector.
        glm::vec3 translate_vector;        // translate vector.
        yli::data::SphericalCoordinatesStruct spherical_coordinates;
        std::string text_string;
        const char* text_string_char;
        yli::ontology::VectorFont* parent; // pointer to the `VectorFont` (parent).
        yli::ontology::Brain* brain;       // pointer to the `Brain` (not a parent!).
        float rotate_angle;                // rotate angle.
        float yaw;                         // yaw in radians.
        float pitch;                       // pitch in radians.
    };
}

#endif
