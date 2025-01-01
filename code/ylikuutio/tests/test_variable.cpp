// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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
#include "code/mock/mock_application.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/variable.hpp"
#include "code/ylikuutio/ontology/ecosystem.hpp"
#include "code/ylikuutio/ontology/movable_variable_activation.hpp"
#include "code/ylikuutio/ontology/movable_variable_read.hpp"
#include "code/ylikuutio/ontology/variable_struct.hpp"
#include "code/ylikuutio/ontology/ecosystem_struct.hpp"
#include "code/ylikuutio/ontology/scene_struct.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>    // NAN, std::isnan
#include <cstddef>  // uintptr_t
#include <limits>   // std::numeric_limits
#include <optional> // std::optional
#include <stdint.h> // uint32_t etc.
#include <variant>  // std::holds_alternative

TEST(is_variable_must_return_false_for_nonexisting_variables, headless_universe)
{
    mock::MockApplication application;
    ASSERT_FALSE(application.get_universe().has_variable("foo"));
}

TEST(get_must_return_nullptr_for_nonexisting_variables, headless_universe)
{
    mock::MockApplication application;
    ASSERT_EQ(application.get_universe().get_variable("foo"), nullptr);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_unnamed_variable_bool_true_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    bool bool_true = true;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(bool_true));
    ASSERT_FALSE(application.get_universe().has_variable("foo"));
    ASSERT_EQ(application.get_universe().get_variable("foo"), nullptr);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_bool_true_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    bool bool_true = true;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(bool_true));
    ASSERT_TRUE(application.get_universe().has_variable("foo"));
    ASSERT_NE(application.get_universe().get_variable("foo"), nullptr);
    ASSERT_FALSE(application.get_universe().has_variable("bar"));
    ASSERT_EQ(application.get_universe().get_variable("bar"), nullptr);

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    ASSERT_NE(variable, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(variable) % alignof(yli::ontology::Variable), 0);
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<bool>(variable_value->data));
    ASSERT_TRUE(std::get<bool>(variable_value->data));
}

TEST(variable_must_be_initialized_appropriately, headless_universe_unnamed_variable_bool_false_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    bool bool_false = false;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(bool_false));
    ASSERT_FALSE(application.get_universe().has_variable("foo"));
    ASSERT_EQ(application.get_universe().get_variable("foo"), nullptr);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_bool_false_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    bool bool_false = false;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(bool_false));
    ASSERT_TRUE(application.get_universe().has_variable("foo"));
    ASSERT_NE(application.get_universe().get_variable("foo"), nullptr);
    ASSERT_FALSE(application.get_universe().has_variable("bar"));
    ASSERT_EQ(application.get_universe().get_variable("bar"), nullptr);

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    ASSERT_NE(variable, nullptr);
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<bool>(variable_value->data));
    ASSERT_FALSE(std::get<bool>(variable_value->data));
}

TEST(variable_must_be_initialized_appropriately, headless_universe_unnamed_variable_char_lowercase_a_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    char char_lowercase_a = 'a';
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(char_lowercase_a));
    ASSERT_FALSE(application.get_universe().has_variable("foo"));
    ASSERT_EQ(application.get_universe().get_variable("foo"), nullptr);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_char_lowercase_a_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    char char_lowercase_a = 'a';
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(char_lowercase_a));
    ASSERT_TRUE(application.get_universe().has_variable("foo"));
    ASSERT_NE(application.get_universe().get_variable("foo"), nullptr);
    ASSERT_FALSE(application.get_universe().has_variable("bar"));
    ASSERT_EQ(application.get_universe().get_variable("bar"), nullptr);

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    ASSERT_NE(variable, nullptr);
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<char>(variable_value->data));
    ASSERT_EQ(std::get<char>(variable_value->data), 'a');
}

TEST(variable_must_be_initialized_appropriately, headless_universe_unnamed_variable_char_lowercase_b_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    char char_lowercase_b = 'b';
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(char_lowercase_b));
    ASSERT_FALSE(application.get_universe().has_variable("foo"));
    ASSERT_EQ(application.get_universe().get_variable("foo"), nullptr);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_char_lowercase_b_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    char char_lowercase_b = 'b';
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(char_lowercase_b));
    ASSERT_TRUE(application.get_universe().has_variable("foo"));
    ASSERT_NE(application.get_universe().get_variable("foo"), nullptr);
    ASSERT_FALSE(application.get_universe().has_variable("bar"));
    ASSERT_EQ(application.get_universe().get_variable("bar"), nullptr);

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    ASSERT_NE(variable, nullptr);
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<char>(variable_value->data));
    ASSERT_EQ(std::get<char>(variable_value->data), 'b');
}

TEST(variable_must_be_initialized_appropriately, headless_universe_unnamed_variable_char_space_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    char char_space = ' ';
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(char_space));
    ASSERT_FALSE(application.get_universe().has_variable("foo"));
    ASSERT_EQ(application.get_universe().get_variable("foo"), nullptr);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_char_space_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    char char_space = ' ';
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(char_space));
    ASSERT_TRUE(application.get_universe().has_variable("foo"));
    ASSERT_NE(application.get_universe().get_variable("foo"), nullptr);
    ASSERT_FALSE(application.get_universe().has_variable("bar"));
    ASSERT_EQ(application.get_universe().get_variable("bar"), nullptr);

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    ASSERT_NE(variable, nullptr);
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<char>(variable_value->data));
    ASSERT_EQ(std::get<char>(variable_value->data), ' ');
}

TEST(variable_must_be_initialized_appropriately, headless_universe_unnamed_variable_char_newline_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    char char_newline = '\n';
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(char_newline));
    ASSERT_FALSE(application.get_universe().has_variable("foo"));
    ASSERT_EQ(application.get_universe().get_variable("foo"), nullptr);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_char_newline_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    char char_newline = '\n';
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(char_newline));
    ASSERT_TRUE(application.get_universe().has_variable("foo"));
    ASSERT_NE(application.get_universe().get_variable("foo"), nullptr);
    ASSERT_FALSE(application.get_universe().has_variable("bar"));
    ASSERT_EQ(application.get_universe().get_variable("bar"), nullptr);

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    ASSERT_NE(variable, nullptr);
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<char>(variable_value->data));
    ASSERT_EQ(std::get<char>(variable_value->data), '\n');
}

TEST(variable_must_be_initialized_appropriately, headless_universe_unnamed_variable_float_0_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    float float_zero = 0.0f;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(float_zero));
    ASSERT_FALSE(application.get_universe().has_variable("foo"));
    ASSERT_EQ(application.get_universe().get_variable("foo"), nullptr);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_float_0_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    float float_zero = 0.0f;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(float_zero));
    ASSERT_TRUE(application.get_universe().has_variable("foo"));
    ASSERT_NE(application.get_universe().get_variable("foo"), nullptr);
    ASSERT_FALSE(application.get_universe().has_variable("bar"));
    ASSERT_EQ(application.get_universe().get_variable("bar"), nullptr);

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    ASSERT_NE(variable, nullptr);
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<float>(variable_value->data));
    ASSERT_EQ(std::get<float>(variable_value->data), 0.0f);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_float_positive_infinity_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    float float_positive_infinity = std::numeric_limits<float>::infinity();
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(float_positive_infinity));
    ASSERT_TRUE(application.get_universe().has_variable("foo"));
    ASSERT_NE(application.get_universe().get_variable("foo"), nullptr);
    ASSERT_FALSE(application.get_universe().has_variable("bar"));
    ASSERT_EQ(application.get_universe().get_variable("bar"), nullptr);

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    ASSERT_NE(variable, nullptr);
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<float>(variable_value->data));
    ASSERT_EQ(std::get<float>(variable_value->data), std::numeric_limits<float>::infinity());
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_float_negative_infinity_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    float float_negative_infinity = -1.0f * std::numeric_limits<float>::infinity();
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(float_negative_infinity));
    ASSERT_TRUE(application.get_universe().has_variable("foo"));
    ASSERT_NE(application.get_universe().get_variable("foo"), nullptr);
    ASSERT_FALSE(application.get_universe().has_variable("bar"));
    ASSERT_EQ(application.get_universe().get_variable("bar"), nullptr);

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    ASSERT_NE(variable, nullptr);
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<float>(variable_value->data));
    ASSERT_EQ(std::get<float>(variable_value->data), -1.0f * std::numeric_limits<float>::infinity());
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_float_nan_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    float float_nan = NAN;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(float_nan));
    ASSERT_TRUE(application.get_universe().has_variable("foo"));
    ASSERT_NE(application.get_universe().get_variable("foo"), nullptr);
    ASSERT_FALSE(application.get_universe().has_variable("bar"));
    ASSERT_EQ(application.get_universe().get_variable("bar"), nullptr);

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    ASSERT_NE(variable, nullptr);
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<float>(variable_value->data));
    ASSERT_TRUE(std::isnan(std::get<float>(variable_value->data)));
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_TRUE(std::holds_alternative<float>(variable->get()->data));
    ASSERT_TRUE(std::isnan(std::get<float>(variable->get()->data)));
}

