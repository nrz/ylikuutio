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
#include "request.hpp"

// Include standard headers
#include <utility> // std::move
#include <vector>  // std::vector

namespace yli::ontology
{
    class Material;
    class VectorFont;

    struct GlyphStruct final : public MeshProviderStruct
    {
        GlyphStruct(
                Request<VectorFont>&& vector_font_parent,
                Request<Material>&& material_master)
            : vector_font_parent { std::move(vector_font_parent) },
            material_master { std::move(material_master) }
        {
        }

        Request<VectorFont> vector_font_parent {};
        Request<Material> material_master      {};
        std::vector<std::vector<glm::vec2>>* glyph_vertex_data { nullptr }; // For `Glyph`s.
        const char* glyph_name_pointer         { nullptr }; // We need only a pointer, because `Glyph`s are always created by the `VectorFont` constructor.
        const char* unicode_char_pointer       { nullptr }; // We need only a pointer, because `Glyph`s are always created by the `VectorFont` constructor.
    };
}

#endif
