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
#include "code/ylikuutio/ontology/symbiosis.hpp"
#include "code/ylikuutio/ontology/universe_struct.hpp"
#include "code/ylikuutio/ontology/ecosystem_struct.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/shader_struct.hpp"
#include "code/ylikuutio/ontology/material_struct.hpp"
#include "code/ylikuutio/ontology/model_struct.hpp"
#include "code/ylikuutio/render/graphics_api_backend.hpp"

TEST(shader_must_be_initialized_and_must_bind_to_ecosystem_appropriately, headless)
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

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem->get_scene(), nullptr);
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 1); // `shader`.

    // `Shader` member functions.
    ASSERT_EQ(shader->get_number_of_apprentices(), 0);

    // `Entity` member functions.
    ASSERT_EQ(shader->get_childID(), 0);
    ASSERT_EQ(shader->get_type(), "yli::ontology::Shader*");
    ASSERT_TRUE(shader->get_can_be_erased());
    ASSERT_EQ(&(shader->get_universe()), universe);
    ASSERT_EQ(shader->get_scene(), nullptr);
    ASSERT_EQ(shader->get_parent(), ecosystem);
    ASSERT_EQ(shader->get_number_of_non_variable_children(), 0);
}

TEST(shader_must_be_initialized_appropriately, headless)
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

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 1);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_scene(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 2); // Default `Camera`, `shader`.

    // `Shader` member functions.
    ASSERT_EQ(shader->get_number_of_apprentices(), 0);

    // `Entity` member functions.
    ASSERT_EQ(shader->get_childID(), 0);
    ASSERT_EQ(shader->get_type(), "yli::ontology::Shader*");
    ASSERT_TRUE(shader->get_can_be_erased());
    ASSERT_EQ(&(shader->get_universe()), universe);
    ASSERT_EQ(shader->get_scene(), scene);
    ASSERT_EQ(shader->get_parent(), scene);
    ASSERT_EQ(shader->get_number_of_non_variable_children(), 0);
}

TEST(shader_must_bind_to_ecosystem_appropriately, ecosystem)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem1 = new yli::ontology::Ecosystem(
            *universe,
            ecosystem_struct,
            &universe->parent_of_ecosystems);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = ecosystem1;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(*universe, shader_struct, &ecosystem1->parent_of_shaders);
    ASSERT_EQ(shader->get_scene(), nullptr);
    ASSERT_EQ(shader->get_parent(), ecosystem1);
    ASSERT_EQ(ecosystem1->get_number_of_non_variable_children(), 1);

    yli::ontology::Ecosystem* const ecosystem2 = new yli::ontology::Ecosystem(
            *universe,
            ecosystem_struct,
            &universe->parent_of_ecosystems);

    ASSERT_EQ(shader->get_scene(), nullptr);
    ASSERT_EQ(shader->get_parent(), ecosystem1);
    ASSERT_EQ(ecosystem2->get_number_of_non_variable_children(), 0);

    yli::ontology::Shader::bind_to_new_ecosystem_parent(*shader, *ecosystem2);
    ASSERT_EQ(shader->get_scene(), nullptr);
    ASSERT_EQ(shader->get_parent(), ecosystem2);
    ASSERT_EQ(ecosystem1->get_number_of_non_variable_children(), 0);
    ASSERT_EQ(ecosystem2->get_number_of_non_variable_children(), 1);
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 2); // `ecosystem1`, `ecosystem2`.

    yli::ontology::Shader::bind_to_new_ecosystem_parent(*shader, *ecosystem1);
    ASSERT_EQ(shader->get_scene(), nullptr);
    ASSERT_EQ(shader->get_parent(), ecosystem1);
    ASSERT_EQ(ecosystem1->get_number_of_non_variable_children(), 1);
    ASSERT_EQ(ecosystem2->get_number_of_non_variable_children(), 0);
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 2); // `ecosystem1`, `ecosystem2`.
}

