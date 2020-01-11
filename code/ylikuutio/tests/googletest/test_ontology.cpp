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
#include "code/ylikuutio/ontology/brain.hpp"
#include "code/ylikuutio/ontology/universe_struct.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/shader_struct.hpp"
#include "code/ylikuutio/ontology/material_struct.hpp"
#include "code/ylikuutio/ontology/species_struct.hpp"
#include "code/ylikuutio/ontology/object_struct.hpp"
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

TEST(world_must_be_initialized_appropriately, world)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::World* const world = new yli::ontology::World(universe);

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

TEST(scene_must_be_initialized_appropriately, scene)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    yli::ontology::World* const world = new yli::ontology::World(universe);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct);

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

TEST(shader_must_be_initialized_appropriately, shader)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    yli::ontology::World* const world = new yli::ontology::World(universe);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct);

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

TEST(material_must_be_initialized_appropriately, material)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    yli::ontology::World* const world = new yli::ontology::World(universe);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(universe, shader_struct);

    yli::ontology::MaterialStruct material_struct;
    material_struct.shader = shader;
    yli::ontology::Material* const material = new yli::ontology::Material(universe, material_struct);

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

TEST(species_must_be_initialized_appropriately, species)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    yli::ontology::World* const world = new yli::ontology::World(universe);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(universe, shader_struct);

    yli::ontology::MaterialStruct material_struct;
    material_struct.shader = shader;
    yli::ontology::Material* const material = new yli::ontology::Material(universe, material_struct);

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

TEST(object_must_be_initialized_appropriately, object)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    yli::ontology::World* const world = new yli::ontology::World(universe);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(universe, shader_struct);

    yli::ontology::MaterialStruct material_struct;
    material_struct.shader = shader;
    yli::ontology::Material* const material = new yli::ontology::Material(universe, material_struct);

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

TEST(brain_must_be_initialized_appropriately, brain)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    yli::ontology::World* const world = new yli::ontology::World(universe);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct);

    yli::ontology::BrainStruct brain_struct;
    brain_struct.parent = scene;
    yli::ontology::Brain* const brain = new yli::ontology::Brain(universe, brain_struct);

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

TEST(scene_must_be_activated_appropriately, scene)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    yli::ontology::World* const world = new yli::ontology::World(universe);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct);

    ASSERT_EQ(universe->get_active_scene(), nullptr);
    universe->set_active_scene(scene);
    ASSERT_EQ(universe->get_active_scene(), scene);
}

TEST(scene_must_be_bound_to_worlds_appropriately, scene)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    yli::ontology::World* const world1 = new yli::ontology::World(universe);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world1;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct);
    ASSERT_EQ(scene->get_parent(), world1);
    ASSERT_EQ(world1->get_number_of_children(), 1);

    yli::ontology::World* const world2 = new yli::ontology::World(universe);
    ASSERT_EQ(world2->get_number_of_children(), 0);

    scene->bind_to_new_parent(world2);
    ASSERT_EQ(scene->get_parent(), world2);
    ASSERT_EQ(world1->get_number_of_children(), 0);
    ASSERT_EQ(world2->get_number_of_children(), 1);
}

TEST(active_scene_must_remain_active_scene_after_binding_to_a_new_parent, scene)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    yli::ontology::World* const world1 = new yli::ontology::World(universe);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world1;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct);
    universe->set_active_scene(scene);
    ASSERT_EQ(universe->get_active_scene(), scene);

    yli::ontology::World* const world2 = new yli::ontology::World(universe);
    scene->bind_to_new_parent(world2);
    ASSERT_EQ(universe->get_active_scene(), scene);
}

TEST(inactive_scene_must_remain_inactive_scene_after_binding_to_a_new_parent, scene)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    yli::ontology::World* const world1 = new yli::ontology::World(universe);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world1;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct);
    ASSERT_EQ(universe->get_active_scene(), nullptr);

    yli::ontology::World* const world2 = new yli::ontology::World(universe);
    scene->bind_to_new_parent(world2);
    ASSERT_EQ(universe->get_active_scene(), nullptr);
}
