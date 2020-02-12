// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
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
#include "code/ylikuutio/ontology/universe.cpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/world.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/shader.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/symbiosis.hpp"
#include "code/ylikuutio/ontology/holobiont.hpp"
#include "code/ylikuutio/ontology/shapeshifter_transformation.hpp"
#include "code/ylikuutio/ontology/shapeshifter_form.hpp"
#include "code/ylikuutio/ontology/shapeshifter_sequence.hpp"
#include "code/ylikuutio/ontology/shapeshifter_sequence_struct.hpp"
#include "code/ylikuutio/ontology/font2D.hpp"
#include "code/ylikuutio/ontology/brain.hpp"
#include "code/ylikuutio/ontology/object_type.hpp"
#include "code/ylikuutio/ontology/universe_struct.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/shader_struct.hpp"
#include "code/ylikuutio/ontology/material_struct.hpp"
#include "code/ylikuutio/ontology/species_struct.hpp"
#include "code/ylikuutio/ontology/object_struct.hpp"
#include "code/ylikuutio/ontology/symbiosis_struct.hpp"
#include "code/ylikuutio/ontology/holobiont_struct.hpp"
#include "code/ylikuutio/ontology/brain_struct.hpp"
#include "code/ylikuutio/scheme/scheme_master.cpp"
#include "code/ylikuutio/scheme/scheme_master.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <limits>  // std::numeric_limits
#include <memory>  // std::make_shared, std::shared_ptr

TEST(universe_must_be_initialized_appropriately, headless)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    // `Universe` member variables.
    ASSERT_FALSE(universe->is_invert_mouse_in_use);
    ASSERT_FALSE(universe->is_first_turbo_pressed);
    ASSERT_FALSE(universe->is_second_turbo_pressed);
    ASSERT_TRUE(universe->is_exit_requested);
    ASSERT_FALSE(universe->in_console);
    ASSERT_TRUE(universe->in_help_mode);
    ASSERT_TRUE(universe->can_display_help_screen);

    // `Universe` member functions.
    ASSERT_TRUE(universe->get_is_headless());
    ASSERT_EQ(universe->get_active_font2D(), nullptr);
    ASSERT_EQ(universe->get_number_of_worlds(), 0);
    ASSERT_EQ(universe->get_active_scene(), nullptr);

    // `Entity` member functions.
    ASSERT_EQ(universe->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(universe->get_type(), "yli::ontology::Universe*");
    ASSERT_FALSE(universe->get_can_be_erased());
    ASSERT_EQ(universe->get_universe(), universe);
    ASSERT_NE(universe->get_setting_master(), nullptr);
    ASSERT_EQ(universe->get_parent(), nullptr);
    ASSERT_EQ(universe->get_number_of_children(), 0);
    ASSERT_EQ(universe->get_number_of_descendants(), 0);
}

TEST(world_must_be_initialized_appropriately, headless)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::World* const world = new yli::ontology::World(universe, &universe->parent_of_worlds);

    // `Universe` member functions.
    ASSERT_EQ(universe->get_number_of_worlds(), 1);
    ASSERT_EQ(universe->get_active_scene(), nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_children(), 1);
    ASSERT_EQ(universe->get_number_of_descendants(), 1);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world->get_childID(), 0);
    ASSERT_EQ(world->get_type(), "yli::ontology::World*");
    ASSERT_TRUE(world->get_can_be_erased());
    ASSERT_EQ(world->get_universe(), universe);
    ASSERT_NE(world->get_setting_master(), nullptr);
    ASSERT_EQ(world->get_parent(), universe);
    ASSERT_EQ(world->get_number_of_children(), 0);
    ASSERT_EQ(world->get_number_of_descendants(), 0);
}

TEST(world_must_be_initialized_appropriately, no_universe)
{
    yli::ontology::World* const world = new yli::ontology::World(nullptr, nullptr);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(world->get_type(), "yli::ontology::World*");
    ASSERT_TRUE(world->get_can_be_erased());
    ASSERT_EQ(world->get_universe(), nullptr);
    ASSERT_NE(world->get_setting_master(), nullptr);
    ASSERT_EQ(world->get_parent(), nullptr);
    ASSERT_EQ(world->get_number_of_children(), 0);
    ASSERT_EQ(world->get_number_of_descendants(), 0);
}

TEST(scene_must_be_initialized_appropriately, headless)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    yli::ontology::World* const world = new yli::ontology::World(universe, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);

    // `Universe` member functions.
    ASSERT_EQ(universe->get_number_of_worlds(), 1);
    ASSERT_EQ(universe->get_active_scene(), nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_children(), 1);
    ASSERT_EQ(universe->get_number_of_descendants(), 2);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world->get_number_of_children(), 1);
    ASSERT_EQ(world->get_number_of_descendants(), 1);

    // `Entity` member functions.
    ASSERT_EQ(scene->get_childID(), 0);
    ASSERT_EQ(scene->get_type(), "yli::ontology::Scene*");
    ASSERT_TRUE(scene->get_can_be_erased());
    ASSERT_EQ(scene->get_universe(), universe);
    ASSERT_NE(scene->get_setting_master(), nullptr);
    ASSERT_EQ(scene->get_parent(), world);
    ASSERT_EQ(scene->get_number_of_children(), 0);
    ASSERT_EQ(scene->get_number_of_descendants(), 0);
}

TEST(scene_must_be_initialized_appropriately, no_universe)
{
    yli::ontology::World* const world = new yli::ontology::World(nullptr, nullptr);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(nullptr, scene_struct, &world->parent_of_scenes);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world->get_number_of_children(), 1);
    ASSERT_EQ(world->get_number_of_descendants(), 1);

    // `Entity` member functions.
    ASSERT_EQ(scene->get_childID(), 0);
    ASSERT_EQ(scene->get_type(), "yli::ontology::Scene*");
    ASSERT_TRUE(scene->get_can_be_erased());
    ASSERT_EQ(scene->get_universe(), nullptr);
    ASSERT_NE(scene->get_setting_master(), nullptr);
    ASSERT_EQ(scene->get_parent(), world);
    ASSERT_EQ(scene->get_number_of_children(), 0);
    ASSERT_EQ(scene->get_number_of_descendants(), 0);
}

TEST(scene_must_be_initialized_appropriately, no_universe_no_world)
{
    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = nullptr;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(nullptr, scene_struct, nullptr);

    // `Entity` member functions.
    ASSERT_EQ(scene->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(scene->get_type(), "yli::ontology::Scene*");
    ASSERT_TRUE(scene->get_can_be_erased());
    ASSERT_EQ(scene->get_universe(), nullptr);
    ASSERT_NE(scene->get_setting_master(), nullptr);
    ASSERT_EQ(scene->get_parent(), nullptr);
    ASSERT_EQ(scene->get_number_of_children(), 0);
    ASSERT_EQ(scene->get_number_of_descendants(), 0);
}

TEST(shader_must_be_initialized_appropriately, headless)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    yli::ontology::World* const world = new yli::ontology::World(universe, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(universe, shader_struct);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_children(), 1);
    ASSERT_EQ(universe->get_number_of_descendants(), 3);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world->get_number_of_children(), 1);
    ASSERT_EQ(world->get_number_of_descendants(), 2);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_children(), 1);
    ASSERT_EQ(scene->get_number_of_descendants(), 1);

    // `Entity` member functions.
    ASSERT_EQ(shader->get_childID(), 0);
    ASSERT_EQ(shader->get_type(), "yli::ontology::Shader*");
    ASSERT_TRUE(shader->get_can_be_erased());
    ASSERT_EQ(shader->get_universe(), universe);
    ASSERT_NE(shader->get_setting_master(), nullptr);
    ASSERT_EQ(shader->get_parent(), scene);
    ASSERT_EQ(shader->get_number_of_children(), 0);
    ASSERT_EQ(shader->get_number_of_descendants(), 0);
}

TEST(shader_must_be_initialized_appropriately, no_universe)
{
    yli::ontology::World* const world = new yli::ontology::World(nullptr, nullptr);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(nullptr, scene_struct, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(nullptr, shader_struct);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world->get_number_of_children(), 1);
    ASSERT_EQ(world->get_number_of_descendants(), 2);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_children(), 1);
    ASSERT_EQ(scene->get_number_of_descendants(), 1);

    // `Entity` member functions.
    ASSERT_EQ(shader->get_childID(), 0);
    ASSERT_EQ(shader->get_type(), "yli::ontology::Shader*");
    ASSERT_TRUE(shader->get_can_be_erased());
    ASSERT_EQ(shader->get_universe(), nullptr);
    ASSERT_NE(shader->get_setting_master(), nullptr);
    ASSERT_EQ(shader->get_parent(), scene);
    ASSERT_EQ(shader->get_number_of_children(), 0);
    ASSERT_EQ(shader->get_number_of_descendants(), 0);
}

TEST(shader_must_be_initialized_appropriately, no_universe_no_world)
{
    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = nullptr;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(nullptr, scene_struct, nullptr);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(nullptr, shader_struct);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_children(), 1);
    ASSERT_EQ(scene->get_number_of_descendants(), 1);

    // `Entity` member functions.
    ASSERT_EQ(shader->get_childID(), 0);
    ASSERT_EQ(shader->get_type(), "yli::ontology::Shader*");
    ASSERT_TRUE(shader->get_can_be_erased());
    ASSERT_EQ(shader->get_universe(), nullptr);
    ASSERT_NE(shader->get_setting_master(), nullptr);
    ASSERT_EQ(shader->get_parent(), scene);
    ASSERT_EQ(shader->get_number_of_children(), 0);
    ASSERT_EQ(shader->get_number_of_descendants(), 0);
}

