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

#ifndef __YLIKUUTIO_RENDER_RENDER_SPECIES_OR_GLYPH_HPP_INCLUDED
#define __YLIKUUTIO_RENDER_RENDER_SPECIES_OR_GLYPH_HPP_INCLUDED

#include "render_templates.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

namespace yli::render
{
    // T1: `yli::ontology::Object*` or `yli::ontology::Glyph*`.
    // T2: type of stored child pointers.
    // T3: type in which to cast the child pointers.
    template<class T1, class T2, class T3>
        void render_species_or_glyph(T1 const species_or_glyph_pointer)
        {
            // Compute the MVP matrix from keyboard and mouse input.
            glUniform3f(
                    species_or_glyph_pointer->light_id,
                    species_or_glyph_pointer->light_position.x,
                    species_or_glyph_pointer->light_position.y,
                    species_or_glyph_pointer->light_position.z);

            // 1st attribute buffer: vertices.
            yli::opengl::enable_vertex_attrib_array(species_or_glyph_pointer->vertex_position_modelspace_id);

            // 2nd attribute buffer: UVs.
            yli::opengl::enable_vertex_attrib_array(species_or_glyph_pointer->vertex_uv_id);

            // 3rd attribute buffer: normals.
            yli::opengl::enable_vertex_attrib_array(species_or_glyph_pointer->vertex_normal_modelspace_id);

            // Render this `Species` or `Glyph` by calling `render()` function of each `Object`.
            yli::render::render_children<T2, T3>(species_or_glyph_pointer->parent_of_objects.child_pointer_vector);

            yli::opengl::disable_vertex_attrib_array(species_or_glyph_pointer->vertex_position_modelspace_id);
            yli::opengl::disable_vertex_attrib_array(species_or_glyph_pointer->vertex_uv_id);
            yli::opengl::disable_vertex_attrib_array(species_or_glyph_pointer->vertex_normal_modelspace_id);
        }
}

#endif
