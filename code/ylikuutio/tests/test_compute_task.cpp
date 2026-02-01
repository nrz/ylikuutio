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
#include "code/ylikuutio/ontology/ecosystem.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/pipeline.hpp"
#include "code/ylikuutio/ontology/compute_task.hpp"
#include "code/ylikuutio/ontology/request.hpp"
#include "code/ylikuutio/ontology/ecosystem_struct.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/pipeline_struct.hpp"
#include "code/ylikuutio/ontology/compute_task_struct.hpp"

// Include standard headers
#include <cstddef> // std::size_t, uintptr_t
#include <limits>  // std::numeric_limits

TEST(compute_task_must_be_initialized_and_must_bind_to_pipeline_appropriately, headless_pipeline_is_a_child_of_an_ecosystem_pipeline_parent_provided_as_valid_pointer)
{
    mock::MockApplication application;
    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    yli::ontology::PipelineStruct pipeline_struct { yli::ontology::Request(ecosystem) };
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::ComputeTaskStruct compute_task_struct { yli::ontology::Request(pipeline) };
    yli::ontology::ComputeTask* const compute_task = application.get_generic_entity_factory().create_compute_task(
            compute_task_struct);
    ASSERT_NE(compute_task, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(compute_task) % alignof(yli::ontology::ComputeTask), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);  // `ecosystem`.

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 1); // `pipeline`.

    // `Entity` member functions of `Pipeline`.
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 1);  // `compute_task`.

    // `Pipeline` member functions.
    ASSERT_EQ(pipeline->get_number_of_apprentices(), 0);

    // `Entity` member functions of `ComputeTask`.
    ASSERT_EQ(compute_task->get_childID(), 0);
    ASSERT_EQ(compute_task->get_type(), "yli::ontology::ComputeTask*");
    ASSERT_TRUE(compute_task->get_can_be_erased());
    ASSERT_EQ(compute_task->get_scene(), nullptr);
    ASSERT_EQ(compute_task->get_parent(), pipeline);
    ASSERT_EQ(compute_task->get_number_of_non_variable_children(), 0);
}

TEST(compute_task_must_be_initialized_and_must_bind_to_pipeline_appropriately, headless_pipeline_is_a_child_of_a_scene_pipeline_parent_provided_as_valid_pointer)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct { yli::ontology::Request(scene) };
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::ComputeTaskStruct compute_task_struct { yli::ontology::Request(pipeline) };
    yli::ontology::ComputeTask* const compute_task = application.get_generic_entity_factory().create_compute_task(
            compute_task_struct);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1); // `ecosystem`.

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 2);    // Default `Camera`, `pipeline`.

    // `Entity` member functions of `Pipeline`.
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 1); // `compute_task`.

    // `Pipeline` member functions.
    ASSERT_EQ(pipeline->get_number_of_apprentices(), 0);

    // `Entity` member functions of `ComputeTask`.
    ASSERT_EQ(compute_task->get_childID(), 0);
    ASSERT_EQ(compute_task->get_type(), "yli::ontology::ComputeTask*");
    ASSERT_TRUE(compute_task->get_can_be_erased());
    ASSERT_EQ(compute_task->get_scene(), scene);
    ASSERT_EQ(compute_task->get_parent(), pipeline);
    ASSERT_EQ(compute_task->get_number_of_non_variable_children(), 0);
}

TEST(compute_task_must_be_initialized_and_must_bind_to_pipeline_appropriately, headless_pipeline_is_a_child_of_an_ecosystem_pipeline_parent_provided_as_nullptr)
{
    mock::MockApplication application;
    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    yli::ontology::PipelineStruct pipeline_struct { yli::ontology::Request(ecosystem) };
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::ComputeTaskStruct compute_task_struct { yli::ontology::Request<yli::ontology::Pipeline>(nullptr) };
    yli::ontology::ComputeTask* const compute_task = application.get_generic_entity_factory().create_compute_task(
            compute_task_struct);
    ASSERT_NE(compute_task, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(compute_task) % alignof(yli::ontology::ComputeTask), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);  // `ecosystem`.

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 1); // `pipeline`.

    // `Entity` member functions of `Pipeline`.
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 0);

    // `Pipeline` member functions.
    ASSERT_EQ(pipeline->get_number_of_apprentices(), 0);

    // `Entity` member functions of `ComputeTask`.
    ASSERT_EQ(compute_task->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(compute_task->get_type(), "yli::ontology::ComputeTask*");
    ASSERT_TRUE(compute_task->get_can_be_erased());
    ASSERT_EQ(compute_task->get_parent(), nullptr);
    ASSERT_EQ(compute_task->get_number_of_non_variable_children(), 0);
}

TEST(compute_task_must_be_initialized_and_must_bind_to_pipeline_appropriately, headless_pipeline_is_a_child_of_an_ecosystem_pipeline_parent_provided_as_valid_global_name)
{
    mock::MockApplication application;
    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    yli::ontology::PipelineStruct pipeline_struct { yli::ontology::Request(ecosystem) };
    pipeline_struct.global_name = "foo";
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::ComputeTaskStruct compute_task_struct { yli::ontology::Request<yli::ontology::Pipeline>("foo") };
    yli::ontology::ComputeTask* const compute_task = application.get_generic_entity_factory().create_compute_task(
            compute_task_struct);
    ASSERT_NE(compute_task, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(compute_task) % alignof(yli::ontology::ComputeTask), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);  // `ecosystem`.

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 1); // `pipeline`.

    // `Entity` member functions of `Pipeline`.
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 1);  // `compute_task`.

    // `Pipeline` member functions.
    ASSERT_EQ(pipeline->get_number_of_apprentices(), 0);

    // `Entity` member functions of `ComputeTask`.
    ASSERT_EQ(compute_task->get_childID(), 0);
    ASSERT_EQ(compute_task->get_type(), "yli::ontology::ComputeTask*");
    ASSERT_TRUE(compute_task->get_can_be_erased());
    ASSERT_EQ(compute_task->get_scene(), nullptr);
    ASSERT_EQ(compute_task->get_parent(), pipeline);
    ASSERT_EQ(compute_task->get_number_of_non_variable_children(), 0);
}

TEST(compute_task_must_be_initialized_and_must_bind_to_pipeline_appropriately, headless_pipeline_is_a_child_of_an_ecosystem_pipeline_parent_provided_as_invalid_global_name)
{
    mock::MockApplication application;
    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    yli::ontology::PipelineStruct pipeline_struct { yli::ontology::Request(ecosystem) };
    pipeline_struct.global_name = "foo";
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::ComputeTaskStruct compute_task_struct { yli::ontology::Request<yli::ontology::Pipeline>("bar") };
    yli::ontology::ComputeTask* const compute_task = application.get_generic_entity_factory().create_compute_task(
            compute_task_struct);
    ASSERT_NE(compute_task, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(compute_task) % alignof(yli::ontology::ComputeTask), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);  // `ecosystem`.

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 1); // `pipeline`.

    // `Entity` member functions of `Pipeline`.
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 0);

    // `Pipeline` member functions.
    ASSERT_EQ(pipeline->get_number_of_apprentices(), 0);

    // `Entity` member functions of `ComputeTask`.
    ASSERT_EQ(compute_task->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(compute_task->get_type(), "yli::ontology::ComputeTask*");
    ASSERT_TRUE(compute_task->get_can_be_erased());
    ASSERT_EQ(compute_task->get_parent(), nullptr);
    ASSERT_EQ(compute_task->get_number_of_non_variable_children(), 0);
}
