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
#include "code/ylikuutio/ontology/any_value_entity.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/universe_struct.hpp"

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string, std::getline
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

TEST(any_value_entity_must_be_created_appropriately, headless_universe_bool_true)
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

    std::vector<std::string> command_parameters = { any_value_entity_name, any_value_entity_type, any_value_entity_value };
    universe->create_AnyValueEntity(console, universe, command_parameters);
    ASSERT_TRUE(universe->is_entity(any_value_entity_name));

    yli::ontology::Entity* const entity = universe->get_entity(any_value_entity_name);
    ASSERT_NE(entity, nullptr);

    yli::ontology::AnyValueEntity* const any_value_entity = dynamic_cast<yli::ontology::AnyValueEntity*>(entity);
    ASSERT_NE(any_value_entity, nullptr);

    yli::common::AnyValue* any_value = any_value_entity;
    ASSERT_EQ(any_value->type, yli::common::Datatype::BOOL);
    ASSERT_EQ(any_value->bool_value, true);

    ASSERT_EQ(any_value_entity->type, yli::common::Datatype::BOOL);
    ASSERT_EQ(any_value_entity->bool_value, true);
}

TEST(any_value_entity_must_be_created_appropriately, headless_universe_bool_false)
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

    std::vector<std::string> command_parameters = { any_value_entity_name, any_value_entity_type, any_value_entity_value };
    universe->create_AnyValueEntity(console, universe, command_parameters);
    ASSERT_TRUE(universe->is_entity(any_value_entity_name));

    yli::ontology::Entity* const entity = universe->get_entity(any_value_entity_name);
    ASSERT_NE(entity, nullptr);

    yli::ontology::AnyValueEntity* const any_value_entity = dynamic_cast<yli::ontology::AnyValueEntity*>(entity);
    ASSERT_NE(any_value_entity, nullptr);

    yli::common::AnyValue* any_value = any_value_entity;
    ASSERT_EQ(any_value->type, yli::common::Datatype::BOOL);
    ASSERT_EQ(any_value->bool_value, false);

    ASSERT_EQ(any_value_entity->type, yli::common::Datatype::BOOL);
    ASSERT_EQ(any_value_entity->bool_value, false);
}

TEST(any_value_entity_must_be_created_appropriately, headless_universe_float_0)
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

    std::vector<std::string> command_parameters = { any_value_entity_name, any_value_entity_type, any_value_entity_value };
    universe->create_AnyValueEntity(console, universe, command_parameters);
    ASSERT_TRUE(universe->is_entity(any_value_entity_name));

    yli::ontology::Entity* const entity = universe->get_entity(any_value_entity_name);
    ASSERT_NE(entity, nullptr);

    yli::ontology::AnyValueEntity* const any_value_entity = dynamic_cast<yli::ontology::AnyValueEntity*>(entity);
    ASSERT_NE(any_value_entity, nullptr);

    yli::common::AnyValue* any_value = any_value_entity;
    ASSERT_EQ(any_value->type, yli::common::Datatype::FLOAT);
    ASSERT_EQ(any_value->float_value, 0.0f);

    ASSERT_EQ(any_value_entity->type, yli::common::Datatype::FLOAT);
    ASSERT_EQ(any_value_entity->float_value, 0.0f);
}

TEST(any_value_entity_must_be_created_appropriately, headless_universe_float_0_0)
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

    std::vector<std::string> command_parameters = { any_value_entity_name, any_value_entity_type, any_value_entity_value };
    universe->create_AnyValueEntity(console, universe, command_parameters);
    ASSERT_TRUE(universe->is_entity(any_value_entity_name));

    yli::ontology::Entity* const entity = universe->get_entity(any_value_entity_name);
    ASSERT_NE(entity, nullptr);

    yli::ontology::AnyValueEntity* const any_value_entity = dynamic_cast<yli::ontology::AnyValueEntity*>(entity);
    ASSERT_NE(any_value_entity, nullptr);

    yli::common::AnyValue* any_value = any_value_entity;
    ASSERT_EQ(any_value->type, yli::common::Datatype::FLOAT);
    ASSERT_EQ(any_value->float_value, 0.0f);

    ASSERT_EQ(any_value_entity->type, yli::common::Datatype::FLOAT);
    ASSERT_EQ(any_value_entity->float_value, 0.0f);
}

