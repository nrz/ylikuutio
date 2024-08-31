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
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/ontology/console_callback_object.hpp"
#include "code/ylikuutio/ontology/console_callback_parameter.hpp"
#include "code/ylikuutio/ontology/console_callback_object_struct.hpp"
#include "code/ylikuutio/ontology/console_callback_parameter_struct.hpp"

// Include standard headers
#include <cstddef>  // std::size_t, uintptr_t
#include <limits>   // std::numeric_limits
#include <stdint.h> // uint32_t etc.
#include <utility>  // std::move

namespace yli::ontology
{
    class ConsoleCallbackObject;
}

TEST(console_callback_parameter_must_be_initialized_appropriately, headless_with_parent_provided_as_valid_pointer)
{
    mock::MockApplication application;
    const yli::ontology::ConsoleCallbackObjectStruct console_callback_object_struct(static_cast<yli::ontology::ConsoleCallbackEngine*>(nullptr));
    yli::ontology::ConsoleCallbackObject* const console_callback_object = application.get_generic_entity_factory().create_console_callback_object(
            console_callback_object_struct);

    const int32_t zero = 0;
    yli::data::AnyValue zero_value(zero);

    const yli::ontology::ConsoleCallbackParameterStruct console_callback_parameter_struct(console_callback_object);
    yli::ontology::ConsoleCallbackParameter* const console_callback_parameter = application.get_generic_entity_factory().create_console_callback_parameter(
            console_callback_parameter_struct,
            std::move(zero_value));
    ASSERT_NE(console_callback_parameter, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(console_callback_parameter) % alignof(yli::ontology::ConsoleCallbackParameter), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 0);

    // `Entity` member functions of `ConsoleCallbackObject`.
    ASSERT_EQ(console_callback_object->get_scene(), nullptr);
    ASSERT_EQ(console_callback_object->get_number_of_non_variable_children(), 1); // `console_callback_parameter`.

    // `Entity` member functions.
    ASSERT_EQ(console_callback_parameter->get_childID(), 0);
    ASSERT_EQ(console_callback_parameter->get_type(), "yli::ontology::ConsoleCallbackParameter*");
    ASSERT_FALSE(console_callback_parameter->get_can_be_erased());
    ASSERT_EQ(console_callback_parameter->get_scene(), nullptr);
    ASSERT_EQ(console_callback_parameter->get_parent(), console_callback_object);
    ASSERT_EQ(console_callback_parameter->get_number_of_non_variable_children(), 0);
}

