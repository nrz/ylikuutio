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

#ifndef __SHAPESHIFTER_SEQUENCE_STRUCT_HPP_INCLUDED
#define __SHAPESHIFTER_SEQUENCE_STRUCT_HPP_INCLUDED

#include "entity_struct.hpp"

// Include standard headers
#include <cstddef> // std::size_t

namespace yli::ontology
{
    class ShapeshifterTransformation;

    struct ShapeshifterSequenceStruct: public yli::ontology::EntityStruct
    {
        ShapeshifterSequenceStruct()
            : parent(nullptr),
            transformation_speed(0.0f),
            initial_offset(0),
            is_repeating_transformation(true),
            bounce_from_start(false),
            bounce_from_end(false)
        {
            // constructor.
        }

        yli::ontology::ShapeshifterTransformation* parent; // Pointer to `ShapeshifterTransformation` object.
        float transformation_speed;                        // Negative speed means inverse initial transition direction.
        std::size_t initial_offset;                        // Index of the `ShapeshifterForm` from which to begin the transition.

        // Repeating transitions begin from the `initial_offset`
        // endlessly in the same initial transition direction,
        // after all potential bouncing has ended.
        bool is_repeating_transformation;

        // If both `bounce_from_start` and `bounce_from_end` are `true`,
        // then bouncing continues endlessly and the value of
        // `is_repeating_transformation` has no effect.
        bool bounce_from_start;
        bool bounce_from_end;
    };
}

#endif
