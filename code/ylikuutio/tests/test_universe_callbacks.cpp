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
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/ontology/entity.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/pipeline.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/camera.hpp"
#include "code/ylikuutio/ontology/font_2d.hpp"
#include "code/ylikuutio/ontology/console.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/pipeline_struct.hpp"
#include "code/ylikuutio/ontology/material_struct.hpp"
#include "code/ylikuutio/ontology/mesh_provider_struct.hpp"
#include "code/ylikuutio/ontology/object_struct.hpp"
#include "code/ylikuutio/ontology/camera_struct.hpp"
#include "code/ylikuutio/ontology/font_struct.hpp"
#include "code/ylikuutio/ontology/console_struct.hpp"

// Include standard headers
#include <string>   // std::string

// Tests for `yli::ontology::Universe` callbacks
// that can be tested in headless mode.

namespace yli::ontology
{
    class Entity;
    class Console;
}

// Public `Entity` activate callbacks.

TEST(scene_must_be_activated_appropriately, universe_callback)
{
    mock::MockApplication application;

    const std::string scene_name = "foo";

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);
    scene->set_global_name(scene_name);

    ASSERT_EQ(application.get_universe().get_active_scene(), scene);

    // TODO: deactivate before activating by creating another `Scene`!
    application.get_universe().activate_entity(*scene);
    ASSERT_EQ(application.get_universe().get_active_scene(), scene);
}

TEST(console_must_be_activated_appropriately, universe_callback_without_font_2d)
{
    mock::MockApplication application;
    const std::string console_name = "foo";

    yli::ontology::ConsoleStruct console_struct;
    yli::ontology::Console* const console = application.get_generic_entity_factory().create_console(
            console_struct);
    console->set_global_name(console_name);

    ASSERT_EQ(application.get_universe().get_active_console(), nullptr);

    application.get_universe().activate_entity(*console);
    ASSERT_EQ(application.get_universe().get_active_console(), console);
}

TEST(console_must_be_activated_appropriately, universe_callback_with_font_2d)
{
    mock::MockApplication application;
    application.get_generic_entity_factory().create_font_2d(
            yli::ontology::FontStruct());

    const std::string console_name = "foo";

    yli::ontology::ConsoleStruct console_struct;
    yli::ontology::Console* const console = application.get_generic_entity_factory().create_console(
            console_struct);
    console->set_global_name(console_name);

    ASSERT_EQ(application.get_universe().get_active_console(), nullptr);

    application.get_universe().activate_entity(*console);
    ASSERT_EQ(application.get_universe().get_active_console(), console);
}

TEST(scene_and_camera_must_be_activated_appropriately, universe_callback)
{
    mock::MockApplication application;

    const std::string scene_name = "foo";

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);
    scene->set_global_name(scene_name);

    yli::ontology::CameraStruct camera_struct { yli::ontology::Request(scene) };
    camera_struct.global_name = "bar";
    yli::ontology::Camera* const camera = application.get_generic_entity_factory().create_camera(camera_struct);

    ASSERT_EQ(application.get_universe().get_active_scene(), scene);
    ASSERT_NE(scene->get_active_camera(), nullptr); // Default `Camera` gets activated.

    application.get_universe().activate_entity(*scene);
    ASSERT_EQ(application.get_universe().get_active_scene(), scene);
    ASSERT_NE(scene->get_active_camera(), nullptr); // Default `Camera` gets activated.

    application.get_universe().activate_entity(*camera);
    ASSERT_EQ(application.get_universe().get_active_scene(), scene);
    ASSERT_EQ(scene->get_active_camera(), camera);
}

// Public YliLisp-related callbacks.
