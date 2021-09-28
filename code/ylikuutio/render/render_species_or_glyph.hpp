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

#ifndef __YLIKUUTIO_RENDER_RENDER_SPECIES_OR_GLYPH_HPP_INCLUDED
#define __YLIKUUTIO_RENDER_RENDER_SPECIES_OR_GLYPH_HPP_INCLUDED

#include "render_templates.hpp"
#include "code/ylikuutio/ontology/model_module.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

namespace yli::render
{
    // ContainerType = container type, T1 = stored type, CastType = type in which to cast the stored type into.
    template<class ContainerType, class StoredType, class CastType>
        void render_model(const yli::ontology::ModelModule& model, ContainerType& renderables_container)
        {
            // Compute the MVP matrix from keyboard and mouse input.
            glUniform3f(
                    model.light_id,
                    model.light_position.x,
                    model.light_position.y,
                    model.light_position.z);

            // 1st attribute buffer: vertices.
            yli::opengl::enable_vertex_attrib_array(model.vertex_position_modelspace_id);

            // 2nd attribute buffer: UVs.
            yli::opengl::enable_vertex_attrib_array(model.vertex_uv_id);

            // 3rd attribute buffer: normals.
            yli::opengl::enable_vertex_attrib_array(model.vertex_normal_modelspace_id);

            // Render this `Species` or `Glyph` by calling `render()` function of each `Object`.
            yli::render::render_children<ContainerType&, StoredType, CastType>(renderables_container);

            yli::opengl::disable_vertex_attrib_array(model.vertex_position_modelspace_id);
            yli::opengl::disable_vertex_attrib_array(model.vertex_uv_id);
            yli::opengl::disable_vertex_attrib_array(model.vertex_normal_modelspace_id);
        }
}

#endif
