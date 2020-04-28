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
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/common/datatype.hpp"
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
#include "code/ylikuutio/ontology/any_value_entity.hpp"
#include "code/ylikuutio/ontology/any_struct_entity.hpp"
#include "code/ylikuutio/ontology/universe_struct.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"
#include "code/ylikuutio/ontology/shader_struct.hpp"
#include "code/ylikuutio/ontology/material_struct.hpp"
#include "code/ylikuutio/ontology/species_struct.hpp"
#include "code/ylikuutio/ontology/object_struct.hpp"
#include "code/ylikuutio/ontology/camera_struct.hpp"
#include "code/ylikuutio/ontology/font2D.hpp"

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string, std::getline
#include <variant>  // std::variant
#include <vector>   // std::vector

// Tests for `yli::ontology::Universe` callbacks
// that can be tested in headless mode.

namespace yli
{
    namespace ontology
    {
        class Entity;
        class Console;
    }
}

// Public `Entity` bind callbacks.

TEST(object_must_be_bound_to_species_appropriately, universe_callback)
{
    yli::ontology::Console* const console = nullptr;

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

    yli::ontology::Material* const material = new yli::ontology::Material(universe, yli::ontology::MaterialStruct(), &shader->parent_of_materials);

    const std::string species1_name = "foo";

    yli::ontology::SpeciesStruct species1_struct;
    species1_struct.scene = scene;
    species1_struct.shader = shader;
    species1_struct.material = material;
    yli::ontology::Species* const species1 = new yli::ontology::Species(universe, species1_struct, &material->parent_of_species);
    species1->set_name(species1_name);

    const std::string object_name = "bar";

    yli::ontology::ObjectStruct object_struct;
    object_struct.species_parent = species1;
    yli::ontology::Object* const object = new yli::ontology::Object(universe, object_struct, &species1->parent_of_objects);
    object->set_name(object_name);

    const std::string species2_name = "baz";

    yli::ontology::SpeciesStruct species2_struct;
    species2_struct.scene = scene;
    species2_struct.shader = shader;
    species2_struct.material = material;
    yli::ontology::Species* const species2 = new yli::ontology::Species(universe, species2_struct, &material->parent_of_species);
    species2->set_name(species2_name);

    const std::vector<std::string> bind_object_to_species2_command_parameters { object_name, species2_name };

    ASSERT_EQ(object->get_parent(), species1);
    ASSERT_EQ(species1->get_number_of_children(), 1);
    ASSERT_EQ(species2->get_number_of_children(), 0);

    universe->bind(console, universe, bind_object_to_species2_command_parameters);
    ASSERT_EQ(object->get_parent(), species2);
    ASSERT_EQ(species1->get_number_of_children(), 0);
    ASSERT_EQ(species2->get_number_of_children(), 1);
}

// Public `Entity` create callbacks.

TEST(any_value_entity_must_be_created_appropriately, universe_callback_bool_true)
{
    yli::ontology::Console* const console = nullptr;

    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    const std::string any_value_entity_name = "foo";
    const std::string any_value_entity_type = "bool";
    const std::string any_value_entity_value = "true";
    ASSERT_FALSE(universe->is_entity(any_value_entity_name));
    ASSERT_EQ(universe->get_entity(any_value_entity_name), nullptr);

    const std::vector<std::string> command_parameters { any_value_entity_name, any_value_entity_type, any_value_entity_value };
    universe->create_AnyValueEntity(console, universe, command_parameters);
    ASSERT_TRUE(universe->is_entity(any_value_entity_name));

    yli::ontology::Entity* const entity = universe->get_entity(any_value_entity_name);
    ASSERT_NE(entity, nullptr);

    yli::ontology::AnyValueEntity* const any_value_entity = dynamic_cast<yli::ontology::AnyValueEntity*>(entity);
    ASSERT_NE(any_value_entity, nullptr);

    yli::common::AnyValue* any_value = any_value_entity;
    ASSERT_TRUE(std::holds_alternative<bool>(any_value->data));
    ASSERT_TRUE(std::get<bool>(any_value->data));

    ASSERT_TRUE(std::holds_alternative<bool>(any_value_entity->data));
    ASSERT_TRUE(std::get<bool>(any_value_entity->data));
}