TEST(variable_must_be_initialized_appropriately, headless_universe_unnamed_variable_double_0_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    double double_zero = 0.0;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(double_zero));
    ASSERT_FALSE(application.get_universe().has_variable("foo"));
    ASSERT_EQ(application.get_universe().get_variable("foo"), nullptr);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_double_0_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    double double_zero = 0.0;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(double_zero));
    ASSERT_TRUE(application.get_universe().has_variable("foo"));
    ASSERT_NE(application.get_universe().get_variable("foo"), nullptr);
    ASSERT_FALSE(application.get_universe().has_variable("bar"));
    ASSERT_EQ(application.get_universe().get_variable("bar"), nullptr);

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    ASSERT_NE(variable, nullptr);
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<double>(variable_value->data));
    ASSERT_EQ(std::get<double>(variable_value->data), 0.0);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_double_positive_infinity_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    double double_positive_infinity = std::numeric_limits<double>::infinity();
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(double_positive_infinity));
    ASSERT_TRUE(application.get_universe().has_variable("foo"));
    ASSERT_NE(application.get_universe().get_variable("foo"), nullptr);
    ASSERT_FALSE(application.get_universe().has_variable("bar"));
    ASSERT_EQ(application.get_universe().get_variable("bar"), nullptr);

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    ASSERT_NE(variable, nullptr);
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<double>(variable_value->data));
    ASSERT_EQ(std::get<double>(variable_value->data), std::numeric_limits<double>::infinity());
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_double_negative_infinity_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    double double_negative_infinity = -1.0 * std::numeric_limits<double>::infinity();
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(double_negative_infinity));
    ASSERT_TRUE(application.get_universe().has_variable("foo"));
    ASSERT_NE(application.get_universe().get_variable("foo"), nullptr);
    ASSERT_FALSE(application.get_universe().has_variable("bar"));
    ASSERT_EQ(application.get_universe().get_variable("bar"), nullptr);

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    ASSERT_NE(variable, nullptr);
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<double>(variable_value->data));
    ASSERT_EQ(std::get<double>(variable_value->data), -1.0 * std::numeric_limits<double>::infinity());
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_double_nan_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    double double_nan = NAN;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(double_nan));
    ASSERT_TRUE(application.get_universe().has_variable("foo"));
    ASSERT_NE(application.get_universe().get_variable("foo"), nullptr);
    ASSERT_FALSE(application.get_universe().has_variable("bar"));
    ASSERT_EQ(application.get_universe().get_variable("bar"), nullptr);

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    ASSERT_NE(variable, nullptr);
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<double>(variable_value->data));
    ASSERT_TRUE(std::isnan(std::get<double>(variable_value->data)));
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_TRUE(std::holds_alternative<double>(variable->get()->data));
    ASSERT_TRUE(std::isnan(std::get<double>(variable->get()->data)));
}

TEST(variable_must_be_initialized_appropriately, headless_universe_unnamed_variable_int32_t_0_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    int32_t int32_t_zero = 0;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(int32_t_zero));
    ASSERT_FALSE(application.get_universe().has_variable("foo"));
    ASSERT_EQ(application.get_universe().get_variable("foo"), nullptr);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_int32_t_0_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    int32_t int32_t_zero = 0;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(int32_t_zero));
    ASSERT_TRUE(application.get_universe().has_variable("foo"));
    ASSERT_NE(application.get_universe().get_variable("foo"), nullptr);
    ASSERT_FALSE(application.get_universe().has_variable("bar"));
    ASSERT_EQ(application.get_universe().get_variable("bar"), nullptr);

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    ASSERT_NE(variable, nullptr);
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<int32_t>(variable_value->data));
    ASSERT_EQ(std::get<int32_t>(variable_value->data), 0);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_unnamed_variable_int32_t_plus_1_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    int32_t int32_t_plus_1 = 1;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(int32_t_plus_1));
    ASSERT_FALSE(application.get_universe().has_variable("foo"));
    ASSERT_EQ(application.get_universe().get_variable("foo"), nullptr);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_int32_t_plus_1_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    int32_t int32_t_plus_1 = 1;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(int32_t_plus_1));
    ASSERT_TRUE(application.get_universe().has_variable("foo"));
    ASSERT_NE(application.get_universe().get_variable("foo"), nullptr);
    ASSERT_FALSE(application.get_universe().has_variable("bar"));
    ASSERT_EQ(application.get_universe().get_variable("bar"), nullptr);

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    ASSERT_NE(variable, nullptr);
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<int32_t>(variable_value->data));
    ASSERT_EQ(std::get<int32_t>(variable_value->data), 1);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_unnamed_variable_int32_t_minus_1_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    int32_t int32_t_minus_1 = -1;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(int32_t_minus_1));
    ASSERT_FALSE(application.get_universe().has_variable("foo"));
    ASSERT_EQ(application.get_universe().get_variable("foo"), nullptr);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_int32_t_minus_1_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    int32_t int32_t_minus_1 = -1;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(int32_t_minus_1));
    ASSERT_TRUE(application.get_universe().has_variable("foo"));
    ASSERT_NE(application.get_universe().get_variable("foo"), nullptr);
    ASSERT_FALSE(application.get_universe().has_variable("bar"));
    ASSERT_EQ(application.get_universe().get_variable("bar"), nullptr);

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    ASSERT_NE(variable, nullptr);
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<int32_t>(variable_value->data));
    ASSERT_EQ(std::get<int32_t>(variable_value->data), -1);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_unnamed_variable_int32_t_max_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    int32_t int32_t_max = std::numeric_limits<int32_t>::max();
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(int32_t_max));
    ASSERT_FALSE(application.get_universe().has_variable("foo"));
    ASSERT_EQ(application.get_universe().get_variable("foo"), nullptr);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_int32_t_max_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    int32_t int32_t_max = std::numeric_limits<int32_t>::max();
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(int32_t_max));
    ASSERT_TRUE(application.get_universe().has_variable("foo"));
    ASSERT_NE(application.get_universe().get_variable("foo"), nullptr);
    ASSERT_FALSE(application.get_universe().has_variable("bar"));
    ASSERT_EQ(application.get_universe().get_variable("bar"), nullptr);

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    ASSERT_NE(variable, nullptr);
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<int32_t>(variable_value->data));
    ASSERT_EQ(std::get<int32_t>(variable_value->data), std::numeric_limits<int32_t>::max());
}

TEST(variable_must_be_initialized_appropriately, headless_universe_unnamed_variable_int32_t_min_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    int32_t int32_t_min = std::numeric_limits<int32_t>::min();
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(int32_t_min));
    ASSERT_FALSE(application.get_universe().has_variable("foo"));
    ASSERT_EQ(application.get_universe().get_variable("foo"), nullptr);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_int32_t_min_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    int32_t int32_t_min = std::numeric_limits<int32_t>::min();
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(int32_t_min));
    ASSERT_TRUE(application.get_universe().has_variable("foo"));
    ASSERT_NE(application.get_universe().get_variable("foo"), nullptr);
    ASSERT_FALSE(application.get_universe().has_variable("bar"));
    ASSERT_EQ(application.get_universe().get_variable("bar"), nullptr);

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    ASSERT_NE(variable, nullptr);
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<int32_t>(variable_value->data));
    ASSERT_EQ(std::get<int32_t>(variable_value->data), std::numeric_limits<int32_t>::min());
}

TEST(variable_must_be_initialized_appropriately, headless_universe_unnamed_variable_uint32_t_0_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    uint32_t uint32_t_zero = 0;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(uint32_t_zero));
    ASSERT_FALSE(application.get_universe().has_variable("foo"));
    ASSERT_EQ(application.get_universe().get_variable("foo"), nullptr);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_uint32_t_0_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    uint32_t uint32_t_zero = 0;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(uint32_t_zero));
    ASSERT_TRUE(application.get_universe().has_variable("foo"));
    ASSERT_NE(application.get_universe().get_variable("foo"), nullptr);
    ASSERT_FALSE(application.get_universe().has_variable("bar"));
    ASSERT_EQ(application.get_universe().get_variable("bar"), nullptr);

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    ASSERT_NE(variable, nullptr);
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<uint32_t>(variable_value->data));
    ASSERT_EQ(std::get<uint32_t>(variable_value->data), 0);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_unnamed_variable_uint32_t_plus_1_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    uint32_t uint32_t_plus_1 = 1;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(uint32_t_plus_1));
    ASSERT_FALSE(application.get_universe().has_variable("foo"));
    ASSERT_EQ(application.get_universe().get_variable("foo"), nullptr);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_uint32_t_plus_1_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    uint32_t uint32_t_plus_1 = 1;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(uint32_t_plus_1));
    ASSERT_TRUE(application.get_universe().has_variable("foo"));
    ASSERT_NE(application.get_universe().get_variable("foo"), nullptr);
    ASSERT_FALSE(application.get_universe().has_variable("bar"));
    ASSERT_EQ(application.get_universe().get_variable("bar"), nullptr);

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    ASSERT_NE(variable, nullptr);
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<uint32_t>(variable_value->data));
    ASSERT_EQ(std::get<uint32_t>(variable_value->data), 1);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_unnamed_variable_uint32_t_max_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    uint32_t uint32_t_max = std::numeric_limits<uint32_t>::max();
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(uint32_t_max));
    ASSERT_FALSE(application.get_universe().has_variable("foo"));
    ASSERT_EQ(application.get_universe().get_variable("foo"), nullptr);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_named_variable_uint32_t_max_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    uint32_t uint32_t_max = std::numeric_limits<uint32_t>::max();
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(uint32_t_max));
    ASSERT_TRUE(application.get_universe().has_variable("foo"));
    ASSERT_NE(application.get_universe().get_variable("foo"), nullptr);
    ASSERT_FALSE(application.get_universe().has_variable("bar"));
    ASSERT_EQ(application.get_universe().get_variable("bar"), nullptr);

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    ASSERT_NE(variable, nullptr);
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<uint32_t>(variable_value->data));
    ASSERT_EQ(std::get<uint32_t>(variable_value->data), std::numeric_limits<uint32_t>::max());
}

