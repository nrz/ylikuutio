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
#include "code/ylikuutio/ontology/brain.hpp"
#include "code/ylikuutio/ontology/waypoint.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/waypoint.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/waypoint_struct.hpp"

// Include standard headers
#include <limits>  // std::numeric_limits
#include <cstddef> // std::size_t, uintptr_t

TEST(waypoint_must_be_initialized_appropriately, headless_with_parent_provided_as_valid_pointer)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::BrainStruct brain_struct(scene, nullptr);
    yli::ontology::Brain* const brain = application.get_generic_entity_factory().create_brain(
            brain_struct);

    yli::ontology::WaypointStruct waypoint_struct(brain, scene);
    yli::ontology::Waypoint* const waypoint = application.get_generic_entity_factory().create_waypoint(
            waypoint_struct);
    ASSERT_NE(waypoint, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(waypoint) % alignof(yli::ontology::Waypoint), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_scene(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 3); // Default `Camera`, `Brain`, `Waypoint`.

    // `Entity` member functions.
    ASSERT_EQ(waypoint->get_childID(), 0);
    ASSERT_EQ(waypoint->get_type(), "yli::ontology::Waypoint*");
    ASSERT_TRUE(waypoint->get_can_be_erased());
    ASSERT_EQ(waypoint->get_scene(), scene);
    ASSERT_EQ(waypoint->get_parent(), scene);
    ASSERT_EQ(waypoint->get_number_of_non_variable_children(), 0);
}

TEST(waypoint_must_be_initialized_appropriately, headless_with_parent_provided_as_nullptr)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::BrainStruct brain_struct(scene, nullptr);
    yli::ontology::Brain* const brain = application.get_generic_entity_factory().create_brain(
            brain_struct);

    yli::ontology::WaypointStruct waypoint_struct(brain, nullptr);
    yli::ontology::Waypoint* const waypoint = application.get_generic_entity_factory().create_waypoint(
            waypoint_struct);
    ASSERT_NE(waypoint, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(waypoint) % alignof(yli::ontology::Waypoint), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_scene(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 2); // Default `Camera`, `Brain`.

    // `Entity` member functions.
    ASSERT_EQ(waypoint->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(waypoint->get_type(), "yli::ontology::Waypoint*");
    ASSERT_TRUE(waypoint->get_can_be_erased());
    ASSERT_EQ(waypoint->get_scene(), nullptr);
    ASSERT_EQ(waypoint->get_parent(), nullptr);
    ASSERT_EQ(waypoint->get_number_of_non_variable_children(), 0);
}

TEST(waypoint_must_be_initialized_appropriately, headless_with_parent_provided_as_valid_global_name)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    scene_struct.global_name = "foo";
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::BrainStruct brain_struct(scene, nullptr);
    yli::ontology::Brain* const brain = application.get_generic_entity_factory().create_brain(
            brain_struct);

    yli::ontology::WaypointStruct waypoint_struct(brain, "foo");
    yli::ontology::Waypoint* const waypoint = application.get_generic_entity_factory().create_waypoint(
            waypoint_struct);
    ASSERT_NE(waypoint, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(waypoint) % alignof(yli::ontology::Waypoint), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_scene(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 3); // Default `Camera`, `Brain`, `Waypoint`.

    // `Entity` member functions.
    ASSERT_EQ(waypoint->get_childID(), 0);
    ASSERT_EQ(waypoint->get_type(), "yli::ontology::Waypoint*");
    ASSERT_TRUE(waypoint->get_can_be_erased());
    ASSERT_EQ(waypoint->get_scene(), scene);
    ASSERT_EQ(waypoint->get_parent(), scene);
    ASSERT_EQ(waypoint->get_number_of_non_variable_children(), 0);
}

TEST(waypoint_must_be_initialized_appropriately, headless_with_parent_provided_as_invalid_global_name)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    scene_struct.global_name = "foo";
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::BrainStruct brain_struct(scene, nullptr);
    yli::ontology::Brain* const brain = application.get_generic_entity_factory().create_brain(
            brain_struct);

    yli::ontology::WaypointStruct waypoint_struct(brain, "bar");
    yli::ontology::Waypoint* const waypoint = application.get_generic_entity_factory().create_waypoint(
            waypoint_struct);
    ASSERT_NE(waypoint, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(waypoint) % alignof(yli::ontology::Waypoint), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_scene(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 2); // Default `Camera`, `Brain`.

    // `Entity` member functions.
    ASSERT_EQ(waypoint->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(waypoint->get_type(), "yli::ontology::Waypoint*");
    ASSERT_TRUE(waypoint->get_can_be_erased());
    ASSERT_EQ(waypoint->get_scene(), nullptr);
    ASSERT_EQ(waypoint->get_parent(), nullptr);
    ASSERT_EQ(waypoint->get_number_of_non_variable_children(), 0);
}
