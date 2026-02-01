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

#include "gtest/gtest.h"
#include "code/mock/mock_application.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/camera.hpp"
#include "code/ylikuutio/ontology/request.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/camera_struct.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef> // std::size_t, uintptr_t
#include <limits>  // std::numeric_limits

TEST(camera_must_be_initialized_and_must_bind_to_scene_appropriately, headless_with_parent_provided_as_valid_pointer)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::CameraStruct camera_struct { yli::ontology::Request(scene) };
    yli::ontology::Camera* const camera = application.get_generic_entity_factory().create_camera(
            camera_struct);
    ASSERT_NE(camera, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(camera) % alignof(yli::ontology::Camera), 0);

    const glm::mat4& projection_matrix = camera->get_projection_matrix();
    ASSERT_EQ(projection_matrix, glm::mat4(1.0f));
    const glm::mat4& view_matrix = camera->get_view_matrix();
    ASSERT_EQ(view_matrix, glm::mat4(1.0f));

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_scene(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 2); // Default `Camera`, `camera`.

    // `Entity` member functions.
    ASSERT_EQ(camera->get_childID(), 1); // Default `Camera` has id 0.
    ASSERT_EQ(camera->get_type(), "yli::ontology::Camera*");
    ASSERT_TRUE(camera->get_can_be_erased());
    ASSERT_EQ(camera->get_scene(), scene);
    ASSERT_EQ(camera->get_parent(), scene);
    ASSERT_EQ(camera->get_number_of_non_variable_children(), 0);
}

TEST(camera_must_be_initialized_and_must_bind_to_scene_appropriately, headless_with_parent_provided_as_nullptr)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::CameraStruct camera_struct { yli::ontology::Request<yli::ontology::Scene>(nullptr) };
    yli::ontology::Camera* const camera = application.get_generic_entity_factory().create_camera(
            camera_struct);
    ASSERT_NE(camera, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(camera) % alignof(yli::ontology::Camera), 0);

    const glm::mat4& projection_matrix = camera->get_projection_matrix();
    ASSERT_EQ(projection_matrix, glm::mat4(1.0f));
    const glm::mat4& view_matrix = camera->get_view_matrix();
    ASSERT_EQ(view_matrix, glm::mat4(1.0f));

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_scene(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 1); // Default `Camera`.

    // `Entity` member functions.
    ASSERT_EQ(camera->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(camera->get_type(), "yli::ontology::Camera*");
    ASSERT_TRUE(camera->get_can_be_erased());
    ASSERT_EQ(camera->get_scene(), nullptr);
    ASSERT_EQ(camera->get_parent(), nullptr);
    ASSERT_EQ(camera->get_number_of_non_variable_children(), 0);
}

TEST(camera_must_be_initialized_and_must_bind_to_scene_appropriately, headless_with_parent_provided_as_valid_global_name)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    scene_struct.global_name = "foo";
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::CameraStruct camera_struct { yli::ontology::Request<yli::ontology::Scene>("foo") };
    yli::ontology::Camera* const camera = application.get_generic_entity_factory().create_camera(
            camera_struct);
    ASSERT_NE(camera, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(camera) % alignof(yli::ontology::Camera), 0);

    const glm::mat4& projection_matrix = camera->get_projection_matrix();
    ASSERT_EQ(projection_matrix, glm::mat4(1.0f));
    const glm::mat4& view_matrix = camera->get_view_matrix();
    ASSERT_EQ(view_matrix, glm::mat4(1.0f));

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_scene(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 2); // Default `Camera`, `camera`.

    // `Entity` member functions.
    ASSERT_EQ(camera->get_childID(), 1); // Default `Camera` has id 0.
    ASSERT_EQ(camera->get_type(), "yli::ontology::Camera*");
    ASSERT_TRUE(camera->get_can_be_erased());
    ASSERT_EQ(camera->get_scene(), scene);
    ASSERT_EQ(camera->get_parent(), scene);
    ASSERT_EQ(camera->get_number_of_non_variable_children(), 0);
}

TEST(camera_must_be_initialized_and_must_bind_to_scene_appropriately, headless_with_parent_provided_as_invalid_global_name)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    scene_struct.global_name = "foo";
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::CameraStruct camera_struct { yli::ontology::Request<yli::ontology::Scene>("bar") };
    yli::ontology::Camera* const camera = application.get_generic_entity_factory().create_camera(
            camera_struct);
    ASSERT_NE(camera, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(camera) % alignof(yli::ontology::Camera), 0);

    const glm::mat4& projection_matrix = camera->get_projection_matrix();
    ASSERT_EQ(projection_matrix, glm::mat4(1.0f));
    const glm::mat4& view_matrix = camera->get_view_matrix();
    ASSERT_EQ(view_matrix, glm::mat4(1.0f));

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_scene(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 1); // Default `Camera`.

    // `Entity` member functions.
    ASSERT_EQ(camera->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(camera->get_type(), "yli::ontology::Camera*");
    ASSERT_TRUE(camera->get_can_be_erased());
    ASSERT_EQ(camera->get_scene(), nullptr);
    ASSERT_EQ(camera->get_parent(), nullptr);
    ASSERT_EQ(camera->get_number_of_non_variable_children(), 0);
}
