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
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/ecosystem.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/pipeline.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/universe_struct.hpp"
#include "code/ylikuutio/ontology/ecosystem_struct.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/pipeline_struct.hpp"
#include "code/ylikuutio/ontology/material_struct.hpp"
#include "code/ylikuutio/ontology/model_struct.hpp"
#include "code/ylikuutio/render/graphics_api_backend.hpp"

TEST(material_must_be_initialized_and_must_bind_to_ecosystem_appropriately, headless_pipeline_is_child_of_ecosystem)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = new yli::ontology::Ecosystem(
            *universe,
            ecosystem_struct,
            &universe->parent_of_ecosystems);

    yli::ontology::PipelineStruct pipeline_struct;
    pipeline_struct.parent = ecosystem;
    yli::ontology::Pipeline* const pipeline = new yli::ontology::Pipeline(*universe, pipeline_struct, &ecosystem->parent_of_pipelines);

    yli::ontology::MaterialStruct material_struct;
    material_struct.parent = ecosystem;
    material_struct.pipeline = pipeline;
    yli::ontology::Material* const material = new yli::ontology::Material(
            *universe,
            material_struct,
            &ecosystem->parent_of_materials, &pipeline->master_of_materials);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_scene(), nullptr);
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 1); // `ecosystem`.

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem->get_scene(), nullptr);
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 2); // `pipeline`, `material`.

    // `Entity` member functions of `Pipeline`.
    ASSERT_EQ(pipeline->get_scene(), nullptr);
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 0);

    // `Pipeline` member functions.
    ASSERT_EQ(pipeline->get_number_of_apprentices(), 1); // `material`.

    // `Material` member functions.
    ASSERT_EQ(material->get_number_of_apprentices(), 0);

    ASSERT_EQ(material->apprentice_of_pipeline.get_master(), pipeline);
    ASSERT_EQ(material->apprentice_of_pipeline.get_apprenticeID(), 0);

    // `Entity` member functions.
    ASSERT_EQ(material->get_childID(), 0);
    ASSERT_EQ(material->get_type(), "yli::ontology::Material*");
    ASSERT_TRUE(material->get_can_be_erased());
    ASSERT_EQ(&(material->get_universe()), universe);
    ASSERT_EQ(material->get_scene(), nullptr);
    ASSERT_EQ(material->get_parent(), ecosystem);
    ASSERT_EQ(material->get_number_of_non_variable_children(), 0);
}

TEST(material_must_be_initialized_and_must_bind_to_ecosystem_appropriately, headless_pipeline_is_child_of_scene)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = new yli::ontology::Ecosystem(
            *universe,
            ecosystem_struct,
            &universe->parent_of_ecosystems);

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);

    yli::ontology::PipelineStruct pipeline_struct;
    pipeline_struct.parent = scene;
    yli::ontology::Pipeline* const pipeline = new yli::ontology::Pipeline(*universe, pipeline_struct, &scene->parent_of_pipelines);

    yli::ontology::MaterialStruct material_struct;
    material_struct.parent = ecosystem;
    material_struct.pipeline = pipeline;
    yli::ontology::Material* const material = new yli::ontology::Material(
            *universe,
            material_struct,
            &ecosystem->parent_of_materials, &pipeline->master_of_materials);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_scene(), nullptr);
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 2); // `ecosystem`, `scene`.

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem->get_scene(), nullptr);
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 1); // `material`.

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_scene(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 2); // Default `Camera`, `pipeline`.

    // `Entity` member functions of `Pipeline`.
    ASSERT_EQ(pipeline->get_scene(), scene);
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 0);

    // `Pipeline` member functions.
    ASSERT_EQ(pipeline->get_number_of_apprentices(), 1); // `material`.

    // `Material` member functions.
    ASSERT_EQ(material->get_number_of_apprentices(), 0);

    ASSERT_EQ(material->apprentice_of_pipeline.get_master(), pipeline);
    ASSERT_EQ(material->apprentice_of_pipeline.get_apprenticeID(), 0);

    // `Entity` member functions.
    ASSERT_EQ(material->get_childID(), 0);
    ASSERT_EQ(material->get_type(), "yli::ontology::Material*");
    ASSERT_TRUE(material->get_can_be_erased());
    ASSERT_EQ(&(material->get_universe()), universe);
    ASSERT_EQ(material->get_scene(), nullptr);
    ASSERT_EQ(material->get_parent(), ecosystem);
    ASSERT_EQ(material->get_number_of_non_variable_children(), 0);
}