TEST(shader_must_bind_to_scene_appropriately, scenes)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene1 = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene1;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(*universe, shader_struct, &scene1->parent_of_shaders);
    ASSERT_EQ(shader->get_scene(), scene1);
    ASSERT_EQ(shader->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 2);

    yli::ontology::Scene* const scene2 = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);
    ASSERT_EQ(shader->get_scene(), scene1);
    ASSERT_EQ(shader->get_parent(), scene1);
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 1);

    yli::ontology::Shader::bind_to_new_scene_parent(*shader, *scene2);
    ASSERT_EQ(shader->get_scene(), scene2);
    ASSERT_EQ(shader->get_parent(), scene2);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 1);
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 2);
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 2);

    yli::ontology::Shader::bind_to_new_scene_parent(*shader, *scene1);
    ASSERT_EQ(shader->get_scene(), scene1);
    ASSERT_EQ(shader->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 2);
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 1);
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 2);
}

TEST(shader_must_bind_to_ecosystem_appropriately_after_binding_to_scene, ecosystem_scene)
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
    ASSERT_EQ(shader->get_scene(), scene);
    ASSERT_EQ(shader->get_parent(), scene);
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 0);

    yli::ontology::Shader::bind_to_new_ecosystem_parent(*shader, *ecosystem);
    ASSERT_EQ(shader->get_scene(), nullptr);
    ASSERT_EQ(shader->get_parent(), ecosystem);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 1);     // Default `Camera`.
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 1); // `shader`.
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 2);  // `ecosystem`, `scene`.

    yli::ontology::Shader::bind_to_new_scene_parent(*shader, *scene);
    ASSERT_EQ(shader->get_scene(), scene);
    ASSERT_EQ(shader->get_parent(), scene);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 2);     // Default `Camera`, `shader`.
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 0);
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 2);  // `ecosystem`, `scene`.
}

TEST(shader_must_bind_to_scene_appropriately_after_binding_to_ecosystem, scene_ecosystem)
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

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);
    ASSERT_EQ(shader->get_scene(), nullptr);
    ASSERT_EQ(shader->get_parent(), ecosystem);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 1); // Default `Camera`.

    yli::ontology::Shader::bind_to_new_scene_parent(*shader, *scene);
    ASSERT_EQ(shader->get_scene(), scene);
    ASSERT_EQ(shader->get_parent(), scene);
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 0);
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 2);     // Default `Camera`, `shader`.
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 2);  // `Ecosystem`, `Scene`.

    yli::ontology::Shader::bind_to_new_ecosystem_parent(*shader, *ecosystem);
    ASSERT_EQ(shader->get_scene(), nullptr);
    ASSERT_EQ(shader->get_parent(), ecosystem);
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 1); // `shader`.
    ASSERT_EQ(scene->get_number_of_non_variable_children(), 1);     // Default `Camera`.
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 2);  // `Ecosystem`, `Scene`.
}

TEST(shader_must_be_given_a_global_name_appropriately, headless)
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
    ASSERT_EQ(shader->get_global_name(), "");
    ASSERT_EQ(shader->get_local_name(), "");

    shader->set_global_name("foo");
    ASSERT_EQ(shader->get_global_name(), "foo");
    ASSERT_EQ(shader->get_local_name(), "");
    ASSERT_TRUE(universe->has_child("foo"));
    ASSERT_FALSE(scene->has_child("foo"));
    ASSERT_EQ(universe->get_entity("foo"), shader);
    ASSERT_EQ(scene->get_entity("foo"), nullptr);
}

TEST(shader_must_be_given_a_local_name_appropriately, headless)
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
    ASSERT_EQ(shader->get_global_name(), "");
    ASSERT_EQ(shader->get_local_name(), "");

    shader->set_local_name("foo");
    ASSERT_EQ(shader->get_global_name(), "");
    ASSERT_EQ(shader->get_local_name(), "foo");
    ASSERT_FALSE(universe->has_child("foo"));
    ASSERT_TRUE(scene->has_child("foo"));
    ASSERT_EQ(universe->get_entity("foo"), nullptr);
    ASSERT_EQ(scene->get_entity("foo"), shader);
}

