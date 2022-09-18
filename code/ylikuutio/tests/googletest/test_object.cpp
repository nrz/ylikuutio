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
#include "code/ylikuutio/ontology/brain.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/pipeline.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/universe_struct.hpp"
#include "code/ylikuutio/ontology/brain_struct.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/pipeline_struct.hpp"
#include "code/ylikuutio/ontology/material_struct.hpp"
#include "code/ylikuutio/ontology/model_struct.hpp"
#include "code/ylikuutio/ontology/object_struct.hpp"
#include "code/ylikuutio/render/graphics_api_backend.hpp"

TEST(object_must_be_initialized_appropriately, headless)
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

    yli::ontology::ModelStruct model_struct;
    model_struct.parent = scene;
    model_struct.pipeline = pipeline;
    model_struct.material = material;
    yli::ontology::Species* const species = new yli::ontology::Species(
            *universe,
            model_struct,
            &scene->parent_of_species,
            &material->master_of_species);

    yli::ontology::ObjectStruct object_struct(scene);
    yli::ontology::Object* const object = new yli::ontology::Object(
            *universe,
            object_struct,
            &scene->parent_of_objects,
            &species->master_of_objects,
            nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_scene(), nullptr);
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_scene(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 5); // Default `Camera`, `pipeline`, `material`, `species`, `object`.

    // `Entity` member functions of `Pipeline`.
    ASSERT_EQ(pipeline->get_scene(), scene);
    ASSERT_EQ(pipeline->get_number_of_non_variable_children(), 0);

    // `Entity` member functions of `Material`.
    ASSERT_EQ(material->get_scene(), scene);
    ASSERT_EQ(material->get_number_of_non_variable_children(), 0);

    // `Material` member functions.
    ASSERT_EQ(material->get_number_of_apprentices(), 1); // `species`.

    // `Entity` member functions of `Species`.
    ASSERT_EQ(species->get_scene(), scene);
    ASSERT_EQ(species->get_number_of_non_variable_children(), 0);

    ASSERT_EQ(object->apprentice_of_brain.get_master(), nullptr); // No `Brain`.
    ASSERT_EQ(object->apprentice_of_brain.get_apprenticeID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(object->apprentice_of_mesh.get_master(), species);
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

TEST(object_must_bind_to_scene_appropriately, scenes_no_pipelines_no_materials_no_species_no_shapeshifters_no_text_3ds)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::SceneStruct scene_struct1;
    yli::ontology::Scene* const scene1 = new yli::ontology::Scene(
            *universe,
            scene_struct1,
            &universe->parent_of_scenes);

    yli::ontology::ObjectStruct object_struct(scene1);
    yli::ontology::Object* const object = new yli::ontology::Object(
            *universe,
            object_struct,
            &scene1->parent_of_objects,
            nullptr,
            nullptr);
    ASSERT_EQ(object->get_scene(), scene1);
    ASSERT_EQ(object->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 2); // Default `Camera`, `species`.

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene2 = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);
    ASSERT_EQ(object->get_scene(), scene1);
    ASSERT_EQ(object->get_parent(), scene1);
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 1); // Default `Camera`.

    yli::ontology::Object::bind_to_new_scene_parent(*object, *scene2);
    ASSERT_EQ(object->get_scene(), scene2);
    ASSERT_EQ(object->get_parent(), scene2);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 1); // Default `Camera`.
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 2); // Default `Camera`, `object`.
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 2);

    yli::ontology::Object::bind_to_new_scene_parent(*object, *scene1);
    ASSERT_EQ(object->get_scene(), scene1);
    ASSERT_EQ(object->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 2); // Default `Camera`, `object`.
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 1); // Default `Camera`.
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 2);
}