TEST(shader_must_be_initialized_appropriately, no_universe_no_world_no_scene)
{
    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = nullptr;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(nullptr, shader_struct);

    // `Entity` member functions.
    ASSERT_EQ(shader->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(shader->get_type(), "yli::ontology::Shader*");
    ASSERT_TRUE(shader->get_can_be_erased());
    ASSERT_EQ(shader->get_universe(), nullptr);
    ASSERT_NE(shader->get_setting_master(), nullptr);
    ASSERT_EQ(shader->get_parent(), nullptr);
    ASSERT_EQ(shader->get_number_of_children(), 0);
    ASSERT_EQ(shader->get_number_of_descendants(), 0);
}

TEST(material_must_be_initialized_appropriately, headless)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    yli::ontology::World* const world = new yli::ontology::World(universe, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(universe, shader_struct);

    yli::ontology::MaterialStruct material_struct;
    material_struct.shader = shader;
    yli::ontology::Material* const material = new yli::ontology::Material(universe, material_struct, &shader->parent_of_materials);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_children(), 1);
    ASSERT_EQ(universe->get_number_of_descendants(), 4);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world->get_number_of_children(), 1);
    ASSERT_EQ(world->get_number_of_descendants(), 3);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_children(), 1);
    ASSERT_EQ(scene->get_number_of_descendants(), 2);

    // `Entity` member functions of `Shader`.
    ASSERT_EQ(shader->get_number_of_children(), 1);
    ASSERT_EQ(shader->get_number_of_descendants(), 1);

    // `Entity` member functions.
    ASSERT_EQ(material->get_childID(), 0);
    ASSERT_EQ(material->get_type(), "yli::ontology::Material*");
    ASSERT_TRUE(material->get_can_be_erased());
    ASSERT_EQ(material->get_universe(), universe);
    ASSERT_NE(material->get_setting_master(), nullptr);
    ASSERT_EQ(material->get_parent(), shader);
    ASSERT_EQ(material->get_number_of_children(), 0);
    ASSERT_EQ(material->get_number_of_descendants(), 0);
}

TEST(material_must_be_initialized_appropriately, no_universe)
{
    yli::ontology::World* const world = new yli::ontology::World(nullptr, nullptr);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(nullptr, scene_struct, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(nullptr, shader_struct);

    yli::ontology::MaterialStruct material_struct;
    material_struct.shader = shader;
    yli::ontology::Material* const material = new yli::ontology::Material(nullptr, material_struct, &shader->parent_of_materials);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world->get_number_of_children(), 1);
    ASSERT_EQ(world->get_number_of_descendants(), 3);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_children(), 1);
    ASSERT_EQ(scene->get_number_of_descendants(), 2);

    // `Entity` member functions of `Shader`.
    ASSERT_EQ(shader->get_number_of_children(), 1);
    ASSERT_EQ(shader->get_number_of_descendants(), 1);

    // `Entity` member functions.
    ASSERT_EQ(material->get_childID(), 0);
    ASSERT_EQ(material->get_type(), "yli::ontology::Material*");
    ASSERT_TRUE(material->get_can_be_erased());
    ASSERT_EQ(material->get_universe(), nullptr);
    ASSERT_NE(material->get_setting_master(), nullptr);
    ASSERT_EQ(material->get_parent(), shader);
    ASSERT_EQ(material->get_number_of_children(), 0);
    ASSERT_EQ(material->get_number_of_descendants(), 0);
}

TEST(material_must_be_initialized_appropriately, no_universe_no_world)
{
    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = nullptr;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(nullptr, scene_struct, nullptr);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(nullptr, shader_struct);

    yli::ontology::MaterialStruct material_struct;
    material_struct.shader = shader;
    yli::ontology::Material* const material = new yli::ontology::Material(nullptr, material_struct, &shader->parent_of_materials);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_children(), 1);
    ASSERT_EQ(scene->get_number_of_descendants(), 2);

    // `Entity` member functions of `Shader`.
    ASSERT_EQ(shader->get_number_of_children(), 1);
    ASSERT_EQ(shader->get_number_of_descendants(), 1);

    // `Entity` member functions.
    ASSERT_EQ(material->get_childID(), 0);
    ASSERT_EQ(material->get_type(), "yli::ontology::Material*");
    ASSERT_TRUE(material->get_can_be_erased());
    ASSERT_EQ(material->get_universe(), nullptr);
    ASSERT_NE(material->get_setting_master(), nullptr);
    ASSERT_EQ(material->get_parent(), shader);
    ASSERT_EQ(material->get_number_of_children(), 0);
    ASSERT_EQ(material->get_number_of_descendants(), 0);
}

TEST(material_must_be_initialized_appropriately, no_universe_no_world_no_scene)
{
    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = nullptr;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(nullptr, shader_struct);

    yli::ontology::MaterialStruct material_struct;
    material_struct.shader = shader;
    yli::ontology::Material* const material = new yli::ontology::Material(nullptr, material_struct, &shader->parent_of_materials);

    // `Entity` member functions of `Shader`.
    ASSERT_EQ(shader->get_number_of_children(), 1);
    ASSERT_EQ(shader->get_number_of_descendants(), 1);

    // `Entity` member functions.
    ASSERT_EQ(material->get_childID(), 0);
    ASSERT_EQ(material->get_type(), "yli::ontology::Material*");
    ASSERT_TRUE(material->get_can_be_erased());
    ASSERT_EQ(material->get_universe(), nullptr);
    ASSERT_NE(material->get_setting_master(), nullptr);
    ASSERT_EQ(material->get_parent(), shader);
    ASSERT_EQ(material->get_number_of_children(), 0);
    ASSERT_EQ(material->get_number_of_descendants(), 0);
}

TEST(material_must_be_initialized_appropriately, no_universe_no_world_no_scene_no_shader)
{
    yli::ontology::MaterialStruct material_struct;
    material_struct.shader = nullptr;
    yli::ontology::Material* const material = new yli::ontology::Material(nullptr, material_struct, nullptr);

    // `Entity` member functions.
    ASSERT_EQ(material->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(material->get_type(), "yli::ontology::Material*");
    ASSERT_TRUE(material->get_can_be_erased());
    ASSERT_EQ(material->get_universe(), nullptr);
    ASSERT_NE(material->get_setting_master(), nullptr);
    ASSERT_EQ(material->get_parent(), nullptr);
    ASSERT_EQ(material->get_number_of_children(), 0);
    ASSERT_EQ(material->get_number_of_descendants(), 0);
}

TEST(species_must_be_initialized_appropriately, headless)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    yli::ontology::World* const world = new yli::ontology::World(universe, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(universe, shader_struct);

    yli::ontology::MaterialStruct material_struct;
    material_struct.shader = shader;
    yli::ontology::Material* const material = new yli::ontology::Material(universe, material_struct, &shader->parent_of_materials);

    yli::ontology::SpeciesStruct species_struct;
    species_struct.scene = scene;
    species_struct.shader = shader;
    species_struct.material = material;
    yli::ontology::Species* const species = new yli::ontology::Species(universe, species_struct);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_children(), 1);
    ASSERT_EQ(universe->get_number_of_descendants(), 5);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world->get_number_of_children(), 1);
    ASSERT_EQ(world->get_number_of_descendants(), 4);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_children(), 1);
    ASSERT_EQ(scene->get_number_of_descendants(), 3);

    // `Entity` member functions of `Shader`.
    ASSERT_EQ(shader->get_number_of_children(), 1);
    ASSERT_EQ(shader->get_number_of_descendants(), 2);

    // `Entity` member functions of `Material`.
    ASSERT_EQ(material->get_number_of_children(), 1);
    ASSERT_EQ(material->get_number_of_descendants(), 1);

    // `Entity` member functions.
    ASSERT_EQ(species->get_childID(), 0);
    ASSERT_EQ(species->get_type(), "yli::ontology::Species*");
    ASSERT_TRUE(species->get_can_be_erased());
    ASSERT_EQ(species->get_universe(), universe);
    ASSERT_NE(species->get_setting_master(), nullptr);
    ASSERT_EQ(species->get_parent(), material);
    ASSERT_EQ(species->get_number_of_children(), 0);
    ASSERT_EQ(species->get_number_of_descendants(), 0);
}

TEST(species_must_be_initialized_appropriately, no_universe_no_world_no_scene_no_shader_no_material)
{
    yli::ontology::SpeciesStruct species_struct;
    species_struct.scene = nullptr;
    species_struct.shader = nullptr;
    species_struct.material = nullptr;
    yli::ontology::Species* const species = new yli::ontology::Species(nullptr, species_struct);

    // `Entity` member functions.
    ASSERT_EQ(species->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(species->get_type(), "yli::ontology::Species*");
    ASSERT_TRUE(species->get_can_be_erased());
    ASSERT_EQ(species->get_universe(), nullptr);
    ASSERT_NE(species->get_setting_master(), nullptr);
    ASSERT_EQ(species->get_parent(), nullptr);
    ASSERT_EQ(species->get_number_of_children(), 0);
    ASSERT_EQ(species->get_number_of_descendants(), 0);
}

TEST(object_must_be_initialized_appropriately, headless)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    yli::ontology::World* const world = new yli::ontology::World(universe, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(universe, shader_struct);

    yli::ontology::MaterialStruct material_struct;
    material_struct.shader = shader;
    yli::ontology::Material* const material = new yli::ontology::Material(universe, material_struct, &shader->parent_of_materials);

    yli::ontology::SpeciesStruct species_struct;
    species_struct.scene = scene;
    species_struct.shader = shader;
    species_struct.material = material;
    yli::ontology::Species* const species = new yli::ontology::Species(universe, species_struct);

    yli::ontology::ObjectStruct object_struct;
    object_struct.species_parent = species;
    yli::ontology::Object* const object = new yli::ontology::Object(universe, object_struct);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_children(), 1);
    ASSERT_EQ(universe->get_number_of_descendants(), 6);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world->get_number_of_children(), 1);
    ASSERT_EQ(world->get_number_of_descendants(), 5);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_children(), 1);
    ASSERT_EQ(scene->get_number_of_descendants(), 4);

    // `Entity` member functions of `Shader`.
    ASSERT_EQ(shader->get_number_of_children(), 1);
    ASSERT_EQ(shader->get_number_of_descendants(), 3);

    // `Entity` member functions of `Material`.
    ASSERT_EQ(material->get_number_of_children(), 1);
    ASSERT_EQ(material->get_number_of_descendants(), 2);

    // `Entity` member functions of `Species`.
    ASSERT_EQ(species->get_number_of_children(), 1);
    ASSERT_EQ(species->get_number_of_descendants(), 1);

    // `Entity` member functions.
    ASSERT_EQ(object->get_childID(), 0);
    ASSERT_EQ(object->get_type(), "yli::ontology::Object*");
    ASSERT_TRUE(object->get_can_be_erased());
    ASSERT_EQ(object->get_universe(), universe);
    ASSERT_NE(object->get_setting_master(), nullptr);
    ASSERT_EQ(object->get_parent(), species);
    ASSERT_EQ(object->get_number_of_children(), 0);
    ASSERT_EQ(object->get_number_of_descendants(), 0);
}