TEST(variable_must_be_initialized_appropriately, headless_universe_variable_universe_x_float_1234_dot_25_with_activate_callback_and_read_callback)
{
    mock::MockApplication application;

    // Creating a `Scene` also creates its default `Camera` and makes the `Scene` the active `Scene` if there is none.
    yli::ontology::SceneStruct scene_struct;
    application.get_generic_entity_factory().create_scene(scene_struct);

    float x = 1234.25f;
    yli::ontology::VariableStruct x_variable_struct(application.get_universe(), &application.get_universe());
    x_variable_struct.local_name = "x";
    x_variable_struct.activate_callback = &yli::ontology::activate_x;
    x_variable_struct.read_callback = &yli::ontology::read_x;
    x_variable_struct.should_call_activate_callback_now = true;
    ASSERT_EQ(application.get_universe().get_variable("x"), nullptr);
    application.get_universe().create_variable(x_variable_struct, yli::data::AnyValue(x));

    ASSERT_NE(application.get_universe().get_variable("x"), nullptr);
    yli::ontology::Variable* x_variable = application.get_universe().get_variable("x");
    ASSERT_NE(x_variable, nullptr);

    std::optional<yli::data::AnyValue> x_value = x_variable->get();
    ASSERT_NE(x_value, std::nullopt);
    ASSERT_TRUE(std::holds_alternative<float>(x_value->data));
    ASSERT_EQ(std::get<float>(x_value->data), 1234.25f);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_variable_universe_y_float_1234_dot_25_with_activate_callback_and_read_callback)
{
    mock::MockApplication application;

    // Creating a `Scene` also creates its default `Camera` and makes the `Scene` the active `Scene` if there is none.
    yli::ontology::SceneStruct scene_struct;
    application.get_generic_entity_factory().create_scene(scene_struct);

    float y = 1234.25f;
    yli::ontology::VariableStruct y_variable_struct(application.get_universe(), &application.get_universe());
    y_variable_struct.local_name = "y";
    y_variable_struct.activate_callback = &yli::ontology::activate_y;
    y_variable_struct.read_callback = &yli::ontology::read_y;
    y_variable_struct.should_call_activate_callback_now = true;
    ASSERT_EQ(application.get_universe().get_variable("y"), nullptr);
    application.get_universe().create_variable(y_variable_struct, yli::data::AnyValue(y));

    ASSERT_NE(application.get_universe().get_variable("y"), nullptr);
    yli::ontology::Variable* y_variable = application.get_universe().get_variable("y");
    ASSERT_NE(y_variable, nullptr);

    std::optional<yli::data::AnyValue> y_value = y_variable->get();
    ASSERT_NE(y_value, std::nullopt);
    ASSERT_TRUE(std::holds_alternative<float>(y_value->data));
    ASSERT_EQ(std::get<float>(y_value->data), 1234.25f);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_variable_universe_z_float_1234_dot_25_with_activate_callback_and_read_callback)
{
    mock::MockApplication application;

    // Creating a `Scene` also creates its default `Camera` and makes the `Scene` the active `Scene` if there is none.
    yli::ontology::SceneStruct scene_struct;
    application.get_generic_entity_factory().create_scene(scene_struct);

    float z = 1234.25f;
    yli::ontology::VariableStruct z_variable_struct(application.get_universe(), &application.get_universe());
    z_variable_struct.local_name = "z";
    z_variable_struct.activate_callback = &yli::ontology::activate_z;
    z_variable_struct.read_callback = &yli::ontology::read_z;
    z_variable_struct.should_call_activate_callback_now = true;
    ASSERT_EQ(application.get_universe().get_variable("z"), nullptr);
    application.get_universe().create_variable(z_variable_struct, yli::data::AnyValue(z));

    ASSERT_NE(application.get_universe().get_variable("z"), nullptr);
    yli::ontology::Variable* z_variable = application.get_universe().get_variable("z");
    ASSERT_NE(z_variable, nullptr);

    std::optional<yli::data::AnyValue> z_value = z_variable->get();
    ASSERT_NE(z_value, std::nullopt);
    ASSERT_TRUE(std::holds_alternative<float>(z_value->data));
    ASSERT_EQ(std::get<float>(z_value->data), 1234.25f);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_variable_universe_red_float_0_dot_0_with_activate_callback)
{
    mock::MockApplication application;

    float red = 0.0f;
    yli::ontology::VariableStruct red_variable_struct(application.get_universe(), &application.get_universe());
    red_variable_struct.local_name = "red";
    red_variable_struct.activate_callback = &yli::ontology::Variable::activate_background_color;
    red_variable_struct.should_call_activate_callback_now = true;
    ASSERT_EQ(application.get_universe().get_variable("red"), nullptr);
    application.get_universe().create_variable(red_variable_struct, yli::data::AnyValue(red));

    ASSERT_NE(application.get_universe().get_variable("red"), nullptr);
    yli::ontology::Variable* red_variable = application.get_universe().get_variable("red");
    ASSERT_NE(red_variable, nullptr);

    ASSERT_EQ(red_variable->variable_value, *red_variable->get());
    std::optional<yli::data::AnyValue> red_value = red_variable->get();
    ASSERT_NE(red_value, std::nullopt);
    ASSERT_TRUE(std::holds_alternative<float>(red_value->data));
    ASSERT_EQ(std::get<float>(red_value->data), 0.0f);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_variable_universe_red_float_1_dot_0_with_activate_callback)
{
    mock::MockApplication application;

    float red = 1.0f;
    yli::ontology::VariableStruct red_variable_struct(application.get_universe(), &application.get_universe());
    red_variable_struct.local_name = "red";
    red_variable_struct.activate_callback = &yli::ontology::Variable::activate_background_color;
    red_variable_struct.should_call_activate_callback_now = true;
    ASSERT_EQ(application.get_universe().get_variable("red"), nullptr);
    application.get_universe().create_variable(red_variable_struct, yli::data::AnyValue(red));

    ASSERT_NE(application.get_universe().get_variable("red"), nullptr);
    yli::ontology::Variable* red_variable = application.get_universe().get_variable("red");
    ASSERT_NE(red_variable, nullptr);

    ASSERT_EQ(red_variable->variable_value, *red_variable->get());
    std::optional<yli::data::AnyValue> red_value = red_variable->get();
    ASSERT_NE(red_value, std::nullopt);
    ASSERT_TRUE(std::holds_alternative<float>(red_value->data));
    ASSERT_EQ(std::get<float>(red_value->data), 1.0f);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_variable_universe_red_float_0_dot_875_with_activate_callback)
{
    mock::MockApplication application;

    float red = 0.875f;
    yli::ontology::VariableStruct red_variable_struct(application.get_universe(), &application.get_universe());
    red_variable_struct.local_name = "red";
    red_variable_struct.activate_callback = &yli::ontology::Variable::activate_background_color;
    red_variable_struct.should_call_activate_callback_now = true;
    ASSERT_EQ(application.get_universe().get_variable("red"), nullptr);
    application.get_universe().create_variable(red_variable_struct, yli::data::AnyValue(red));

    ASSERT_NE(application.get_universe().get_variable("red"), nullptr);
    yli::ontology::Variable* red_variable = application.get_universe().get_variable("red");
    ASSERT_NE(red_variable, nullptr);

    ASSERT_EQ(red_variable->variable_value, *red_variable->get());
    std::optional<yli::data::AnyValue> red_value = red_variable->get();
    ASSERT_NE(red_value, std::nullopt);
    ASSERT_TRUE(std::holds_alternative<float>(red_value->data));
    ASSERT_EQ(std::get<float>(red_value->data), 0.875f);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_variable_universe_green_float_0_dot_0_with_activate_callback)
{
    mock::MockApplication application;

    float green = 0.0f;
    yli::ontology::VariableStruct green_variable_struct(application.get_universe(), &application.get_universe());
    green_variable_struct.local_name = "green";
    green_variable_struct.activate_callback = &yli::ontology::Variable::activate_background_color;
    green_variable_struct.should_call_activate_callback_now = true;
    ASSERT_EQ(application.get_universe().get_variable("green"), nullptr);
    application.get_universe().create_variable(green_variable_struct, yli::data::AnyValue(green));

    ASSERT_NE(application.get_universe().get_variable("green"), nullptr);
    yli::ontology::Variable* green_variable = application.get_universe().get_variable("green");
    ASSERT_NE(green_variable, nullptr);

    ASSERT_EQ(green_variable->variable_value, *green_variable->get());
    std::optional<yli::data::AnyValue> green_value = green_variable->get();
    ASSERT_NE(green_value, std::nullopt);
    ASSERT_TRUE(std::holds_alternative<float>(green_value->data));
    ASSERT_EQ(std::get<float>(green_value->data), 0.0f);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_variable_universe_green_float_1_dot_0_with_activate_callback)
{
    mock::MockApplication application;

    float green = 1.0f;
    yli::ontology::VariableStruct green_variable_struct(application.get_universe(), &application.get_universe());
    green_variable_struct.local_name = "green";
    green_variable_struct.activate_callback = &yli::ontology::Variable::activate_background_color;
    green_variable_struct.should_call_activate_callback_now = true;
    ASSERT_EQ(application.get_universe().get_variable("green"), nullptr);
    application.get_universe().create_variable(green_variable_struct, yli::data::AnyValue(green));

    ASSERT_NE(application.get_universe().get_variable("green"), nullptr);
    yli::ontology::Variable* green_variable = application.get_universe().get_variable("green");
    ASSERT_NE(green_variable, nullptr);

    ASSERT_EQ(green_variable->variable_value, *green_variable->get());
    std::optional<yli::data::AnyValue> green_value = green_variable->get();
    ASSERT_NE(green_value, std::nullopt);
    ASSERT_TRUE(std::holds_alternative<float>(green_value->data));
    ASSERT_EQ(std::get<float>(green_value->data), 1.0f);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_variable_universe_green_float_0_dot_875_with_activate_callback)
{
    mock::MockApplication application;

    float green = 0.875f;
    yli::ontology::VariableStruct green_variable_struct(application.get_universe(), &application.get_universe());
    green_variable_struct.local_name = "green";
    green_variable_struct.activate_callback = &yli::ontology::Variable::activate_background_color;
    green_variable_struct.should_call_activate_callback_now = true;
    ASSERT_EQ(application.get_universe().get_variable("green"), nullptr);
    application.get_universe().create_variable(green_variable_struct, yli::data::AnyValue(green));

    ASSERT_NE(application.get_universe().get_variable("green"), nullptr);
    yli::ontology::Variable* green_variable = application.get_universe().get_variable("green");
    ASSERT_NE(green_variable, nullptr);

    ASSERT_EQ(green_variable->variable_value, *green_variable->get());
    std::optional<yli::data::AnyValue> green_value = green_variable->get();
    ASSERT_NE(green_value, std::nullopt);
    ASSERT_TRUE(std::holds_alternative<float>(green_value->data));
    ASSERT_EQ(std::get<float>(green_value->data), 0.875f);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_variable_universe_blue_float_0_dot_0_with_activate_callback)
{
    mock::MockApplication application;

    float blue = 0.0f;
    yli::ontology::VariableStruct blue_variable_struct(application.get_universe(), &application.get_universe());
    blue_variable_struct.local_name = "blue";
    blue_variable_struct.activate_callback = &yli::ontology::Variable::activate_background_color;
    blue_variable_struct.should_call_activate_callback_now = true;
    ASSERT_EQ(application.get_universe().get_variable("blue"), nullptr);
    application.get_universe().create_variable(blue_variable_struct, yli::data::AnyValue(blue));

    ASSERT_NE(application.get_universe().get_variable("blue"), nullptr);
    yli::ontology::Variable* blue_variable = application.get_universe().get_variable("blue");
    ASSERT_NE(blue_variable, nullptr);

    ASSERT_EQ(blue_variable->variable_value, *blue_variable->get());
    std::optional<yli::data::AnyValue> blue_value = blue_variable->get();
    ASSERT_NE(blue_value, std::nullopt);
    ASSERT_TRUE(std::holds_alternative<float>(blue_value->data));
    ASSERT_EQ(std::get<float>(blue_value->data), 0.0f);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_variable_universe_blue_float_1_dot_0_with_activate_callback)
{
    mock::MockApplication application;

    float blue = 1.0f;
    yli::ontology::VariableStruct blue_variable_struct(application.get_universe(), &application.get_universe());
    blue_variable_struct.local_name = "blue";
    blue_variable_struct.activate_callback = &yli::ontology::Variable::activate_background_color;
    blue_variable_struct.should_call_activate_callback_now = true;
    ASSERT_EQ(application.get_universe().get_variable("blue"), nullptr);
    application.get_universe().create_variable(blue_variable_struct, yli::data::AnyValue(blue));

    ASSERT_NE(application.get_universe().get_variable("blue"), nullptr);
    yli::ontology::Variable* blue_variable = application.get_universe().get_variable("blue");
    ASSERT_NE(blue_variable, nullptr);

    ASSERT_EQ(blue_variable->variable_value, *blue_variable->get());
    std::optional<yli::data::AnyValue> blue_value = blue_variable->get();
    ASSERT_NE(blue_value, std::nullopt);
    ASSERT_TRUE(std::holds_alternative<float>(blue_value->data));
    ASSERT_EQ(std::get<float>(blue_value->data), 1.0f);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_variable_universe_blue_float_0_dot_875_with_activate_callback)
{
    mock::MockApplication application;

    float blue = 0.875f;
    yli::ontology::VariableStruct blue_variable_struct(application.get_universe(), &application.get_universe());
    blue_variable_struct.local_name = "blue";
    blue_variable_struct.activate_callback = &yli::ontology::Variable::activate_background_color;
    blue_variable_struct.should_call_activate_callback_now = true;
    ASSERT_EQ(application.get_universe().get_variable("blue"), nullptr);
    application.get_universe().create_variable(blue_variable_struct, yli::data::AnyValue(blue));

    ASSERT_NE(application.get_universe().get_variable("blue"), nullptr);
    yli::ontology::Variable* blue_variable = application.get_universe().get_variable("blue");
    ASSERT_NE(blue_variable, nullptr);

    ASSERT_EQ(blue_variable->variable_value, *blue_variable->get());
    std::optional<yli::data::AnyValue> blue_value = blue_variable->get();
    ASSERT_NE(blue_value, std::nullopt);
    ASSERT_TRUE(std::holds_alternative<float>(blue_value->data));
    ASSERT_EQ(std::get<float>(blue_value->data), 0.875f);
}

