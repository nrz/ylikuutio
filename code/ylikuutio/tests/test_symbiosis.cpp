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
#include "code/ylikuutio/ontology/symbiosis.hpp"
#include "code/ylikuutio/ontology/ecosystem_struct.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/pipeline_struct.hpp"
#include "code/ylikuutio/ontology/model_struct.hpp"

// Include standard headers
#include <cstddef> // uintptr_t

TEST(symbiosis_must_be_initialized_and_must_bind_to_ecosystem_appropriately, headless_pipeline_is_child_of_ecosystem)
{
    mock::MockApplication application;
    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    yli::ontology::PipelineStruct pipeline_struct;
    pipeline_struct.parent = ecosystem;
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::ModelStruct model_struct;
    model_struct.parent = ecosystem;
    model_struct.pipeline = pipeline;
    yli::ontology::Symbiosis* const symbiosis = application.get_generic_entity_factory().create_symbiosis(
            model_struct);
    ASSERT_NE(symbiosis, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(symbiosis) % alignof(yli::ontology::Symbiosis), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem->get_scene(), nullptr);
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 2); // `pipeline`, `symbiosis`.

    // `Entity` member functions of `Pipeline`.
    ASSERT_EQ(pipeline->get_scene(), nullptr);
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 0);

    ASSERT_EQ(symbiosis->apprentice_of_pipeline.get_master(), pipeline);
    ASSERT_EQ(symbiosis->apprentice_of_pipeline.get_apprenticeID(), 0);

    // `Entity` member functions.
    ASSERT_EQ(symbiosis->get_childID(), 0);
    ASSERT_EQ(symbiosis->get_type(), "yli::ontology::Symbiosis*");
    ASSERT_TRUE(symbiosis->get_can_be_erased());
    ASSERT_EQ(symbiosis->get_scene(), nullptr);
    ASSERT_EQ(symbiosis->get_parent(), ecosystem);
    ASSERT_EQ(symbiosis->get_number_of_non_variable_children(), 0);
}

TEST(symbiosis_must_be_initialized_and_must_bind_to_ecosystem_appropriately, headless_pipeline_is_child_of_scene)
{
    mock::MockApplication application;
    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct;
    pipeline_struct.parent = scene;
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::ModelStruct model_struct;
    model_struct.parent = ecosystem;
    model_struct.pipeline = pipeline;
    yli::ontology::Symbiosis* const symbiosis = application.get_generic_entity_factory().create_symbiosis(
            model_struct);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 2); // `ecosystem`, `scene`.

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem->get_scene(), nullptr);
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 1); // `symbiosis`.

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_scene(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 2); // Default `Camera`, `pipeline`.

    // `Entity` member functions of `Pipeline`.
    ASSERT_EQ(pipeline->get_scene(), scene);
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 0);

    ASSERT_EQ(symbiosis->apprentice_of_pipeline.get_master(), pipeline);
    ASSERT_EQ(symbiosis->apprentice_of_pipeline.get_apprenticeID(), 0);

    // `Entity` member functions.
    ASSERT_EQ(symbiosis->get_childID(), 0);
    ASSERT_EQ(symbiosis->get_type(), "yli::ontology::Symbiosis*");
    ASSERT_TRUE(symbiosis->get_can_be_erased());
    ASSERT_EQ(symbiosis->get_scene(), nullptr);
    ASSERT_EQ(symbiosis->get_parent(), ecosystem);
    ASSERT_EQ(symbiosis->get_number_of_non_variable_children(), 0);
}

TEST(symbiosis_must_be_initialized_appropriately, headless)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct;
    pipeline_struct.parent = scene;
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::ModelStruct model_struct;
    model_struct.parent = scene;
    model_struct.pipeline = pipeline;
    yli::ontology::Symbiosis* const symbiosis = application.get_generic_entity_factory().create_symbiosis(
            model_struct);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_scene(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 3); // Default `Camera`, `pipeline`, `symbiosis`.

    // `Entity` member functions of `Pipeline`.
    ASSERT_EQ(pipeline->get_scene(), scene);
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 0);

    ASSERT_EQ(symbiosis->apprentice_of_pipeline.get_master(), pipeline);
    ASSERT_EQ(symbiosis->apprentice_of_pipeline.get_apprenticeID(), 0);

    // `Entity` member functions.
    ASSERT_EQ(symbiosis->get_childID(), 0);
    ASSERT_EQ(symbiosis->get_type(), "yli::ontology::Symbiosis*");
    ASSERT_TRUE(symbiosis->get_can_be_erased());
    ASSERT_EQ(symbiosis->get_scene(), scene);
    ASSERT_EQ(symbiosis->get_parent(), scene);
    ASSERT_EQ(symbiosis->get_number_of_non_variable_children(), 0);
}