TEST(any_value_entity_must_be_created_appropriately, universe_callback_bool_false)
{
    yli::ontology::Console* const console = nullptr;

    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = false;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    const std::string any_value_entity_name = "foo";
    const std::string any_value_entity_type = "bool";
    const std::string any_value_entity_value = "false";
    ASSERT_FALSE(universe->is_entity(any_value_entity_name));
    ASSERT_EQ(universe->get_entity(any_value_entity_name), nullptr);

    const std::vector<std::string> command_parameters { any_value_entity_name, any_value_entity_type, any_value_entity_value };
    universe->create_AnyValueEntity(console, universe, command_parameters);
    ASSERT_TRUE(universe->is_entity(any_value_entity_name));

    yli::ontology::Entity* const entity = universe->get_entity(any_value_entity_name);
    ASSERT_NE(entity, nullptr);

    yli::ontology::AnyValueEntity* const any_value_entity = dynamic_cast<yli::ontology::AnyValueEntity*>(entity);
    ASSERT_NE(any_value_entity, nullptr);

    yli::common::AnyValue* any_value = any_value_entity;
    ASSERT_TRUE(std::holds_alternative<bool>(any_value->data));
    ASSERT_FALSE(std::get<bool>(any_value->data));

    ASSERT_TRUE(std::holds_alternative<bool>(any_value_entity->data));
    ASSERT_FALSE(std::get<bool>(any_value_entity->data));
}

TEST(any_value_entity_must_be_created_appropriately, universe_callback_float_0)
{
    yli::ontology::Console* const console = nullptr;

    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    const std::string any_value_entity_name = "foo";
    const std::string any_value_entity_type = "float";
    const std::string any_value_entity_value = "0";
    ASSERT_FALSE(universe->is_entity(any_value_entity_name));
    ASSERT_EQ(universe->get_entity(any_value_entity_name), nullptr);

    const std::vector<std::string> command_parameters { any_value_entity_name, any_value_entity_type, any_value_entity_value };
    universe->create_AnyValueEntity(console, universe, command_parameters);
    ASSERT_TRUE(universe->is_entity(any_value_entity_name));

    yli::ontology::Entity* const entity = universe->get_entity(any_value_entity_name);
    ASSERT_NE(entity, nullptr);

    yli::ontology::AnyValueEntity* const any_value_entity = dynamic_cast<yli::ontology::AnyValueEntity*>(entity);
    ASSERT_NE(any_value_entity, nullptr);

    yli::common::AnyValue* any_value = any_value_entity;
    ASSERT_TRUE(std::holds_alternative<float>(any_value->data));
    ASSERT_EQ(std::get<float>(any_value->data), 0.0f);

    ASSERT_TRUE(std::holds_alternative<float>(any_value_entity->data));
    ASSERT_EQ(std::get<float>(any_value_entity->data), 0.0f);
}

TEST(any_value_entity_must_be_created_appropriately, universe_callback_float_0_0)
{
    yli::ontology::Console* const console = nullptr;

    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    const std::string any_value_entity_name = "foo";
    const std::string any_value_entity_type = "float";
    const std::string any_value_entity_value = "0.0";
    ASSERT_FALSE(universe->is_entity(any_value_entity_name));
    ASSERT_EQ(universe->get_entity(any_value_entity_name), nullptr);

    const std::vector<std::string> command_parameters { any_value_entity_name, any_value_entity_type, any_value_entity_value };
    universe->create_AnyValueEntity(console, universe, command_parameters);
    ASSERT_TRUE(universe->is_entity(any_value_entity_name));

    yli::ontology::Entity* const entity = universe->get_entity(any_value_entity_name);
    ASSERT_NE(entity, nullptr);

    yli::ontology::AnyValueEntity* const any_value_entity = dynamic_cast<yli::ontology::AnyValueEntity*>(entity);
    ASSERT_NE(any_value_entity, nullptr);

    yli::common::AnyValue* any_value = any_value_entity;
    ASSERT_TRUE(std::holds_alternative<float>(any_value->data));
    ASSERT_EQ(std::get<float>(any_value->data), 0.0f);

    ASSERT_TRUE(std::holds_alternative<float>(any_value_entity->data));
    ASSERT_EQ(std::get<float>(any_value_entity->data), 0.0f);
}