TEST(variables_must_be_initialized_appropriately, headless_universe_variable_universe_cartesian_coordinates_x_y_z_activate_callbacks_and_read_callbacks)
{
    mock::MockApplication application;

    // Creating a `Scene` also creates its default `Camera` and makes the `Scene` the active `Scene` if there is none.
    yli::ontology::SceneStruct scene_struct;
    application.get_generic_entity_factory().create_scene(scene_struct);

    float x = 1234.25f;
    float y = 2345.50f;
    float z = 3456.75f;

    yli::ontology::VariableStruct cartesian_coordinates_variable_struct(application.get_universe(), &application.get_universe());
    cartesian_coordinates_variable_struct.local_name = "cartesian";
    cartesian_coordinates_variable_struct.activate_callback = &yli::ontology::activate_cartesian_coordinates;
    cartesian_coordinates_variable_struct.read_callback = &yli::ontology::read_cartesian_coordinates;
    cartesian_coordinates_variable_struct.should_call_activate_callback_now = false;
    application.get_universe().create_variable(cartesian_coordinates_variable_struct, yli::data::AnyValue(glm::vec3(NAN, NAN, NAN)));

    yli::ontology::VariableStruct x_variable_struct(application.get_universe(), &application.get_universe());
    x_variable_struct.local_name = "x";
    x_variable_struct.activate_callback = &yli::ontology::activate_x;
    x_variable_struct.read_callback = &yli::ontology::read_x;
    x_variable_struct.should_call_activate_callback_now = true;
    application.get_universe().create_variable(x_variable_struct, yli::data::AnyValue(x));

    yli::ontology::VariableStruct y_variable_struct(application.get_universe(), &application.get_universe());
    y_variable_struct.local_name = "y";
    y_variable_struct.activate_callback = &yli::ontology::activate_y;
    y_variable_struct.read_callback = &yli::ontology::read_y;
    y_variable_struct.should_call_activate_callback_now = true;
    application.get_universe().create_variable(y_variable_struct, yli::data::AnyValue(y));

    yli::ontology::VariableStruct z_variable_struct(application.get_universe(), &application.get_universe());
    z_variable_struct.local_name = "z";
    z_variable_struct.activate_callback = &yli::ontology::activate_z;
    z_variable_struct.read_callback = &yli::ontology::read_z;
    z_variable_struct.should_call_activate_callback_now = true;
    application.get_universe().create_variable(z_variable_struct, yli::data::AnyValue(z));

    ASSERT_NE(application.get_universe().get_variable("x"), nullptr);
    yli::ontology::Variable* x_variable = application.get_universe().get_variable("x");
    ASSERT_NE(x_variable, nullptr);
    std::optional<yli::data::AnyValue> x_value = x_variable->get();
    ASSERT_NE(x_value, std::nullopt);
    ASSERT_TRUE(std::holds_alternative<float>(x_value->data));
    ASSERT_EQ(std::get<float>(x_value->data), 1234.25f);

    ASSERT_NE(application.get_universe().get_variable("y"), nullptr);
    yli::ontology::Variable* y_variable = application.get_universe().get_variable("y");
    ASSERT_NE(y_variable, nullptr);
    std::optional<yli::data::AnyValue> y_value = y_variable->get();
    ASSERT_NE(y_value, std::nullopt);
    ASSERT_TRUE(std::holds_alternative<float>(y_value->data));
    ASSERT_EQ(std::get<float>(y_value->data), 2345.50f);

    ASSERT_NE(application.get_universe().get_variable("z"), nullptr);
    yli::ontology::Variable* z_variable = application.get_universe().get_variable("z");
    ASSERT_NE(z_variable, nullptr);
    std::optional<yli::data::AnyValue> z_value = z_variable->get();
    ASSERT_NE(z_value, std::nullopt);
    ASSERT_TRUE(std::holds_alternative<float>(z_value->data));
    ASSERT_EQ(std::get<float>(z_value->data), 3456.75f);

    ASSERT_NE(application.get_universe().get_variable("cartesian"), nullptr);
    yli::ontology::Variable* cartesian_coordinates_variable = application.get_universe().get_variable("cartesian");
    ASSERT_NE(cartesian_coordinates_variable, nullptr);
    std::optional<yli::data::AnyValue> cartesian_coordinates_value = cartesian_coordinates_variable->get();
    ASSERT_NE(cartesian_coordinates_value, std::nullopt);
    ASSERT_TRUE(std::holds_alternative<std::reference_wrapper<const glm::vec3>>(cartesian_coordinates_value->data));
    ASSERT_EQ(std::get<std::reference_wrapper<const glm::vec3>>(cartesian_coordinates_value->data).get(), glm::vec3(1234.25f, 2345.50f, 3456.75f));
}

