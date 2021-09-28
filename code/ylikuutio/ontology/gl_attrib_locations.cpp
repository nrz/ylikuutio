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

#include "gl_attrib_locations.hpp"
#include "shader.hpp"
#include "mesh_module.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

namespace yli::ontology
{
    void set_gl_attrib_locations(yli::ontology::Shader* const shader, yli::ontology::MeshModule* const mesh_module)
    {
        if (shader != nullptr && mesh_module != nullptr)
        {
            mesh_module->set_vertex_position_modelspace_id(glGetAttribLocation(shader->get_program_id(), "vertex_position_modelspace"));
            mesh_module->set_vertex_uv_id(glGetAttribLocation(shader->get_program_id(), "vertexUV"));
            mesh_module->set_vertex_normal_modelspace_id(glGetAttribLocation(shader->get_program_id(), "vertex_normal_modelspace"));
        }
    }
}
