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
#include "code/ylikuutio/data/datatype.hpp"
#include "code/ylikuutio/ontology/console_callback_engine.hpp"
#include "code/ylikuutio/ontology/request.hpp"
#include "code/ylikuutio/ontology/console_callback_engine_struct.hpp"

// Include standard headers
#include <cstddef> // std::size_t, uintptr_t
#include <limits>  // std::numeric_limits

namespace yli::ontology
{
    class GenericParentModule;
}

TEST(console_callback_engine_must_be_initialized_appropriately, universe_provided_as_valid_pointer)
{
    mock::MockApplication application;
    yli::ontology::ConsoleCallbackEngineStruct console_callback_engine_struct { yli::ontology::Request<yli::ontology::Console>(nullptr) };
    yli::ontology::ConsoleCallbackEngine* const console_callback_engine = application.get_generic_entity_factory().create_console_callback_engine(
            console_callback_engine_struct);
    ASSERT_NE(console_callback_engine, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(console_callback_engine) % alignof(yli::ontology::ConsoleCallbackEngine), 0);

    for (int datatype = 0; datatype < yli::data::Datatype::MAX_VALUE; datatype++)
    {
        const yli::ontology::GenericParentModule* const generic_parent_module = console_callback_engine->get_generic_parent_module(datatype);

        if (datatype == yli::data::Datatype::CONSOLE_CALLBACK_OBJECT)
        {
            ASSERT_NE(generic_parent_module, nullptr);
        }
        else
        {
            ASSERT_EQ(generic_parent_module, nullptr);
        }
    }

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 0);

    // `Entity` member functions.
    ASSERT_EQ(console_callback_engine->get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(console_callback_engine->get_type(), "yli::ontology::ConsoleCallbackEngine*");
    ASSERT_FALSE(console_callback_engine->get_can_be_erased());
    ASSERT_EQ(console_callback_engine->get_scene(), nullptr);
    ASSERT_EQ(console_callback_engine->get_parent(), nullptr);
    ASSERT_EQ(console_callback_engine->get_number_of_non_variable_children(), 0);
}
