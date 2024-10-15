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
#include "code/ylikuutio/data/datatype.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/ecosystem.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/pipeline.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/ecosystem_struct.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/pipeline_struct.hpp"
#include "code/ylikuutio/ontology/material_struct.hpp"
#include "code/ylikuutio/ontology/species_struct.hpp"

// Include standard headers
#include <cstddef> // std::size_t, uintptr_t
#include <limits>  // std::numeric_limits

namespace yli::ontology
{
    class GenericParentModule;
    class Species;
}

TEST(material_must_be_initialized_appropriately, headless_pipeline_is_child_of_ecosystem_ecosystem_parent_provided_as_valid_pointer)
{
    mock::MockApplication application;
    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    yli::ontology::PipelineStruct pipeline_struct(ecosystem);
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::MaterialStruct material_struct(ecosystem, pipeline);
    yli::ontology::Material* const material = application.get_generic_entity_factory().create_material(
            material_struct);
    ASSERT_NE(material, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(material) % alignof(yli::ontology::Material), 0);

    const yli::ontology::GenericParentModule* parent_of_shapeshifter_transformations { nullptr };
    const yli::ontology::GenericParentModule* parent_of_vector_fonts                 { nullptr };

    for (int datatype = 0; datatype < yli::data::Datatype::MAX_VALUE; datatype++)
    {
        const yli::ontology::GenericParentModule* const generic_parent_module = material->get_generic_parent_module(datatype);

        if (datatype == yli::data::Datatype::SHAPESHIFTER_TRANSFORMATION)
        {
            parent_of_shapeshifter_transformations = generic_parent_module;
            ASSERT_NE(parent_of_shapeshifter_transformations, nullptr);
        }
        else if (datatype == yli::data::Datatype::VECTOR_FONT)
        {
            parent_of_vector_fonts = generic_parent_module;
            ASSERT_NE(parent_of_vector_fonts, nullptr);
        }
        else
        {
            ASSERT_EQ(generic_parent_module, nullptr);
        }
    }

    ASSERT_LT(parent_of_shapeshifter_transformations, parent_of_vector_fonts);

    ASSERT_NE(material->get_generic_master_module<yli::ontology::Species>(), nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1); // `ecosystem`.

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
    ASSERT_EQ(material->get_scene(), nullptr);
    ASSERT_EQ(material->get_parent(), ecosystem);
    ASSERT_EQ(material->get_number_of_non_variable_children(), 0);
}

TEST(material_must_be_initialized_and_appropriately, headless_pipeline_is_child_of_scene_ecosystem_parent_provided_as_valid_pointer)
{
    mock::MockApplication application;
    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct(scene);
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::MaterialStruct material_struct(ecosystem, pipeline);
    yli::ontology::Material* const material = application.get_generic_entity_factory().create_material(
            material_struct);
    ASSERT_NE(material, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(material) % alignof(yli::ontology::Material), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 2); // `ecosystem`, `scene`.

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
    ASSERT_EQ(material->get_scene(), nullptr);
    ASSERT_EQ(material->get_parent(), ecosystem);
    ASSERT_EQ(material->get_number_of_non_variable_children(), 0);
}

TEST(material_must_be_initialized_appropriately, headless_pipeline_is_child_of_ecosystem_ecosystem_parent_provided_as_valid_global_name)
{
    mock::MockApplication application;
    yli::ontology::EcosystemStruct ecosystem_struct;
    ecosystem_struct.global_name = "foo";
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    yli::ontology::PipelineStruct pipeline_struct(ecosystem);
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::MaterialStruct material_struct("foo", pipeline);
    yli::ontology::Material* const material = application.get_generic_entity_factory().create_material(
            material_struct);
    ASSERT_NE(material, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(material) % alignof(yli::ontology::Material), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1); // `ecosystem`.

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
    ASSERT_EQ(material->get_scene(), nullptr);
    ASSERT_EQ(material->get_parent(), ecosystem);
    ASSERT_EQ(material->get_number_of_non_variable_children(), 0);
}

