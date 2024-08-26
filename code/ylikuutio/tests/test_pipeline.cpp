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
#include "code/ylikuutio/ontology/ecosystem.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/pipeline.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/symbiosis.hpp"
#include "code/ylikuutio/ontology/ecosystem_struct.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/pipeline_struct.hpp"
#include "code/ylikuutio/ontology/material_struct.hpp"
#include "code/ylikuutio/ontology/symbiosis_struct.hpp"

// Include standard headers
#include <cstddef> // std::size_t, uintptr_t
#include <limits>  // std::numeric_limits

TEST(pipeline_must_be_initialized_and_must_bind_to_ecosystem_appropriately, headless_with_ecosystem_parent_provided_as_valid_pointer)
{
    mock::MockApplication application;
    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    yli::ontology::PipelineStruct pipeline_struct(ecosystem);
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);
    ASSERT_NE(pipeline, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(pipeline) % alignof(yli::ontology::Pipeline), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem->get_scene(), nullptr);
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 1); // `pipeline`.

    // `Pipeline` member functions.
    ASSERT_EQ(pipeline->get_number_of_apprentices(), 0);

    // `Entity` member functions.
    ASSERT_EQ(pipeline->get_childID(), 0);
    ASSERT_EQ(pipeline->get_type(), "yli::ontology::Pipeline*");
    ASSERT_TRUE(pipeline->get_can_be_erased());
    ASSERT_EQ(pipeline->get_scene(), nullptr);
    ASSERT_EQ(pipeline->get_parent(), ecosystem);
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 0);
}

TEST(pipeline_must_be_initialized_appropriately, headless_with_scene_parent_provided_as_valid_pointer)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct(scene);
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_scene(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 2); // Default `Camera`, `pipeline`.

    // `Pipeline` member functions.
    ASSERT_EQ(pipeline->get_number_of_apprentices(), 0);

    // `Entity` member functions.
    ASSERT_EQ(pipeline->get_childID(), 0);
    ASSERT_EQ(pipeline->get_type(), "yli::ontology::Pipeline*");
    ASSERT_TRUE(pipeline->get_can_be_erased());
    ASSERT_EQ(pipeline->get_scene(), scene);
    ASSERT_EQ(pipeline->get_parent(), scene);
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 0);
}

TEST(pipeline_must_be_initialized_and_must_bind_to_ecosystem_appropriately, headless_with_ecosystem_parent_provided_as_valid_global_name)
{
    mock::MockApplication application;
    yli::ontology::EcosystemStruct ecosystem_struct;
    ecosystem_struct.global_name = "foo";
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    yli::ontology::PipelineStruct pipeline_struct("foo");
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);
    ASSERT_NE(pipeline, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(pipeline) % alignof(yli::ontology::Pipeline), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem->get_scene(), nullptr);
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 1); // `pipeline`.

    // `Pipeline` member functions.
    ASSERT_EQ(pipeline->get_number_of_apprentices(), 0);

    // `Entity` member functions.
    ASSERT_EQ(pipeline->get_childID(), 0);
    ASSERT_EQ(pipeline->get_type(), "yli::ontology::Pipeline*");
    ASSERT_TRUE(pipeline->get_can_be_erased());
    ASSERT_EQ(pipeline->get_scene(), nullptr);
    ASSERT_EQ(pipeline->get_parent(), ecosystem);
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 0);
}

TEST(pipeline_must_be_initialized_appropriately, headless_with_scene_parent_provided_as_valid_global_name)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    scene_struct.global_name = "foo";
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct("foo");
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_scene(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 2); // Default `Camera`, `pipeline`.

    // `Pipeline` member functions.
    ASSERT_EQ(pipeline->get_number_of_apprentices(), 0);

    // `Entity` member functions.
    ASSERT_EQ(pipeline->get_childID(), 0);
    ASSERT_EQ(pipeline->get_type(), "yli::ontology::Pipeline*");
    ASSERT_TRUE(pipeline->get_can_be_erased());
    ASSERT_EQ(pipeline->get_scene(), scene);
    ASSERT_EQ(pipeline->get_parent(), scene);
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 0);
}

