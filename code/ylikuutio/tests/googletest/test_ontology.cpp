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
#include "code/ylikuutio/angelscript/angelscript_master.cpp"
#include "code/ylikuutio/angelscript/angelscript_master.hpp"
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
#include "code/ylikuutio/ontology/world_struct.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/shader_struct.hpp"
#include "code/ylikuutio/ontology/material_struct.hpp"
#include "code/ylikuutio/ontology/species_struct.hpp"
#include "code/ylikuutio/ontology/object_struct.hpp"
#include "code/ylikuutio/ontology/symbiosis_struct.hpp"
#include "code/ylikuutio/ontology/holobiont_struct.hpp"
#include "code/ylikuutio/ontology/brain_struct.hpp"

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
    ASSERT_EQ(universe->get_number_of_all_children(), 0);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 0);
}

TEST(worlds_must_be_initialized_appropriately, headless)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct1;
    yli::ontology::World* const world1 = new yli::ontology::World(universe, world_struct1, &universe->parent_of_worlds);

    // `Universe` member functions.
    ASSERT_EQ(universe->get_number_of_worlds(), 1);
    ASSERT_EQ(universe->get_active_scene(), nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 1);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world1->get_childID(), 0);
    ASSERT_EQ(world1->get_type(), "yli::ontology::World*");
    ASSERT_TRUE(world1->get_can_be_erased());
    ASSERT_EQ(world1->get_universe(), universe);
    ASSERT_NE(world1->get_setting_master(), nullptr);
    ASSERT_EQ(world1->get_parent(), universe);
    ASSERT_EQ(world1->get_number_of_all_children(), 0);
    ASSERT_EQ(world1->get_number_of_all_descendants(), 0);

    yli::ontology::WorldStruct world_struct2;
    yli::ontology::World* const world2 = new yli::ontology::World(universe, world_struct2, &universe->parent_of_worlds);

    // `Universe` member functions.
    ASSERT_EQ(universe->get_number_of_worlds(), 2);
    ASSERT_EQ(universe->get_active_scene(), nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_all_children(), 2);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 2);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world2->get_childID(), 1);
    ASSERT_EQ(world2->get_type(), "yli::ontology::World*");
    ASSERT_TRUE(world2->get_can_be_erased());
    ASSERT_EQ(world2->get_universe(), universe);
    ASSERT_NE(world2->get_setting_master(), nullptr);
    ASSERT_EQ(world2->get_parent(), universe);
    ASSERT_EQ(world2->get_number_of_all_children(), 0);
    ASSERT_EQ(world2->get_number_of_all_descendants(), 0);

    yli::ontology::WorldStruct world_struct3;
    yli::ontology::World* const world3 = new yli::ontology::World(universe, world_struct3, &universe->parent_of_worlds);

    // `Universe` member functions.
    ASSERT_EQ(universe->get_number_of_worlds(), 3);
    ASSERT_EQ(universe->get_active_scene(), nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_all_children(), 3);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 3);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world3->get_childID(), 2);
    ASSERT_EQ(world3->get_type(), "yli::ontology::World*");
    ASSERT_TRUE(world3->get_can_be_erased());
    ASSERT_EQ(world3->get_universe(), universe);
    ASSERT_NE(world3->get_setting_master(), nullptr);
    ASSERT_EQ(world3->get_parent(), universe);
    ASSERT_EQ(world3->get_number_of_all_children(), 0);
    ASSERT_EQ(world3->get_number_of_all_descendants(), 0);

    yli::ontology::WorldStruct world_struct4;
    yli::ontology::World* const world4 = new yli::ontology::World(universe, world_struct4, &universe->parent_of_worlds);

    // `Universe` member functions.
    ASSERT_EQ(universe->get_number_of_worlds(), 4);
    ASSERT_EQ(universe->get_active_scene(), nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_all_children(), 4);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 4);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world4->get_childID(), 3);
    ASSERT_EQ(world4->get_type(), "yli::ontology::World*");
    ASSERT_TRUE(world4->get_can_be_erased());
    ASSERT_EQ(world4->get_universe(), universe);
    ASSERT_NE(world4->get_setting_master(), nullptr);
    ASSERT_EQ(world4->get_parent(), universe);
    ASSERT_EQ(world4->get_number_of_all_children(), 0);
    ASSERT_EQ(world4->get_number_of_all_descendants(), 0);
}

TEST(worlds_must_be_initialized_appropriately_after_having_deleted_the_earlier_worlds, headless)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct1;
    yli::ontology::World* const world1 = new yli::ontology::World(universe, world_struct1, &universe->parent_of_worlds);

    // `Universe` member functions.
    ASSERT_EQ(universe->get_number_of_worlds(), 1);
    ASSERT_EQ(universe->get_active_scene(), nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 1);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world1->get_childID(), 0);
    ASSERT_EQ(world1->get_type(), "yli::ontology::World*");
    ASSERT_TRUE(world1->get_can_be_erased());
    ASSERT_EQ(world1->get_universe(), universe);
    ASSERT_NE(world1->get_setting_master(), nullptr);
    ASSERT_EQ(world1->get_parent(), universe);
    ASSERT_EQ(world1->get_number_of_all_children(), 0);
    ASSERT_EQ(world1->get_number_of_all_descendants(), 0);

    delete world1;
    yli::ontology::WorldStruct world_struct2;
    yli::ontology::World* const world2 = new yli::ontology::World(universe, world_struct2, &universe->parent_of_worlds);

    // `Universe` member functions.
    ASSERT_EQ(universe->get_number_of_worlds(), 1);
    ASSERT_EQ(universe->get_active_scene(), nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 1);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world2->get_childID(), 0);
    ASSERT_EQ(world2->get_type(), "yli::ontology::World*");
    ASSERT_TRUE(world2->get_can_be_erased());
    ASSERT_EQ(world2->get_universe(), universe);
    ASSERT_NE(world2->get_setting_master(), nullptr);
    ASSERT_EQ(world2->get_parent(), universe);
    ASSERT_EQ(world2->get_number_of_all_children(), 0);
    ASSERT_EQ(world2->get_number_of_all_descendants(), 0);

    delete world2;
    yli::ontology::WorldStruct world_struct3;
    yli::ontology::World* const world3 = new yli::ontology::World(universe, world_struct3, &universe->parent_of_worlds);

    // `Universe` member functions.
    ASSERT_EQ(universe->get_number_of_worlds(), 1);
    ASSERT_EQ(universe->get_active_scene(), nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 1);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world3->get_childID(), 0);
    ASSERT_EQ(world3->get_type(), "yli::ontology::World*");
    ASSERT_TRUE(world3->get_can_be_erased());
    ASSERT_EQ(world3->get_universe(), universe);
    ASSERT_NE(world3->get_setting_master(), nullptr);
    ASSERT_EQ(world3->get_parent(), universe);
    ASSERT_EQ(world3->get_number_of_all_children(), 0);
    ASSERT_EQ(world3->get_number_of_all_descendants(), 0);

    delete world3;
    yli::ontology::WorldStruct world_struct4;
    yli::ontology::World* const world4 = new yli::ontology::World(universe, world_struct4, &universe->parent_of_worlds);

    // `Universe` member functions.
    ASSERT_EQ(universe->get_number_of_worlds(), 1);
    ASSERT_EQ(universe->get_active_scene(), nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 1);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world4->get_childID(), 0);
    ASSERT_EQ(world4->get_type(), "yli::ontology::World*");
    ASSERT_TRUE(world4->get_can_be_erased());
    ASSERT_EQ(world4->get_universe(), universe);
    ASSERT_NE(world4->get_setting_master(), nullptr);
    ASSERT_EQ(world4->get_parent(), universe);
    ASSERT_EQ(world4->get_number_of_all_children(), 0);
    ASSERT_EQ(world4->get_number_of_all_descendants(), 0);
}

TEST(worlds_must_be_initialized_appropriately_after_having_deleted_some_earlier_worlds, headless)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct1;
    yli::ontology::World* const world1 = new yli::ontology::World(universe, world_struct1, &universe->parent_of_worlds);

    // `Universe` member functions.
    ASSERT_EQ(universe->get_number_of_worlds(), 1);
    ASSERT_EQ(universe->get_active_scene(), nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 1);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world1->get_childID(), 0);
    ASSERT_EQ(world1->get_type(), "yli::ontology::World*");
    ASSERT_TRUE(world1->get_can_be_erased());
    ASSERT_EQ(world1->get_universe(), universe);
    ASSERT_NE(world1->get_setting_master(), nullptr);
    ASSERT_EQ(world1->get_parent(), universe);
    ASSERT_EQ(world1->get_number_of_all_children(), 0);
    ASSERT_EQ(world1->get_number_of_all_descendants(), 0);

    yli::ontology::WorldStruct world_struct2;
    yli::ontology::World* const world2 = new yli::ontology::World(universe, world_struct2, &universe->parent_of_worlds);

    // `Universe` member functions.
    ASSERT_EQ(universe->get_number_of_worlds(), 2);
    ASSERT_EQ(universe->get_active_scene(), nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_all_children(), 2);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 2);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world2->get_childID(), 1);
    ASSERT_EQ(world2->get_type(), "yli::ontology::World*");
    ASSERT_TRUE(world2->get_can_be_erased());
    ASSERT_EQ(world2->get_universe(), universe);
    ASSERT_NE(world2->get_setting_master(), nullptr);
    ASSERT_EQ(world2->get_parent(), universe);
    ASSERT_EQ(world2->get_number_of_all_children(), 0);
    ASSERT_EQ(world2->get_number_of_all_descendants(), 0);

    delete world1;
    yli::ontology::WorldStruct world_struct3;
    yli::ontology::World* const world3 = new yli::ontology::World(universe, world_struct3, &universe->parent_of_worlds);

    // `Universe` member functions.
    ASSERT_EQ(universe->get_number_of_worlds(), 2);
    ASSERT_EQ(universe->get_active_scene(), nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_all_children(), 2);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 2);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world3->get_childID(), 0);
    ASSERT_EQ(world3->get_type(), "yli::ontology::World*");
    ASSERT_TRUE(world3->get_can_be_erased());
    ASSERT_EQ(world3->get_universe(), universe);
    ASSERT_NE(world3->get_setting_master(), nullptr);
    ASSERT_EQ(world3->get_parent(), universe);
    ASSERT_EQ(world3->get_number_of_all_children(), 0);
    ASSERT_EQ(world3->get_number_of_all_descendants(), 0);

    yli::ontology::WorldStruct world_struct4;
    yli::ontology::World* const world4 = new yli::ontology::World(universe, world_struct4, &universe->parent_of_worlds);

    // `Universe` member functions.
    ASSERT_EQ(universe->get_number_of_worlds(), 3);
    ASSERT_EQ(universe->get_active_scene(), nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_all_children(), 3);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 3);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world4->get_childID(), 2);
    ASSERT_EQ(world4->get_type(), "yli::ontology::World*");
    ASSERT_TRUE(world4->get_can_be_erased());
    ASSERT_EQ(world4->get_universe(), universe);
    ASSERT_NE(world4->get_setting_master(), nullptr);
    ASSERT_EQ(world4->get_parent(), universe);
    ASSERT_EQ(world4->get_number_of_all_children(), 0);
    ASSERT_EQ(world4->get_number_of_all_descendants(), 0);
}

TEST(world_must_be_initialized_appropriately, no_universe)
{
    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(nullptr, world_struct, nullptr);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(world->get_type(), "yli::ontology::World*");
    ASSERT_TRUE(world->get_can_be_erased());
    ASSERT_EQ(world->get_universe(), nullptr);
    ASSERT_NE(world->get_setting_master(), nullptr);
    ASSERT_EQ(world->get_parent(), nullptr);
    ASSERT_EQ(world->get_number_of_all_children(), 0);
    ASSERT_EQ(world->get_number_of_all_descendants(), 0);
}

TEST(scene_must_be_initialized_appropriately, headless)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(universe, world_struct, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);

    // `Universe` member functions.
    ASSERT_EQ(universe->get_number_of_worlds(), 1);
    ASSERT_EQ(universe->get_active_scene(), nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 3);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world->get_number_of_all_children(), 1);
    ASSERT_EQ(world->get_number_of_all_descendants(), 2);

    // `Entity` member functions.
    ASSERT_EQ(scene->get_childID(), 0);
    ASSERT_EQ(scene->get_type(), "yli::ontology::Scene*");
    ASSERT_TRUE(scene->get_can_be_erased());
    ASSERT_EQ(scene->get_universe(), universe);
    ASSERT_NE(scene->get_setting_master(), nullptr);
    ASSERT_EQ(scene->get_parent(), world);
    ASSERT_EQ(scene->get_number_of_all_children(), 1);
    ASSERT_EQ(scene->get_number_of_all_descendants(), 1);
}

TEST(scene_must_be_initialized_appropriately, no_universe)
{
    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(nullptr, world_struct, nullptr);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(nullptr, scene_struct, &world->parent_of_scenes);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world->get_number_of_all_children(), 1);
    ASSERT_EQ(world->get_number_of_all_descendants(), 2);

    // `Entity` member functions.
    ASSERT_EQ(scene->get_childID(), 0);
    ASSERT_EQ(scene->get_type(), "yli::ontology::Scene*");
    ASSERT_TRUE(scene->get_can_be_erased());
    ASSERT_EQ(scene->get_universe(), nullptr);
    ASSERT_NE(scene->get_setting_master(), nullptr);
    ASSERT_EQ(scene->get_parent(), world);
    ASSERT_EQ(scene->get_number_of_all_children(), 1);
    ASSERT_EQ(scene->get_number_of_all_descendants(), 1);
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
    ASSERT_EQ(scene->get_number_of_all_children(), 1);
    ASSERT_EQ(scene->get_number_of_all_descendants(), 1);
}

TEST(shader_must_be_initialized_appropriately, headless)
{
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

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 4);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world->get_number_of_all_children(), 1);
    ASSERT_EQ(world->get_number_of_all_descendants(), 3);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_all_children(), 2);
    ASSERT_EQ(scene->get_number_of_all_descendants(), 2);

    // `Entity` member functions.
    ASSERT_EQ(shader->get_childID(), 0);
    ASSERT_EQ(shader->get_type(), "yli::ontology::Shader*");
    ASSERT_TRUE(shader->get_can_be_erased());
    ASSERT_EQ(shader->get_universe(), universe);
    ASSERT_NE(shader->get_setting_master(), nullptr);
    ASSERT_EQ(shader->get_parent(), scene);
    ASSERT_EQ(shader->get_number_of_all_children(), 0);
    ASSERT_EQ(shader->get_number_of_all_descendants(), 0);
}

TEST(shader_must_be_initialized_appropriately, no_universe)
{
    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(nullptr, world_struct, nullptr);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(nullptr, scene_struct, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(nullptr, shader_struct);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world->get_number_of_all_children(), 1);
    ASSERT_EQ(world->get_number_of_all_descendants(), 3);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_all_children(), 2);
    ASSERT_EQ(scene->get_number_of_all_descendants(), 2);

    // `Entity` member functions.
    ASSERT_EQ(shader->get_childID(), 0);
    ASSERT_EQ(shader->get_type(), "yli::ontology::Shader*");
    ASSERT_TRUE(shader->get_can_be_erased());
    ASSERT_EQ(shader->get_universe(), nullptr);
    ASSERT_NE(shader->get_setting_master(), nullptr);
    ASSERT_EQ(shader->get_parent(), scene);
    ASSERT_EQ(shader->get_number_of_all_children(), 0);
    ASSERT_EQ(shader->get_number_of_all_descendants(), 0);
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
    ASSERT_EQ(scene->get_number_of_all_children(), 2);
    ASSERT_EQ(scene->get_number_of_all_descendants(), 2);

    // `Entity` member functions.
    ASSERT_EQ(shader->get_childID(), 0);
    ASSERT_EQ(shader->get_type(), "yli::ontology::Shader*");
    ASSERT_TRUE(shader->get_can_be_erased());
    ASSERT_EQ(shader->get_universe(), nullptr);
    ASSERT_NE(shader->get_setting_master(), nullptr);
    ASSERT_EQ(shader->get_parent(), scene);
    ASSERT_EQ(shader->get_number_of_all_children(), 0);
    ASSERT_EQ(shader->get_number_of_all_descendants(), 0);
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
    ASSERT_EQ(shader->get_number_of_all_children(), 0);
    ASSERT_EQ(shader->get_number_of_all_descendants(), 0);
}

TEST(material_must_be_initialized_appropriately, headless)
{
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

    yli::ontology::MaterialStruct material_struct;
    material_struct.shader = shader;
    yli::ontology::Material* const material = new yli::ontology::Material(universe, material_struct, &shader->parent_of_materials);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 5);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world->get_number_of_all_children(), 1);
    ASSERT_EQ(world->get_number_of_all_descendants(), 4);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_all_children(), 2);
    ASSERT_EQ(scene->get_number_of_all_descendants(), 3);

    // `Entity` member functions of `Shader`.
    ASSERT_EQ(shader->get_number_of_all_children(), 1);
    ASSERT_EQ(shader->get_number_of_all_descendants(), 1);

    // `Entity` member functions.
    ASSERT_EQ(material->get_childID(), 0);
    ASSERT_EQ(material->get_type(), "yli::ontology::Material*");
    ASSERT_TRUE(material->get_can_be_erased());
    ASSERT_EQ(material->get_universe(), universe);
    ASSERT_NE(material->get_setting_master(), nullptr);
    ASSERT_EQ(material->get_parent(), shader);
    ASSERT_EQ(material->get_number_of_all_children(), 0);
    ASSERT_EQ(material->get_number_of_all_descendants(), 0);
}

