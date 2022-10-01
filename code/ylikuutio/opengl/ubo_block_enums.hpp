// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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

#ifndef YLIKUUTIO_OPENGL_UBO_BLOCK_ENUMS_HPP_INCLUDED
#define YLIKUUTIO_OPENGL_UBO_BLOCK_ENUMS_HPP_INCLUDED

// Include GLM
#ifndef GLM_GLM_HPP_INCLUDED
#define GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

namespace yli::opengl
{
    enum UboBlockIndices
    {
        SCENE = 0,
        MOVABLE = 1,
        CAMERA = 2
    };

    namespace scene_ubo
    {
        enum SceneUboBlockOffsets
        {
            LIGHT_POSITION_WORLDSPACE = 0,   // vec4
            WATER_LEVEL = sizeof(glm::vec4), // float
            TOTAL_SIZE = yli::opengl::scene_ubo::SceneUboBlockOffsets::WATER_LEVEL + sizeof(float)
        };
    }

    namespace movable_ubo
    {
        enum MovableUboBlockOffsets
        {
            MVP = 0,                                                                       // mat4
            M = yli::opengl::movable_ubo::MovableUboBlockOffsets::MVP + sizeof(glm::mat4), // mat4
            TOTAL_SIZE = yli::opengl::movable_ubo::MovableUboBlockOffsets::M + sizeof(glm::mat4)
        };
    }

    namespace camera_ubo
    {
        enum CameraUboBlockOffsets
        {
            V = 0, // mat4
            TOTAL_SIZE = yli::opengl::camera_ubo::CameraUboBlockOffsets::V + sizeof(glm::mat4)
        };
    }
}

#endif

