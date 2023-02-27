// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/console.hpp"
#include "code/ylikuutio/ontology/input_mode.hpp"
#include "code/ylikuutio/ontology/universe_struct.hpp"
#include "code/ylikuutio/ontology/input_mode_struct.hpp"
#include "code/ylikuutio/ontology/console_struct.hpp"
#include "code/ylikuutio/render/graphics_api_backend.hpp"

TEST(input_mode_must_be_initialized_appropriately, headless_universe_no_console_master)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::InputModeStruct input_mode_struct;
    yli::ontology::InputMode* const input_mode = new yli::ontology::InputMode(
            *universe,
            input_mode_struct,
            &universe->parent_of_input_modes,
            nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 1);

    // `Entity` member functions.
    ASSERT_EQ(input_mode->get_childID(), 0);
    ASSERT_EQ(input_mode->get_type(), "yli::ontology::InputMode*");
    ASSERT_FALSE(input_mode->get_can_be_erased());
    ASSERT_EQ(&(input_mode->get_universe()), universe);
    ASSERT_EQ(input_mode->get_scene(), nullptr);
    ASSERT_EQ(input_mode->get_parent(), universe);
    ASSERT_EQ(input_mode->get_number_of_non_variable_children(), 0);
}

TEST(input_mode_must_be_initialized_appropriately, headless_universe_and_console_master)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::ConsoleStruct console_struct;
    yli::ontology::Console* console = new yli::ontology::Console(
            *universe,
            console_struct,
            &universe->parent_of_consoles,
            nullptr);

    yli::ontology::InputModeStruct input_mode_struct;
    yli::ontology::InputMode* const input_mode = new yli::ontology::InputMode(
            *universe,
            input_mode_struct,
            &universe->parent_of_input_modes,
            &console->master_of_input_modes);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 2); // `Console`, `InputMode`.

    // `Entity` member functions.
    ASSERT_EQ(input_mode->get_childID(), 0);
    ASSERT_EQ(input_mode->get_type(), "yli::ontology::InputMode*");
    ASSERT_FALSE(input_mode->get_can_be_erased());
    ASSERT_EQ(&(input_mode->get_universe()), universe);
    ASSERT_EQ(input_mode->get_scene(), nullptr);
    ASSERT_EQ(input_mode->get_parent(), universe);
    ASSERT_EQ(input_mode->get_number_of_non_variable_children(), 0);

    // `Console` member functions.
    ASSERT_EQ(console->get_number_of_apprentices(), 1);
}
