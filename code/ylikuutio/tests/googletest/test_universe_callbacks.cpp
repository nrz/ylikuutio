// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
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
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/ontology/entity.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/world.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/shader.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/camera.hpp"
#include "code/ylikuutio/ontology/font2D.hpp"
#include "code/ylikuutio/ontology/console.hpp"
#include "code/ylikuutio/ontology/universe_struct.hpp"
#include "code/ylikuutio/ontology/world_struct.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/shader_struct.hpp"
#include "code/ylikuutio/ontology/material_struct.hpp"
#include "code/ylikuutio/ontology/species_struct.hpp"
#include "code/ylikuutio/ontology/object_struct.hpp"
#include "code/ylikuutio/ontology/camera_struct.hpp"
#include "code/ylikuutio/ontology/console_struct.hpp"

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string, std::getline
#include <variant>  // std::holds_alternative, std::variant
#include <vector>   // std::vector

// Tests for `yli::ontology::Universe` callbacks
// that can be tested in headless mode.

namespace yli::ontology
{
    class Entity;
    class Console;
}

// Public `Entity` bind callbacks.

TEST(object_must_be_bound_to_species_appropriately, universe_callback)
{
    yli::ontology::Console* const console = nullptr;

    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(universe, world_struct, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(universe, shader_struct);

    yli::ontology::Material* const material = new yli::ontology::Material(universe, yli::ontology::MaterialStruct(), &shader->parent_of_materials);

    const std::string species1_name = "foo";

    yli::ontology::SpeciesStruct species1_struct;
    species1_struct.scene = scene;
    species1_struct.shader = shader;
    species1_struct.material = material;
    yli::ontology::Species* const species1 = new yli::ontology::Species(universe, species1_struct, &material->parent_of_species);
    species1->set_global_name(species1_name);

    const std::string object_name = "bar";

    yli::ontology::ObjectStruct object_struct;
    object_struct.species_parent = species1;
    yli::ontology::Object* const object = new yli::ontology::Object(universe, object_struct, &species1->parent_of_objects);
    object->set_global_name(object_name);

    const std::string species2_name = "baz";

    yli::ontology::SpeciesStruct species2_struct;
    species2_struct.scene = scene;
    species2_struct.shader = shader;
    species2_struct.material = material;
    yli::ontology::Species* const species2 = new yli::ontology::Species(universe, species2_struct, &material->parent_of_species);
    species2->set_global_name(species2_name);

    ASSERT_EQ(object->get_parent(), species1);
    ASSERT_EQ(species1->get_number_of_non_variable_children(), 1);
    ASSERT_EQ(species2->get_number_of_non_variable_children(), 0);

    universe->bind(universe, object, species2);
    ASSERT_EQ(object->get_parent(), species2);
    ASSERT_EQ(species1->get_number_of_non_variable_children(), 0);
    ASSERT_EQ(species2->get_number_of_non_variable_children(), 1);
}

// Public `Entity` create callbacks.

// Public `Entity` delete callbacks.

TEST(scene_must_be_deleted_appropriately, universe_callback)
{
    yli::ontology::Console* const console = nullptr;

    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(universe, world_struct, &universe->parent_of_worlds);

    const std::string scene_name = "foo";

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);
    scene->set_global_name(scene_name);

    universe->activate_entity(scene);

    delete scene;
    /*
    universe->delete_entity(universe, scene);
    ASSERT_EQ(universe->get_active_scene(), nullptr);
    */
}

// Public `Entity` activate callbacks.

TEST(scene_must_be_activated_appropriately, universe_callback)
{
    yli::ontology::Console* const console = nullptr;

    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(universe, world_struct, &universe->parent_of_worlds);

    const std::string scene_name = "foo";

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);
    scene->set_global_name(scene_name);

    ASSERT_EQ(universe->get_active_scene(), nullptr);

    universe->activate_entity(scene);
    ASSERT_EQ(universe->get_active_scene(), scene);
}

TEST(console_must_be_activated_appropriately, universe_callback_without_font2D)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    const std::string console_name = "foo";

    yli::ontology::ConsoleStruct console_struct;
    yli::ontology::Console* const console = new yli::ontology::Console(universe, console_struct, &universe->parent_of_consoles);
    console->set_global_name(console_name);

    ASSERT_EQ(universe->get_active_console(), nullptr);

    universe->activate_entity(console);
    ASSERT_EQ(universe->get_active_console(), console);
}

TEST(console_must_be_activated_appropriately, universe_callback_with_font2D)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::Font2D* font2D = new yli::ontology::Font2D(universe, yli::ontology::FontStruct(), &universe->parent_of_font2Ds);

    const std::string console_name = "foo";

    yli::ontology::ConsoleStruct console_struct;
    yli::ontology::Console* const console = new yli::ontology::Console(universe, console_struct, &universe->parent_of_consoles);
    console->set_global_name(console_name);

    ASSERT_EQ(universe->get_active_console(), nullptr);

    universe->activate_entity(console);
    ASSERT_EQ(universe->get_active_console(), console);
}

TEST(scene_and_camera_must_be_activated_appropriately, universe_callback)
{
    yli::ontology::Console* const console = nullptr;

    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(universe, world_struct, &universe->parent_of_worlds);

    const std::string scene_name = "foo";

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);
    scene->set_global_name(scene_name);

    const std::string camera_name = "bar";
    yli::ontology::Camera* const camera = new yli::ontology::Camera(universe, yli::ontology::CameraStruct(), &scene->parent_of_cameras);
    camera->set_global_name(camera_name);

    ASSERT_EQ(universe->get_active_scene(), nullptr);
    ASSERT_EQ(scene->get_active_camera(), nullptr);

    universe->activate_entity(scene);
    ASSERT_EQ(universe->get_active_scene(), scene);
    ASSERT_EQ(scene->get_active_camera(), nullptr);

    universe->activate_entity(camera);
    ASSERT_EQ(universe->get_active_scene(), scene);
    ASSERT_EQ(scene->get_active_camera(), camera);
}

// Public YliLisp-related callbacks.
