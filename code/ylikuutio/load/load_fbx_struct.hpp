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

#ifndef YLIKUUTIO_LOAD_LOAD_FBX_STRUCT_HPP_INCLUDED
#define YLIKUUTIO_LOAD_LOAD_FBX_STRUCT_HPP_INCLUDED

#include "ufbx.h"

// Include standard headers
#include <cstddef> // std::size_t
#include <vector>  // std::vector

namespace yli::load
{
    struct LoadFbxStruct
    {
        ufbx_load_opts load_opts {};
        std::vector<std::size_t> mesh_material_indices {};
        std::size_t subdivision_level { 0 };
        bool needs_subdivision { true };
        bool apply_to_root_to_vertices { false };
        bool apply_to_root_to_normals { false };
        bool force_apply_to_root_to_vertices { false };
        bool force_apply_to_root_to_normals { false };
        bool is_debug_mode { false };

        LoadFbxStruct()
        {
            this->load_opts.evaluate_skinning = true;
            this->load_opts.load_external_files = false;
            this->load_opts.ignore_missing_external_files = true;
            this->load_opts.generate_missing_normals = true;
            this->load_opts.use_root_transform = false;
            this->load_opts.root_transform.rotation = ufbx_identity_quat;
            this->load_opts.target_unit_meters = 1.0f;
            this->load_opts.target_axes = {
                .right = UFBX_COORDINATE_AXIS_NEGATIVE_Y,
                .up = UFBX_COORDINATE_AXIS_POSITIVE_Z,
                .front = UFBX_COORDINATE_AXIS_NEGATIVE_X
            };

            constexpr ufbx_real scale = 1.0f;
            this->load_opts.root_transform.scale = ufbx_vec3 { .x = scale, .y = scale, .z = scale };
        }
    };
}

#endif