TEST(object_must_be_initialized_appropriately, no_universe_no_world_no_scene_no_shader_no_material_no_species)
{
    yli::ontology::ObjectStruct object_struct;
    object_struct.species_parent = nullptr;
    yli::ontology::Object* const object = new yli::ontology::Object(nullptr, object_struct);

    // `Entity` member functions.
    ASSERT_EQ(object->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(object->get_type(), "yli::ontology::Object*");
    ASSERT_TRUE(object->get_can_be_erased());
    ASSERT_EQ(object->get_universe(), nullptr);
    ASSERT_NE(object->get_setting_master(), nullptr);
    ASSERT_EQ(object->get_parent(), nullptr);
    ASSERT_EQ(object->get_number_of_children(), 0);
    ASSERT_EQ(object->get_number_of_descendants(), 0);
}

TEST(symbiosis_must_be_initialized_appropriately, headless)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    yli::ontology::World* const world = new yli::ontology::World(universe, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(universe, shader_struct);

    yli::ontology::SymbiosisStruct symbiosis_struct;
    symbiosis_struct.parent = shader;
    yli::ontology::Symbiosis* const symbiosis = new yli::ontology::Symbiosis(universe, symbiosis_struct, &shader->parent_of_symbioses);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_children(), 1);
    ASSERT_EQ(universe->get_number_of_descendants(), 4);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world->get_number_of_children(), 1);
    ASSERT_EQ(world->get_number_of_descendants(), 3);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_children(), 1);
    ASSERT_EQ(scene->get_number_of_descendants(), 2);

    // `Entity` member functions of `Shader`.
    ASSERT_EQ(shader->get_number_of_children(), 1);
    ASSERT_EQ(shader->get_number_of_descendants(), 1);

    // `Entity` member functions.
    ASSERT_EQ(symbiosis->get_childID(), 0);
    ASSERT_EQ(symbiosis->get_type(), "yli::ontology::Symbiosis*");
    ASSERT_TRUE(symbiosis->get_can_be_erased());
    ASSERT_EQ(symbiosis->get_universe(), universe);
    ASSERT_NE(symbiosis->get_setting_master(), nullptr);
    ASSERT_EQ(symbiosis->get_parent(), shader);
    ASSERT_EQ(symbiosis->get_number_of_children(), 0);
    ASSERT_EQ(symbiosis->get_number_of_descendants(), 0);
}

TEST(symbiosis_must_be_initialized_appropriately, no_universe_no_world_no_scene_no_material_no_shader)
{
    yli::ontology::SymbiosisStruct symbiosis_struct;
    symbiosis_struct.parent = nullptr;
    yli::ontology::Symbiosis* const symbiosis = new yli::ontology::Symbiosis(nullptr, symbiosis_struct, nullptr);

    // `Entity` member functions.
    ASSERT_EQ(symbiosis->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(symbiosis->get_type(), "yli::ontology::Symbiosis*");
    ASSERT_TRUE(symbiosis->get_can_be_erased());
    ASSERT_EQ(symbiosis->get_universe(), nullptr);
    ASSERT_NE(symbiosis->get_setting_master(), nullptr);
    ASSERT_EQ(symbiosis->get_parent(), nullptr);
    ASSERT_EQ(symbiosis->get_number_of_children(), 0);
    ASSERT_EQ(symbiosis->get_number_of_descendants(), 0);
}

TEST(symbiosis_must_be_initialized_appropriately, headless_turbo_polizei)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    yli::ontology::World* const world = new yli::ontology::World(universe, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(universe, shader_struct);

    yli::ontology::SymbiosisStruct symbiosis_struct;
    symbiosis_struct.parent = shader;
    symbiosis_struct.model_filename = "turbo_polizei.fbx";
    symbiosis_struct.model_file_format = "FBX";
    yli::ontology::Symbiosis* const symbiosis = new yli::ontology::Symbiosis(universe, symbiosis_struct, &shader->parent_of_symbioses);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_children(), 1);
    ASSERT_EQ(universe->get_number_of_descendants(), 11);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world->get_number_of_children(), 1);
    ASSERT_EQ(world->get_number_of_descendants(), 10);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_children(), 1);
    ASSERT_EQ(scene->get_number_of_descendants(), 9);

    // `Entity` member functions of `Shader`.
    ASSERT_EQ(shader->get_number_of_children(), 1);
    ASSERT_EQ(shader->get_number_of_descendants(), 8);

    // `Entity` member functions.
    ASSERT_EQ(symbiosis->get_childID(), 0);
    ASSERT_EQ(symbiosis->get_type(), "yli::ontology::Symbiosis*");
    ASSERT_TRUE(symbiosis->get_can_be_erased());
    ASSERT_EQ(symbiosis->get_universe(), universe);
    ASSERT_NE(symbiosis->get_setting_master(), nullptr);
    ASSERT_EQ(symbiosis->get_parent(), shader);
    ASSERT_EQ(symbiosis->get_number_of_children(), 2);    // 2 `SymbiontMaterial`s.
    ASSERT_EQ(symbiosis->get_number_of_descendants(), 7); // 2 `SymbiontMaterial`s and 5 `SymbiontSpecies`.
}

TEST(symbiosis_must_be_initialized_appropriately, no_universe_no_world_no_scene_no_material_no_shader_turbo_polizei)
{
    yli::ontology::SymbiosisStruct symbiosis_struct;
    symbiosis_struct.parent = nullptr;
    symbiosis_struct.model_filename = "turbo_polizei.fbx";
    symbiosis_struct.model_file_format = "FBX";
    yli::ontology::Symbiosis* const symbiosis = new yli::ontology::Symbiosis(nullptr, symbiosis_struct, nullptr);

    // `Entity` member functions.
    ASSERT_EQ(symbiosis->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(symbiosis->get_type(), "yli::ontology::Symbiosis*");
    ASSERT_TRUE(symbiosis->get_can_be_erased());
    ASSERT_EQ(symbiosis->get_universe(), nullptr);
    ASSERT_NE(symbiosis->get_setting_master(), nullptr);
    ASSERT_EQ(symbiosis->get_parent(), nullptr);
    ASSERT_EQ(symbiosis->get_number_of_children(), 2);    // 2 `SymbiontMaterial`s.
    ASSERT_EQ(symbiosis->get_number_of_descendants(), 7); // 2 `SymbiontMaterial`s and 5 `SymbiontSpecies`.
}

TEST(holobiont_must_be_initialized_appropriately, headless)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    yli::ontology::World* const world = new yli::ontology::World(universe, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(universe, shader_struct);

    yli::ontology::SymbiosisStruct symbiosis_struct;
    symbiosis_struct.parent = shader;
    yli::ontology::Symbiosis* const symbiosis = new yli::ontology::Symbiosis(universe, symbiosis_struct, &shader->parent_of_symbioses);

    yli::ontology::HolobiontStruct holobiont_struct;
    holobiont_struct.symbiosis_parent = symbiosis;
    yli::ontology::Holobiont* const holobiont = new yli::ontology::Holobiont(universe, holobiont_struct, &symbiosis->parent_of_holobionts);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_children(), 1);
    ASSERT_EQ(universe->get_number_of_descendants(), 5);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world->get_number_of_children(), 1);
    ASSERT_EQ(world->get_number_of_descendants(), 4);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_children(), 1);
    ASSERT_EQ(scene->get_number_of_descendants(), 3);

    // `Entity` member functions of `Shader`.
    ASSERT_EQ(shader->get_number_of_children(), 1);
    ASSERT_EQ(shader->get_number_of_descendants(), 2);

    // `Entity` member functions of `Symbiosis`.
    ASSERT_EQ(symbiosis->get_number_of_children(), 1);
    ASSERT_EQ(symbiosis->get_number_of_descendants(), 1);

    // `Entity` member functions.
    ASSERT_EQ(holobiont->get_childID(), 0);
    ASSERT_EQ(holobiont->get_type(), "yli::ontology::Holobiont*");
    ASSERT_TRUE(holobiont->get_can_be_erased());
    ASSERT_EQ(holobiont->get_universe(), universe);
    ASSERT_NE(holobiont->get_setting_master(), nullptr);
    ASSERT_EQ(holobiont->get_parent(), symbiosis);
    ASSERT_EQ(holobiont->get_number_of_children(), 0);
    ASSERT_EQ(holobiont->get_number_of_descendants(), 0);
}

TEST(holobiont_must_be_initialized_appropriately, no_universe_no_world_no_scene_no_shader_no_symbiosis)
{
    yli::ontology::HolobiontStruct holobiont_struct;
    holobiont_struct.symbiosis_parent = nullptr;
    yli::ontology::Holobiont* const holobiont = new yli::ontology::Holobiont(nullptr, holobiont_struct, nullptr);

    // `Entity` member functions.
    ASSERT_EQ(holobiont->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(holobiont->get_type(), "yli::ontology::Holobiont*");
    ASSERT_TRUE(holobiont->get_can_be_erased());
    ASSERT_EQ(holobiont->get_universe(), nullptr);
    ASSERT_NE(holobiont->get_setting_master(), nullptr);
    ASSERT_EQ(holobiont->get_parent(), nullptr);
    ASSERT_EQ(holobiont->get_number_of_children(), 0);
    ASSERT_EQ(holobiont->get_number_of_descendants(), 0);
}

TEST(holobiont_must_be_initialized_appropriately, headless_turbo_polizei)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    yli::ontology::World* const world = new yli::ontology::World(universe, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(universe, shader_struct);

    yli::ontology::SymbiosisStruct symbiosis_struct;
    symbiosis_struct.parent = shader;
    symbiosis_struct.model_filename = "turbo_polizei.fbx";
    symbiosis_struct.model_file_format = "FBX";
    yli::ontology::Symbiosis* const symbiosis = new yli::ontology::Symbiosis(universe, symbiosis_struct, &shader->parent_of_symbioses);

    yli::ontology::HolobiontStruct holobiont_struct;
    holobiont_struct.symbiosis_parent = symbiosis;
    yli::ontology::Holobiont* const holobiont = new yli::ontology::Holobiont(universe, holobiont_struct, &symbiosis->parent_of_holobionts);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_children(), 1);
    ASSERT_EQ(universe->get_number_of_descendants(), 17);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world->get_number_of_children(), 1);
    ASSERT_EQ(world->get_number_of_descendants(), 16);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_children(), 1);
    ASSERT_EQ(scene->get_number_of_descendants(), 15);

    // `Entity` member functions of `Shader`.
    ASSERT_EQ(shader->get_number_of_children(), 1);
    ASSERT_EQ(shader->get_number_of_descendants(), 14);

    // `Entity` member functions of `Symbiosis`.
    ASSERT_EQ(symbiosis->get_number_of_children(), 3);     // 2 `SymbiontMaterial`s and 1 `Holobiont`.
    ASSERT_EQ(symbiosis->get_number_of_descendants(), 13); // 2 `SymbiontMaterial`s, 5 `SymbiontSpecies`, 1 `Holobiont`, and 5 `Biont`s.

    // `Entity` member functions.
    ASSERT_EQ(holobiont->get_childID(), 0);
    ASSERT_EQ(holobiont->get_type(), "yli::ontology::Holobiont*");
    ASSERT_TRUE(holobiont->get_can_be_erased());
    ASSERT_EQ(holobiont->get_universe(), universe);
    ASSERT_NE(holobiont->get_setting_master(), nullptr);
    ASSERT_EQ(holobiont->get_parent(), symbiosis);
    ASSERT_EQ(holobiont->get_number_of_children(), 5);     // 5 `Biont`s.
    ASSERT_EQ(holobiont->get_number_of_descendants(), 5);  // 5 `Biont`s.
}