TEST(variables_must_be_initialized_appropriately, headless_universe_variable_universe_x_y_z_cartesian_coordinates_activate_callbacks_and_read_callbacks)
{
    mock::MockApplication application;

    // Creating a `Scene` also creates its default `Camera` and makes the `Scene` the active `Scene` if there is none.
    yli::ontology::SceneStruct scene_struct;
    application.get_generic_entity_factory().create_scene(scene_struct);

    float x = 1234.25f;
    float y = 2345.50f;
    float z = 3456.75f;

    yli::ontology::VariableStruct x_variable_struct(application.get_universe(), &application.get_universe());
    x_variable_struct.local_name = "x";
    x_variable_struct.activate_callback = &yli::ontology::activate_x;
    x_variable_struct.read_callback = &yli::ontology::read_x;
    x_variable_struct.should_call_activate_callback_now = true;
    application.get_universe().create_variable(x_variable_struct, yli::data::AnyValue(x));

    yli::ontology::VariableStruct y_variable_struct(application.get_universe(), &application.get_universe());
    y_variable_struct.local_name = "y";
    y_variable_struct.activate_callback = &yli::ontology::activate_y;
    y_variable_struct.read_callback = &yli::ontology::read_y;
    y_variable_struct.should_call_activate_callback_now = true;
    application.get_universe().create_variable(y_variable_struct, yli::data::AnyValue(y));

    yli::ontology::VariableStruct z_variable_struct(application.get_universe(), &application.get_universe());
    z_variable_struct.local_name = "z";
    z_variable_struct.activate_callback = &yli::ontology::activate_z;
    z_variable_struct.read_callback = &yli::ontology::read_z;
    z_variable_struct.should_call_activate_callback_now = true;
    application.get_universe().create_variable(z_variable_struct, yli::data::AnyValue(z));

    yli::ontology::VariableStruct cartesian_coordinates_variable_struct(application.get_universe(), &application.get_universe());
    cartesian_coordinates_variable_struct.local_name = "cartesian";
    cartesian_coordinates_variable_struct.activate_callback = &yli::ontology::activate_cartesian_coordinates;
    cartesian_coordinates_variable_struct.read_callback = &yli::ontology::read_cartesian_coordinates;
    cartesian_coordinates_variable_struct.should_call_activate_callback_now = false;
    application.get_universe().create_variable(cartesian_coordinates_variable_struct, yli::data::AnyValue(glm::vec3(NAN, NAN, NAN)));

    ASSERT_NE(application.get_universe().get_variable("x"), nullptr);
    yli::ontology::Variable* x_variable = application.get_universe().get_variable("x");
    ASSERT_NE(x_variable, nullptr);
    std::optional<yli::data::AnyValue> x_value = x_variable->get();
    ASSERT_NE(x_value, std::nullopt);
    ASSERT_TRUE(std::holds_alternative<float>(x_value->data));
    ASSERT_EQ(std::get<float>(x_value->data), 1234.25f);

    ASSERT_NE(application.get_universe().get_variable("y"), nullptr);
    yli::ontology::Variable* y_variable = application.get_universe().get_variable("y");
    ASSERT_NE(y_variable, nullptr);
    std::optional<yli::data::AnyValue> y_value = y_variable->get();
    ASSERT_NE(y_value, std::nullopt);
    ASSERT_TRUE(std::holds_alternative<float>(y_value->data));
    ASSERT_EQ(std::get<float>(y_value->data), 2345.50f);

    ASSERT_NE(application.get_universe().get_variable("z"), nullptr);
    yli::ontology::Variable* z_variable = application.get_universe().get_variable("z");
    ASSERT_NE(z_variable, nullptr);
    std::optional<yli::data::AnyValue> z_value = z_variable->get();
    ASSERT_NE(z_value, std::nullopt);
    ASSERT_TRUE(std::holds_alternative<float>(z_value->data));
    ASSERT_EQ(std::get<float>(z_value->data), 3456.75f);

    ASSERT_NE(application.get_universe().get_variable("cartesian"), nullptr);
    yli::ontology::Variable* cartesian_coordinates_variable = application.get_universe().get_variable("cartesian");
    ASSERT_NE(cartesian_coordinates_variable, nullptr);
    std::optional<yli::data::AnyValue> cartesian_coordinates_value = cartesian_coordinates_variable->get();
    ASSERT_NE(cartesian_coordinates_value, std::nullopt);
    ASSERT_TRUE(std::holds_alternative<std::reference_wrapper<const glm::vec3>>(cartesian_coordinates_value->data));
    ASSERT_EQ(std::get<std::reference_wrapper<const glm::vec3>>(cartesian_coordinates_value->data).get(), glm::vec3(1234.25f, 2345.50f, 3456.75f));
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_variable_universe_x_y_z_cartesian_coordinates_activate_callbacks_and_read_callbacks)
{
    mock::MockApplication application;

    // Creating a `Scene` also creates its default `Camera` and makes the `Scene` the active `Scene` if there is none.
    yli::ontology::SceneStruct scene_struct;
    application.get_generic_entity_factory().create_scene(scene_struct);

    float x = 1234.25f;
    float y = 2345.50f;
    float z = 3456.75f;

    yli::ontology::VariableStruct x_variable_struct(application.get_universe(), &application.get_universe());
    x_variable_struct.local_name = "x";
    x_variable_struct.activate_callback = &yli::ontology::activate_x;
    x_variable_struct.read_callback = &yli::ontology::read_x;
    x_variable_struct.should_call_activate_callback_now = true;
    application.get_universe().create_variable(x_variable_struct, yli::data::AnyValue(x));

    yli::ontology::VariableStruct y_variable_struct(application.get_universe(), &application.get_universe());
    y_variable_struct.local_name = "y";
    y_variable_struct.activate_callback = &yli::ontology::activate_y;
    y_variable_struct.read_callback = &yli::ontology::read_y;
    y_variable_struct.should_call_activate_callback_now = true;
    application.get_universe().create_variable(y_variable_struct, yli::data::AnyValue(y));

    yli::ontology::VariableStruct z_variable_struct(application.get_universe(), &application.get_universe());
    z_variable_struct.local_name = "z";
    z_variable_struct.activate_callback = &yli::ontology::activate_z;
    z_variable_struct.read_callback = &yli::ontology::read_z;
    z_variable_struct.should_call_activate_callback_now = true;
    application.get_universe().create_variable(z_variable_struct, yli::data::AnyValue(z));

    yli::ontology::VariableStruct cartesian_coordinates_variable_struct(application.get_universe(), &application.get_universe());
    cartesian_coordinates_variable_struct.local_name = "cartesian";
    cartesian_coordinates_variable_struct.activate_callback = &yli::ontology::activate_cartesian_coordinates;
    cartesian_coordinates_variable_struct.read_callback = &yli::ontology::read_cartesian_coordinates;
    cartesian_coordinates_variable_struct.should_call_activate_callback_now = false;
    application.get_universe().create_variable(cartesian_coordinates_variable_struct, yli::data::AnyValue(glm::vec3(NAN, NAN, NAN)));

    yli::ontology::Variable* x_variable = application.get_universe().get_variable("x");
    yli::ontology::Variable* y_variable = application.get_universe().get_variable("y");
    yli::ontology::Variable* z_variable = application.get_universe().get_variable("z");
    yli::ontology::Variable* cartesian_coordinates_variable = application.get_universe().get_variable("cartesian");

    x_variable->set("0.875");
    std::optional<yli::data::AnyValue> x_value = x_variable->get();
    ASSERT_NE(x_value, std::nullopt);
    ASSERT_TRUE(std::holds_alternative<float>(x_value->data));
    ASSERT_EQ(std::get<float>(x_value->data), 0.875f);
    ASSERT_EQ(std::get<std::reference_wrapper<const glm::vec3>>(cartesian_coordinates_variable->get()->data).get(), glm::vec3(0.875f, 2345.50f, 3456.75f));

    y_variable->set("0.9375");
    std::optional<yli::data::AnyValue> y_value = y_variable->get();
    ASSERT_NE(y_value, std::nullopt);
    ASSERT_TRUE(std::holds_alternative<float>(y_value->data));
    ASSERT_EQ(std::get<float>(y_value->data), 0.9375f);
    ASSERT_EQ(std::get<std::reference_wrapper<const glm::vec3>>(cartesian_coordinates_variable->get()->data).get(), glm::vec3(0.875f, 0.9375f, 3456.75f));

    z_variable->set("0.96875");
    std::optional<yli::data::AnyValue> z_value = z_variable->get();
    ASSERT_NE(z_value, std::nullopt);
    ASSERT_TRUE(std::holds_alternative<float>(z_value->data));
    ASSERT_EQ(std::get<float>(z_value->data), 0.96875f);
    ASSERT_EQ(std::get<std::reference_wrapper<const glm::vec3>>(cartesian_coordinates_variable->get()->data).get(), glm::vec3(0.875f, 0.9375f, 0.96875f));
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_bool_true_new_value_true_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    bool bool_true = true;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(bool_true));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("true");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<bool>(variable_value->data));
    ASSERT_TRUE(std::get<bool>(variable_value->data));
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_bool_true_new_value_false_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    bool bool_true = true;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(bool_true));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("false");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<bool>(variable_value->data));
    ASSERT_FALSE(std::get<bool>(variable_value->data));
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_bool_false_new_value_true_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    bool bool_false = false;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(bool_false));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("true");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<bool>(variable_value->data));
    ASSERT_TRUE(std::get<bool>(variable_value->data));
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_bool_false_new_value_false_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    bool bool_false = false;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(bool_false));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("false");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<bool>(variable_value->data));
    ASSERT_FALSE(std::get<bool>(variable_value->data));
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_bool_true_new_value_foo_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    bool bool_true = true;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(bool_true));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("foo");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<bool>(variable_value->data));
    ASSERT_TRUE(std::get<bool>(variable_value->data));
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_bool_false_new_value_foo_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    bool bool_false = false;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(bool_false));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("foo");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<bool>(variable_value->data));
    ASSERT_FALSE(std::get<bool>(variable_value->data));
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_char_lowercase_a_new_value_a_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    char char_lowercase_a = 'a';
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(char_lowercase_a));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("a");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<char>(variable_value->data));
    ASSERT_EQ(std::get<char>(variable_value->data), 'a');
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_char_lowercase_a_new_value_b_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    char char_lowercase_a = 'a';
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(char_lowercase_a));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("b");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<char>(variable_value->data));
    ASSERT_EQ(std::get<char>(variable_value->data), 'b');
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_char_lowercase_a_new_value_A_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    char char_lowercase_a = 'a';
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(char_lowercase_a));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("A");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<char>(variable_value->data));
    ASSERT_EQ(std::get<char>(variable_value->data), 'A');
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_char_lowercase_a_new_value_space_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    char char_lowercase_a = 'a';
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(char_lowercase_a));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set(" ");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<char>(variable_value->data));
    ASSERT_EQ(std::get<char>(variable_value->data), ' ');
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_char_lowercase_a_new_value_newline_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    char char_lowercase_a = 'a';
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(char_lowercase_a));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("\n");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<char>(variable_value->data));
    ASSERT_EQ(std::get<char>(variable_value->data), '\n');
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_char_lowercase_a_new_value_ba_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    char char_lowercase_a = 'a';
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(char_lowercase_a));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("ba");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<char>(variable_value->data));
    ASSERT_EQ(std::get<char>(variable_value->data), 'a');
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_char_lowercase_a_new_value_bb_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    char char_lowercase_a = 'a';
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(char_lowercase_a));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("bb");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<char>(variable_value->data));
    ASSERT_EQ(std::get<char>(variable_value->data), 'a');
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_char_lowercase_a_new_value_bc_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    char char_lowercase_a = 'a';
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(char_lowercase_a));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("bc");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<char>(variable_value->data));
    ASSERT_EQ(std::get<char>(variable_value->data), 'a');
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_float_0_new_value_0_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    float float_zero = 0.0f;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(float_zero));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("0");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<float>(variable_value->data));
    ASSERT_EQ(std::get<float>(variable_value->data), 0.0f);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_float_0_new_value_0_dot_0_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    float float_zero = 0.0f;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(float_zero));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("0.0");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<float>(variable_value->data));
    ASSERT_EQ(std::get<float>(variable_value->data), 0.0f);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_float_0_new_value_plus_1_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    float float_zero = 0.0f;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(float_zero));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("1");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<float>(variable_value->data));
    ASSERT_EQ(std::get<float>(variable_value->data), 1.0f);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_float_0_new_value_plus_1_dot_0_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    float float_zero = 0.0f;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(float_zero));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("1.0");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<float>(variable_value->data));
    ASSERT_EQ(std::get<float>(variable_value->data), 1.0f);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_float_0_new_value_minus_1_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    float float_zero = 0.0f;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(float_zero));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("-1");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<float>(variable_value->data));
    ASSERT_EQ(std::get<float>(variable_value->data), -1.0f);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_float_0_new_value_minus_1_dot_0_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    float float_zero = 0.0f;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(float_zero));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("-1.0");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<float>(variable_value->data));
    ASSERT_EQ(std::get<float>(variable_value->data), -1.0f);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_float_0_new_value_foo_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    float float_zero = 0.0f;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(float_zero));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("foo");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<float>(variable_value->data));
    ASSERT_EQ(std::get<float>(variable_value->data), 0.0f);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_float_plus_1_new_value_0_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    float float_plus_1 = 1.0f;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(float_plus_1));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("0");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<float>(variable_value->data));
    ASSERT_EQ(std::get<float>(variable_value->data), 0.0f);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_float_plus_1_new_value_0_dot_0_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    float float_plus_1 = 1.0f;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(float_plus_1));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("0.0");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<float>(variable_value->data));
    ASSERT_EQ(std::get<float>(variable_value->data), 0.0f);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_float_plus_1_new_value_plus_1_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    float float_plus_1 = 1.0f;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(float_plus_1));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("1");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<float>(variable_value->data));
    ASSERT_EQ(std::get<float>(variable_value->data), 1.0f);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_float_plus_1_new_value_plus_1_dot_0_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    float float_plus_1 = 1.0f;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(float_plus_1));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("1.0");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<float>(variable_value->data));
    ASSERT_EQ(std::get<float>(variable_value->data), 1.0f);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_float_plus_1_new_value_minus_1_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    float float_plus_1 = 1.0f;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(float_plus_1));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("-1");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<float>(variable_value->data));
    ASSERT_EQ(std::get<float>(variable_value->data), -1.0f);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_float_plus_1_new_value_minus_1_dot_0_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    float float_plus_1 = 1.0f;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(float_plus_1));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("-1.0");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<float>(variable_value->data));
    ASSERT_EQ(std::get<float>(variable_value->data), -1.0f);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_float_plus_1_new_value_foo_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    float float_plus_1 = 1.0f;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(float_plus_1));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("foo");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<float>(variable_value->data));
    ASSERT_EQ(std::get<float>(variable_value->data), 1.0f);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_double_0_new_value_0_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    double double_zero = 0.0;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(double_zero));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("0");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<double>(variable_value->data));
    ASSERT_EQ(std::get<double>(variable_value->data), 0.0);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_double_0_new_value_0_dot_0_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    double double_zero = 0.0;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(double_zero));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("0.0");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<double>(variable_value->data));
    ASSERT_EQ(std::get<double>(variable_value->data), 0.0);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_double_0_new_value_plus_1_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    double double_zero = 0.0;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(double_zero));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("1");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<double>(variable_value->data));
    ASSERT_EQ(std::get<double>(variable_value->data), 1.0);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_double_0_new_value_plus_1_dot_0_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    double double_zero = 0.0;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(double_zero));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("1.0");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<double>(variable_value->data));
    ASSERT_EQ(std::get<double>(variable_value->data), 1.0);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_double_0_new_value_minus_1_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    double double_zero = 0.0;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(double_zero));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("-1");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<double>(variable_value->data));
    ASSERT_EQ(std::get<double>(variable_value->data), -1.0);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_double_0_new_value_minus_1_dot_0_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    double double_zero = 0.0;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(double_zero));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("-1.0");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<double>(variable_value->data));
    ASSERT_EQ(std::get<double>(variable_value->data), -1.0);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_double_0_new_value_foo_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    double double_zero = 0.0;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(double_zero));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("foo");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<double>(variable_value->data));
    ASSERT_EQ(std::get<double>(variable_value->data), 0.0);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_double_plus_1_new_value_0_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    double double_plus_1 = 1.0;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(double_plus_1));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("0");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<double>(variable_value->data));
    ASSERT_EQ(std::get<double>(variable_value->data), 0.0);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_double_plus_1_new_value_0_dot_0_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    double double_plus_1 = 1.0;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(double_plus_1));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("0.0");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<double>(variable_value->data));
    ASSERT_EQ(std::get<double>(variable_value->data), 0.0);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_double_plus_1_new_value_plus_1_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    double double_plus_1 = 1.0;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(double_plus_1));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("1");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<double>(variable_value->data));
    ASSERT_EQ(std::get<double>(variable_value->data), 1.0);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_double_plus_1_new_value_plus_1_dot_0_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    double double_plus_1 = 1.0;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(double_plus_1));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("1.0");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<double>(variable_value->data));
    ASSERT_EQ(std::get<double>(variable_value->data), 1.0);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_double_plus_1_new_value_minus_1_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    double double_plus_1 = 1.0;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(double_plus_1));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("-1");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<double>(variable_value->data));
    ASSERT_EQ(std::get<double>(variable_value->data), -1.0);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_double_plus_1_new_value_minus_1_dot_0_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    double double_plus_1 = 1.0;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(double_plus_1));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("-1.0");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<double>(variable_value->data));
    ASSERT_EQ(std::get<double>(variable_value->data), -1.0);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_double_plus_1_new_value_foo_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    double double_plus_1 = 1.0;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(double_plus_1));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("foo");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<double>(variable_value->data));
    ASSERT_EQ(std::get<double>(variable_value->data), 1.0);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_int32_t_0_new_value_0_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    int32_t int32_t_zero = 0;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(int32_t_zero));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("0");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<int32_t>(variable_value->data));
    ASSERT_EQ(std::get<int32_t>(variable_value->data), 0);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_int32_t_0_new_value_plus_1_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    int32_t int32_t_zero = 0;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(int32_t_zero));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("1");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<int32_t>(variable_value->data));
    ASSERT_EQ(std::get<int32_t>(variable_value->data), 1);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_int32_t_0_new_value_minus_1_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    int32_t int32_t_zero = 0;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(int32_t_zero));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("-1");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<int32_t>(variable_value->data));
    ASSERT_EQ(std::get<int32_t>(variable_value->data), -1);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_int32_t_0_new_value_0_dot_0_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    int32_t int32_t_zero = 0;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(int32_t_zero));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("0.0");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<int32_t>(variable_value->data));
    ASSERT_EQ(std::get<int32_t>(variable_value->data), 0);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_int32_t_0_new_value_plus_1_dot_0_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    int32_t int32_t_zero = 0;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(int32_t_zero));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("1.0");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<int32_t>(variable_value->data));
    ASSERT_EQ(std::get<int32_t>(variable_value->data), 0);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_int32_t_0_new_value_minus_1_dot_0_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    int32_t int32_t_zero = 0;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(int32_t_zero));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("-1.0");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<int32_t>(variable_value->data));
    ASSERT_EQ(std::get<int32_t>(variable_value->data), 0);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_int32_t_0_new_value_foo_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    int32_t int32_t_zero = 0;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(int32_t_zero));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("foo");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<int32_t>(variable_value->data));
    ASSERT_EQ(std::get<int32_t>(variable_value->data), 0);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_int32_t_plus_1_new_value_0_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    int32_t int32_t_plus_1 = 1;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(int32_t_plus_1));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("0");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<int32_t>(variable_value->data));
    ASSERT_EQ(std::get<int32_t>(variable_value->data), 0);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_int32_t_plus_1_new_value_plus_1_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    int32_t int32_t_plus_1 = 1;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(int32_t_plus_1));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("1");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<int32_t>(variable_value->data));
    ASSERT_EQ(std::get<int32_t>(variable_value->data), 1);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_int32_t_plus_1_new_value_minus_1_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    int32_t int32_t_plus_1 = 1;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(int32_t_plus_1));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("-1");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<int32_t>(variable_value->data));
    ASSERT_EQ(std::get<int32_t>(variable_value->data), -1);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_int32_t_plus_1_new_value_0_dot_0_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    int32_t int32_t_plus_1 = 1;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(int32_t_plus_1));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("0.0");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<int32_t>(variable_value->data));
    ASSERT_EQ(std::get<int32_t>(variable_value->data), 1);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_int32_t_plus_1_new_value_plus_1_dot_0_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    int32_t int32_t_plus_1 = 1;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(int32_t_plus_1));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("1.0");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<int32_t>(variable_value->data));
    ASSERT_EQ(std::get<int32_t>(variable_value->data), 1);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_int32_t_plus_1_new_value_foo_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    int32_t int32_t_plus_1 = 1;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(int32_t_plus_1));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("foo");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<int32_t>(variable_value->data));
    ASSERT_EQ(std::get<int32_t>(variable_value->data), 1);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_uint32_t_0_new_value_0_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    uint32_t uint32_t_zero = 0;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(uint32_t_zero));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("0");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<uint32_t>(variable_value->data));
    ASSERT_EQ(std::get<uint32_t>(variable_value->data), 0);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_uint32_t_0_new_value_plus_1_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    uint32_t uint32_t_zero = 0;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(uint32_t_zero));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("1");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<uint32_t>(variable_value->data));
    ASSERT_EQ(std::get<uint32_t>(variable_value->data), 1);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_uint32_t_0_new_value_minus_1_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    uint32_t uint32_t_zero = 0;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(uint32_t_zero));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("-1");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<uint32_t>(variable_value->data));
    ASSERT_EQ(std::get<uint32_t>(variable_value->data), 0);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_uint32_t_0_new_value_0_dot_0_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    uint32_t uint32_t_zero = 0;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(uint32_t_zero));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("0.0");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<uint32_t>(variable_value->data));
    ASSERT_EQ(std::get<uint32_t>(variable_value->data), 0);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_uint32_t_0_new_value_plus_1_dot_0_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    uint32_t uint32_t_zero = 0;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(uint32_t_zero));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("1.0");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<uint32_t>(variable_value->data));
    ASSERT_EQ(std::get<uint32_t>(variable_value->data), 0);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_uint32_t_0_new_value_minus_1_dot_0_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    uint32_t uint32_t_zero = 0;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(uint32_t_zero));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("-1.0");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<uint32_t>(variable_value->data));
    ASSERT_EQ(std::get<uint32_t>(variable_value->data), 0);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_uint32_t_0_new_value_foo_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    uint32_t uint32_t_zero = 0;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(uint32_t_zero));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("foo");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<uint32_t>(variable_value->data));
    ASSERT_EQ(std::get<uint32_t>(variable_value->data), 0);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_uint32_t_plus_1_new_value_0_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    uint32_t uint32_t_plus_1 = 1;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(uint32_t_plus_1));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("0");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<uint32_t>(variable_value->data));
    ASSERT_EQ(std::get<uint32_t>(variable_value->data), 0);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_uint32_t_plus_1_new_value_plus_1_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    uint32_t uint32_t_plus_1 = 1;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(uint32_t_plus_1));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("1");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<uint32_t>(variable_value->data));
    ASSERT_EQ(std::get<uint32_t>(variable_value->data), 1);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_uint32_t_plus_1_new_value_minus_1_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    uint32_t uint32_t_plus_1 = 1;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(uint32_t_plus_1));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("-1");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<uint32_t>(variable_value->data));
    ASSERT_EQ(std::get<uint32_t>(variable_value->data), 1);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_uint32_t_plus_1_new_value_0_dot_0_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    uint32_t uint32_t_plus_1 = 1;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(uint32_t_plus_1));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("0.0");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<uint32_t>(variable_value->data));
    ASSERT_EQ(std::get<uint32_t>(variable_value->data), 1);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_uint32_t_plus_1_new_value_plus_1_dot_0_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    uint32_t uint32_t_plus_1 = 1;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(uint32_t_plus_1));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("1.0");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<uint32_t>(variable_value->data));
    ASSERT_EQ(std::get<uint32_t>(variable_value->data), 1);
}

