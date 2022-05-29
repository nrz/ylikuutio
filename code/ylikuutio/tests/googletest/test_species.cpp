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
#include "code/ylikuutio/ontology/ecosystem.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/shader.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/universe_struct.hpp"
#include "code/ylikuutio/ontology/ecosystem_struct.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/shader_struct.hpp"
#include "code/ylikuutio/ontology/material_struct.hpp"
#include "code/ylikuutio/ontology/model_struct.hpp"
#include "code/ylikuutio/ontology/object_struct.hpp"
#include "code/ylikuutio/render/graphics_api_backend.hpp"

TEST(species_must_be_initialized_and_must_bind_to_ecosystem_appropriately, headless_shader_and_material_are_children_of_an_ecosystem)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = new yli::ontology::Ecosystem(
            *universe,
            ecosystem_struct,
            &universe->parent_of_ecosystems);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = ecosystem;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(*universe, shader_struct, &ecosystem->parent_of_shaders);

    yli::ontology::MaterialStruct material_struct;
    material_struct.parent = ecosystem;
    material_struct.shader = shader;
    yli::ontology::Material* const material = new yli::ontology::Material(
            *universe,
            material_struct,
            &ecosystem->parent_of_materials, &shader->master_of_materials);

    yli::ontology::ModelStruct model_struct;
    model_struct.shader = shader;
    model_struct.material = material;
    yli::ontology::Species* const species = new yli::ontology::Species(
            *universe,
            model_struct,
            &ecosystem->parent_of_species,
            &material->master_of_species);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 1);  // `ecosystem`.

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 3); // `shader`, `material`, `species`.

    // `Entity` member functions of `Shader`.
    ASSERT_EQ(shader->get_number_of_non_variable_children(), 0);

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
    ASSERT_EQ(&(species->get_universe()), universe);
    ASSERT_EQ(species->get_scene(), nullptr);
    ASSERT_EQ(species->get_parent(), ecosystem);
    ASSERT_EQ(species->get_number_of_non_variable_children(), 0);
}

TEST(species_must_be_initialized_and_must_bind_to_ecosystem_appropriately, headless_shader_and_material_are_children_of_scene)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(*universe, shader_struct, &scene->parent_of_shaders);

    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = new yli::ontology::Ecosystem(
            *universe,
            ecosystem_struct,
            &universe->parent_of_ecosystems);

    yli::ontology::MaterialStruct material_struct;
    material_struct.parent = scene;
    material_struct.shader = shader;
    yli::ontology::Material* const material = new yli::ontology::Material(
            *universe,
            material_struct,
            &scene->parent_of_materials, &shader->master_of_materials);

    yli::ontology::ModelStruct model_struct;
    model_struct.shader = shader;
    model_struct.material = material;
    yli::ontology::Species* const species = new yli::ontology::Species(
            *universe,
            model_struct,
            &ecosystem->parent_of_species,
            &material->master_of_species);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 2); // `ecosystem`, `scene`.

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 1); // `species`.

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 3); // Default `Camera`, `shader`, `material`.

    // `Entity` member functions of `Shader`.
    ASSERT_EQ(shader->get_number_of_non_variable_children(), 0);

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
    ASSERT_EQ(&(species->get_universe()), universe);
    ASSERT_EQ(species->get_scene(), nullptr);
    ASSERT_EQ(species->get_parent(), ecosystem);
    ASSERT_EQ(species->get_number_of_non_variable_children(), 0);
}

TEST(species_must_be_initialized_appropriately, headless)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(*universe, shader_struct, &scene->parent_of_shaders);

    yli::ontology::MaterialStruct material_struct;
    material_struct.parent = scene;
    material_struct.shader = shader;
    yli::ontology::Material* const material = new yli::ontology::Material(
            *universe,
            material_struct,
            &scene->parent_of_materials, &shader->master_of_materials);

    yli::ontology::ModelStruct model_struct;
    model_struct.scene = scene;
    model_struct.shader = shader;
    model_struct.material = material;
    yli::ontology::Species* const species = new yli::ontology::Species(
            *universe,
            model_struct,
            &scene->parent_of_species,
            &material->master_of_species);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 4); // Default `Camera`, `shader`, `material`, `species`.

    // `Entity` member functions of `Shader`.
    ASSERT_EQ(shader->get_number_of_non_variable_children(), 0);

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
    ASSERT_EQ(&(species->get_universe()), universe);
    ASSERT_EQ(species->get_scene(), scene);
    ASSERT_EQ(species->get_parent(), scene);
    ASSERT_EQ(species->get_number_of_non_variable_children(), 0);
}

