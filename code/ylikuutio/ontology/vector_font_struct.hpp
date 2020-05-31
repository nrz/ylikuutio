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

#ifndef __VECTOR_FONT_STRUCT_HPP_INCLUDED
#define __VECTOR_FONT_STRUCT_HPP_INCLUDED

#include "entity_struct.hpp"

// Include standard headers
#include <string>   // std::string

#define DEFAULT_VERTEX_SCALING_FACTOR (0.001f)

namespace yli::ontology
{
    class Material;

    struct VectorFontStruct: public yli::ontology::EntityStruct
    {
        VectorFontStruct()
            : parent(nullptr), vertex_scaling_factor(DEFAULT_VERTEX_SCALING_FACTOR)
        {
            // constructor.
        }

        // used for all files (for all `VectorFont`s).
        yli::ontology::Material* parent; // pointer to the `Material`.
        float vertex_scaling_factor;
        std::string font_file_format;    // type of the font file. supported file formats so far: `"svg"`/`"SVG"`.
        std::string font_filename;       // filename of the font file.
    };
}

#endif