TEST(material_must_be_initialized_appropriately, headless)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);

    yli::ontology::PipelineStruct pipeline_struct;
    pipeline_struct.parent = scene;
    yli::ontology::Pipeline* const pipeline = new yli::ontology::Pipeline(*universe, pipeline_struct, &scene->parent_of_pipelines);

    yli::ontology::MaterialStruct material_struct;
    material_struct.parent = scene;
    material_struct.pipeline = pipeline;
    yli::ontology::Material* const material = new yli::ontology::Material(
            *universe,
            material_struct,
            &scene->parent_of_materials, &pipeline->master_of_materials);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_scene(), nullptr);
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_scene(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 3); // Default `Camera`, `pipeline`, `material`.

    // `Entity` member functions of `Pipeline`.
    ASSERT_EQ(pipeline->get_scene(), scene);
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 0);

    // `Pipeline` member functions.
    ASSERT_EQ(pipeline->get_number_of_apprentices(), 1); // `material`.

    // `Material` member functions.
    ASSERT_EQ(material->get_number_of_apprentices(), 0);

    ASSERT_EQ(material->apprentice_of_pipeline.get_master(), pipeline);
    ASSERT_EQ(material->apprentice_of_pipeline.get_apprenticeID(), 0);

    // `Entity` member functions.
    ASSERT_EQ(material->get_childID(), 0);
    ASSERT_EQ(material->get_type(), "yli::ontology::Material*");
    ASSERT_TRUE(material->get_can_be_erased());
    ASSERT_EQ(&(material->get_universe()), universe);
    ASSERT_EQ(material->get_scene(), scene);
    ASSERT_EQ(material->get_parent(), scene);
    ASSERT_EQ(material->get_number_of_non_variable_children(), 0);
}

TEST(material_must_bind_to_ecosystem_appropriately, ecosystem)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem1 = new yli::ontology::Ecosystem(
            *universe,
            ecosystem_struct,
            &universe->parent_of_ecosystems);

    yli::ontology::MaterialStruct material_struct;
    material_struct.parent = ecosystem1;
    yli::ontology::Material* const material = new yli::ontology::Material(
            *universe,
            material_struct,
            &ecosystem1->parent_of_materials, nullptr);
    ASSERT_EQ(material->get_scene(), nullptr);
    ASSERT_EQ(material->get_parent(), ecosystem1);
    ASSERT_EQ(ecosystem1->get_number_of_non_variable_children(), 1);

    yli::ontology::Ecosystem* const ecosystem2 = new yli::ontology::Ecosystem(
            *universe,
            ecosystem_struct,
            &universe->parent_of_ecosystems);

    ASSERT_EQ(material->get_scene(), nullptr);
    ASSERT_EQ(material->get_parent(), ecosystem1);
    ASSERT_EQ(ecosystem2->get_number_of_non_variable_children(), 0);

    yli::ontology::Material::bind_to_new_ecosystem_parent(*material, *ecosystem2);
    ASSERT_EQ(material->get_scene(), nullptr);
    ASSERT_EQ(material->get_parent(), ecosystem2);
    ASSERT_EQ(ecosystem1->get_number_of_non_variable_children(), 0);
    ASSERT_EQ(ecosystem2->get_number_of_non_variable_children(), 1);
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 2); // `ecosystem1`, `ecosystem2`.

    yli::ontology::Material::bind_to_new_ecosystem_parent(*material, *ecosystem1);
    ASSERT_EQ(material->get_scene(), nullptr);
    ASSERT_EQ(material->get_parent(), ecosystem1);
    ASSERT_EQ(ecosystem1->get_number_of_non_variable_children(), 1);
    ASSERT_EQ(ecosystem2->get_number_of_non_variable_children(), 0);
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 2); // `ecosystem1`, `ecosystem2`.
}

TEST(material_must_bind_to_scene_appropriately, scenes_no_pipelines)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene1 = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);

    yli::ontology::MaterialStruct material_struct;
    material_struct.parent = scene1;
    yli::ontology::Material* const material = new yli::ontology::Material(
            *universe,
            material_struct,
            &scene1->parent_of_materials, nullptr);
    ASSERT_EQ(material->get_scene(), scene1);
    ASSERT_EQ(material->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 2); // Default `Camera`, `material`.

    yli::ontology::Scene* const scene2 = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);
    ASSERT_EQ(material->get_scene(), scene1);
    ASSERT_EQ(material->get_parent(), scene1);
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 1);

    yli::ontology::Material::bind_to_new_scene_parent(*material, *scene2);
    ASSERT_EQ(material->get_scene(), scene2);
    ASSERT_EQ(material->get_parent(), scene2);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 1); // Default `Camera`.
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 2); // Default `Camera`, `material`.
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 2);

    yli::ontology::Material::bind_to_new_scene_parent(*material, *scene1);
    ASSERT_EQ(material->get_scene(), scene1);
    ASSERT_EQ(material->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 2); // Default `Camera`, `material`.
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 1); // Default `Camera`.
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 2);
}