TEST(any_value_entity_must_be_created_appropriately, universe_callback_float_pi)
{
    yli::ontology::Console* const console = nullptr;

    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    const std::string any_value_entity_name = "foo";
    const std::string any_value_entity_type = "float";
    const std::string any_value_entity_value = "3.1415927";
    ASSERT_FALSE(universe->is_entity(any_value_entity_name));
    ASSERT_EQ(universe->get_entity(any_value_entity_name), nullptr);

    const std::vector<std::string> command_parameters { any_value_entity_name, any_value_entity_type, any_value_entity_value };
    universe->create_AnyValueEntity(console, universe, command_parameters);
    ASSERT_TRUE(universe->is_entity(any_value_entity_name));

    yli::ontology::Entity* const entity = universe->get_entity(any_value_entity_name);
    ASSERT_NE(entity, nullptr);

    yli::ontology::AnyValueEntity* const any_value_entity = dynamic_cast<yli::ontology::AnyValueEntity*>(entity);
    ASSERT_NE(any_value_entity, nullptr);

    yli::common::AnyValue* any_value = any_value_entity;
    ASSERT_TRUE(std::holds_alternative<float>(any_value->data));
    ASSERT_GT(std::get<float>(any_value->data), 3.141592f);
    ASSERT_LT(std::get<float>(any_value->data), 3.141593f);

    ASSERT_TRUE(std::holds_alternative<float>(any_value_entity->data));
    ASSERT_GT(std::get<float>(any_value_entity->data), 3.141592f);
    ASSERT_LT(std::get<float>(any_value_entity->data), 3.141593f);
}

TEST(any_value_entity_must_be_created_appropriately, universe_callback_double_0)
{
    yli::ontology::Console* const console = nullptr;

    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    const std::string any_value_entity_name = "foo";
    const std::string any_value_entity_type = "double";
    const std::string any_value_entity_value = "0";
    ASSERT_FALSE(universe->is_entity(any_value_entity_name));
    ASSERT_EQ(universe->get_entity(any_value_entity_name), nullptr);

    const std::vector<std::string> command_parameters { any_value_entity_name, any_value_entity_type, any_value_entity_value };
    universe->create_AnyValueEntity(console, universe, command_parameters);
    ASSERT_TRUE(universe->is_entity(any_value_entity_name));

    yli::ontology::Entity* const entity = universe->get_entity(any_value_entity_name);
    ASSERT_NE(entity, nullptr);

    yli::ontology::AnyValueEntity* const any_value_entity = dynamic_cast<yli::ontology::AnyValueEntity*>(entity);
    ASSERT_NE(any_value_entity, nullptr);

    yli::common::AnyValue* any_value = any_value_entity;
    ASSERT_TRUE(std::holds_alternative<double>(any_value->data));
    ASSERT_EQ(std::get<double>(any_value->data), 0.0f);

    ASSERT_TRUE(std::holds_alternative<double>(any_value_entity->data));
    ASSERT_EQ(std::get<double>(any_value_entity->data), 0.0f);
}

TEST(any_value_entity_must_be_created_appropriately, universe_callback_double_0_0)
{
    yli::ontology::Console* const console = nullptr;

    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    const std::string any_value_entity_name = "foo";
    const std::string any_value_entity_type = "double";
    const std::string any_value_entity_value = "0.0";
    ASSERT_FALSE(universe->is_entity(any_value_entity_name));
    ASSERT_EQ(universe->get_entity(any_value_entity_name), nullptr);

    const std::vector<std::string> command_parameters { any_value_entity_name, any_value_entity_type, any_value_entity_value };
    universe->create_AnyValueEntity(console, universe, command_parameters);
    ASSERT_TRUE(universe->is_entity(any_value_entity_name));

    yli::ontology::Entity* const entity = universe->get_entity(any_value_entity_name);
    ASSERT_NE(entity, nullptr);

    yli::ontology::AnyValueEntity* const any_value_entity = dynamic_cast<yli::ontology::AnyValueEntity*>(entity);
    ASSERT_NE(any_value_entity, nullptr);

    yli::common::AnyValue* any_value = any_value_entity;
    ASSERT_TRUE(std::holds_alternative<double>(any_value->data));
    ASSERT_EQ(std::get<double>(any_value->data), 0.0f);

    ASSERT_TRUE(std::holds_alternative<double>(any_value_entity->data));
    ASSERT_EQ(std::get<double>(any_value_entity->data), 0.0f);
}

