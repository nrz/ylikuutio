// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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
#include "code/ylikuutio/data/datatype.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"

// Include standard headers
#include <cstddef> // uintptr_t

namespace yli::ontology
{
    class GenericParentModule;
}

TEST(scene_must_be_initialized_appropriately, headless)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);
    ASSERT_NE(scene, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(scene) % alignof(yli::ontology::Scene), 0);

    const yli::ontology::GenericParentModule* parent_of_brains     { nullptr };
    const yli::ontology::GenericParentModule* parent_of_waypoints  { nullptr };
    const yli::ontology::GenericParentModule* parent_of_cameras    { nullptr };
    const yli::ontology::GenericParentModule* parent_of_pipelines  { nullptr };
    const yli::ontology::GenericParentModule* parent_of_materials  { nullptr };
    const yli::ontology::GenericParentModule* parent_of_species    { nullptr };
    const yli::ontology::GenericParentModule* parent_of_objects    { nullptr };
    const yli::ontology::GenericParentModule* parent_of_symbioses  { nullptr };
    const yli::ontology::GenericParentModule* parent_of_holobionts { nullptr };
    const yli::ontology::GenericParentModule* parent_of_shapeshifters { nullptr };
    const yli::ontology::GenericParentModule* parent_of_text_3ds      { nullptr };

    for (int datatype = 0; datatype < yli::data::Datatype::MAX_VALUE; datatype++)
    {
        const yli::ontology::GenericParentModule* const generic_parent_module = scene->get_generic_parent_module(datatype);

        if (datatype == yli::data::Datatype::BRAIN)
        {
            parent_of_brains = generic_parent_module;
            ASSERT_NE(parent_of_brains, nullptr);
        }
        else if (datatype == yli::data::Datatype::WAYPOINT)
        {
            parent_of_waypoints = generic_parent_module;
            ASSERT_NE(parent_of_waypoints, nullptr);
        }
        else if (datatype == yli::data::Datatype::CAMERA)
        {
            parent_of_cameras = generic_parent_module;
            ASSERT_NE(parent_of_cameras, nullptr);
        }
        else if (datatype == yli::data::Datatype::PIPELINE)
        {
            parent_of_pipelines = generic_parent_module;
            ASSERT_NE(parent_of_pipelines, nullptr);
        }
        else if (datatype == yli::data::Datatype::MATERIAL)
        {
            parent_of_materials = generic_parent_module;
            ASSERT_NE(parent_of_materials, nullptr);
        }
        else if (datatype == yli::data::Datatype::SPECIES)
        {
            parent_of_species = generic_parent_module;
            ASSERT_NE(parent_of_species, nullptr);
        }
        else if (datatype == yli::data::Datatype::OBJECT)
        {
            parent_of_objects = generic_parent_module;
            ASSERT_NE(parent_of_objects, nullptr);
        }
        else if (datatype == yli::data::Datatype::SYMBIOSIS)
        {
            parent_of_symbioses = generic_parent_module;
            ASSERT_NE(parent_of_symbioses, nullptr);
        }
        else if (datatype == yli::data::Datatype::HOLOBIONT)
        {
            parent_of_holobionts = generic_parent_module;
            ASSERT_NE(parent_of_holobionts, nullptr);
        }
        else if (datatype == yli::data::Datatype::SHAPESHIFTER)
        {
            parent_of_shapeshifters = generic_parent_module;
            ASSERT_NE(parent_of_cameras, nullptr);
        }
        else if (datatype == yli::data::Datatype::TEXT_3D)
        {
            parent_of_text_3ds = generic_parent_module;
            ASSERT_NE(parent_of_text_3ds, nullptr);
        }
        else
        {
            ASSERT_EQ(generic_parent_module, nullptr);
        }
    }

    ASSERT_LT(parent_of_brains, parent_of_waypoints);
    ASSERT_LT(parent_of_waypoints, parent_of_cameras);
    ASSERT_LT(parent_of_cameras, parent_of_pipelines);
    ASSERT_LT(parent_of_pipelines, parent_of_materials);
    ASSERT_LT(parent_of_materials, parent_of_species);
    ASSERT_LT(parent_of_species, parent_of_objects);
    ASSERT_LT(parent_of_objects, parent_of_symbioses);
    ASSERT_LT(parent_of_symbioses, parent_of_holobionts);
    ASSERT_LT(parent_of_holobionts, parent_of_shapeshifters);
    ASSERT_LT(parent_of_shapeshifters, parent_of_text_3ds);

    // `Universe` member functions.
    ASSERT_EQ(application.get_universe().get_number_of_ecosystems(), 0);
    ASSERT_EQ(application.get_universe().get_number_of_scenes(), 1);
    ASSERT_EQ(application.get_universe().get_active_scene(), scene); // If there is no active `Scene`, newly created `Scene` becomes active.

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
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    ASSERT_EQ(application.get_universe().get_active_scene(), scene);
    application.get_universe().set_active_scene(nullptr);
    ASSERT_EQ(application.get_universe().get_active_scene(), nullptr);
    application.get_universe().set_active_scene(scene);
    ASSERT_EQ(application.get_universe().get_active_scene(), scene);
}

TEST(scene_must_be_given_a_global_name_appropriately, headless)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
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
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
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
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
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
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
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
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
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
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
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
