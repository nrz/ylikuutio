// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2026 Antti Nuortimo.
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
#include "code/hirvi/hirvi.hpp"
#include "code/ylikuutio/ontology/console_lisp_function.hpp"
#include "code/ylikuutio/ontology/console.hpp"
#include "code/ylikuutio/ontology/request.hpp"
#include "code/ylikuutio/ontology/console_struct.hpp"
#include "code/ylikuutio/ontology/console_lisp_function_struct.hpp"

// Include standard headers
#include <cstdint> // uintptr_t
#include <limits>  // std::numeric_limits

using yli::ontology::Console;
using yli::ontology::ConsoleLispFunction;
using yli::ontology::ConsoleLispFunctionStruct;
using yli::ontology::ConsoleStruct;

TEST(console_lisp_function_must_be_initialized_appropriately, console_provided_as_valid_pointer)
{
    constexpr int argc { 0 };
    const char** const argv { nullptr };
    hirvi::HirviApplication hirvi_application(argc, argv);

    ConsoleStruct console_struct(0, 39, 15, 0); // Some dummy dimensions.
    Console* const console = hirvi_application.get_abstract_entity_factory().create_console(
        console_struct);
    ConsoleLispFunctionStruct console_lisp_function_struct { yli::ontology::Request(console) };
    ConsoleLispFunction* const console_lisp_function = hirvi_application.get_abstract_entity_factory().
            create_console_lisp_function(
                console_lisp_function_struct);
    ASSERT_NE(console_lisp_function, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(console_lisp_function) % alignof(yli::ontology::ConsoleLispFunction), 0);

    // `Entity` member functions of `Console`.
    ASSERT_EQ(console->get_number_of_non_variable_children(), 1);

    // `Entity` member functions.
    ASSERT_EQ(console_lisp_function->get_childID(), 0);
    ASSERT_EQ(console_lisp_function->get_type(), "yli::ontology::ConsoleLispFunction*");
    ASSERT_FALSE(console_lisp_function->get_can_be_erased());
    ASSERT_EQ(console_lisp_function->get_scene(), console->get_scene());
    ASSERT_EQ(console_lisp_function->get_parent(), console);
    ASSERT_EQ(console_lisp_function->get_number_of_non_variable_children(), 0);
}

TEST(console_lisp_function_must_be_initialized_appropriately, console_provided_as_nullptr)
{
    constexpr int argc { 0 };
    const char** const argv { nullptr };
    hirvi::HirviApplication hirvi_application(argc, argv);

    ConsoleLispFunctionStruct console_lisp_function_struct { yli::ontology::Request<Console>(nullptr) };
    ConsoleLispFunction* const console_lisp_function = hirvi_application.get_abstract_entity_factory().
            create_console_lisp_function(
                console_lisp_function_struct);
    ASSERT_NE(console_lisp_function, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(console_lisp_function) % alignof(yli::ontology::ConsoleLispFunction), 0);

    // `Entity` member functions.
    ASSERT_EQ(console_lisp_function->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(console_lisp_function->get_type(), "yli::ontology::ConsoleLispFunction*");
    ASSERT_FALSE(console_lisp_function->get_can_be_erased());
    ASSERT_EQ(console_lisp_function->get_scene(), nullptr);
    ASSERT_EQ(console_lisp_function->get_parent(), nullptr);
    ASSERT_EQ(console_lisp_function->get_number_of_non_variable_children(), 0);
}

TEST(console_lisp_function_must_be_initialized_appropriately, console_provided_as_valid_global_name)
{
    constexpr int argc { 0 };
    const char** const argv { nullptr };
    hirvi::HirviApplication hirvi_application(argc, argv);

    ConsoleStruct console_struct(0, 39, 15, 0); // Some dummy dimensions.
    console_struct.global_name = "foo";
    Console* const console = hirvi_application.get_abstract_entity_factory().create_console(
        console_struct);
    ConsoleLispFunctionStruct console_lisp_function_struct { yli::ontology::Request<Console>("foo") };
    ConsoleLispFunction* const console_lisp_function = hirvi_application.get_abstract_entity_factory().
            create_console_lisp_function(
                console_lisp_function_struct);
    ASSERT_NE(console_lisp_function, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(console_lisp_function) % alignof(yli::ontology::ConsoleLispFunction), 0);

    // `Entity` member functions of `Console`.
    ASSERT_EQ(console->get_number_of_non_variable_children(), 1);

    // `Entity` member functions.
    ASSERT_EQ(console_lisp_function->get_childID(), 0);
    ASSERT_EQ(console_lisp_function->get_type(), "yli::ontology::ConsoleLispFunction*");
    ASSERT_FALSE(console_lisp_function->get_can_be_erased());
    ASSERT_EQ(console_lisp_function->get_scene(), console->get_scene());
    ASSERT_EQ(console_lisp_function->get_parent(), console);
    ASSERT_EQ(console_lisp_function->get_number_of_non_variable_children(), 0);
}

TEST(console_lisp_function_must_be_initialized_appropriately, console_provided_as_invalid_global_name)
{
    constexpr int argc { 0 };
    const char** const argv { nullptr };
    hirvi::HirviApplication hirvi_application(argc, argv);

    ConsoleStruct console_struct(0, 39, 15, 0); // Some dummy dimensions.
    console_struct.global_name = "foo";
    Console* const console = hirvi_application.get_abstract_entity_factory().create_console(
        console_struct);
    ConsoleLispFunctionStruct console_lisp_function_struct { yli::ontology::Request<Console>("bar") };
    ConsoleLispFunction* const console_lisp_function = hirvi_application.get_abstract_entity_factory().
            create_console_lisp_function(
                console_lisp_function_struct);
    ASSERT_NE(console_lisp_function, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(console_lisp_function) % alignof(yli::ontology::ConsoleLispFunction), 0);

    // `Entity` member functions of `Console`.
    ASSERT_EQ(console->get_number_of_non_variable_children(), 0);

    // `Entity` member functions.
    ASSERT_EQ(console_lisp_function->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(console_lisp_function->get_type(), "yli::ontology::ConsoleLispFunction*");
    ASSERT_FALSE(console_lisp_function->get_can_be_erased());
    ASSERT_EQ(console_lisp_function->get_scene(), nullptr);
    ASSERT_EQ(console_lisp_function->get_parent(), nullptr);
    ASSERT_EQ(console_lisp_function->get_number_of_non_variable_children(), 0);
}