TEST(any_value_entity_must_be_created_appropriately, universe_callback_double_pi)
{
    yli::ontology::Console* const console = nullptr;

    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    const std::string any_value_entity_name = "foo";
    const std::string any_value_entity_type = "double";
    const std::string any_value_entity_value = "3.1415927";
    ASSERT_FALSE(universe->is_entity(any_value_entity_name));
    ASSERT_EQ(universe->get_entity(any_value_entity_name), nullptr);

    const std::vector<std::string> command_parameters { any_value_entity_name, any_value_entity_type, any_value_entity_value };
    universe->create_AnyValueEntity(console, universe, command_parameters);
    ASSERT_TRUE(universe->is_entity(any_value_entity_name));

    yli::ontology::Entity* const entity = universe->get_entity(any_value_entity_name);
    ASSERT_NE(entity, nullptr);

    yli::ontology::AnyValueEntity* const any_value_entity = dynamic_cast<yli::ontology::AnyValueEntity*>(entity);
    ASSERT_NE(any_value_entity, nullptr);

    yli::common::AnyValue* any_value = any_value_entity;
    ASSERT_TRUE(std::holds_alternative<double>(any_value->data));
    ASSERT_EQ(std::get<double>(any_value->data), 3.1415927);

    ASSERT_TRUE(std::holds_alternative<double>(any_value_entity->data));
    ASSERT_EQ(std::get<double>(any_value_entity->data), 3.1415927);
}

TEST(any_value_entity_must_be_created_appropriately, universe_callback_int32_t_0)
{
    yli::ontology::Console* const console = nullptr;

    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    const std::string any_value_entity_name = "foo";
    const std::string any_value_entity_type = "int32_t";
    const std::string any_value_entity_value = "0";
    ASSERT_FALSE(universe->is_entity(any_value_entity_name));
    ASSERT_EQ(universe->get_entity(any_value_entity_name), nullptr);

    const std::vector<std::string> command_parameters { any_value_entity_name, any_value_entity_type, any_value_entity_value };
    universe->create_AnyValueEntity(console, universe, command_parameters);
    ASSERT_TRUE(universe->is_entity(any_value_entity_name));

    yli::ontology::Entity* const entity = universe->get_entity(any_value_entity_name);
    ASSERT_NE(entity, nullptr);

    yli::ontology::AnyValueEntity* const any_value_entity = dynamic_cast<yli::ontology::AnyValueEntity*>(entity);
    ASSERT_NE(any_value_entity, nullptr);

    yli::common::AnyValue* any_value = any_value_entity;
    ASSERT_TRUE(std::holds_alternative<int32_t>(any_value->data));
    ASSERT_EQ(std::get<int32_t>(any_value->data), 0);

    ASSERT_TRUE(std::holds_alternative<int32_t>(any_value_entity->data));
    ASSERT_EQ(std::get<int32_t>(any_value_entity->data), 0);
}

TEST(any_value_entity_must_be_created_appropriately, universe_callback_int32_t_plus_1)
{
    yli::ontology::Console* const console = nullptr;

    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    const std::string any_value_entity_name = "foo";
    const std::string any_value_entity_type = "int32_t";
    const std::string any_value_entity_value = "1";
    ASSERT_FALSE(universe->is_entity(any_value_entity_name));
    ASSERT_EQ(universe->get_entity(any_value_entity_name), nullptr);

    const std::vector<std::string> command_parameters { any_value_entity_name, any_value_entity_type, any_value_entity_value };
    universe->create_AnyValueEntity(console, universe, command_parameters);
    ASSERT_TRUE(universe->is_entity(any_value_entity_name));

    yli::ontology::Entity* const entity = universe->get_entity(any_value_entity_name);
    ASSERT_NE(entity, nullptr);

    yli::ontology::AnyValueEntity* const any_value_entity = dynamic_cast<yli::ontology::AnyValueEntity*>(entity);
    ASSERT_NE(any_value_entity, nullptr);

    yli::common::AnyValue* any_value = any_value_entity;
    ASSERT_TRUE(std::holds_alternative<int32_t>(any_value->data));
    ASSERT_EQ(std::get<int32_t>(any_value->data), 1);

    ASSERT_TRUE(std::holds_alternative<int32_t>(any_value_entity->data));
    ASSERT_EQ(std::get<int32_t>(any_value_entity->data), 1);
}