TEST(material_must_be_initialized_appropriately, no_universe)
{
    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(nullptr, world_struct, nullptr);

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
    ASSERT_EQ(world->get_number_of_all_children(), 1);
    ASSERT_EQ(world->get_number_of_all_descendants(), 4);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_all_children(), 2);
    ASSERT_EQ(scene->get_number_of_all_descendants(), 3);

    // `Entity` member functions of `Shader`.
    ASSERT_EQ(shader->get_number_of_all_children(), 1);
    ASSERT_EQ(shader->get_number_of_all_descendants(), 1);

    // `Entity` member functions.
    ASSERT_EQ(material->get_childID(), 0);
    ASSERT_EQ(material->get_type(), "yli::ontology::Material*");
    ASSERT_TRUE(material->get_can_be_erased());
    ASSERT_EQ(material->get_universe(), nullptr);
    ASSERT_NE(material->get_setting_master(), nullptr);
    ASSERT_EQ(material->get_parent(), shader);
    ASSERT_EQ(material->get_number_of_all_children(), 0);
    ASSERT_EQ(material->get_number_of_all_descendants(), 0);
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
    ASSERT_EQ(scene->get_number_of_all_children(), 2);
    ASSERT_EQ(scene->get_number_of_all_descendants(), 3);

    // `Entity` member functions of `Shader`.
    ASSERT_EQ(shader->get_number_of_all_children(), 1);
    ASSERT_EQ(shader->get_number_of_all_descendants(), 1);

    // `Entity` member functions.
    ASSERT_EQ(material->get_childID(), 0);
    ASSERT_EQ(material->get_type(), "yli::ontology::Material*");
    ASSERT_TRUE(material->get_can_be_erased());
    ASSERT_EQ(material->get_universe(), nullptr);
    ASSERT_NE(material->get_setting_master(), nullptr);
    ASSERT_EQ(material->get_parent(), shader);
    ASSERT_EQ(material->get_number_of_all_children(), 0);
    ASSERT_EQ(material->get_number_of_all_descendants(), 0);
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
    ASSERT_EQ(shader->get_number_of_all_children(), 1);
    ASSERT_EQ(shader->get_number_of_all_descendants(), 1);

    // `Entity` member functions.
    ASSERT_EQ(material->get_childID(), 0);
    ASSERT_EQ(material->get_type(), "yli::ontology::Material*");
    ASSERT_TRUE(material->get_can_be_erased());
    ASSERT_EQ(material->get_universe(), nullptr);
    ASSERT_NE(material->get_setting_master(), nullptr);
    ASSERT_EQ(material->get_parent(), shader);
    ASSERT_EQ(material->get_number_of_all_children(), 0);
    ASSERT_EQ(material->get_number_of_all_descendants(), 0);
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
    ASSERT_EQ(material->get_number_of_all_children(), 0);
    ASSERT_EQ(material->get_number_of_all_descendants(), 0);
}

TEST(species_must_be_initialized_appropriately, headless)
{
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

    yli::ontology::MaterialStruct material_struct;
    material_struct.shader = shader;
    yli::ontology::Material* const material = new yli::ontology::Material(universe, material_struct, &shader->parent_of_materials);

    yli::ontology::SpeciesStruct species_struct;
    species_struct.scene = scene;
    species_struct.shader = shader;
    species_struct.material = material;
    yli::ontology::Species* const species = new yli::ontology::Species(universe, species_struct, &material->parent_of_species);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 6);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world->get_number_of_all_children(), 1);
    ASSERT_EQ(world->get_number_of_all_descendants(), 5);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_all_children(), 2);
    ASSERT_EQ(scene->get_number_of_all_descendants(), 4);

    // `Entity` member functions of `Shader`.
    ASSERT_EQ(shader->get_number_of_all_children(), 1);
    ASSERT_EQ(shader->get_number_of_all_descendants(), 2);

    // `Entity` member functions of `Material`.
    ASSERT_EQ(material->get_number_of_all_children(), 1);
    ASSERT_EQ(material->get_number_of_all_descendants(), 1);

    // `Entity` member functions.
    ASSERT_EQ(species->get_childID(), 0);
    ASSERT_EQ(species->get_type(), "yli::ontology::Species*");
    ASSERT_TRUE(species->get_can_be_erased());
    ASSERT_EQ(species->get_universe(), universe);
    ASSERT_NE(species->get_setting_master(), nullptr);
    ASSERT_EQ(species->get_parent(), material);
    ASSERT_EQ(species->get_number_of_all_children(), 0);
    ASSERT_EQ(species->get_number_of_all_descendants(), 0);
}

TEST(species_must_be_initialized_appropriately, no_universe_no_world_no_scene_no_shader_no_material)
{
    yli::ontology::SpeciesStruct species_struct;
    species_struct.scene = nullptr;
    species_struct.shader = nullptr;
    species_struct.material = nullptr;
    yli::ontology::Species* const species = new yli::ontology::Species(nullptr, species_struct, nullptr);

    // `Entity` member functions.
    ASSERT_EQ(species->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(species->get_type(), "yli::ontology::Species*");
    ASSERT_TRUE(species->get_can_be_erased());
    ASSERT_EQ(species->get_universe(), nullptr);
    ASSERT_NE(species->get_setting_master(), nullptr);
    ASSERT_EQ(species->get_parent(), nullptr);
    ASSERT_EQ(species->get_number_of_all_children(), 0);
    ASSERT_EQ(species->get_number_of_all_descendants(), 0);
}

TEST(object_must_be_initialized_appropriately, headless)
{
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

    yli::ontology::MaterialStruct material_struct;
    material_struct.shader = shader;
    yli::ontology::Material* const material = new yli::ontology::Material(universe, material_struct, &shader->parent_of_materials);

    yli::ontology::SpeciesStruct species_struct;
    species_struct.scene = scene;
    species_struct.shader = shader;
    species_struct.material = material;
    yli::ontology::Species* const species = new yli::ontology::Species(universe, species_struct, &material->parent_of_species);

    yli::ontology::ObjectStruct object_struct;
    object_struct.species_parent = species;
    yli::ontology::Object* const object = new yli::ontology::Object(universe, object_struct, &species->parent_of_objects);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 7);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world->get_number_of_all_children(), 1);
    ASSERT_EQ(world->get_number_of_all_descendants(), 6);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_all_children(), 2);
    ASSERT_EQ(scene->get_number_of_all_descendants(), 5);

    // `Entity` member functions of `Shader`.
    ASSERT_EQ(shader->get_number_of_all_children(), 1);
    ASSERT_EQ(shader->get_number_of_all_descendants(), 3);

    // `Entity` member functions of `Material`.
    ASSERT_EQ(material->get_number_of_all_children(), 1);
    ASSERT_EQ(material->get_number_of_all_descendants(), 2);

    // `Entity` member functions of `Species`.
    ASSERT_EQ(species->get_number_of_all_children(), 1);
    ASSERT_EQ(species->get_number_of_all_descendants(), 1);

    // `Entity` member functions.
    ASSERT_EQ(object->get_childID(), 0);
    ASSERT_EQ(object->get_type(), "yli::ontology::Object*");
    ASSERT_TRUE(object->get_can_be_erased());
    ASSERT_EQ(object->get_universe(), universe);
    ASSERT_NE(object->get_setting_master(), nullptr);
    ASSERT_EQ(object->get_glyph(), nullptr);
    ASSERT_EQ(object->get_parent(), species);
    ASSERT_EQ(object->get_number_of_all_children(), 0);
    ASSERT_EQ(object->get_number_of_all_descendants(), 0);
}

TEST(object_must_be_initialized_appropriately, no_universe_no_world_no_scene_no_shader_no_material_no_species)
{
    yli::ontology::ObjectStruct object_struct;
    object_struct.species_parent = nullptr;
    yli::ontology::Object* const object = new yli::ontology::Object(nullptr, object_struct, nullptr);

    // `Entity` member functions.
    ASSERT_EQ(object->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(object->get_type(), "yli::ontology::Object*");
    ASSERT_TRUE(object->get_can_be_erased());
    ASSERT_EQ(object->get_universe(), nullptr);
    ASSERT_NE(object->get_setting_master(), nullptr);
    ASSERT_EQ(object->get_glyph(), nullptr);
    ASSERT_EQ(object->get_parent(), nullptr);
    ASSERT_EQ(object->get_number_of_all_children(), 0);
    ASSERT_EQ(object->get_number_of_all_descendants(), 0);
}

TEST(symbiosis_must_be_initialized_appropriately, headless)
{
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

    yli::ontology::SymbiosisStruct symbiosis_struct;
    symbiosis_struct.parent = shader;
    yli::ontology::Symbiosis* const symbiosis = new yli::ontology::Symbiosis(universe, symbiosis_struct, &shader->parent_of_symbioses);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 5);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world->get_number_of_all_children(), 1);
    ASSERT_EQ(world->get_number_of_all_descendants(), 4);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_all_children(), 2);
    ASSERT_EQ(scene->get_number_of_all_descendants(), 3);

    // `Entity` member functions of `Shader`.
    ASSERT_EQ(shader->get_number_of_all_children(), 1);
    ASSERT_EQ(shader->get_number_of_all_descendants(), 1);

    // `Entity` member functions.
    ASSERT_EQ(symbiosis->get_childID(), 0);
    ASSERT_EQ(symbiosis->get_type(), "yli::ontology::Symbiosis*");
    ASSERT_TRUE(symbiosis->get_can_be_erased());
    ASSERT_EQ(symbiosis->get_universe(), universe);
    ASSERT_NE(symbiosis->get_setting_master(), nullptr);
    ASSERT_EQ(symbiosis->get_parent(), shader);
    ASSERT_EQ(symbiosis->get_number_of_all_children(), 0);
    ASSERT_EQ(symbiosis->get_number_of_all_descendants(), 0);
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
    ASSERT_EQ(symbiosis->get_number_of_all_children(), 0);
    ASSERT_EQ(symbiosis->get_number_of_all_descendants(), 0);
}

TEST(symbiosis_must_be_initialized_appropriately, headless_turbo_polizei)
{
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

    yli::ontology::SymbiosisStruct symbiosis_struct;
    symbiosis_struct.parent = shader;
    symbiosis_struct.model_filename = "turbo_polizei_bmp_textures.fbx";
    symbiosis_struct.model_file_format = "FBX";
    yli::ontology::Symbiosis* const symbiosis = new yli::ontology::Symbiosis(universe, symbiosis_struct, &shader->parent_of_symbioses);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 12);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world->get_number_of_all_children(), 1);
    ASSERT_EQ(world->get_number_of_all_descendants(), 11);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_all_children(), 2);
    ASSERT_EQ(scene->get_number_of_all_descendants(), 10);

    // `Entity` member functions of `Shader`.
    ASSERT_EQ(shader->get_number_of_all_children(), 1);
    ASSERT_EQ(shader->get_number_of_all_descendants(), 8);

    // `Entity` member functions.
    ASSERT_EQ(symbiosis->get_childID(), 0);
    ASSERT_EQ(symbiosis->get_type(), "yli::ontology::Symbiosis*");
    ASSERT_TRUE(symbiosis->get_can_be_erased());
    ASSERT_EQ(symbiosis->get_universe(), universe);
    ASSERT_NE(symbiosis->get_setting_master(), nullptr);
    ASSERT_EQ(symbiosis->get_parent(), shader);
    ASSERT_EQ(symbiosis->get_number_of_all_children(), 2);    // 2 `SymbiontMaterial`s.
    ASSERT_EQ(symbiosis->get_number_of_all_descendants(), 7); // 2 `SymbiontMaterial`s and 5 `SymbiontSpecies`.
}

TEST(symbiosis_must_be_initialized_appropriately, no_universe_no_world_no_scene_no_material_no_shader_turbo_polizei)
{
    yli::ontology::SymbiosisStruct symbiosis_struct;
    symbiosis_struct.parent = nullptr;
    symbiosis_struct.model_filename = "turbo_polizei_bmp_textures.fbx";
    symbiosis_struct.model_file_format = "FBX";
    yli::ontology::Symbiosis* const symbiosis = new yli::ontology::Symbiosis(nullptr, symbiosis_struct, nullptr);

    // `Entity` member functions.
    ASSERT_EQ(symbiosis->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(symbiosis->get_type(), "yli::ontology::Symbiosis*");
    ASSERT_TRUE(symbiosis->get_can_be_erased());
    ASSERT_EQ(symbiosis->get_universe(), nullptr);
    ASSERT_NE(symbiosis->get_setting_master(), nullptr);
    ASSERT_EQ(symbiosis->get_parent(), nullptr);
    ASSERT_EQ(symbiosis->get_number_of_all_children(), 2);    // 2 `SymbiontMaterial`s.
    ASSERT_EQ(symbiosis->get_number_of_all_descendants(), 7); // 2 `SymbiontMaterial`s and 5 `SymbiontSpecies`.
}

TEST(holobiont_must_be_initialized_appropriately, headless)
{
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

    yli::ontology::SymbiosisStruct symbiosis_struct;
    symbiosis_struct.parent = shader;
    yli::ontology::Symbiosis* const symbiosis = new yli::ontology::Symbiosis(universe, symbiosis_struct, &shader->parent_of_symbioses);

    yli::ontology::HolobiontStruct holobiont_struct;
    holobiont_struct.symbiosis_parent = symbiosis;
    yli::ontology::Holobiont* const holobiont = new yli::ontology::Holobiont(universe, holobiont_struct, &symbiosis->parent_of_holobionts);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 6);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world->get_number_of_all_children(), 1);
    ASSERT_EQ(world->get_number_of_all_descendants(), 5);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_all_children(), 2);
    ASSERT_EQ(scene->get_number_of_all_descendants(), 4);

    // `Entity` member functions of `Shader`.
    ASSERT_EQ(shader->get_number_of_all_children(), 1);
    ASSERT_EQ(shader->get_number_of_all_descendants(), 2);

    // `Entity` member functions of `Symbiosis`.
    ASSERT_EQ(symbiosis->get_number_of_all_children(), 1);
    ASSERT_EQ(symbiosis->get_number_of_all_descendants(), 1);

    // `Entity` member functions.
    ASSERT_EQ(holobiont->get_childID(), 0);
    ASSERT_EQ(holobiont->get_type(), "yli::ontology::Holobiont*");
    ASSERT_TRUE(holobiont->get_can_be_erased());
    ASSERT_EQ(holobiont->get_universe(), universe);
    ASSERT_NE(holobiont->get_setting_master(), nullptr);
    ASSERT_EQ(holobiont->get_parent(), symbiosis);
    ASSERT_EQ(holobiont->get_number_of_all_children(), 0);
    ASSERT_EQ(holobiont->get_number_of_all_descendants(), 0);
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
    ASSERT_EQ(holobiont->get_number_of_all_children(), 0);
    ASSERT_EQ(holobiont->get_number_of_all_descendants(), 0);
}

TEST(holobiont_must_be_initialized_appropriately, headless_turbo_polizei)
{
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

    yli::ontology::SymbiosisStruct symbiosis_struct;
    symbiosis_struct.parent = shader;
    symbiosis_struct.model_filename = "turbo_polizei_bmp_textures.fbx";
    symbiosis_struct.model_file_format = "FBX";
    yli::ontology::Symbiosis* const symbiosis = new yli::ontology::Symbiosis(universe, symbiosis_struct, &shader->parent_of_symbioses);

    yli::ontology::HolobiontStruct holobiont_struct;
    holobiont_struct.symbiosis_parent = symbiosis;
    yli::ontology::Holobiont* const holobiont = new yli::ontology::Holobiont(universe, holobiont_struct, &symbiosis->parent_of_holobionts);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 18);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world->get_number_of_all_children(), 1);
    ASSERT_EQ(world->get_number_of_all_descendants(), 17);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_all_children(), 2);
    ASSERT_EQ(scene->get_number_of_all_descendants(), 16);

    // `Entity` member functions of `Shader`.
    ASSERT_EQ(shader->get_number_of_all_children(), 1);
    ASSERT_EQ(shader->get_number_of_all_descendants(), 14);

    // `Entity` member functions of `Symbiosis`.
    ASSERT_EQ(symbiosis->get_number_of_all_children(), 3);     // 2 `SymbiontMaterial`s and 1 `Holobiont`.
    ASSERT_EQ(symbiosis->get_number_of_all_descendants(), 13); // 2 `SymbiontMaterial`s, 5 `SymbiontSpecies`, 1 `Holobiont`, and 5 `Biont`s.

    // `Entity` member functions.
    ASSERT_EQ(holobiont->get_childID(), 0);
    ASSERT_EQ(holobiont->get_type(), "yli::ontology::Holobiont*");
    ASSERT_TRUE(holobiont->get_can_be_erased());
    ASSERT_EQ(holobiont->get_universe(), universe);
    ASSERT_NE(holobiont->get_setting_master(), nullptr);
    ASSERT_EQ(holobiont->get_parent(), symbiosis);
    ASSERT_EQ(holobiont->get_number_of_all_children(), 5);     // 5 `Biont`s.
    ASSERT_EQ(holobiont->get_number_of_all_descendants(), 5);  // 5 `Biont`s.
}

TEST(holobiont_must_be_initialized_appropriately, no_universe_no_world_no_scene_no_shader_turbo_polizei)
{
    yli::ontology::SymbiosisStruct symbiosis_struct;
    symbiosis_struct.parent = nullptr;
    symbiosis_struct.model_filename = "turbo_polizei_bmp_textures.fbx";
    symbiosis_struct.model_file_format = "FBX";
    yli::ontology::Symbiosis* const symbiosis = new yli::ontology::Symbiosis(nullptr, symbiosis_struct, nullptr);

    yli::ontology::HolobiontStruct holobiont_struct;
    holobiont_struct.symbiosis_parent = symbiosis;
    yli::ontology::Holobiont* const holobiont = new yli::ontology::Holobiont(nullptr, holobiont_struct, &symbiosis->parent_of_holobionts);

    // `Entity` member functions of `Symbiosis`.
    ASSERT_EQ(symbiosis->get_number_of_all_children(), 3);     // 2 `SymbiontMaterial`s and 1 `Holobiont`.
    ASSERT_EQ(symbiosis->get_number_of_all_descendants(), 13); // 2 `SymbiontMaterial`s, 5 `SymbiontSpecies`, 1 `Holobiont`, and 5 `Biont`s.

    // `Entity` member functions.
    ASSERT_EQ(holobiont->get_childID(), 0);
    ASSERT_EQ(holobiont->get_type(), "yli::ontology::Holobiont*");
    ASSERT_TRUE(holobiont->get_can_be_erased());
    ASSERT_EQ(holobiont->get_universe(), nullptr);
    ASSERT_NE(holobiont->get_setting_master(), nullptr);
    ASSERT_EQ(holobiont->get_parent(), symbiosis);
    ASSERT_EQ(holobiont->get_number_of_all_children(), 5);     // 5 `Biont`s.
    ASSERT_EQ(holobiont->get_number_of_all_descendants(), 5);  // 5 `Biont`s.
}

