// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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
#include "code/ylikuutio/ontology/scene_struct.hpp"

TEST(scene_must_be_initialized_appropriately, headless)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_entity_factory().create_scene(
            scene_struct);

    // `Universe` member functions.
    ASSERT_EQ(application.get_universe().get_number_of_ecosystems(), 0);
    ASSERT_EQ(application.get_universe().get_number_of_scenes(), 1);
    ASSERT_EQ(application.get_universe().get_active_scene(), nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions.
    ASSERT_EQ(scene->get_childID(), 0);
    ASSERT_EQ(scene->get_type(), "yli::ontology::Scene*");
    ASSERT_TRUE(scene->get_can_be_erased());
    ASSERT_EQ(scene->get_scene(), scene);
    ASSERT_EQ(scene->get_parent(), &application.get_universe());
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 1);
}

TEST(scene_must_be_activated_appropriately, scene)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_entity_factory().create_scene(
            scene_struct);

    ASSERT_EQ(application.get_universe().get_active_scene(), nullptr);
    application.get_universe().set_active_scene(scene);
    ASSERT_EQ(application.get_universe().get_active_scene(), scene);
}

TEST(scene_must_be_given_a_global_name_appropriately, headless)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_entity_factory().create_scene(
            scene_struct);
    ASSERT_EQ(scene->get_global_name(), "");
    ASSERT_EQ(scene->get_local_name(), "");

    // `Scene`s are children of the `Universe` and thus global name is local name, and vice versa.
    scene->set_global_name("foo");
    ASSERT_EQ(scene->get_global_name(), "foo");
    ASSERT_EQ(scene->get_local_name(), "foo");
    ASSERT_TRUE(application.get_universe().has_child("foo"));
    ASSERT_EQ(application.get_universe().get_entity("foo"), scene);
}

TEST(scene_must_be_given_a_local_name_appropriately, headless)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_entity_factory().create_scene(
            scene_struct);
    ASSERT_EQ(scene->get_global_name(), "");
    ASSERT_EQ(scene->get_local_name(), "");

    // `Scene`s are children of the `Universe` and thus global name is local name, and vice versa.
    scene->set_local_name("foo");
    ASSERT_EQ(scene->get_global_name(), "foo");
    ASSERT_EQ(scene->get_local_name(), "foo");
    ASSERT_TRUE(application.get_universe().has_child("foo"));
    ASSERT_EQ(application.get_universe().get_entity("foo"), scene);
}

TEST(scene_must_be_given_a_global_name_appropriately_after_setting_a_global_name, headless)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_entity_factory().create_scene(
            scene_struct);
    ASSERT_EQ(scene->get_global_name(), "");
    ASSERT_EQ(scene->get_local_name(), "");

    // `Scene`s are children of the `Universe` and thus global name is local name, and vice versa.
    scene->set_global_name("foo");
    scene->set_global_name("bar");
    ASSERT_EQ(scene->get_global_name(), "bar");
    ASSERT_EQ(scene->get_local_name(), "bar");
    ASSERT_FALSE(application.get_universe().has_child("foo"));
    ASSERT_TRUE(application.get_universe().has_child("bar"));
    ASSERT_EQ(application.get_universe().get_entity("foo"), nullptr);
    ASSERT_EQ(application.get_universe().get_entity("bar"), scene);
}

TEST(scene_must_be_given_a_local_name_appropriately_after_setting_a_local_name, headless)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_entity_factory().create_scene(
            scene_struct);
    ASSERT_EQ(scene->get_global_name(), "");
    ASSERT_EQ(scene->get_local_name(), "");

    // `Scene`s are children of the `Universe` and thus global name is local name, and vice versa.
    scene->set_local_name("foo");
    scene->set_local_name("bar");
    ASSERT_EQ(scene->get_global_name(), "bar");
    ASSERT_EQ(scene->get_local_name(), "bar");
    ASSERT_FALSE(application.get_universe().has_child("foo"));
    ASSERT_TRUE(application.get_universe().has_child("bar"));
    ASSERT_EQ(application.get_universe().get_entity("foo"), nullptr);
    ASSERT_EQ(application.get_universe().get_entity("bar"), scene);
}

TEST(scene_must_be_given_a_global_name_appropriately_after_setting_a_local_name, headless)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_entity_factory().create_scene(
            scene_struct);
    ASSERT_EQ(scene->get_global_name(), "");
    ASSERT_EQ(scene->get_local_name(), "");

    // `Scene`s are children of the `Universe` and thus global name is local name, and vice versa.
    scene->set_local_name("foo");
    scene->set_global_name("bar");
    ASSERT_EQ(scene->get_global_name(), "bar");
    ASSERT_EQ(scene->get_local_name(), "bar");
    ASSERT_FALSE(application.get_universe().has_child("foo"));
    ASSERT_TRUE(application.get_universe().has_child("bar"));
    ASSERT_EQ(application.get_universe().get_entity("foo"), nullptr);
    ASSERT_EQ(application.get_universe().get_entity("bar"), scene);
}

TEST(scene_must_be_given_a_local_name_appropriately_after_setting_a_global_name, headless)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_entity_factory().create_scene(
            scene_struct);
    ASSERT_EQ(scene->get_global_name(), "");
    ASSERT_EQ(scene->get_local_name(), "");

    // `Scene`s are children of the `Universe` and thus global name is local name, and vice versa.
    scene->set_global_name("foo");
    scene->set_local_name("bar");
    ASSERT_EQ(scene->get_global_name(), "bar");
    ASSERT_EQ(scene->get_local_name(), "bar");
    ASSERT_FALSE(application.get_universe().has_child("foo"));
    ASSERT_TRUE(application.get_universe().has_child("bar"));
    ASSERT_EQ(application.get_universe().get_entity("foo"), nullptr);
    ASSERT_EQ(application.get_universe().get_entity("bar"), scene);
}
