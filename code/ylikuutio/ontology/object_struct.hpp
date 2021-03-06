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

// Include standard headers
#include <variant> // std::holds_alternative, std::variant

namespace yli::ontology
{
    class Species;
    class ShapeshifterSequence;
    class Glyph;
    class Text3D;

    struct ObjectStruct: public yli::ontology::MovableStruct
    {
        explicit ObjectStruct(yli::ontology::Species* const parent)
            : parent { parent }
        {
            // constructor.
        }

        explicit ObjectStruct(yli::ontology::ShapeshifterSequence* const parent)
            : parent { parent }
        {
            // constructor.
        }

        explicit ObjectStruct(yli::ontology::Text3D* const parent)
            : parent { parent }
        {
            // constructor.
        }

        std::variant<yli::ontology::Species*, yli::ontology::ShapeshifterSequence*, yli::ontology::Text3D*> parent;
        yli::ontology::Glyph* glyph { nullptr }; // pointer to the `Glyph` (not a parent!).
    };
}

#endif