TEST(shapeshifter_transformation_must_be_initialized_appropriately, headless)
{
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

    yli::ontology::MaterialStruct material_struct;
    material_struct.shader = shader;
    yli::ontology::Material* const material = new yli::ontology::Material(universe, material_struct, &shader->parent_of_materials);

    yli::ontology::SpeciesStruct shapeshifter_transformation_struct;
    shapeshifter_transformation_struct.scene = scene;
    shapeshifter_transformation_struct.shader = shader;
    shapeshifter_transformation_struct.material = material;
    yli::ontology::ShapeshifterTransformation* const shapeshifter_transformation = new yli::ontology::ShapeshifterTransformation(universe, shapeshifter_transformation_struct);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 6);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world->get_number_of_all_children(), 1);
    ASSERT_EQ(world->get_number_of_all_descendants(), 5);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_all_children(), 2);
    ASSERT_EQ(scene->get_number_of_all_descendants(), 4);

    // `Entity` member functions of `Shader`.
    ASSERT_EQ(shader->get_number_of_all_children(), 1);
    ASSERT_EQ(shader->get_number_of_all_descendants(), 2);

    // `Entity` member functions of `Material`.
    ASSERT_EQ(material->get_number_of_all_children(), 1);
    ASSERT_EQ(material->get_number_of_all_descendants(), 1);

    // `Entity` member functions.
    ASSERT_EQ(shapeshifter_transformation->get_childID(), 0);
    ASSERT_EQ(shapeshifter_transformation->get_type(), "yli::ontology::ShapeshifterTransformation*");
    ASSERT_TRUE(shapeshifter_transformation->get_can_be_erased());
    ASSERT_EQ(shapeshifter_transformation->get_universe(), universe);
    ASSERT_NE(shapeshifter_transformation->get_setting_master(), nullptr);
    ASSERT_EQ(shapeshifter_transformation->get_parent(), material);
    ASSERT_EQ(shapeshifter_transformation->get_number_of_all_children(), 0);
    ASSERT_EQ(shapeshifter_transformation->get_number_of_all_descendants(), 0);
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
    ASSERT_EQ(shapeshifter_transformation->get_number_of_all_children(), 0);
    ASSERT_EQ(shapeshifter_transformation->get_number_of_all_descendants(), 0);
}

TEST(shapeshifter_form_must_be_initialized_appropriately, headless)
{
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
    yli::ontology::ShapeshifterForm* const shapeshifter_form = new yli::ontology::ShapeshifterForm(
            universe,
            shapeshifter_form_struct,
            &shapeshifter_transformation->parent_of_shapeshifter_forms);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 7);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world->get_number_of_all_children(), 1);
    ASSERT_EQ(world->get_number_of_all_descendants(), 6);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_all_children(), 2);
    ASSERT_EQ(scene->get_number_of_all_descendants(), 5);

    // `Entity` member functions of `Shader`.
    ASSERT_EQ(shader->get_number_of_all_children(), 1);
    ASSERT_EQ(shader->get_number_of_all_descendants(), 3);

    // `Entity` member functions of `Material`.
    ASSERT_EQ(material->get_number_of_all_children(), 1);
    ASSERT_EQ(material->get_number_of_all_descendants(), 2);

    // `Entity` member functions of `ShapeshifterTransformation`.
    ASSERT_EQ(shapeshifter_transformation->get_number_of_all_children(), 1);
    ASSERT_EQ(shapeshifter_transformation->get_number_of_all_descendants(), 1);

    // `Entity` member functions.
    ASSERT_EQ(shapeshifter_form->get_childID(), 0);
    ASSERT_EQ(shapeshifter_form->get_type(), "yli::ontology::ShapeshifterForm*");
    ASSERT_FALSE(shapeshifter_form->get_can_be_erased());
    ASSERT_EQ(shapeshifter_form->get_universe(), universe);
    ASSERT_NE(shapeshifter_form->get_setting_master(), nullptr);
    ASSERT_EQ(shapeshifter_form->get_parent(), shapeshifter_transformation);
    ASSERT_EQ(shapeshifter_form->get_number_of_all_children(), 0);
    ASSERT_EQ(shapeshifter_form->get_number_of_all_descendants(), 0);
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
    yli::ontology::ShapeshifterForm* const shapeshifter_form = new yli::ontology::ShapeshifterForm(
            nullptr,
            shapeshifter_form_struct,
            &shapeshifter_transformation->parent_of_shapeshifter_forms);

    // `Entity` member functions.
    ASSERT_EQ(shapeshifter_form->get_childID(), 0);
    ASSERT_EQ(shapeshifter_form->get_type(), "yli::ontology::ShapeshifterForm*");
    ASSERT_FALSE(shapeshifter_form->get_can_be_erased());
    ASSERT_EQ(shapeshifter_form->get_universe(), nullptr);
    ASSERT_NE(shapeshifter_form->get_setting_master(), nullptr);
    ASSERT_EQ(shapeshifter_form->get_parent(), shapeshifter_transformation);
    ASSERT_EQ(shapeshifter_form->get_number_of_all_children(), 0);
    ASSERT_EQ(shapeshifter_form->get_number_of_all_descendants(), 0);
}

TEST(shapeshifter_form_must_be_initialized_appropriately, no_universe_no_world_no_scene_no_shader_no_material_no_shapeshifter_transformation)
{
    yli::ontology::SpeciesStruct shapeshifter_form_struct;
    shapeshifter_form_struct.scene = nullptr;
    shapeshifter_form_struct.shader = nullptr;
    shapeshifter_form_struct.material = nullptr;
    shapeshifter_form_struct.shapeshifter_transformation = nullptr;
    yli::ontology::ShapeshifterForm* const shapeshifter_form = new yli::ontology::ShapeshifterForm(nullptr, shapeshifter_form_struct, nullptr);

    // `Entity` member functions.
    ASSERT_EQ(shapeshifter_form->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(shapeshifter_form->get_type(), "yli::ontology::ShapeshifterForm*");
    ASSERT_FALSE(shapeshifter_form->get_can_be_erased());
    ASSERT_EQ(shapeshifter_form->get_universe(), nullptr);
    ASSERT_NE(shapeshifter_form->get_setting_master(), nullptr);
    ASSERT_EQ(shapeshifter_form->get_parent(), nullptr);
    ASSERT_EQ(shapeshifter_form->get_number_of_all_children(), 0);
    ASSERT_EQ(shapeshifter_form->get_number_of_all_descendants(), 0);
}

TEST(shapeshifter_sequence_must_be_initialized_appropriately, headless)
{
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
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 7);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world->get_number_of_all_children(), 1);
    ASSERT_EQ(world->get_number_of_all_descendants(), 6);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_all_children(), 2);
    ASSERT_EQ(scene->get_number_of_all_descendants(), 5);

    // `Entity` member functions of `Shader`.
    ASSERT_EQ(shader->get_number_of_all_children(), 1);
    ASSERT_EQ(shader->get_number_of_all_descendants(), 3);

    // `Entity` member functions of `Material`.
    ASSERT_EQ(material->get_number_of_all_children(), 1);
    ASSERT_EQ(material->get_number_of_all_descendants(), 2);

    // `Entity` member functions of `ShapeshifterTransformation`.
    ASSERT_EQ(shapeshifter_transformation->get_number_of_all_children(), 1);
    ASSERT_EQ(shapeshifter_transformation->get_number_of_all_descendants(), 1);

    // `Entity` member functions.
    ASSERT_EQ(shapeshifter_sequence->get_childID(), 0);
    ASSERT_EQ(shapeshifter_sequence->get_type(), "yli::ontology::ShapeshifterSequence*");
    ASSERT_TRUE(shapeshifter_sequence->get_can_be_erased());
    ASSERT_EQ(shapeshifter_sequence->get_universe(), universe);
    ASSERT_NE(shapeshifter_sequence->get_setting_master(), nullptr);
    ASSERT_EQ(shapeshifter_sequence->get_parent(), shapeshifter_transformation);
    ASSERT_EQ(shapeshifter_sequence->get_number_of_all_children(), 0);
    ASSERT_EQ(shapeshifter_sequence->get_number_of_all_descendants(), 0);
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
    ASSERT_EQ(shapeshifter_sequence->get_number_of_all_children(), 0);
    ASSERT_EQ(shapeshifter_sequence->get_number_of_all_descendants(), 0);
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
    ASSERT_EQ(shapeshifter_sequence->get_number_of_all_children(), 0);
    ASSERT_EQ(shapeshifter_sequence->get_number_of_all_descendants(), 0);
}

TEST(shapeshifter_form_and_sequence_must_be_initialized_appropriately, headless)
{
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

    yli::ontology::MaterialStruct material_struct;
    material_struct.shader = shader;
    yli::ontology::Material* const material = new yli::ontology::Material(universe, material_struct, &shader->parent_of_materials);

    yli::ontology::SpeciesStruct shapeshifter_transformation_struct;
    shapeshifter_transformation_struct.scene = scene;
    shapeshifter_transformation_struct.shader = shader;
    shapeshifter_transformation_struct.material = material;
    yli::ontology::ShapeshifterTransformation* const shapeshifter_transformation = new yli::ontology::ShapeshifterTransformation(
            universe,
            shapeshifter_transformation_struct);

    yli::ontology::SpeciesStruct shapeshifter_form_struct;
    shapeshifter_form_struct.shapeshifter_transformation = shapeshifter_transformation;
    yli::ontology::ShapeshifterForm* const shapeshifter_form = new yli::ontology::ShapeshifterForm(
            universe,
            shapeshifter_form_struct,
            &shapeshifter_transformation->parent_of_shapeshifter_forms);

    yli::ontology::ShapeshifterSequenceStruct shapeshifter_sequence_struct;
    shapeshifter_sequence_struct.parent = shapeshifter_transformation;
    yli::ontology::ShapeshifterSequence* const shapeshifter_sequence = new yli::ontology::ShapeshifterSequence(universe, shapeshifter_sequence_struct);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 8);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world->get_number_of_all_children(), 1);
    ASSERT_EQ(world->get_number_of_all_descendants(), 7);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_all_children(), 2);
    ASSERT_EQ(scene->get_number_of_all_descendants(), 6);

    // `Entity` member functions of `Shader`.
    ASSERT_EQ(shader->get_number_of_all_children(), 1);
    ASSERT_EQ(shader->get_number_of_all_descendants(), 4);

    // `Entity` member functions of `Material`.
    ASSERT_EQ(material->get_number_of_all_children(), 1);
    ASSERT_EQ(material->get_number_of_all_descendants(), 3);

    // `Entity` member functions of `ShapeshifterTransformation`.
    ASSERT_EQ(shapeshifter_transformation->get_number_of_all_children(), 2);
    ASSERT_EQ(shapeshifter_transformation->get_number_of_all_descendants(), 2);

    // `Entity` member functions.
    ASSERT_EQ(shapeshifter_form->get_childID(), 0);
    ASSERT_EQ(shapeshifter_form->get_type(), "yli::ontology::ShapeshifterForm*");
    ASSERT_FALSE(shapeshifter_form->get_can_be_erased());
    ASSERT_EQ(shapeshifter_form->get_universe(), universe);
    ASSERT_NE(shapeshifter_form->get_setting_master(), nullptr);
    ASSERT_EQ(shapeshifter_form->get_parent(), shapeshifter_transformation);
    ASSERT_EQ(shapeshifter_form->get_number_of_all_children(), 0);
    ASSERT_EQ(shapeshifter_form->get_number_of_all_descendants(), 0);

    // `Entity` member functions.
    ASSERT_EQ(shapeshifter_sequence->get_childID(), 0);
    ASSERT_EQ(shapeshifter_sequence->get_type(), "yli::ontology::ShapeshifterSequence*");
    ASSERT_TRUE(shapeshifter_sequence->get_can_be_erased());
    ASSERT_EQ(shapeshifter_sequence->get_universe(), universe);
    ASSERT_NE(shapeshifter_sequence->get_setting_master(), nullptr);
    ASSERT_EQ(shapeshifter_sequence->get_parent(), shapeshifter_transformation);
    ASSERT_EQ(shapeshifter_sequence->get_number_of_all_children(), 0);
    ASSERT_EQ(shapeshifter_sequence->get_number_of_all_descendants(), 0);
}

TEST(shapeshifter_form_and_sequence_must_be_initialized_appropriately, no_universe_no_world_no_scene_no_shader_no_material)
{
    yli::ontology::SpeciesStruct shapeshifter_transformation_struct;
    shapeshifter_transformation_struct.scene = nullptr;
    shapeshifter_transformation_struct.shader = nullptr;
    shapeshifter_transformation_struct.material = nullptr;
    yli::ontology::ShapeshifterTransformation* const shapeshifter_transformation = new yli::ontology::ShapeshifterTransformation(
            nullptr,
            shapeshifter_transformation_struct);

    yli::ontology::SpeciesStruct shapeshifter_form_struct;
    shapeshifter_form_struct.scene = nullptr;
    shapeshifter_form_struct.shader = nullptr;
    shapeshifter_form_struct.material = nullptr;
    shapeshifter_form_struct.shapeshifter_transformation = shapeshifter_transformation;
    yli::ontology::ShapeshifterForm* const shapeshifter_form = new yli::ontology::ShapeshifterForm(
            nullptr,
            shapeshifter_form_struct,
            &shapeshifter_transformation->parent_of_shapeshifter_forms);

    yli::ontology::ShapeshifterSequenceStruct shapeshifter_sequence_struct;
    shapeshifter_sequence_struct.parent = shapeshifter_transformation;
    yli::ontology::ShapeshifterSequence* const shapeshifter_sequence = new yli::ontology::ShapeshifterSequence(nullptr, shapeshifter_sequence_struct);

    // `Entity` member functions of `ShapeshifterTransformation`.
    ASSERT_EQ(shapeshifter_transformation->get_number_of_all_children(), 2);
    ASSERT_EQ(shapeshifter_transformation->get_number_of_all_descendants(), 2);

    // `Entity` member functions.
    ASSERT_EQ(shapeshifter_form->get_childID(), 0);
    ASSERT_EQ(shapeshifter_form->get_type(), "yli::ontology::ShapeshifterForm*");
    ASSERT_FALSE(shapeshifter_form->get_can_be_erased());
    ASSERT_EQ(shapeshifter_form->get_universe(), nullptr);
    ASSERT_NE(shapeshifter_form->get_setting_master(), nullptr);
    ASSERT_EQ(shapeshifter_form->get_parent(), shapeshifter_transformation);
    ASSERT_EQ(shapeshifter_form->get_number_of_all_children(), 0);
    ASSERT_EQ(shapeshifter_form->get_number_of_all_descendants(), 0);

    // `Entity` member functions.
    ASSERT_EQ(shapeshifter_sequence->get_childID(), 0);
    ASSERT_EQ(shapeshifter_sequence->get_type(), "yli::ontology::ShapeshifterSequence*");
    ASSERT_TRUE(shapeshifter_sequence->get_can_be_erased());
    ASSERT_EQ(shapeshifter_sequence->get_universe(), nullptr);
    ASSERT_NE(shapeshifter_sequence->get_setting_master(), nullptr);
    ASSERT_EQ(shapeshifter_sequence->get_parent(), shapeshifter_transformation);
    ASSERT_EQ(shapeshifter_sequence->get_number_of_all_children(), 0);
    ASSERT_EQ(shapeshifter_sequence->get_number_of_all_descendants(), 0);
}

TEST(shapeshifter_object_must_be_initialized_appropriately, headless)
{
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

    yli::ontology::MaterialStruct material_struct;
    material_struct.shader = shader;
    yli::ontology::Material* const material = new yli::ontology::Material(universe, material_struct, &shader->parent_of_materials);

    yli::ontology::SpeciesStruct shapeshifter_transformation_struct;
    shapeshifter_transformation_struct.scene = scene;
    shapeshifter_transformation_struct.shader = shader;
    shapeshifter_transformation_struct.material = material;
    yli::ontology::ShapeshifterTransformation* const shapeshifter_transformation = new yli::ontology::ShapeshifterTransformation(
            universe,
            shapeshifter_transformation_struct);

    yli::ontology::SpeciesStruct shapeshifter_form_struct;
    shapeshifter_form_struct.shapeshifter_transformation = shapeshifter_transformation;
    yli::ontology::ShapeshifterForm* const shapeshifter_form = new yli::ontology::ShapeshifterForm(
            universe,
            shapeshifter_form_struct,
            &shapeshifter_transformation->parent_of_shapeshifter_forms);

    yli::ontology::ShapeshifterSequenceStruct shapeshifter_sequence_struct;
    shapeshifter_sequence_struct.parent = shapeshifter_transformation;
    yli::ontology::ShapeshifterSequence* const shapeshifter_sequence = new yli::ontology::ShapeshifterSequence(universe, shapeshifter_sequence_struct);

    yli::ontology::ObjectStruct object_struct;
    object_struct.shapeshifter_sequence_parent = shapeshifter_sequence;
    object_struct.object_type = yli::ontology::ObjectType::SHAPESHIFTER;
    yli::ontology::Object* const object = new yli::ontology::Object(universe, object_struct, &shapeshifter_sequence->parent_of_objects);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 9);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world->get_number_of_all_children(), 1);
    ASSERT_EQ(world->get_number_of_all_descendants(), 8);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_all_children(), 2);
    ASSERT_EQ(scene->get_number_of_all_descendants(), 7);

    // `Entity` member functions of `Shader`.
    ASSERT_EQ(shader->get_number_of_all_children(), 1);
    ASSERT_EQ(shader->get_number_of_all_descendants(), 5);

    // `Entity` member functions of `Material`.
    ASSERT_EQ(material->get_number_of_all_children(), 1);
    ASSERT_EQ(material->get_number_of_all_descendants(), 4);

    // `Entity` member functions of `ShapeshifterTransformation`.
    ASSERT_EQ(shapeshifter_transformation->get_number_of_all_children(), 2);
    ASSERT_EQ(shapeshifter_transformation->get_number_of_all_descendants(), 3);

    // `Entity` member functions of `ShapeshifterForm`.
    ASSERT_EQ(shapeshifter_form->get_number_of_all_children(), 0);
    ASSERT_EQ(shapeshifter_form->get_number_of_all_descendants(), 0);

    // `Entity` member functions of `ShapeshifterSequence`.
    ASSERT_EQ(shapeshifter_sequence->get_number_of_all_children(), 1);
    ASSERT_EQ(shapeshifter_sequence->get_number_of_all_descendants(), 1);

    // `Entity` member functions.
    ASSERT_EQ(object->get_childID(), 0);
    ASSERT_EQ(object->get_type(), "yli::ontology::Object*");
    ASSERT_TRUE(object->get_can_be_erased());
    ASSERT_EQ(object->get_universe(), universe);
    ASSERT_NE(object->get_setting_master(), nullptr);
    ASSERT_EQ(object->get_glyph(), nullptr);
    ASSERT_EQ(object->get_parent(), shapeshifter_sequence);
    ASSERT_EQ(object->get_number_of_all_children(), 0);
    ASSERT_EQ(object->get_number_of_all_descendants(), 0);
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
    yli::ontology::ShapeshifterForm* const shapeshifter_form = new yli::ontology::ShapeshifterForm(
            nullptr,
            shapeshifter_form_struct,
            &shapeshifter_transformation->parent_of_shapeshifter_forms);

    yli::ontology::ShapeshifterSequenceStruct shapeshifter_sequence_struct;
    shapeshifter_sequence_struct.parent = shapeshifter_transformation;
    yli::ontology::ShapeshifterSequence* const shapeshifter_sequence = new yli::ontology::ShapeshifterSequence(nullptr, shapeshifter_sequence_struct);

    yli::ontology::ObjectStruct object_struct;
    object_struct.shapeshifter_sequence_parent = shapeshifter_sequence;
    object_struct.object_type = yli::ontology::ObjectType::SHAPESHIFTER;
    yli::ontology::Object* const object = new yli::ontology::Object(nullptr, object_struct, &shapeshifter_sequence->parent_of_objects);

    // `Entity` member functions of `ShapeshifterTransformation`.
    ASSERT_EQ(shapeshifter_transformation->get_number_of_all_children(), 2);
    ASSERT_EQ(shapeshifter_transformation->get_number_of_all_descendants(), 3);

    // `Entity` member functions of `ShapeshifterForm`.
    ASSERT_EQ(shapeshifter_form->get_number_of_all_children(), 0);
    ASSERT_EQ(shapeshifter_form->get_number_of_all_descendants(), 0);

    // `Entity` member functions of `ShapeshifterSequence`.
    ASSERT_EQ(shapeshifter_sequence->get_number_of_all_children(), 1);
    ASSERT_EQ(shapeshifter_sequence->get_number_of_all_descendants(), 1);

    // `Entity` member functions.
    ASSERT_EQ(object->get_childID(), 0);
    ASSERT_EQ(object->get_type(), "yli::ontology::Object*");
    ASSERT_TRUE(object->get_can_be_erased());
    ASSERT_EQ(object->get_universe(), nullptr);
    ASSERT_NE(object->get_setting_master(), nullptr);
    ASSERT_EQ(object->get_glyph(), nullptr);
    ASSERT_EQ(object->get_parent(), shapeshifter_sequence);
    ASSERT_EQ(object->get_number_of_all_children(), 0);
    ASSERT_EQ(object->get_number_of_all_descendants(), 0);
}