TEST(any_value_entity_must_be_created_appropriately, headless_universe_float_pi)
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

    std::vector<std::string> command_parameters = { any_value_entity_name, any_value_entity_type, any_value_entity_value };
    universe->create_AnyValueEntity(console, universe, command_parameters);
    ASSERT_TRUE(universe->is_entity(any_value_entity_name));

    yli::ontology::Entity* const entity = universe->get_entity(any_value_entity_name);
    ASSERT_NE(entity, nullptr);

    yli::ontology::AnyValueEntity* const any_value_entity = dynamic_cast<yli::ontology::AnyValueEntity*>(entity);
    ASSERT_NE(any_value_entity, nullptr);

    yli::common::AnyValue* any_value = any_value_entity;
    ASSERT_EQ(any_value->type, yli::common::Datatype::FLOAT);
    ASSERT_GT(any_value->float_value, 3.141592f);
    ASSERT_LT(any_value->float_value, 3.141593f);

    ASSERT_EQ(any_value_entity->type, yli::common::Datatype::FLOAT);
    ASSERT_GT(any_value_entity->float_value, 3.141592f);
    ASSERT_LT(any_value_entity->float_value, 3.141593f);
}

TEST(any_value_entity_must_be_created_appropriately, headless_universe_double_0)
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

    std::vector<std::string> command_parameters = { any_value_entity_name, any_value_entity_type, any_value_entity_value };
    universe->create_AnyValueEntity(console, universe, command_parameters);
    ASSERT_TRUE(universe->is_entity(any_value_entity_name));

    yli::ontology::Entity* const entity = universe->get_entity(any_value_entity_name);
    ASSERT_NE(entity, nullptr);

    yli::ontology::AnyValueEntity* const any_value_entity = dynamic_cast<yli::ontology::AnyValueEntity*>(entity);
    ASSERT_NE(any_value_entity, nullptr);

    yli::common::AnyValue* any_value = any_value_entity;
    ASSERT_EQ(any_value->type, yli::common::Datatype::DOUBLE);
    ASSERT_EQ(any_value->double_value, 0.0f);

    ASSERT_EQ(any_value_entity->type, yli::common::Datatype::DOUBLE);
    ASSERT_EQ(any_value_entity->double_value, 0.0f);
}

TEST(any_value_entity_must_be_created_appropriately, headless_universe_double_0_0)
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

    std::vector<std::string> command_parameters = { any_value_entity_name, any_value_entity_type, any_value_entity_value };
    universe->create_AnyValueEntity(console, universe, command_parameters);
    ASSERT_TRUE(universe->is_entity(any_value_entity_name));

    yli::ontology::Entity* const entity = universe->get_entity(any_value_entity_name);
    ASSERT_NE(entity, nullptr);

    yli::ontology::AnyValueEntity* const any_value_entity = dynamic_cast<yli::ontology::AnyValueEntity*>(entity);
    ASSERT_NE(any_value_entity, nullptr);

    yli::common::AnyValue* any_value = any_value_entity;
    ASSERT_EQ(any_value->type, yli::common::Datatype::DOUBLE);
    ASSERT_EQ(any_value->double_value, 0.0f);

    ASSERT_EQ(any_value_entity->type, yli::common::Datatype::DOUBLE);
    ASSERT_EQ(any_value_entity->double_value, 0.0f);
}

TEST(any_value_entity_must_be_created_appropriately, headless_universe_double_pi)
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

    std::vector<std::string> command_parameters = { any_value_entity_name, any_value_entity_type, any_value_entity_value };
    universe->create_AnyValueEntity(console, universe, command_parameters);
    ASSERT_TRUE(universe->is_entity(any_value_entity_name));

    yli::ontology::Entity* const entity = universe->get_entity(any_value_entity_name);
    ASSERT_NE(entity, nullptr);

    yli::ontology::AnyValueEntity* const any_value_entity = dynamic_cast<yli::ontology::AnyValueEntity*>(entity);
    ASSERT_NE(any_value_entity, nullptr);

    yli::common::AnyValue* any_value = any_value_entity;
    ASSERT_EQ(any_value->type, yli::common::Datatype::DOUBLE);
    ASSERT_EQ(any_value->double_value, 3.1415927);

    ASSERT_EQ(any_value_entity->type, yli::common::Datatype::DOUBLE);
    ASSERT_EQ(any_value_entity->double_value, 3.1415927);
}