TEST(pipeline_must_be_initialized_and_must_bind_to_ecosystem_appropriately, headless_with_ecosystem_parent_provided_as_invalid_global_name)
{
    mock::MockApplication application;
    yli::ontology::EcosystemStruct ecosystem_struct;
    ecosystem_struct.global_name = "foo";
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    yli::ontology::PipelineStruct pipeline_struct("bar");
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);
    ASSERT_NE(pipeline, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(pipeline) % alignof(yli::ontology::Pipeline), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem->get_scene(), nullptr);
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 0);

    // `Pipeline` member functions.
    ASSERT_EQ(pipeline->get_number_of_apprentices(), 0);

    // `Entity` member functions.
    ASSERT_EQ(pipeline->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(pipeline->get_type(), "yli::ontology::Pipeline*");
    ASSERT_TRUE(pipeline->get_can_be_erased());
    ASSERT_EQ(pipeline->get_scene(), nullptr);
    ASSERT_EQ(pipeline->get_parent(), nullptr);
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 0);
}

TEST(pipeline_must_be_initialized_appropriately, headless_with_scene_parent_provided_as_invalid_global_name)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    scene_struct.global_name = "foo";
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct("bar");
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_scene(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 1); // Default `Camera`.

    // `Pipeline` member functions.
    ASSERT_EQ(pipeline->get_number_of_apprentices(), 0);

    // `Entity` member functions.
    ASSERT_EQ(pipeline->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(pipeline->get_type(), "yli::ontology::Pipeline*");
    ASSERT_TRUE(pipeline->get_can_be_erased());
    ASSERT_EQ(pipeline->get_scene(), nullptr);
    ASSERT_EQ(pipeline->get_parent(), nullptr);
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 0);
}

TEST(pipeline_must_be_initialized_and_must_bind_to_ecosystem_appropriately, headless_with_ecosystem_parent_provided_as_nullptr)
{
    mock::MockApplication application;
    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    yli::ontology::PipelineStruct pipeline_struct(static_cast<yli::ontology::Ecosystem*>(nullptr));
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);
    ASSERT_NE(pipeline, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(pipeline) % alignof(yli::ontology::Pipeline), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem->get_scene(), nullptr);
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 0);

    // `Pipeline` member functions.
    ASSERT_EQ(pipeline->get_number_of_apprentices(), 0);

    // `Entity` member functions.
    ASSERT_EQ(pipeline->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(pipeline->get_type(), "yli::ontology::Pipeline*");
    ASSERT_TRUE(pipeline->get_can_be_erased());
    ASSERT_EQ(pipeline->get_scene(), nullptr);
    ASSERT_EQ(pipeline->get_parent(), nullptr);
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 0);
}

TEST(pipeline_must_be_initialized_appropriately, headless_with_scene_parent_provided_as_nullptr)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct(static_cast<yli::ontology::Scene*>(nullptr));
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_scene(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 1); // Default `Camera`.

    // `Pipeline` member functions.
    ASSERT_EQ(pipeline->get_number_of_apprentices(), 0);

    // `Entity` member functions.
    ASSERT_EQ(pipeline->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(pipeline->get_type(), "yli::ontology::Pipeline*");
    ASSERT_TRUE(pipeline->get_can_be_erased());
    ASSERT_EQ(pipeline->get_scene(), nullptr);
    ASSERT_EQ(pipeline->get_parent(), nullptr);
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 0);
}

