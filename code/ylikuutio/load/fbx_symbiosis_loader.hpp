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

#ifndef __FBX_SYMBIOSIS_LOADER_HPP_INCLUDED
#define __FBX_SYMBIOSIS_LOADER_HPP_INCLUDED

#include <ofbx.h>

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>       // std::size_t
#include <stdint.h>      // uint32_t etc.
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

namespace yli::load
{
    bool load_fbx(
            const std::string& filename,
            std::vector<std::vector<glm::vec3>>& out_vertices,
            std::vector<std::vector<glm::vec2>>& out_uvs,
            std::vector<std::vector<glm::vec3>>& out_normals,
            std::unordered_map<const ofbx::Texture*, std::vector<int32_t>>& ofbx_diffuse_texture_mesh_map,
            std::vector<const ofbx::Mesh*>& ofbx_meshes,
            std::vector<const ofbx::Texture*>& ofbx_diffuse_texture_vector,
            std::vector<const ofbx::Texture*>& ofbx_normal_texture_vector,
            std::vector<const ofbx::Texture*>& ofbx_count_texture_vector,
            std::size_t& mesh_count,
            const bool is_debug_mode);
}

#endif
