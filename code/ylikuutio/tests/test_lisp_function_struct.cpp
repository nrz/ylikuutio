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
#include "code/ylikuutio/ontology/lisp_function_struct.hpp"

// Include standard headers
#include <variant> // std::holds_alternative

namespace yli::ontology
{
    class Console;
}

TEST(lisp_function_struct_must_be_initialized_appropriately, lisp_function_struct_parent_provided_as_nullptr)
{
    const yli::ontology::LispFunctionStruct test_lisp_function_struct(nullptr);

    ASSERT_FALSE(test_lisp_function_struct.console_parent.valueless_by_exception());
    ASSERT_TRUE(std::holds_alternative<yli::ontology::Console*>(test_lisp_function_struct.console_parent));
    ASSERT_FALSE(std::holds_alternative<std::string>(test_lisp_function_struct.console_parent));
    ASSERT_EQ(std::get<yli::ontology::Console*>(test_lisp_function_struct.console_parent), nullptr);
}

TEST(lisp_function_struct_must_be_initialized_appropriately, lisp_function_struct_parent_provided_as_global_name)
{
    const yli::ontology::LispFunctionStruct test_lisp_function_struct("foo");

    ASSERT_FALSE(test_lisp_function_struct.console_parent.valueless_by_exception());
    ASSERT_FALSE(std::holds_alternative<yli::ontology::Console*>(test_lisp_function_struct.console_parent));
    ASSERT_TRUE(std::holds_alternative<std::string>(test_lisp_function_struct.console_parent));
    ASSERT_EQ(std::get<std::string>(test_lisp_function_struct.console_parent), "foo");
}