TEST(symbiosis_must_be_initialized_appropriately, headless_turbo_polizei)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct;
    pipeline_struct.parent = scene;
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::ModelStruct model_struct;
    model_struct.parent = scene;
    model_struct.pipeline = pipeline;
    model_struct.model_filename = "turbo_polizei_png_textures.fbx";
    model_struct.model_file_format = "FBX";
    yli::ontology::Symbiosis* const symbiosis = application.get_generic_entity_factory().create_symbiosis(
            model_struct);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_scene(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 3); // Default `Camera`, `pipeline`, `symbiosis`.

    // `Entity` member functions of `Pipeline`.
    ASSERT_EQ(pipeline->get_scene(), scene);
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 0);

    ASSERT_EQ(symbiosis->apprentice_of_pipeline.get_master(), pipeline);
    ASSERT_EQ(symbiosis->apprentice_of_pipeline.get_apprenticeID(), 0);

    // `Entity` member functions.
    ASSERT_EQ(symbiosis->get_childID(), 0);
    ASSERT_EQ(symbiosis->get_type(), "yli::ontology::Symbiosis*");
    ASSERT_TRUE(symbiosis->get_can_be_erased());
    ASSERT_EQ(symbiosis->get_scene(), scene);
    ASSERT_EQ(symbiosis->get_parent(), scene);
    ASSERT_EQ(symbiosis->get_number_of_non_variable_children(), 2);    // 2 `SymbiontMaterial`s.
}

TEST(symbiosis_must_bind_to_ecosystem_appropriately, ecosystem)
{
    mock::MockApplication application;
    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem1 = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    yli::ontology::ModelStruct model_struct;
    model_struct.parent = ecosystem1;
    yli::ontology::Symbiosis* const symbiosis = application.get_generic_entity_factory().create_symbiosis(
            model_struct);
    ASSERT_EQ(symbiosis->get_scene(), nullptr);
    ASSERT_EQ(symbiosis->get_parent(), ecosystem1);
    ASSERT_EQ(ecosystem1->get_number_of_non_variable_children(), 1);

    yli::ontology::Ecosystem* const ecosystem2 = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    ASSERT_EQ(symbiosis->get_scene(), nullptr);
    ASSERT_EQ(symbiosis->get_parent(), ecosystem1);
    ASSERT_EQ(ecosystem2->get_number_of_non_variable_children(), 0);

    yli::ontology::Symbiosis::bind_to_new_ecosystem_parent(*symbiosis, *ecosystem2);
    ASSERT_EQ(symbiosis->get_scene(), nullptr);
    ASSERT_EQ(symbiosis->get_parent(), ecosystem2);
    ASSERT_EQ(ecosystem1->get_number_of_non_variable_children(), 0);
    ASSERT_EQ(ecosystem2->get_number_of_non_variable_children(), 1);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 2); // `ecosystem1`, `ecosystem2`.

    yli::ontology::Symbiosis::bind_to_new_ecosystem_parent(*symbiosis, *ecosystem1);
    ASSERT_EQ(symbiosis->get_scene(), nullptr);
    ASSERT_EQ(symbiosis->get_parent(), ecosystem1);
    ASSERT_EQ(ecosystem1->get_number_of_non_variable_children(), 1);
    ASSERT_EQ(ecosystem2->get_number_of_non_variable_children(), 0);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 2); // `ecosystem1`, `ecosystem2`.
}

TEST(symbiosis_must_bind_to_scene_appropriately, scenes)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene1 = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct;
    pipeline_struct.parent = scene1;
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::ModelStruct model_struct;
    model_struct.parent = scene1;
    model_struct.pipeline = pipeline;
    yli::ontology::Symbiosis* const symbiosis = application.get_generic_entity_factory().create_symbiosis(
            model_struct);

    ASSERT_EQ(symbiosis->get_scene(), scene1);
    ASSERT_EQ(symbiosis->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 3); // Default `Camera`, `pipeline`, `symbiosis`.

    yli::ontology::Scene* const scene2 = application.get_generic_entity_factory().create_scene(
            scene_struct);
    ASSERT_EQ(symbiosis->get_scene(), scene1);
    ASSERT_EQ(symbiosis->get_parent(), scene1);
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 1); // Default `Camera`.

    yli::ontology::Symbiosis::bind_to_new_scene_parent(*symbiosis, *scene2);
    ASSERT_EQ(symbiosis->get_scene(), scene2);
    ASSERT_EQ(symbiosis->get_parent(), scene2);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 2); // Default `Camera`, `pipeline`.
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 2); // Default `Camera`, `symbiosis`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 2);

    yli::ontology::Symbiosis::bind_to_new_scene_parent(*symbiosis, *scene1);
    ASSERT_EQ(symbiosis->get_scene(), scene1);
    ASSERT_EQ(symbiosis->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 3); // Default `Camera`, `pipeline`, `symbiosis`.
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 1); // Default `Camera`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 2);
}

