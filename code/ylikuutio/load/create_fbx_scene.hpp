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

#ifndef YLIKUUTIO_LOAD_CREATE_FBX_SCENE_HPP_INCLUDED
#define YLIKUUTIO_LOAD_CREATE_FBX_SCENE_HPP_INCLUDED

#include "fbx_scene.hpp"
#include <ufbx.h>

// Include standard headers
#include <cstddef>  // std::size_t
#include <optional> // std::optional

namespace yli::load
{
    std::optional<FbxScene> create_fbx_scene(const ufbx_scene& original_scene,
        std::size_t subdivision_level,
        bool needs_subdivision,
        bool is_debug_mode);
}

#endif
