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
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/ontology/variable.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/movable_variable_activation.hpp"
#include "code/ylikuutio/ontology/movable_variable_read.hpp"
#include "code/ylikuutio/ontology/variable_struct.hpp"
#include "code/ylikuutio/ontology/universe_struct.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <limits>   // std::numeric_limits
#include <memory>   // std::make_shared, std::shared_ptr
#include <stdint.h> // uint32_t etc.
#include <variant>  // std::holds_alternative, std::variant

TEST(is_variable_must_return_false_for_nonexisting_variables, headless_universe)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    ASSERT_FALSE(universe->has_variable("foo"));
}

TEST(get_must_return_nullptr_for_nonexisting_variables, headless_universe)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);
    ASSERT_EQ(universe->get("foo"), nullptr);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_unnamed_variable_bool_true_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    bool bool_true = true;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(bool_true));
    universe->create_variable(variable_struct);
    ASSERT_FALSE(universe->has_variable("foo"));
    yli::ontology::Variable* const variable = universe->get("foo");
    ASSERT_EQ(universe->get("foo"), nullptr);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_bool_true_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    bool bool_true = true;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(bool_true));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);
    ASSERT_TRUE(universe->has_variable("foo"));
    ASSERT_NE(universe->get("foo"), nullptr);
    ASSERT_FALSE(universe->has_variable("bar"));
    ASSERT_EQ(universe->get("bar"), nullptr);

    yli::ontology::Variable* const variable = universe->get("foo");
    ASSERT_NE(variable, nullptr);
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<bool>(variable_value->data));
    ASSERT_TRUE(std::get<bool>(variable_value->data));
}

TEST(variable_must_be_initialized_appropriately, headless_universe_unnamed_variable_bool_false_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    bool bool_false = false;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(bool_false));
    universe->create_variable(variable_struct);
    ASSERT_FALSE(universe->has_variable("foo"));
    yli::ontology::Variable* const variable = universe->get("foo");
    ASSERT_EQ(universe->get("foo"), nullptr);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_bool_false_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    bool bool_false = false;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(bool_false));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);
    ASSERT_TRUE(universe->has_variable("foo"));
    ASSERT_NE(universe->get("foo"), nullptr);
    ASSERT_FALSE(universe->has_variable("bar"));
    ASSERT_EQ(universe->get("bar"), nullptr);

    yli::ontology::Variable* const variable = universe->get("foo");
    ASSERT_NE(variable, nullptr);
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<bool>(variable_value->data));
    ASSERT_FALSE(std::get<bool>(variable_value->data));
}

TEST(variable_must_be_initialized_appropriately, headless_universe_unnamed_variable_char_lowercase_a_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    char char_lowercase_a = 'a';
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(char_lowercase_a));
    universe->create_variable(variable_struct);
    ASSERT_FALSE(universe->has_variable("foo"));
    yli::ontology::Variable* const variable = universe->get("foo");
    ASSERT_EQ(universe->get("foo"), nullptr);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_char_lowercase_a_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    char char_lowercase_a = 'a';
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(char_lowercase_a));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);
    ASSERT_TRUE(universe->has_variable("foo"));
    ASSERT_NE(universe->get("foo"), nullptr);
    ASSERT_FALSE(universe->has_variable("bar"));
    ASSERT_EQ(universe->get("bar"), nullptr);

    yli::ontology::Variable* const variable = universe->get("foo");
    ASSERT_NE(variable, nullptr);
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<char>(variable_value->data));
    ASSERT_EQ(std::get<char>(variable_value->data), 'a');
}

TEST(variable_must_be_initialized_appropriately, headless_universe_unnamed_variable_char_lowercase_b_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    char char_lowercase_b = 'b';
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(char_lowercase_b));
    universe->create_variable(variable_struct);
    ASSERT_FALSE(universe->has_variable("foo"));
    yli::ontology::Variable* const variable = universe->get("foo");
    ASSERT_EQ(universe->get("foo"), nullptr);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_char_lowercase_b_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    char char_lowercase_b = 'b';
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(char_lowercase_b));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);
    ASSERT_TRUE(universe->has_variable("foo"));
    ASSERT_NE(universe->get("foo"), nullptr);
    ASSERT_FALSE(universe->has_variable("bar"));
    ASSERT_EQ(universe->get("bar"), nullptr);

    yli::ontology::Variable* const variable = universe->get("foo");
    ASSERT_NE(variable, nullptr);
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<char>(variable_value->data));
    ASSERT_EQ(std::get<char>(variable_value->data), 'b');
}

TEST(variable_must_be_initialized_appropriately, headless_universe_unnamed_variable_char_space_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    char char_space = ' ';
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(char_space));
    universe->create_variable(variable_struct);
    ASSERT_FALSE(universe->has_variable("foo"));
    yli::ontology::Variable* const variable = universe->get("foo");
    ASSERT_EQ(universe->get("foo"), nullptr);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_char_space_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    char char_space = ' ';
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(char_space));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);
    ASSERT_TRUE(universe->has_variable("foo"));
    ASSERT_NE(universe->get("foo"), nullptr);
    ASSERT_FALSE(universe->has_variable("bar"));
    ASSERT_EQ(universe->get("bar"), nullptr);

    yli::ontology::Variable* const variable = universe->get("foo");
    ASSERT_NE(variable, nullptr);
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<char>(variable_value->data));
    ASSERT_EQ(std::get<char>(variable_value->data), ' ');
}

TEST(variable_must_be_initialized_appropriately, headless_universe_unnamed_variable_char_newline_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    char char_newline = '\n';
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(char_newline));
    universe->create_variable(variable_struct);
    ASSERT_FALSE(universe->has_variable("foo"));
    yli::ontology::Variable* const variable = universe->get("foo");
    ASSERT_EQ(universe->get("foo"), nullptr);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_char_newline_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    char char_newline = '\n';
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(char_newline));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);
    ASSERT_TRUE(universe->has_variable("foo"));
    ASSERT_NE(universe->get("foo"), nullptr);
    ASSERT_FALSE(universe->has_variable("bar"));
    ASSERT_EQ(universe->get("bar"), nullptr);

    yli::ontology::Variable* const variable = universe->get("foo");
    ASSERT_NE(variable, nullptr);
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<char>(variable_value->data));
    ASSERT_EQ(std::get<char>(variable_value->data), '\n');
}

TEST(variable_must_be_initialized_appropriately, headless_universe_unnamed_variable_float_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    float float_zero = 0.0f;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(float_zero));
    universe->create_variable(variable_struct);
    ASSERT_FALSE(universe->has_variable("foo"));
    yli::ontology::Variable* const variable = universe->get("foo");
    ASSERT_EQ(universe->get("foo"), nullptr);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_float_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    float float_zero = 0.0f;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(float_zero));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);
    ASSERT_TRUE(universe->has_variable("foo"));
    ASSERT_NE(universe->get("foo"), nullptr);
    ASSERT_FALSE(universe->has_variable("bar"));
    ASSERT_EQ(universe->get("bar"), nullptr);

    yli::ontology::Variable* const variable = universe->get("foo");
    ASSERT_NE(variable, nullptr);
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(variable_value->data));
    ASSERT_EQ(std::get<float>(variable_value->data), 0.0f);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_float_positive_infinity_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    float float_positive_infinity = std::numeric_limits<float>::infinity();
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(float_positive_infinity));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);
    ASSERT_TRUE(universe->has_variable("foo"));
    ASSERT_NE(universe->get("foo"), nullptr);
    ASSERT_FALSE(universe->has_variable("bar"));
    ASSERT_EQ(universe->get("bar"), nullptr);

    yli::ontology::Variable* const variable = universe->get("foo");
    ASSERT_NE(variable, nullptr);
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(variable_value->data));
    ASSERT_EQ(std::get<float>(variable_value->data), std::numeric_limits<float>::infinity());
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_float_negative_infinity_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    float float_negative_infinity = -1.0f * std::numeric_limits<float>::infinity();
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(float_negative_infinity));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);
    ASSERT_TRUE(universe->has_variable("foo"));
    ASSERT_NE(universe->get("foo"), nullptr);
    ASSERT_FALSE(universe->has_variable("bar"));
    ASSERT_EQ(universe->get("bar"), nullptr);

    yli::ontology::Variable* const variable = universe->get("foo");
    ASSERT_NE(variable, nullptr);
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(variable_value->data));
    ASSERT_EQ(std::get<float>(variable_value->data), -1.0f * std::numeric_limits<float>::infinity());
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_float_nan_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    float float_nan = NAN;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(float_nan));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);
    ASSERT_TRUE(universe->has_variable("foo"));
    ASSERT_NE(universe->get("foo"), nullptr);
    ASSERT_FALSE(universe->has_variable("bar"));
    ASSERT_EQ(universe->get("bar"), nullptr);

    yli::ontology::Variable* const variable = universe->get("foo");
    ASSERT_NE(variable, nullptr);
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(variable_value->data));
    ASSERT_TRUE(std::isnan(std::get<float>(variable_value->data)));
}

