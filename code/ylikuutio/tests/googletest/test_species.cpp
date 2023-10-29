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
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/ecosystem_struct.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/pipeline_struct.hpp"
#include "code/ylikuutio/ontology/material_struct.hpp"
#include "code/ylikuutio/ontology/model_struct.hpp"
#include "code/ylikuutio/ontology/object_struct.hpp"

TEST(species_must_be_initialized_and_must_bind_to_ecosystem_appropriately, headless_pipeline_and_material_are_children_of_an_ecosystem)
{
    mock::MockApplication application;
    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    yli::ontology::PipelineStruct pipeline_struct;
    pipeline_struct.parent = ecosystem;
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::MaterialStruct material_struct;
    material_struct.parent = ecosystem;
    material_struct.pipeline = pipeline;
    yli::ontology::Material* const material = application.get_generic_entity_factory().create_material(
            material_struct);

    yli::ontology::ModelStruct model_struct;
    model_struct.parent = ecosystem;
    model_struct.pipeline = pipeline;
    model_struct.material = material;
    yli::ontology::Species* const species = application.get_generic_entity_factory().create_species(
            model_struct);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);  // `ecosystem`.

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 3); // `pipeline`, `material`, `species`.

    // `Entity` member functions of `Pipeline`.
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 0);

    // `Entity` member functions of `Material`.
    ASSERT_EQ(material->get_number_of_non_variable_children(), 0);

    // `Material` member functions.
    ASSERT_EQ(material->get_number_of_apprentices(), 1); // `species`.

    ASSERT_EQ(species->apprentice_of_material.get_master(), material);
    ASSERT_EQ(species->apprentice_of_material.get_apprenticeID(), 0);

    // `Entity` member functions.
    ASSERT_EQ(species->get_childID(), 0);
    ASSERT_EQ(species->get_type(), "yli::ontology::Species*");
    ASSERT_TRUE(species->get_can_be_erased());
    ASSERT_EQ(species->get_scene(), nullptr);
    ASSERT_EQ(species->get_parent(), ecosystem);
    ASSERT_EQ(species->get_number_of_non_variable_children(), 0);
}

TEST(species_must_be_initialized_and_must_bind_to_ecosystem_appropriately, headless_pipeline_and_material_are_children_of_scene)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct;
    pipeline_struct.parent = scene;
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    yli::ontology::MaterialStruct material_struct;
    material_struct.parent = scene;
    material_struct.pipeline = pipeline;
    yli::ontology::Material* const material = application.get_generic_entity_factory().create_material(
            material_struct);

    yli::ontology::ModelStruct model_struct;
    model_struct.parent = ecosystem;
    model_struct.pipeline = pipeline;
    model_struct.material = material;
    yli::ontology::Species* const species = application.get_generic_entity_factory().create_species(
            model_struct);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 2); // `ecosystem`, `scene`.

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 1); // `species`.

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 3); // Default `Camera`, `pipeline`, `material`.

    // `Entity` member functions of `Pipeline`.
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 0);

    // `Entity` member functions of `Material`.
    ASSERT_EQ(material->get_number_of_non_variable_children(), 0);

    // `Material` member functions.
    ASSERT_EQ(material->get_number_of_apprentices(), 1); // `species`.

    ASSERT_EQ(species->apprentice_of_material.get_master(), material);
    ASSERT_EQ(species->apprentice_of_material.get_apprenticeID(), 0);

    // `Entity` member functions.
    ASSERT_EQ(species->get_childID(), 0);
    ASSERT_EQ(species->get_type(), "yli::ontology::Species*");
    ASSERT_TRUE(species->get_can_be_erased());
    ASSERT_EQ(species->get_scene(), nullptr);
    ASSERT_EQ(species->get_parent(), ecosystem);
    ASSERT_EQ(species->get_number_of_non_variable_children(), 0);
}