TEST(material_must_be_initialized_and_appropriately, headless_pipeline_is_child_of_scene_scene_parent_provided_as_valid_global_name)
{
    mock::MockApplication application;
    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.global_name = "foo";
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct(scene);
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::MaterialStruct material_struct("foo", pipeline);
    yli::ontology::Material* const material = application.get_generic_entity_factory().create_material(
            material_struct);
    ASSERT_NE(material, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(material) % alignof(yli::ontology::Material), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 2); // `ecosystem`, `scene`.

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem->get_scene(), nullptr);
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 0);

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
    ASSERT_EQ(material->get_scene(), scene);
    ASSERT_EQ(material->get_parent(), scene);
    ASSERT_EQ(material->get_number_of_non_variable_children(), 0);
}

TEST(material_must_be_initialized_appropriately, headless_pipeline_is_child_of_ecosystem_parent_provided_as_invalid_global_name)
{
    mock::MockApplication application;
    yli::ontology::EcosystemStruct ecosystem_struct;
    ecosystem_struct.global_name = "foo";
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    yli::ontology::PipelineStruct pipeline_struct(ecosystem);
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::MaterialStruct material_struct("bar", pipeline);
    yli::ontology::Material* const material = application.get_generic_entity_factory().create_material(
            material_struct);
    ASSERT_NE(material, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(material) % alignof(yli::ontology::Material), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1); // `ecosystem`.

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem->get_scene(), nullptr);
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 1); // `material`.

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
    ASSERT_EQ(material->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(material->get_type(), "yli::ontology::Material*");
    ASSERT_TRUE(material->get_can_be_erased());
    ASSERT_EQ(material->get_scene(), nullptr);
    ASSERT_EQ(material->get_parent(), nullptr);
    ASSERT_EQ(material->get_number_of_non_variable_children(), 0);
}

TEST(material_must_be_initialized_and_appropriately, headless_pipeline_is_child_of_scene_parent_provided_as_invalid_global_name)
{
    mock::MockApplication application;
    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.global_name = "foo";
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct(scene);
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::MaterialStruct material_struct("bar", pipeline);
    yli::ontology::Material* const material = application.get_generic_entity_factory().create_material(
            material_struct);
    ASSERT_NE(material, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(material) % alignof(yli::ontology::Material), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 2); // `ecosystem`, `scene`.

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem->get_scene(), nullptr);
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 0);

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
    ASSERT_EQ(material->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(material->get_type(), "yli::ontology::Material*");
    ASSERT_TRUE(material->get_can_be_erased());
    ASSERT_EQ(material->get_scene(), nullptr);
    ASSERT_EQ(material->get_parent(), nullptr);
    ASSERT_EQ(material->get_number_of_non_variable_children(), 0);
}

TEST(material_must_be_initialized_appropriately, headless)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct(scene);
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::MaterialStruct material_struct(scene, pipeline);
    yli::ontology::Material* const material = application.get_generic_entity_factory().create_material(
            material_struct);
    ASSERT_NE(material, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(material) % alignof(yli::ontology::Material), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

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
    ASSERT_EQ(material->get_scene(), scene);
    ASSERT_EQ(material->get_parent(), scene);
    ASSERT_EQ(material->get_number_of_non_variable_children(), 0);
}

TEST(material_must_bind_to_ecosystem_appropriately, ecosystem)
{
    mock::MockApplication application;
    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem1 = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    yli::ontology::MaterialStruct material_struct(ecosystem1, nullptr);
    yli::ontology::Material* const material = application.get_generic_entity_factory().create_material(
            material_struct);
    ASSERT_EQ(material->get_scene(), nullptr);
    ASSERT_EQ(material->get_parent(), ecosystem1);
    ASSERT_EQ(ecosystem1->get_number_of_non_variable_children(), 1);

    yli::ontology::Ecosystem* const ecosystem2 = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    ASSERT_EQ(material->get_scene(), nullptr);
    ASSERT_EQ(material->get_parent(), ecosystem1);
    ASSERT_EQ(ecosystem2->get_number_of_non_variable_children(), 0);

    yli::ontology::Material::bind_to_new_ecosystem_parent(*material, *ecosystem2);
    ASSERT_EQ(material->get_scene(), nullptr);
    ASSERT_EQ(material->get_parent(), ecosystem2);
    ASSERT_EQ(ecosystem1->get_number_of_non_variable_children(), 0);
    ASSERT_EQ(ecosystem2->get_number_of_non_variable_children(), 1);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 2); // `ecosystem1`, `ecosystem2`.

    yli::ontology::Material::bind_to_new_ecosystem_parent(*material, *ecosystem1);
    ASSERT_EQ(material->get_scene(), nullptr);
    ASSERT_EQ(material->get_parent(), ecosystem1);
    ASSERT_EQ(ecosystem1->get_number_of_non_variable_children(), 1);
    ASSERT_EQ(ecosystem2->get_number_of_non_variable_children(), 0);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 2); // `ecosystem1`, `ecosystem2`.
}