TEST(holobiont_must_be_initialized_appropriately, no_universe_no_world_no_scene_no_shader_turbo_polizei)
{
    yli::ontology::SymbiosisStruct symbiosis_struct;
    symbiosis_struct.parent = nullptr;
    symbiosis_struct.model_filename = "turbo_polizei.fbx";
    symbiosis_struct.model_file_format = "FBX";
    yli::ontology::Symbiosis* const symbiosis = new yli::ontology::Symbiosis(nullptr, symbiosis_struct, nullptr);

    yli::ontology::HolobiontStruct holobiont_struct;
    holobiont_struct.symbiosis_parent = symbiosis;
    yli::ontology::Holobiont* const holobiont = new yli::ontology::Holobiont(nullptr, holobiont_struct, &symbiosis->parent_of_holobionts);

    // `Entity` member functions of `Symbiosis`.
    ASSERT_EQ(symbiosis->get_number_of_children(), 3);     // 2 `SymbiontMaterial`s and 1 `Holobiont`.
    ASSERT_EQ(symbiosis->get_number_of_descendants(), 13); // 2 `SymbiontMaterial`s, 5 `SymbiontSpecies`, 1 `Holobiont`, and 5 `Biont`s.

    // `Entity` member functions.
    ASSERT_EQ(holobiont->get_childID(), 0);
    ASSERT_EQ(holobiont->get_type(), "yli::ontology::Holobiont*");
    ASSERT_TRUE(holobiont->get_can_be_erased());
    ASSERT_EQ(holobiont->get_universe(), nullptr);
    ASSERT_NE(holobiont->get_setting_master(), nullptr);
    ASSERT_EQ(holobiont->get_parent(), symbiosis);
    ASSERT_EQ(holobiont->get_number_of_children(), 5);     // 5 `Biont`s.
    ASSERT_EQ(holobiont->get_number_of_descendants(), 5);  // 5 `Biont`s.
}

TEST(shapeshifter_transformation_must_be_initialized_appropriately, headless)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    yli::ontology::World* const world = new yli::ontology::World(universe, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(universe, shader_struct);

    yli::ontology::MaterialStruct material_struct;
    material_struct.shader = shader;
    yli::ontology::Material* const material = new yli::ontology::Material(universe, material_struct, &shader->parent_of_materials);

    yli::ontology::SpeciesStruct shapeshifter_transformation_struct;
    shapeshifter_transformation_struct.scene = scene;
    shapeshifter_transformation_struct.shader = shader;
    shapeshifter_transformation_struct.material = material;
    yli::ontology::ShapeshifterTransformation* const shapeshifter_transformation = new yli::ontology::ShapeshifterTransformation(universe, shapeshifter_transformation_struct);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_children(), 1);
    ASSERT_EQ(universe->get_number_of_descendants(), 5);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world->get_number_of_children(), 1);
    ASSERT_EQ(world->get_number_of_descendants(), 4);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_children(), 1);
    ASSERT_EQ(scene->get_number_of_descendants(), 3);

    // `Entity` member functions of `Shader`.
    ASSERT_EQ(shader->get_number_of_children(), 1);
    ASSERT_EQ(shader->get_number_of_descendants(), 2);

    // `Entity` member functions of `Material`.
    ASSERT_EQ(material->get_number_of_children(), 1);
    ASSERT_EQ(material->get_number_of_descendants(), 1);

    // `Entity` member functions.
    ASSERT_EQ(shapeshifter_transformation->get_childID(), 0);
    ASSERT_EQ(shapeshifter_transformation->get_type(), "yli::ontology::ShapeshifterTransformation*");
    ASSERT_TRUE(shapeshifter_transformation->get_can_be_erased());
    ASSERT_EQ(shapeshifter_transformation->get_universe(), universe);
    ASSERT_NE(shapeshifter_transformation->get_setting_master(), nullptr);
    ASSERT_EQ(shapeshifter_transformation->get_parent(), material);
    ASSERT_EQ(shapeshifter_transformation->get_number_of_children(), 0);
    ASSERT_EQ(shapeshifter_transformation->get_number_of_descendants(), 0);
}

TEST(shapeshifter_transformation_must_be_initialized_appropriately, no_universe_no_world_no_scene_no_shader_no_material)
{
    yli::ontology::SpeciesStruct shapeshifter_transformation_struct;
    shapeshifter_transformation_struct.scene = nullptr;
    shapeshifter_transformation_struct.shader = nullptr;
    shapeshifter_transformation_struct.material = nullptr;
    yli::ontology::ShapeshifterTransformation* const shapeshifter_transformation = new yli::ontology::ShapeshifterTransformation(nullptr, shapeshifter_transformation_struct);

    // `Entity` member functions.
    ASSERT_EQ(shapeshifter_transformation->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(shapeshifter_transformation->get_type(), "yli::ontology::ShapeshifterTransformation*");
    ASSERT_TRUE(shapeshifter_transformation->get_can_be_erased());
    ASSERT_EQ(shapeshifter_transformation->get_universe(), nullptr);
    ASSERT_NE(shapeshifter_transformation->get_setting_master(), nullptr);
    ASSERT_EQ(shapeshifter_transformation->get_parent(), nullptr);
    ASSERT_EQ(shapeshifter_transformation->get_number_of_children(), 0);
    ASSERT_EQ(shapeshifter_transformation->get_number_of_descendants(), 0);
}

TEST(shapeshifter_form_must_be_initialized_appropriately, headless)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    yli::ontology::World* const world = new yli::ontology::World(universe, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(universe, shader_struct);

    yli::ontology::MaterialStruct material_struct;
    material_struct.shader = shader;
    yli::ontology::Material* const material = new yli::ontology::Material(universe, material_struct, &shader->parent_of_materials);

    yli::ontology::SpeciesStruct shapeshifter_transformation_struct;
    shapeshifter_transformation_struct.scene = scene;
    shapeshifter_transformation_struct.shader = shader;
    shapeshifter_transformation_struct.material = material;
    yli::ontology::ShapeshifterTransformation* const shapeshifter_transformation = new yli::ontology::ShapeshifterTransformation(universe, shapeshifter_transformation_struct);

    yli::ontology::SpeciesStruct shapeshifter_form_struct;
    shapeshifter_form_struct.shapeshifter_transformation = shapeshifter_transformation;
    yli::ontology::ShapeshifterForm* const shapeshifter_form = new yli::ontology::ShapeshifterForm(universe, shapeshifter_form_struct);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_children(), 1);
    ASSERT_EQ(universe->get_number_of_descendants(), 6);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world->get_number_of_children(), 1);
    ASSERT_EQ(world->get_number_of_descendants(), 5);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_children(), 1);
    ASSERT_EQ(scene->get_number_of_descendants(), 4);

    // `Entity` member functions of `Shader`.
    ASSERT_EQ(shader->get_number_of_children(), 1);
    ASSERT_EQ(shader->get_number_of_descendants(), 3);

    // `Entity` member functions of `Material`.
    ASSERT_EQ(material->get_number_of_children(), 1);
    ASSERT_EQ(material->get_number_of_descendants(), 2);

    // `Entity` member functions of `ShapeshifterTransformation`.
    ASSERT_EQ(shapeshifter_transformation->get_number_of_children(), 1);
    ASSERT_EQ(shapeshifter_transformation->get_number_of_descendants(), 1);

    // `Entity` member functions.
    ASSERT_EQ(shapeshifter_form->get_childID(), 0);
    ASSERT_EQ(shapeshifter_form->get_type(), "yli::ontology::ShapeshifterForm*");
    ASSERT_FALSE(shapeshifter_form->get_can_be_erased());
    ASSERT_EQ(shapeshifter_form->get_universe(), universe);
    ASSERT_NE(shapeshifter_form->get_setting_master(), nullptr);
    ASSERT_EQ(shapeshifter_form->get_parent(), shapeshifter_transformation);
    ASSERT_EQ(shapeshifter_form->get_number_of_children(), 0);
    ASSERT_EQ(shapeshifter_form->get_number_of_descendants(), 0);
}

TEST(shapeshifter_form_must_be_initialized_appropriately, no_universe_no_world_no_scene_no_shader_no_material)
{
    yli::ontology::SpeciesStruct shapeshifter_transformation_struct;
    shapeshifter_transformation_struct.scene = nullptr;
    shapeshifter_transformation_struct.shader = nullptr;
    shapeshifter_transformation_struct.material = nullptr;
    yli::ontology::ShapeshifterTransformation* const shapeshifter_transformation = new yli::ontology::ShapeshifterTransformation(nullptr, shapeshifter_transformation_struct);

    yli::ontology::SpeciesStruct shapeshifter_form_struct;
    shapeshifter_form_struct.scene = nullptr;
    shapeshifter_form_struct.shader = nullptr;
    shapeshifter_form_struct.material = nullptr;
    shapeshifter_form_struct.shapeshifter_transformation = shapeshifter_transformation;
    yli::ontology::ShapeshifterForm* const shapeshifter_form = new yli::ontology::ShapeshifterForm(nullptr, shapeshifter_form_struct);

    // `Entity` member functions.
    ASSERT_EQ(shapeshifter_form->get_childID(), 0);
    ASSERT_EQ(shapeshifter_form->get_type(), "yli::ontology::ShapeshifterForm*");
    ASSERT_FALSE(shapeshifter_form->get_can_be_erased());
    ASSERT_EQ(shapeshifter_form->get_universe(), nullptr);
    ASSERT_NE(shapeshifter_form->get_setting_master(), nullptr);
    ASSERT_EQ(shapeshifter_form->get_parent(), shapeshifter_transformation);
    ASSERT_EQ(shapeshifter_form->get_number_of_children(), 0);
    ASSERT_EQ(shapeshifter_form->get_number_of_descendants(), 0);
}

