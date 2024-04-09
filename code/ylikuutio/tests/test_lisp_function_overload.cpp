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
#include "code/ylikuutio/ontology/entity.hpp"
#include "code/ylikuutio/ontology/variable.hpp"
#include "code/ylikuutio/ontology/console.hpp"
#include "code/ylikuutio/ontology/console_struct.hpp"

// Include standard headers
#include <string> // std::string

namespace yli::ontology
{
    class GenericLispFunctionOverload;
}

TEST(variables_lisp_function_overload_must_function_appropriately, variables)
{
    mock::MockApplication application;

    yli::ontology::ConsoleStruct my_console_struct;
    yli::ontology::Entity* const my_console_entity = application.get_generic_entity_factory().create_console(my_console_struct);
    yli::ontology::Console* const my_console = dynamic_cast<yli::ontology::Console*>(my_console_entity);
    ASSERT_NE(my_console, nullptr);

    const std::string lisp_function_name = "variables";
    yli::ontology::GenericLispFunctionOverload* const lisp_function_overload = application.entity_factory.create_lisp_function_overload(
            lisp_function_name,
            *my_console,
            &yli::ontology::Entity::print_variables0);

    ASSERT_NE(lisp_function_overload, nullptr);
    // `LispfunctionOverload` is allocated in using standard allocator so proper alignment should be guaranteed.

    // TODO: `variables` should return a list of variables and not print them in console!
    // Once that is done create a test that counts the number of variables first from the list, creates a new variable, and
    // and then counts the number of variables first from the list again!
}

TEST(set_lisp_function_overload_must_function_appropriately, set)
{
    mock::MockApplication application;

    yli::ontology::ConsoleStruct my_console_struct;
    yli::ontology::Entity* const my_console_entity = application.get_generic_entity_factory().create_console(my_console_struct);
    yli::ontology::Console* const my_console = dynamic_cast<yli::ontology::Console*>(my_console_entity);
    ASSERT_NE(my_console, nullptr);

    const std::string lisp_function_name = "set";
    yli::ontology::GenericLispFunctionOverload* const lisp_function_overload = application.entity_factory.create_lisp_function_overload(
            lisp_function_name,
            *my_console,
            &yli::ontology::Variable::set_variable_const_std_string);

    ASSERT_NE(lisp_function_overload, nullptr);

    // TODO: set the value of a variable using `set` Lisp function overload and check that value changes!
}