TEST(species_must_bind_to_ecosystem_appropriately, ecosystem)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem1 = new yli::ontology::Ecosystem(
            *universe,
            ecosystem_struct,
            &universe->parent_of_ecosystems);

    yli::ontology::ModelStruct model_struct;
    yli::ontology::Species* const species = new yli::ontology::Species(
            *universe,
            model_struct,
            &ecosystem1->parent_of_species,
            nullptr);
    ASSERT_EQ(species->get_scene(), nullptr);
    ASSERT_EQ(species->get_parent(), ecosystem1);
    ASSERT_EQ(ecosystem1->get_number_of_non_variable_children(), 1); // `species`.

    yli::ontology::Ecosystem* const ecosystem2 = new yli::ontology::Ecosystem(
            *universe,
            ecosystem_struct,
            &universe->parent_of_ecosystems);

    ASSERT_EQ(species->get_scene(), nullptr);
    ASSERT_EQ(species->get_parent(), ecosystem1);
    ASSERT_EQ(ecosystem2->get_number_of_non_variable_children(), 0);

    yli::ontology::Species::bind_to_new_ecosystem_parent(*species, *ecosystem2);
    ASSERT_EQ(species->get_scene(), nullptr);
    ASSERT_EQ(species->get_parent(), ecosystem2);
    ASSERT_EQ(ecosystem1->get_number_of_non_variable_children(), 0);
    ASSERT_EQ(ecosystem2->get_number_of_non_variable_children(), 1);
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 2); // `ecosystem1`, `ecosystem2`.

    yli::ontology::Species::bind_to_new_ecosystem_parent(*species, *ecosystem1);
    ASSERT_EQ(species->get_scene(), nullptr);
    ASSERT_EQ(species->get_parent(), ecosystem1);
    ASSERT_EQ(ecosystem1->get_number_of_non_variable_children(), 1);
    ASSERT_EQ(ecosystem2->get_number_of_non_variable_children(), 0);
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 2); // `ecosystem1`, `ecosystem2`.
}

TEST(species_must_bind_to_scene_appropriately, scenes_no_shaders_no_materials)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::SceneStruct scene_struct1;
    yli::ontology::Scene* const scene1 = new yli::ontology::Scene(
            *universe,
            scene_struct1,
            &universe->parent_of_scenes);

    yli::ontology::ModelStruct model_struct;
    model_struct.scene = scene1;
    yli::ontology::Species* const species = new yli::ontology::Species(
            *universe,
            model_struct,
            &scene1->parent_of_species,
            nullptr);
    ASSERT_EQ(species->get_scene(), scene1);
    ASSERT_EQ(species->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 2); // Default `Camera`, `species`.

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene2 = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);
    ASSERT_EQ(species->get_scene(), scene1);
    ASSERT_EQ(species->get_parent(), scene1);
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 1); // Default `Camera`.

    yli::ontology::Species::bind_to_new_scene_parent(*species, *scene2);
    ASSERT_EQ(species->get_scene(), scene2);
    ASSERT_EQ(species->get_parent(), scene2);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 1); // Default `Camera`.
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 2); // Default `Camera`, `species`.
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 2);

    yli::ontology::Species::bind_to_new_scene_parent(*species, *scene1);
    ASSERT_EQ(species->get_scene(), scene1);
    ASSERT_EQ(species->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 2); // Default `Camera`, `species`.
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 1); // Default `Camera`.
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 2);
}

TEST(species_must_bind_to_ecosystem_appropriately_after_binding_to_scene, ecosystem_scene)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);

    yli::ontology::ModelStruct model_struct;
    model_struct.scene = scene;
    yli::ontology::Species* const species = new yli::ontology::Species(
            *universe,
            model_struct,
            &scene->parent_of_species,
            nullptr);
    ASSERT_EQ(species->get_scene(), scene);
    ASSERT_EQ(species->get_parent(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 2); // Default `Camera`, `species`.

    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = new yli::ontology::Ecosystem(
            *universe,
            ecosystem_struct,
            &universe->parent_of_ecosystems);
    ASSERT_EQ(species->get_scene(), scene);
    ASSERT_EQ(species->get_parent(), scene);
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 0);

    yli::ontology::Species::bind_to_new_ecosystem_parent(*species, *ecosystem);
    ASSERT_EQ(species->get_scene(), nullptr);
    ASSERT_EQ(species->get_parent(), ecosystem);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 1);     // Default `Camera`.
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 1); // `species`.
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 2);  // `ecosystem`, `scene`.

    yli::ontology::Species::bind_to_new_scene_parent(*species, *scene);
    ASSERT_EQ(species->get_scene(), scene);
    ASSERT_EQ(species->get_parent(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 2);     // Default `Camera`, `species`.
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 0);
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 2);  // `ecosystem`, `scene`.
}