TEST(variable_must_be_initialized_appropriately, headless_universe_unnamed_variable_double_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    double double_zero = 0.0;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(double_zero));
    universe->create_variable(variable_struct);
    ASSERT_FALSE(universe->has_variable("foo"));
    yli::ontology::Variable* const variable = universe->get("foo");
    ASSERT_EQ(universe->get("foo"), nullptr);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_double_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    double double_zero = 0.0;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(double_zero));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);
    ASSERT_TRUE(universe->has_variable("foo"));
    ASSERT_NE(universe->get("foo"), nullptr);
    ASSERT_FALSE(universe->has_variable("bar"));
    ASSERT_EQ(universe->get("bar"), nullptr);

    yli::ontology::Variable* const variable = universe->get("foo");
    ASSERT_NE(variable, nullptr);
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<double>(variable_value->data));
    ASSERT_EQ(std::get<double>(variable_value->data), 0.0);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_double_positive_infinity_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    double double_positive_infinity = std::numeric_limits<double>::infinity();
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(double_positive_infinity));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);
    ASSERT_TRUE(universe->has_variable("foo"));
    ASSERT_NE(universe->get("foo"), nullptr);
    ASSERT_FALSE(universe->has_variable("bar"));
    ASSERT_EQ(universe->get("bar"), nullptr);

    yli::ontology::Variable* const variable = universe->get("foo");
    ASSERT_NE(variable, nullptr);
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<double>(variable_value->data));
    ASSERT_EQ(std::get<double>(variable_value->data), std::numeric_limits<double>::infinity());
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_double_negative_infinity_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    double double_negative_infinity = -1.0 * std::numeric_limits<double>::infinity();
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(double_negative_infinity));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);
    ASSERT_TRUE(universe->has_variable("foo"));
    ASSERT_NE(universe->get("foo"), nullptr);
    ASSERT_FALSE(universe->has_variable("bar"));
    ASSERT_EQ(universe->get("bar"), nullptr);

    yli::ontology::Variable* const variable = universe->get("foo");
    ASSERT_NE(variable, nullptr);
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<double>(variable_value->data));
    ASSERT_EQ(std::get<double>(variable_value->data), -1.0 * std::numeric_limits<double>::infinity());
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_double_nan_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    double double_nan = NAN;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(double_nan));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);
    ASSERT_TRUE(universe->has_variable("foo"));
    ASSERT_NE(universe->get("foo"), nullptr);
    ASSERT_FALSE(universe->has_variable("bar"));
    ASSERT_EQ(universe->get("bar"), nullptr);

    yli::ontology::Variable* const variable = universe->get("foo");
    ASSERT_NE(variable, nullptr);
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<double>(variable_value->data));
    ASSERT_TRUE(std::isnan(std::get<double>(variable_value->data)));
}

TEST(variable_must_be_initialized_appropriately, headless_universe_unnamed_variable_int32_t_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    int32_t int32_t_zero = 0;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(int32_t_zero));
    universe->create_variable(variable_struct);
    ASSERT_FALSE(universe->has_variable("foo"));
    yli::ontology::Variable* const variable = universe->get("foo");
    ASSERT_EQ(universe->get("foo"), nullptr);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_int32_t_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    int32_t int32_t_zero = 0;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(int32_t_zero));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);
    ASSERT_TRUE(universe->has_variable("foo"));
    ASSERT_NE(universe->get("foo"), nullptr);
    ASSERT_FALSE(universe->has_variable("bar"));
    ASSERT_EQ(universe->get("bar"), nullptr);

    yli::ontology::Variable* const variable = universe->get("foo");
    ASSERT_NE(variable, nullptr);
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<int32_t>(variable_value->data));
    ASSERT_EQ(std::get<int32_t>(variable_value->data), 0);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_unnamed_variable_int32_t_plus_1_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    int32_t int32_t_plus_1 = 1;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(int32_t_plus_1));
    universe->create_variable(variable_struct);
    ASSERT_FALSE(universe->has_variable("foo"));
    yli::ontology::Variable* const variable = universe->get("foo");
    ASSERT_EQ(universe->get("foo"), nullptr);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_int32_t_plus_1_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    int32_t int32_t_plus_1 = 1;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(int32_t_plus_1));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);
    ASSERT_TRUE(universe->has_variable("foo"));
    ASSERT_NE(universe->get("foo"), nullptr);
    ASSERT_FALSE(universe->has_variable("bar"));
    ASSERT_EQ(universe->get("bar"), nullptr);

    yli::ontology::Variable* const variable = universe->get("foo");
    ASSERT_NE(variable, nullptr);
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<int32_t>(variable_value->data));
    ASSERT_EQ(std::get<int32_t>(variable_value->data), 1);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_unnamed_variable_int32_t_minus_1_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    int32_t int32_t_minus_1 = -1;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(int32_t_minus_1));
    universe->create_variable(variable_struct);
    ASSERT_FALSE(universe->has_variable("foo"));
    yli::ontology::Variable* const variable = universe->get("foo");
    ASSERT_EQ(universe->get("foo"), nullptr);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_int32_t_minus_1_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    int32_t int32_t_minus_1 = -1;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(int32_t_minus_1));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);
    ASSERT_TRUE(universe->has_variable("foo"));
    ASSERT_NE(universe->get("foo"), nullptr);
    ASSERT_FALSE(universe->has_variable("bar"));
    ASSERT_EQ(universe->get("bar"), nullptr);

    yli::ontology::Variable* const variable = universe->get("foo");
    ASSERT_NE(variable, nullptr);
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<int32_t>(variable_value->data));
    ASSERT_EQ(std::get<int32_t>(variable_value->data), -1);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_unnamed_variable_int32_t_max_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    int32_t int32_t_max = std::numeric_limits<int32_t>::max();
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(int32_t_max));
    universe->create_variable(variable_struct);
    ASSERT_FALSE(universe->has_variable("foo"));
    yli::ontology::Variable* const variable = universe->get("foo");
    ASSERT_EQ(universe->get("foo"), nullptr);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_int32_t_max_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    int32_t int32_t_max = std::numeric_limits<int32_t>::max();
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(int32_t_max));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);
    ASSERT_TRUE(universe->has_variable("foo"));
    ASSERT_NE(universe->get("foo"), nullptr);
    ASSERT_FALSE(universe->has_variable("bar"));
    ASSERT_EQ(universe->get("bar"), nullptr);

    yli::ontology::Variable* const variable = universe->get("foo");
    ASSERT_NE(variable, nullptr);
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<int32_t>(variable_value->data));
    ASSERT_EQ(std::get<int32_t>(variable_value->data), std::numeric_limits<int32_t>::max());
}

