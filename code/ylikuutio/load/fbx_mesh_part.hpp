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

#ifndef YLIKUUTIO_LOAD_FBX_MESH_PART_HPP_INCLUDED
#define YLIKUUTIO_LOAD_FBX_MESH_PART_HPP_INCLUDED

#include "fbx_buffer_resource.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <cstdint> // std::int32_t

namespace yli::load
{
    struct FbxMeshPart
    {
        FbxBufferResource vertex_buffer;
        FbxBufferResource index_buffer;
        FbxBufferResource skin_buffer; // Optional.

        std::size_t num_indices { 0 };
        std::int32_t material_index { -1 };
    };
}

#endif
