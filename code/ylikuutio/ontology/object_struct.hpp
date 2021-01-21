// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
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

#ifndef __YLIKUUTIO_ONTOLOGY_OBJECT_STRUCT_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_OBJECT_STRUCT_HPP_INCLUDED

#include "movable_struct.hpp"
#include "object_type.hpp"

namespace yli::ontology
{
    class Brain;
    class Species;
    class ShapeshifterSequence;
    class Glyph;
    class Text3D;

    struct ObjectStruct: public yli::ontology::MovableStruct
    {
        ObjectStruct()
        {
            // constructor.
        }

        yli::ontology::Species* species_parent { nullptr };                            // pointer to the parent `Species`.
        yli::ontology::ShapeshifterSequence* shapeshifter_sequence_parent { nullptr }; // pointer to the `ShapeshifterSequence` parent.
        yli::ontology::Text3D* text_3d_parent { nullptr };                             // pointer to the parent `Text3D`.
        yli::ontology::Glyph* glyph { nullptr };                                       // pointer to the `Glyph` (not a parent!).
        yli::ontology::Brain* brain { nullptr };                                       // pointer to the `Brain` master.

        // The parent of a character object is a `Glyph`. The parent of a regular object is a `Species`.
        yli::ontology::ObjectType object_type { yli::ontology::ObjectType::REGULAR };
    };
}

#endif
