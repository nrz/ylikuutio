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

#ifndef YLIKUUTIO_RENDER_RENDER_TEXT_HPP_INCLUDED
#define YLIKUUTIO_RENDER_RENDER_TEXT_HPP_INCLUDED

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
            const GLint vertex_uv_id);
}

#endif
