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
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/pipeline.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/shapeshifter_transformation.hpp"
#include "code/ylikuutio/ontology/shapeshifter_sequence.hpp"
#include "code/ylikuutio/ontology/shapeshifter_form.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/pipeline_struct.hpp"
#include "code/ylikuutio/ontology/material_struct.hpp"
#include "code/ylikuutio/ontology/object_struct.hpp"
#include "code/ylikuutio/ontology/shapeshifter_transformation_struct.hpp"
#include "code/ylikuutio/ontology/shapeshifter_sequence_struct.hpp"
#include "code/ylikuutio/ontology/shapeshifter_form_struct.hpp"

// Include standard headers
#include <cstddef> // std::size_t, uintptr_t
#include <limits>  // std::numeric_limits

TEST(shapeshifter_transformation_must_be_initialized_appropriately, headless_material_parent_provided_as_valid_pointer)
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

    yli::ontology::ShapeshifterTransformationStruct shapeshifter_transformation_struct(material);
    yli::ontology::ShapeshifterTransformation* const shapeshifter_transformation = application.get_generic_entity_factory().create_shapeshifter_transformation(
            shapeshifter_transformation_struct);
    ASSERT_NE(shapeshifter_transformation, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(shapeshifter_transformation) % alignof(yli::ontology::ShapeshifterTransformation), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_scene(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 3); // Default `Camera`, `pipeline`, `material`.

    // `Entity` member functions of `Pipeline`.
    ASSERT_EQ(pipeline->get_scene(), scene);
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 0);

    // `Entity` member functions of `Material`.
    ASSERT_EQ(material->get_scene(), scene);
    ASSERT_EQ(material->get_number_of_non_variable_children(), 1); // `shapeshifter_transformation`.

    // `Material` member functions.
    ASSERT_EQ(material->get_number_of_apprentices(), 0);

    // `Entity` member functions.
    ASSERT_EQ(shapeshifter_transformation->get_childID(), 0);
    ASSERT_EQ(shapeshifter_transformation->get_type(), "yli::ontology::ShapeshifterTransformation*");
    ASSERT_TRUE(shapeshifter_transformation->get_can_be_erased());
    ASSERT_EQ(shapeshifter_transformation->get_scene(), scene);
    ASSERT_EQ(shapeshifter_transformation->get_parent(), material);
    ASSERT_EQ(shapeshifter_transformation->get_number_of_non_variable_children(), 0);
}

TEST(shapeshifter_transformation_must_be_initialized_appropriately, headless_material_parent_provided_as_nullptr)
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

    yli::ontology::ShapeshifterTransformationStruct shapeshifter_transformation_struct(nullptr);
    yli::ontology::ShapeshifterTransformation* const shapeshifter_transformation = application.get_generic_entity_factory().create_shapeshifter_transformation(
            shapeshifter_transformation_struct);
    ASSERT_NE(shapeshifter_transformation, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(shapeshifter_transformation) % alignof(yli::ontology::ShapeshifterTransformation), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_scene(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 3); // Default `Camera`, `pipeline`, `material`.

    // `Entity` member functions of `Pipeline`.
    ASSERT_EQ(pipeline->get_scene(), scene);
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 0);

    // `Entity` member functions of `Material`.
    ASSERT_EQ(material->get_scene(), scene);
    ASSERT_EQ(material->get_number_of_non_variable_children(), 0);

    // `Material` member functions.
    ASSERT_EQ(material->get_number_of_apprentices(), 0);

    // `Entity` member functions.
    ASSERT_EQ(shapeshifter_transformation->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(shapeshifter_transformation->get_type(), "yli::ontology::ShapeshifterTransformation*");
    ASSERT_TRUE(shapeshifter_transformation->get_can_be_erased());
    ASSERT_EQ(shapeshifter_transformation->get_parent(), nullptr);
    ASSERT_EQ(shapeshifter_transformation->get_number_of_non_variable_children(), 0);
}