TEST(species_must_bind_to_scene_appropriately_after_binding_to_ecosystem, scene_ecosystem)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = new yli::ontology::Ecosystem(
            *universe,
            ecosystem_struct,
            &universe->parent_of_ecosystems);

    yli::ontology::ModelStruct model_struct;
    yli::ontology::Species* const species = new yli::ontology::Species(
            *universe,
            model_struct,
            &ecosystem->parent_of_species,
            nullptr);
    ASSERT_EQ(species->get_scene(), nullptr);
    ASSERT_EQ(species->get_parent(), ecosystem);
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 1); // `species`.

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);
    ASSERT_EQ(species->get_scene(), nullptr);
    ASSERT_EQ(species->get_parent(), ecosystem);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 1); // Default `Camera`.

    yli::ontology::Species::bind_to_new_scene_parent(*species, *scene);
    ASSERT_EQ(species->get_scene(), scene);
    ASSERT_EQ(species->get_parent(), scene);
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 0);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 2);     // Default `Camera`, `species`.
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 2);  // `Ecosystem`, `Scene`.

    yli::ontology::Species::bind_to_new_ecosystem_parent(*species, *ecosystem);
    ASSERT_EQ(species->get_scene(), nullptr);
    ASSERT_EQ(species->get_parent(), ecosystem);
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 1); // `species`.
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 1);     // Default `Camera`.
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 2);  // `Ecosystem`, `Scene`.
}

TEST(species_must_maintain_the_local_name_after_binding_to_a_new_parent, headless_universe_species_with_only_local_name)
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

    yli::ontology::ModelStruct model_struct;
    model_struct.scene = scene1;
    yli::ontology::Species* const species = new yli::ontology::Species(
            *universe,
            model_struct,
            &scene1->parent_of_species,
            nullptr);

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

    yli::ontology::ModelStruct model_struct;
    model_struct.scene = scene1;
    yli::ontology::Species* const species = new yli::ontology::Species(
            *universe,
            model_struct,
            &scene1->parent_of_species,
            nullptr);

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

    yli::ontology::ModelStruct model_struct1;
    model_struct1.scene = scene1;
    yli::ontology::Species* const species1 = new yli::ontology::Species(
            *universe,
            model_struct1,
            &scene1->parent_of_species,
            nullptr);

    yli::ontology::ModelStruct model_struct2;
    model_struct2.scene = scene2;
    yli::ontology::Species* const species2 = new yli::ontology::Species(
            *universe,
            model_struct2,
            &scene2->parent_of_species,
            nullptr);

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

    yli::ontology::ModelStruct model_struct1;
    model_struct1.scene = scene1;
    yli::ontology::Species* const species1 = new yli::ontology::Species(
            *universe,
            model_struct1,
            &scene1->parent_of_species,
            nullptr);

    yli::ontology::ModelStruct model_struct2;
    model_struct2.scene = scene2;
    yli::ontology::Species* const species2 = new yli::ontology::Species(
            *universe,
            model_struct2,
            &scene2->parent_of_species,
            nullptr);

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
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::SceneStruct scene_struct1;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(
            *universe,
            scene_struct1,
            &universe->parent_of_scenes);

    yli::ontology::ModelStruct model_struct;
    model_struct.scene = scene;
    yli::ontology::Species* const species = new yli::ontology::Species(
            *universe,
            model_struct,
            &scene->parent_of_species,
            nullptr);

    yli::ontology::ObjectStruct object_struct(scene);
    yli::ontology::Object* const object = new yli::ontology::Object(
            *universe,
            object_struct,
            &scene->parent_of_objects,
            &species->master_of_objects,
            nullptr);

    ASSERT_EQ(species->get_number_of_apprentices(), 1);

    yli::ontology::Species::bind_to_new_scene_parent(*species, *scene);
    ASSERT_EQ(species->get_number_of_apprentices(), 1);
}

TEST(species_must_unbind_all_its_apprentice_modules_when_binding_to_a_different_scene, headless_universe_object_apprentice)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::SceneStruct scene_struct1;
    yli::ontology::Scene* const scene1 = new yli::ontology::Scene(
            *universe,
            scene_struct1,
            &universe->parent_of_scenes);

    yli::ontology::ModelStruct model_struct;
    model_struct.scene = scene1;
    yli::ontology::Species* const species = new yli::ontology::Species(
            *universe,
            model_struct,
            &scene1->parent_of_species,
            nullptr);

    yli::ontology::ObjectStruct object_struct(scene1);
    yli::ontology::Object* const object = new yli::ontology::Object(
            *universe,
            object_struct,
            &scene1->parent_of_objects,
            &species->master_of_objects,
            nullptr);

    ASSERT_EQ(species->get_number_of_apprentices(), 1);

    yli::ontology::Scene* const scene2 = new yli::ontology::Scene(
            *universe,
            scene_struct1,
            &universe->parent_of_scenes);

    yli::ontology::Species::bind_to_new_scene_parent(*species, *scene2);
    ASSERT_EQ(species->get_number_of_apprentices(), 0);
}