TEST(variable_value_must_not_be_modified_for_invalid_value, headless_universe_named_variable_originally_uint32_t_plus_1_new_value_foo_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    uint32_t uint32_t_plus_1 = 1;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(uint32_t_plus_1));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    variable->set("foo");
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<uint32_t>(variable_value->data));
    ASSERT_EQ(std::get<uint32_t>(variable_value->data), 1);
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_bool_true_copy_value_true_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    bool bool_true = true;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(bool_true));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    yli::data::AnyValue bool_true_any_value(true);
    variable->set(bool_true_any_value);
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<bool>(variable_value->data));
    ASSERT_TRUE(std::get<bool>(variable_value->data));

    bool_true_any_value.data = false;
    ASSERT_TRUE(std::get<bool>(variable_value->data)); // Must do a deep copy, that is, changing the source value after copying must not affect the dest value.
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_bool_true_copy_value_false_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    bool bool_true = true;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(bool_true));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    yli::data::AnyValue bool_false_any_value(false);
    variable->set(bool_false_any_value);
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<bool>(variable_value->data));
    ASSERT_FALSE(std::get<bool>(variable_value->data));

    bool_false_any_value.data = true;
    ASSERT_FALSE(std::get<bool>(variable_value->data)); // Must do a deep copy, that is, changing the source value after copying must not affect the dest value.
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_bool_false_copy_value_true_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    bool bool_false = false;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(bool_false));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    yli::data::AnyValue bool_true_any_value(true);
    variable->set(bool_true_any_value);
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<bool>(variable_value->data));
    ASSERT_TRUE(std::get<bool>(variable_value->data));

    bool_true_any_value.data = false;
    ASSERT_TRUE(std::get<bool>(variable_value->data)); // Must do a deep copy, that is, changing the source value after copying must not affect the dest value.
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_named_variable_originally_bool_false_copy_value_false_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    bool bool_false = false;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.local_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(bool_false));

    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");
    yli::data::AnyValue bool_false_any_value(false);
    variable->set(bool_false_any_value);
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<bool>(variable_value->data));
    ASSERT_FALSE(std::get<bool>(variable_value->data));

    bool_false_any_value.data = true;
    ASSERT_FALSE(std::get<bool>(variable_value->data)); // Must do a deep copy, that is, changing the source value after copying must not affect the dest value.
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_variable_with_global_name_bool_true_set_to_false_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    bool bool_true = true;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.global_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(bool_true));
    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");

    yli::ontology::Variable::set_variable_const_std_string(*variable, "false");
    ASSERT_TRUE(std::holds_alternative<bool>(variable->variable_value.data));
    ASSERT_FALSE(std::get<bool>(variable->variable_value.data));

    yli::ontology::Variable::set_variable_const_std_string(*variable, "true");
    ASSERT_TRUE(std::holds_alternative<bool>(variable->variable_value.data));
    ASSERT_TRUE(std::get<bool>(variable->variable_value.data));
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_variable_with_global_name_bool_false_set_to_true_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    bool bool_false = false;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.global_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(bool_false));
    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");

    yli::ontology::Variable::set_variable_const_std_string(*variable, "true");
    ASSERT_TRUE(std::holds_alternative<bool>(variable->variable_value.data));
    ASSERT_TRUE(std::get<bool>(variable->variable_value.data));

    yli::ontology::Variable::set_variable_const_std_string(*variable, "false");
    ASSERT_TRUE(std::holds_alternative<bool>(variable->variable_value.data));
    ASSERT_FALSE(std::get<bool>(variable->variable_value.data));
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_variable_with_global_name_bool_true_set_to_true_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    bool bool_true = true;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.global_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(bool_true));
    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");

    yli::ontology::Variable::set_variable_const_std_string(*variable, "true");
    ASSERT_TRUE(std::holds_alternative<bool>(variable->variable_value.data));
    ASSERT_TRUE(std::get<bool>(variable->variable_value.data));

    yli::ontology::Variable::set_variable_const_std_string(*variable, "false");
    ASSERT_TRUE(std::holds_alternative<bool>(variable->variable_value.data));
    ASSERT_FALSE(std::get<bool>(variable->variable_value.data));
}