TEST(variable_must_be_initialized_appropriately, headless_universe_unnamed_variable_int32_t_min_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    int32_t int32_t_min = std::numeric_limits<int32_t>::min();
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(int32_t_min));
    universe->create_variable(variable_struct);
    ASSERT_FALSE(universe->has_variable("foo"));
    yli::ontology::Variable* const variable = universe->get("foo");
    ASSERT_EQ(universe->get("foo"), nullptr);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_int32_t_min_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    int32_t int32_t_min = std::numeric_limits<int32_t>::min();
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(int32_t_min));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);
    ASSERT_TRUE(universe->has_variable("foo"));
    ASSERT_NE(universe->get("foo"), nullptr);
    ASSERT_FALSE(universe->has_variable("bar"));
    ASSERT_EQ(universe->get("bar"), nullptr);

    yli::ontology::Variable* const variable = universe->get("foo");
    ASSERT_NE(variable, nullptr);
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<int32_t>(variable_value->data));
    ASSERT_EQ(std::get<int32_t>(variable_value->data), std::numeric_limits<int32_t>::min());
}

TEST(variable_must_be_initialized_appropriately, headless_universe_unnamed_variable_uint32_t_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    uint32_t uint32_t_zero = 0;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(uint32_t_zero));
    universe->create_variable(variable_struct);
    ASSERT_FALSE(universe->has_variable("foo"));
    yli::ontology::Variable* const variable = universe->get("foo");
    ASSERT_EQ(universe->get("foo"), nullptr);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_uint32_t_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    uint32_t uint32_t_zero = 0;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(uint32_t_zero));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);
    ASSERT_TRUE(universe->has_variable("foo"));
    ASSERT_NE(universe->get("foo"), nullptr);
    ASSERT_FALSE(universe->has_variable("bar"));
    ASSERT_EQ(universe->get("bar"), nullptr);

    yli::ontology::Variable* const variable = universe->get("foo");
    ASSERT_NE(variable, nullptr);
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<uint32_t>(variable_value->data));
    ASSERT_EQ(std::get<uint32_t>(variable_value->data), 0);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_unnamed_variable_uint32_t_plus_1_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    uint32_t uint32_t_plus_1 = 1;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(uint32_t_plus_1));
    universe->create_variable(variable_struct);
    ASSERT_FALSE(universe->has_variable("foo"));
    yli::ontology::Variable* const variable = universe->get("foo");
    ASSERT_EQ(universe->get("foo"), nullptr);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_uint32_t_plus_1_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    uint32_t uint32_t_plus_1 = 1;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(uint32_t_plus_1));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);
    ASSERT_TRUE(universe->has_variable("foo"));
    ASSERT_NE(universe->get("foo"), nullptr);
    ASSERT_FALSE(universe->has_variable("bar"));
    ASSERT_EQ(universe->get("bar"), nullptr);

    yli::ontology::Variable* const variable = universe->get("foo");
    ASSERT_NE(variable, nullptr);
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<uint32_t>(variable_value->data));
    ASSERT_EQ(std::get<uint32_t>(variable_value->data), 1);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_unnamed_variable_uint32_t_max_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    uint32_t uint32_t_max = std::numeric_limits<uint32_t>::max();
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(uint32_t_max));
    universe->create_variable(variable_struct);
    ASSERT_FALSE(universe->has_variable("foo"));
    yli::ontology::Variable* const variable = universe->get("foo");
    ASSERT_EQ(universe->get("foo"), nullptr);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_uint32_t_max_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    uint32_t uint32_t_max = std::numeric_limits<uint32_t>::max();
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(uint32_t_max));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);
    ASSERT_TRUE(universe->has_variable("foo"));
    ASSERT_NE(universe->get("foo"), nullptr);
    ASSERT_FALSE(universe->has_variable("bar"));
    ASSERT_EQ(universe->get("bar"), nullptr);

    yli::ontology::Variable* const variable = universe->get("foo");
    ASSERT_NE(variable, nullptr);
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<uint32_t>(variable_value->data));
    ASSERT_EQ(std::get<uint32_t>(variable_value->data), std::numeric_limits<uint32_t>::max());
}