TEST(symbiosis_must_bind_to_ecosystem_appropriately_after_binding_to_scene, ecosystem_scene)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::ModelStruct model_struct;
    model_struct.parent = scene;
    yli::ontology::Symbiosis* const symbiosis = application.get_generic_entity_factory().create_symbiosis(
            model_struct);

    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);
    ASSERT_EQ(symbiosis->get_scene(), scene);
    ASSERT_EQ(symbiosis->get_parent(), scene);
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 0);

    yli::ontology::Symbiosis::bind_to_new_ecosystem_parent(*symbiosis, *ecosystem);
    ASSERT_EQ(symbiosis->get_scene(), nullptr);
    ASSERT_EQ(symbiosis->get_parent(), ecosystem);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 1);     // Default `Camera`.
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 1); // `symbiosis`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 2);  // `ecosystem`, `scene`.

    yli::ontology::Symbiosis::bind_to_new_scene_parent(*symbiosis, *scene);
    ASSERT_EQ(symbiosis->get_scene(), scene);
    ASSERT_EQ(symbiosis->get_parent(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 2);     // Default `Camera`, `symbiosis`.
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 0);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 2);  // `ecosystem`, `scene`.
}

TEST(symbiosis_must_bind_to_scene_appropriately_after_binding_to_ecosystem, scene_ecosystem)
{
    mock::MockApplication application;
    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    yli::ontology::ModelStruct model_struct;
    model_struct.parent = ecosystem;
    yli::ontology::Symbiosis* const symbiosis = application.get_generic_entity_factory().create_symbiosis(
            model_struct);

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);
    ASSERT_EQ(symbiosis->get_scene(), nullptr);
    ASSERT_EQ(symbiosis->get_parent(), ecosystem);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 1); // Default `Camera`.

    yli::ontology::Symbiosis::bind_to_new_scene_parent(*symbiosis, *scene);
    ASSERT_EQ(symbiosis->get_scene(), scene);
    ASSERT_EQ(symbiosis->get_parent(), scene);
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 0);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 2);     // Default `Camera`, `symbiosis`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 2);  // `Ecosystem`, `Scene`.

    yli::ontology::Symbiosis::bind_to_new_ecosystem_parent(*symbiosis, *ecosystem);
    ASSERT_EQ(symbiosis->get_scene(), nullptr);
    ASSERT_EQ(symbiosis->get_parent(), ecosystem);
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 1); // `symbiosis`.
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 1);     // Default `Camera`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 2);  // `Ecosystem`, `Scene`.
}

TEST(symbiosis_must_bind_to_pipeline_appropriately, master_and_apprentice)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct;
    pipeline_struct.parent = scene;
    yli::ontology::Pipeline* const pipeline1 = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::ModelStruct model_struct;
    model_struct.parent = scene;
    model_struct.pipeline = pipeline1;
    model_struct.model_filename = "turbo_polizei_png_textures.fbx";
    model_struct.model_file_format = "FBX";
    yli::ontology::Symbiosis* const symbiosis = application.get_generic_entity_factory().create_symbiosis(
            model_struct);
    ASSERT_EQ(symbiosis->get_pipeline(), pipeline1);

    yli::ontology::Pipeline* const pipeline2 = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);
    ASSERT_EQ(symbiosis->get_pipeline(), pipeline1);

    yli::ontology::Symbiosis::bind_to_new_pipeline(*symbiosis, *pipeline2);
    ASSERT_EQ(symbiosis->get_pipeline(), pipeline2);

    ASSERT_EQ(symbiosis->apprentice_of_pipeline.get_master(), pipeline2);
    ASSERT_EQ(symbiosis->apprentice_of_pipeline.get_apprenticeID(), 0);

    yli::ontology::Symbiosis::bind_to_new_pipeline(*symbiosis, *pipeline1);
    ASSERT_EQ(symbiosis->get_pipeline(), pipeline1);

    ASSERT_EQ(symbiosis->apprentice_of_pipeline.get_master(), pipeline1);
    ASSERT_EQ(symbiosis->apprentice_of_pipeline.get_apprenticeID(), 0);
}