TEST(any_value_entity_must_be_created_appropriately, universe_callback_int32_t_minus_1)
{
    yli::ontology::Console* const console = nullptr;

    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    const std::string any_value_entity_name = "foo";
    const std::string any_value_entity_type = "int32_t";
    const std::string any_value_entity_value = "-1";
    ASSERT_FALSE(universe->is_entity(any_value_entity_name));
    ASSERT_EQ(universe->get_entity(any_value_entity_name), nullptr);

    const std::vector<std::string> command_parameters { any_value_entity_name, any_value_entity_type, any_value_entity_value };
    universe->create_AnyValueEntity(console, universe, command_parameters);
    ASSERT_TRUE(universe->is_entity(any_value_entity_name));

    yli::ontology::Entity* const entity = universe->get_entity(any_value_entity_name);
    ASSERT_NE(entity, nullptr);

    yli::ontology::AnyValueEntity* const any_value_entity = dynamic_cast<yli::ontology::AnyValueEntity*>(entity);
    ASSERT_NE(any_value_entity, nullptr);

    yli::common::AnyValue* any_value = any_value_entity;
    ASSERT_TRUE(std::holds_alternative<int32_t>(any_value->data));
    ASSERT_EQ(std::get<int32_t>(any_value->data), -1);

    ASSERT_TRUE(std::holds_alternative<int32_t>(any_value_entity->data));
    ASSERT_EQ(std::get<int32_t>(any_value_entity->data), -1);
}

TEST(any_value_entity_must_be_created_appropriately, universe_callback_int32_t_max)
{
    yli::ontology::Console* const console = nullptr;

    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    const std::string any_value_entity_name = "foo";
    const std::string any_value_entity_type = "int32_t";
    const std::string any_value_entity_value = "2147483647";
    ASSERT_FALSE(universe->is_entity(any_value_entity_name));
    ASSERT_EQ(universe->get_entity(any_value_entity_name), nullptr);

    const std::vector<std::string> command_parameters { any_value_entity_name, any_value_entity_type, any_value_entity_value };
    universe->create_AnyValueEntity(console, universe, command_parameters);
    ASSERT_TRUE(universe->is_entity(any_value_entity_name));

    yli::ontology::Entity* const entity = universe->get_entity(any_value_entity_name);
    ASSERT_NE(entity, nullptr);

    yli::ontology::AnyValueEntity* const any_value_entity = dynamic_cast<yli::ontology::AnyValueEntity*>(entity);
    ASSERT_NE(any_value_entity, nullptr);

    yli::common::AnyValue* any_value = any_value_entity;
    ASSERT_TRUE(std::holds_alternative<int32_t>(any_value->data));
    ASSERT_EQ(std::get<int32_t>(any_value->data), 2147483647);

    ASSERT_TRUE(std::holds_alternative<int32_t>(any_value_entity->data));
    ASSERT_EQ(std::get<int32_t>(any_value_entity->data), 2147483647);
}

TEST(any_value_entity_must_be_created_appropriately, universe_callback_int32_t_min)
{
    yli::ontology::Console* const console = nullptr;

    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    const std::string any_value_entity_name = "foo";
    const std::string any_value_entity_type = "int32_t";
    const std::string any_value_entity_value = "-2147483648";
    ASSERT_FALSE(universe->is_entity(any_value_entity_name));
    ASSERT_EQ(universe->get_entity(any_value_entity_name), nullptr);

    const std::vector<std::string> command_parameters { any_value_entity_name, any_value_entity_type, any_value_entity_value };
    universe->create_AnyValueEntity(console, universe, command_parameters);
    ASSERT_TRUE(universe->is_entity(any_value_entity_name));

    yli::ontology::Entity* const entity = universe->get_entity(any_value_entity_name);
    ASSERT_NE(entity, nullptr);

    yli::ontology::AnyValueEntity* const any_value_entity = dynamic_cast<yli::ontology::AnyValueEntity*>(entity);
    ASSERT_NE(any_value_entity, nullptr);

    yli::common::AnyValue* any_value = any_value_entity;
    ASSERT_TRUE(std::holds_alternative<int32_t>(any_value->data));
    ASSERT_EQ(std::get<int32_t>(any_value->data), -2147483648);

    ASSERT_TRUE(std::holds_alternative<int32_t>(any_value_entity->data));
    ASSERT_EQ(std::get<int32_t>(any_value_entity->data), -2147483648);
}