TEST(variable_must_be_initialized_appropriately, headless_universe_variable_universe_x_float_1234_dot_25_with_activate_callback_and_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    float x = 1234.25f;
    yli::ontology::VariableStruct x_variable_struct(std::make_shared<yli::data::AnyValue>(x));
    x_variable_struct.local_name = "x";
    x_variable_struct.activate_callback = &yli::ontology::activate_x;
    x_variable_struct.read_callback = &yli::ontology::read_x;
    x_variable_struct.should_ylikuutio_call_activate_callback_now = true;
    ASSERT_EQ(universe->get("x"), nullptr);
    universe->create_variable(x_variable_struct);

    ASSERT_NE(universe->get("x"), nullptr);
    yli::ontology::Variable* x_variable = universe->get("x");
    ASSERT_NE(x_variable, nullptr);

    std::shared_ptr<yli::data::AnyValue> x_value = x_variable->get();
    ASSERT_NE(x_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(x_value->data));
    ASSERT_EQ(std::get<float>(x_value->data), 1234.25f);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_variable_universe_y_float_1234_dot_25_with_activate_callback_and_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    float y = 1234.25f;
    yli::ontology::VariableStruct y_variable_struct(std::make_shared<yli::data::AnyValue>(y));
    y_variable_struct.local_name = "y";
    y_variable_struct.activate_callback = &yli::ontology::activate_y;
    y_variable_struct.read_callback = &yli::ontology::read_y;
    y_variable_struct.should_ylikuutio_call_activate_callback_now = true;
    ASSERT_EQ(universe->get("y"), nullptr);
    universe->create_variable(y_variable_struct);

    ASSERT_NE(universe->get("y"), nullptr);
    yli::ontology::Variable* y_variable = universe->get("y");
    ASSERT_NE(y_variable, nullptr);

    std::shared_ptr<yli::data::AnyValue> y_value = y_variable->get();
    ASSERT_NE(y_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(y_value->data));
    ASSERT_EQ(std::get<float>(y_value->data), 1234.25f);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_variable_universe_z_float_1234_dot_25_with_activate_callback_and_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    float z = 1234.25f;
    yli::ontology::VariableStruct z_variable_struct(std::make_shared<yli::data::AnyValue>(z));
    z_variable_struct.local_name = "z";
    z_variable_struct.activate_callback = &yli::ontology::activate_z;
    z_variable_struct.read_callback = &yli::ontology::read_z;
    z_variable_struct.should_ylikuutio_call_activate_callback_now = true;
    ASSERT_EQ(universe->get("z"), nullptr);
    universe->create_variable(z_variable_struct);

    ASSERT_NE(universe->get("z"), nullptr);
    yli::ontology::Variable* z_variable = universe->get("z");
    ASSERT_NE(z_variable, nullptr);

    std::shared_ptr<yli::data::AnyValue> z_value = z_variable->get();
    ASSERT_NE(z_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(z_value->data));
    ASSERT_EQ(std::get<float>(z_value->data), 1234.25f);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_variable_universe_red_float_0_dot_0_with_activate_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    float red = 0.0f;
    yli::ontology::VariableStruct red_variable_struct(std::make_shared<yli::data::AnyValue>(red));
    red_variable_struct.local_name = "red";
    red_variable_struct.activate_callback = &yli::ontology::Variable::activate_background_color;
    red_variable_struct.should_ylikuutio_call_activate_callback_now = true;
    ASSERT_EQ(universe->get("red"), nullptr);
    universe->create_variable(red_variable_struct);

    ASSERT_NE(universe->get("red"), nullptr);
    yli::ontology::Variable* red_variable = universe->get("red");
    ASSERT_NE(red_variable, nullptr);

    std::shared_ptr<yli::data::AnyValue> red_value = red_variable->get();
    ASSERT_NE(red_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(red_value->data));
    ASSERT_EQ(std::get<float>(red_value->data), 0.0f);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_variable_universe_red_float_1_dot_0_with_activate_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    float red = 1.0f;
    yli::ontology::VariableStruct red_variable_struct(std::make_shared<yli::data::AnyValue>(red));
    red_variable_struct.local_name = "red";
    red_variable_struct.activate_callback = &yli::ontology::Variable::activate_background_color;
    red_variable_struct.should_ylikuutio_call_activate_callback_now = true;
    ASSERT_EQ(universe->get("red"), nullptr);
    universe->create_variable(red_variable_struct);

    ASSERT_NE(universe->get("red"), nullptr);
    yli::ontology::Variable* red_variable = universe->get("red");
    ASSERT_NE(red_variable, nullptr);

    std::shared_ptr<yli::data::AnyValue> red_value = red_variable->get();
    ASSERT_NE(red_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(red_value->data));
    ASSERT_EQ(std::get<float>(red_value->data), 1.0f);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_variable_universe_red_float_0_dot_875_with_activate_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    float red = 0.875f;
    yli::ontology::VariableStruct red_variable_struct(std::make_shared<yli::data::AnyValue>(red));
    red_variable_struct.local_name = "red";
    red_variable_struct.activate_callback = &yli::ontology::Variable::activate_background_color;
    red_variable_struct.should_ylikuutio_call_activate_callback_now = true;
    ASSERT_EQ(universe->get("red"), nullptr);
    universe->create_variable(red_variable_struct);

    ASSERT_NE(universe->get("red"), nullptr);
    yli::ontology::Variable* red_variable = universe->get("red");
    ASSERT_NE(red_variable, nullptr);

    std::shared_ptr<yli::data::AnyValue> red_value = red_variable->get();
    ASSERT_NE(red_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(red_value->data));
    ASSERT_EQ(std::get<float>(red_value->data), 0.875f);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_variable_universe_green_float_0_dot_0_with_activate_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    float green = 0.0f;
    yli::ontology::VariableStruct green_variable_struct(std::make_shared<yli::data::AnyValue>(green));
    green_variable_struct.local_name = "green";
    green_variable_struct.activate_callback = &yli::ontology::Variable::activate_background_color;
    green_variable_struct.should_ylikuutio_call_activate_callback_now = true;
    ASSERT_EQ(universe->get("green"), nullptr);
    universe->create_variable(green_variable_struct);

    ASSERT_NE(universe->get("green"), nullptr);
    yli::ontology::Variable* green_variable = universe->get("green");
    ASSERT_NE(green_variable, nullptr);

    std::shared_ptr<yli::data::AnyValue> green_value = green_variable->get();
    ASSERT_NE(green_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(green_value->data));
    ASSERT_EQ(std::get<float>(green_value->data), 0.0f);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_variable_universe_green_float_1_dot_0_with_activate_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    float green = 1.0f;
    yli::ontology::VariableStruct green_variable_struct(std::make_shared<yli::data::AnyValue>(green));
    green_variable_struct.local_name = "green";
    green_variable_struct.activate_callback = &yli::ontology::Variable::activate_background_color;
    green_variable_struct.should_ylikuutio_call_activate_callback_now = true;
    ASSERT_EQ(universe->get("green"), nullptr);
    universe->create_variable(green_variable_struct);

    ASSERT_NE(universe->get("green"), nullptr);
    yli::ontology::Variable* green_variable = universe->get("green");
    ASSERT_NE(green_variable, nullptr);

    std::shared_ptr<yli::data::AnyValue> green_value = green_variable->get();
    ASSERT_NE(green_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(green_value->data));
    ASSERT_EQ(std::get<float>(green_value->data), 1.0f);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_variable_universe_green_float_0_dot_875_with_activate_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    float green = 0.875f;
    yli::ontology::VariableStruct green_variable_struct(std::make_shared<yli::data::AnyValue>(green));
    green_variable_struct.local_name = "green";
    green_variable_struct.activate_callback = &yli::ontology::Variable::activate_background_color;
    green_variable_struct.should_ylikuutio_call_activate_callback_now = true;
    ASSERT_EQ(universe->get("green"), nullptr);
    universe->create_variable(green_variable_struct);

    ASSERT_NE(universe->get("green"), nullptr);
    yli::ontology::Variable* green_variable = universe->get("green");
    ASSERT_NE(green_variable, nullptr);

    std::shared_ptr<yli::data::AnyValue> green_value = green_variable->get();
    ASSERT_NE(green_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(green_value->data));
    ASSERT_EQ(std::get<float>(green_value->data), 0.875f);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_variable_universe_blue_float_0_dot_0_with_activate_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    float blue = 0.0f;
    yli::ontology::VariableStruct blue_variable_struct(std::make_shared<yli::data::AnyValue>(blue));
    blue_variable_struct.local_name = "blue";
    blue_variable_struct.activate_callback = &yli::ontology::Variable::activate_background_color;
    blue_variable_struct.should_ylikuutio_call_activate_callback_now = true;
    ASSERT_EQ(universe->get("blue"), nullptr);
    universe->create_variable(blue_variable_struct);

    ASSERT_NE(universe->get("blue"), nullptr);
    yli::ontology::Variable* blue_variable = universe->get("blue");
    ASSERT_NE(blue_variable, nullptr);

    std::shared_ptr<yli::data::AnyValue> blue_value = blue_variable->get();
    ASSERT_NE(blue_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(blue_value->data));
    ASSERT_EQ(std::get<float>(blue_value->data), 0.0f);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_variable_universe_blue_float_1_dot_0_with_activate_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    float blue = 1.0f;
    yli::ontology::VariableStruct blue_variable_struct(std::make_shared<yli::data::AnyValue>(blue));
    blue_variable_struct.local_name = "blue";
    blue_variable_struct.activate_callback = &yli::ontology::Variable::activate_background_color;
    blue_variable_struct.should_ylikuutio_call_activate_callback_now = true;
    ASSERT_EQ(universe->get("blue"), nullptr);
    universe->create_variable(blue_variable_struct);

    ASSERT_NE(universe->get("blue"), nullptr);
    yli::ontology::Variable* blue_variable = universe->get("blue");
    ASSERT_NE(blue_variable, nullptr);

    std::shared_ptr<yli::data::AnyValue> blue_value = blue_variable->get();
    ASSERT_NE(blue_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(blue_value->data));
    ASSERT_EQ(std::get<float>(blue_value->data), 1.0f);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_variable_universe_blue_float_0_dot_875_with_activate_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    float blue = 0.875f;
    yli::ontology::VariableStruct blue_variable_struct(std::make_shared<yli::data::AnyValue>(blue));
    blue_variable_struct.local_name = "blue";
    blue_variable_struct.activate_callback = &yli::ontology::Variable::activate_background_color;
    blue_variable_struct.should_ylikuutio_call_activate_callback_now = true;
    ASSERT_EQ(universe->get("blue"), nullptr);
    universe->create_variable(blue_variable_struct);

    ASSERT_NE(universe->get("blue"), nullptr);
    yli::ontology::Variable* blue_variable = universe->get("blue");
    ASSERT_NE(blue_variable, nullptr);

    std::shared_ptr<yli::data::AnyValue> blue_value = blue_variable->get();
    ASSERT_NE(blue_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(blue_value->data));
    ASSERT_EQ(std::get<float>(blue_value->data), 0.875f);
}