TEST(material_must_bind_to_ecosystem_appropriately_after_binding_to_scene, ecosystem_scene)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);

    yli::ontology::MaterialStruct material_struct;
    material_struct.parent = scene;
    yli::ontology::Material* const material = new yli::ontology::Material(
            *universe,
            material_struct,
            &scene->parent_of_materials, nullptr);

    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = new yli::ontology::Ecosystem(
            *universe,
            ecosystem_struct,
            &universe->parent_of_ecosystems);
    ASSERT_EQ(material->get_scene(), scene);
    ASSERT_EQ(material->get_parent(), scene);
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 0);

    yli::ontology::Material::bind_to_new_ecosystem_parent(*material, *ecosystem);
    ASSERT_EQ(material->get_scene(), nullptr);
    ASSERT_EQ(material->get_parent(), ecosystem);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 1);     // Default `Camera`.
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 1); // `material`.
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 2);  // `ecosystem`, `scene`.

    yli::ontology::Material::bind_to_new_scene_parent(*material, *scene);
    ASSERT_EQ(material->get_scene(), scene);
    ASSERT_EQ(material->get_parent(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 2);     // Default `Camera`, `material`.
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 0);
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 2);  // `ecosystem`, `scene`.
}

TEST(material_must_bind_to_scene_appropriately_after_binding_to_ecosystem, scene_ecosystem)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = new yli::ontology::Ecosystem(
            *universe,
            ecosystem_struct,
            &universe->parent_of_ecosystems);

    yli::ontology::MaterialStruct material_struct;
    material_struct.parent = ecosystem;
    yli::ontology::Material* const material = new yli::ontology::Material(
            *universe,
            material_struct,
            &ecosystem->parent_of_materials, nullptr);

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);
    ASSERT_EQ(material->get_scene(), nullptr);
    ASSERT_EQ(material->get_parent(), ecosystem);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 1); // Default `Camera`.

    yli::ontology::Material::bind_to_new_scene_parent(*material, *scene);
    ASSERT_EQ(material->get_scene(), scene);
    ASSERT_EQ(material->get_parent(), scene);
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 0);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 2);     // Default `Camera`, `material`.
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 2);  // `Ecosystem`, `Scene`.

    yli::ontology::Material::bind_to_new_ecosystem_parent(*material, *ecosystem);
    ASSERT_EQ(material->get_scene(), nullptr);
    ASSERT_EQ(material->get_parent(), ecosystem);
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 1); // `material`.
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 1);     // Default `Camera`.
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 2);  // `Ecosystem`, `Scene`.
}

TEST(material_must_bind_to_pipeline_appropriately, master_and_apprentice)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);

    yli::ontology::PipelineStruct pipeline_struct;
    pipeline_struct.parent = scene;
    yli::ontology::Pipeline* const pipeline1 = new yli::ontology::Pipeline(*universe, pipeline_struct, &scene->parent_of_pipelines);

    yli::ontology::MaterialStruct material_struct;
    material_struct.parent = scene;
    material_struct.pipeline = pipeline1;
    yli::ontology::Material* const material = new yli::ontology::Material(
            *universe,
            material_struct,
            &scene->parent_of_materials, &pipeline1->master_of_materials);

    ASSERT_EQ(pipeline1->get_number_of_apprentices(), 1);
    yli::ontology::Pipeline* const pipeline2 = new yli::ontology::Pipeline(*universe, pipeline_struct, &scene->parent_of_pipelines);
    ASSERT_EQ(pipeline1->get_number_of_apprentices(), 1);
    ASSERT_EQ(pipeline2->get_number_of_apprentices(), 0);
    ASSERT_EQ(material->apprentice_of_pipeline.get_master(), pipeline1);
    ASSERT_EQ(material->apprentice_of_pipeline.get_apprenticeID(), 0);

    yli::ontology::Material::bind_to_new_pipeline(*material, *pipeline2);
    ASSERT_EQ(pipeline1->get_number_of_apprentices(), 0);
    ASSERT_EQ(pipeline2->get_number_of_apprentices(), 1);
    ASSERT_EQ(material->apprentice_of_pipeline.get_master(), pipeline2);
    ASSERT_EQ(material->apprentice_of_pipeline.get_apprenticeID(), 0);

    yli::ontology::Material::bind_to_new_pipeline(*material, *pipeline1);
    ASSERT_EQ(pipeline1->get_number_of_apprentices(), 1);
    ASSERT_EQ(pipeline2->get_number_of_apprentices(), 0);
    ASSERT_EQ(material->apprentice_of_pipeline.get_master(), pipeline1);
    ASSERT_EQ(material->apprentice_of_pipeline.get_apprenticeID(), 0);
}

