// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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
#include "code/ylikuutio/data/datatype.hpp"
#include "code/ylikuutio/memory/memory_allocator.hpp"
#include "code/ylikuutio/ontology/console.hpp"
#include "code/ylikuutio/ontology/console_struct.hpp"

namespace yli::ontology
{
    class AbstractConsoleLispFunctionOverload;
}

TEST(memory_allocator_must_be_initialized_appropriately, default_memory_allocator_universe_datatype)
{
    const yli::memory::MemoryAllocator memory_allocator(yli::data::Datatype::UNIVERSE);
    ASSERT_EQ(memory_allocator.get_datatype(), yli::data::Datatype::UNIVERSE);
    ASSERT_EQ(memory_allocator.get_number_of_instances(), 0);
}

TEST(memory_allocator_must_be_initialized_appropriately, default_memory_allocator_variable_datatype)
{
    const yli::memory::MemoryAllocator memory_allocator(yli::data::Datatype::VARIABLE);
    ASSERT_EQ(memory_allocator.get_datatype(), yli::data::Datatype::VARIABLE);
    ASSERT_EQ(memory_allocator.get_number_of_instances(), 0);
}

TEST(memory_allocator_must_be_initialized_appropriately,
     default_memory_allocator_console_lisp_function_overload_datatype)
{
    const yli::memory::MemoryAllocator memory_allocator(yli::data::Datatype::CONSOLE_LISP_FUNCTION_OVERLOAD);
    ASSERT_EQ(memory_allocator.get_datatype(), yli::data::Datatype::CONSOLE_LISP_FUNCTION_OVERLOAD);
    ASSERT_EQ(memory_allocator.get_number_of_instances(), 0);
}

TEST(memory_allocator_must_allocate_appropriately, default_memory_allocator_console_lisp_function_overload_datatype)
{
    mock::MockApplication application;

    yli::ontology::ConsoleStruct my_console_struct(0, 39, 15, 0); // Some dummy dimensions.
    yli::ontology::Console* const my_console = application.get_abstract_entity_factory().create_console(
        my_console_struct);

    yli::memory::MemoryAllocator<yli::ontology::AbstractConsoleLispFunctionOverload> memory_allocator(
        yli::data::Datatype::CONSOLE_LISP_FUNCTION_OVERLOAD);
    yli::ontology::AbstractConsoleLispFunctionOverload* console_lisp_function_overload =
            memory_allocator.build_in(
                application,
                application.get_universe(),
                &my_console->parent_of_console_lisp_functions,
                &yli::ontology::Variable::set_variable_const_std_string);
    ASSERT_NE(console_lisp_function_overload, nullptr);
}