TEST(shapeshifter_form_must_be_initialized_appropriately, no_universe_no_world_no_scene_no_shader_no_material_no_shapeshifter_transformation)
{
    yli::ontology::SpeciesStruct shapeshifter_form_struct;
    shapeshifter_form_struct.scene = nullptr;
    shapeshifter_form_struct.shader = nullptr;
    shapeshifter_form_struct.material = nullptr;
    shapeshifter_form_struct.shapeshifter_transformation = nullptr;
    yli::ontology::ShapeshifterForm* const shapeshifter_form = new yli::ontology::ShapeshifterForm(nullptr, shapeshifter_form_struct);

    // `Entity` member functions.
    ASSERT_EQ(shapeshifter_form->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(shapeshifter_form->get_type(), "yli::ontology::ShapeshifterForm*");
    ASSERT_FALSE(shapeshifter_form->get_can_be_erased());
    ASSERT_EQ(shapeshifter_form->get_universe(), nullptr);
    ASSERT_NE(shapeshifter_form->get_setting_master(), nullptr);
    ASSERT_EQ(shapeshifter_form->get_parent(), nullptr);
    ASSERT_EQ(shapeshifter_form->get_number_of_children(), 0);
    ASSERT_EQ(shapeshifter_form->get_number_of_descendants(), 0);
}

TEST(shapeshifter_sequence_must_be_initialized_appropriately, headless)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    yli::ontology::World* const world = new yli::ontology::World(universe, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(universe, shader_struct);

    yli::ontology::MaterialStruct material_struct;
    material_struct.shader = shader;
    yli::ontology::Material* const material = new yli::ontology::Material(universe, material_struct, &shader->parent_of_materials);

    yli::ontology::SpeciesStruct shapeshifter_transformation_struct;
    shapeshifter_transformation_struct.scene = scene;
    shapeshifter_transformation_struct.shader = shader;
    shapeshifter_transformation_struct.material = material;
    yli::ontology::ShapeshifterTransformation* const shapeshifter_transformation = new yli::ontology::ShapeshifterTransformation(universe, shapeshifter_transformation_struct);

    yli::ontology::ShapeshifterSequenceStruct shapeshifter_sequence_struct;
    shapeshifter_sequence_struct.parent = shapeshifter_transformation;
    yli::ontology::ShapeshifterSequence* const shapeshifter_sequence = new yli::ontology::ShapeshifterSequence(universe, shapeshifter_sequence_struct);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_children(), 1);
    ASSERT_EQ(universe->get_number_of_descendants(), 6);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world->get_number_of_children(), 1);
    ASSERT_EQ(world->get_number_of_descendants(), 5);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_children(), 1);
    ASSERT_EQ(scene->get_number_of_descendants(), 4);

    // `Entity` member functions of `Shader`.
    ASSERT_EQ(shader->get_number_of_children(), 1);
    ASSERT_EQ(shader->get_number_of_descendants(), 3);

    // `Entity` member functions of `Material`.
    ASSERT_EQ(material->get_number_of_children(), 1);
    ASSERT_EQ(material->get_number_of_descendants(), 2);

    // `Entity` member functions of `ShapeshifterTransformation`.
    ASSERT_EQ(shapeshifter_transformation->get_number_of_children(), 1);
    ASSERT_EQ(shapeshifter_transformation->get_number_of_descendants(), 1);

    // `Entity` member functions.
    ASSERT_EQ(shapeshifter_sequence->get_childID(), 0);
    ASSERT_EQ(shapeshifter_sequence->get_type(), "yli::ontology::ShapeshifterSequence*");
    ASSERT_TRUE(shapeshifter_sequence->get_can_be_erased());
    ASSERT_EQ(shapeshifter_sequence->get_universe(), universe);
    ASSERT_NE(shapeshifter_sequence->get_setting_master(), nullptr);
    ASSERT_EQ(shapeshifter_sequence->get_parent(), shapeshifter_transformation);
    ASSERT_EQ(shapeshifter_sequence->get_number_of_children(), 0);
    ASSERT_EQ(shapeshifter_sequence->get_number_of_descendants(), 0);
}

TEST(shapeshifter_sequence_must_be_initialized_appropriately, no_universe_no_world_no_scene_no_shader_no_material)
{
    yli::ontology::SpeciesStruct shapeshifter_transformation_struct;
    shapeshifter_transformation_struct.scene = nullptr;
    shapeshifter_transformation_struct.shader = nullptr;
    shapeshifter_transformation_struct.material = nullptr;
    yli::ontology::ShapeshifterTransformation* const shapeshifter_transformation = new yli::ontology::ShapeshifterTransformation(nullptr, shapeshifter_transformation_struct);

    yli::ontology::ShapeshifterSequenceStruct shapeshifter_sequence_struct;
    shapeshifter_sequence_struct.parent = shapeshifter_transformation;
    yli::ontology::ShapeshifterSequence* const shapeshifter_sequence = new yli::ontology::ShapeshifterSequence(nullptr, shapeshifter_sequence_struct);

    // `Entity` member functions.
    ASSERT_EQ(shapeshifter_sequence->get_childID(), 0);
    ASSERT_EQ(shapeshifter_sequence->get_type(), "yli::ontology::ShapeshifterSequence*");
    ASSERT_TRUE(shapeshifter_sequence->get_can_be_erased());
    ASSERT_EQ(shapeshifter_sequence->get_universe(), nullptr);
    ASSERT_NE(shapeshifter_sequence->get_setting_master(), nullptr);
    ASSERT_EQ(shapeshifter_sequence->get_parent(), shapeshifter_transformation);
    ASSERT_EQ(shapeshifter_sequence->get_number_of_children(), 0);
    ASSERT_EQ(shapeshifter_sequence->get_number_of_descendants(), 0);
}

TEST(shapeshifter_sequence_must_be_initialized_appropriately, no_universe_no_world_no_scene_no_shader_no_material_no_shapeshifter_transformation)
{
    yli::ontology::ShapeshifterSequenceStruct shapeshifter_sequence_struct;
    shapeshifter_sequence_struct.parent = nullptr;
    yli::ontology::ShapeshifterSequence* const shapeshifter_sequence = new yli::ontology::ShapeshifterSequence(nullptr, shapeshifter_sequence_struct);

    // `Entity` member functions.
    ASSERT_EQ(shapeshifter_sequence->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(shapeshifter_sequence->get_type(), "yli::ontology::ShapeshifterSequence*");
    ASSERT_TRUE(shapeshifter_sequence->get_can_be_erased());
    ASSERT_EQ(shapeshifter_sequence->get_universe(), nullptr);
    ASSERT_NE(shapeshifter_sequence->get_setting_master(), nullptr);
    ASSERT_EQ(shapeshifter_sequence->get_parent(), nullptr);
    ASSERT_EQ(shapeshifter_sequence->get_number_of_children(), 0);
    ASSERT_EQ(shapeshifter_sequence->get_number_of_descendants(), 0);
}

TEST(shapeshifter_form_and_sequence_must_be_initialized_appropriately, headless)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    yli::ontology::World* const world = new yli::ontology::World(universe, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(universe, shader_struct);

    yli::ontology::MaterialStruct material_struct;
    material_struct.shader = shader;
    yli::ontology::Material* const material = new yli::ontology::Material(universe, material_struct, &shader->parent_of_materials);

    yli::ontology::SpeciesStruct shapeshifter_transformation_struct;
    shapeshifter_transformation_struct.scene = scene;
    shapeshifter_transformation_struct.shader = shader;
    shapeshifter_transformation_struct.material = material;
    yli::ontology::ShapeshifterTransformation* const shapeshifter_transformation = new yli::ontology::ShapeshifterTransformation(universe, shapeshifter_transformation_struct);

    yli::ontology::SpeciesStruct shapeshifter_form_struct;
    shapeshifter_form_struct.shapeshifter_transformation = shapeshifter_transformation;
    yli::ontology::ShapeshifterForm* const shapeshifter_form = new yli::ontology::ShapeshifterForm(universe, shapeshifter_form_struct);

    yli::ontology::ShapeshifterSequenceStruct shapeshifter_sequence_struct;
    shapeshifter_sequence_struct.parent = shapeshifter_transformation;
    yli::ontology::ShapeshifterSequence* const shapeshifter_sequence = new yli::ontology::ShapeshifterSequence(universe, shapeshifter_sequence_struct);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_children(), 1);
    ASSERT_EQ(universe->get_number_of_descendants(), 7);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world->get_number_of_children(), 1);
    ASSERT_EQ(world->get_number_of_descendants(), 6);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_children(), 1);
    ASSERT_EQ(scene->get_number_of_descendants(), 5);

    // `Entity` member functions of `Shader`.
    ASSERT_EQ(shader->get_number_of_children(), 1);
    ASSERT_EQ(shader->get_number_of_descendants(), 4);

    // `Entity` member functions of `Material`.
    ASSERT_EQ(material->get_number_of_children(), 1);
    ASSERT_EQ(material->get_number_of_descendants(), 3);

    // `Entity` member functions of `ShapeshifterTransformation`.
    ASSERT_EQ(shapeshifter_transformation->get_number_of_children(), 2);
    ASSERT_EQ(shapeshifter_transformation->get_number_of_descendants(), 2);

    // `Entity` member functions.
    ASSERT_EQ(shapeshifter_form->get_childID(), 0);
    ASSERT_EQ(shapeshifter_form->get_type(), "yli::ontology::ShapeshifterForm*");
    ASSERT_FALSE(shapeshifter_form->get_can_be_erased());
    ASSERT_EQ(shapeshifter_form->get_universe(), universe);
    ASSERT_NE(shapeshifter_form->get_setting_master(), nullptr);
    ASSERT_EQ(shapeshifter_form->get_parent(), shapeshifter_transformation);
    ASSERT_EQ(shapeshifter_form->get_number_of_children(), 0);
    ASSERT_EQ(shapeshifter_form->get_number_of_descendants(), 0);

    // `Entity` member functions.
    ASSERT_EQ(shapeshifter_sequence->get_childID(), 0);
    ASSERT_EQ(shapeshifter_sequence->get_type(), "yli::ontology::ShapeshifterSequence*");
    ASSERT_TRUE(shapeshifter_sequence->get_can_be_erased());
    ASSERT_EQ(shapeshifter_sequence->get_universe(), universe);
    ASSERT_NE(shapeshifter_sequence->get_setting_master(), nullptr);
    ASSERT_EQ(shapeshifter_sequence->get_parent(), shapeshifter_transformation);
    ASSERT_EQ(shapeshifter_sequence->get_number_of_children(), 0);
    ASSERT_EQ(shapeshifter_sequence->get_number_of_descendants(), 0);
}