TEST(material_must_bind_to_scene_appropriately, scenes_no_pipelines)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene1 = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::MaterialStruct material_struct(scene1, nullptr);
    yli::ontology::Material* const material = application.get_generic_entity_factory().create_material(
            material_struct);
    ASSERT_EQ(material->get_scene(), scene1);
    ASSERT_EQ(material->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 2); // Default `Camera`, `material`.

    yli::ontology::Scene* const scene2 = application.get_generic_entity_factory().create_scene(
            scene_struct);
    ASSERT_EQ(material->get_scene(), scene1);
    ASSERT_EQ(material->get_parent(), scene1);
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 1);

    yli::ontology::Material::bind_to_new_scene_parent(*material, *scene2);
    ASSERT_EQ(material->get_scene(), scene2);
    ASSERT_EQ(material->get_parent(), scene2);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 1); // Default `Camera`.
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 2); // Default `Camera`, `material`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 2);

    yli::ontology::Material::bind_to_new_scene_parent(*material, *scene1);
    ASSERT_EQ(material->get_scene(), scene1);
    ASSERT_EQ(material->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 2); // Default `Camera`, `material`.
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 1); // Default `Camera`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 2);
}

TEST(material_must_bind_to_ecosystem_appropriately_after_binding_to_scene, ecosystem_scene)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::MaterialStruct material_struct(scene, nullptr);
    yli::ontology::Material* const material = application.get_generic_entity_factory().create_material(
            material_struct);

    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);
    ASSERT_EQ(material->get_scene(), scene);
    ASSERT_EQ(material->get_parent(), scene);
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 0);

    yli::ontology::Material::bind_to_new_ecosystem_parent(*material, *ecosystem);
    ASSERT_EQ(material->get_scene(), nullptr);
    ASSERT_EQ(material->get_parent(), ecosystem);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 1);     // Default `Camera`.
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 1); // `material`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 2);  // `ecosystem`, `scene`.

    yli::ontology::Material::bind_to_new_scene_parent(*material, *scene);
    ASSERT_EQ(material->get_scene(), scene);
    ASSERT_EQ(material->get_parent(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 2);     // Default `Camera`, `material`.
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 0);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 2);  // `ecosystem`, `scene`.
}

TEST(material_must_bind_to_scene_appropriately_after_binding_to_ecosystem, scene_ecosystem)
{
    mock::MockApplication application;
    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    yli::ontology::MaterialStruct material_struct(ecosystem, nullptr);
    yli::ontology::Material* const material = application.get_generic_entity_factory().create_material(
            material_struct);

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);
    ASSERT_EQ(material->get_scene(), nullptr);
    ASSERT_EQ(material->get_parent(), ecosystem);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 1); // Default `Camera`.

    yli::ontology::Material::bind_to_new_scene_parent(*material, *scene);
    ASSERT_EQ(material->get_scene(), scene);
    ASSERT_EQ(material->get_parent(), scene);
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 0);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 2);     // Default `Camera`, `material`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 2);  // `Ecosystem`, `Scene`.

    yli::ontology::Material::bind_to_new_ecosystem_parent(*material, *ecosystem);
    ASSERT_EQ(material->get_scene(), nullptr);
    ASSERT_EQ(material->get_parent(), ecosystem);
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 1); // `material`.
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 1);     // Default `Camera`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 2);  // `Ecosystem`, `Scene`.
}

