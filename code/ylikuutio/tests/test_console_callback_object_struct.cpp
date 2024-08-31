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
#include "code/ylikuutio/ontology/console_callback_object_struct.hpp"

// Include standard headers
#include <string>  // std::string
#include <variant> // std::holds_alternative, std::monostate

namespace yli::ontology
{
    class ConsoleCallbackEngine;
}

TEST(console_callback_object_struct_must_be_initialized_appropriately, parent_provided_as_nullptr)
{
    const yli::ontology::ConsoleCallbackObjectStruct test_console_callback_object_struct(static_cast<yli::ontology::ConsoleCallbackEngine*>(nullptr));

    ASSERT_FALSE(test_console_callback_object_struct.console_callback_engine_parent.valueless_by_exception());
    ASSERT_TRUE(std::holds_alternative<yli::ontology::ConsoleCallbackEngine*>(test_console_callback_object_struct.console_callback_engine_parent));
    ASSERT_FALSE(std::holds_alternative<std::string>(test_console_callback_object_struct.console_callback_engine_parent));
    ASSERT_EQ(std::get<yli::ontology::ConsoleCallbackEngine*>(test_console_callback_object_struct.console_callback_engine_parent), nullptr);
}

TEST(console_callback_object_struct_must_be_initialized_appropriately, parent_provided_as_global_name)
{
    const yli::ontology::ConsoleCallbackObjectStruct test_console_callback_object_struct("foo");

    ASSERT_FALSE(test_console_callback_object_struct.console_callback_engine_parent.valueless_by_exception());
    ASSERT_FALSE(std::holds_alternative<yli::ontology::ConsoleCallbackEngine*>(test_console_callback_object_struct.console_callback_engine_parent));
    ASSERT_TRUE(std::holds_alternative<std::string>(test_console_callback_object_struct.console_callback_engine_parent));
    ASSERT_EQ(std::get<std::string>(test_console_callback_object_struct.console_callback_engine_parent), "foo");
}
