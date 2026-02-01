// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2026 Antti Nuortimo.
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

#ifndef YLIKUUTIO_ONTOLOGY_VECTOR_FONT_STRUCT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_VECTOR_FONT_STRUCT_HPP_INCLUDED

#include "entity_struct.hpp"
#include "request.hpp"

// Include standard headers
#include <string> // std::string
#include <utility> // std::move

namespace yli::ontology
{
    class Material;

    struct VectorFontStruct final : public EntityStruct
    {
        explicit VectorFontStruct(Request<Material>&& material_parent)
            : material_parent { std::move(material_parent) }
        {
        }

        // used for all files (for all `VectorFont`s).
        Request<Material> material_parent {};
        float vertex_scaling_factor     { 0.001f };  // Default value.
        std::string font_file_format;    // type of the font file. supported file formats so far: `"svg"`/`"SVG"`.
        std::string font_filename;       // filename of the font file.
    };
}

#endif
