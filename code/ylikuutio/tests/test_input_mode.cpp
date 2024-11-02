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
#include "code/ylikuutio/ontology/console.hpp"
#include "code/ylikuutio/ontology/input_mode.hpp"
#include "code/ylikuutio/ontology/request.hpp"
#include "code/ylikuutio/ontology/input_mode_struct.hpp"
#include "code/ylikuutio/ontology/console_struct.hpp"

// Include standard headers
#include <cstddef> // uintptr_t

TEST(input_mode_must_be_initialized_appropriately, headless_universe_no_console_master)
{
    mock::MockApplication application;

    yli::ontology::InputModeStruct input_mode_struct;
    yli::ontology::InputMode* const input_mode = application.get_generic_entity_factory().create_input_mode(input_mode_struct);
    ASSERT_NE(input_mode, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(input_mode) % alignof(yli::ontology::InputMode), 0);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions.
    ASSERT_EQ(input_mode->get_childID(), 0);
    ASSERT_EQ(input_mode->get_type(), "yli::ontology::InputMode*");
    ASSERT_FALSE(input_mode->get_can_be_erased());
    ASSERT_EQ(input_mode->get_scene(), nullptr);
    ASSERT_EQ(input_mode->get_parent(), &application.get_universe());
    ASSERT_EQ(input_mode->get_number_of_non_variable_children(), 0);
}

TEST(input_mode_must_be_initialized_appropriately, headless_universe_and_console_master)
{
    mock::MockApplication application;

    yli::ontology::ConsoleStruct console_struct;
    yli::ontology::Console* console = application.get_generic_entity_factory().create_console(console_struct);

    yli::ontology::InputModeStruct input_mode_struct;
    input_mode_struct.console_master = yli::ontology::Request(console);
    yli::ontology::InputMode* const input_mode = application.get_generic_entity_factory().create_input_mode(input_mode_struct);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 2); // `Console`, `InputMode`.

    // `Entity` member functions.
    ASSERT_EQ(input_mode->get_childID(), 0);
    ASSERT_EQ(input_mode->get_type(), "yli::ontology::InputMode*");
    ASSERT_FALSE(input_mode->get_can_be_erased());
    ASSERT_EQ(input_mode->get_scene(), nullptr);
    ASSERT_EQ(input_mode->get_parent(), &application.get_universe());
    ASSERT_EQ(input_mode->get_number_of_non_variable_children(), 0);

    // `Console` member functions.
    ASSERT_EQ(console->get_number_of_apprentices(), 1);
}