TEST(material_must_maintain_the_local_name_after_binding_to_a_new_parent, headless_universe_material_with_only_local_name)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::SceneStruct scene_struct1;
    yli::ontology::Scene* const scene1 = new yli::ontology::Scene(
            *universe,
            scene_struct1,
            &universe->parent_of_scenes);

    yli::ontology::MaterialStruct material_struct;
    material_struct.parent = scene1;
    yli::ontology::Material* const material = new yli::ontology::Material(
            *universe,
            material_struct,
            &scene1->parent_of_materials, nullptr);

    yli::ontology::SceneStruct scene_struct2;
    yli::ontology::Scene* const scene2 = new yli::ontology::Scene(
            *universe,
            scene_struct2,
            &universe->parent_of_scenes);

    material->set_local_name("foo");
    yli::ontology::Material::bind_to_new_scene_parent(*material, *scene2);
    ASSERT_FALSE(scene1->has_child("foo"));
    ASSERT_TRUE(scene2->has_child("foo"));
    ASSERT_EQ(material->get_parent(), scene2);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 1); // Default `Camera`.
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 2); // Default `Camera`, `material`.

    yli::ontology::Material::bind_to_new_scene_parent(*material, *scene1);
    ASSERT_TRUE(scene1->has_child("foo"));
    ASSERT_FALSE(scene2->has_child("foo"));
    ASSERT_EQ(material->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 2); // Default `Camera`, `material`.
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 1); // Default `Camera`.
}

TEST(material_must_maintain_the_local_name_after_binding_to_a_new_parent, headless_universe_material_with_global_name_and_local_name)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::SceneStruct scene_struct1;
    yli::ontology::Scene* const scene1 = new yli::ontology::Scene(
            *universe,
            scene_struct1,
            &universe->parent_of_scenes);

    yli::ontology::MaterialStruct material_struct;
    material_struct.parent = scene1;
    yli::ontology::Material* const material = new yli::ontology::Material(
            *universe,
            material_struct,
            &scene1->parent_of_materials, nullptr);

    yli::ontology::SceneStruct scene_struct2;
    yli::ontology::Scene* const scene2 = new yli::ontology::Scene(
            *universe,
            scene_struct2,
            &universe->parent_of_scenes);

    material->set_global_name("foo");
    material->set_local_name("bar");
    yli::ontology::Material::bind_to_new_scene_parent(*material, *scene2);
    ASSERT_FALSE(scene1->has_child("foo"));
    ASSERT_FALSE(scene2->has_child("foo"));
    ASSERT_FALSE(scene1->has_child("bar"));
    ASSERT_TRUE(scene2->has_child("bar"));
    ASSERT_EQ(material->get_parent(), scene2);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 1); // Default `Camera`.
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 2); // Default `Camera`, `material`.

    yli::ontology::Material::bind_to_new_scene_parent(*material, *scene1);
    ASSERT_FALSE(scene1->has_child("foo"));
    ASSERT_FALSE(scene2->has_child("foo"));
    ASSERT_TRUE(scene1->has_child("bar"));
    ASSERT_FALSE(scene2->has_child("bar"));
    ASSERT_EQ(material->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 2); // Default `Camera`, `material`.
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 1); // Default `Camera`.
}

