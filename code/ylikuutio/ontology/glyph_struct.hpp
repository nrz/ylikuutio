// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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

#ifndef YLIKUUTIO_ONTOLOGY_GLYPH_STRUCT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_GLYPH_STRUCT_HPP_INCLUDED

#include "mesh_provider_struct.hpp"

// Include GLM
#ifndef GLM_GLM_HPP_INCLUDED
#define GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <vector> // std::vector

namespace yli::ontology
{
    class VectorFont;

    struct GlyphStruct final : public MeshProviderStruct
    {
        explicit GlyphStruct(
                VectorFont* const vector_font_parent)
            : MeshProviderStruct(vector_font_parent)
        {
        }

        std::vector<std::vector<glm::vec2>>* glyph_vertex_data { nullptr }; // For `Glyph`s.
        const char* glyph_name_pointer         { nullptr }; // We need only a pointer, because `Glyph`s are always created by the `VectorFont` constructor.
        const char* unicode_char_pointer       { nullptr }; // We need only a pointer, because `Glyph`s are always created by the `VectorFont` constructor.
    };
}

#endif