TEST(pipeline_must_bind_to_ecosystem_appropriately, headless_with_ecosystem_parents_provided_as_valid_pointers)
{
    mock::MockApplication application;
    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem1 = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    yli::ontology::PipelineStruct pipeline_struct(ecosystem1);
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);
    ASSERT_EQ(pipeline->get_scene(), nullptr);
    ASSERT_EQ(pipeline->get_parent(), ecosystem1);
    ASSERT_EQ(ecosystem1->get_number_of_non_variable_children(), 1);

    yli::ontology::Ecosystem* const ecosystem2 = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    ASSERT_EQ(pipeline->get_scene(), nullptr);
    ASSERT_EQ(pipeline->get_parent(), ecosystem1);
    ASSERT_EQ(ecosystem2->get_number_of_non_variable_children(), 0);

    yli::ontology::Pipeline::bind_to_new_ecosystem_parent(*pipeline, *ecosystem2);
    ASSERT_EQ(pipeline->get_scene(), nullptr);
    ASSERT_EQ(pipeline->get_parent(), ecosystem2);
    ASSERT_EQ(ecosystem1->get_number_of_non_variable_children(), 0);
    ASSERT_EQ(ecosystem2->get_number_of_non_variable_children(), 1);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 2); // `ecosystem1`, `ecosystem2`.

    yli::ontology::Pipeline::bind_to_new_ecosystem_parent(*pipeline, *ecosystem1);
    ASSERT_EQ(pipeline->get_scene(), nullptr);
    ASSERT_EQ(pipeline->get_parent(), ecosystem1);
    ASSERT_EQ(ecosystem1->get_number_of_non_variable_children(), 1);
    ASSERT_EQ(ecosystem2->get_number_of_non_variable_children(), 0);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 2); // `ecosystem1`, `ecosystem2`.
}

TEST(pipeline_must_bind_to_scene_appropriately, headless_with_scene_parents_provided_as_valid_pointers)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene1 = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct(scene1);
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);
    ASSERT_EQ(pipeline->get_scene(), scene1);
    ASSERT_EQ(pipeline->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 2);

    yli::ontology::Scene* const scene2 = application.get_generic_entity_factory().create_scene(
            scene_struct);
    ASSERT_EQ(pipeline->get_scene(), scene1);
    ASSERT_EQ(pipeline->get_parent(), scene1);
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 1);

    yli::ontology::Pipeline::bind_to_new_scene_parent(*pipeline, *scene2);
    ASSERT_EQ(pipeline->get_scene(), scene2);
    ASSERT_EQ(pipeline->get_parent(), scene2);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 1);
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 2);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 2);

    yli::ontology::Pipeline::bind_to_new_scene_parent(*pipeline, *scene1);
    ASSERT_EQ(pipeline->get_scene(), scene1);
    ASSERT_EQ(pipeline->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 2);
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 1);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 2);
}

TEST(pipeline_must_bind_to_ecosystem_appropriately_after_binding_to_scene, headless_with_ecosystem_parent_and_scene_parent_provided_as_valid_pointers)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct(scene);
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);
    ASSERT_EQ(pipeline->get_scene(), scene);
    ASSERT_EQ(pipeline->get_parent(), scene);
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 0);

    yli::ontology::Pipeline::bind_to_new_ecosystem_parent(*pipeline, *ecosystem);
    ASSERT_EQ(pipeline->get_scene(), nullptr);
    ASSERT_EQ(pipeline->get_parent(), ecosystem);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 1);     // Default `Camera`.
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 1); // `pipeline`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 2);  // `ecosystem`, `scene`.

    yli::ontology::Pipeline::bind_to_new_scene_parent(*pipeline, *scene);
    ASSERT_EQ(pipeline->get_scene(), scene);
    ASSERT_EQ(pipeline->get_parent(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 2);     // Default `Camera`, `pipeline`.
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 0);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 2);  // `ecosystem`, `scene`.
}

TEST(pipeline_must_bind_to_scene_appropriately_after_binding_to_ecosystem, headless_with_ecosystem_parent_and_scene_parent_provided_as_valid_pointers)
{
    mock::MockApplication application;
    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    yli::ontology::PipelineStruct pipeline_struct(ecosystem);
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);
    ASSERT_EQ(pipeline->get_scene(), nullptr);
    ASSERT_EQ(pipeline->get_parent(), ecosystem);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 1); // Default `Camera`.

    yli::ontology::Pipeline::bind_to_new_scene_parent(*pipeline, *scene);
    ASSERT_EQ(pipeline->get_scene(), scene);
    ASSERT_EQ(pipeline->get_parent(), scene);
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 0);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 2);     // Default `Camera`, `pipeline`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 2);  // `Ecosystem`, `Scene`.

    yli::ontology::Pipeline::bind_to_new_ecosystem_parent(*pipeline, *ecosystem);
    ASSERT_EQ(pipeline->get_scene(), nullptr);
    ASSERT_EQ(pipeline->get_parent(), ecosystem);
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 1); // `pipeline`.
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 1);     // Default `Camera`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 2);  // `Ecosystem`, `Scene`.
}