TEST(shapeshifter_object_must_be_initialized_appropriately, no_universe_no_world_no_scene_no_shader_no_material_no_shapeshifter_transformation)
{
    yli::ontology::SpeciesStruct shapeshifter_form_struct;
    shapeshifter_form_struct.scene = nullptr;
    shapeshifter_form_struct.shader = nullptr;
    shapeshifter_form_struct.material = nullptr;
    shapeshifter_form_struct.shapeshifter_transformation = nullptr;
    yli::ontology::ShapeshifterForm* const shapeshifter_form = new yli::ontology::ShapeshifterForm(nullptr, shapeshifter_form_struct, nullptr);

    yli::ontology::ShapeshifterSequenceStruct shapeshifter_sequence_struct;
    shapeshifter_sequence_struct.parent = nullptr;
    yli::ontology::ShapeshifterSequence* const shapeshifter_sequence = new yli::ontology::ShapeshifterSequence(nullptr, shapeshifter_sequence_struct);

    yli::ontology::ObjectStruct object_struct;
    object_struct.shapeshifter_sequence_parent = shapeshifter_sequence;
    object_struct.object_type = yli::ontology::ObjectType::SHAPESHIFTER;
    yli::ontology::Object* const object = new yli::ontology::Object(nullptr, object_struct, &shapeshifter_sequence->parent_of_objects);

    // `Entity` member functions.
    ASSERT_EQ(object->get_childID(), 0);
    ASSERT_EQ(object->get_type(), "yli::ontology::Object*");
    ASSERT_TRUE(object->get_can_be_erased());
    ASSERT_EQ(object->get_universe(), nullptr);
    ASSERT_NE(object->get_setting_master(), nullptr);
    ASSERT_EQ(object->get_glyph(), nullptr);
    ASSERT_EQ(object->get_parent(), shapeshifter_sequence);
    ASSERT_EQ(object->get_number_of_all_children(), 0);
    ASSERT_EQ(object->get_number_of_all_descendants(), 0);
}

TEST(brain_must_be_initialized_appropriately, headless)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(universe, world_struct, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);

    yli::ontology::BrainStruct brain_struct;
    brain_struct.parent = scene;
    yli::ontology::Brain* const brain = new yli::ontology::Brain(universe, brain_struct, &scene->parent_of_brains);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 4);

    // `Entity` member functions of `World`.
    ASSERT_EQ(world->get_number_of_all_children(), 1);
    ASSERT_EQ(world->get_number_of_all_descendants(), 3);

    // `Entity` member functions of `Scene`.
    ASSERT_EQ(scene->get_number_of_all_children(), 2);
    ASSERT_EQ(scene->get_number_of_all_descendants(), 2);

    // `Brain` member functions.
    ASSERT_EQ(brain->get_number_of_apprentices(), 0);

    // `Entity` member functions.
    ASSERT_EQ(brain->get_childID(), 0);
    ASSERT_EQ(brain->get_type(), "yli::ontology::Brain*");
    ASSERT_TRUE(brain->get_can_be_erased());
    ASSERT_EQ(brain->get_universe(), universe);
    ASSERT_NE(brain->get_setting_master(), nullptr);
    ASSERT_EQ(brain->get_parent(), scene);
    ASSERT_EQ(brain->get_number_of_all_children(), 0);
    ASSERT_EQ(brain->get_number_of_all_descendants(), 0);
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
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 1);

    // `Entity` member functions of `Font2D`.
    ASSERT_EQ(font2D->get_childID(), 0);
    ASSERT_EQ(font2D->get_type(), "yli::ontology::Font2D*");
    ASSERT_FALSE(font2D->get_can_be_erased());               // Currently `Font2D`s can not be erased.
    ASSERT_EQ(font2D->get_universe(), universe);
    ASSERT_NE(font2D->get_setting_master(), nullptr);
    ASSERT_EQ(font2D->get_parent(), universe);
    ASSERT_EQ(font2D->get_number_of_all_children(), 0);
    ASSERT_EQ(font2D->get_number_of_all_descendants(), 0);
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
    ASSERT_EQ(font2D->get_number_of_all_children(), 0);
    ASSERT_EQ(font2D->get_number_of_all_descendants(), 0);
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
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 1);

    // `Entity` member functions of `Font2D`.
    ASSERT_EQ(font2D->get_childID(), 0);
    ASSERT_EQ(font2D->get_type(), "yli::ontology::Font2D*");
    ASSERT_FALSE(font2D->get_can_be_erased());               // Currently `Font2D`s can not be erased.
    ASSERT_EQ(font2D->get_universe(), universe);
    ASSERT_NE(font2D->get_setting_master(), nullptr);
    ASSERT_EQ(font2D->get_parent(), universe);
    ASSERT_EQ(font2D->get_number_of_all_children(), 0);
    ASSERT_EQ(font2D->get_number_of_all_descendants(), 0);
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
    ASSERT_EQ(font2D->get_number_of_all_children(), 0);
    ASSERT_EQ(font2D->get_number_of_all_descendants(), 0);
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
    ASSERT_EQ(brain->get_number_of_all_children(), 0);
    ASSERT_EQ(brain->get_number_of_all_descendants(), 0);
}

TEST(scene_must_be_activated_appropriately, scene)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(universe, world_struct, &universe->parent_of_worlds);

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

    yli::ontology::WorldStruct world_struct1;
    yli::ontology::World* const world1 = new yli::ontology::World(universe, world_struct1, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world1;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world1->parent_of_scenes);
    ASSERT_EQ(scene->get_parent(), world1);
    ASSERT_EQ(world1->get_number_of_all_children(), 1);
    ASSERT_EQ(world1->get_number_of_all_descendants(), 2);

    yli::ontology::WorldStruct world_struct2;
    yli::ontology::World* const world2 = new yli::ontology::World(universe, world_struct2, &universe->parent_of_worlds);
    ASSERT_EQ(scene->get_parent(), world1);
    ASSERT_EQ(world2->get_number_of_all_children(), 0);
    ASSERT_EQ(world2->get_number_of_all_descendants(), 0);

    scene->bind_to_new_parent(world2);
    ASSERT_EQ(scene->get_parent(), world2);
    ASSERT_EQ(world1->get_number_of_all_children(), 0);
    ASSERT_EQ(world1->get_number_of_all_descendants(), 0);
    ASSERT_EQ(world2->get_number_of_all_children(), 1);
    ASSERT_EQ(world2->get_number_of_all_descendants(), 2);
    ASSERT_EQ(universe->get_number_of_all_children(), 2);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 4);

    scene->bind_to_new_parent(world1);
    ASSERT_EQ(scene->get_parent(), world1);
    ASSERT_EQ(world1->get_number_of_all_children(), 1);
    ASSERT_EQ(world1->get_number_of_all_descendants(), 2);
    ASSERT_EQ(world2->get_number_of_all_children(), 0);
    ASSERT_EQ(world2->get_number_of_all_descendants(), 0);
    ASSERT_EQ(universe->get_number_of_all_children(), 2);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 4);
}

TEST(active_scene_must_remain_active_scene_after_binding_to_a_new_parent, scene)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct1;
    yli::ontology::World* const world1 = new yli::ontology::World(universe, world_struct1, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world1;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world1->parent_of_scenes);
    universe->set_active_scene(scene);
    ASSERT_EQ(universe->get_active_scene(), scene);

    yli::ontology::WorldStruct world_struct2;
    yli::ontology::World* const world2 = new yli::ontology::World(universe, world_struct2, &universe->parent_of_worlds);
    scene->bind_to_new_parent(world2);
    ASSERT_EQ(universe->get_active_scene(), scene);
}

TEST(inactive_scene_must_remain_inactive_scene_after_binding_to_a_new_parent, scene)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct1;
    yli::ontology::World* const world1 = new yli::ontology::World(universe, world_struct1, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world1;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world1->parent_of_scenes);
    ASSERT_EQ(universe->get_active_scene(), nullptr);

    yli::ontology::WorldStruct world_struct2;
    yli::ontology::World* const world2 = new yli::ontology::World(universe, world_struct2, &universe->parent_of_worlds);
    scene->bind_to_new_parent(world2);
    ASSERT_EQ(universe->get_active_scene(), nullptr);
}

TEST(shader_must_bind_to_scene_appropriately, scenes_of_the_same_world)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(universe, world_struct, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene1 = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene1;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(universe, shader_struct);
    ASSERT_EQ(shader->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_all_children(), 2);

    yli::ontology::Scene* const scene2 = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);
    ASSERT_EQ(shader->get_parent(), scene1);
    ASSERT_EQ(scene2->get_number_of_all_children(), 1);

    shader->bind_to_new_parent(scene2);
    ASSERT_EQ(shader->get_parent(), scene2);
    ASSERT_EQ(scene1->get_number_of_all_children(), 1);
    ASSERT_EQ(scene1->get_number_of_all_descendants(), 1);
    ASSERT_EQ(scene2->get_number_of_all_children(), 2);
    ASSERT_EQ(scene2->get_number_of_all_descendants(), 2);
    ASSERT_EQ(world->get_number_of_all_children(), 2);
    ASSERT_EQ(world->get_number_of_all_descendants(), 5);
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 6);

    shader->bind_to_new_parent(scene1);
    ASSERT_EQ(shader->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_all_children(), 2);
    ASSERT_EQ(scene1->get_number_of_all_descendants(), 2);
    ASSERT_EQ(scene2->get_number_of_all_children(), 1);
    ASSERT_EQ(scene2->get_number_of_all_descendants(), 1);
    ASSERT_EQ(world->get_number_of_all_children(), 2);
    ASSERT_EQ(world->get_number_of_all_descendants(), 5);
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 6);
}

TEST(shader_must_bind_to_scene_appropriately, scenes_of_the_different_worlds)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct1;
    yli::ontology::World* const world1 = new yli::ontology::World(universe, world_struct1, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct1;
    scene_struct1.world = world1;
    yli::ontology::Scene* const scene1 = new yli::ontology::Scene(universe, scene_struct1, &world1->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene1;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(universe, shader_struct);
    ASSERT_EQ(shader->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_all_children(), 2);
    ASSERT_EQ(scene1->get_number_of_all_descendants(), 2);

    yli::ontology::WorldStruct world_struct2;
    yli::ontology::World* const world2 = new yli::ontology::World(universe, world_struct2, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct2;
    scene_struct2.world = world2;
    yli::ontology::Scene* const scene2 = new yli::ontology::Scene(universe, scene_struct2, &world2->parent_of_scenes);
    ASSERT_EQ(shader->get_parent(), scene1);
    ASSERT_EQ(world2->get_number_of_all_children(), 1);
    ASSERT_EQ(world2->get_number_of_all_descendants(), 2);
    ASSERT_EQ(scene2->get_number_of_all_children(), 1);
    ASSERT_EQ(scene2->get_number_of_all_descendants(), 1);

    shader->bind_to_new_parent(scene2);
    ASSERT_EQ(shader->get_parent(), scene2);
    ASSERT_EQ(scene1->get_number_of_all_children(), 1);
    ASSERT_EQ(scene1->get_number_of_all_descendants(), 1);
    ASSERT_EQ(scene2->get_number_of_all_children(), 2);
    ASSERT_EQ(scene2->get_number_of_all_descendants(), 2);
    ASSERT_EQ(world1->get_number_of_all_children(), 1);
    ASSERT_EQ(world1->get_number_of_all_descendants(), 2);
    ASSERT_EQ(world2->get_number_of_all_children(), 1);
    ASSERT_EQ(world2->get_number_of_all_descendants(), 3);
    ASSERT_EQ(universe->get_number_of_all_children(), 2);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 7);

    shader->bind_to_new_parent(scene1);
    ASSERT_EQ(shader->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_all_children(), 2);
    ASSERT_EQ(scene1->get_number_of_all_descendants(), 2);
    ASSERT_EQ(scene2->get_number_of_all_children(), 1);
    ASSERT_EQ(scene2->get_number_of_all_descendants(), 1);
    ASSERT_EQ(world1->get_number_of_all_children(), 1);
    ASSERT_EQ(world1->get_number_of_all_descendants(), 3);
    ASSERT_EQ(world2->get_number_of_all_children(), 1);
    ASSERT_EQ(world2->get_number_of_all_descendants(), 2);
    ASSERT_EQ(universe->get_number_of_all_children(), 2);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 7);
}

TEST(material_must_bind_to_shader_appropriately, shaders_of_the_same_scene)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(universe, world_struct, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct1;
    scene_struct1.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct1, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct1;
    shader_struct1.parent = scene;
    yli::ontology::Shader* const shader1 = new yli::ontology::Shader(universe, shader_struct1);
    ASSERT_EQ(shader1->get_number_of_all_children(), 0);
    ASSERT_EQ(shader1->get_number_of_all_descendants(), 0);

    yli::ontology::MaterialStruct material_struct;
    material_struct.shader = shader1;
    yli::ontology::Material* const material = new yli::ontology::Material(universe, material_struct, &shader1->parent_of_materials);
    ASSERT_EQ(material->get_parent(), shader1);
    ASSERT_EQ(shader1->get_number_of_all_children(), 1);
    ASSERT_EQ(shader1->get_number_of_all_descendants(), 1);

    yli::ontology::ShaderStruct shader_struct2;
    shader_struct2.parent = scene;
    yli::ontology::Shader* const shader2 = new yli::ontology::Shader(universe, shader_struct2);
    ASSERT_EQ(shader2->get_number_of_all_children(), 0);
    ASSERT_EQ(shader2->get_number_of_all_descendants(), 0);

    material->bind_to_new_parent(shader2);
    ASSERT_EQ(material->get_parent(), shader2);
    ASSERT_EQ(shader1->get_number_of_all_children(), 0);
    ASSERT_EQ(shader1->get_number_of_all_descendants(), 0);
    ASSERT_EQ(shader2->get_number_of_all_children(), 1);
    ASSERT_EQ(shader2->get_number_of_all_descendants(), 1);
    ASSERT_EQ(scene->get_number_of_all_children(), 3);
    ASSERT_EQ(scene->get_number_of_all_descendants(), 4);
    ASSERT_EQ(world->get_number_of_all_children(), 1);
    ASSERT_EQ(world->get_number_of_all_descendants(), 5);
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 6);

    material->bind_to_new_parent(shader1);
    ASSERT_EQ(material->get_parent(), shader1);
    ASSERT_EQ(shader1->get_number_of_all_children(), 1);
    ASSERT_EQ(shader1->get_number_of_all_descendants(), 1);
    ASSERT_EQ(shader2->get_number_of_all_children(), 0);
    ASSERT_EQ(shader2->get_number_of_all_descendants(), 0);
    ASSERT_EQ(scene->get_number_of_all_children(), 3);
    ASSERT_EQ(scene->get_number_of_all_descendants(), 4);
    ASSERT_EQ(world->get_number_of_all_children(), 1);
    ASSERT_EQ(world->get_number_of_all_descendants(), 5);
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 6);
}