TEST(console_callback_parameter_must_be_initialized_appropriately, headless_with_parent_provided_as_nullptr)
{
    mock::MockApplication application;
    const yli::ontology::ConsoleCallbackObjectStruct console_callback_object_struct(static_cast<yli::ontology::ConsoleCallbackEngine*>(nullptr));
    yli::ontology::ConsoleCallbackObject* const console_callback_object = application.get_generic_entity_factory().create_console_callback_object(
            console_callback_object_struct);

    const int32_t zero = 0;
    yli::data::AnyValue zero_value(zero);

    const yli::ontology::ConsoleCallbackParameterStruct console_callback_parameter_struct(static_cast<yli::ontology::ConsoleCallbackObject*>(nullptr));
    yli::ontology::ConsoleCallbackParameter* const console_callback_parameter = application.get_generic_entity_factory().create_console_callback_parameter(
            console_callback_parameter_struct,
            std::move(zero_value));
    ASSERT_NE(console_callback_parameter, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(console_callback_parameter) % alignof(yli::ontology::ConsoleCallbackParameter), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 0);

    // `Entity` member functions of `ConsoleCallbackObject`.
    ASSERT_EQ(console_callback_object->get_scene(), nullptr);
    ASSERT_EQ(console_callback_object->get_number_of_non_variable_children(), 0);

    // `Entity` member functions.
    ASSERT_EQ(console_callback_parameter->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(console_callback_parameter->get_type(), "yli::ontology::ConsoleCallbackParameter*");
    ASSERT_FALSE(console_callback_parameter->get_can_be_erased());
    ASSERT_EQ(console_callback_parameter->get_scene(), nullptr);
    ASSERT_EQ(console_callback_parameter->get_parent(), nullptr);
    ASSERT_EQ(console_callback_parameter->get_number_of_non_variable_children(), 0);
}

TEST(console_callback_parameter_must_be_initialized_appropriately, parent_provided_as_valid_global_name)
{
    mock::MockApplication application;
    yli::ontology::ConsoleCallbackObjectStruct console_callback_object_struct(static_cast<yli::ontology::ConsoleCallbackEngine*>(nullptr));
    console_callback_object_struct.global_name = "foo";
    yli::ontology::ConsoleCallbackObject* const console_callback_object = application.get_generic_entity_factory().create_console_callback_object(
            console_callback_object_struct);

    const int32_t zero = 0;
    yli::data::AnyValue zero_value(zero);

    const yli::ontology::ConsoleCallbackParameterStruct console_callback_parameter_struct("foo");
    yli::ontology::ConsoleCallbackParameter* const console_callback_parameter = application.get_generic_entity_factory().create_console_callback_parameter(
            console_callback_parameter_struct,
            std::move(zero_value));
    ASSERT_NE(console_callback_parameter, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(console_callback_parameter) % alignof(yli::ontology::ConsoleCallbackParameter), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 0);

    // `Entity` member functions of `ConsoleCallbackObject`.
    ASSERT_EQ(console_callback_object->get_scene(), nullptr);
    ASSERT_EQ(console_callback_object->get_number_of_non_variable_children(), 1);

    // `Entity` member functions.
    ASSERT_EQ(console_callback_parameter->get_childID(), 0);
    ASSERT_EQ(console_callback_parameter->get_type(), "yli::ontology::ConsoleCallbackParameter*");
    ASSERT_FALSE(console_callback_parameter->get_can_be_erased());
    ASSERT_EQ(console_callback_parameter->get_scene(), nullptr);
    ASSERT_EQ(console_callback_parameter->get_parent(), console_callback_object);
    ASSERT_EQ(console_callback_parameter->get_number_of_non_variable_children(), 0);
}

TEST(console_callback_parameter_must_be_initialized_appropriately, parent_provided_as_invalid_global_name)
{
    mock::MockApplication application;
    yli::ontology::ConsoleCallbackObjectStruct console_callback_object_struct(static_cast<yli::ontology::ConsoleCallbackEngine*>(nullptr));
    console_callback_object_struct.global_name = "foo";
    yli::ontology::ConsoleCallbackObject* const console_callback_object = application.get_generic_entity_factory().create_console_callback_object(
            console_callback_object_struct);

    const int32_t zero = 0;
    yli::data::AnyValue zero_value(zero);

    const yli::ontology::ConsoleCallbackParameterStruct console_callback_parameter_struct("bar");
    yli::ontology::ConsoleCallbackParameter* const console_callback_parameter = application.get_generic_entity_factory().create_console_callback_parameter(
            console_callback_parameter_struct,
            std::move(zero_value));
    ASSERT_NE(console_callback_parameter, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(console_callback_parameter) % alignof(yli::ontology::ConsoleCallbackParameter), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_scene(), nullptr);
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 0);

    // `Entity` member functions of `ConsoleCallbackObject`.
    ASSERT_EQ(console_callback_object->get_scene(), nullptr);
    ASSERT_EQ(console_callback_object->get_number_of_non_variable_children(), 0);

    // `Entity` member functions.
    ASSERT_EQ(console_callback_parameter->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(console_callback_parameter->get_type(), "yli::ontology::ConsoleCallbackParameter*");
    ASSERT_FALSE(console_callback_parameter->get_can_be_erased());
    ASSERT_EQ(console_callback_parameter->get_scene(), nullptr);
    ASSERT_EQ(console_callback_parameter->get_parent(), nullptr);
    ASSERT_EQ(console_callback_parameter->get_number_of_non_variable_children(), 0);
}
