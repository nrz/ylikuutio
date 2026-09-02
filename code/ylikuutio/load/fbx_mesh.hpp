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

#ifndef YLIKUUTIO_LOAD_FBX_MESH_HPP_INCLUDED
#define YLIKUUTIO_LOAD_FBX_MESH_HPP_INCLUDED

#include "fbx_mesh_part.hpp"
#include "fbx_mesh_vertex.hpp"
#include "fbx_image_resource.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>   // NAN
#include <cstdint> // std::int32_t
#include <limits>  // std::numeric_limits
#include <vector>  // std::vector

namespace yli::load
{
    struct FbxMesh
    {
        std::size_t material_i { std::numeric_limits<std::size_t>::max() };
        std::vector<std::int32_t> instance_node_indices {};
        std::size_t num_instances { 0 };

        std::vector<FbxMeshPart> parts {};
        std::size_t num_parts { 0 };

        bool aabb_is_local { false };
        glm::vec3 aabb_min { NAN, NAN, NAN };
        glm::vec3 aabb_max { NAN, NAN, NAN };;

        // Skinning (optional)
        bool skinned { false };
        std::vector<int32_t> bone_indices {};
        std::vector<glm::mat4> bone_matrices {};
        std::size_t num_bones { 0 };

        // Blend shapes (optional)
        FbxImageResource blend_shape_image {};
        std::vector<int32_t> blend_channel_indices {};

        std::vector<FbxMeshVertex> vertices {};
    };
}

#endif