TEST(species_must_be_initialized_appropriately, headless)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct;
    pipeline_struct.parent = scene;
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::MaterialStruct material_struct;
    material_struct.parent = scene;
    material_struct.pipeline = pipeline;
    yli::ontology::Material* const material = application.get_generic_entity_factory().create_material(
            material_struct);

    yli::ontology::ModelStruct model_struct;
    model_struct.parent = scene;
    model_struct.pipeline = pipeline;
    model_struct.material = material;
    yli::ontology::Species* const species = application.get_generic_entity_factory().create_species(
            model_struct);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 4); // Default `Camera`, `pipeline`, `material`, `species`.

    // `Entity` member functions of `Pipeline`.
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 0);

    // `Entity` member functions of `Material`.
    ASSERT_EQ(material->get_number_of_non_variable_children(), 0);

    // `Material` member functions.
    ASSERT_EQ(material->get_number_of_apprentices(), 1); // `species`.

    ASSERT_EQ(species->apprentice_of_material.get_master(), material);
    ASSERT_EQ(species->apprentice_of_material.get_apprenticeID(), 0);

    // `Entity` member functions.
    ASSERT_EQ(species->get_childID(), 0);
    ASSERT_EQ(species->get_type(), "yli::ontology::Species*");
    ASSERT_TRUE(species->get_can_be_erased());
    ASSERT_EQ(species->get_scene(), scene);
    ASSERT_EQ(species->get_parent(), scene);
    ASSERT_EQ(species->get_number_of_non_variable_children(), 0);
}

TEST(species_must_bind_to_ecosystem_appropriately, ecosystem)
{
    mock::MockApplication application;
    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem1 = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    yli::ontology::ModelStruct model_struct;
    model_struct.parent = ecosystem1;
    yli::ontology::Species* const species = application.get_generic_entity_factory().create_species(
            model_struct);
    ASSERT_EQ(species->get_scene(), nullptr);
    ASSERT_EQ(species->get_parent(), ecosystem1);
    ASSERT_EQ(ecosystem1->get_number_of_non_variable_children(), 1); // `species`.

    yli::ontology::Ecosystem* const ecosystem2 = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    ASSERT_EQ(species->get_scene(), nullptr);
    ASSERT_EQ(species->get_parent(), ecosystem1);
    ASSERT_EQ(ecosystem2->get_number_of_non_variable_children(), 0);

    yli::ontology::Species::bind_to_new_ecosystem_parent(*species, *ecosystem2);
    ASSERT_EQ(species->get_scene(), nullptr);
    ASSERT_EQ(species->get_parent(), ecosystem2);
    ASSERT_EQ(ecosystem1->get_number_of_non_variable_children(), 0);
    ASSERT_EQ(ecosystem2->get_number_of_non_variable_children(), 1);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 2); // `ecosystem1`, `ecosystem2`.

    yli::ontology::Species::bind_to_new_ecosystem_parent(*species, *ecosystem1);
    ASSERT_EQ(species->get_scene(), nullptr);
    ASSERT_EQ(species->get_parent(), ecosystem1);
    ASSERT_EQ(ecosystem1->get_number_of_non_variable_children(), 1);
    ASSERT_EQ(ecosystem2->get_number_of_non_variable_children(), 0);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 2); // `ecosystem1`, `ecosystem2`.
}

TEST(species_must_bind_to_scene_appropriately, scenes_no_pipelines_no_materials)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct1;
    yli::ontology::Scene* const scene1 = application.get_generic_entity_factory().create_scene(
            scene_struct1);

    yli::ontology::ModelStruct model_struct;
    model_struct.parent = scene1;
    yli::ontology::Species* const species = application.get_generic_entity_factory().create_species(
            model_struct);
    ASSERT_EQ(species->get_scene(), scene1);
    ASSERT_EQ(species->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 2); // Default `Camera`, `species`.

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene2 = application.get_generic_entity_factory().create_scene(
            scene_struct);
    ASSERT_EQ(species->get_scene(), scene1);
    ASSERT_EQ(species->get_parent(), scene1);
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 1); // Default `Camera`.

    yli::ontology::Species::bind_to_new_scene_parent(*species, *scene2);
    ASSERT_EQ(species->get_scene(), scene2);
    ASSERT_EQ(species->get_parent(), scene2);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 1); // Default `Camera`.
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 2); // Default `Camera`, `species`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 2);

    yli::ontology::Species::bind_to_new_scene_parent(*species, *scene1);
    ASSERT_EQ(species->get_scene(), scene1);
    ASSERT_EQ(species->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 2); // Default `Camera`, `species`.
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 1); // Default `Camera`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 2);
}