TEST(shapeshifter_form_and_sequence_must_be_initialized_appropriately, no_universe_no_world_no_scene_no_shader_no_material)
{
    yli::ontology::SpeciesStruct shapeshifter_transformation_struct;
    shapeshifter_transformation_struct.scene = nullptr;
    shapeshifter_transformation_struct.shader = nullptr;
    shapeshifter_transformation_struct.material = nullptr;
    yli::ontology::ShapeshifterTransformation* const shapeshifter_transformation = new yli::ontology::ShapeshifterTransformation(nullptr, shapeshifter_transformation_struct);

    yli::ontology::SpeciesStruct shapeshifter_form_struct;
    shapeshifter_form_struct.scene = nullptr;
    shapeshifter_form_struct.shader = nullptr;
    shapeshifter_form_struct.material = nullptr;
    shapeshifter_form_struct.shapeshifter_transformation = shapeshifter_transformation;
    yli::ontology::ShapeshifterForm* const shapeshifter_form = new yli::ontology::ShapeshifterForm(nullptr, shapeshifter_form_struct);

    yli::ontology::ShapeshifterSequenceStruct shapeshifter_sequence_struct;
    shapeshifter_sequence_struct.parent = shapeshifter_transformation;
    yli::ontology::ShapeshifterSequence* const shapeshifter_sequence = new yli::ontology::ShapeshifterSequence(nullptr, shapeshifter_sequence_struct);

    // `Entity` member functions of `ShapeshifterTransformation`.
    ASSERT_EQ(shapeshifter_transformation->get_number_of_children(), 2);
    ASSERT_EQ(shapeshifter_transformation->get_number_of_descendants(), 2);

    // `Entity` member functions.
    ASSERT_EQ(shapeshifter_form->get_childID(), 0);
    ASSERT_EQ(shapeshifter_form->get_type(), "yli::ontology::ShapeshifterForm*");
    ASSERT_FALSE(shapeshifter_form->get_can_be_erased());
    ASSERT_EQ(shapeshifter_form->get_universe(), nullptr);
    ASSERT_NE(shapeshifter_form->get_setting_master(), nullptr);
    ASSERT_EQ(shapeshifter_form->get_parent(), shapeshifter_transformation);
    ASSERT_EQ(shapeshifter_form->get_number_of_children(), 0);
    ASSERT_EQ(shapeshifter_form->get_number_of_descendants(), 0);

    // `Entity` member functions.
    ASSERT_EQ(shapeshifter_sequence->get_childID(), 0);
    ASSERT_EQ(shapeshifter_sequence->get_type(), "yli::ontology::ShapeshifterSequence*");
    ASSERT_TRUE(shapeshifter_sequence->get_can_be_erased());
    ASSERT_EQ(shapeshifter_sequence->get_universe(), nullptr);
    ASSERT_NE(shapeshifter_sequence->get_setting_master(), nullptr);
    ASSERT_EQ(shapeshifter_sequence->get_parent(), shapeshifter_transformation);
    ASSERT_EQ(shapeshifter_sequence->get_number_of_children(), 0);
    ASSERT_EQ(shapeshifter_sequence->get_number_of_descendants(), 0);
}

TEST(shapeshifter_object_must_be_initialized_appropriately, headless)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    yli::ontology::World* const world = new yli::ontology::World(universe, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(universe, shader_struct);

    yli::ontology::MaterialStruct material_struct;
    material_struct.shader = shader;
    yli::ontology::Material* const material = new yli::ontology::Material(universe, material_struct, &shader->parent_of_materials);

    yli::ontology::SpeciesStruct shapeshifter_transformation_struct;
    shapeshifter_transformation_struct.scene = scene;
    shapeshifter_transformation_struct.shader = shader;
    shapeshifter_transformation_struct.material = material;
    yli::ontology::ShapeshifterTransformation* const shapeshifter_transformation = new yli::ontology::ShapeshifterTransformation(universe, shapeshifter_transformation_struct);

    yli::ontology::SpeciesStruct shapeshifter_form_struct;
    shapeshifter_form_struct.shapeshifter_transformation = shapeshifter_transformation;
    yli::ontology::ShapeshifterForm* const shapeshifter_form = new yli::ontology::ShapeshifterForm(universe, shapeshifter_form_struct);

    yli::ontology::ShapeshifterSequenceStruct shapeshifter_sequence_struct;
    shapeshifter_sequence_struct.parent = shapeshifter_transformation;
    yli::ontology::ShapeshifterSequence* const shapeshifter_sequence = new yli::ontology::ShapeshifterSequence(universe, shapeshifter_sequence_struct);

    yli::ontology::ObjectStruct object_struct;
    object_struct.shapeshifter_sequence_parent = shapeshifter_sequence;
    object_struct.object_type = yli::ontology::ObjectType::SHAPESHIFTER;
    yli::ontology::Object* const object = new yli::ontology::Object(universe, object_struct);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_children(), 1);
    ASSERT_EQ(universe->get_number_of_descendants(), 8);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world->get_number_of_children(), 1);
    ASSERT_EQ(world->get_number_of_descendants(), 7);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_children(), 1);
    ASSERT_EQ(scene->get_number_of_descendants(), 6);

    // `Entity` member functions of `Shader`.
    ASSERT_EQ(shader->get_number_of_children(), 1);
    ASSERT_EQ(shader->get_number_of_descendants(), 5);

    // `Entity` member functions of `Material`.
    ASSERT_EQ(material->get_number_of_children(), 1);
    ASSERT_EQ(material->get_number_of_descendants(), 4);

    // `Entity` member functions of `ShapeshifterTransformation`.
    ASSERT_EQ(shapeshifter_transformation->get_number_of_children(), 2);
    ASSERT_EQ(shapeshifter_transformation->get_number_of_descendants(), 3);

    // `Entity` member functions of `ShapeshifterForm`.
    ASSERT_EQ(shapeshifter_form->get_number_of_children(), 0);
    ASSERT_EQ(shapeshifter_form->get_number_of_descendants(), 0);

    // `Entity` member functions of `ShapeshifterSequence`.
    ASSERT_EQ(shapeshifter_sequence->get_number_of_children(), 1);
    ASSERT_EQ(shapeshifter_sequence->get_number_of_descendants(), 1);

    // `Entity` member functions.
    ASSERT_EQ(object->get_childID(), 0);
    ASSERT_EQ(object->get_type(), "yli::ontology::Object*");
    ASSERT_TRUE(object->get_can_be_erased());
    ASSERT_EQ(object->get_universe(), universe);
    ASSERT_NE(object->get_setting_master(), nullptr);
    ASSERT_EQ(object->get_parent(), shapeshifter_sequence);
    ASSERT_EQ(object->get_number_of_children(), 0);
    ASSERT_EQ(object->get_number_of_descendants(), 0);
}

TEST(shapeshifter_object_must_be_initialized_appropriately, no_universe_no_world_no_scene_no_shader_no_material)
{
    yli::ontology::SpeciesStruct shapeshifter_transformation_struct;
    shapeshifter_transformation_struct.scene = nullptr;
    shapeshifter_transformation_struct.shader = nullptr;
    shapeshifter_transformation_struct.material = nullptr;
    yli::ontology::ShapeshifterTransformation* const shapeshifter_transformation = new yli::ontology::ShapeshifterTransformation(nullptr, shapeshifter_transformation_struct);

    yli::ontology::SpeciesStruct shapeshifter_form_struct;
    shapeshifter_form_struct.scene = nullptr;
    shapeshifter_form_struct.shader = nullptr;
    shapeshifter_form_struct.material = nullptr;
    shapeshifter_form_struct.shapeshifter_transformation = shapeshifter_transformation;
    yli::ontology::ShapeshifterForm* const shapeshifter_form = new yli::ontology::ShapeshifterForm(nullptr, shapeshifter_form_struct);

    yli::ontology::ShapeshifterSequenceStruct shapeshifter_sequence_struct;
    shapeshifter_sequence_struct.parent = shapeshifter_transformation;
    yli::ontology::ShapeshifterSequence* const shapeshifter_sequence = new yli::ontology::ShapeshifterSequence(nullptr, shapeshifter_sequence_struct);

    yli::ontology::ObjectStruct object_struct;
    object_struct.shapeshifter_sequence_parent = shapeshifter_sequence;
    object_struct.object_type = yli::ontology::ObjectType::SHAPESHIFTER;
    yli::ontology::Object* const object = new yli::ontology::Object(nullptr, object_struct);

    // `Entity` member functions of `ShapeshifterTransformation`.
    ASSERT_EQ(shapeshifter_transformation->get_number_of_children(), 2);
    ASSERT_EQ(shapeshifter_transformation->get_number_of_descendants(), 3);

    // `Entity` member functions of `ShapeshifterForm`.
    ASSERT_EQ(shapeshifter_form->get_number_of_children(), 0);
    ASSERT_EQ(shapeshifter_form->get_number_of_descendants(), 0);

    // `Entity` member functions of `ShapeshifterSequence`.
    ASSERT_EQ(shapeshifter_sequence->get_number_of_children(), 1);
    ASSERT_EQ(shapeshifter_sequence->get_number_of_descendants(), 1);

    // `Entity` member functions.
    ASSERT_EQ(object->get_childID(), 0);
    ASSERT_EQ(object->get_type(), "yli::ontology::Object*");
    ASSERT_TRUE(object->get_can_be_erased());
    ASSERT_EQ(object->get_universe(), nullptr);
    ASSERT_NE(object->get_setting_master(), nullptr);
    ASSERT_EQ(object->get_parent(), shapeshifter_sequence);
    ASSERT_EQ(object->get_number_of_children(), 0);
    ASSERT_EQ(object->get_number_of_descendants(), 0);
}