TEST(any_value_entity_must_be_created_appropriately, headless_universe_int32_t_0)
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

    std::vector<std::string> command_parameters = { any_value_entity_name, any_value_entity_type, any_value_entity_value };
    universe->create_AnyValueEntity(console, universe, command_parameters);
    ASSERT_TRUE(universe->is_entity(any_value_entity_name));

    yli::ontology::Entity* const entity = universe->get_entity(any_value_entity_name);
    ASSERT_NE(entity, nullptr);

    yli::ontology::AnyValueEntity* const any_value_entity = dynamic_cast<yli::ontology::AnyValueEntity*>(entity);
    ASSERT_NE(any_value_entity, nullptr);

    yli::common::AnyValue* any_value = any_value_entity;
    ASSERT_EQ(any_value->type, yli::common::Datatype::INT32_T);
    ASSERT_EQ(any_value->int32_t_value, 0);

    ASSERT_EQ(any_value_entity->type, yli::common::Datatype::INT32_T);
    ASSERT_EQ(any_value_entity->int32_t_value, 0);
}

TEST(any_value_entity_must_be_created_appropriately, headless_universe_int32_t_plus_1)
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

    std::vector<std::string> command_parameters = { any_value_entity_name, any_value_entity_type, any_value_entity_value };
    universe->create_AnyValueEntity(console, universe, command_parameters);
    ASSERT_TRUE(universe->is_entity(any_value_entity_name));

    yli::ontology::Entity* const entity = universe->get_entity(any_value_entity_name);
    ASSERT_NE(entity, nullptr);

    yli::ontology::AnyValueEntity* const any_value_entity = dynamic_cast<yli::ontology::AnyValueEntity*>(entity);
    ASSERT_NE(any_value_entity, nullptr);

    yli::common::AnyValue* any_value = any_value_entity;
    ASSERT_EQ(any_value->type, yli::common::Datatype::INT32_T);
    ASSERT_EQ(any_value->int32_t_value, 1);

    ASSERT_EQ(any_value_entity->type, yli::common::Datatype::INT32_T);
    ASSERT_EQ(any_value_entity->int32_t_value, 1);
}

TEST(any_value_entity_must_be_created_appropriately, headless_universe_int32_t_minus_1)
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

    std::vector<std::string> command_parameters = { any_value_entity_name, any_value_entity_type, any_value_entity_value };
    universe->create_AnyValueEntity(console, universe, command_parameters);
    ASSERT_TRUE(universe->is_entity(any_value_entity_name));

    yli::ontology::Entity* const entity = universe->get_entity(any_value_entity_name);
    ASSERT_NE(entity, nullptr);

    yli::ontology::AnyValueEntity* const any_value_entity = dynamic_cast<yli::ontology::AnyValueEntity*>(entity);
    ASSERT_NE(any_value_entity, nullptr);

    yli::common::AnyValue* any_value = any_value_entity;
    ASSERT_EQ(any_value->type, yli::common::Datatype::INT32_T);
    ASSERT_EQ(any_value->int32_t_value, -1);

    ASSERT_EQ(any_value_entity->type, yli::common::Datatype::INT32_T);
    ASSERT_EQ(any_value_entity->int32_t_value, -1);
}

TEST(any_value_entity_must_be_created_appropriately, headless_universe_int32_t_max)
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

    std::vector<std::string> command_parameters = { any_value_entity_name, any_value_entity_type, any_value_entity_value };
    universe->create_AnyValueEntity(console, universe, command_parameters);
    ASSERT_TRUE(universe->is_entity(any_value_entity_name));

    yli::ontology::Entity* const entity = universe->get_entity(any_value_entity_name);
    ASSERT_NE(entity, nullptr);

    yli::ontology::AnyValueEntity* const any_value_entity = dynamic_cast<yli::ontology::AnyValueEntity*>(entity);
    ASSERT_NE(any_value_entity, nullptr);

    yli::common::AnyValue* any_value = any_value_entity;
    ASSERT_EQ(any_value->type, yli::common::Datatype::INT32_T);
    ASSERT_EQ(any_value->int32_t_value, 2147483647);

    ASSERT_EQ(any_value_entity->type, yli::common::Datatype::INT32_T);
    ASSERT_EQ(any_value_entity->int32_t_value, 2147483647);
}