TEST(shader_must_be_given_a_global_name_appropriately_after_setting_a_global_name, headless)
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
    ASSERT_EQ(shader->get_global_name(), "");
    ASSERT_EQ(shader->get_local_name(), "");

    shader->set_global_name("foo");
    shader->set_global_name("bar");
    ASSERT_EQ(shader->get_global_name(), "bar");
    ASSERT_EQ(shader->get_local_name(), "");
    ASSERT_FALSE(universe->has_child("foo"));
    ASSERT_TRUE(universe->has_child("bar"));
    ASSERT_FALSE(scene->has_child("foo"));
    ASSERT_FALSE(scene->has_child("bar"));
    ASSERT_EQ(universe->get_entity("foo"), nullptr);
    ASSERT_EQ(universe->get_entity("bar"), shader);
    ASSERT_EQ(scene->get_entity("foo"), nullptr);
    ASSERT_EQ(scene->get_entity("bar"), nullptr);
}

TEST(shader_must_be_given_a_local_name_appropriately_after_setting_a_local_name, headless)
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
    ASSERT_EQ(shader->get_global_name(), "");
    ASSERT_EQ(shader->get_local_name(), "");

    shader->set_local_name("foo");
    shader->set_local_name("bar");
    ASSERT_EQ(shader->get_global_name(), "");
    ASSERT_EQ(shader->get_local_name(), "bar");
    ASSERT_FALSE(universe->has_child("foo"));
    ASSERT_FALSE(universe->has_child("bar"));
    ASSERT_FALSE(scene->has_child("foo"));
    ASSERT_TRUE(scene->has_child("bar"));
    ASSERT_EQ(universe->get_entity("foo"), nullptr);
    ASSERT_EQ(universe->get_entity("bar"), nullptr);
    ASSERT_EQ(scene->get_entity("foo"), nullptr);
    ASSERT_EQ(scene->get_entity("bar"), shader);
}

TEST(shader_must_be_given_a_global_name_appropriately_after_setting_a_local_name, headless)
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
    ASSERT_EQ(shader->get_global_name(), "");
    ASSERT_EQ(shader->get_local_name(), "");

    shader->set_local_name("foo");
    shader->set_global_name("bar");
    ASSERT_EQ(shader->get_global_name(), "bar");
    ASSERT_EQ(shader->get_local_name(), "foo");
    ASSERT_FALSE(universe->has_child("foo"));
    ASSERT_TRUE(universe->has_child("bar"));
    ASSERT_TRUE(scene->has_child("foo"));
    ASSERT_FALSE(scene->has_child("bar"));
    ASSERT_EQ(universe->get_entity("foo"), nullptr);
    ASSERT_EQ(universe->get_entity("bar"), shader);
    ASSERT_EQ(scene->get_entity("foo"), shader);
    ASSERT_EQ(scene->get_entity("bar"), nullptr);
}

TEST(shader_must_be_given_a_local_name_appropriately_after_setting_a_global_name, headless)
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
    ASSERT_EQ(shader->get_global_name(), "");
    ASSERT_EQ(shader->get_local_name(), "");

    shader->set_global_name("foo");
    shader->set_local_name("bar");
    ASSERT_EQ(shader->get_global_name(), "foo");
    ASSERT_EQ(shader->get_local_name(), "bar");
    ASSERT_TRUE(universe->has_child("foo"));
    ASSERT_FALSE(universe->has_child("bar"));
    ASSERT_FALSE(scene->has_child("foo"));
    ASSERT_TRUE(scene->has_child("bar"));
    ASSERT_EQ(universe->get_entity("foo"), shader);
    ASSERT_EQ(universe->get_entity("bar"), nullptr);
    ASSERT_EQ(scene->get_entity("foo"), nullptr);
    ASSERT_EQ(scene->get_entity("bar"), shader);
}

