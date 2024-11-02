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
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/brain.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/request.hpp"
#include "code/ylikuutio/ontology/brain_struct.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"

// Include standard headers
#include <limits>  // std::numeric_limits
#include <cstddef> // std::size_t, uintptr_t

namespace yli::ontology
{
    class Movable;
    class CallbackEngine;
}

TEST(brain_must_be_initialized_appropriately, headless_with_parent_provided_as_valid_pointer)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::BrainStruct brain_struct(
            (yli::ontology::Request(scene)),
            (yli::ontology::Request<yli::ontology::CallbackEngine>(nullptr)));
    yli::ontology::Brain* const brain = application.get_generic_entity_factory().create_brain(
            brain_struct);
    ASSERT_NE(brain, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(brain) % alignof(yli::ontology::Brain), 0);

    ASSERT_NE(brain->get_generic_master_module<yli::ontology::Movable>(), nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_scene(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 2);

    // `Brain` member functions.
    ASSERT_EQ(brain->get_number_of_apprentices(), 0);

    // `Entity` member functions.
    ASSERT_EQ(brain->get_childID(), 0);
    ASSERT_EQ(brain->get_type(), "yli::ontology::Brain*");
    ASSERT_TRUE(brain->get_can_be_erased());
    ASSERT_EQ(brain->get_scene(), scene);
    ASSERT_EQ(brain->get_parent(), scene);
    ASSERT_EQ(brain->get_number_of_non_variable_children(), 0);
}

TEST(brain_must_be_initialized_appropriately, headless_with_parent_provided_as_nullptr)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::BrainStruct brain_struct(
            (yli::ontology::Request<yli::ontology::Scene>(nullptr)),
            (yli::ontology::Request<yli::ontology::CallbackEngine>(nullptr)));
    yli::ontology::Brain* const brain = application.get_generic_entity_factory().create_brain(
            brain_struct);
    ASSERT_NE(brain, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(brain) % alignof(yli::ontology::Brain), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_scene(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 1); // Default `Camera`.

    // `Brain` member functions.
    ASSERT_EQ(brain->get_number_of_apprentices(), 0);

    // `Entity` member functions.
    ASSERT_EQ(brain->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(brain->get_type(), "yli::ontology::Brain*");
    ASSERT_TRUE(brain->get_can_be_erased());
    ASSERT_EQ(brain->get_scene(), nullptr);
    ASSERT_EQ(brain->get_parent(), nullptr);
    ASSERT_EQ(brain->get_number_of_non_variable_children(), 0);
}

TEST(brain_must_be_initialized_appropriately, headless_with_parent_provided_as_valid_global_name)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    scene_struct.global_name = "foo";
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::BrainStruct brain_struct(
            (yli::ontology::Request<yli::ontology::Scene>("foo")),
            (yli::ontology::Request<yli::ontology::CallbackEngine>(nullptr)));
    yli::ontology::Brain* const brain = application.get_generic_entity_factory().create_brain(
            brain_struct);
    ASSERT_NE(brain, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(brain) % alignof(yli::ontology::Brain), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_scene(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 2);

    // `Brain` member functions.
    ASSERT_EQ(brain->get_number_of_apprentices(), 0);

    // `Entity` member functions.
    ASSERT_EQ(brain->get_childID(), 0);
    ASSERT_EQ(brain->get_type(), "yli::ontology::Brain*");
    ASSERT_TRUE(brain->get_can_be_erased());
    ASSERT_EQ(brain->get_scene(), scene);
    ASSERT_EQ(brain->get_parent(), scene);
    ASSERT_EQ(brain->get_number_of_non_variable_children(), 0);
}

TEST(brain_must_be_initialized_appropriately, headless_with_parent_provided_as_invalid_global_name)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    scene_struct.global_name = "foo";
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::BrainStruct brain_struct(
            (yli::ontology::Request<yli::ontology::Scene>("bar")),
            (yli::ontology::Request<yli::ontology::CallbackEngine>(nullptr)));
    yli::ontology::Brain* const brain = application.get_generic_entity_factory().create_brain(
            brain_struct);
    ASSERT_NE(brain, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(brain) % alignof(yli::ontology::Brain), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_scene(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 1); // Default `Camera`.

    // `Brain` member functions.
    ASSERT_EQ(brain->get_number_of_apprentices(), 0);

    // `Entity` member functions.
    ASSERT_EQ(brain->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(brain->get_type(), "yli::ontology::Brain*");
    ASSERT_TRUE(brain->get_can_be_erased());
    ASSERT_EQ(brain->get_scene(), nullptr);
    ASSERT_EQ(brain->get_parent(), nullptr);
    ASSERT_EQ(brain->get_number_of_non_variable_children(), 0);
}
