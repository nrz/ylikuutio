// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/pipeline.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/shapeshifter_transformation.hpp"
#include "code/ylikuutio/ontology/shapeshifter_sequence.hpp"
#include "code/ylikuutio/ontology/shapeshifter_form.hpp"
#include "code/ylikuutio/ontology/universe_struct.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/pipeline_struct.hpp"
#include "code/ylikuutio/ontology/material_struct.hpp"
#include "code/ylikuutio/ontology/model_struct.hpp"
#include "code/ylikuutio/ontology/object_struct.hpp"
#include "code/ylikuutio/ontology/shapeshifter_sequence_struct.hpp"
#include "code/ylikuutio/render/graphics_api_backend.hpp"

TEST(shapeshifter_transformation_must_be_initialized_appropriately, headless)
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

    yli::ontology::ModelStruct shapeshifter_transformation_struct;
    shapeshifter_transformation_struct.parent = scene;
    shapeshifter_transformation_struct.pipeline = pipeline;
    shapeshifter_transformation_struct.material = material;
    yli::ontology::ShapeshifterTransformation* const shapeshifter_transformation = new yli::ontology::ShapeshifterTransformation(
            *universe,
            shapeshifter_transformation_struct,
            &material->parent_of_shapeshifter_transformations);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_scene(), nullptr);
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 1);

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

    // `Entity` member functions.
    ASSERT_EQ(shapeshifter_transformation->get_childID(), 0);
    ASSERT_EQ(shapeshifter_transformation->get_type(), "yli::ontology::ShapeshifterTransformation*");
    ASSERT_TRUE(shapeshifter_transformation->get_can_be_erased());
    ASSERT_EQ(&(shapeshifter_transformation->get_universe()), universe);
    ASSERT_EQ(shapeshifter_transformation->get_scene(), scene);
    ASSERT_EQ(shapeshifter_transformation->get_parent(), material);
    ASSERT_EQ(shapeshifter_transformation->get_number_of_non_variable_children(), 0);
}

TEST(shapeshifter_form_must_be_initialized_appropriately, headless)
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

    yli::ontology::ModelStruct shapeshifter_transformation_struct;
    shapeshifter_transformation_struct.parent = scene;
    shapeshifter_transformation_struct.pipeline = pipeline;
    shapeshifter_transformation_struct.material = material;
    yli::ontology::ShapeshifterTransformation* const shapeshifter_transformation = new yli::ontology::ShapeshifterTransformation(
            *universe,
            shapeshifter_transformation_struct,
            &material->parent_of_shapeshifter_transformations);

    yli::ontology::ModelStruct shapeshifter_form_struct;
    shapeshifter_form_struct.shapeshifter_transformation = shapeshifter_transformation;
    yli::ontology::ShapeshifterForm* const shapeshifter_form = new yli::ontology::ShapeshifterForm(
            *universe,
            shapeshifter_form_struct,
            &shapeshifter_transformation->parent_of_shapeshifter_forms);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_scene(), nullptr);
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 1);

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
    ASSERT_EQ(&(shapeshifter_form->get_universe()), universe);
    ASSERT_EQ(shapeshifter_form->get_scene(), scene);
    ASSERT_EQ(shapeshifter_form->get_parent(), shapeshifter_transformation);
    ASSERT_EQ(shapeshifter_form->get_number_of_non_variable_children(), 0);
}

TEST(shapeshifter_sequence_must_be_initialized_appropriately, headless)
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

    yli::ontology::ModelStruct shapeshifter_transformation_struct;
    shapeshifter_transformation_struct.parent = scene;
    shapeshifter_transformation_struct.pipeline = pipeline;
    shapeshifter_transformation_struct.material = material;
    yli::ontology::ShapeshifterTransformation* const shapeshifter_transformation = new yli::ontology::ShapeshifterTransformation(
            *universe,
            shapeshifter_transformation_struct,
            &material->parent_of_shapeshifter_transformations);

    yli::ontology::ShapeshifterSequenceStruct shapeshifter_sequence_struct;
    shapeshifter_sequence_struct.parent = shapeshifter_transformation;
    yli::ontology::ShapeshifterSequence* const shapeshifter_sequence = new yli::ontology::ShapeshifterSequence(
            *universe,
            shapeshifter_sequence_struct,
            &shapeshifter_transformation->parent_of_shapeshifter_sequences);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_scene(), nullptr);
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 1);

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
    ASSERT_EQ(&(shapeshifter_sequence->get_universe()), universe);
    ASSERT_EQ(shapeshifter_sequence->get_scene(), scene);
    ASSERT_EQ(shapeshifter_sequence->get_parent(), shapeshifter_transformation);
    ASSERT_EQ(shapeshifter_sequence->get_number_of_non_variable_children(), 0);
}

