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

#ifndef __GLYPH_STRUCT_HPP_INCLUDED
#define __GLYPH_STRUCT_HPP_INCLUDED

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <vector>   // std::vector

namespace yli::ontology
{
    class Universe;
    class Shader;
    class VectorFont;

    struct GlyphStruct
    {
        GlyphStruct()
            : light_position(glm::vec3(0.0f, 0.0f, 0.0f)),
            glyph_vertex_data(nullptr),
            glyph_name_pointer(nullptr),
            unicode_char_pointer(nullptr),
            universe(nullptr),
            shader_pointer(nullptr),
            parent(nullptr),
            opengl_in_use(true)
        {
            // constructor.
        }

        glm::vec3 light_position;              // light position.
        std::vector<std::vector<glm::vec2>>* glyph_vertex_data;
        const char* glyph_name_pointer;        // we need only a pointer, because `Glyph`s are always created by the `VectorFont` constructor.
        const char* unicode_char_pointer;      // we need only a pointer, because `Glyph`s are always created by the `VectorFont` constructor.
        yli::ontology::Universe* universe;     // pointer to the `Universe` (not a parent!).
        yli::ontology::Shader* shader_pointer; // pointer to the `Shader` (not a parent!).
        yli::ontology::VectorFont* parent;     // pointer to the `VectorFont`.
        bool opengl_in_use;                    // If `opengl_in_use` is `false, then no OpenGL-specific code shall be executed.
    };
}

#endif