TEST(pipeline_must_be_given_a_global_name_appropriately, headless_with_scene_parent_provided_as_valid_pointer)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct(scene);
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);
    ASSERT_EQ(pipeline->get_global_name(), "");
    ASSERT_EQ(pipeline->get_local_name(), "");

    pipeline->set_global_name("foo");
    ASSERT_EQ(pipeline->get_global_name(), "foo");
    ASSERT_EQ(pipeline->get_local_name(), "");
    ASSERT_TRUE(application.get_universe().has_child("foo"));
    ASSERT_FALSE(scene->has_child("foo"));
    ASSERT_EQ(application.get_universe().get_entity("foo"), pipeline);
    ASSERT_EQ(scene->get_entity("foo"), nullptr);
}

TEST(pipeline_must_be_given_a_local_name_appropriately, headless_with_scene_parent_provided_as_valid_pointer)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct(scene);
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);
    ASSERT_EQ(pipeline->get_global_name(), "");
    ASSERT_EQ(pipeline->get_local_name(), "");

    pipeline->set_local_name("foo");
    ASSERT_EQ(pipeline->get_global_name(), "");
    ASSERT_EQ(pipeline->get_local_name(), "foo");
    ASSERT_FALSE(application.get_universe().has_child("foo"));
    ASSERT_TRUE(scene->has_child("foo"));
    ASSERT_EQ(application.get_universe().get_entity("foo"), nullptr);
    ASSERT_EQ(scene->get_entity("foo"), pipeline);
}

TEST(pipeline_must_be_given_a_global_name_appropriately_after_setting_a_global_name, headless_with_scene_parent_provided_as_valid_pointer)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct(scene);
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);
    ASSERT_EQ(pipeline->get_global_name(), "");
    ASSERT_EQ(pipeline->get_local_name(), "");

    pipeline->set_global_name("foo");
    pipeline->set_global_name("bar");
    ASSERT_EQ(pipeline->get_global_name(), "bar");
    ASSERT_EQ(pipeline->get_local_name(), "");
    ASSERT_FALSE(application.get_universe().has_child("foo"));
    ASSERT_TRUE(application.get_universe().has_child("bar"));
    ASSERT_FALSE(scene->has_child("foo"));
    ASSERT_FALSE(scene->has_child("bar"));
    ASSERT_EQ(application.get_universe().get_entity("foo"), nullptr);
    ASSERT_EQ(application.get_universe().get_entity("bar"), pipeline);
    ASSERT_EQ(scene->get_entity("foo"), nullptr);
    ASSERT_EQ(scene->get_entity("bar"), nullptr);
}

TEST(pipeline_must_be_given_a_local_name_appropriately_after_setting_a_local_name, headless_with_scene_parent_provided_as_valid_pointer)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct(scene);
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);
    ASSERT_EQ(pipeline->get_global_name(), "");
    ASSERT_EQ(pipeline->get_local_name(), "");

    pipeline->set_local_name("foo");
    pipeline->set_local_name("bar");
    ASSERT_EQ(pipeline->get_global_name(), "");
    ASSERT_EQ(pipeline->get_local_name(), "bar");
    ASSERT_FALSE(application.get_universe().has_child("foo"));
    ASSERT_FALSE(application.get_universe().has_child("bar"));
    ASSERT_FALSE(scene->has_child("foo"));
    ASSERT_TRUE(scene->has_child("bar"));
    ASSERT_EQ(application.get_universe().get_entity("foo"), nullptr);
    ASSERT_EQ(application.get_universe().get_entity("bar"), nullptr);
    ASSERT_EQ(scene->get_entity("foo"), nullptr);
    ASSERT_EQ(scene->get_entity("bar"), pipeline);
}