TEST(variable_value_must_be_modified_appropriately, headless_universe_variable_with_global_name_bool_false_set_to_false_no_activate_callback_no_read_callback)
{
    mock::MockApplication application;

    bool bool_false = false;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), &application.get_universe());
    variable_struct.global_name = "foo";
    application.get_universe().create_variable(variable_struct, yli::data::AnyValue(bool_false));
    yli::ontology::Variable* const variable = application.get_universe().get_variable("foo");

    yli::ontology::Variable::set_variable_const_std_string(*variable, "false");
    ASSERT_TRUE(std::holds_alternative<bool>(variable->variable_value.data));
    ASSERT_FALSE(std::get<bool>(variable->variable_value.data));

    yli::ontology::Variable::set_variable_const_std_string(*variable, "true");
    ASSERT_TRUE(std::holds_alternative<bool>(variable->variable_value.data));
    ASSERT_TRUE(std::get<bool>(variable->variable_value.data));
}

TEST(variable_must_be_initialized_appropriately, headless_universe_unnamed_variable_bool_true_no_activate_callback_no_read_callback_ecosystem_given_as_valid_pointer)
{
    mock::MockApplication application;
    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    bool bool_true = true;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), ecosystem);
    yli::ontology::Variable* const variable = application.get_generic_entity_factory().create_variable(variable_struct, yli::data::AnyValue(bool_true));

    ASSERT_NE(variable, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(variable) % alignof(yli::ontology::Variable), 0);
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<bool>(variable_value->data));
    ASSERT_TRUE(std::get<bool>(variable_value->data));

    ASSERT_FALSE(application.get_universe().has_variable("foo"));
    ASSERT_EQ(application.get_universe().get_variable("foo"), nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1); // `ecosystem`.

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 0);

    // `Entity` member functions.
    ASSERT_EQ(variable->get_type(), "yli::ontology::Variable*");
    ASSERT_TRUE(variable->get_can_be_erased());
    ASSERT_EQ(variable->get_scene(), nullptr);
    ASSERT_EQ(variable->get_parent(), ecosystem);
    ASSERT_EQ(variable->get_number_of_non_variable_children(), 0);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_unnamed_variable_bool_true_no_activate_callback_no_read_callback_ecosystem_given_as_nullptr)
{
    mock::MockApplication application;
    yli::ontology::EcosystemStruct ecosystem_struct;
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    bool bool_true = true;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), nullptr);
    yli::ontology::Variable* const variable = application.get_generic_entity_factory().create_variable(variable_struct, yli::data::AnyValue(bool_true));

    ASSERT_NE(variable, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(variable) % alignof(yli::ontology::Variable), 0);
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<bool>(variable_value->data));
    ASSERT_TRUE(std::get<bool>(variable_value->data));

    ASSERT_FALSE(application.get_universe().has_variable("foo"));
    ASSERT_EQ(application.get_universe().get_variable("foo"), nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1); // `ecosystem`.

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 0);

    // `Entity` member functions.
    ASSERT_EQ(variable->get_type(), "yli::ontology::Variable*");
    ASSERT_TRUE(variable->get_can_be_erased());
    ASSERT_EQ(variable->get_number_of_non_variable_children(), 0);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_unnamed_variable_bool_true_no_activate_callback_no_read_callback_ecosystem_given_as_valid_global_name)
{
    mock::MockApplication application;
    yli::ontology::EcosystemStruct ecosystem_struct;
    ecosystem_struct.global_name = "foo";
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    bool bool_true = true;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), "foo");
    yli::ontology::Variable* const variable = application.get_generic_entity_factory().create_variable(variable_struct, yli::data::AnyValue(bool_true));

    ASSERT_NE(variable, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(variable) % alignof(yli::ontology::Variable), 0);
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<bool>(variable_value->data));
    ASSERT_TRUE(std::get<bool>(variable_value->data));

    ASSERT_FALSE(application.get_universe().has_variable("bar"));
    ASSERT_EQ(application.get_universe().get_variable("bar"), nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1); // `ecosystem`.

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 0);

    // `Entity` member functions.
    ASSERT_EQ(variable->get_type(), "yli::ontology::Variable*");
    ASSERT_TRUE(variable->get_can_be_erased());
    ASSERT_EQ(variable->get_scene(), nullptr);
    ASSERT_EQ(variable->get_parent(), ecosystem);
    ASSERT_EQ(variable->get_number_of_non_variable_children(), 0);
}