TEST(any_value_entity_must_be_created_appropriately, headless_universe_int32_t_min)
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

    std::vector<std::string> command_parameters = { any_value_entity_name, any_value_entity_type, any_value_entity_value };
    universe->create_AnyValueEntity(console, universe, command_parameters);
    ASSERT_TRUE(universe->is_entity(any_value_entity_name));

    yli::ontology::Entity* const entity = universe->get_entity(any_value_entity_name);
    ASSERT_NE(entity, nullptr);

    yli::ontology::AnyValueEntity* const any_value_entity = dynamic_cast<yli::ontology::AnyValueEntity*>(entity);
    ASSERT_NE(any_value_entity, nullptr);

    yli::common::AnyValue* any_value = any_value_entity;
    ASSERT_EQ(any_value->type, yli::common::Datatype::INT32_T);
    ASSERT_EQ(any_value->int32_t_value, -2147483648);

    ASSERT_EQ(any_value_entity->type, yli::common::Datatype::INT32_T);
    ASSERT_EQ(any_value_entity->int32_t_value, -2147483648);
}

TEST(any_value_entity_must_be_created_appropriately, headless_universe_uint32_t_0)
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

    std::vector<std::string> command_parameters = { any_value_entity_name, any_value_entity_type, any_value_entity_value };
    universe->create_AnyValueEntity(console, universe, command_parameters);
    ASSERT_TRUE(universe->is_entity(any_value_entity_name));

    yli::ontology::Entity* const entity = universe->get_entity(any_value_entity_name);
    ASSERT_NE(entity, nullptr);

    yli::ontology::AnyValueEntity* const any_value_entity = dynamic_cast<yli::ontology::AnyValueEntity*>(entity);
    ASSERT_NE(any_value_entity, nullptr);

    yli::common::AnyValue* any_value = any_value_entity;
    ASSERT_EQ(any_value->type, yli::common::Datatype::UINT32_T);
    ASSERT_EQ(any_value->uint32_t_value, 0);

    ASSERT_EQ(any_value_entity->type, yli::common::Datatype::UINT32_T);
    ASSERT_EQ(any_value_entity->uint32_t_value, 0);
}

TEST(any_value_entity_must_be_created_appropriately, headless_universe_uint32_t_1)
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

    std::vector<std::string> command_parameters = { any_value_entity_name, any_value_entity_type, any_value_entity_value };
    universe->create_AnyValueEntity(console, universe, command_parameters);
    ASSERT_TRUE(universe->is_entity(any_value_entity_name));

    yli::ontology::Entity* const entity = universe->get_entity(any_value_entity_name);
    ASSERT_NE(entity, nullptr);

    yli::ontology::AnyValueEntity* const any_value_entity = dynamic_cast<yli::ontology::AnyValueEntity*>(entity);
    ASSERT_NE(any_value_entity, nullptr);

    yli::common::AnyValue* any_value = any_value_entity;
    ASSERT_EQ(any_value->type, yli::common::Datatype::UINT32_T);
    ASSERT_EQ(any_value->uint32_t_value, 1);

    ASSERT_EQ(any_value_entity->type, yli::common::Datatype::UINT32_T);
    ASSERT_EQ(any_value_entity->uint32_t_value, 1);
}

TEST(any_value_entity_must_be_created_appropriately, headless_universe_uint32_t_max)
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

    std::vector<std::string> command_parameters = { any_value_entity_name, any_value_entity_type, any_value_entity_value };
    universe->create_AnyValueEntity(console, universe, command_parameters);
    ASSERT_TRUE(universe->is_entity(any_value_entity_name));

    yli::ontology::Entity* const entity = universe->get_entity(any_value_entity_name);
    ASSERT_NE(entity, nullptr);

    yli::ontology::AnyValueEntity* const any_value_entity = dynamic_cast<yli::ontology::AnyValueEntity*>(entity);
    ASSERT_NE(any_value_entity, nullptr);

    yli::common::AnyValue* any_value = any_value_entity;
    ASSERT_EQ(any_value->type, yli::common::Datatype::UINT32_T);
    ASSERT_EQ(any_value->uint32_t_value, 4294967295);

    ASSERT_EQ(any_value_entity->type, yli::common::Datatype::UINT32_T);
    ASSERT_EQ(any_value_entity->uint32_t_value, 4294967295);
}