TEST(any_value_entity_must_be_created_appropriately, universe_callback_uint32_t_0)
{
    yli::ontology::Console* const console = nullptr;

    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    const std::string any_value_entity_name = "foo";
    const std::string any_value_entity_type = "uint32_t";
    const std::string any_value_entity_value = "0";
    ASSERT_FALSE(universe->is_entity(any_value_entity_name));
    ASSERT_EQ(universe->get_entity(any_value_entity_name), nullptr);

    const std::vector<std::string> command_parameters { any_value_entity_name, any_value_entity_type, any_value_entity_value };
    universe->create_AnyValueEntity(console, universe, command_parameters);
    ASSERT_TRUE(universe->is_entity(any_value_entity_name));

    yli::ontology::Entity* const entity = universe->get_entity(any_value_entity_name);
    ASSERT_NE(entity, nullptr);

    yli::ontology::AnyValueEntity* const any_value_entity = dynamic_cast<yli::ontology::AnyValueEntity*>(entity);
    ASSERT_NE(any_value_entity, nullptr);

    yli::common::AnyValue* any_value = any_value_entity;
    ASSERT_TRUE(std::holds_alternative<uint32_t>(any_value->data));
    ASSERT_EQ(std::get<uint32_t>(any_value->data), 0);

    ASSERT_TRUE(std::holds_alternative<uint32_t>(any_value_entity->data));
    ASSERT_EQ(std::get<uint32_t>(any_value_entity->data), 0);
}

TEST(any_value_entity_must_be_created_appropriately, universe_callback_uint32_t_1)
{
    yli::ontology::Console* const console = nullptr;

    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    const std::string any_value_entity_name = "foo";
    const std::string any_value_entity_type = "uint32_t";
    const std::string any_value_entity_value = "1";
    ASSERT_FALSE(universe->is_entity(any_value_entity_name));
    ASSERT_EQ(universe->get_entity(any_value_entity_name), nullptr);

    const std::vector<std::string> command_parameters { any_value_entity_name, any_value_entity_type, any_value_entity_value };
    universe->create_AnyValueEntity(console, universe, command_parameters);
    ASSERT_TRUE(universe->is_entity(any_value_entity_name));

    yli::ontology::Entity* const entity = universe->get_entity(any_value_entity_name);
    ASSERT_NE(entity, nullptr);

    yli::ontology::AnyValueEntity* const any_value_entity = dynamic_cast<yli::ontology::AnyValueEntity*>(entity);
    ASSERT_NE(any_value_entity, nullptr);

    yli::common::AnyValue* any_value = any_value_entity;
    ASSERT_TRUE(std::holds_alternative<uint32_t>(any_value->data));
    ASSERT_EQ(std::get<uint32_t>(any_value->data), 1);

    ASSERT_TRUE(std::holds_alternative<uint32_t>(any_value_entity->data));
    ASSERT_EQ(std::get<uint32_t>(any_value_entity->data), 1);
}

TEST(any_value_entity_must_be_created_appropriately, universe_callback_uint32_t_max)
{
    yli::ontology::Console* const console = nullptr;

    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    const std::string any_value_entity_name = "foo";
    const std::string any_value_entity_type = "uint32_t";
    const std::string any_value_entity_value = "4294967295";
    ASSERT_FALSE(universe->is_entity(any_value_entity_name));
    ASSERT_EQ(universe->get_entity(any_value_entity_name), nullptr);

    const std::vector<std::string> command_parameters { any_value_entity_name, any_value_entity_type, any_value_entity_value };
    universe->create_AnyValueEntity(console, universe, command_parameters);
    ASSERT_TRUE(universe->is_entity(any_value_entity_name));

    yli::ontology::Entity* const entity = universe->get_entity(any_value_entity_name);
    ASSERT_NE(entity, nullptr);

    yli::ontology::AnyValueEntity* const any_value_entity = dynamic_cast<yli::ontology::AnyValueEntity*>(entity);
    ASSERT_NE(any_value_entity, nullptr);

    yli::common::AnyValue* any_value = any_value_entity;
    ASSERT_TRUE(std::holds_alternative<uint32_t>(any_value->data));
    ASSERT_EQ(std::get<uint32_t>(any_value->data), 4294967295);

    ASSERT_TRUE(std::holds_alternative<uint32_t>(any_value_entity->data));
    ASSERT_EQ(std::get<uint32_t>(any_value_entity->data), 4294967295);
}