TEST(shapeshifter_form_and_sequence_must_be_initialized_appropriately, headless)
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

    yli::ontology::ModelStruct shapeshifter_transformation_struct;
    shapeshifter_transformation_struct.parent = scene;
    shapeshifter_transformation_struct.pipeline = pipeline;
    shapeshifter_transformation_struct.material = material;
    yli::ontology::ShapeshifterTransformation* const shapeshifter_transformation = new yli::ontology::ShapeshifterTransformation(
            *universe,
            shapeshifter_transformation_struct,
            &material->parent_of_shapeshifter_transformations);

    yli::ontology::ModelStruct shapeshifter_form_struct;
    shapeshifter_form_struct.shapeshifter_transformation = shapeshifter_transformation;
    yli::ontology::ShapeshifterForm* const shapeshifter_form = new yli::ontology::ShapeshifterForm(
            *universe,
            shapeshifter_form_struct,
            &shapeshifter_transformation->parent_of_shapeshifter_forms);

    yli::ontology::ShapeshifterSequenceStruct shapeshifter_sequence_struct;
    shapeshifter_sequence_struct.parent = shapeshifter_transformation;
    yli::ontology::ShapeshifterSequence* const shapeshifter_sequence = new yli::ontology::ShapeshifterSequence(
            *universe,
            shapeshifter_sequence_struct,
            &shapeshifter_transformation->parent_of_shapeshifter_sequences);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_scene(), nullptr);
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 1);

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
    ASSERT_EQ(&(shapeshifter_form->get_universe()), universe);
    ASSERT_EQ(shapeshifter_form->get_scene(), scene);
    ASSERT_EQ(shapeshifter_form->get_parent(), shapeshifter_transformation);
    ASSERT_EQ(shapeshifter_form->get_number_of_non_variable_children(), 0);

    // `Entity` member functions.
    ASSERT_EQ(shapeshifter_sequence->get_childID(), 0);
    ASSERT_EQ(shapeshifter_sequence->get_type(), "yli::ontology::ShapeshifterSequence*");
    ASSERT_TRUE(shapeshifter_sequence->get_can_be_erased());
    ASSERT_EQ(&(shapeshifter_sequence->get_universe()), universe);
    ASSERT_EQ(shapeshifter_sequence->get_scene(), scene);
    ASSERT_EQ(shapeshifter_sequence->get_parent(), shapeshifter_transformation);
    ASSERT_EQ(shapeshifter_sequence->get_number_of_non_variable_children(), 0);
}

TEST(shapeshifter_object_must_be_initialized_appropriately, headless)
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

    yli::ontology::ModelStruct shapeshifter_transformation_struct;
    shapeshifter_transformation_struct.parent = scene;
    shapeshifter_transformation_struct.pipeline = pipeline;
    shapeshifter_transformation_struct.material = material;
    yli::ontology::ShapeshifterTransformation* const shapeshifter_transformation = new yli::ontology::ShapeshifterTransformation(
            *universe,
            shapeshifter_transformation_struct,
            &material->parent_of_shapeshifter_transformations);

    yli::ontology::ModelStruct shapeshifter_form_struct;
    shapeshifter_form_struct.shapeshifter_transformation = shapeshifter_transformation;
    yli::ontology::ShapeshifterForm* const shapeshifter_form = new yli::ontology::ShapeshifterForm(
            *universe,
            shapeshifter_form_struct,
            &shapeshifter_transformation->parent_of_shapeshifter_forms);

    yli::ontology::ShapeshifterSequenceStruct shapeshifter_sequence_struct;
    shapeshifter_sequence_struct.parent = shapeshifter_transformation;
    yli::ontology::ShapeshifterSequence* const shapeshifter_sequence = new yli::ontology::ShapeshifterSequence(
            *universe,
            shapeshifter_sequence_struct,
            &shapeshifter_transformation->parent_of_shapeshifter_sequences);

    yli::ontology::ObjectStruct object_struct(scene);
    object_struct.mesh_master = shapeshifter_sequence;
    yli::ontology::Object* const object = new yli::ontology::Object(
            *universe,
            object_struct,
            &scene->parent_of_objects,
            &shapeshifter_sequence->master_of_objects,
            nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_scene(), nullptr);
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 1);

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
    ASSERT_EQ(&(object->get_universe()), universe);
    ASSERT_EQ(object->get_scene(), scene);
    ASSERT_EQ(object->get_parent(), scene);
    ASSERT_EQ(object->get_number_of_non_variable_children(), 0);
}
