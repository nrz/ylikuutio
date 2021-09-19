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

#ifndef __YLIKUUTIO_LOAD_MODEL_LOADER_HPP_INCLUDED
#define __YLIKUUTIO_LOAD_MODEL_LOADER_HPP_INCLUDED

#include "species_loader_struct.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace yli::load
{
    bool load_species(
            const yli::load::SpeciesLoaderStruct& species_loader_struct,
            std::vector<glm::vec3>& out_vertices,
            std::vector<glm::vec2>& out_uvs,
            std::vector<glm::vec3>& out_normals,
            std::vector<uint32_t>& indices,
            std::vector<glm::vec3>& indexed_vertices,
            std::vector<glm::vec2>& indexed_uvs,
            std::vector<glm::vec3>& indexed_normals,
            GLuint* vertexbuffer,
            GLuint* uvbuffer,
            GLuint* normalbuffer,
            GLuint* elementbuffer,
            bool& opengl_in_use,
            const bool is_debug_mode);
}

#endif
