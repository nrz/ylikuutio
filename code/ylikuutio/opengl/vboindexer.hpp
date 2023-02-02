// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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

#ifndef YLIKUUTIO_OPENGL_VBOINDEXER_HPP_INCLUDED
#define YLIKUUTIO_OPENGL_VBOINDEXER_HPP_INCLUDED

// Include GLM
#ifndef GLM_GLM_HPP_INCLUDED
#define GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <stdint.h>  // uint32_t etc.
#include <vector>    // std::vector

namespace yli::opengl
{
    void indexVBO(
            const std::vector<glm::vec3>& in_vertices,
            const std::vector<glm::vec2>& in_uvs,
            const std::vector<glm::vec3>& in_normals,
            std::vector<uint32_t>& out_indices,
            std::vector<glm::vec3>& out_vertices,
            std::vector<glm::vec2>& out_uvs,
            std::vector<glm::vec3>& out_normals
            );
}

#endif