TEST(object_must_bind_to_brain_appropriately, master_and_apprentice)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);

    yli::ontology::BrainStruct brain_struct;
    brain_struct.parent = scene;
    yli::ontology::Brain* const brain = new yli::ontology::Brain(
            *universe,
            brain_struct,
            &scene->parent_of_brains);

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

    yli::ontology::ModelStruct model_struct;
    model_struct.parent = scene;
    model_struct.pipeline = pipeline;
    model_struct.material = material;
    yli::ontology::Species* const species = new yli::ontology::Species(
            *universe,
            model_struct,
            &scene->parent_of_species,
            &material->master_of_species);

    yli::ontology::ObjectStruct object_struct(scene);
    object_struct.mesh_master = species;
    yli::ontology::Object* const object = new yli::ontology::Object(
            *universe,
            object_struct,
            &scene->parent_of_objects,
            &species->master_of_objects,
            nullptr);

    ASSERT_EQ(brain->get_number_of_apprentices(), 0);
    yli::ontology::Movable::bind_to_new_brain(*object, *brain);
    ASSERT_EQ(brain->get_number_of_apprentices(), 1);

    ASSERT_EQ(object->apprentice_of_brain.get_master(), brain);
    ASSERT_EQ(object->apprentice_of_brain.get_apprenticeID(), 0);
}

TEST(object_must_bind_to_species_appropriately, master_and_apprentice)
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

    yli::ontology::ModelStruct model_struct;
    model_struct.parent = scene;
    model_struct.pipeline = pipeline;
    model_struct.material = material;
    yli::ontology::Species* const species1 = new yli::ontology::Species(
            *universe,
            model_struct,
            &scene->parent_of_species,
            &material->master_of_species);

    yli::ontology::ObjectStruct object_struct(scene);
    object_struct.mesh_master = species1;
    yli::ontology::Object* const object = new yli::ontology::Object(
            *universe,
            object_struct,
            &scene->parent_of_objects,
            &species1->master_of_objects,
            nullptr);

    ASSERT_EQ(species1->get_number_of_apprentices(), 1);
    ASSERT_EQ(object->apprentice_of_mesh.get_master(), species1);
    ASSERT_EQ(object->apprentice_of_mesh.get_apprenticeID(), 0);

    yli::ontology::Species* const species2 = new yli::ontology::Species(
            *universe,
            model_struct,
            &scene->parent_of_species,
            &material->master_of_species);

    yli::ontology::Object::bind_to_new_species_master(*object, *species2);
    ASSERT_EQ(object->apprentice_of_mesh.get_master(), species2);
    ASSERT_EQ(object->apprentice_of_mesh.get_apprenticeID(), 0);
    ASSERT_EQ(species1->get_number_of_apprentices(), 0);
    ASSERT_EQ(species2->get_number_of_apprentices(), 1);

    yli::ontology::Object::bind_to_new_species_master(*object, *species1);
    ASSERT_EQ(object->apprentice_of_mesh.get_master(), species1);
    ASSERT_EQ(object->apprentice_of_mesh.get_apprenticeID(), 0);
    ASSERT_EQ(species1->get_number_of_apprentices(), 1);
    ASSERT_EQ(species2->get_number_of_apprentices(), 0);
}

TEST(object_must_maintain_the_local_name_after_binding_to_a_new_parent, headless_universe_object_with_only_local_name)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene1 = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);
    yli::ontology::Scene* const scene2 = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);

    yli::ontology::ObjectStruct object_struct(scene1);
    yli::ontology::Object* const object = new yli::ontology::Object(
            *universe,
            object_struct,
            &scene1->parent_of_objects,
            nullptr,
            nullptr);

    object->set_local_name("foo");
    yli::ontology::Object::bind_to_new_scene_parent(*object, *scene2);
    ASSERT_FALSE(scene1->has_child("foo"));
    ASSERT_TRUE(scene2->has_child("foo"));
    ASSERT_EQ(object->get_parent(), scene2);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 1); // Default `Camera`.
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 2); // Default `Camera`, `object`.

    yli::ontology::Object::bind_to_new_scene_parent(*object, *scene1);
    ASSERT_TRUE(scene1->has_child("foo"));
    ASSERT_FALSE(scene2->has_child("foo"));
    ASSERT_EQ(object->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 2); // Default `Camera`, `object`.
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 1); // Default `Camera`.
}

