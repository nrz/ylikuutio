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
#include "code/ylikuutio/ontology/ecosystem.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/pipeline.hpp"
#include "code/ylikuutio/ontology/compute_task.hpp"
#include "code/ylikuutio/ontology/universe_struct.hpp"
#include "code/ylikuutio/ontology/ecosystem_struct.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/pipeline_struct.hpp"
#include "code/ylikuutio/ontology/compute_task_struct.hpp"
#include "code/ylikuutio/render/graphics_api_backend.hpp"

TEST(compute_task_must_be_initialized_and_must_bind_to_pipeline_appropriately, headless_pipeline_is_a_child_of_an_ecosystem)
{
    mock::MockApplication application;

    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(application, universe_struct);

    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = new yli::ontology::Ecosystem(
            application,
            *universe,
            ecosystem_struct,
            &universe->parent_of_ecosystems);

    yli::ontology::PipelineStruct pipeline_struct;
    pipeline_struct.parent = ecosystem;
    yli::ontology::Pipeline* const pipeline = new yli::ontology::Pipeline(application, *universe, pipeline_struct, &ecosystem->parent_of_pipelines);

    yli::ontology::ComputeTaskStruct compute_task_struct;
    compute_task_struct.parent = pipeline;
    yli::ontology::ComputeTask* const compute_task = new yli::ontology::ComputeTask(application, *universe, compute_task_struct);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 1);  // `ecosystem`.

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
    ASSERT_EQ(&(compute_task->get_universe()), universe);
    ASSERT_EQ(compute_task->get_scene(), nullptr);
    ASSERT_EQ(compute_task->get_parent(), pipeline);
    ASSERT_EQ(compute_task->get_number_of_non_variable_children(), 0);
}

TEST(compute_task_must_be_initialized_and_must_bind_to_pipeline_appropriately, headless_pipeline_is_a_child_of_a_scene)
{
    mock::MockApplication application;

    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(application, universe_struct);

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(
            application,
            *universe,
            scene_struct,
            &universe->parent_of_scenes);

    yli::ontology::PipelineStruct pipeline_struct;
    pipeline_struct.parent = scene;
    yli::ontology::Pipeline* const pipeline = new yli::ontology::Pipeline(application, *universe, pipeline_struct, &scene->parent_of_pipelines);

    yli::ontology::ComputeTaskStruct compute_task_struct;
    compute_task_struct.parent = pipeline;
    yli::ontology::ComputeTask* const compute_task = new yli::ontology::ComputeTask(application, *universe, compute_task_struct);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 1); // `ecosystem`.

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
    ASSERT_EQ(&(compute_task->get_universe()), universe);
    ASSERT_EQ(compute_task->get_scene(), scene);
    ASSERT_EQ(compute_task->get_parent(), pipeline);
    ASSERT_EQ(compute_task->get_number_of_non_variable_children(), 0);
}