TEST(any_struct_entity_must_be_created_appropriately, universe_callback_any_struct)
{
    yli::ontology::Console* const console = nullptr;

    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    const std::string any_value_entity_name = "foo";
    ASSERT_FALSE(universe->is_entity(any_value_entity_name));
    ASSERT_EQ(universe->get_entity(any_value_entity_name), nullptr);

    const std::vector<std::string> command_parameters { any_value_entity_name };
    universe->create_AnyStructEntity(console, universe, command_parameters);
    ASSERT_TRUE(universe->is_entity(any_value_entity_name));

    yli::ontology::Entity* const entity = universe->get_entity(any_value_entity_name);
    ASSERT_NE(entity, nullptr);

    yli::ontology::AnyStructEntity* const any_struct_entity = dynamic_cast<yli::ontology::AnyStructEntity*>(entity);
    ASSERT_NE(any_struct_entity, nullptr);
}

// Public `Entity` delete callbacks.

TEST(scene_must_be_deleted_appropriately, universe_callback)
{
    yli::ontology::Console* const console = nullptr;

    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::World* const world = new yli::ontology::World(universe, &universe->parent_of_worlds);

    const std::string scene_name = "foo";

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);
    scene->set_name(scene_name);

    const std::vector<std::string> command_parameters { scene_name };
    universe->activate(console, universe, command_parameters);

    universe->delete_entity(console, universe, command_parameters);
    ASSERT_EQ(universe->get_active_scene(), nullptr);
}

// Public `Entity` activate callbacks.

TEST(scene_must_be_activated_appropriately, universe_callback)
{
    yli::ontology::Console* const console = nullptr;

    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::World* const world = new yli::ontology::World(universe, &universe->parent_of_worlds);

    const std::string scene_name = "foo";

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);
    scene->set_name(scene_name);

    ASSERT_EQ(universe->get_active_scene(), nullptr);

    const std::vector<std::string> command_parameters { scene_name };
    universe->activate(console, universe, command_parameters);
    ASSERT_EQ(universe->get_active_scene(), scene);
}

TEST(console_must_be_activated_appropriately, universe_callback_without_font2D)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    const std::string console_name = "foo";

    yli::ontology::Console* const console = new yli::ontology::Console(universe, &universe->parent_of_consoles);
    console->set_name(console_name);

    ASSERT_EQ(universe->get_active_console(), nullptr);

    const std::vector<std::string> command_parameters { console_name };
    universe->activate(console, universe, command_parameters);
    ASSERT_EQ(universe->get_active_console(), console);
}

TEST(console_must_be_activated_appropriately, universe_callback_with_font2D)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::Font2D* font2D = new yli::ontology::Font2D(universe, yli::ontology::FontStruct(), &universe->parent_of_font2Ds);

    const std::string console_name = "foo";

    yli::ontology::Console* const console = new yli::ontology::Console(universe, &universe->parent_of_consoles);
    console->set_name(console_name);

    ASSERT_EQ(universe->get_active_console(), nullptr);

    const std::vector<std::string> command_parameters { console_name };
    universe->activate(console, universe, command_parameters);
    ASSERT_EQ(universe->get_active_console(), console);
}

TEST(scene_and_camera_must_be_activated_appropriately, universe_callback)
{
    yli::ontology::Console* const console = nullptr;

    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::World* const world = new yli::ontology::World(universe, &universe->parent_of_worlds);

    const std::string scene_name = "foo";

    yli::ontology::SceneStruct scene_struct;
    scene_struct.world = world;
    yli::ontology::Scene* const scene = new yli::ontology::Scene(universe, scene_struct, &world->parent_of_scenes);
    scene->set_name(scene_name);

    const std::string camera_name = "bar";
    yli::ontology::Camera* const camera = new yli::ontology::Camera(universe, yli::ontology::CameraStruct(), &scene->parent_of_cameras);
    camera->set_name(camera_name);

    ASSERT_EQ(universe->get_active_scene(), nullptr);
    ASSERT_EQ(scene->get_active_camera(), nullptr);

    const std::vector<std::string> activate_scene_command_parameters { scene_name };
    universe->activate(console, universe, activate_scene_command_parameters);
    ASSERT_EQ(universe->get_active_scene(), scene);
    ASSERT_EQ(scene->get_active_camera(), nullptr);

    const std::vector<std::string> activate_camera_command_parameters { camera_name };
    universe->activate(console, universe, activate_camera_command_parameters);
    ASSERT_EQ(universe->get_active_scene(), scene);
    ASSERT_EQ(scene->get_active_camera(), camera);
}

// Public AngelScript-related callbacks.
