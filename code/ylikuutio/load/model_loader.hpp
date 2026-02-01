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

#ifndef YLIKUUTIO_LOAD_MODEL_LOADER_HPP_INCLUDED
#define YLIKUUTIO_LOAD_MODEL_LOADER_HPP_INCLUDED

#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include GLM
#ifndef GLM_GLM_HPP_INCLUDED
#define GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace yli::render
{
    enum class GraphicsApiBackend;
}

namespace yli::load
{
    struct ModelLoaderStruct;

    bool load_model(
            const yli::load::ModelLoaderStruct& model_loader_struct,
            std::vector<glm::vec3>& out_vertices,
            std::vector<glm::vec2>& out_uvs,
            std::vector<glm::vec3>& out_normals,
            std::vector<uint32_t>& indices,
            std::vector<glm::vec3>& indexed_vertices,
            std::vector<glm::vec2>& indexed_uvs,
            std::vector<glm::vec3>& indexed_normals,
            GLuint& vao,
            GLuint& vertex_buffer,
            GLuint& uv_buffer,
            GLuint& normal_buffer,
            GLuint& element_buffer,
            const yli::render::GraphicsApiBackend graphics_api_backend,
            const bool is_debug_mode);
}

#endif
