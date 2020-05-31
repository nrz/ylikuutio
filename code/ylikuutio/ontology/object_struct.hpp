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

#ifndef __OBJECT_STRUCT_HPP_INCLUDED
#define __OBJECT_STRUCT_HPP_INCLUDED

#ifndef PI
#define PI 3.14159265359f
#endif

#include "entity_struct.hpp"
#include "object_type.hpp"
#include "code/ylikuutio/data/spherical_coordinates_struct.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath> // NAN, std::isnan, std::pow

namespace yli::ontology
{
    class Species;
    class ShapeshifterSequence;
    class Glyph;
    class Text3D;
    class Brain;

    struct ObjectStruct: public yli::ontology::EntityStruct
    {
        ObjectStruct()
            : original_scale_vector(glm::vec3(1.0f, 1.0f, 1.0f)),
            cartesian_coordinates(glm::vec3(NAN, NAN, NAN)),
            rotate_vector(glm::vec3(0.0f, 0.0f, 0.0f)),
            initial_rotate_vector(glm::vec3(0.0f, 1.0f, 1.0f)),
            translate_vector(glm::vec3(0.0f, 0.0f, 0.0f)),
            spherical_coordinates(NAN, NAN, NAN),
            species_parent(nullptr),
            shapeshifter_sequence_parent(nullptr),
            text3D_parent(nullptr),
            glyph(nullptr),
            brain(nullptr),
            rotate_angle(0.0f),
            initial_rotate_angle(PI),
            horizontal_angle(0.0),
            vertical_angle(0.0),
            object_type(yli::ontology::ObjectType::REGULAR)
        {
            // constructor.
        }

        glm::vec3 original_scale_vector;        // original scale vector.
        glm::vec3 cartesian_coordinates;        // coordinate vector.
        glm::vec3 rotate_vector;                // rotate vector.
        glm::vec3 initial_rotate_vector;        // initial rotate vector.
        glm::vec3 translate_vector;             // translate vector.
        yli::data::SphericalCoordinatesStruct spherical_coordinates;
        yli::ontology::Species* species_parent; // pointer to the parent `Species`.
        yli::ontology::ShapeshifterSequence* shapeshifter_sequence_parent; // pointer to the `ShapeshifterSequence` parent.
        yli::ontology::Text3D* text3D_parent;   // pointer to the parent `Text3D`.
        yli::ontology::Glyph* glyph;            // pointer to the `Glyph` (not a parent!).
        yli::ontology::Brain* brain;            // pointer to the `Brain` (not a parent!).
        float rotate_angle;                     // rotate angle.
        float initial_rotate_angle;             // initial rotate angle.
        double horizontal_angle;                // horizontal angle in radians.
        double vertical_angle;                  // vertical angle in radians.
        yli::ontology::ObjectType object_type;  // The parent of a character object is a `Glyph`. The parent of a regular object is a `Species`.
    };
}

#endif