TEST(object_must_maintain_the_local_name_after_binding_to_a_new_parent, headless_universe_object_with_global_name_and_local_name)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene1 = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);
    yli::ontology::Scene* const scene2 = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);

    yli::ontology::ObjectStruct object_struct(scene1);
    yli::ontology::Object* const object = new yli::ontology::Object(
            *universe,
            object_struct,
            &scene1->parent_of_objects,
            nullptr,
            nullptr);

    object->set_global_name("foo");
    object->set_local_name("bar");
    yli::ontology::Object::bind_to_new_scene_parent(*object, *scene2);
    ASSERT_FALSE(scene1->has_child("foo"));
    ASSERT_FALSE(scene2->has_child("foo"));
    ASSERT_FALSE(scene1->has_child("bar"));
    ASSERT_TRUE(scene2->has_child("bar"));
    ASSERT_EQ(object->get_parent(), scene2);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 1); // Default `Camera`.
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 2) ;// Default `Camera`, `object`.

    yli::ontology::Object::bind_to_new_scene_parent(*object, *scene1);
    ASSERT_FALSE(scene1->has_child("foo"));
    ASSERT_FALSE(scene2->has_child("foo"));
    ASSERT_TRUE(scene1->has_child("bar"));
    ASSERT_FALSE(scene2->has_child("bar"));
    ASSERT_EQ(object->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 2); // Default `Camera`, `object`.
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 1); // Default `Camera`.
}

TEST(object_must_not_bind_to_a_new_parent_when_local_name_is_already_in_use, headless_universe_objects_with_only_local_name)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene1 = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);
    yli::ontology::Scene* const scene2 = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);

    yli::ontology::ObjectStruct object_struct1(scene1);
    yli::ontology::Object* const object1 = new yli::ontology::Object(
            *universe,
            object_struct1,
            &scene1->parent_of_objects,
            nullptr,
            nullptr);

    yli::ontology::ObjectStruct object_struct2(scene2);
    yli::ontology::Object* const object2 = new yli::ontology::Object(
            *universe,
            object_struct2,
            &scene2->parent_of_objects,
            nullptr,
            nullptr);

    object1->set_local_name("foo");
    object2->set_local_name("foo");
    yli::ontology::Object::bind_to_new_scene_parent(*object1, *scene2);
    ASSERT_EQ(object1->get_scene(), scene1);
    ASSERT_EQ(object1->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 2); // Default `Camera`, `object1`.
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 2); // Default `Camera`, `object2`.
    ASSERT_TRUE(scene1->has_child("foo"));
    ASSERT_TRUE(scene2->has_child("foo"));
}

TEST(object_must_not_bind_to_a_new_parent_when_local_name_is_already_in_use, headless_universe_objects_with_different_global_names_and_same_local_name)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene1 = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);
    yli::ontology::Scene* const scene2 = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);

    yli::ontology::ObjectStruct object_struct1(scene1);
    yli::ontology::Object* const object1 = new yli::ontology::Object(
            *universe,
            object_struct1,
            &scene1->parent_of_objects,
            nullptr,
            nullptr);

    yli::ontology::ObjectStruct object_struct2(scene2);
    yli::ontology::Object* const object2 = new yli::ontology::Object(
            *universe,
            object_struct2,
            &scene2->parent_of_objects,
            nullptr,
            nullptr);

    object1->set_global_name("foo");
    object2->set_global_name("bar");
    object1->set_local_name("baz");
    object2->set_local_name("baz");
    yli::ontology::Object::bind_to_new_scene_parent(*object1, *scene2);
    ASSERT_EQ(object1->get_scene(), scene1);
    ASSERT_EQ(object1->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 2); // Default `Camera`, `object1`.
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 2); // Default `Camera`, `object2`.
    ASSERT_FALSE(scene1->has_child("foo"));
    ASSERT_FALSE(scene2->has_child("foo"));
    ASSERT_FALSE(scene1->has_child("bar"));
    ASSERT_FALSE(scene2->has_child("bar"));
    ASSERT_TRUE(scene1->has_child("baz"));
    ASSERT_TRUE(scene2->has_child("baz"));
}