TEST(shapeshifter_transformation_must_be_initialized_appropriately, headless_material_parent_provided_as_valid_global_name)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct(scene);
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::MaterialStruct material_struct(scene, pipeline);
    material_struct.global_name = "foo";
    yli::ontology::Material* const material = application.get_generic_entity_factory().create_material(
            material_struct);

    yli::ontology::ShapeshifterTransformationStruct shapeshifter_transformation_struct("foo");
    yli::ontology::ShapeshifterTransformation* const shapeshifter_transformation = application.get_generic_entity_factory().create_shapeshifter_transformation(
            shapeshifter_transformation_struct);
    ASSERT_NE(shapeshifter_transformation, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(shapeshifter_transformation) % alignof(yli::ontology::ShapeshifterTransformation), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_scene(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 3); // Default `Camera`, `pipeline`, `material`.

    // `Entity` member functions of `Pipeline`.
    ASSERT_EQ(pipeline->get_scene(), scene);
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 0);

    // `Entity` member functions of `Material`.
    ASSERT_EQ(material->get_scene(), scene);
    ASSERT_EQ(material->get_number_of_non_variable_children(), 1); // `shapeshifter_transformation`.

    // `Material` member functions.
    ASSERT_EQ(material->get_number_of_apprentices(), 0);

    // `Entity` member functions.
    ASSERT_EQ(shapeshifter_transformation->get_childID(), 0);
    ASSERT_EQ(shapeshifter_transformation->get_type(), "yli::ontology::ShapeshifterTransformation*");
    ASSERT_TRUE(shapeshifter_transformation->get_can_be_erased());
    ASSERT_EQ(shapeshifter_transformation->get_scene(), scene);
    ASSERT_EQ(shapeshifter_transformation->get_parent(), material);
    ASSERT_EQ(shapeshifter_transformation->get_number_of_non_variable_children(), 0);
}

TEST(shapeshifter_transformation_must_be_initialized_appropriately, headless_material_parent_provided_as_invalid_global_name)
{
    mock::MockApplication application;
    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = application.get_generic_entity_factory().create_scene(
            scene_struct);

    yli::ontology::PipelineStruct pipeline_struct(scene);
    yli::ontology::Pipeline* const pipeline = application.get_generic_entity_factory().create_pipeline(
            pipeline_struct);

    yli::ontology::MaterialStruct material_struct(scene, pipeline);
    material_struct.global_name = "foo";
    yli::ontology::Material* const material = application.get_generic_entity_factory().create_material(
            material_struct);

    yli::ontology::ShapeshifterTransformationStruct shapeshifter_transformation_struct("bar");
    yli::ontology::ShapeshifterTransformation* const shapeshifter_transformation = application.get_generic_entity_factory().create_shapeshifter_transformation(
            shapeshifter_transformation_struct);
    ASSERT_NE(shapeshifter_transformation, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(shapeshifter_transformation) % alignof(yli::ontology::ShapeshifterTransformation), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_scene(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 3); // Default `Camera`, `pipeline`, `material`.

    // `Entity` member functions of `Pipeline`.
    ASSERT_EQ(pipeline->get_scene(), scene);
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 0);

    // `Entity` member functions of `Material`.
    ASSERT_EQ(material->get_scene(), scene);
    ASSERT_EQ(material->get_number_of_non_variable_children(), 0);

    // `Material` member functions.
    ASSERT_EQ(material->get_number_of_apprentices(), 0);

    // `Entity` member functions.
    ASSERT_EQ(shapeshifter_transformation->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(shapeshifter_transformation->get_type(), "yli::ontology::ShapeshifterTransformation*");
    ASSERT_TRUE(shapeshifter_transformation->get_can_be_erased());
    ASSERT_EQ(shapeshifter_transformation->get_parent(), nullptr);
    ASSERT_EQ(shapeshifter_transformation->get_number_of_non_variable_children(), 0);
}

TEST(shapeshifter_form_must_be_initialized_appropriately, headless)
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

    yli::ontology::ShapeshifterTransformationStruct shapeshifter_transformation_struct(material);
    yli::ontology::ShapeshifterTransformation* const shapeshifter_transformation = application.get_generic_entity_factory().create_shapeshifter_transformation(
            shapeshifter_transformation_struct);

    yli::ontology::ShapeshifterFormStruct shapeshifter_form_struct;
    shapeshifter_form_struct.shapeshifter_transformation = shapeshifter_transformation;
    yli::ontology::ShapeshifterForm* const shapeshifter_form = application.get_generic_entity_factory().create_shapeshifter_form(
            shapeshifter_form_struct);
    ASSERT_NE(shapeshifter_form, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(shapeshifter_form) % alignof(yli::ontology::ShapeshifterForm), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_scene(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 3); // Default `Camera`, `pipeline`, `material`.

    // `Entity` member functions of `Pipeline`.
    ASSERT_EQ(pipeline->get_scene(), scene);
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 0);

    // `Entity` member functions of `Material`.
    ASSERT_EQ(material->get_scene(), scene);
    ASSERT_EQ(material->get_number_of_non_variable_children(), 1);

    // `Material` member functions.
    ASSERT_EQ(material->get_number_of_apprentices(), 0);

    // `Entity` member functions of `ShapeshifterTransformation`.
    ASSERT_EQ(shapeshifter_transformation->get_scene(), scene);
    ASSERT_EQ(shapeshifter_transformation->get_number_of_non_variable_children(), 1);

    // `Entity` member functions.
    ASSERT_EQ(shapeshifter_form->get_childID(), 0);
    ASSERT_EQ(shapeshifter_form->get_type(), "yli::ontology::ShapeshifterForm*");
    ASSERT_FALSE(shapeshifter_form->get_can_be_erased());
    ASSERT_EQ(shapeshifter_form->get_scene(), scene);
    ASSERT_EQ(shapeshifter_form->get_parent(), shapeshifter_transformation);
    ASSERT_EQ(shapeshifter_form->get_number_of_non_variable_children(), 0);
}