TEST(pipeline_must_be_given_a_global_name_appropriately_after_setting_a_local_name, headless_with_scene_parent_provided_as_valid_pointer)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct(scene);
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);
    ASSERT_EQ(pipeline->get_global_name(), "");
    ASSERT_EQ(pipeline->get_local_name(), "");

    pipeline->set_local_name("foo");
    pipeline->set_global_name("bar");
    ASSERT_EQ(pipeline->get_global_name(), "bar");
    ASSERT_EQ(pipeline->get_local_name(), "foo");
    ASSERT_FALSE(application.get_universe().has_child("foo"));
    ASSERT_TRUE(application.get_universe().has_child("bar"));
    ASSERT_TRUE(scene->has_child("foo"));
    ASSERT_FALSE(scene->has_child("bar"));
    ASSERT_EQ(application.get_universe().get_entity("foo"), nullptr);
    ASSERT_EQ(application.get_universe().get_entity("bar"), pipeline);
    ASSERT_EQ(scene->get_entity("foo"), pipeline);
    ASSERT_EQ(scene->get_entity("bar"), nullptr);
}

TEST(pipeline_must_be_given_a_local_name_appropriately_after_setting_a_global_name, headless_with_scene_parent_provided_as_valid_pointer)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct(scene);
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);
    ASSERT_EQ(pipeline->get_global_name(), "");
    ASSERT_EQ(pipeline->get_local_name(), "");

    pipeline->set_global_name("foo");
    pipeline->set_local_name("bar");
    ASSERT_EQ(pipeline->get_global_name(), "foo");
    ASSERT_EQ(pipeline->get_local_name(), "bar");
    ASSERT_TRUE(application.get_universe().has_child("foo"));
    ASSERT_FALSE(application.get_universe().has_child("bar"));
    ASSERT_FALSE(scene->has_child("foo"));
    ASSERT_TRUE(scene->has_child("bar"));
    ASSERT_EQ(application.get_universe().get_entity("foo"), pipeline);
    ASSERT_EQ(application.get_universe().get_entity("bar"), nullptr);
    ASSERT_EQ(scene->get_entity("foo"), nullptr);
    ASSERT_EQ(scene->get_entity("bar"), pipeline);
}

TEST(pipeline_must_maintain_the_local_name_after_binding_to_a_new_parent, headless_universe_pipeline_with_only_local_name)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct1;
    yli::ontology::Scene* const scene1 = application.get_generic_entity_factory().create_scene(
            scene_struct1);

    yli::ontology::PipelineStruct pipeline_struct(scene1);
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::SceneStruct scene_struct2;
    yli::ontology::Scene* const scene2 = application.get_generic_entity_factory().create_scene(
            scene_struct2);

    pipeline->set_local_name("foo");
    yli::ontology::Pipeline::bind_to_new_scene_parent(*pipeline, *scene2);
    ASSERT_FALSE(scene1->has_child("foo"));
    ASSERT_TRUE(scene2->has_child("foo"));
    ASSERT_EQ(pipeline->get_parent(), scene2);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 1);
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 2);

    yli::ontology::Pipeline::bind_to_new_scene_parent(*pipeline, *scene1);
    ASSERT_TRUE(scene1->has_child("foo"));
    ASSERT_FALSE(scene2->has_child("foo"));
    ASSERT_EQ(pipeline->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 2);
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 1);
}

TEST(pipeline_must_maintain_the_local_name_after_binding_to_a_new_parent, headless_universe_pipeline_with_global_name_and_local_name)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct1;
    yli::ontology::Scene* const scene1 = application.get_generic_entity_factory().create_scene(
            scene_struct1);

    yli::ontology::PipelineStruct pipeline_struct(scene1);
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::SceneStruct scene_struct2;
    yli::ontology::Scene* const scene2 = application.get_generic_entity_factory().create_scene(
            scene_struct2);

    pipeline->set_global_name("foo");
    pipeline->set_local_name("bar");
    yli::ontology::Pipeline::bind_to_new_scene_parent(*pipeline, *scene2);
    ASSERT_FALSE(scene1->has_child("foo"));
    ASSERT_FALSE(scene2->has_child("foo"));
    ASSERT_FALSE(scene1->has_child("bar"));
    ASSERT_TRUE(scene2->has_child("bar"));
    ASSERT_EQ(pipeline->get_parent(), scene2);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 1);
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 2);

    yli::ontology::Pipeline::bind_to_new_scene_parent(*pipeline, *scene1);
    ASSERT_FALSE(scene1->has_child("foo"));
    ASSERT_FALSE(scene2->has_child("foo"));
    ASSERT_TRUE(scene1->has_child("bar"));
    ASSERT_FALSE(scene2->has_child("bar"));
    ASSERT_EQ(pipeline->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 2);
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 1);
}

