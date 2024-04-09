// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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

#include "gtest/gtest.h"
#include "code/mock/mock_application.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/camera.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/camera_struct.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef> // uintptr_t

TEST(camera_must_be_initialized_and_must_bind_to_scene_appropriately, headless)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);
    ASSERT_NE(scene, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(scene) % alignof(yli::ontology::Scene), 0);

    yli::ontology::CameraStruct camera_struct;
    camera_struct.scene = scene;
    yli::ontology::Camera* const camera = application.get_generic_entity_factory().create_camera(
            camera_struct);
    ASSERT_NE(camera, nullptr);
    const glm::mat4& projection_matrix = camera->get_projection_matrix();
    ASSERT_EQ(projection_matrix, glm::mat4(1.0f));
    const glm::mat4& view_matrix = camera->get_view_matrix();
    ASSERT_EQ(view_matrix, glm::mat4(1.0f));
}
