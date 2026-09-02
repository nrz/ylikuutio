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

#ifndef YLIKUUTIO_LOAD_READ_FBX_ANIM_STACK_SCENE_HPP_INCLUDED
#define YLIKUUTIO_LOAD_READ_FBX_ANIM_STACK_SCENE_HPP_INCLUDED

#include "fbx_anim.hpp"
#include <ufbx.h>

namespace yli::load
{
    struct viewer_anim;

    FbxAnim read_fbx_anim_stack(const ufbx_anim_stack& stack, const ufbx_scene& scene);
}

#endif
