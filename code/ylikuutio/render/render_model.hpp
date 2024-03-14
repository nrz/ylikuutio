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

#ifndef YLIKUUTIO_RENDER_RENDER_MODEL_HPP_INCLUDED
#define YLIKUUTIO_RENDER_RENDER_MODEL_HPP_INCLUDED

#include "render_templates.hpp"
#include "code/ylikuutio/ontology/mesh_module.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"

namespace yli::ontology
{
    class Scene;
}

namespace yli::render
{
    // ContainerType = container type, CastType = type in which to cast the stored type into.
    template<typename ContainerType, typename CastType>
        void render_model(
                const yli::ontology::MeshModule& mesh,
                ContainerType& renderables_container,
                const yli::ontology::Scene* const scene)
        {
            // 1st attribute buffer: vertices.
            yli::opengl::enable_vertex_attrib_array(mesh.vertex_position_modelspace_id);

            // 2nd attribute buffer: UVs.
            yli::opengl::enable_vertex_attrib_array(mesh.vertex_uv_id);

            // 3rd attribute buffer: normals.
            yli::opengl::enable_vertex_attrib_array(mesh.vertex_normal_modelspace_id);

            // Render this `Species` or `Glyph` by calling `render` function of each `Object`.
            yli::render::render_children_of_given_scene_or_of_all_scenes<ContainerType&, CastType>(renderables_container, scene);

            yli::opengl::disable_vertex_attrib_array(mesh.vertex_position_modelspace_id);
            yli::opengl::disable_vertex_attrib_array(mesh.vertex_uv_id);
            yli::opengl::disable_vertex_attrib_array(mesh.vertex_normal_modelspace_id);
        }
}

#endif