TEST(material_must_bind_to_shader_appropriately, shaders_of_different_scenes)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(universe, world_struct, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct1;
    scene_struct1.world = world;
    yli::ontology::Scene* const scene1 = new yli::ontology::Scene(universe, scene_struct1, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct1;
    shader_struct1.parent = scene1;
    yli::ontology::Shader* const shader1 = new yli::ontology::Shader(universe, shader_struct1);
    ASSERT_EQ(shader1->get_number_of_all_children(), 0);
    ASSERT_EQ(shader1->get_number_of_all_descendants(), 0);

    yli::ontology::MaterialStruct material_struct;
    material_struct.shader = shader1;
    yli::ontology::Material* const material = new yli::ontology::Material(universe, material_struct, &shader1->parent_of_materials);
    ASSERT_EQ(material->get_parent(), shader1);
    ASSERT_EQ(shader1->get_number_of_all_children(), 1);
    ASSERT_EQ(shader1->get_number_of_all_descendants(), 1);

    yli::ontology::SceneStruct scene_struct2;
    scene_struct2.world = world;
    yli::ontology::Scene* const scene2 = new yli::ontology::Scene(universe, scene_struct2, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct2;
    shader_struct2.parent = scene2;
    yli::ontology::Shader* const shader2 = new yli::ontology::Shader(universe, shader_struct2);
    ASSERT_EQ(shader2->get_number_of_all_children(), 0);
    ASSERT_EQ(shader2->get_number_of_all_descendants(), 0);

    material->bind_to_new_parent(shader2);
    ASSERT_EQ(material->get_parent(), shader2);
    ASSERT_EQ(shader1->get_number_of_all_children(), 0);
    ASSERT_EQ(shader1->get_number_of_all_descendants(), 0);
    ASSERT_EQ(shader2->get_number_of_all_children(), 1);
    ASSERT_EQ(shader2->get_number_of_all_descendants(), 1);
    ASSERT_EQ(scene1->get_number_of_all_children(), 2);
    ASSERT_EQ(scene1->get_number_of_all_descendants(), 2);
    ASSERT_EQ(scene2->get_number_of_all_children(), 2);
    ASSERT_EQ(scene2->get_number_of_all_descendants(), 3);
    ASSERT_EQ(world->get_number_of_all_children(), 2);
    ASSERT_EQ(world->get_number_of_all_descendants(), 7);
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 8);

    material->bind_to_new_parent(shader1);
    ASSERT_EQ(material->get_parent(), shader1);
    ASSERT_EQ(shader1->get_number_of_all_children(), 1);
    ASSERT_EQ(shader1->get_number_of_all_descendants(), 1);
    ASSERT_EQ(shader2->get_number_of_all_children(), 0);
    ASSERT_EQ(shader2->get_number_of_all_descendants(), 0);
    ASSERT_EQ(scene1->get_number_of_all_children(), 2);
    ASSERT_EQ(scene1->get_number_of_all_descendants(), 3);
    ASSERT_EQ(scene2->get_number_of_all_children(), 2);
    ASSERT_EQ(scene2->get_number_of_all_descendants(), 2);
    ASSERT_EQ(world->get_number_of_all_children(), 2);
    ASSERT_EQ(world->get_number_of_all_descendants(), 7);
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 8);
}

TEST(species_must_bind_to_material_appropriately, materials_of_the_same_shader)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(universe, world_struct, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct1;
    scene_struct1.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct1, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(universe, shader_struct);

    yli::ontology::MaterialStruct material_struct1;
    material_struct1.shader = shader;
    yli::ontology::Material* const material1 = new yli::ontology::Material(universe, material_struct1, &shader->parent_of_materials);

    yli::ontology::SpeciesStruct species_struct;
    species_struct.scene = scene;
    species_struct.shader = shader;
    species_struct.material = material1;
    yli::ontology::Species* const species = new yli::ontology::Species(universe, species_struct, &material1->parent_of_species);
    ASSERT_EQ(species->get_parent(), material1);
    ASSERT_EQ(material1->get_number_of_all_children(), 1);
    ASSERT_EQ(material1->get_number_of_all_descendants(), 1);

    yli::ontology::MaterialStruct material_struct2;
    material_struct2.shader = shader;
    yli::ontology::Material* const material2 = new yli::ontology::Material(universe, material_struct2, &shader->parent_of_materials);
    ASSERT_EQ(material2->get_number_of_all_children(), 0);
    ASSERT_EQ(material2->get_number_of_all_descendants(), 0);

    species->bind_to_new_parent(material2);
    ASSERT_EQ(species->get_parent(), material2);
    ASSERT_EQ(material1->get_number_of_all_children(), 0);
    ASSERT_EQ(material1->get_number_of_all_descendants(), 0);
    ASSERT_EQ(material2->get_number_of_all_children(), 1);
    ASSERT_EQ(material2->get_number_of_all_descendants(), 1);
    ASSERT_EQ(shader->get_number_of_all_children(), 2);
    ASSERT_EQ(shader->get_number_of_all_descendants(), 3);
    ASSERT_EQ(scene->get_number_of_all_children(), 2);
    ASSERT_EQ(scene->get_number_of_all_descendants(), 5);
    ASSERT_EQ(world->get_number_of_all_children(), 1);
    ASSERT_EQ(world->get_number_of_all_descendants(), 6);
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 7);

    species->bind_to_new_parent(material1);
    ASSERT_EQ(species->get_parent(), material1);
    ASSERT_EQ(material1->get_number_of_all_children(), 1);
    ASSERT_EQ(material1->get_number_of_all_descendants(), 1);
    ASSERT_EQ(material2->get_number_of_all_children(), 0);
    ASSERT_EQ(material2->get_number_of_all_descendants(), 0);
    ASSERT_EQ(shader->get_number_of_all_children(), 2);
    ASSERT_EQ(shader->get_number_of_all_descendants(), 3);
    ASSERT_EQ(scene->get_number_of_all_children(), 2);
    ASSERT_EQ(scene->get_number_of_all_descendants(), 5);
    ASSERT_EQ(world->get_number_of_all_children(), 1);
    ASSERT_EQ(world->get_number_of_all_descendants(), 6);
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 7);
}

TEST(species_must_bind_to_material_appropriately, materials_of_different_shaders)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(universe, world_struct, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct1;
    scene_struct1.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct1, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct1;
    shader_struct1.parent = scene;
    yli::ontology::Shader* const shader1 = new yli::ontology::Shader(universe, shader_struct1);

    yli::ontology::MaterialStruct material_struct1;
    material_struct1.shader = shader1;
    yli::ontology::Material* const material1 = new yli::ontology::Material(universe, material_struct1, &shader1->parent_of_materials);

    yli::ontology::SpeciesStruct species_struct;
    species_struct.scene = scene;
    species_struct.shader = shader1;
    species_struct.material = material1;
    yli::ontology::Species* const species = new yli::ontology::Species(universe, species_struct, &material1->parent_of_species);
    ASSERT_EQ(species->get_parent(), material1);
    ASSERT_EQ(material1->get_number_of_all_children(), 1);
    ASSERT_EQ(material1->get_number_of_all_descendants(), 1);

    yli::ontology::ShaderStruct shader_struct2;
    shader_struct2.parent = scene;
    yli::ontology::Shader* const shader2 = new yli::ontology::Shader(universe, shader_struct2);

    yli::ontology::MaterialStruct material_struct2;
    material_struct2.shader = shader2;
    yli::ontology::Material* const material2 = new yli::ontology::Material(universe, material_struct2, &shader2->parent_of_materials);
    ASSERT_EQ(material2->get_number_of_all_children(), 0);
    ASSERT_EQ(material2->get_number_of_all_descendants(), 0);

    species->bind_to_new_parent(material2);
    ASSERT_EQ(species->get_parent(), material2);
    ASSERT_EQ(material1->get_number_of_all_children(), 0);
    ASSERT_EQ(material1->get_number_of_all_descendants(), 0);
    ASSERT_EQ(material2->get_number_of_all_children(), 1);
    ASSERT_EQ(material2->get_number_of_all_descendants(), 1);
    ASSERT_EQ(shader1->get_number_of_all_children(), 1);
    ASSERT_EQ(shader1->get_number_of_all_descendants(), 1);
    ASSERT_EQ(shader2->get_number_of_all_children(), 1);
    ASSERT_EQ(shader2->get_number_of_all_descendants(), 2);
    ASSERT_EQ(scene->get_number_of_all_children(), 3);
    ASSERT_EQ(scene->get_number_of_all_descendants(), 6);
    ASSERT_EQ(world->get_number_of_all_children(), 1);
    ASSERT_EQ(world->get_number_of_all_descendants(), 7);
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 8);

    species->bind_to_new_parent(material1);
    ASSERT_EQ(species->get_parent(), material1);
    ASSERT_EQ(material1->get_number_of_all_children(), 1);
    ASSERT_EQ(material1->get_number_of_all_descendants(), 1);
    ASSERT_EQ(material2->get_number_of_all_children(), 0);
    ASSERT_EQ(material2->get_number_of_all_descendants(), 0);
    ASSERT_EQ(shader1->get_number_of_all_children(), 1);
    ASSERT_EQ(shader1->get_number_of_all_descendants(), 2);
    ASSERT_EQ(shader2->get_number_of_all_children(), 1);
    ASSERT_EQ(shader2->get_number_of_all_descendants(), 1);
    ASSERT_EQ(scene->get_number_of_all_children(), 3);
    ASSERT_EQ(scene->get_number_of_all_descendants(), 6);
    ASSERT_EQ(world->get_number_of_all_children(), 1);
    ASSERT_EQ(world->get_number_of_all_descendants(), 7);
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 8);
}

TEST(object_must_bind_to_species_appropriately, species_of_the_same_material)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(universe, world_struct, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct1;
    scene_struct1.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct1, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(universe, shader_struct);

    yli::ontology::MaterialStruct material_struct;
    material_struct.shader = shader;
    yli::ontology::Material* const material = new yli::ontology::Material(universe, material_struct, &shader->parent_of_materials);

    yli::ontology::SpeciesStruct species_struct1;
    species_struct1.scene = scene;
    species_struct1.shader = shader;
    species_struct1.material = material;
    yli::ontology::Species* const species1 = new yli::ontology::Species(universe, species_struct1, &material->parent_of_species);

    yli::ontology::ObjectStruct object_struct;
    object_struct.species_parent = species1;
    yli::ontology::Object* const object = new yli::ontology::Object(universe, object_struct, &species1->parent_of_objects);
    ASSERT_EQ(object->get_parent(), species1);
    ASSERT_EQ(species1->get_number_of_all_children(), 1);
    ASSERT_EQ(species1->get_number_of_all_descendants(), 1);

    yli::ontology::SpeciesStruct species_struct2;
    species_struct2.scene = scene;
    species_struct2.shader = shader;
    species_struct2.material = material;
    yli::ontology::Species* const species2 = new yli::ontology::Species(universe, species_struct2, &material->parent_of_species);

    object->bind_to_new_parent(species2);
    ASSERT_EQ(object->get_parent(), species2);
    ASSERT_EQ(species1->get_number_of_all_children(), 0);
    ASSERT_EQ(species1->get_number_of_all_descendants(), 0);
    ASSERT_EQ(species2->get_number_of_all_children(), 1);
    ASSERT_EQ(species2->get_number_of_all_descendants(), 1);
    ASSERT_EQ(material->get_number_of_all_children(), 2);
    ASSERT_EQ(material->get_number_of_all_descendants(), 3);
    ASSERT_EQ(shader->get_number_of_all_children(), 1);
    ASSERT_EQ(shader->get_number_of_all_descendants(), 4);
    ASSERT_EQ(scene->get_number_of_all_children(), 2);
    ASSERT_EQ(scene->get_number_of_all_descendants(), 6);
    ASSERT_EQ(world->get_number_of_all_children(), 1);
    ASSERT_EQ(world->get_number_of_all_descendants(), 7);
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 8);

    object->bind_to_new_parent(species1);
    ASSERT_EQ(object->get_parent(), species1);
    ASSERT_EQ(species1->get_number_of_all_children(), 1);
    ASSERT_EQ(species1->get_number_of_all_descendants(), 1);
    ASSERT_EQ(species2->get_number_of_all_children(), 0);
    ASSERT_EQ(species2->get_number_of_all_descendants(), 0);
    ASSERT_EQ(material->get_number_of_all_children(), 2);
    ASSERT_EQ(material->get_number_of_all_descendants(), 3);
    ASSERT_EQ(shader->get_number_of_all_children(), 1);
    ASSERT_EQ(shader->get_number_of_all_descendants(), 4);
    ASSERT_EQ(scene->get_number_of_all_children(), 2);
    ASSERT_EQ(scene->get_number_of_all_descendants(), 6);
    ASSERT_EQ(world->get_number_of_all_children(), 1);
    ASSERT_EQ(world->get_number_of_all_descendants(), 7);
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 8);
}

TEST(object_must_bind_to_species_appropriately, species_of_different_materials)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(universe, world_struct, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct1;
    scene_struct1.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct1, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(universe, shader_struct);

    yli::ontology::MaterialStruct material_struct1;
    material_struct1.shader = shader;
    yli::ontology::Material* const material1 = new yli::ontology::Material(universe, material_struct1, &shader->parent_of_materials);

    yli::ontology::SpeciesStruct species_struct1;
    species_struct1.scene = scene;
    species_struct1.shader = shader;
    species_struct1.material = material1;
    yli::ontology::Species* const species1 = new yli::ontology::Species(universe, species_struct1, &material1->parent_of_species);

    yli::ontology::ObjectStruct object_struct;
    object_struct.species_parent = species1;
    yli::ontology::Object* const object = new yli::ontology::Object(universe, object_struct, &species1->parent_of_objects);
    ASSERT_EQ(object->get_parent(), species1);
    ASSERT_EQ(species1->get_number_of_all_children(), 1);
    ASSERT_EQ(species1->get_number_of_all_descendants(), 1);

    yli::ontology::MaterialStruct material_struct2;
    material_struct2.shader = shader;
    yli::ontology::Material* const material2 = new yli::ontology::Material(universe, material_struct2, &shader->parent_of_materials);

    yli::ontology::SpeciesStruct species_struct2;
    species_struct2.scene = scene;
    species_struct2.shader = shader;
    species_struct2.material = material2;
    yli::ontology::Species* const species2 = new yli::ontology::Species(universe, species_struct2, &material2->parent_of_species);

    object->bind_to_new_parent(species2);
    ASSERT_EQ(object->get_parent(), species2);
    ASSERT_EQ(species1->get_number_of_all_children(), 0);
    ASSERT_EQ(species1->get_number_of_all_descendants(), 0);
    ASSERT_EQ(species2->get_number_of_all_children(), 1);
    ASSERT_EQ(species2->get_number_of_all_descendants(), 1);
    ASSERT_EQ(material1->get_number_of_all_children(), 1);
    ASSERT_EQ(material1->get_number_of_all_descendants(), 1);
    ASSERT_EQ(material2->get_number_of_all_children(), 1);
    ASSERT_EQ(material2->get_number_of_all_descendants(), 2);
    ASSERT_EQ(shader->get_number_of_all_children(), 2);
    ASSERT_EQ(shader->get_number_of_all_descendants(), 5);
    ASSERT_EQ(scene->get_number_of_all_children(), 2);
    ASSERT_EQ(scene->get_number_of_all_descendants(), 7);
    ASSERT_EQ(world->get_number_of_all_children(), 1);
    ASSERT_EQ(world->get_number_of_all_descendants(), 8);
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 9);

    object->bind_to_new_parent(species1);
    ASSERT_EQ(object->get_parent(), species1);
    ASSERT_EQ(species1->get_number_of_all_children(), 1);
    ASSERT_EQ(species1->get_number_of_all_descendants(), 1);
    ASSERT_EQ(species2->get_number_of_all_children(), 0);
    ASSERT_EQ(species2->get_number_of_all_descendants(), 0);
    ASSERT_EQ(material1->get_number_of_all_children(), 1);
    ASSERT_EQ(material1->get_number_of_all_descendants(), 2);
    ASSERT_EQ(material2->get_number_of_all_children(), 1);
    ASSERT_EQ(material2->get_number_of_all_descendants(), 1);
    ASSERT_EQ(shader->get_number_of_all_children(), 2);
    ASSERT_EQ(shader->get_number_of_all_descendants(), 5);
    ASSERT_EQ(scene->get_number_of_all_children(), 2);
    ASSERT_EQ(scene->get_number_of_all_descendants(), 7);
    ASSERT_EQ(world->get_number_of_all_children(), 1);
    ASSERT_EQ(world->get_number_of_all_descendants(), 8);
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 9);
}

TEST(shapeshifter_transformation_must_bind_to_material_appropriately, materials_of_the_same_shader)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(universe, world_struct, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct1;
    scene_struct1.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct1, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(universe, shader_struct);

    yli::ontology::MaterialStruct material_struct1;
    material_struct1.shader = shader;
    yli::ontology::Material* const material1 = new yli::ontology::Material(universe, material_struct1, &shader->parent_of_materials);

    yli::ontology::SpeciesStruct shapeshifter_transformation_struct;
    shapeshifter_transformation_struct.scene = scene;
    shapeshifter_transformation_struct.shader = shader;
    shapeshifter_transformation_struct.material = material1;
    yli::ontology::ShapeshifterTransformation* const shapeshifter_transformation = new yli::ontology::ShapeshifterTransformation(universe, shapeshifter_transformation_struct);
    ASSERT_EQ(shapeshifter_transformation->get_parent(), material1);
    ASSERT_EQ(material1->get_number_of_all_children(), 1);
    ASSERT_EQ(material1->get_number_of_all_descendants(), 1);

    yli::ontology::MaterialStruct material_struct2;
    material_struct2.shader = shader;
    yli::ontology::Material* const material2 = new yli::ontology::Material(universe, material_struct2, &shader->parent_of_materials);
    ASSERT_EQ(material2->get_number_of_all_children(), 0);
    ASSERT_EQ(material2->get_number_of_all_descendants(), 0);

    shapeshifter_transformation->bind_to_new_parent(material2);
    ASSERT_EQ(shapeshifter_transformation->get_parent(), material2);
    ASSERT_EQ(material1->get_number_of_all_children(), 0);
    ASSERT_EQ(material1->get_number_of_all_descendants(), 0);
    ASSERT_EQ(material2->get_number_of_all_children(), 1);
    ASSERT_EQ(material2->get_number_of_all_descendants(), 1);
    ASSERT_EQ(shader->get_number_of_all_children(), 2);
    ASSERT_EQ(shader->get_number_of_all_descendants(), 3);
    ASSERT_EQ(scene->get_number_of_all_children(), 2);
    ASSERT_EQ(scene->get_number_of_all_descendants(), 5);
    ASSERT_EQ(world->get_number_of_all_children(), 1);
    ASSERT_EQ(world->get_number_of_all_descendants(), 6);
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 7);

    shapeshifter_transformation->bind_to_new_parent(material1);
    ASSERT_EQ(shapeshifter_transformation->get_parent(), material1);
    ASSERT_EQ(material1->get_number_of_all_children(), 1);
    ASSERT_EQ(material1->get_number_of_all_descendants(), 1);
    ASSERT_EQ(material2->get_number_of_all_children(), 0);
    ASSERT_EQ(material2->get_number_of_all_descendants(), 0);
    ASSERT_EQ(shader->get_number_of_all_children(), 2);
    ASSERT_EQ(shader->get_number_of_all_descendants(), 3);
    ASSERT_EQ(scene->get_number_of_all_children(), 2);
    ASSERT_EQ(scene->get_number_of_all_descendants(), 5);
    ASSERT_EQ(world->get_number_of_all_children(), 1);
    ASSERT_EQ(world->get_number_of_all_descendants(), 6);
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 7);
}