TEST(variable_must_be_initialized_appropriately, headless_universe_unnamed_variable_bool_true_no_activate_callback_no_read_callback_ecosystem_given_as_invalid_global_name)
{
    mock::MockApplication application;
    yli::ontology::EcosystemStruct ecosystem_struct;
    ecosystem_struct.global_name = "foo";
    yli::ontology::Ecosystem* const ecosystem = application.get_generic_entity_factory().create_ecosystem(
            ecosystem_struct);

    bool bool_true = true;
    yli::ontology::VariableStruct variable_struct(application.get_universe(), "bar");
    yli::ontology::Variable* const variable = application.get_generic_entity_factory().create_variable(variable_struct, yli::data::AnyValue(bool_true));

    ASSERT_NE(variable, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(variable) % alignof(yli::ontology::Variable), 0);
    ASSERT_NE(variable->get(), std::nullopt);
    ASSERT_EQ(variable->variable_value, *variable->get());
    std::optional<yli::data::AnyValue> variable_value = variable->get();
    ASSERT_TRUE(std::holds_alternative<bool>(variable_value->data));
    ASSERT_TRUE(std::get<bool>(variable_value->data));

    ASSERT_FALSE(application.get_universe().has_variable("baz"));
    ASSERT_EQ(application.get_universe().get_variable("baz"), nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1); // `ecosystem`.

    // `Entity` member functions of `Ecosystem`.
    ASSERT_EQ(ecosystem->get_number_of_non_variable_children(), 0);

    // `Entity` member functions.
    ASSERT_EQ(variable->get_type(), "yli::ontology::Variable*");
    ASSERT_TRUE(variable->get_can_be_erased());
    ASSERT_EQ(variable->get_number_of_non_variable_children(), 0);
}