TEST(shader_must_maintain_the_local_name_after_binding_to_a_new_parent, headless_universe_shader_with_only_local_name)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::SceneStruct scene_struct1;
    yli::ontology::Scene* const scene1 = new yli::ontology::Scene(
            *universe,
            scene_struct1,
            &universe->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene1;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(*universe, shader_struct, &scene1->parent_of_shaders);

    yli::ontology::SceneStruct scene_struct2;
    yli::ontology::Scene* const scene2 = new yli::ontology::Scene(
            *universe,
            scene_struct2,
            &universe->parent_of_scenes);

    shader->set_local_name("foo");
    yli::ontology::Shader::bind_to_new_scene_parent(*shader, *scene2);
    ASSERT_FALSE(scene1->has_child("foo"));
    ASSERT_TRUE(scene2->has_child("foo"));
    ASSERT_EQ(shader->get_parent(), scene2);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 1);
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 2);

    yli::ontology::Shader::bind_to_new_scene_parent(*shader, *scene1);
    ASSERT_TRUE(scene1->has_child("foo"));
    ASSERT_FALSE(scene2->has_child("foo"));
    ASSERT_EQ(shader->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 2);
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 1);
}

TEST(shader_must_maintain_the_local_name_after_binding_to_a_new_parent, headless_universe_shader_with_global_name_and_local_name)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::SceneStruct scene_struct1;
    yli::ontology::Scene* const scene1 = new yli::ontology::Scene(
            *universe,
            scene_struct1,
            &universe->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene1;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(*universe, shader_struct, &scene1->parent_of_shaders);

    yli::ontology::SceneStruct scene_struct2;
    yli::ontology::Scene* const scene2 = new yli::ontology::Scene(
            *universe,
            scene_struct2,
            &universe->parent_of_scenes);

    shader->set_global_name("foo");
    shader->set_local_name("bar");
    yli::ontology::Shader::bind_to_new_scene_parent(*shader, *scene2);
    ASSERT_FALSE(scene1->has_child("foo"));
    ASSERT_FALSE(scene2->has_child("foo"));
    ASSERT_FALSE(scene1->has_child("bar"));
    ASSERT_TRUE(scene2->has_child("bar"));
    ASSERT_EQ(shader->get_parent(), scene2);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 1);
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 2);

    yli::ontology::Shader::bind_to_new_scene_parent(*shader, *scene1);
    ASSERT_FALSE(scene1->has_child("foo"));
    ASSERT_FALSE(scene2->has_child("foo"));
    ASSERT_TRUE(scene1->has_child("bar"));
    ASSERT_FALSE(scene2->has_child("bar"));
    ASSERT_EQ(shader->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 2);
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 1);
}

TEST(shader_must_not_bind_to_a_new_parent_when_local_name_is_already_in_use, headless_universe_shaders_with_only_local_name)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::SceneStruct scene_struct1;
    yli::ontology::Scene* const scene1 = new yli::ontology::Scene(
            *universe,
            scene_struct1,
            &universe->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct1;
    shader_struct1.parent = scene1;
    yli::ontology::Shader* const shader1 = new yli::ontology::Shader(*universe, shader_struct1, &scene1->parent_of_shaders);

    yli::ontology::SceneStruct scene_struct2;
    yli::ontology::Scene* const scene2 = new yli::ontology::Scene(
            *universe,
            scene_struct2,
            &universe->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct2;
    shader_struct2.parent = scene2;
    yli::ontology::Shader* const shader2 = new yli::ontology::Shader(*universe, shader_struct2, &scene2->parent_of_shaders);

    shader1->set_local_name("foo");
    shader2->set_local_name("foo");
    yli::ontology::Shader::bind_to_new_scene_parent(*shader1, *scene2);
    ASSERT_EQ(shader1->get_scene(), scene1);
    ASSERT_EQ(shader1->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 2);
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 2);
    ASSERT_TRUE(scene1->has_child("foo"));
    ASSERT_TRUE(scene2->has_child("foo"));
}

