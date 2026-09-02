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

#include "read_fbx_node.hpp"
#include "fbx_node.hpp"
#include "convert_ufbx_matrix_to_glm_mat4.hpp"
#include <ufbx.h>

namespace yli::load
{
    FbxNode read_fbx_node(const ufbx_node& node)
    {
        FbxNode fbx_node {};
        fbx_node.parent_index = node.parent != nullptr ? static_cast<std::int32_t>(node.parent->typed_id) : -1;
        fbx_node.node_to_parent = convert_ufbx_matrix_to_glm_mat4(&node.node_to_parent);
        fbx_node.node_to_world = convert_ufbx_matrix_to_glm_mat4(&node.node_to_world);
        fbx_node.geometry_to_node = convert_ufbx_matrix_to_glm_mat4(&node.geometry_to_node);
        fbx_node.geometry_to_world = convert_ufbx_matrix_to_glm_mat4(&node.geometry_to_world);
        // fbx_node.normal_to_world = compute_normals(convert_ufbx_matrix_to_glm_mat4(&node->geometry_to_world)); // TODO!
        // FIXME: implement the normal computation above, otherwise this function should be fine!
        return fbx_node;
    }
}