TEST(pipeline_must_not_bind_to_a_new_parent_when_local_name_is_already_in_use, headless_universe_pipelines_with_only_local_name)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct1;
    yli::ontology::Scene* const scene1 = application.get_generic_entity_factory().create_scene(
            scene_struct1);

    yli::ontology::PipelineStruct pipeline_struct1(scene1);
    yli::ontology::Pipeline* const pipeline1 = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct1);

    yli::ontology::SceneStruct scene_struct2;
    yli::ontology::Scene* const scene2 = application.get_generic_entity_factory().create_scene(
            scene_struct2);

    yli::ontology::PipelineStruct pipeline_struct2(scene2);
    yli::ontology::Pipeline* const pipeline2 = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct2);

    pipeline1->set_local_name("foo");
    pipeline2->set_local_name("foo");
    yli::ontology::Pipeline::bind_to_new_scene_parent(*pipeline1, *scene2);
    ASSERT_EQ(pipeline1->get_scene(), scene1);
    ASSERT_EQ(pipeline1->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 2);
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 2);
    ASSERT_TRUE(scene1->has_child("foo"));
    ASSERT_TRUE(scene2->has_child("foo"));
}

TEST(pipeline_must_not_bind_to_a_new_parent_when_local_name_is_already_in_use, headless_universe_pipelines_with_different_global_names_and_same_local_name)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct1;
    yli::ontology::Scene* const scene1 = application.get_generic_entity_factory().create_scene(
            scene_struct1);

    yli::ontology::PipelineStruct pipeline_struct1(scene1);
    yli::ontology::Pipeline* const pipeline1 = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct1);

    yli::ontology::SceneStruct scene_struct2;
    yli::ontology::Scene* const scene2 = application.get_generic_entity_factory().create_scene(
            scene_struct2);

    yli::ontology::PipelineStruct pipeline_struct2(scene2);
    yli::ontology::Pipeline* const pipeline2 = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct2);

    pipeline1->set_global_name("foo");
    pipeline2->set_global_name("bar");
    pipeline1->set_local_name("baz");
    pipeline2->set_local_name("baz");
    yli::ontology::Pipeline::bind_to_new_scene_parent(*pipeline1, *scene2);
    ASSERT_EQ(pipeline1->get_scene(), scene1);
    ASSERT_EQ(pipeline1->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 2);
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 2);
    ASSERT_FALSE(scene1->has_child("foo"));
    ASSERT_FALSE(scene2->has_child("foo"));
    ASSERT_FALSE(scene1->has_child("bar"));
    ASSERT_FALSE(scene2->has_child("bar"));
    ASSERT_TRUE(scene1->has_child("baz"));
    ASSERT_TRUE(scene2->has_child("baz"));
}

TEST(pipeline_must_not_unbind_any_of_its_apprentice_modules_when_binding_to_an_ecosystem, headless_universe_material_apprentice)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct(scene);
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::MaterialStruct material_struct(scene, pipeline);
    application.get_generic_entity_factory().create_material(
            material_struct);

    ASSERT_EQ(pipeline->get_number_of_apprentices(), 1);

    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    yli::ontology::Pipeline::bind_to_new_ecosystem_parent(*pipeline, *ecosystem);
    ASSERT_EQ(pipeline->get_number_of_apprentices(), 1);
}

TEST(pipeline_must_not_unbind_any_of_its_apprentice_modules_when_binding_to_an_ecosystem, headless_universe_symbiosis_apprentice)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct(scene);
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::SymbiosisStruct symbiosis_struct(scene, pipeline);
    application.get_generic_entity_factory().create_symbiosis(
            symbiosis_struct);

    ASSERT_EQ(pipeline->get_number_of_apprentices(), 1);

    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    yli::ontology::Pipeline::bind_to_new_ecosystem_parent(*pipeline, *ecosystem);
    ASSERT_EQ(pipeline->get_number_of_apprentices(), 1);
}