TEST(species_must_bind_to_ecosystem_appropriately_after_binding_to_scene, ecosystem_scene)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::ModelStruct model_struct;
    model_struct.parent = scene;
    yli::ontology::Species* const species = application.get_generic_entity_factory().create_species(
            model_struct);
    ASSERT_EQ(species->get_scene(), scene);
    ASSERT_EQ(species->get_parent(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 2); // Default `Camera`, `species`.

    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);
    ASSERT_EQ(species->get_scene(), scene);
    ASSERT_EQ(species->get_parent(), scene);
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 0);

    yli::ontology::Species::bind_to_new_ecosystem_parent(*species, *ecosystem);
    ASSERT_EQ(species->get_scene(), nullptr);
    ASSERT_EQ(species->get_parent(), ecosystem);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 1);     // Default `Camera`.
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 1); // `species`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 2);  // `ecosystem`, `scene`.

    yli::ontology::Species::bind_to_new_scene_parent(*species, *scene);
    ASSERT_EQ(species->get_scene(), scene);
    ASSERT_EQ(species->get_parent(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 2);     // Default `Camera`, `species`.
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 0);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 2);  // `ecosystem`, `scene`.
}

TEST(species_must_bind_to_scene_appropriately_after_binding_to_ecosystem, scene_ecosystem)
{
    mock::MockApplication application;
    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    yli::ontology::ModelStruct model_struct;
    model_struct.parent = ecosystem;
    yli::ontology::Species* const species = application.get_generic_entity_factory().create_species(
            model_struct);
    ASSERT_EQ(species->get_scene(), nullptr);
    ASSERT_EQ(species->get_parent(), ecosystem);
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 1); // `species`.

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);
    ASSERT_EQ(species->get_scene(), nullptr);
    ASSERT_EQ(species->get_parent(), ecosystem);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 1); // Default `Camera`.

    yli::ontology::Species::bind_to_new_scene_parent(*species, *scene);
    ASSERT_EQ(species->get_scene(), scene);
    ASSERT_EQ(species->get_parent(), scene);
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 0);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 2);     // Default `Camera`, `species`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 2);  // `Ecosystem`, `Scene`.

    yli::ontology::Species::bind_to_new_ecosystem_parent(*species, *ecosystem);
    ASSERT_EQ(species->get_scene(), nullptr);
    ASSERT_EQ(species->get_parent(), ecosystem);
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 1); // `species`.
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 1);     // Default `Camera`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 2);  // `Ecosystem`, `Scene`.
}

TEST(species_must_maintain_the_local_name_after_binding_to_a_new_parent, headless_universe_species_with_only_local_name)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene1 = application.get_generic_entity_factory().create_scene(
            scene_struct);
    yli::ontology::Scene* const scene2 = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::ModelStruct model_struct;
    model_struct.parent = scene1;
    yli::ontology::Species* const species = application.get_generic_entity_factory().create_species(
            model_struct);

    species->set_local_name("foo");
    yli::ontology::Species::bind_to_new_scene_parent(*species, *scene2);
    ASSERT_FALSE(scene1->has_child("foo"));
    ASSERT_TRUE(scene2->has_child("foo"));
    ASSERT_EQ(species->get_parent(), scene2);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 1); // Default `Camera`.
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 2); // Default `Camera`, `species`.

    yli::ontology::Species::bind_to_new_scene_parent(*species, *scene1);
    ASSERT_TRUE(scene1->has_child("foo"));
    ASSERT_FALSE(scene2->has_child("foo"));
    ASSERT_EQ(species->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 2); // Default `Camera`, `species`.
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 1); // Default `Camera`.
}

TEST(species_must_maintain_the_local_name_after_binding_to_a_new_parent, headless_universe_species_with_global_name_and_local_name)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene1 = application.get_generic_entity_factory().create_scene(
            scene_struct);
    yli::ontology::Scene* const scene2 = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::ModelStruct model_struct;
    model_struct.parent = scene1;
    yli::ontology::Species* const species = application.get_generic_entity_factory().create_species(
            model_struct);

    species->set_global_name("foo");
    species->set_local_name("bar");
    yli::ontology::Species::bind_to_new_scene_parent(*species, *scene2);
    ASSERT_FALSE(scene1->has_child("foo"));
    ASSERT_FALSE(scene2->has_child("foo"));
    ASSERT_FALSE(scene1->has_child("bar"));
    ASSERT_TRUE(scene2->has_child("bar"));
    ASSERT_EQ(species->get_parent(), scene2);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 1); // Default `Camera`.
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 2); // Default `Camera`, `species`.

    yli::ontology::Species::bind_to_new_scene_parent(*species, *scene1);
    ASSERT_FALSE(scene1->has_child("foo"));
    ASSERT_FALSE(scene2->has_child("foo"));
    ASSERT_TRUE(scene1->has_child("bar"));
    ASSERT_FALSE(scene2->has_child("bar"));
    ASSERT_EQ(species->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 2); // Default `Camera`, `species`.
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 1); // Default `Camera`.
}