TEST(shader_must_not_bind_to_a_new_parent_when_local_name_is_already_in_use, headless_universe_shaders_with_different_global_names_and_same_local_name)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::SceneStruct scene_struct1;
    yli::ontology::Scene* const scene1 = new yli::ontology::Scene(
            *universe,
            scene_struct1,
            &universe->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct1;
    shader_struct1.parent = scene1;
    yli::ontology::Shader* const shader1 = new yli::ontology::Shader(*universe, shader_struct1, &scene1->parent_of_shaders);

    yli::ontology::SceneStruct scene_struct2;
    yli::ontology::Scene* const scene2 = new yli::ontology::Scene(
            *universe,
            scene_struct2,
            &universe->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct2;
    shader_struct2.parent = scene2;
    yli::ontology::Shader* const shader2 = new yli::ontology::Shader(*universe, shader_struct2, &scene2->parent_of_shaders);

    shader1->set_global_name("foo");
    shader2->set_global_name("bar");
    shader1->set_local_name("baz");
    shader2->set_local_name("baz");
    yli::ontology::Shader::bind_to_new_scene_parent(*shader1, *scene2);
    ASSERT_EQ(shader1->get_scene(), scene1);
    ASSERT_EQ(shader1->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_non_variable_children(), 2);
    ASSERT_EQ(scene2->get_number_of_non_variable_children(), 2);
    ASSERT_FALSE(scene1->has_child("foo"));
    ASSERT_FALSE(scene2->has_child("foo"));
    ASSERT_FALSE(scene1->has_child("bar"));
    ASSERT_FALSE(scene2->has_child("bar"));
    ASSERT_TRUE(scene1->has_child("baz"));
    ASSERT_TRUE(scene2->has_child("baz"));
}

TEST(shader_must_not_unbind_any_of_its_apprentice_modules_when_binding_to_an_ecosystem, headless_universe_material_apprentice)
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
            &scene->parent_of_materials,
            &shader->master_of_materials);

    ASSERT_EQ(shader->get_number_of_apprentices(), 1);

    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = new yli::ontology::Ecosystem(
            *universe,
            ecosystem_struct,
            &universe->parent_of_ecosystems);

    yli::ontology::Shader::bind_to_new_ecosystem_parent(*shader, *ecosystem);
    ASSERT_EQ(shader->get_number_of_apprentices(), 1);
}

TEST(shader_must_not_unbind_any_of_its_apprentice_modules_when_binding_to_an_ecosystem, headless_universe_symbiosis_apprentice)
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

    yli::ontology::ModelStruct model_struct;
    model_struct.scene = scene;
    model_struct.shader = shader;
    yli::ontology::Symbiosis* const symbiosis = new yli::ontology::Symbiosis(
            *universe,
            model_struct,
            &scene->parent_of_symbioses,
            &shader->master_of_symbioses);

    ASSERT_EQ(shader->get_number_of_apprentices(), 1);

    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = new yli::ontology::Ecosystem(
            *universe,
            ecosystem_struct,
            &universe->parent_of_ecosystems);

    yli::ontology::Shader::bind_to_new_ecosystem_parent(*shader, *ecosystem);
    ASSERT_EQ(shader->get_number_of_apprentices(), 1);
}

TEST(shader_must_not_unbind_any_of_its_apprentice_modules_when_binding_to_the_current_scene, headless_universe_material_apprentice)
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
            &scene->parent_of_materials,
            &shader->master_of_materials);

    ASSERT_EQ(shader->get_number_of_apprentices(), 1);

    yli::ontology::Shader::bind_to_new_scene_parent(*shader, *scene);
    ASSERT_EQ(shader->get_number_of_apprentices(), 1);
}

TEST(shader_must_not_unbind_any_of_its_apprentice_modules_when_binding_to_the_current_scene, headless_universe_symbiosis_apprentice)
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

    yli::ontology::ModelStruct model_struct;
    model_struct.scene = scene;
    model_struct.shader = shader;
    yli::ontology::Symbiosis* const symbiosis = new yli::ontology::Symbiosis(
            *universe,
            model_struct,
            &scene->parent_of_symbioses,
            &shader->master_of_symbioses);

    ASSERT_EQ(shader->get_number_of_apprentices(), 1);

    yli::ontology::Shader::bind_to_new_scene_parent(*shader, *scene);
    ASSERT_EQ(shader->get_number_of_apprentices(), 1);
}

