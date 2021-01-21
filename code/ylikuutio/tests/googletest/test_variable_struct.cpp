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
#include "code/ylikuutio/ontology/variable_struct.hpp"

// Include standard headers
#include <limits>  // std::numeric_limits
#include <memory>  // std::make_shared, std::shared_ptr
#include <variant> // std::holds_alternative, std::variant

TEST(variable_struct_must_be_initialized_appropriately, variable_struct_default_constructor)
{
    const yli::ontology::VariableStruct test_variable_struct;
    ASSERT_EQ(test_variable_struct.parent, nullptr);
    ASSERT_EQ(test_variable_struct.initial_value, nullptr);
    ASSERT_EQ(test_variable_struct.activate_callback, nullptr);
    ASSERT_EQ(test_variable_struct.read_callback, nullptr);
    ASSERT_TRUE(test_variable_struct.should_ylikuutio_call_activate_callback_now);
    ASSERT_EQ(test_variable_struct.global_name, "");
    ASSERT_EQ(test_variable_struct.local_name, "");
    ASSERT_TRUE(test_variable_struct.is_variable);
}

TEST(variable_struct_must_be_initialized_appropriately, variable_struct_initial_value_constructor_positive_infinity)
{
    float float_positive_infinity = std::numeric_limits<float>::infinity();
    std::shared_ptr<yli::data::AnyValue> float_positive_infinity_value = std::make_shared<yli::data::AnyValue>(float_positive_infinity);
    const yli::ontology::VariableStruct test_variable_struct(float_positive_infinity_value);
    ASSERT_EQ(test_variable_struct.parent, nullptr);
    ASSERT_NE(test_variable_struct.initial_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(test_variable_struct.initial_value->data));
    ASSERT_EQ(std::get<float>(test_variable_struct.initial_value->data), std::numeric_limits<float>::infinity());
    ASSERT_EQ(test_variable_struct.activate_callback, nullptr);
    ASSERT_EQ(test_variable_struct.read_callback, nullptr);
    ASSERT_TRUE(test_variable_struct.should_ylikuutio_call_activate_callback_now);
    ASSERT_EQ(test_variable_struct.global_name, "");
    ASSERT_EQ(test_variable_struct.local_name, "");
    ASSERT_TRUE(test_variable_struct.is_variable);
}

TEST(variable_struct_must_be_initialized_appropriately, variable_struct_copy_constructor)
{
    float float_positive_infinity = std::numeric_limits<float>::infinity();
    std::shared_ptr<yli::data::AnyValue> float_positive_infinity_value = std::make_shared<yli::data::AnyValue>(float_positive_infinity);
    yli::ontology::VariableStruct original_variable_struct(float_positive_infinity_value);
    original_variable_struct.global_name = "foo";
    original_variable_struct.local_name = "bar";
    const yli::ontology::VariableStruct copy_variable_struct(original_variable_struct);
    ASSERT_EQ(copy_variable_struct.parent, nullptr);
    ASSERT_NE(copy_variable_struct.initial_value, nullptr);
    ASSERT_TRUE(std::holds_alternative<float>(copy_variable_struct.initial_value->data));
    ASSERT_EQ(std::get<float>(copy_variable_struct.initial_value->data), std::numeric_limits<float>::infinity());
    ASSERT_EQ(copy_variable_struct.activate_callback, nullptr);
    ASSERT_EQ(copy_variable_struct.read_callback, nullptr);
    ASSERT_TRUE(copy_variable_struct.should_ylikuutio_call_activate_callback_now);
    ASSERT_EQ(copy_variable_struct.global_name, "foo");
    ASSERT_EQ(copy_variable_struct.local_name, "bar");
    ASSERT_TRUE(copy_variable_struct.is_variable);
}