TEST(shapeshifter_transformation_must_bind_to_material_appropriately, materials_of_different_shaders)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(universe, world_struct, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct1;
    scene_struct1.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct1, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct1;
    shader_struct1.parent = scene;
    yli::ontology::Shader* const shader1 = new yli::ontology::Shader(universe, shader_struct1);

    yli::ontology::MaterialStruct material_struct1;
    material_struct1.shader = shader1;
    yli::ontology::Material* const material1 = new yli::ontology::Material(universe, material_struct1, &shader1->parent_of_materials);

    yli::ontology::SpeciesStruct shapeshifter_transformation_struct;
    shapeshifter_transformation_struct.scene = scene;
    shapeshifter_transformation_struct.shader = shader1;
    shapeshifter_transformation_struct.material = material1;
    yli::ontology::ShapeshifterTransformation* const shapeshifter_transformation = new yli::ontology::ShapeshifterTransformation(universe, shapeshifter_transformation_struct);
    ASSERT_EQ(shapeshifter_transformation->get_parent(), material1);
    ASSERT_EQ(material1->get_number_of_all_children(), 1);
    ASSERT_EQ(material1->get_number_of_all_descendants(), 1);

    yli::ontology::ShaderStruct shader_struct2;
    shader_struct2.parent = scene;
    yli::ontology::Shader* const shader2 = new yli::ontology::Shader(universe, shader_struct2);

    yli::ontology::MaterialStruct material_struct2;
    material_struct2.shader = shader2;
    yli::ontology::Material* const material2 = new yli::ontology::Material(universe, material_struct2, &shader2->parent_of_materials);
    ASSERT_EQ(material2->get_number_of_all_children(), 0);
    ASSERT_EQ(material2->get_number_of_all_descendants(), 0);

    shapeshifter_transformation->bind_to_new_parent(material2);
    ASSERT_EQ(shapeshifter_transformation->get_parent(), material2);
    ASSERT_EQ(material1->get_number_of_all_children(), 0);
    ASSERT_EQ(material1->get_number_of_all_descendants(), 0);
    ASSERT_EQ(material2->get_number_of_all_children(), 1);
    ASSERT_EQ(material2->get_number_of_all_descendants(), 1);
    ASSERT_EQ(shader1->get_number_of_all_children(), 1);
    ASSERT_EQ(shader1->get_number_of_all_descendants(), 1);
    ASSERT_EQ(shader2->get_number_of_all_children(), 1);
    ASSERT_EQ(shader2->get_number_of_all_descendants(), 2);
    ASSERT_EQ(scene->get_number_of_all_children(), 3);
    ASSERT_EQ(scene->get_number_of_all_descendants(), 6);
    ASSERT_EQ(world->get_number_of_all_children(), 1);
    ASSERT_EQ(world->get_number_of_all_descendants(), 7);
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 8);

    shapeshifter_transformation->bind_to_new_parent(material1);
    ASSERT_EQ(shapeshifter_transformation->get_parent(), material1);
    ASSERT_EQ(material1->get_number_of_all_children(), 1);
    ASSERT_EQ(material1->get_number_of_all_descendants(), 1);
    ASSERT_EQ(material2->get_number_of_all_children(), 0);
    ASSERT_EQ(material2->get_number_of_all_descendants(), 0);
    ASSERT_EQ(shader1->get_number_of_all_children(), 1);
    ASSERT_EQ(shader1->get_number_of_all_descendants(), 2);
    ASSERT_EQ(shader2->get_number_of_all_children(), 1);
    ASSERT_EQ(shader2->get_number_of_all_descendants(), 1);
    ASSERT_EQ(scene->get_number_of_all_children(), 3);
    ASSERT_EQ(scene->get_number_of_all_descendants(), 6);
    ASSERT_EQ(world->get_number_of_all_children(), 1);
    ASSERT_EQ(world->get_number_of_all_descendants(), 7);
    ASSERT_EQ(universe->get_number_of_all_children(), 1);
    ASSERT_EQ(universe->get_number_of_all_descendants(), 8);
}

TEST(object_must_bind_to_brain_appropriately, master_and_apprentice)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(universe, world_struct, &universe->parent_of_worlds);

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
    yli::ontology::Species* const species = new yli::ontology::Species(universe, species_struct, &material->parent_of_species);

    yli::ontology::ObjectStruct object_struct;
    object_struct.species_parent = species;
    yli::ontology::Object* const object = new yli::ontology::Object(universe, object_struct, &species->parent_of_objects);

    ASSERT_EQ(brain->get_number_of_apprentices(), 0);
    object->bind_to_new_brain(brain);
    ASSERT_EQ(brain->get_number_of_apprentices(), 1);
}

TEST(universe_must_be_given_a_global_name_appropriately, headless)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    ASSERT_EQ(universe->get_global_name(), "");
    ASSERT_EQ(universe->get_local_name(), "");

    universe->set_global_name("foo");
    ASSERT_EQ(universe->get_global_name(), "foo");
    ASSERT_EQ(universe->get_local_name(), "");
}

TEST(universe_must_not_accept_a_local_name_before_setting_a_global_name, headless)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    ASSERT_EQ(universe->get_global_name(), "");
    ASSERT_EQ(universe->get_local_name(), "");

    universe->set_local_name("foo");
    ASSERT_EQ(universe->get_global_name(), "");
    ASSERT_EQ(universe->get_local_name(), "");
}

TEST(universe_must_not_accept_a_local_name_after_setting_a_global_name, headless)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    ASSERT_EQ(universe->get_global_name(), "");
    ASSERT_EQ(universe->get_local_name(), "");

    universe->set_global_name("foo");
    universe->set_local_name("bar");
    ASSERT_EQ(universe->get_global_name(), "foo");
    ASSERT_EQ(universe->get_local_name(), "");
}

TEST(world_must_be_given_a_global_name_appropriately, headless)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(universe, world_struct, &universe->parent_of_worlds);
    ASSERT_EQ(world->get_global_name(), "");
    ASSERT_EQ(world->get_local_name(), "");

    // `World`s are children of the `Universe` and thus global name is local name, and vice versa.
    world->set_global_name("foo");
    ASSERT_EQ(world->get_global_name(), "foo");
    ASSERT_EQ(world->get_local_name(), "foo");
    ASSERT_TRUE(universe->is_entity("foo"));
}

TEST(world_must_be_given_a_local_name_appropriately, headless)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(universe, world_struct, &universe->parent_of_worlds);
    ASSERT_EQ(world->get_global_name(), "");
    ASSERT_EQ(world->get_local_name(), "");

    // `World`s are children of the `Universe` and thus global name is local name, and vice versa.
    world->set_local_name("foo");
    ASSERT_EQ(world->get_global_name(), "foo");
    ASSERT_EQ(world->get_local_name(), "foo");
    ASSERT_TRUE(universe->is_entity("foo"));
}

TEST(world_must_be_given_a_global_name_appropriately_after_setting_a_global_name, headless)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(universe, world_struct, &universe->parent_of_worlds);
    ASSERT_EQ(world->get_global_name(), "");
    ASSERT_EQ(world->get_local_name(), "");

    // `World`s are children of the `Universe` and thus global name is local name, and vice versa.
    world->set_global_name("foo");
    world->set_global_name("bar");
    ASSERT_EQ(world->get_global_name(), "bar");
    ASSERT_EQ(world->get_local_name(), "bar");
    ASSERT_FALSE(universe->is_entity("foo"));
    ASSERT_TRUE(universe->is_entity("bar"));
}

TEST(world_must_be_given_a_local_name_appropriately_after_setting_a_local_name, headless)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(universe, world_struct, &universe->parent_of_worlds);
    ASSERT_EQ(world->get_global_name(), "");
    ASSERT_EQ(world->get_local_name(), "");

    // `World`s are children of the `Universe` and thus global name is local name, and vice versa.
    world->set_local_name("foo");
    world->set_local_name("bar");
    ASSERT_EQ(world->get_global_name(), "bar");
    ASSERT_EQ(world->get_local_name(), "bar");
    ASSERT_FALSE(universe->is_entity("foo"));
    ASSERT_TRUE(universe->is_entity("bar"));
}

TEST(world_must_be_given_a_global_name_appropriately_after_setting_a_local_name, headless)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(universe, world_struct, &universe->parent_of_worlds);
    ASSERT_EQ(world->get_global_name(), "");
    ASSERT_EQ(world->get_local_name(), "");

    // `World`s are children of the `Universe` and thus global name is local name, and vice versa.
    world->set_local_name("foo");
    world->set_global_name("bar");
    ASSERT_EQ(world->get_global_name(), "bar");
    ASSERT_EQ(world->get_local_name(), "bar");
    ASSERT_FALSE(universe->is_entity("foo"));
    ASSERT_TRUE(universe->is_entity("bar"));
}

TEST(world_must_be_given_a_local_name_appropriately_after_setting_a_global_name, headless)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(universe, world_struct, &universe->parent_of_worlds);
    ASSERT_EQ(world->get_global_name(), "");
    ASSERT_EQ(world->get_local_name(), "");

    // `World`s are children of the `Universe` and thus global name is local name, and vice versa.
    world->set_global_name("foo");
    world->set_local_name("bar");
    ASSERT_EQ(world->get_global_name(), "bar");
    ASSERT_EQ(world->get_local_name(), "bar");
    ASSERT_FALSE(universe->is_entity("foo"));
    ASSERT_TRUE(universe->is_entity("bar"));
}

TEST(scene_must_be_given_a_global_name_appropriately, headless)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(universe, world_struct, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);
    ASSERT_EQ(scene->get_global_name(), "");
    ASSERT_EQ(scene->get_local_name(), "");

    scene->set_global_name("foo");
    ASSERT_EQ(scene->get_global_name(), "foo");
    ASSERT_EQ(scene->get_local_name(), "");
    ASSERT_TRUE(universe->is_entity("foo"));
    ASSERT_FALSE(world->is_entity("foo"));
}

TEST(scene_must_be_given_a_local_name_appropriately, headless)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(universe, world_struct, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);
    ASSERT_EQ(scene->get_global_name(), "");
    ASSERT_EQ(scene->get_local_name(), "");

    scene->set_local_name("foo");
    ASSERT_EQ(scene->get_global_name(), "");
    ASSERT_EQ(scene->get_local_name(), "foo");
    ASSERT_FALSE(universe->is_entity("foo"));
    ASSERT_TRUE(world->is_entity("foo"));
}

TEST(scene_must_be_given_a_global_name_appropriately_after_setting_a_global_name, headless)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(universe, world_struct, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);
    ASSERT_EQ(scene->get_global_name(), "");
    ASSERT_EQ(scene->get_local_name(), "");

    scene->set_global_name("foo");
    scene->set_global_name("bar");
    ASSERT_EQ(scene->get_global_name(), "bar");
    ASSERT_EQ(scene->get_local_name(), "");
    ASSERT_FALSE(universe->is_entity("foo"));
    ASSERT_TRUE(universe->is_entity("bar"));
    ASSERT_FALSE(world->is_entity("foo"));
    ASSERT_FALSE(world->is_entity("bar"));
}

TEST(scene_must_be_given_a_local_name_appropriately_after_setting_a_local_name, headless)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(universe, world_struct, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);
    ASSERT_EQ(scene->get_global_name(), "");
    ASSERT_EQ(scene->get_local_name(), "");

    scene->set_local_name("foo");
    scene->set_local_name("bar");
    ASSERT_EQ(scene->get_global_name(), "");
    ASSERT_EQ(scene->get_local_name(), "bar");
    ASSERT_FALSE(universe->is_entity("foo"));
    ASSERT_FALSE(universe->is_entity("bar"));
    ASSERT_FALSE(world->is_entity("foo"));
    ASSERT_TRUE(world->is_entity("bar"));
}

TEST(scene_must_be_given_a_global_name_appropriately_after_setting_a_local_name, headless)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(universe, world_struct, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);
    ASSERT_EQ(scene->get_global_name(), "");
    ASSERT_EQ(scene->get_local_name(), "");

    scene->set_local_name("foo");
    scene->set_global_name("bar");
    ASSERT_EQ(scene->get_global_name(), "bar");
    ASSERT_EQ(scene->get_local_name(), "foo");
    ASSERT_FALSE(universe->is_entity("foo"));
    ASSERT_TRUE(universe->is_entity("bar"));
    ASSERT_TRUE(world->is_entity("foo"));
    ASSERT_FALSE(world->is_entity("bar"));
}

TEST(scene_must_be_given_a_local_name_appropriately_after_setting_a_global_name, headless)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(universe, world_struct, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);
    ASSERT_EQ(scene->get_global_name(), "");
    ASSERT_EQ(scene->get_local_name(), "");

    scene->set_global_name("foo");
    scene->set_local_name("bar");
    ASSERT_EQ(scene->get_global_name(), "foo");
    ASSERT_EQ(scene->get_local_name(), "bar");
    ASSERT_TRUE(universe->is_entity("foo"));
    ASSERT_FALSE(universe->is_entity("bar"));
    ASSERT_FALSE(world->is_entity("foo"));
    ASSERT_TRUE(world->is_entity("bar"));
}

TEST(shader_must_be_given_a_global_name_appropriately, headless)
{
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
    ASSERT_EQ(shader->get_global_name(), "");
    ASSERT_EQ(shader->get_local_name(), "");

    shader->set_global_name("foo");
    ASSERT_EQ(shader->get_global_name(), "foo");
    ASSERT_EQ(shader->get_local_name(), "");
    ASSERT_TRUE(universe->is_entity("foo"));
    ASSERT_FALSE(world->is_entity("foo"));
    ASSERT_FALSE(scene->is_entity("foo"));
}

TEST(shader_must_be_given_a_local_name_appropriately, headless)
{
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
    ASSERT_EQ(shader->get_global_name(), "");
    ASSERT_EQ(shader->get_local_name(), "");

    shader->set_local_name("foo");
    ASSERT_EQ(shader->get_global_name(), "");
    ASSERT_EQ(shader->get_local_name(), "foo");
    ASSERT_FALSE(universe->is_entity("foo"));
    ASSERT_FALSE(world->is_entity("foo"));
    ASSERT_TRUE(scene->is_entity("foo"));
}

TEST(shader_must_be_given_a_global_name_appropriately_after_setting_a_global_name, headless)
{
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
    ASSERT_EQ(shader->get_global_name(), "");
    ASSERT_EQ(shader->get_local_name(), "");

    shader->set_global_name("foo");
    shader->set_global_name("bar");
    ASSERT_EQ(shader->get_global_name(), "bar");
    ASSERT_EQ(shader->get_local_name(), "");
    ASSERT_FALSE(universe->is_entity("foo"));
    ASSERT_TRUE(universe->is_entity("bar"));
    ASSERT_FALSE(world->is_entity("foo"));
    ASSERT_FALSE(world->is_entity("bar"));
    ASSERT_FALSE(scene->is_entity("foo"));
    ASSERT_FALSE(scene->is_entity("bar"));
}

TEST(shader_must_be_given_a_local_name_appropriately_after_setting_a_local_name, headless)
{
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
    ASSERT_EQ(shader->get_global_name(), "");
    ASSERT_EQ(shader->get_local_name(), "");

    shader->set_local_name("foo");
    shader->set_local_name("bar");
    ASSERT_EQ(shader->get_global_name(), "");
    ASSERT_EQ(shader->get_local_name(), "bar");
    ASSERT_FALSE(universe->is_entity("foo"));
    ASSERT_FALSE(universe->is_entity("bar"));
    ASSERT_FALSE(world->is_entity("foo"));
    ASSERT_FALSE(world->is_entity("bar"));
    ASSERT_FALSE(scene->is_entity("foo"));
    ASSERT_TRUE(scene->is_entity("bar"));
}

TEST(shader_must_be_given_a_global_name_appropriately_after_setting_a_local_name, headless)
{
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
    ASSERT_EQ(shader->get_global_name(), "");
    ASSERT_EQ(shader->get_local_name(), "");

    shader->set_local_name("foo");
    shader->set_global_name("bar");
    ASSERT_EQ(shader->get_global_name(), "bar");
    ASSERT_EQ(shader->get_local_name(), "foo");
    ASSERT_FALSE(universe->is_entity("foo"));
    ASSERT_TRUE(universe->is_entity("bar"));
    ASSERT_FALSE(world->is_entity("foo"));
    ASSERT_FALSE(world->is_entity("bar"));
    ASSERT_TRUE(scene->is_entity("foo"));
    ASSERT_FALSE(scene->is_entity("bar"));
}

TEST(shader_must_be_given_a_local_name_appropriately_after_setting_a_global_name, headless)
{
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
    ASSERT_EQ(shader->get_global_name(), "");
    ASSERT_EQ(shader->get_local_name(), "");

    shader->set_global_name("foo");
    shader->set_local_name("bar");
    ASSERT_EQ(shader->get_global_name(), "foo");
    ASSERT_EQ(shader->get_local_name(), "bar");
    ASSERT_TRUE(universe->is_entity("foo"));
    ASSERT_FALSE(universe->is_entity("bar"));
    ASSERT_FALSE(world->is_entity("foo"));
    ASSERT_FALSE(world->is_entity("bar"));
    ASSERT_FALSE(scene->is_entity("foo"));
    ASSERT_TRUE(scene->is_entity("bar"));
}