TEST(shapeshifter_object_must_be_initialized_appropriately, no_universe_no_world_no_scene_no_shader_no_material_no_shapeshifter_transformation)
{
    yli::ontology::SpeciesStruct shapeshifter_form_struct;
    shapeshifter_form_struct.scene = nullptr;
    shapeshifter_form_struct.shader = nullptr;
    shapeshifter_form_struct.material = nullptr;
    shapeshifter_form_struct.shapeshifter_transformation = nullptr;
    yli::ontology::ShapeshifterForm* const shapeshifter_form = new yli::ontology::ShapeshifterForm(nullptr, shapeshifter_form_struct);

    yli::ontology::ShapeshifterSequenceStruct shapeshifter_sequence_struct;
    shapeshifter_sequence_struct.parent = nullptr;
    yli::ontology::ShapeshifterSequence* const shapeshifter_sequence = new yli::ontology::ShapeshifterSequence(nullptr, shapeshifter_sequence_struct);

    yli::ontology::ObjectStruct object_struct;
    object_struct.shapeshifter_sequence_parent = shapeshifter_sequence;
    object_struct.object_type = yli::ontology::ObjectType::SHAPESHIFTER;
    yli::ontology::Object* const object = new yli::ontology::Object(nullptr, object_struct);

    // `Entity` member functions.
    ASSERT_EQ(object->get_childID(), 0);
    ASSERT_EQ(object->get_type(), "yli::ontology::Object*");
    ASSERT_TRUE(object->get_can_be_erased());
    ASSERT_EQ(object->get_universe(), nullptr);
    ASSERT_NE(object->get_setting_master(), nullptr);
    ASSERT_EQ(object->get_parent(), shapeshifter_sequence);
    ASSERT_EQ(object->get_number_of_children(), 0);
    ASSERT_EQ(object->get_number_of_descendants(), 0);
}

TEST(brain_must_be_initialized_appropriately, headless)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    yli::ontology::World* const world = new yli::ontology::World(universe, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);

    yli::ontology::BrainStruct brain_struct;
    brain_struct.parent = scene;
    yli::ontology::Brain* const brain = new yli::ontology::Brain(universe, brain_struct, &scene->parent_of_brains);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_children(), 1);
    ASSERT_EQ(universe->get_number_of_descendants(), 3);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world->get_number_of_children(), 1);
    ASSERT_EQ(world->get_number_of_descendants(), 2);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_children(), 1);
    ASSERT_EQ(scene->get_number_of_descendants(), 1);

    // `Brain` member functions.
    ASSERT_EQ(brain->get_number_of_apprentices(), 0);

    // `Entity` member functions.
    ASSERT_EQ(brain->get_childID(), 0);
    ASSERT_EQ(brain->get_type(), "yli::ontology::Brain*");
    ASSERT_TRUE(brain->get_can_be_erased());
    ASSERT_EQ(brain->get_universe(), universe);
    ASSERT_NE(brain->get_setting_master(), nullptr);
    ASSERT_EQ(brain->get_parent(), scene);
    ASSERT_EQ(brain->get_number_of_children(), 0);
    ASSERT_EQ(brain->get_number_of_descendants(), 0);
}

TEST(font2D_must_be_initialized_appropriately, headless)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::FontStruct font_struct;
    font_struct.screen_width = universe->get_window_width();
    font_struct.screen_height = universe->get_window_height();
    font_struct.text_size = universe->get_text_size();
    font_struct.font_size = universe->get_font_size();
    yli::ontology::Font2D* const font2D = new yli::ontology::Font2D(universe, font_struct, &universe->parent_of_font2Ds);

    // `Universe` member functions.
    ASSERT_EQ(universe->get_number_of_worlds(), 0);
    ASSERT_EQ(universe->get_active_scene(), nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_children(), 1);
    ASSERT_EQ(universe->get_number_of_descendants(), 1);

    // `Entity` member functions of `Font2D`.
    ASSERT_EQ(font2D->get_childID(), 0);
    ASSERT_EQ(font2D->get_type(), "yli::ontology::Font2D*");
    ASSERT_FALSE(font2D->get_can_be_erased());               // Currently `Font2D`s can not be erased.
    ASSERT_EQ(font2D->get_universe(), universe);
    ASSERT_NE(font2D->get_setting_master(), nullptr);
    ASSERT_EQ(font2D->get_parent(), universe);
    ASSERT_EQ(font2D->get_number_of_children(), 0);
    ASSERT_EQ(font2D->get_number_of_descendants(), 0);
}

TEST(font2D_must_be_initialized_appropriately, no_universe)
{
    yli::ontology::FontStruct font_struct;
    yli::ontology::Font2D* const font2D = new yli::ontology::Font2D(nullptr, font_struct, nullptr);

    // `Entity` member functions of `World`.
    ASSERT_EQ(font2D->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(font2D->get_type(), "yli::ontology::Font2D*");
    ASSERT_FALSE(font2D->get_can_be_erased());               // Currently `Font2D`s can not be erased.
    ASSERT_EQ(font2D->get_universe(), nullptr);
    ASSERT_NE(font2D->get_setting_master(), nullptr);
    ASSERT_EQ(font2D->get_parent(), nullptr);
    ASSERT_EQ(font2D->get_number_of_children(), 0);
    ASSERT_EQ(font2D->get_number_of_descendants(), 0);
}

TEST(font2D_must_be_initialized_appropriately, headless_holstein)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::FontStruct font_struct;
    font_struct.texture_filename = "Holstein.bmp";
    font_struct.font_texture_file_format = "BMP";
    font_struct.screen_width = universe->get_window_width();
    font_struct.screen_height = universe->get_window_height();
    font_struct.text_size = universe->get_text_size();
    font_struct.font_size = universe->get_font_size();
    yli::ontology::Font2D* const font2D = new yli::ontology::Font2D(universe, font_struct, &universe->parent_of_font2Ds);

    // `Universe` member functions.
    ASSERT_EQ(universe->get_number_of_worlds(), 0);
    ASSERT_EQ(universe->get_active_scene(), nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_children(), 1);
    ASSERT_EQ(universe->get_number_of_descendants(), 1);

    // `Entity` member functions of `Font2D`.
    ASSERT_EQ(font2D->get_childID(), 0);
    ASSERT_EQ(font2D->get_type(), "yli::ontology::Font2D*");
    ASSERT_FALSE(font2D->get_can_be_erased());               // Currently `Font2D`s can not be erased.
    ASSERT_EQ(font2D->get_universe(), universe);
    ASSERT_NE(font2D->get_setting_master(), nullptr);
    ASSERT_EQ(font2D->get_parent(), universe);
    ASSERT_EQ(font2D->get_number_of_children(), 0);
    ASSERT_EQ(font2D->get_number_of_descendants(), 0);
}

TEST(font2D_must_be_initialized_appropriately, no_universe_holstein)
{
    yli::ontology::FontStruct font_struct;
    font_struct.texture_filename = "Holstein.bmp";
    font_struct.font_texture_file_format = "BMP";
    yli::ontology::Font2D* const font2D = new yli::ontology::Font2D(nullptr, font_struct, nullptr);

    // `Entity` member functions of `World`.
    ASSERT_EQ(font2D->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(font2D->get_type(), "yli::ontology::Font2D*");
    ASSERT_FALSE(font2D->get_can_be_erased());               // Currently `Font2D`s can not be erased.
    ASSERT_EQ(font2D->get_universe(), nullptr);
    ASSERT_NE(font2D->get_setting_master(), nullptr);
    ASSERT_EQ(font2D->get_parent(), nullptr);
    ASSERT_EQ(font2D->get_number_of_children(), 0);
    ASSERT_EQ(font2D->get_number_of_descendants(), 0);
}

TEST(brain_must_be_initialized_appropriately, no_universe_no_world_no_scene)
{
    yli::ontology::BrainStruct brain_struct;
    brain_struct.parent = nullptr;
    yli::ontology::Brain* const brain = new yli::ontology::Brain(nullptr, brain_struct, nullptr);

    // `Brain` member functions.
    ASSERT_EQ(brain->get_number_of_apprentices(), 0);

    // `Entity` member functions.
    ASSERT_EQ(brain->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(brain->get_type(), "yli::ontology::Brain*");
    ASSERT_TRUE(brain->get_can_be_erased());
    ASSERT_EQ(brain->get_universe(), nullptr);
    ASSERT_NE(brain->get_setting_master(), nullptr);
    ASSERT_EQ(brain->get_parent(), nullptr);
    ASSERT_EQ(brain->get_number_of_children(), 0);
    ASSERT_EQ(brain->get_number_of_descendants(), 0);
}

TEST(scene_must_be_activated_appropriately, scene)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    yli::ontology::World* const world = new yli::ontology::World(universe, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);

    ASSERT_EQ(universe->get_active_scene(), nullptr);
    universe->set_active_scene(scene);
    ASSERT_EQ(universe->get_active_scene(), scene);
}

TEST(scene_must_bind_to_worlds_appropriately, scene)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    yli::ontology::World* const world1 = new yli::ontology::World(universe, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world1;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world1->parent_of_scenes);
    ASSERT_EQ(scene->get_parent(), world1);
    ASSERT_EQ(world1->get_number_of_children(), 1);

    yli::ontology::World* const world2 = new yli::ontology::World(universe, &universe->parent_of_worlds);
    ASSERT_EQ(scene->get_parent(), world1);
    ASSERT_EQ(world2->get_number_of_children(), 0);

    scene->bind_to_new_parent(world2);
    ASSERT_EQ(scene->get_parent(), world2);
    ASSERT_EQ(world1->get_number_of_children(), 0);
    ASSERT_EQ(world1->get_number_of_descendants(), 0);
    ASSERT_EQ(world2->get_number_of_children(), 1);
    ASSERT_EQ(world2->get_number_of_descendants(), 1);
    ASSERT_EQ(universe->get_number_of_children(), 2);
    ASSERT_EQ(universe->get_number_of_descendants(), 3);
}

