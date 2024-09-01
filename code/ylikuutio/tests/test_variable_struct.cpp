// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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
#include "code/ylikuutio/ontology/variable_struct.hpp"

// Include standard headers
#include <string>  // std::string
#include <variant> // std::holds_alternative

namespace yli::ontology
{
    class Entity;
}

TEST(variable_struct_must_be_initialized_appropriately, variable_struct_constructor_parent_given_as_valid_pointer)
{
    mock::MockApplication application;

    const yli::ontology::VariableStruct test_variable_struct(application.get_universe(), &application.get_universe());

    ASSERT_FALSE(test_variable_struct.entity_parent.valueless_by_exception());
    ASSERT_TRUE(std::holds_alternative<yli::ontology::Entity*>(test_variable_struct.entity_parent));
    ASSERT_FALSE(std::holds_alternative<std::string>(test_variable_struct.entity_parent));

    ASSERT_EQ(test_variable_struct.activate_callback, nullptr);
    ASSERT_EQ(test_variable_struct.read_callback, nullptr);
    ASSERT_TRUE(test_variable_struct.should_call_activate_callback_now);
    ASSERT_EQ(test_variable_struct.global_name, "");
    ASSERT_EQ(test_variable_struct.local_name, "");
    ASSERT_TRUE(test_variable_struct.is_variable);
}

TEST(variable_struct_must_be_initialized_appropriately, variable_struct_constructor_parent_given_as_nullptr)
{
    mock::MockApplication application;

    const yli::ontology::VariableStruct test_variable_struct(application.get_universe(), nullptr);

    ASSERT_FALSE(test_variable_struct.entity_parent.valueless_by_exception());
    ASSERT_TRUE(std::holds_alternative<yli::ontology::Entity*>(test_variable_struct.entity_parent));
    ASSERT_FALSE(std::holds_alternative<std::string>(test_variable_struct.entity_parent));

    ASSERT_EQ(test_variable_struct.activate_callback, nullptr);
    ASSERT_EQ(test_variable_struct.read_callback, nullptr);
    ASSERT_TRUE(test_variable_struct.should_call_activate_callback_now);
    ASSERT_EQ(test_variable_struct.global_name, "");
    ASSERT_EQ(test_variable_struct.local_name, "");
    ASSERT_TRUE(test_variable_struct.is_variable);
}

TEST(variable_struct_must_be_initialized_appropriately, variable_struct_constructor_parent_given_as_string)
{
    mock::MockApplication application;

    const yli::ontology::VariableStruct test_variable_struct(application.get_universe(), "foo");

    ASSERT_FALSE(test_variable_struct.entity_parent.valueless_by_exception());
    ASSERT_FALSE(std::holds_alternative<yli::ontology::Entity*>(test_variable_struct.entity_parent));
    ASSERT_TRUE(std::holds_alternative<std::string>(test_variable_struct.entity_parent));

    ASSERT_EQ(test_variable_struct.activate_callback, nullptr);
    ASSERT_EQ(test_variable_struct.read_callback, nullptr);
    ASSERT_TRUE(test_variable_struct.should_call_activate_callback_now);
    ASSERT_EQ(test_variable_struct.global_name, "");
    ASSERT_EQ(test_variable_struct.local_name, "");
    ASSERT_TRUE(test_variable_struct.is_variable);
}

TEST(variable_struct_must_be_initialized_appropriately, variable_struct_copy_constructor)
{
    mock::MockApplication application;

    yli::ontology::VariableStruct original_variable_struct(application.get_universe(), &application.get_universe());
    original_variable_struct.global_name = "foo";
    original_variable_struct.local_name = "bar";
    const yli::ontology::VariableStruct copy_variable_struct(original_variable_struct);

    ASSERT_FALSE(copy_variable_struct.entity_parent.valueless_by_exception());
    ASSERT_TRUE(std::holds_alternative<yli::ontology::Entity*>(copy_variable_struct.entity_parent));
    ASSERT_FALSE(std::holds_alternative<std::string>(copy_variable_struct.entity_parent));

    ASSERT_EQ(copy_variable_struct.activate_callback, nullptr);
    ASSERT_EQ(copy_variable_struct.read_callback, nullptr);
    ASSERT_TRUE(copy_variable_struct.should_call_activate_callback_now);
    ASSERT_EQ(copy_variable_struct.global_name, "foo");
    ASSERT_EQ(copy_variable_struct.local_name, "bar");
    ASSERT_TRUE(copy_variable_struct.is_variable);
}