TEST(shapeshifter_sequence_must_be_initialized_appropriately, headless)
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

    yli::ontology::ShapeshifterTransformationStruct shapeshifter_transformation_struct(material);
    yli::ontology::ShapeshifterTransformation* const shapeshifter_transformation = application.get_generic_entity_factory().create_shapeshifter_transformation(
            shapeshifter_transformation_struct);

    yli::ontology::ShapeshifterSequenceStruct shapeshifter_sequence_struct;
    shapeshifter_sequence_struct.parent = shapeshifter_transformation;
    yli::ontology::ShapeshifterSequence* const shapeshifter_sequence = application.get_generic_entity_factory().create_shapeshifter_sequence(
            shapeshifter_sequence_struct);
    ASSERT_NE(shapeshifter_sequence, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(shapeshifter_sequence) % alignof(yli::ontology::ShapeshifterSequence), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_scene(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 3); // Default `Camera`, `pipeline`, `material`.

    // `Entity` member functions of `Pipeline`.
    ASSERT_EQ(pipeline->get_scene(), scene);
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 0);

    // `Entity` member functions of `Material`.
    ASSERT_EQ(material->get_scene(), scene);
    ASSERT_EQ(material->get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `ShapeshifterTransformation`.
    ASSERT_EQ(shapeshifter_transformation->get_scene(), scene);
    ASSERT_EQ(shapeshifter_transformation->get_number_of_non_variable_children(), 1);

    // `Entity` member functions.
    ASSERT_EQ(shapeshifter_sequence->get_childID(), 0);
    ASSERT_EQ(shapeshifter_sequence->get_type(), "yli::ontology::ShapeshifterSequence*");
    ASSERT_TRUE(shapeshifter_sequence->get_can_be_erased());
    ASSERT_EQ(shapeshifter_sequence->get_scene(), scene);
    ASSERT_EQ(shapeshifter_sequence->get_parent(), shapeshifter_transformation);
    ASSERT_EQ(shapeshifter_sequence->get_number_of_non_variable_children(), 0);
}

TEST(shapeshifter_form_and_sequence_must_be_initialized_appropriately, headless)
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

    yli::ontology::ShapeshifterTransformationStruct shapeshifter_transformation_struct(material);
    yli::ontology::ShapeshifterTransformation* const shapeshifter_transformation = application.get_generic_entity_factory().create_shapeshifter_transformation(
            shapeshifter_transformation_struct);

    yli::ontology::ShapeshifterFormStruct shapeshifter_form_struct;
    shapeshifter_form_struct.shapeshifter_transformation = shapeshifter_transformation;
    yli::ontology::ShapeshifterForm* const shapeshifter_form = application.get_generic_entity_factory().create_shapeshifter_form(
            shapeshifter_form_struct);

    yli::ontology::ShapeshifterSequenceStruct shapeshifter_sequence_struct;
    shapeshifter_sequence_struct.parent = shapeshifter_transformation;
    yli::ontology::ShapeshifterSequence* const shapeshifter_sequence = application.get_generic_entity_factory().create_shapeshifter_sequence(
            shapeshifter_sequence_struct);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_scene(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 3); // Default `Camera`, `pipeline`, `material`.

    // `Entity` member functions of `Pipeline`.
    ASSERT_EQ(pipeline->get_scene(), scene);
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 0);

    // `Entity` member functions of `Material`.
    ASSERT_EQ(material->get_scene(), scene);
    ASSERT_EQ(material->get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `ShapeshifterTransformation`.
    ASSERT_EQ(shapeshifter_transformation->get_scene(), scene);
    ASSERT_EQ(shapeshifter_transformation->get_number_of_non_variable_children(), 2);

    // `Entity` member functions.
    ASSERT_EQ(shapeshifter_form->get_childID(), 0);
    ASSERT_EQ(shapeshifter_form->get_type(), "yli::ontology::ShapeshifterForm*");
    ASSERT_FALSE(shapeshifter_form->get_can_be_erased());
    ASSERT_EQ(shapeshifter_form->get_scene(), scene);
    ASSERT_EQ(shapeshifter_form->get_parent(), shapeshifter_transformation);
    ASSERT_EQ(shapeshifter_form->get_number_of_non_variable_children(), 0);

    // `Entity` member functions.
    ASSERT_EQ(shapeshifter_sequence->get_childID(), 0);
    ASSERT_EQ(shapeshifter_sequence->get_type(), "yli::ontology::ShapeshifterSequence*");
    ASSERT_TRUE(shapeshifter_sequence->get_can_be_erased());
    ASSERT_EQ(shapeshifter_sequence->get_scene(), scene);
    ASSERT_EQ(shapeshifter_sequence->get_parent(), shapeshifter_transformation);
    ASSERT_EQ(shapeshifter_sequence->get_number_of_non_variable_children(), 0);
}

