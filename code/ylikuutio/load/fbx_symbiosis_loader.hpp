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

#ifndef YLIKUUTIO_LOAD_FBX_SYMBIOSIS_LOADER_HPP_INCLUDED
#define YLIKUUTIO_LOAD_FBX_SYMBIOSIS_LOADER_HPP_INCLUDED

#include "fbx_material.hpp"
#include "fbx_mesh.hpp"

// Include GLM
#ifndef GLM_GLM_HPP_INCLUDED
#define GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>       // std::size_t
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

namespace yli::load
{
    struct FbxMaterial;

    bool load_fbx(
        const std::string& filename,
        std::vector<std::vector<glm::vec3>>& out_vertices,
        std::vector<std::vector<glm::vec2>>& out_uvs,
        std::vector<std::vector<glm::vec3>>& out_normals,
        std::unordered_map<std::size_t, std::vector<std::size_t>>& fbx_material_mesh_map,
        std::vector<FbxMaterial>& fbx_materials,
        std::vector<FbxMesh>& fbx_meshes,
        std::size_t& mesh_count,
        bool is_debug_mode);
}

#endif
