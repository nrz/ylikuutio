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

#ifndef YLIKUUTIO_LOAD_FBX_SCENE_HPP_INCLUDED
#define YLIKUUTIO_LOAD_FBX_SCENE_HPP_INCLUDED

#include "fbx_material.hpp"
#include "fbx_mesh.hpp"
#include "fbx_node.hpp"
#include "fbx_anim.hpp"
#include "fbx_blend_channel.hpp"
#include "fbx_triangle_info.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>  // NAN
#include <vector> // std::vector

namespace yli::load
{
    struct FbxScene
    {
        std::vector<FbxMaterial> materials {};
        std::vector<FbxMesh> meshes {};
        std::vector<FbxNode> nodes {};
        std::vector<FbxTriangleInfo> triangles {};
        std::vector<FbxAnim> animations {};
        std::vector<FbxBlendChannel> blend_channels {};
        glm::vec3 aabb_min { NAN };
        glm::vec3 aabb_max { NAN };
    };
}

#endif