TEST(shapeshifter_object_must_be_initialized_appropriately, headless)
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

    yli::ontology::ShapeshifterTransformationStruct shapeshifter_transformation_struct(material);
    yli::ontology::ShapeshifterTransformation* const shapeshifter_transformation = application.get_generic_entity_factory().create_shapeshifter_transformation(
            shapeshifter_transformation_struct);

    yli::ontology::ShapeshifterFormStruct shapeshifter_form_struct;
    shapeshifter_form_struct.shapeshifter_transformation = shapeshifter_transformation;
    yli::ontology::ShapeshifterForm* const shapeshifter_form = application.get_generic_entity_factory().create_shapeshifter_form(
            shapeshifter_form_struct);

    yli::ontology::ShapeshifterSequenceStruct shapeshifter_sequence_struct;
    shapeshifter_sequence_struct.parent = shapeshifter_transformation;
    yli::ontology::ShapeshifterSequence* const shapeshifter_sequence = application.get_generic_entity_factory().create_shapeshifter_sequence(
            shapeshifter_sequence_struct);

    yli::ontology::ObjectStruct object_struct(scene);
    object_struct.mesh_master = shapeshifter_sequence;
    yli::ontology::Object* const object = application.get_generic_entity_factory().create_object(
            object_struct);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_scene(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 4); // Default `Camera`, `pipeline`, `material`, `object`.

    // `Entity` member functions of `Pipeline`.
    ASSERT_EQ(pipeline->get_scene(), scene);
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 0);

    // `Entity` member functions of `Material`.
    ASSERT_EQ(material->get_scene(), scene);
    ASSERT_EQ(material->get_number_of_non_variable_children(), 1); // `shapeshifter_transformation`.

    // `Entity` member functions of `ShapeshifterTransformation`.
    ASSERT_EQ(shapeshifter_transformation->get_scene(), scene);
    ASSERT_EQ(shapeshifter_transformation->get_number_of_non_variable_children(), 2);

    // `Entity` member functions of `ShapeshifterForm`.
    ASSERT_EQ(shapeshifter_form->get_scene(), scene);
    ASSERT_EQ(shapeshifter_form->get_number_of_non_variable_children(), 0);

    // `Entity` member functions of `ShapeshifterSequence`.
    ASSERT_EQ(shapeshifter_sequence->get_scene(), scene);
    ASSERT_EQ(shapeshifter_sequence->get_number_of_non_variable_children(), 0);

    // `Material` member functions.
    ASSERT_EQ(material->get_number_of_apprentices(), 0);

    ASSERT_EQ(object->apprentice_of_mesh.get_master(), shapeshifter_sequence);
    ASSERT_EQ(object->apprentice_of_mesh.get_apprenticeID(), 0);

    // `Entity` member functions.
    ASSERT_EQ(object->get_childID(), 0);
    ASSERT_EQ(object->get_type(), "yli::ontology::Object*");
    ASSERT_TRUE(object->get_can_be_erased());
    ASSERT_EQ(object->get_scene(), scene);
    ASSERT_EQ(object->get_parent(), scene);
    ASSERT_EQ(object->get_number_of_non_variable_children(), 0);
}