TEST(material_must_bind_to_pipeline_appropriately, master_and_apprentice)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct(scene);
    yli::ontology::Pipeline* const pipeline1 = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::MaterialStruct material_struct(scene, pipeline1);
    yli::ontology::Material* const material = application.get_generic_entity_factory().create_material(
            material_struct);

    ASSERT_EQ(pipeline1->get_number_of_apprentices(), 1);
    yli::ontology::Pipeline* const pipeline2 = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);
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
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct1;
    yli::ontology::Scene* const scene1 = application.get_generic_entity_factory().create_scene(
            scene_struct1);

    yli::ontology::MaterialStruct material_struct(scene1, nullptr);
    yli::ontology::Material* const material = application.get_generic_entity_factory().create_material(
            material_struct);

    yli::ontology::SceneStruct scene_struct2;
    yli::ontology::Scene* const scene2 = application.get_generic_entity_factory().create_scene(
            scene_struct2);

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
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct1;
    yli::ontology::Scene* const scene1 = application.get_generic_entity_factory().create_scene(
            scene_struct1);

    yli::ontology::MaterialStruct material_struct(scene1, nullptr);
    yli::ontology::Material* const material = application.get_generic_entity_factory().create_material(
            material_struct);

    yli::ontology::SceneStruct scene_struct2;
    yli::ontology::Scene* const scene2 = application.get_generic_entity_factory().create_scene(
            scene_struct2);

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
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct1;
    yli::ontology::Scene* const scene1 = application.get_generic_entity_factory().create_scene(
            scene_struct1);

    yli::ontology::MaterialStruct material_struct1(scene1, nullptr);
    yli::ontology::Material* const material1 = application.get_generic_entity_factory().create_material(
            material_struct1);

    yli::ontology::SceneStruct scene_struct2;
    yli::ontology::Scene* const scene2 = application.get_generic_entity_factory().create_scene(
            scene_struct2);

    yli::ontology::MaterialStruct material_struct2(scene2, nullptr);
    yli::ontology::Material* const material2 = application.get_generic_entity_factory().create_material(
            material_struct2);

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
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct1;
    yli::ontology::Scene* const scene1 = application.get_generic_entity_factory().create_scene(
            scene_struct1);

    yli::ontology::MaterialStruct material_struct1(scene1, nullptr);
    yli::ontology::Material* const material1 = application.get_generic_entity_factory().create_material(
            material_struct1);

    yli::ontology::SceneStruct scene_struct2;
    yli::ontology::Scene* const scene2 = application.get_generic_entity_factory().create_scene(
            scene_struct2);

    yli::ontology::MaterialStruct material_struct2(scene2, nullptr);
    yli::ontology::Material* const material2 = application.get_generic_entity_factory().create_material(
            material_struct2);

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
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::MaterialStruct material_struct(scene, nullptr);
    yli::ontology::Material* const material = application.get_generic_entity_factory().create_material(
            material_struct);

    yli::ontology::SpeciesStruct species_struct(scene, nullptr, material);
    application.get_generic_entity_factory().create_species(
            species_struct);

    ASSERT_EQ(material->get_number_of_apprentices(), 1);

    yli::ontology::Material::bind_to_new_scene_parent(*material, *scene);
    ASSERT_EQ(material->get_number_of_apprentices(), 1);
}

TEST(material_must_unbind_all_of_its_apprentice_modules_when_binding_to_a_different_scene, headless_universe_species_apprentice)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene1 = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::MaterialStruct material_struct(scene1, nullptr);
    yli::ontology::Material* const material = application.get_generic_entity_factory().create_material(
            material_struct);

    yli::ontology::SpeciesStruct species_struct(scene1, nullptr, material);
    application.get_generic_entity_factory().create_species(
            species_struct);

    ASSERT_EQ(material->get_number_of_apprentices(), 1);

    yli::ontology::Scene* const scene2 = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::Material::bind_to_new_scene_parent(*material, *scene2);
    ASSERT_EQ(material->get_number_of_apprentices(), 0);
}
