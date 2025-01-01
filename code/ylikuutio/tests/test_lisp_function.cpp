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
#include "code/ylikuutio/ontology/lisp_function.hpp"
#include "code/ylikuutio/ontology/request.hpp"
#include "code/ylikuutio/ontology/lisp_function_struct.hpp"

// Include standard headers
#include <cstddef> // uintptr_t
#include <limits>  // std::numeric_limits

namespace yli::ontology
{
    class Console;
}

TEST(lisp_function_must_be_initialized_appropriately, console_provided_as_valid_pointer)
{
    mock::MockApplication application;
    yli::ontology::ConsoleStruct console_struct;
    yli::ontology::Console* const console = application.get_generic_entity_factory().create_console(
            console_struct);
    yli::ontology::LispFunctionStruct lisp_function_struct { yli::ontology::Request(console) };
    yli::ontology::LispFunction* const lisp_function = application.get_generic_entity_factory().create_lisp_function(
            lisp_function_struct);
    ASSERT_NE(lisp_function, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(lisp_function) % alignof(yli::ontology::LispFunction), 0);

    // `Entity` member functions of `Console`.
    ASSERT_EQ(console->get_number_of_non_variable_children(), 1);

    // `Entity` member functions.
    ASSERT_EQ(lisp_function->get_childID(), 0);
    ASSERT_EQ(lisp_function->get_type(), "yli::ontology::LispFunction*");
    ASSERT_FALSE(lisp_function->get_can_be_erased());
    ASSERT_EQ(lisp_function->get_scene(), console->get_scene());
    ASSERT_EQ(lisp_function->get_parent(), console);
    ASSERT_EQ(lisp_function->get_number_of_non_variable_children(), 0);
}

TEST(lisp_function_must_be_initialized_appropriately, console_provided_as_nullptr)
{
    mock::MockApplication application;
    yli::ontology::LispFunctionStruct lisp_function_struct { yli::ontology::Request<yli::ontology::Console>(nullptr) };
    yli::ontology::LispFunction* const lisp_function = application.get_generic_entity_factory().create_lisp_function(
            lisp_function_struct);
    ASSERT_NE(lisp_function, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(lisp_function) % alignof(yli::ontology::LispFunction), 0);

    // `Entity` member functions.
    ASSERT_EQ(lisp_function->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(lisp_function->get_type(), "yli::ontology::LispFunction*");
    ASSERT_FALSE(lisp_function->get_can_be_erased());
    ASSERT_EQ(lisp_function->get_scene(), nullptr);
    ASSERT_EQ(lisp_function->get_parent(), nullptr);
    ASSERT_EQ(lisp_function->get_number_of_non_variable_children(), 0);
}

TEST(lisp_function_must_be_initialized_appropriately, console_provided_as_valid_global_name)
{
    mock::MockApplication application;
    yli::ontology::ConsoleStruct console_struct;
    console_struct.global_name = "foo";
    yli::ontology::Console* const console = application.get_generic_entity_factory().create_console(
            console_struct);
    yli::ontology::LispFunctionStruct lisp_function_struct { yli::ontology::Request<yli::ontology::Console>("foo") };
    yli::ontology::LispFunction* const lisp_function = application.get_generic_entity_factory().create_lisp_function(
            lisp_function_struct);
    ASSERT_NE(lisp_function, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(lisp_function) % alignof(yli::ontology::LispFunction), 0);

    // `Entity` member functions of `Console`.
    ASSERT_EQ(console->get_number_of_non_variable_children(), 1);

    // `Entity` member functions.
    ASSERT_EQ(lisp_function->get_childID(), 0);
    ASSERT_EQ(lisp_function->get_type(), "yli::ontology::LispFunction*");
    ASSERT_FALSE(lisp_function->get_can_be_erased());
    ASSERT_EQ(lisp_function->get_scene(), console->get_scene());
    ASSERT_EQ(lisp_function->get_parent(), console);
    ASSERT_EQ(lisp_function->get_number_of_non_variable_children(), 0);
}

TEST(lisp_function_must_be_initialized_appropriately, console_provided_as_invalid_global_name)
{
    mock::MockApplication application;
    yli::ontology::ConsoleStruct console_struct;
    console_struct.global_name = "foo";
    yli::ontology::Console* const console = application.get_generic_entity_factory().create_console(
            console_struct);
    yli::ontology::LispFunctionStruct lisp_function_struct { yli::ontology::Request<yli::ontology::Console>("bar") };
    yli::ontology::LispFunction* const lisp_function = application.get_generic_entity_factory().create_lisp_function(
            lisp_function_struct);
    ASSERT_NE(lisp_function, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(lisp_function) % alignof(yli::ontology::LispFunction), 0);

    // `Entity` member functions of `Console`.
    ASSERT_EQ(console->get_number_of_non_variable_children(), 0);

    // `Entity` member functions.
    ASSERT_EQ(lisp_function->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(lisp_function->get_type(), "yli::ontology::LispFunction*");
    ASSERT_FALSE(lisp_function->get_can_be_erased());
    ASSERT_EQ(lisp_function->get_scene(), nullptr);
    ASSERT_EQ(lisp_function->get_parent(), nullptr);
    ASSERT_EQ(lisp_function->get_number_of_non_variable_children(), 0);
}