TEST(variables_must_be_initialized_appropriately, headless_universe_variable_universe_cartesian_coordinates_x_y_z_activate_callbacks_and_read_callbacks)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    float x = 1234.25f;
    float y = 2345.50f;
    float z = 3456.75f;

    yli::ontology::VariableStruct cartesian_coordinates_variable_struct(std::make_shared<yli::data::AnyValue>(std::make_shared<glm::vec3>(NAN, NAN, NAN)));
    cartesian_coordinates_variable_struct.local_name = "cartesian_coordinates";
    cartesian_coordinates_variable_struct.activate_callback = &yli::ontology::activate_cartesian_coordinates;
    cartesian_coordinates_variable_struct.read_callback = &yli::ontology::read_cartesian_coordinates;
    cartesian_coordinates_variable_struct.should_ylikuutio_call_activate_callback_now = false;
    universe->create_variable(cartesian_coordinates_variable_struct);

    yli::ontology::VariableStruct x_variable_struct(std::make_shared<yli::data::AnyValue>(x));
    x_variable_struct.local_name = "x";
    x_variable_struct.activate_callback = &yli::ontology::activate_x;
    x_variable_struct.read_callback = &yli::ontology::read_x;
    x_variable_struct.should_ylikuutio_call_activate_callback_now = true;
    universe->create_variable(x_variable_struct);

    yli::ontology::VariableStruct y_variable_struct(std::make_shared<yli::data::AnyValue>(y));
    y_variable_struct.local_name = "y";
    y_variable_struct.activate_callback = &yli::ontology::activate_y;
    y_variable_struct.read_callback = &yli::ontology::read_y;
    y_variable_struct.should_ylikuutio_call_activate_callback_now = true;
    universe->create_variable(y_variable_struct);

    yli::ontology::VariableStruct z_variable_struct(std::make_shared<yli::data::AnyValue>(z));
    z_variable_struct.local_name = "z";
    z_variable_struct.activate_callback = &yli::ontology::activate_z;
    z_variable_struct.read_callback = &yli::ontology::read_z;
    z_variable_struct.should_ylikuutio_call_activate_callback_now = true;
    universe->create_variable(z_variable_struct);

    ASSERT_NE(universe->get("x"), nullptr);
    yli::ontology::Variable* x_variable = universe->get("x");
    ASSERT_NE(x_variable, nullptr);
    std::shared_ptr<yli::data::AnyValue> x_value = x_variable->get();
    ASSERT_NE(x_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(x_value->data));
    ASSERT_EQ(std::get<float>(x_value->data), 1234.25f);

    ASSERT_NE(universe->get("y"), nullptr);
    yli::ontology::Variable* y_variable = universe->get("y");
    ASSERT_NE(y_variable, nullptr);
    std::shared_ptr<yli::data::AnyValue> y_value = y_variable->get();
    ASSERT_NE(y_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(y_value->data));
    ASSERT_EQ(std::get<float>(y_value->data), 2345.50f);

    ASSERT_NE(universe->get("z"), nullptr);
    yli::ontology::Variable* z_variable = universe->get("z");
    ASSERT_NE(z_variable, nullptr);
    std::shared_ptr<yli::data::AnyValue> z_value = z_variable->get();
    ASSERT_NE(z_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(z_value->data));
    ASSERT_EQ(std::get<float>(z_value->data), 3456.75f);

    ASSERT_NE(universe->get("cartesian_coordinates"), nullptr);
    yli::ontology::Variable* cartesian_coordinates_variable = universe->get("cartesian_coordinates");
    ASSERT_NE(cartesian_coordinates_variable, nullptr);
    std::shared_ptr<yli::data::AnyValue> cartesian_coordinates_value = cartesian_coordinates_variable->get();
    ASSERT_NE(cartesian_coordinates_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<std::shared_ptr<glm::vec3>>(cartesian_coordinates_value->data));
    ASSERT_EQ(*(std::get<std::shared_ptr<glm::vec3>>(cartesian_coordinates_value->data)), glm::vec3(1234.25f, 2345.50f, 3456.75f));
}

