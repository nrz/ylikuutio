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

#ifndef YLIKUUTIO_LOAD_FBX_NODE_ANIM_HPP_INCLUDED
#define YLIKUUTIO_LOAD_FBX_NODE_ANIM_HPP_INCLUDED

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

#ifndef __GLM_GTC_QUATERNION_HPP_INCLUDED
#define __GLM_GTC_QUATERNION_HPP_INCLUDED
#include <glm/gtc/quaternion.hpp> // glm::quat
#endif

// Include standard headers
#include <cstddef> // std::size_t

namespace yli::load
{
    struct FbxNodeAnim
    {
        float time_begin { NAN };
        float framerate { NAN };
        std::size_t num_frames { 0 };
        glm::quat const_rot { glm::vec3(NAN, NAN, NAN) };
        glm::vec3 const_pos { NAN };
        glm::vec3 const_scale { NAN };
        glm::quat rot { glm::vec3(NAN, NAN, NAN) };
        glm::vec3 pos { NAN };
        glm::vec3 scale { NAN };
    };
}

#endif