TEST(scene_must_maintain_the_local_name_after_binding_to_a_new_parent, headless_universe_scene_with_only_local_name)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct1;
    yli::ontology::World* const world1 = new yli::ontology::World(universe, world_struct1, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world1;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world1->parent_of_scenes);

    yli::ontology::WorldStruct world_struct2;
    yli::ontology::World* const world2 = new yli::ontology::World(universe, world_struct2, &universe->parent_of_worlds);

    scene->set_local_name("foo");
    scene->bind_to_new_parent(world2);
    ASSERT_FALSE(world1->is_entity("foo"));
    ASSERT_TRUE(world2->is_entity("foo"));
    ASSERT_EQ(scene->get_parent(), world2);
    ASSERT_EQ(world1->get_number_of_all_children(), 0);
    ASSERT_EQ(world1->get_number_of_all_descendants(), 0);
    ASSERT_EQ(world2->get_number_of_all_children(), 1);
    ASSERT_EQ(world2->get_number_of_all_descendants(), 2);

    scene->bind_to_new_parent(world1);
    ASSERT_TRUE(world1->is_entity("foo"));
    ASSERT_FALSE(world2->is_entity("foo"));
    ASSERT_EQ(scene->get_parent(), world1);
    ASSERT_EQ(world1->get_number_of_all_children(), 1);
    ASSERT_EQ(world1->get_number_of_all_descendants(), 2);
    ASSERT_EQ(world2->get_number_of_all_children(), 0);
    ASSERT_EQ(world2->get_number_of_all_descendants(), 0);
}

TEST(scene_must_maintain_the_local_name_after_binding_to_a_new_parent, headless_universe_scene_with_global_name_and_local_name)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct1;
    yli::ontology::World* const world1 = new yli::ontology::World(universe, world_struct1, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world1;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world1->parent_of_scenes);

    yli::ontology::WorldStruct world_struct2;
    yli::ontology::World* const world2 = new yli::ontology::World(universe, world_struct2, &universe->parent_of_worlds);

    scene->set_global_name("foo");
    scene->set_local_name("bar");
    scene->bind_to_new_parent(world2);
    ASSERT_FALSE(world1->is_entity("foo"));
    ASSERT_FALSE(world2->is_entity("foo"));
    ASSERT_FALSE(world1->is_entity("bar"));
    ASSERT_TRUE(world2->is_entity("bar"));
    ASSERT_EQ(scene->get_parent(), world2);
    ASSERT_EQ(world1->get_number_of_all_children(), 0);
    ASSERT_EQ(world1->get_number_of_all_descendants(), 0);
    ASSERT_EQ(world2->get_number_of_all_children(), 1);
    ASSERT_EQ(world2->get_number_of_all_descendants(), 2);

    scene->bind_to_new_parent(world1);
    ASSERT_FALSE(world1->is_entity("foo"));
    ASSERT_FALSE(world2->is_entity("foo"));
    ASSERT_TRUE(world1->is_entity("bar"));
    ASSERT_FALSE(world2->is_entity("bar"));
    ASSERT_EQ(scene->get_parent(), world1);
    ASSERT_EQ(world1->get_number_of_all_children(), 1);
    ASSERT_EQ(world1->get_number_of_all_descendants(), 2);
    ASSERT_EQ(world2->get_number_of_all_children(), 0);
    ASSERT_EQ(world2->get_number_of_all_descendants(), 0);
}