TEST(pipeline_must_not_unbind_any_of_its_apprentice_modules_when_binding_to_the_current_scene, headless_universe_material_apprentice)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct(scene);
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::MaterialStruct material_struct(scene, pipeline);
    application.get_generic_entity_factory().create_material(
            material_struct);

    ASSERT_EQ(pipeline->get_number_of_apprentices(), 1);

    yli::ontology::Pipeline::bind_to_new_scene_parent(*pipeline, *scene);
    ASSERT_EQ(pipeline->get_number_of_apprentices(), 1);
}

TEST(pipeline_must_not_unbind_any_of_its_apprentice_modules_when_binding_to_the_current_scene, headless_universe_symbiosis_apprentice)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct(scene);
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::SymbiosisStruct symbiosis_struct(scene, pipeline);
    application.get_generic_entity_factory().create_symbiosis(
            symbiosis_struct);

    ASSERT_EQ(pipeline->get_number_of_apprentices(), 1);

    yli::ontology::Pipeline::bind_to_new_scene_parent(*pipeline, *scene);
    ASSERT_EQ(pipeline->get_number_of_apprentices(), 1);
}

TEST(pipeline_must_not_unbind_any_of_its_apprentice_modules_when_binding_to_the_current_scene, headless_universe_material_and_symbiosis_apprentices)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct(scene);
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::MaterialStruct material_struct(scene, pipeline);
    application.get_generic_entity_factory().create_material(
            material_struct);

    yli::ontology::SymbiosisStruct symbiosis_struct(scene, pipeline);
    application.get_generic_entity_factory().create_symbiosis(
            symbiosis_struct);

    ASSERT_EQ(pipeline->get_number_of_apprentices(), 2);

    yli::ontology::Pipeline::bind_to_new_scene_parent(*pipeline, *scene);
    ASSERT_EQ(pipeline->get_number_of_apprentices(), 2);
}

TEST(pipeline_must_unbind_all_of_its_apprentice_modules_when_binding_to_a_different_scene, headless_universe_material_apprentice)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene1 = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct(scene1);
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::MaterialStruct material_struct(scene1, pipeline);
    application.get_generic_entity_factory().create_material(
            material_struct);

    ASSERT_EQ(pipeline->get_number_of_apprentices(), 1);

    yli::ontology::Scene* const scene2 = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::Pipeline::bind_to_new_scene_parent(*pipeline, *scene2);
    ASSERT_EQ(pipeline->get_number_of_apprentices(), 0);
}

TEST(pipeline_must_unbind_all_of_its_apprentice_modules_when_binding_to_a_different_scene, headless_universe_symbiosis_apprentice)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene1 = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct(scene1);
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::SymbiosisStruct symbiosis_struct(scene1, pipeline);
    application.get_generic_entity_factory().create_symbiosis(
            symbiosis_struct);

    ASSERT_EQ(pipeline->get_number_of_apprentices(), 1);

    yli::ontology::Scene* const scene2 = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::Pipeline::bind_to_new_scene_parent(*pipeline, *scene2);
    ASSERT_EQ(pipeline->get_number_of_apprentices(), 0);
}

TEST(pipeline_must_unbind_all_of_its_apprentice_modules_when_binding_to_a_different_scene, headless_universe_material_and_symbiosis_apprentices)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene1 = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct(scene1);
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::MaterialStruct material_struct(scene1, pipeline);
    application.get_generic_entity_factory().create_material(
            material_struct);

    yli::ontology::SymbiosisStruct symbiosis_struct(scene1, pipeline);
    application.get_generic_entity_factory().create_symbiosis(
            symbiosis_struct);

    ASSERT_EQ(pipeline->get_number_of_apprentices(), 2);

    yli::ontology::Scene* const scene2 = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::Pipeline::bind_to_new_scene_parent(*pipeline, *scene2);
    ASSERT_EQ(pipeline->get_number_of_apprentices(), 0);
}