TEST(variables_must_be_initialized_appropriately, headless_universe_variable_universe_x_y_z_cartesian_coordinates_activate_callbacks_and_read_callbacks)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    float x = 1234.25f;
    float y = 2345.50f;
    float z = 3456.75f;

    yli::ontology::VariableStruct x_variable_struct(std::make_shared<yli::data::AnyValue>(x));
    x_variable_struct.local_name = "x";
    x_variable_struct.activate_callback = &yli::ontology::activate_x;
    x_variable_struct.read_callback = &yli::ontology::read_x;
    x_variable_struct.should_ylikuutio_call_activate_callback_now = true;
    universe->create_variable(x_variable_struct);

    yli::ontology::VariableStruct y_variable_struct(std::make_shared<yli::data::AnyValue>(y));
    y_variable_struct.local_name = "y";
    y_variable_struct.activate_callback = &yli::ontology::activate_y;
    y_variable_struct.read_callback = &yli::ontology::read_y;
    y_variable_struct.should_ylikuutio_call_activate_callback_now = true;
    universe->create_variable(y_variable_struct);

    yli::ontology::VariableStruct z_variable_struct(std::make_shared<yli::data::AnyValue>(z));
    z_variable_struct.local_name = "z";
    z_variable_struct.activate_callback = &yli::ontology::activate_z;
    z_variable_struct.read_callback = &yli::ontology::read_z;
    z_variable_struct.should_ylikuutio_call_activate_callback_now = true;
    universe->create_variable(z_variable_struct);

    yli::ontology::VariableStruct cartesian_coordinates_variable_struct(std::make_shared<yli::data::AnyValue>(std::make_shared<glm::vec3>(NAN, NAN, NAN)));
    cartesian_coordinates_variable_struct.local_name = "cartesian_coordinates";
    cartesian_coordinates_variable_struct.activate_callback = &yli::ontology::activate_cartesian_coordinates;
    cartesian_coordinates_variable_struct.read_callback = &yli::ontology::read_cartesian_coordinates;
    cartesian_coordinates_variable_struct.should_ylikuutio_call_activate_callback_now = false;
    universe->create_variable(cartesian_coordinates_variable_struct);

    ASSERT_NE(universe->get("x"), nullptr);
    yli::ontology::Variable* x_variable = universe->get("x");
    ASSERT_NE(x_variable, nullptr);
    std::shared_ptr<yli::data::AnyValue> x_value = x_variable->get();
    ASSERT_NE(x_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(x_value->data));
    ASSERT_EQ(std::get<float>(x_value->data), 1234.25f);

    ASSERT_NE(universe->get("y"), nullptr);
    yli::ontology::Variable* y_variable = universe->get("y");
    ASSERT_NE(y_variable, nullptr);
    std::shared_ptr<yli::data::AnyValue> y_value = y_variable->get();
    ASSERT_NE(y_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(y_value->data));
    ASSERT_EQ(std::get<float>(y_value->data), 2345.50f);

    ASSERT_NE(universe->get("z"), nullptr);
    yli::ontology::Variable* z_variable = universe->get("z");
    ASSERT_NE(z_variable, nullptr);
    std::shared_ptr<yli::data::AnyValue> z_value = z_variable->get();
    ASSERT_NE(z_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(z_value->data));
    ASSERT_EQ(std::get<float>(z_value->data), 3456.75f);

    ASSERT_NE(universe->get("cartesian_coordinates"), nullptr);
    yli::ontology::Variable* cartesian_coordinates_variable = universe->get("cartesian_coordinates");
    ASSERT_NE(cartesian_coordinates_variable, nullptr);
    std::shared_ptr<yli::data::AnyValue> cartesian_coordinates_value = cartesian_coordinates_variable->get();
    ASSERT_NE(cartesian_coordinates_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<std::shared_ptr<glm::vec3>>(cartesian_coordinates_value->data));
    ASSERT_EQ(*(std::get<std::shared_ptr<glm::vec3>>(cartesian_coordinates_value->data)), glm::vec3(1234.25f, 2345.50f, 3456.75f));
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_variable_universe_x_y_z_cartesian_coordinates_activate_callbacks_and_read_callbacks)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    float x = 1234.25f;
    float y = 2345.50f;
    float z = 3456.75f;

    yli::ontology::VariableStruct x_variable_struct(std::make_shared<yli::data::AnyValue>(x));
    x_variable_struct.local_name = "x";
    x_variable_struct.activate_callback = &yli::ontology::activate_x;
    x_variable_struct.read_callback = &yli::ontology::read_x;
    x_variable_struct.should_ylikuutio_call_activate_callback_now = true;
    universe->create_variable(x_variable_struct);

    yli::ontology::VariableStruct y_variable_struct(std::make_shared<yli::data::AnyValue>(y));
    y_variable_struct.local_name = "y";
    y_variable_struct.activate_callback = &yli::ontology::activate_y;
    y_variable_struct.read_callback = &yli::ontology::read_y;
    y_variable_struct.should_ylikuutio_call_activate_callback_now = true;
    universe->create_variable(y_variable_struct);

    yli::ontology::VariableStruct z_variable_struct(std::make_shared<yli::data::AnyValue>(z));
    z_variable_struct.local_name = "z";
    z_variable_struct.activate_callback = &yli::ontology::activate_z;
    z_variable_struct.read_callback = &yli::ontology::read_z;
    z_variable_struct.should_ylikuutio_call_activate_callback_now = true;
    universe->create_variable(z_variable_struct);

    yli::ontology::VariableStruct cartesian_coordinates_variable_struct(std::make_shared<yli::data::AnyValue>(std::make_shared<glm::vec3>(NAN, NAN, NAN)));
    cartesian_coordinates_variable_struct.local_name = "cartesian_coordinates";
    cartesian_coordinates_variable_struct.activate_callback = &yli::ontology::activate_cartesian_coordinates;
    cartesian_coordinates_variable_struct.read_callback = &yli::ontology::read_cartesian_coordinates;
    cartesian_coordinates_variable_struct.should_ylikuutio_call_activate_callback_now = false;
    universe->create_variable(cartesian_coordinates_variable_struct);

    yli::ontology::Variable* x_variable = universe->get("x");
    yli::ontology::Variable* y_variable = universe->get("y");
    yli::ontology::Variable* z_variable = universe->get("z");
    yli::ontology::Variable* cartesian_coordinates_variable = universe->get("cartesian_coordinates");

    x_variable->set("0.875");
    std::shared_ptr<yli::data::AnyValue> x_value = x_variable->get();
    ASSERT_NE(x_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(x_value->data));
    ASSERT_EQ(std::get<float>(x_value->data), 0.875f);
    ASSERT_EQ(*(std::get<std::shared_ptr<glm::vec3>>(cartesian_coordinates_variable->get()->data)), glm::vec3(0.875f, 2345.50f, 3456.75f));

    y_variable->set("0.9375");
    std::shared_ptr<yli::data::AnyValue> y_value = y_variable->get();
    ASSERT_NE(y_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(y_value->data));
    ASSERT_EQ(std::get<float>(y_value->data), 0.9375f);
    ASSERT_EQ(*(std::get<std::shared_ptr<glm::vec3>>(cartesian_coordinates_variable->get()->data)), glm::vec3(0.875f, 0.9375f, 3456.75f));

    z_variable->set("0.96875");
    std::shared_ptr<yli::data::AnyValue> z_value = z_variable->get();
    ASSERT_NE(z_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(z_value->data));
    ASSERT_EQ(std::get<float>(z_value->data), 0.96875f);
    ASSERT_EQ(*(std::get<std::shared_ptr<glm::vec3>>(cartesian_coordinates_variable->get()->data)), glm::vec3(0.875f, 0.9375f, 0.96875f));
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_bool_true_new_value_true_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    bool bool_true = true;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(bool_true));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("true");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<bool>(variable_value->data));
    ASSERT_TRUE(std::get<bool>(variable_value->data));
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_bool_true_new_value_false_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    bool bool_true = true;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(bool_true));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("false");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<bool>(variable_value->data));
    ASSERT_FALSE(std::get<bool>(variable_value->data));
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_bool_false_new_value_true_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    bool bool_false = false;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(bool_false));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("true");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<bool>(variable_value->data));
    ASSERT_TRUE(std::get<bool>(variable_value->data));
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_bool_false_new_value_false_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    bool bool_false = false;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(bool_false));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("false");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<bool>(variable_value->data));
    ASSERT_FALSE(std::get<bool>(variable_value->data));
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_bool_true_new_value_foo_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    bool bool_true = true;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(bool_true));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("foo");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<bool>(variable_value->data));
    ASSERT_TRUE(std::get<bool>(variable_value->data));
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_bool_false_new_value_foo_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    bool bool_false = false;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(bool_false));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("foo");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<bool>(variable_value->data));
    ASSERT_FALSE(std::get<bool>(variable_value->data));
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_char_lowercase_a_new_value_a_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    char char_lowercase_a = 'a';
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(char_lowercase_a));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("a");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<char>(variable_value->data));
    ASSERT_EQ(std::get<char>(variable_value->data), 'a');
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_char_lowercase_a_new_value_b_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    char char_lowercase_a = 'a';
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(char_lowercase_a));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("b");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<char>(variable_value->data));
    ASSERT_EQ(std::get<char>(variable_value->data), 'b');
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_char_lowercase_a_new_value_A_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    char char_lowercase_a = 'a';
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(char_lowercase_a));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("A");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<char>(variable_value->data));
    ASSERT_EQ(std::get<char>(variable_value->data), 'A');
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_char_lowercase_a_new_value_space_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    char char_lowercase_a = 'a';
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(char_lowercase_a));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set(" ");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<char>(variable_value->data));
    ASSERT_EQ(std::get<char>(variable_value->data), ' ');
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_char_lowercase_a_new_value_newline_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    char char_lowercase_a = 'a';
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(char_lowercase_a));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("\n");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<char>(variable_value->data));
    ASSERT_EQ(std::get<char>(variable_value->data), '\n');
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_char_lowercase_a_new_value_ba_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    char char_lowercase_a = 'a';
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(char_lowercase_a));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("ba");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<char>(variable_value->data));
    ASSERT_EQ(std::get<char>(variable_value->data), 'a');
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_char_lowercase_a_new_value_bb_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    char char_lowercase_a = 'a';
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(char_lowercase_a));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("bb");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<char>(variable_value->data));
    ASSERT_EQ(std::get<char>(variable_value->data), 'a');
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_char_lowercase_a_new_value_bc_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    char char_lowercase_a = 'a';
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(char_lowercase_a));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("bc");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<char>(variable_value->data));
    ASSERT_EQ(std::get<char>(variable_value->data), 'a');
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_float_0_new_value_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    float float_zero = 0.0f;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(float_zero));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("0");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(variable_value->data));
    ASSERT_EQ(std::get<float>(variable_value->data), 0.0f);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_float_0_new_value_0_dot_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    float float_zero = 0.0f;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(float_zero));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("0.0");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(variable_value->data));
    ASSERT_EQ(std::get<float>(variable_value->data), 0.0f);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_float_0_new_value_plus_1_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    float float_zero = 0.0f;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(float_zero));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("1");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(variable_value->data));
    ASSERT_EQ(std::get<float>(variable_value->data), 1.0f);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_float_0_new_value_plus_1_dot_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    float float_zero = 0.0f;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(float_zero));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("1.0");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(variable_value->data));
    ASSERT_EQ(std::get<float>(variable_value->data), 1.0f);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_float_0_new_value_minus_1_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    float float_zero = 0.0f;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(float_zero));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("-1");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(variable_value->data));
    ASSERT_EQ(std::get<float>(variable_value->data), -1.0f);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_float_0_new_value_minus_1_dot_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    float float_zero = 0.0f;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(float_zero));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("-1.0");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(variable_value->data));
    ASSERT_EQ(std::get<float>(variable_value->data), -1.0f);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_float_0_new_value_foo_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    float float_zero = 0.0f;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(float_zero));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("foo");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(variable_value->data));
    ASSERT_EQ(std::get<float>(variable_value->data), 0.0f);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_float_plus_1_new_value_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    float float_plus_1 = 1.0f;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(float_plus_1));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("0");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(variable_value->data));
    ASSERT_EQ(std::get<float>(variable_value->data), 0.0f);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_float_plus_1_new_value_0_dot_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    float float_plus_1 = 1.0f;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(float_plus_1));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("0.0");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(variable_value->data));
    ASSERT_EQ(std::get<float>(variable_value->data), 0.0f);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_float_plus_1_new_value_plus_1_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    float float_plus_1 = 1.0f;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(float_plus_1));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("1");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(variable_value->data));
    ASSERT_EQ(std::get<float>(variable_value->data), 1.0f);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_float_plus_1_new_value_plus_1_dot_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    float float_plus_1 = 1.0f;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(float_plus_1));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("1.0");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(variable_value->data));
    ASSERT_EQ(std::get<float>(variable_value->data), 1.0f);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_float_plus_1_new_value_minus_1_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    float float_plus_1 = 1.0f;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(float_plus_1));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("-1");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(variable_value->data));
    ASSERT_EQ(std::get<float>(variable_value->data), -1.0f);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_float_plus_1_new_value_minus_1_dot_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    float float_plus_1 = 1.0f;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(float_plus_1));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("-1.0");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(variable_value->data));
    ASSERT_EQ(std::get<float>(variable_value->data), -1.0f);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_float_plus_1_new_value_foo_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    float float_plus_1 = 1.0f;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(float_plus_1));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("foo");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(variable_value->data));
    ASSERT_EQ(std::get<float>(variable_value->data), 1.0f);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_double_0_new_value_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    double double_zero = 0.0;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(double_zero));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("0");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<double>(variable_value->data));
    ASSERT_EQ(std::get<double>(variable_value->data), 0.0);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_double_0_new_value_0_dot_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    double double_zero = 0.0;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(double_zero));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("0.0");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<double>(variable_value->data));
    ASSERT_EQ(std::get<double>(variable_value->data), 0.0);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_double_0_new_value_plus_1_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    double double_zero = 0.0;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(double_zero));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("1");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<double>(variable_value->data));
    ASSERT_EQ(std::get<double>(variable_value->data), 1.0);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_double_0_new_value_plus_1_dot_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    double double_zero = 0.0;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(double_zero));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("1.0");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<double>(variable_value->data));
    ASSERT_EQ(std::get<double>(variable_value->data), 1.0);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_double_0_new_value_minus_1_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    double double_zero = 0.0;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(double_zero));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("-1");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<double>(variable_value->data));
    ASSERT_EQ(std::get<double>(variable_value->data), -1.0);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_double_0_new_value_minus_1_dot_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    double double_zero = 0.0;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(double_zero));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("-1.0");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<double>(variable_value->data));
    ASSERT_EQ(std::get<double>(variable_value->data), -1.0);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_double_0_new_value_foo_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    double double_zero = 0.0;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(double_zero));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("foo");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<double>(variable_value->data));
    ASSERT_EQ(std::get<double>(variable_value->data), 0.0);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_double_plus_1_new_value_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    double double_plus_1 = 1.0;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(double_plus_1));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("0");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<double>(variable_value->data));
    ASSERT_EQ(std::get<double>(variable_value->data), 0.0);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_double_plus_1_new_value_0_dot_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    double double_plus_1 = 1.0;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(double_plus_1));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("0.0");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<double>(variable_value->data));
    ASSERT_EQ(std::get<double>(variable_value->data), 0.0);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_double_plus_1_new_value_plus_1_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    double double_plus_1 = 1.0;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(double_plus_1));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("1");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<double>(variable_value->data));
    ASSERT_EQ(std::get<double>(variable_value->data), 1.0);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_double_plus_1_new_value_plus_1_dot_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    double double_plus_1 = 1.0;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(double_plus_1));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("1.0");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<double>(variable_value->data));
    ASSERT_EQ(std::get<double>(variable_value->data), 1.0);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_double_plus_1_new_value_minus_1_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    double double_plus_1 = 1.0;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(double_plus_1));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("-1");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<double>(variable_value->data));
    ASSERT_EQ(std::get<double>(variable_value->data), -1.0);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_double_plus_1_new_value_minus_1_dot_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    double double_plus_1 = 1.0;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(double_plus_1));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("-1.0");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<double>(variable_value->data));
    ASSERT_EQ(std::get<double>(variable_value->data), -1.0);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_double_plus_1_new_value_foo_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    double double_plus_1 = 1.0;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(double_plus_1));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("foo");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<double>(variable_value->data));
    ASSERT_EQ(std::get<double>(variable_value->data), 1.0);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_int32_t_0_new_value_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    int32_t int32_t_zero = 0;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(int32_t_zero));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("0");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<int32_t>(variable_value->data));
    ASSERT_EQ(std::get<int32_t>(variable_value->data), 0);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_int32_t_0_new_value_plus_1_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    int32_t int32_t_zero = 0;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(int32_t_zero));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("1");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<int32_t>(variable_value->data));
    ASSERT_EQ(std::get<int32_t>(variable_value->data), 1);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_int32_t_0_new_value_minus_1_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    int32_t int32_t_zero = 0;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(int32_t_zero));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("-1");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<int32_t>(variable_value->data));
    ASSERT_EQ(std::get<int32_t>(variable_value->data), -1);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_int32_t_0_new_value_0_dot_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    int32_t int32_t_zero = 0;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(int32_t_zero));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("0.0");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<int32_t>(variable_value->data));
    ASSERT_EQ(std::get<int32_t>(variable_value->data), 0);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_int32_t_0_new_value_plus_1_dot_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    int32_t int32_t_zero = 0;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(int32_t_zero));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("1.0");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<int32_t>(variable_value->data));
    ASSERT_EQ(std::get<int32_t>(variable_value->data), 0);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_int32_t_0_new_value_minus_1_dot_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    int32_t int32_t_zero = 0;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(int32_t_zero));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("-1.0");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<int32_t>(variable_value->data));
    ASSERT_EQ(std::get<int32_t>(variable_value->data), 0);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_int32_t_0_new_value_foo_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    int32_t int32_t_zero = 0;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(int32_t_zero));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("foo");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<int32_t>(variable_value->data));
    ASSERT_EQ(std::get<int32_t>(variable_value->data), 0);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_int32_t_plus_1_new_value_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    int32_t int32_t_plus_1 = 1;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(int32_t_plus_1));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("0");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<int32_t>(variable_value->data));
    ASSERT_EQ(std::get<int32_t>(variable_value->data), 0);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_int32_t_plus_1_new_value_plus_1_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    int32_t int32_t_plus_1 = 1;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(int32_t_plus_1));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("1");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<int32_t>(variable_value->data));
    ASSERT_EQ(std::get<int32_t>(variable_value->data), 1);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_int32_t_plus_1_new_value_minus_1_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    int32_t int32_t_plus_1 = 1;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(int32_t_plus_1));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("-1");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<int32_t>(variable_value->data));
    ASSERT_EQ(std::get<int32_t>(variable_value->data), -1);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_int32_t_plus_1_new_value_0_dot_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    int32_t int32_t_plus_1 = 1;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(int32_t_plus_1));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("0.0");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<int32_t>(variable_value->data));
    ASSERT_EQ(std::get<int32_t>(variable_value->data), 1);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_int32_t_plus_1_new_value_plus_1_dot_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    int32_t int32_t_plus_1 = 1;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(int32_t_plus_1));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("1.0");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<int32_t>(variable_value->data));
    ASSERT_EQ(std::get<int32_t>(variable_value->data), 1);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_int32_t_plus_1_new_value_foo_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    int32_t int32_t_plus_1 = 1;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(int32_t_plus_1));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("foo");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<int32_t>(variable_value->data));
    ASSERT_EQ(std::get<int32_t>(variable_value->data), 1);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_uint32_t_0_new_value_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    uint32_t uint32_t_zero = 0;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(uint32_t_zero));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("0");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<uint32_t>(variable_value->data));
    ASSERT_EQ(std::get<uint32_t>(variable_value->data), 0);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_uint32_t_0_new_value_plus_1_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    uint32_t uint32_t_zero = 0;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(uint32_t_zero));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("1");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<uint32_t>(variable_value->data));
    ASSERT_EQ(std::get<uint32_t>(variable_value->data), 1);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_uint32_t_0_new_value_minus_1_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    uint32_t uint32_t_zero = 0;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(uint32_t_zero));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("-1");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<uint32_t>(variable_value->data));
    ASSERT_EQ(std::get<uint32_t>(variable_value->data), 0);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_uint32_t_0_new_value_0_dot_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    uint32_t uint32_t_zero = 0;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(uint32_t_zero));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("0.0");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<uint32_t>(variable_value->data));
    ASSERT_EQ(std::get<uint32_t>(variable_value->data), 0);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_uint32_t_0_new_value_plus_1_dot_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    uint32_t uint32_t_zero = 0;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(uint32_t_zero));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("1.0");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<uint32_t>(variable_value->data));
    ASSERT_EQ(std::get<uint32_t>(variable_value->data), 0);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_uint32_t_0_new_value_minus_1_dot_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    uint32_t uint32_t_zero = 0;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(uint32_t_zero));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("-1.0");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<uint32_t>(variable_value->data));
    ASSERT_EQ(std::get<uint32_t>(variable_value->data), 0);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_uint32_t_0_new_value_foo_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    uint32_t uint32_t_zero = 0;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(uint32_t_zero));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("foo");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<uint32_t>(variable_value->data));
    ASSERT_EQ(std::get<uint32_t>(variable_value->data), 0);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_uint32_t_plus_1_new_value_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    uint32_t uint32_t_plus_1 = 1;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(uint32_t_plus_1));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("0");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<uint32_t>(variable_value->data));
    ASSERT_EQ(std::get<uint32_t>(variable_value->data), 0);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_uint32_t_plus_1_new_value_plus_1_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    uint32_t uint32_t_plus_1 = 1;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(uint32_t_plus_1));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("1");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<uint32_t>(variable_value->data));
    ASSERT_EQ(std::get<uint32_t>(variable_value->data), 1);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_uint32_t_plus_1_new_value_minus_1_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    uint32_t uint32_t_plus_1 = 1;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(uint32_t_plus_1));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("-1");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<uint32_t>(variable_value->data));
    ASSERT_EQ(std::get<uint32_t>(variable_value->data), 1);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_uint32_t_plus_1_new_value_0_dot_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    uint32_t uint32_t_plus_1 = 1;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(uint32_t_plus_1));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("0.0");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<uint32_t>(variable_value->data));
    ASSERT_EQ(std::get<uint32_t>(variable_value->data), 1);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_uint32_t_plus_1_new_value_plus_1_dot_0_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    uint32_t uint32_t_plus_1 = 1;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(uint32_t_plus_1));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("1.0");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<uint32_t>(variable_value->data));
    ASSERT_EQ(std::get<uint32_t>(variable_value->data), 1);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_uint32_t_plus_1_new_value_foo_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    uint32_t uint32_t_plus_1 = 1;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(uint32_t_plus_1));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    variable->set("foo");
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<uint32_t>(variable_value->data));
    ASSERT_EQ(std::get<uint32_t>(variable_value->data), 1);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_bool_true_copy_value_true_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    bool bool_true = true;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(bool_true));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    std::shared_ptr<yli::data::AnyValue> bool_true_any_value = std::make_shared<yli::data::AnyValue>(true);
    variable->set(bool_true_any_value);
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<bool>(variable_value->data));
    ASSERT_TRUE(std::get<bool>(variable_value->data));

    bool_true_any_value->data = false;
    ASSERT_TRUE(std::get<bool>(variable_value->data)); // Must do a deep copy, that is, changing the source value after copying must not affect the dest value.
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_bool_true_copy_value_false_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    bool bool_true = true;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(bool_true));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    std::shared_ptr<yli::data::AnyValue> bool_false_any_value = std::make_shared<yli::data::AnyValue>(false);
    variable->set(bool_false_any_value);
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<bool>(variable_value->data));
    ASSERT_FALSE(std::get<bool>(variable_value->data));

    bool_false_any_value->data = true;
    ASSERT_FALSE(std::get<bool>(variable_value->data)); // Must do a deep copy, that is, changing the source value after copying must not affect the dest value.
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_bool_false_copy_value_true_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    bool bool_false = false;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(bool_false));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    std::shared_ptr<yli::data::AnyValue> bool_true_any_value = std::make_shared<yli::data::AnyValue>(true);
    variable->set(bool_true_any_value);
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<bool>(variable_value->data));
    ASSERT_TRUE(std::get<bool>(variable_value->data));

    bool_true_any_value->data = false;
    ASSERT_TRUE(std::get<bool>(variable_value->data)); // Must do a deep copy, that is, changing the source value after copying must not affect the dest value.
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_bool_false_copy_value_false_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    bool bool_false = false;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(bool_false));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    std::shared_ptr<yli::data::AnyValue> bool_false_any_value = std::make_shared<yli::data::AnyValue>(false);
    variable->set(bool_false_any_value);
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<bool>(variable_value->data));
    ASSERT_FALSE(std::get<bool>(variable_value->data));

    bool_false_any_value->data = true;
    ASSERT_FALSE(std::get<bool>(variable_value->data)); // Must do a deep copy, that is, changing the source value after copying must not affect the dest value.
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_bool_true_shallow_copy_value_true_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    bool bool_true = true;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(bool_true));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    std::shared_ptr<yli::data::AnyValue> bool_true_any_value = std::make_shared<yli::data::AnyValue>(true);
    variable->set_shallow(bool_true_any_value);
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<bool>(variable_value->data));
    ASSERT_TRUE(std::get<bool>(variable_value->data));

    bool_true_any_value->data = false;
    ASSERT_FALSE(std::get<bool>(variable_value->data)); // Must do a shallow copy, that is, changing the source value after copying must affect the dest value.
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_bool_true_shallow_copy_value_false_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    bool bool_true = true;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(bool_true));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    std::shared_ptr<yli::data::AnyValue> bool_false_any_value = std::make_shared<yli::data::AnyValue>(false);
    variable->set_shallow(bool_false_any_value);
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<bool>(variable_value->data));
    ASSERT_FALSE(std::get<bool>(variable_value->data));

    bool_false_any_value->data = true;
    ASSERT_TRUE(std::get<bool>(variable_value->data)); // Must do a shallow copy, that is, changing the source value after copying must affect the dest value.
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_bool_false_shallow_copy_value_true_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    bool bool_false = false;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(bool_false));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    std::shared_ptr<yli::data::AnyValue> bool_true_any_value = std::make_shared<yli::data::AnyValue>(true);
    variable->set_shallow(bool_true_any_value);
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<bool>(variable_value->data));
    ASSERT_TRUE(std::get<bool>(variable_value->data));

    bool_true_any_value->data = false;
    ASSERT_FALSE(std::get<bool>(variable_value->data)); // Must do a shallow copy, that is, changing the source value after copying must affect the dest value.
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_bool_false_shallow_copy_value_false_no_activate_callback_no_read_callback)
{
    yli::ontology::UniverseStruct universe_struct;
    universe_struct.is_headless = true;
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    bool bool_false = false;
    yli::ontology::VariableStruct variable_struct(std::make_shared<yli::data::AnyValue>(bool_false));
    variable_struct.local_name = "foo";
    universe->create_variable(variable_struct);

    yli::ontology::Variable* const variable = universe->get("foo");
    std::shared_ptr<yli::data::AnyValue> bool_false_any_value = std::make_shared<yli::data::AnyValue>(false);
    variable->set_shallow(bool_false_any_value);
    std::shared_ptr<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_NE(variable_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<bool>(variable_value->data));
    ASSERT_FALSE(std::get<bool>(variable_value->data));

    bool_false_any_value->data = true;
    ASSERT_TRUE(std::get<bool>(variable_value->data)); // Must do a shallow copy, that is, changing the source value after copying must affect the dest value.
}