TEST(scene_must_not_bind_to_a_new_parent_when_local_name_is_already_in_use, headless_universe_scenes_with_only_local_name)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct1;
    yli::ontology::World* const world1 = new yli::ontology::World(universe, world_struct1, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct1;
    scene_struct1.world = world1;
    yli::ontology::Scene* const scene1 = new yli::ontology::Scene(universe, scene_struct1, &world1->parent_of_scenes);

    yli::ontology::WorldStruct world_struct2;
    yli::ontology::World* const world2 = new yli::ontology::World(universe, world_struct2, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct2;
    scene_struct2.world = world2;
    yli::ontology::Scene* const scene2 = new yli::ontology::Scene(universe, scene_struct2, &world2->parent_of_scenes);

    scene1->set_local_name("foo");
    scene2->set_local_name("foo");
    scene1->bind_to_new_parent(world2);
    ASSERT_EQ(scene1->get_parent(), world1);
    ASSERT_EQ(scene2->get_parent(), world2);
    ASSERT_EQ(world1->get_number_of_all_children(), 1);
    ASSERT_EQ(world1->get_number_of_all_descendants(), 2);
    ASSERT_EQ(world2->get_number_of_all_children(), 1);
    ASSERT_EQ(world2->get_number_of_all_descendants(), 2);
    ASSERT_TRUE(world1->is_entity("foo"));
    ASSERT_TRUE(world2->is_entity("foo"));
}

TEST(scene_must_not_bind_to_a_new_parent_when_local_name_is_already_in_use, headless_universe_scenes_with_different_global_names_and_same_local_name)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct1;
    yli::ontology::World* const world1 = new yli::ontology::World(universe, world_struct1, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct1;
    scene_struct1.world = world1;
    yli::ontology::Scene* const scene1 = new yli::ontology::Scene(universe, scene_struct1, &world1->parent_of_scenes);

    yli::ontology::WorldStruct world_struct2;
    yli::ontology::World* const world2 = new yli::ontology::World(universe, world_struct2, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct2;
    scene_struct2.world = world2;
    yli::ontology::Scene* const scene2 = new yli::ontology::Scene(universe, scene_struct2, &world2->parent_of_scenes);

    scene1->set_global_name("foo");
    scene2->set_global_name("bar");
    scene1->set_local_name("baz");
    scene2->set_local_name("baz");
    scene1->bind_to_new_parent(world2);
    ASSERT_EQ(scene1->get_parent(), world1);
    ASSERT_EQ(scene2->get_parent(), world2);
    ASSERT_EQ(world1->get_number_of_all_children(), 1);
    ASSERT_EQ(world1->get_number_of_all_descendants(), 2);
    ASSERT_EQ(world2->get_number_of_all_children(), 1);
    ASSERT_EQ(world2->get_number_of_all_descendants(), 2);
    ASSERT_FALSE(world1->is_entity("foo"));
    ASSERT_FALSE(world2->is_entity("foo"));
    ASSERT_FALSE(world1->is_entity("bar"));
    ASSERT_FALSE(world2->is_entity("bar"));
    ASSERT_TRUE(world1->is_entity("baz"));
    ASSERT_TRUE(world2->is_entity("baz"));
}

TEST(shader_must_maintain_the_local_name_after_binding_to_a_new_parent, headless_universe_shader_with_only_local_name)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(universe, world_struct, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct1;
    scene_struct1.world = world;
    yli::ontology::Scene* const scene1 = new yli::ontology::Scene(universe, scene_struct1, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene1;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(universe, shader_struct);

    yli::ontology::SceneStruct scene_struct2;
    scene_struct2.world = world;
    yli::ontology::Scene* const scene2 = new yli::ontology::Scene(universe, scene_struct2, &world->parent_of_scenes);

    shader->set_local_name("foo");
    shader->bind_to_new_parent(scene2);
    ASSERT_FALSE(scene1->is_entity("foo"));
    ASSERT_TRUE(scene2->is_entity("foo"));
    ASSERT_EQ(shader->get_parent(), scene2);
    ASSERT_EQ(scene1->get_number_of_all_children(), 1);
    ASSERT_EQ(scene1->get_number_of_all_descendants(), 1);
    ASSERT_EQ(scene2->get_number_of_all_children(), 2);
    ASSERT_EQ(scene2->get_number_of_all_descendants(), 2);

    shader->bind_to_new_parent(scene1);
    ASSERT_TRUE(scene1->is_entity("foo"));
    ASSERT_FALSE(scene2->is_entity("foo"));
    ASSERT_EQ(shader->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_all_children(), 2);
    ASSERT_EQ(scene1->get_number_of_all_descendants(), 2);
    ASSERT_EQ(scene2->get_number_of_all_children(), 1);
    ASSERT_EQ(scene2->get_number_of_all_descendants(), 1);
}

TEST(shader_must_maintain_the_local_name_after_binding_to_a_new_parent, headless_universe_shader_with_global_name_and_local_name)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(universe, world_struct, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct1;
    scene_struct1.world = world;
    yli::ontology::Scene* const scene1 = new yli::ontology::Scene(universe, scene_struct1, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct;
    shader_struct.parent = scene1;
    yli::ontology::Shader* const shader = new yli::ontology::Shader(universe, shader_struct);

    yli::ontology::SceneStruct scene_struct2;
    scene_struct2.world = world;
    yli::ontology::Scene* const scene2 = new yli::ontology::Scene(universe, scene_struct2, &world->parent_of_scenes);

    shader->set_global_name("foo");
    shader->set_local_name("bar");
    shader->bind_to_new_parent(scene2);
    ASSERT_FALSE(scene1->is_entity("foo"));
    ASSERT_FALSE(scene2->is_entity("foo"));
    ASSERT_FALSE(scene1->is_entity("bar"));
    ASSERT_TRUE(scene2->is_entity("bar"));
    ASSERT_EQ(shader->get_parent(), scene2);
    ASSERT_EQ(scene1->get_number_of_all_children(), 1);
    ASSERT_EQ(scene1->get_number_of_all_descendants(), 1);
    ASSERT_EQ(scene2->get_number_of_all_children(), 2);
    ASSERT_EQ(scene2->get_number_of_all_descendants(), 2);

    shader->bind_to_new_parent(scene1);
    ASSERT_FALSE(scene1->is_entity("foo"));
    ASSERT_FALSE(scene2->is_entity("foo"));
    ASSERT_TRUE(scene1->is_entity("bar"));
    ASSERT_FALSE(scene2->is_entity("bar"));
    ASSERT_EQ(shader->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_all_children(), 2);
    ASSERT_EQ(scene1->get_number_of_all_descendants(), 2);
    ASSERT_EQ(scene2->get_number_of_all_children(), 1);
    ASSERT_EQ(scene2->get_number_of_all_descendants(), 1);
}

TEST(shader_must_not_bind_to_a_new_parent_when_local_name_is_already_in_use, headless_universe_shaders_with_only_local_name)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(universe, world_struct, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct1;
    scene_struct1.world = world;
    yli::ontology::Scene* const scene1 = new yli::ontology::Scene(universe, scene_struct1, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct1;
    shader_struct1.parent = scene1;
    yli::ontology::Shader* const shader1 = new yli::ontology::Shader(universe, shader_struct1);

    yli::ontology::SceneStruct scene_struct2;
    scene_struct2.world = world;
    yli::ontology::Scene* const scene2 = new yli::ontology::Scene(universe, scene_struct2, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct2;
    shader_struct2.parent = scene2;
    yli::ontology::Shader* const shader2 = new yli::ontology::Shader(universe, shader_struct2);

    shader1->set_local_name("foo");
    shader2->set_local_name("foo");
    shader1->bind_to_new_parent(scene2);
    ASSERT_EQ(shader1->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_all_children(), 2);
    ASSERT_EQ(scene1->get_number_of_all_descendants(), 2);
    ASSERT_EQ(scene2->get_number_of_all_children(), 2);
    ASSERT_EQ(scene2->get_number_of_all_descendants(), 2);
    ASSERT_TRUE(scene1->is_entity("foo"));
    ASSERT_TRUE(scene2->is_entity("foo"));
}

TEST(shader_must_not_bind_to_a_new_parent_when_local_name_is_already_in_use, headless_universe_shaders_with_different_global_names_and_same_local_name)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(universe, world_struct, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct1;
    scene_struct1.world = world;
    yli::ontology::Scene* const scene1 = new yli::ontology::Scene(universe, scene_struct1, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct1;
    shader_struct1.parent = scene1;
    yli::ontology::Shader* const shader1 = new yli::ontology::Shader(universe, shader_struct1);

    yli::ontology::SceneStruct scene_struct2;
    scene_struct2.world = world;
    yli::ontology::Scene* const scene2 = new yli::ontology::Scene(universe, scene_struct2, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct2;
    shader_struct2.parent = scene2;
    yli::ontology::Shader* const shader2 = new yli::ontology::Shader(universe, shader_struct2);

    shader1->set_global_name("foo");
    shader2->set_global_name("bar");
    shader1->set_local_name("baz");
    shader2->set_local_name("baz");
    shader1->bind_to_new_parent(scene2);
    ASSERT_EQ(shader1->get_parent(), scene1);
    ASSERT_EQ(scene1->get_number_of_all_children(), 2);
    ASSERT_EQ(scene1->get_number_of_all_descendants(), 2);
    ASSERT_EQ(scene2->get_number_of_all_children(), 2);
    ASSERT_EQ(scene2->get_number_of_all_descendants(), 2);
    ASSERT_FALSE(scene1->is_entity("foo"));
    ASSERT_FALSE(scene2->is_entity("foo"));
    ASSERT_FALSE(scene1->is_entity("bar"));
    ASSERT_FALSE(scene2->is_entity("bar"));
    ASSERT_TRUE(scene1->is_entity("baz"));
    ASSERT_TRUE(scene2->is_entity("baz"));
}

TEST(material_must_maintain_the_local_name_after_binding_to_a_new_parent, headless_universe_material_with_only_local_name)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(universe, world_struct, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct1;
    shader_struct1.parent = scene;
    yli::ontology::Shader* const shader1 = new yli::ontology::Shader(universe, shader_struct1);

    yli::ontology::MaterialStruct material_struct;
    material_struct.shader = shader1;
    yli::ontology::Material* const material = new yli::ontology::Material(universe, material_struct, &shader1->parent_of_materials);

    yli::ontology::ShaderStruct shader_struct2;
    shader_struct2.parent = scene;
    yli::ontology::Shader* const shader2 = new yli::ontology::Shader(universe, shader_struct2);

    material->set_local_name("foo");
    material->bind_to_new_parent(shader2);
    ASSERT_FALSE(shader1->is_entity("foo"));
    ASSERT_TRUE(shader2->is_entity("foo"));
    ASSERT_EQ(material->get_parent(), shader2);
    ASSERT_EQ(shader1->get_number_of_all_children(), 0);
    ASSERT_EQ(shader1->get_number_of_all_descendants(), 0);
    ASSERT_EQ(shader2->get_number_of_all_children(), 1);
    ASSERT_EQ(shader2->get_number_of_all_descendants(), 1);

    material->bind_to_new_parent(shader1);
    ASSERT_TRUE(shader1->is_entity("foo"));
    ASSERT_FALSE(shader2->is_entity("foo"));
    ASSERT_EQ(material->get_parent(), shader1);
    ASSERT_EQ(shader1->get_number_of_all_children(), 1);
    ASSERT_EQ(shader1->get_number_of_all_descendants(), 1);
    ASSERT_EQ(shader2->get_number_of_all_children(), 0);
    ASSERT_EQ(shader2->get_number_of_all_descendants(), 0);
}

TEST(material_must_maintain_the_local_name_after_binding_to_a_new_parent, headless_universe_material_with_global_name_and_local_name)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(universe, world_struct, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct1;
    shader_struct1.parent = scene;
    yli::ontology::Shader* const shader1 = new yli::ontology::Shader(universe, shader_struct1);

    yli::ontology::MaterialStruct material_struct;
    material_struct.shader = shader1;
    yli::ontology::Material* const material = new yli::ontology::Material(universe, material_struct, &shader1->parent_of_materials);

    yli::ontology::ShaderStruct shader_struct2;
    shader_struct2.parent = scene;
    yli::ontology::Shader* const shader2 = new yli::ontology::Shader(universe, shader_struct2);

    material->set_global_name("foo");
    material->set_local_name("bar");
    material->bind_to_new_parent(shader2);
    ASSERT_FALSE(shader1->is_entity("foo"));
    ASSERT_FALSE(shader2->is_entity("foo"));
    ASSERT_FALSE(shader1->is_entity("bar"));
    ASSERT_TRUE(shader2->is_entity("bar"));
    ASSERT_EQ(material->get_parent(), shader2);
    ASSERT_EQ(shader1->get_number_of_all_children(), 0);
    ASSERT_EQ(shader1->get_number_of_all_descendants(), 0);
    ASSERT_EQ(shader2->get_number_of_all_children(), 1);
    ASSERT_EQ(shader2->get_number_of_all_descendants(), 1);

    material->bind_to_new_parent(shader1);
    ASSERT_FALSE(shader1->is_entity("foo"));
    ASSERT_FALSE(shader2->is_entity("foo"));
    ASSERT_TRUE(shader1->is_entity("bar"));
    ASSERT_FALSE(shader2->is_entity("bar"));
    ASSERT_EQ(material->get_parent(), shader1);
    ASSERT_EQ(shader1->get_number_of_all_children(), 1);
    ASSERT_EQ(shader1->get_number_of_all_descendants(), 1);
    ASSERT_EQ(shader2->get_number_of_all_children(), 0);
    ASSERT_EQ(shader2->get_number_of_all_descendants(), 0);
}

TEST(material_must_not_bind_to_a_new_parent_when_local_name_is_already_in_use, headless_universe_materials_with_only_local_name)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(universe, world_struct, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct1;
    shader_struct1.parent = scene;
    yli::ontology::Shader* const shader1 = new yli::ontology::Shader(universe, shader_struct1);

    yli::ontology::MaterialStruct material_struct1;
    material_struct1.shader = shader1;
    yli::ontology::Material* const material1 = new yli::ontology::Material(universe, material_struct1, &shader1->parent_of_materials);

    yli::ontology::ShaderStruct shader_struct2;
    shader_struct2.parent = scene;
    yli::ontology::Shader* const shader2 = new yli::ontology::Shader(universe, shader_struct2);

    yli::ontology::MaterialStruct material_struct2;
    material_struct2.shader = shader2;
    yli::ontology::Material* const material2 = new yli::ontology::Material(universe, material_struct2, &shader2->parent_of_materials);

    material1->set_local_name("foo");
    material2->set_local_name("foo");
    material1->bind_to_new_parent(shader2);
    ASSERT_EQ(material1->get_parent(), shader1);
    ASSERT_EQ(shader1->get_number_of_all_children(), 1);
    ASSERT_EQ(shader1->get_number_of_all_descendants(), 1);
    ASSERT_EQ(shader2->get_number_of_all_children(), 1);
    ASSERT_EQ(shader2->get_number_of_all_descendants(), 1);
    ASSERT_TRUE(shader1->is_entity("foo"));
    ASSERT_TRUE(shader2->is_entity("foo"));
}

TEST(material_must_not_bind_to_a_new_parent_when_local_name_is_already_in_use, headless_universe_materials_with_different_global_names_and_same_local_name)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::WorldStruct world_struct;
    yli::ontology::World* const world = new yli::ontology::World(universe, world_struct, &universe->parent_of_worlds);

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);

    yli::ontology::ShaderStruct shader_struct1;
    shader_struct1.parent = scene;
    yli::ontology::Shader* const shader1 = new yli::ontology::Shader(universe, shader_struct1);

    yli::ontology::MaterialStruct material_struct1;
    material_struct1.shader = shader1;
    yli::ontology::Material* const material1 = new yli::ontology::Material(universe, material_struct1, &shader1->parent_of_materials);

    yli::ontology::ShaderStruct shader_struct2;
    shader_struct2.parent = scene;
    yli::ontology::Shader* const shader2 = new yli::ontology::Shader(universe, shader_struct2);

    yli::ontology::MaterialStruct material_struct2;
    material_struct2.shader = shader2;
    yli::ontology::Material* const material2 = new yli::ontology::Material(universe, material_struct2, &shader2->parent_of_materials);

    material1->set_global_name("foo");
    material2->set_global_name("bar");
    material1->set_local_name("baz");
    material2->set_local_name("baz");
    material1->bind_to_new_parent(shader2);
    ASSERT_EQ(material1->get_parent(), shader1);
    ASSERT_EQ(shader1->get_number_of_all_children(), 1);
    ASSERT_EQ(shader1->get_number_of_all_descendants(), 1);
    ASSERT_EQ(shader2->get_number_of_all_children(), 1);
    ASSERT_EQ(shader2->get_number_of_all_descendants(), 1);
    ASSERT_FALSE(shader1->is_entity("foo"));
    ASSERT_FALSE(shader2->is_entity("foo"));
    ASSERT_FALSE(shader1->is_entity("bar"));
    ASSERT_FALSE(shader2->is_entity("bar"));
    ASSERT_TRUE(shader1->is_entity("baz"));
    ASSERT_TRUE(shader2->is_entity("baz"));
}

TEST(species_must_maintain_the_local_name_after_binding_to_a_new_parent, headless_universe_species_with_only_local_name)
{
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

    yli::ontology::MaterialStruct material_struct1;
    material_struct1.shader = shader;
    yli::ontology::Material* const material1 = new yli::ontology::Material(universe, material_struct1, &shader->parent_of_materials);

    yli::ontology::SpeciesStruct species_struct;
    species_struct.scene = scene;
    species_struct.shader = shader;
    species_struct.material = material1;
    yli::ontology::Species* const species = new yli::ontology::Species(universe, species_struct, &material1->parent_of_species);

    yli::ontology::MaterialStruct material_struct2;
    material_struct2.shader = shader;
    yli::ontology::Material* const material2 = new yli::ontology::Material(universe, material_struct2, &shader->parent_of_materials);

    species->set_local_name("foo");
    species->bind_to_new_parent(material2);
    ASSERT_FALSE(material1->is_entity("foo"));
    ASSERT_TRUE(material2->is_entity("foo"));
    ASSERT_EQ(species->get_parent(), material2);
    ASSERT_EQ(material1->get_number_of_all_children(), 0);
    ASSERT_EQ(material1->get_number_of_all_descendants(), 0);
    ASSERT_EQ(material2->get_number_of_all_children(), 1);
    ASSERT_EQ(material2->get_number_of_all_descendants(), 1);

    species->bind_to_new_parent(material1);
    ASSERT_TRUE(material1->is_entity("foo"));
    ASSERT_FALSE(material2->is_entity("foo"));
    ASSERT_EQ(species->get_parent(), material1);
    ASSERT_EQ(material1->get_number_of_all_children(), 1);
    ASSERT_EQ(material1->get_number_of_all_descendants(), 1);
    ASSERT_EQ(material2->get_number_of_all_children(), 0);
    ASSERT_EQ(material2->get_number_of_all_descendants(), 0);
}

TEST(species_must_maintain_the_local_name_after_binding_to_a_new_parent, headless_universe_species_with_global_name_and_local_name)
{
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

    yli::ontology::MaterialStruct material_struct1;
    material_struct1.shader = shader;
    yli::ontology::Material* const material1 = new yli::ontology::Material(universe, material_struct1, &shader->parent_of_materials);

    yli::ontology::SpeciesStruct species_struct;
    species_struct.scene = scene;
    species_struct.shader = shader;
    species_struct.material = material1;
    yli::ontology::Species* const species = new yli::ontology::Species(universe, species_struct, &material1->parent_of_species);

    yli::ontology::MaterialStruct material_struct2;
    material_struct2.shader = shader;
    yli::ontology::Material* const material2 = new yli::ontology::Material(universe, material_struct2, &shader->parent_of_materials);

    species->set_global_name("foo");
    species->set_local_name("bar");
    species->bind_to_new_parent(material2);
    ASSERT_FALSE(material1->is_entity("foo"));
    ASSERT_FALSE(material2->is_entity("foo"));
    ASSERT_FALSE(material1->is_entity("bar"));
    ASSERT_TRUE(material2->is_entity("bar"));
    ASSERT_EQ(species->get_parent(), material2);
    ASSERT_EQ(material1->get_number_of_all_children(), 0);
    ASSERT_EQ(material1->get_number_of_all_descendants(), 0);
    ASSERT_EQ(material2->get_number_of_all_children(), 1);
    ASSERT_EQ(material2->get_number_of_all_descendants(), 1);

    species->bind_to_new_parent(material1);
    ASSERT_FALSE(material1->is_entity("foo"));
    ASSERT_FALSE(material2->is_entity("foo"));
    ASSERT_TRUE(material1->is_entity("bar"));
    ASSERT_FALSE(material2->is_entity("bar"));
    ASSERT_EQ(species->get_parent(), material1);
    ASSERT_EQ(material1->get_number_of_all_children(), 1);
    ASSERT_EQ(material1->get_number_of_all_descendants(), 1);
    ASSERT_EQ(material2->get_number_of_all_children(), 0);
    ASSERT_EQ(material2->get_number_of_all_descendants(), 0);
}

TEST(species_must_not_bind_to_a_new_parent_when_local_name_is_already_in_use, headless_universe_species_with_only_local_name)
{
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

    yli::ontology::MaterialStruct material_struct1;
    material_struct1.shader = shader;
    yli::ontology::Material* const material1 = new yli::ontology::Material(universe, material_struct1, &shader->parent_of_materials);

    yli::ontology::SpeciesStruct species_struct1;
    species_struct1.scene = scene;
    species_struct1.shader = shader;
    species_struct1.material = material1;
    yli::ontology::Species* const species1 = new yli::ontology::Species(universe, species_struct1, &material1->parent_of_species);

    yli::ontology::MaterialStruct material_struct2;
    material_struct2.shader = shader;
    yli::ontology::Material* const material2 = new yli::ontology::Material(universe, material_struct2, &shader->parent_of_materials);

    yli::ontology::SpeciesStruct species_struct2;
    species_struct2.scene = scene;
    species_struct2.shader = shader;
    species_struct2.material = material2;
    yli::ontology::Species* const species2 = new yli::ontology::Species(universe, species_struct2, &material2->parent_of_species);

    species1->set_local_name("foo");
    species2->set_local_name("foo");
    species1->bind_to_new_parent(material2);
    ASSERT_EQ(species1->get_parent(), material1);
    ASSERT_EQ(material1->get_number_of_all_children(), 1);
    ASSERT_EQ(material1->get_number_of_all_descendants(), 1);
    ASSERT_EQ(material2->get_number_of_all_children(), 1);
    ASSERT_EQ(material2->get_number_of_all_descendants(), 1);
    ASSERT_TRUE(material1->is_entity("foo"));
    ASSERT_TRUE(material2->is_entity("foo"));
}

TEST(species_must_not_bind_to_a_new_parent_when_local_name_is_already_in_use, headless_universe_species_with_different_global_names_and_same_local_name)
{
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

    yli::ontology::MaterialStruct material_struct1;
    material_struct1.shader = shader;
    yli::ontology::Material* const material1 = new yli::ontology::Material(universe, material_struct1, &shader->parent_of_materials);

    yli::ontology::SpeciesStruct species_struct1;
    species_struct1.scene = scene;
    species_struct1.shader = shader;
    species_struct1.material = material1;
    yli::ontology::Species* const species1 = new yli::ontology::Species(universe, species_struct1, &material1->parent_of_species);

    yli::ontology::MaterialStruct material_struct2;
    material_struct2.shader = shader;
    yli::ontology::Material* const material2 = new yli::ontology::Material(universe, material_struct2, &shader->parent_of_materials);

    yli::ontology::SpeciesStruct species_struct2;
    species_struct2.scene = scene;
    species_struct2.shader = shader;
    species_struct2.material = material2;
    yli::ontology::Species* const species2 = new yli::ontology::Species(universe, species_struct2, &material2->parent_of_species);

    species1->set_global_name("foo");
    species2->set_global_name("bar");
    species1->set_local_name("baz");
    species2->set_local_name("baz");
    species1->bind_to_new_parent(material2);
    ASSERT_EQ(species1->get_parent(), material1);
    ASSERT_EQ(material1->get_number_of_all_children(), 1);
    ASSERT_EQ(material1->get_number_of_all_descendants(), 1);
    ASSERT_EQ(material2->get_number_of_all_children(), 1);
    ASSERT_EQ(material2->get_number_of_all_descendants(), 1);
    ASSERT_FALSE(material1->is_entity("foo"));
    ASSERT_FALSE(material2->is_entity("foo"));
    ASSERT_FALSE(material1->is_entity("bar"));
    ASSERT_FALSE(material2->is_entity("bar"));
    ASSERT_TRUE(material1->is_entity("baz"));
    ASSERT_TRUE(material2->is_entity("baz"));
}

TEST(object_must_maintain_the_local_name_after_binding_to_a_new_parent, headless_universe_object_with_only_local_name)
{
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

    yli::ontology::MaterialStruct material_struct;
    material_struct.shader = shader;
    yli::ontology::Material* const material = new yli::ontology::Material(universe, material_struct, &shader->parent_of_materials);

    yli::ontology::SpeciesStruct species_struct1;
    species_struct1.scene = scene;
    species_struct1.shader = shader;
    species_struct1.material = material;
    yli::ontology::Species* const species1 = new yli::ontology::Species(universe, species_struct1, &material->parent_of_species);

    yli::ontology::ObjectStruct object_struct;
    object_struct.species_parent = species1;
    yli::ontology::Object* const object = new yli::ontology::Object(universe, object_struct, &species1->parent_of_objects);

    yli::ontology::SpeciesStruct species_struct2;
    species_struct2.scene = scene;
    species_struct2.shader = shader;
    species_struct2.material = material;
    yli::ontology::Species* const species2 = new yli::ontology::Species(universe, species_struct2, &material->parent_of_species);

    object->set_local_name("foo");
    object->bind_to_new_parent(species2);
    ASSERT_FALSE(species1->is_entity("foo"));
    ASSERT_TRUE(species2->is_entity("foo"));
    ASSERT_EQ(object->get_parent(), species2);
    ASSERT_EQ(species1->get_number_of_all_children(), 0);
    ASSERT_EQ(species1->get_number_of_all_descendants(), 0);
    ASSERT_EQ(species2->get_number_of_all_children(), 1);
    ASSERT_EQ(species2->get_number_of_all_descendants(), 1);

    object->bind_to_new_parent(species1);
    ASSERT_TRUE(species1->is_entity("foo"));
    ASSERT_FALSE(species2->is_entity("foo"));
    ASSERT_EQ(object->get_parent(), species1);
    ASSERT_EQ(species1->get_number_of_all_children(), 1);
    ASSERT_EQ(species1->get_number_of_all_descendants(), 1);
    ASSERT_EQ(species2->get_number_of_all_children(), 0);
    ASSERT_EQ(species2->get_number_of_all_descendants(), 0);
}

TEST(object_must_maintain_the_local_name_after_binding_to_a_new_parent, headless_universe_object_with_global_name_and_local_name)
{
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

    yli::ontology::MaterialStruct material_struct;
    material_struct.shader = shader;
    yli::ontology::Material* const material = new yli::ontology::Material(universe, material_struct, &shader->parent_of_materials);

    yli::ontology::SpeciesStruct species_struct1;
    species_struct1.scene = scene;
    species_struct1.shader = shader;
    species_struct1.material = material;
    yli::ontology::Species* const species1 = new yli::ontology::Species(universe, species_struct1, &material->parent_of_species);

    yli::ontology::ObjectStruct object_struct;
    object_struct.species_parent = species1;
    yli::ontology::Object* const object = new yli::ontology::Object(universe, object_struct, &species1->parent_of_objects);

    yli::ontology::SpeciesStruct species_struct2;
    species_struct2.scene = scene;
    species_struct2.shader = shader;
    species_struct2.material = material;
    yli::ontology::Species* const species2 = new yli::ontology::Species(universe, species_struct2, &material->parent_of_species);

    object->set_global_name("foo");
    object->set_local_name("bar");
    object->bind_to_new_parent(species2);
    ASSERT_FALSE(species1->is_entity("foo"));
    ASSERT_FALSE(species2->is_entity("foo"));
    ASSERT_FALSE(species1->is_entity("bar"));
    ASSERT_TRUE(species2->is_entity("bar"));
    ASSERT_EQ(object->get_parent(), species2);
    ASSERT_EQ(species1->get_number_of_all_children(), 0);
    ASSERT_EQ(species1->get_number_of_all_descendants(), 0);
    ASSERT_EQ(species2->get_number_of_all_children(), 1);
    ASSERT_EQ(species2->get_number_of_all_descendants(), 1);

    object->bind_to_new_parent(species1);
    ASSERT_FALSE(species1->is_entity("foo"));
    ASSERT_FALSE(species2->is_entity("foo"));
    ASSERT_TRUE(species1->is_entity("bar"));
    ASSERT_FALSE(species2->is_entity("bar"));
    ASSERT_EQ(object->get_parent(), species1);
    ASSERT_EQ(species1->get_number_of_all_children(), 1);
    ASSERT_EQ(species1->get_number_of_all_descendants(), 1);
    ASSERT_EQ(species2->get_number_of_all_children(), 0);
    ASSERT_EQ(species2->get_number_of_all_descendants(), 0);
}

TEST(object_must_not_bind_to_a_new_parent_when_local_name_is_already_in_use, headless_universe_objects_with_only_local_name)
{
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

    yli::ontology::MaterialStruct material_struct;
    material_struct.shader = shader;
    yli::ontology::Material* const material = new yli::ontology::Material(universe, material_struct, &shader->parent_of_materials);

    yli::ontology::SpeciesStruct species_struct1;
    species_struct1.scene = scene;
    species_struct1.shader = shader;
    species_struct1.material = material;
    yli::ontology::Species* const species1 = new yli::ontology::Species(universe, species_struct1, &material->parent_of_species);

    yli::ontology::ObjectStruct object_struct1;
    object_struct1.species_parent = species1;
    yli::ontology::Object* const object1 = new yli::ontology::Object(universe, object_struct1, &species1->parent_of_objects);

    yli::ontology::SpeciesStruct species_struct2;
    species_struct2.scene = scene;
    species_struct2.shader = shader;
    species_struct2.material = material;
    yli::ontology::Species* const species2 = new yli::ontology::Species(universe, species_struct2, &material->parent_of_species);

    yli::ontology::ObjectStruct object_struct2;
    object_struct2.species_parent = species2;
    yli::ontology::Object* const object2 = new yli::ontology::Object(universe, object_struct2, &species2->parent_of_objects);

    object1->set_local_name("foo");
    object2->set_local_name("foo");
    object1->bind_to_new_parent(species2);
    ASSERT_EQ(object1->get_parent(), species1);
    ASSERT_EQ(species1->get_number_of_all_children(), 1);
    ASSERT_EQ(species1->get_number_of_all_descendants(), 1);
    ASSERT_EQ(species2->get_number_of_all_children(), 1);
    ASSERT_EQ(species2->get_number_of_all_descendants(), 1);
    ASSERT_TRUE(species1->is_entity("foo"));
    ASSERT_TRUE(species2->is_entity("foo"));
}

TEST(object_must_not_bind_to_a_new_parent_when_local_name_is_already_in_use, headless_universe_objects_with_different_global_names_and_same_local_name)
{
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

    yli::ontology::MaterialStruct material_struct;
    material_struct.shader = shader;
    yli::ontology::Material* const material = new yli::ontology::Material(universe, material_struct, &shader->parent_of_materials);

    yli::ontology::SpeciesStruct species_struct1;
    species_struct1.scene = scene;
    species_struct1.shader = shader;
    species_struct1.material = material;
    yli::ontology::Species* const species1 = new yli::ontology::Species(universe, species_struct1, &material->parent_of_species);

    yli::ontology::ObjectStruct object_struct1;
    object_struct1.species_parent = species1;
    yli::ontology::Object* const object1 = new yli::ontology::Object(universe, object_struct1, &species1->parent_of_objects);

    yli::ontology::SpeciesStruct species_struct2;
    species_struct2.scene = scene;
    species_struct2.shader = shader;
    species_struct2.material = material;
    yli::ontology::Species* const species2 = new yli::ontology::Species(universe, species_struct2, &material->parent_of_species);

    yli::ontology::ObjectStruct object_struct2;
    object_struct2.species_parent = species2;
    yli::ontology::Object* const object2 = new yli::ontology::Object(universe, object_struct2, &species2->parent_of_objects);

    object1->set_global_name("foo");
    object2->set_global_name("bar");
    object1->set_local_name("baz");
    object2->set_local_name("baz");
    object1->bind_to_new_parent(species2);
    ASSERT_EQ(object1->get_parent(), species1);
    ASSERT_EQ(species1->get_number_of_all_children(), 1);
    ASSERT_EQ(species1->get_number_of_all_descendants(), 1);
    ASSERT_EQ(species2->get_number_of_all_children(), 1);
    ASSERT_EQ(species2->get_number_of_all_descendants(), 1);
    ASSERT_FALSE(species1->is_entity("foo"));
    ASSERT_FALSE(species2->is_entity("foo"));
    ASSERT_FALSE(species1->is_entity("bar"));
    ASSERT_FALSE(species2->is_entity("bar"));
    ASSERT_TRUE(species1->is_entity("baz"));
    ASSERT_TRUE(species2->is_entity("baz"));
}