TEST(species_must_not_bind_to_a_new_parent_when_local_name_is_already_in_use, headless_universe_species_with_only_local_name)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene1 = application.get_generic_entity_factory().create_scene(
            scene_struct);
    yli::ontology::Scene* const scene2 = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::ModelStruct model_struct1;
    model_struct1.parent = scene1;
    yli::ontology::Species* const species1 = application.get_generic_entity_factory().create_species(
            model_struct1);

    yli::ontology::ModelStruct model_struct2;
    model_struct2.parent = scene2;
    yli::ontology::Species* const species2 = application.get_generic_entity_factory().create_species(
            model_struct2);

    species1->set_local_name("foo");
    species2->set_local_name("foo");
    yli::ontology::Species::bind_to_new_scene_parent(*species1, *scene2);
    ASSERT_EQ(species1->get_scene(), scene1);
    ASSERT_EQ(species1->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 2); // Default `Camera`, `species1`.
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 2); // Default `Camera`, `species2`.
    ASSERT_TRUE(scene1->has_child("foo"));
    ASSERT_TRUE(scene2->has_child("foo"));
}

TEST(species_must_not_bind_to_a_new_parent_when_local_name_is_already_in_use, headless_universe_species_with_different_global_names_and_same_local_name)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene1 = application.get_generic_entity_factory().create_scene(
            scene_struct);
    yli::ontology::Scene* const scene2 = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::ModelStruct model_struct1;
    model_struct1.parent = scene1;
    yli::ontology::Species* const species1 = application.get_generic_entity_factory().create_species(
            model_struct1);

    yli::ontology::ModelStruct model_struct2;
    model_struct2.parent = scene2;
    yli::ontology::Species* const species2 = application.get_generic_entity_factory().create_species(
            model_struct2);

    species1->set_global_name("foo");
    species2->set_global_name("bar");
    species1->set_local_name("baz");
    species2->set_local_name("baz");
    yli::ontology::Species::bind_to_new_scene_parent(*species1, *scene2);
    ASSERT_EQ(species1->get_scene(), scene1);
    ASSERT_EQ(species1->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 2); // Default `Camera`, `species1`.
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 2); // Default `Camera`, `species2`.
    ASSERT_FALSE(scene1->has_child("foo"));
    ASSERT_FALSE(scene2->has_child("foo"));
    ASSERT_FALSE(scene1->has_child("bar"));
    ASSERT_FALSE(scene2->has_child("bar"));
    ASSERT_TRUE(scene1->has_child("baz"));
    ASSERT_TRUE(scene2->has_child("baz"));
}

TEST(species_must_not_unbind_any_of_its_apprentice_modules_when_binding_to_the_current_scene, headless_universe_object_apprentice)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct1;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct1);

    yli::ontology::ModelStruct model_struct;
    model_struct.parent = scene;
    yli::ontology::Species* const species = application.get_generic_entity_factory().create_species(
            model_struct);

    yli::ontology::ObjectStruct object_struct(scene, species);
    application.get_generic_entity_factory().create_object(
            object_struct);

    ASSERT_EQ(species->get_number_of_apprentices(), 1);

    yli::ontology::Species::bind_to_new_scene_parent(*species, *scene);
    ASSERT_EQ(species->get_number_of_apprentices(), 1);
}

TEST(species_must_unbind_all_its_apprentice_modules_when_binding_to_a_different_scene, headless_universe_object_apprentice)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct1;
    yli::ontology::Scene* const scene1 = application.get_generic_entity_factory().create_scene(
            scene_struct1);

    yli::ontology::ModelStruct model_struct;
    model_struct.parent = scene1;
    yli::ontology::Species* const species = application.get_generic_entity_factory().create_species(
            model_struct);

    yli::ontology::ObjectStruct object_struct(scene1, species);
    application.get_generic_entity_factory().create_object(
            object_struct);

    ASSERT_EQ(species->get_number_of_apprentices(), 1);

    yli::ontology::Scene* const scene2 = application.get_generic_entity_factory().create_scene(
            scene_struct1);

    yli::ontology::Species::bind_to_new_scene_parent(*species, *scene2);
    ASSERT_EQ(species->get_number_of_apprentices(), 0);
}