TEST(active_scene_must_remain_active_scene_after_binding_to_a_new_parent, scene)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    yli::ontology::World* const world1 = new yli::ontology::World(universe, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world1;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world1->parent_of_scenes);
    universe->set_active_scene(scene);
    ASSERT_EQ(universe->get_active_scene(), scene);

    yli::ontology::World* const world2 = new yli::ontology::World(universe, &universe->parent_of_worlds);
    scene->bind_to_new_parent(world2);
    ASSERT_EQ(universe->get_active_scene(), scene);
    ASSERT_EQ(scene->get_parent(), world2);
    ASSERT_EQ(world1->get_number_of_children(), 0);
    ASSERT_EQ(world1->get_number_of_descendants(), 0);
    ASSERT_EQ(world2->get_number_of_children(), 1);
    ASSERT_EQ(world2->get_number_of_descendants(), 1);
    ASSERT_EQ(universe->get_number_of_children(), 2);
    ASSERT_EQ(universe->get_number_of_descendants(), 3);
}

TEST(inactive_scene_must_remain_inactive_scene_after_binding_to_a_new_parent, scene)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    yli::ontology::World* const world1 = new yli::ontology::World(universe, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world1;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world1->parent_of_scenes);
    ASSERT_EQ(universe->get_active_scene(), nullptr);

    yli::ontology::World* const world2 = new yli::ontology::World(universe, &universe->parent_of_worlds);
    scene->bind_to_new_parent(world2);
    ASSERT_EQ(universe->get_active_scene(), nullptr);
    ASSERT_EQ(scene->get_parent(), world2);
    ASSERT_EQ(world1->get_number_of_children(), 0);
    ASSERT_EQ(world1->get_number_of_descendants(), 0);
    ASSERT_EQ(world2->get_number_of_children(), 1);
    ASSERT_EQ(world2->get_number_of_descendants(), 1);
    ASSERT_EQ(universe->get_number_of_children(), 2);
    ASSERT_EQ(universe->get_number_of_descendants(), 3);
}

TEST(shader_must_bind_to_scene_appropriately, scenes_of_the_same_world)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    yli::ontology::World* const world = new yli::ontology::World(universe, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene1 = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene1;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(universe, shader_struct);
    ASSERT_EQ(shader->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_children(), 1);

    yli::ontology::Scene* const scene2 = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);
    ASSERT_EQ(shader->get_parent(), scene1);
    ASSERT_EQ(scene2->get_number_of_children(), 0);

    shader->bind_to_new_parent(scene2);
    ASSERT_EQ(shader->get_parent(), scene2);
    ASSERT_EQ(scene1->get_number_of_children(), 0);
    ASSERT_EQ(scene1->get_number_of_descendants(), 0);
    ASSERT_EQ(scene2->get_number_of_children(), 1);
    ASSERT_EQ(scene2->get_number_of_descendants(), 1);
    ASSERT_EQ(world->get_number_of_children(), 2);
    ASSERT_EQ(world->get_number_of_descendants(), 3);
    ASSERT_EQ(universe->get_number_of_children(), 1);
    ASSERT_EQ(universe->get_number_of_descendants(), 4);
}

TEST(shader_must_bind_to_scene_appropriately, scenes_of_the_different_worlds)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    yli::ontology::World* const world1 = new yli::ontology::World(universe, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct1;
    scene_struct1.world = world1;
    yli::ontology::Scene* const scene1 = new yli::ontology::Scene(universe, scene_struct1, &world1->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene1;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(universe, shader_struct);
    ASSERT_EQ(shader->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_children(), 1);
    ASSERT_EQ(scene1->get_number_of_descendants(), 1);

    yli::ontology::World* const world2 = new yli::ontology::World(universe, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct2;
    scene_struct2.world = world2;
    yli::ontology::Scene* const scene2 = new yli::ontology::Scene(universe, scene_struct2, &world2->parent_of_scenes);
    ASSERT_EQ(shader->get_parent(), scene1);
    ASSERT_EQ(world2->get_number_of_children(), 1);
    ASSERT_EQ(world2->get_number_of_descendants(), 1);
    ASSERT_EQ(scene2->get_number_of_children(), 0);
    ASSERT_EQ(scene2->get_number_of_descendants(), 0);

    shader->bind_to_new_parent(scene2);
    ASSERT_EQ(shader->get_parent(), scene2);
    ASSERT_EQ(scene1->get_number_of_children(), 0);
    ASSERT_EQ(scene1->get_number_of_descendants(), 0);
    ASSERT_EQ(scene2->get_number_of_children(), 1);
    ASSERT_EQ(scene2->get_number_of_descendants(), 1);
    ASSERT_EQ(world1->get_number_of_children(), 1);
    ASSERT_EQ(world1->get_number_of_descendants(), 1);
    ASSERT_EQ(world2->get_number_of_children(), 1);
    ASSERT_EQ(world2->get_number_of_descendants(), 2);
    ASSERT_EQ(universe->get_number_of_children(), 2);
    ASSERT_EQ(universe->get_number_of_descendants(), 5);
}

TEST(material_must_bind_to_shader_appropriately, shaders_of_the_same_scene)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    yli::ontology::World* const world = new yli::ontology::World(universe, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct1;
    scene_struct1.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct1, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct1;
    shader_struct1.parent = scene;
    yli::ontology::Shader* const shader1 = new yli::ontology::Shader(universe, shader_struct1);
    ASSERT_EQ(shader1->get_number_of_children(), 0);
    ASSERT_EQ(shader1->get_number_of_descendants(), 0);

    yli::ontology::MaterialStruct material_struct;
    material_struct.shader = shader1;
    yli::ontology::Material* const material = new yli::ontology::Material(universe, material_struct, &shader1->parent_of_materials);
    ASSERT_EQ(material->get_parent(), shader1);
    ASSERT_EQ(shader1->get_number_of_children(), 1);
    ASSERT_EQ(shader1->get_number_of_descendants(), 1);

    yli::ontology::ShaderStruct shader_struct2;
    shader_struct2.parent = scene;
    yli::ontology::Shader* const shader2 = new yli::ontology::Shader(universe, shader_struct2);
    ASSERT_EQ(shader2->get_number_of_children(), 0);
    ASSERT_EQ(shader2->get_number_of_descendants(), 0);

    material->bind_to_new_parent(shader2);
    ASSERT_EQ(material->get_parent(), shader2);
    ASSERT_EQ(shader1->get_number_of_children(), 0);
    ASSERT_EQ(shader1->get_number_of_descendants(), 0);
    ASSERT_EQ(shader2->get_number_of_children(), 1);
    ASSERT_EQ(shader2->get_number_of_descendants(), 1);
    ASSERT_EQ(scene->get_number_of_children(), 2);
    ASSERT_EQ(scene->get_number_of_descendants(), 3);
    ASSERT_EQ(world->get_number_of_children(), 1);
    ASSERT_EQ(world->get_number_of_descendants(), 4);
    ASSERT_EQ(universe->get_number_of_children(), 1);
    ASSERT_EQ(universe->get_number_of_descendants(), 5);
}

TEST(material_must_bind_to_shader_appropriately, shaders_of_different_scenes)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    yli::ontology::World* const world = new yli::ontology::World(universe, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct1;
    scene_struct1.world = world;
    yli::ontology::Scene* const scene1 = new yli::ontology::Scene(universe, scene_struct1, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct1;
    shader_struct1.parent = scene1;
    yli::ontology::Shader* const shader1 = new yli::ontology::Shader(universe, shader_struct1);
    ASSERT_EQ(shader1->get_number_of_children(), 0);
    ASSERT_EQ(shader1->get_number_of_descendants(), 0);

    yli::ontology::MaterialStruct material_struct;
    material_struct.shader = shader1;
    yli::ontology::Material* const material = new yli::ontology::Material(universe, material_struct, &shader1->parent_of_materials);
    ASSERT_EQ(material->get_parent(), shader1);
    ASSERT_EQ(shader1->get_number_of_children(), 1);
    ASSERT_EQ(shader1->get_number_of_descendants(), 1);

    yli::ontology::SceneStruct scene_struct2;
    scene_struct2.world = world;
    yli::ontology::Scene* const scene2 = new yli::ontology::Scene(universe, scene_struct2, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct2;
    shader_struct2.parent = scene2;
    yli::ontology::Shader* const shader2 = new yli::ontology::Shader(universe, shader_struct2);
    ASSERT_EQ(shader2->get_number_of_children(), 0);
    ASSERT_EQ(shader2->get_number_of_descendants(), 0);

    material->bind_to_new_parent(shader2);
    ASSERT_EQ(material->get_parent(), shader2);
    ASSERT_EQ(shader1->get_number_of_children(), 0);
    ASSERT_EQ(shader1->get_number_of_descendants(), 0);
    ASSERT_EQ(shader2->get_number_of_children(), 1);
    ASSERT_EQ(shader2->get_number_of_descendants(), 1);
    ASSERT_EQ(scene1->get_number_of_children(), 1);
    ASSERT_EQ(scene1->get_number_of_descendants(), 1);
    ASSERT_EQ(scene2->get_number_of_children(), 1);
    ASSERT_EQ(scene2->get_number_of_descendants(), 2);
    ASSERT_EQ(world->get_number_of_children(), 2);
    ASSERT_EQ(world->get_number_of_descendants(), 5);
    ASSERT_EQ(universe->get_number_of_children(), 1);
    ASSERT_EQ(universe->get_number_of_descendants(), 6);
}

TEST(object_must_bind_to_brain_appropriately, master_and_apprentice)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    yli::ontology::World* const world = new yli::ontology::World(universe, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);

    yli::ontology::BrainStruct brain_struct;
    brain_struct.parent = scene;
    yli::ontology::Brain* const brain = new yli::ontology::Brain(universe, brain_struct, &scene->parent_of_brains);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(universe, shader_struct);

    yli::ontology::MaterialStruct material_struct;
    material_struct.shader = shader;
    yli::ontology::Material* const material = new yli::ontology::Material(universe, material_struct, &shader->parent_of_materials);

    yli::ontology::SpeciesStruct species_struct;
    species_struct.scene = scene;
    species_struct.shader = shader;
    species_struct.material = material;
    yli::ontology::Species* const species = new yli::ontology::Species(universe, species_struct);

    yli::ontology::ObjectStruct object_struct;
    object_struct.species_parent = species;
    yli::ontology::Object* const object = new yli::ontology::Object(universe, object_struct);

    ASSERT_EQ(brain->get_number_of_apprentices(), 0);
    object->bind_to_new_Brain(brain);
    ASSERT_EQ(brain->get_number_of_apprentices(), 1);
}
