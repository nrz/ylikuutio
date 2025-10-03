// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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

#include "render_text.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <vector> // std::vector

namespace yli::render
{
    void render_text(
            const std::vector<glm::vec2>& vertices,
            const std::vector<glm::vec2>& uvs,
            const GLuint vao,
            const GLuint vertex_buffer,
            const GLuint uv_buffer,
            const GLint vertex_position_in_screenspace_id,
            const GLint vertex_uv_id)
    {
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
        glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

        // 1st attribute buffer: vertices.
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glVertexAttribPointer(vertex_position_in_screenspace_id, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
        yli::opengl::enable_vertex_attrib_array(vertex_position_in_screenspace_id);

        // 2nd attribute buffer: uvs.
        glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
        glVertexAttribPointer(vertex_uv_id, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
        yli::opengl::enable_vertex_attrib_array(vertex_uv_id);

        // Draw call.
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());

        yli::opengl::disable_vertex_attrib_array(vertex_position_in_screenspace_id);
        yli::opengl::disable_vertex_attrib_array(vertex_uv_id);
    }
}