TEST(shader_must_not_unbind_any_of_its_apprentice_modules_when_binding_to_the_current_scene, headless_universe_material_and_symbiosis_apprentices)
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
            &scene->parent_of_materials,
            &shader->master_of_materials);

    yli::ontology::ModelStruct model_struct;
    model_struct.scene = scene;
    model_struct.shader = shader;
    yli::ontology::Symbiosis* const symbiosis = new yli::ontology::Symbiosis(
            *universe,
            model_struct,
            &scene->parent_of_symbioses,
            &shader->master_of_symbioses);

    ASSERT_EQ(shader->get_number_of_apprentices(), 2);

    yli::ontology::Shader::bind_to_new_scene_parent(*shader, *scene);
    ASSERT_EQ(shader->get_number_of_apprentices(), 2);
}

TEST(shader_must_unbind_all_of_its_apprentice_modules_when_binding_to_a_different_scene, headless_universe_material_apprentice)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene1 = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene1;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(*universe, shader_struct, &scene1->parent_of_shaders);

    yli::ontology::MaterialStruct material_struct;
    material_struct.parent = scene1;
    material_struct.shader = shader;
    yli::ontology::Material* const material = new yli::ontology::Material(
            *universe,
            material_struct,
            &scene1->parent_of_materials,
            &shader->master_of_materials);

    ASSERT_EQ(shader->get_number_of_apprentices(), 1);

    yli::ontology::Scene* const scene2 = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);

    yli::ontology::Shader::bind_to_new_scene_parent(*shader, *scene2);
    ASSERT_EQ(shader->get_number_of_apprentices(), 0);
}

TEST(shader_must_unbind_all_of_its_apprentice_modules_when_binding_to_a_different_scene, headless_universe_symbiosis_apprentice)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene1 = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene1;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(*universe, shader_struct, &scene1->parent_of_shaders);

    yli::ontology::ModelStruct model_struct;
    model_struct.scene = scene1;
    model_struct.shader = shader;
    yli::ontology::Symbiosis* const symbiosis = new yli::ontology::Symbiosis(
            *universe,
            model_struct,
            &scene1->parent_of_symbioses,
            &shader->master_of_symbioses);

    ASSERT_EQ(shader->get_number_of_apprentices(), 1);

    yli::ontology::Scene* const scene2 = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);

    yli::ontology::Shader::bind_to_new_scene_parent(*shader, *scene2);
    ASSERT_EQ(shader->get_number_of_apprentices(), 0);
}

TEST(shader_must_unbind_all_of_its_apprentice_modules_when_binding_to_a_different_scene, headless_universe_material_and_symbiosis_apprentices)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::SceneStruct scene_struct;
    yli::ontology::Scene* const scene1 = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene1;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(*universe, shader_struct, &scene1->parent_of_shaders);

    yli::ontology::MaterialStruct material_struct;
    material_struct.parent = scene1;
    material_struct.shader = shader;
    yli::ontology::Material* const material = new yli::ontology::Material(
            *universe,
            material_struct,
            &scene1->parent_of_materials,
            &shader->master_of_materials);

    yli::ontology::ModelStruct model_struct;
    model_struct.scene = scene1;
    model_struct.shader = shader;
    yli::ontology::Symbiosis* const symbiosis = new yli::ontology::Symbiosis(
            *universe,
            model_struct,
            &scene1->parent_of_symbioses,
            &shader->master_of_symbioses);

    ASSERT_EQ(shader->get_number_of_apprentices(), 2);

    yli::ontology::Scene* const scene2 = new yli::ontology::Scene(
            *universe,
            scene_struct,
            &universe->parent_of_scenes);

    yli::ontology::Shader::bind_to_new_scene_parent(*shader, *scene2);
    ASSERT_EQ(shader->get_number_of_apprentices(), 0);
}