TEST(material_must_not_bind_to_a_new_parent_when_local_name_is_already_in_use, headless_universe_materials_with_only_local_name)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::SceneStruct scene_struct1;
    yli::ontology::Scene* const scene1 = new yli::ontology::Scene(
            *universe,
            scene_struct1,
            &universe->parent_of_scenes);

    yli::ontology::MaterialStruct material_struct1;
    material_struct1.parent = scene1;
    yli::ontology::Material* const material1 = new yli::ontology::Material(
            *universe,
            material_struct1,
            &scene1->parent_of_materials, nullptr);

    yli::ontology::SceneStruct scene_struct2;
    yli::ontology::Scene* const scene2 = new yli::ontology::Scene(
            *universe,
            scene_struct2,
            &universe->parent_of_scenes);

    yli::ontology::MaterialStruct material_struct2;
    material_struct2.parent = scene2;
    yli::ontology::Material* const material2 = new yli::ontology::Material(
            *universe,
            material_struct2,
            &scene2->parent_of_materials, nullptr);

    material1->set_local_name("foo");
    material2->set_local_name("foo");
    yli::ontology::Material::bind_to_new_scene_parent(*material1, *scene2);
    ASSERT_EQ(material1->get_scene(), scene1);
    ASSERT_EQ(material1->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 2); // Default `Camera`, `material1`.
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 2); // Default `Cmaera`, `material2`.
    ASSERT_TRUE(scene1->has_child("foo"));
    ASSERT_TRUE(scene2->has_child("foo"));
}

TEST(material_must_not_bind_to_a_new_parent_when_local_name_is_already_in_use, headless_universe_materials_with_different_global_names_and_same_local_name)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::SceneStruct scene_struct1;
    yli::ontology::Scene* const scene1 = new yli::ontology::Scene(
            *universe,
            scene_struct1,
            &universe->parent_of_scenes);

    yli::ontology::MaterialStruct material_struct1;
    material_struct1.parent = scene1;
    yli::ontology::Material* const material1 = new yli::ontology::Material(
            *universe,
            material_struct1,
            &scene1->parent_of_materials, nullptr);

    yli::ontology::SceneStruct scene_struct2;
    yli::ontology::Scene* const scene2 = new yli::ontology::Scene(
            *universe,
            scene_struct2,
            &universe->parent_of_scenes);

    yli::ontology::MaterialStruct material_struct2;
    material_struct2.parent = scene2;
    yli::ontology::Material* const material2 = new yli::ontology::Material(
            *universe,
            material_struct2,
            &scene2->parent_of_materials, nullptr);

    material1->set_global_name("foo");
    material2->set_global_name("bar");
    material1->set_local_name("baz");
    material2->set_local_name("baz");
    yli::ontology::Material::bind_to_new_scene_parent(*material1, *scene2);
    ASSERT_EQ(material1->get_scene(), scene1);
    ASSERT_EQ(material1->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 2); // Default `Camera`, `material1`.
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 2); // Default `Camera`, `material1`.
    ASSERT_FALSE(scene1->has_child("foo"));
    ASSERT_FALSE(scene2->has_child("foo"));
    ASSERT_FALSE(scene1->has_child("bar"));
    ASSERT_FALSE(scene2->has_child("bar"));
    ASSERT_TRUE(scene1->has_child("baz"));
    ASSERT_TRUE(scene2->has_child("baz"));
}

TEST(material_must_not_unbind_any_of_its_apprentice_modules_when_binding_to_the_current_scene, headless_universe_species_apprentice)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);

    yli::ontology::MaterialStruct material_struct;
    material_struct.parent = scene;
    yli::ontology::Material* const material = new yli::ontology::Material(
            *universe,
            material_struct,
            &scene->parent_of_materials, nullptr);

    yli::ontology::ModelStruct model_struct;
    model_struct.parent = scene;
    model_struct.material = material;
    yli::ontology::Species* const species = new yli::ontology::Species(
            *universe,
            model_struct,
            &scene->parent_of_species,
            &material->master_of_species);

    ASSERT_EQ(material->get_number_of_apprentices(), 1);

    yli::ontology::Material::bind_to_new_scene_parent(*material, *scene);
    ASSERT_EQ(material->get_number_of_apprentices(), 1);
}

TEST(material_must_unbind_all_of_its_apprentice_modules_when_binding_to_a_different_scene, headless_universe_species_apprentice)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene1 = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);

    yli::ontology::MaterialStruct material_struct;
    material_struct.parent = scene1;
    yli::ontology::Material* const material = new yli::ontology::Material(
            *universe,
            material_struct,
            &scene1->parent_of_materials, nullptr);

    yli::ontology::ModelStruct model_struct;
    model_struct.parent = scene1;
    model_struct.material = material;
    yli::ontology::Species* const species = new yli::ontology::Species(
            *universe,
            model_struct,
            &scene1->parent_of_species,
            &material->master_of_species);

    ASSERT_EQ(material->get_number_of_apprentices(), 1);

    yli::ontology::Scene* const scene2 = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);

    yli::ontology::Material::bind_to_new_scene_parent(*material, *scene2);
    ASSERT_EQ(material->get_number_of_apprentices(), 0);
}
