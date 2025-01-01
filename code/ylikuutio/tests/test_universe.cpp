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
#include "code/ylikuutio/ontology/universe.hpp"

// Include standard headers
#include <cstddef> // std::size_t, uintptr_t
#include <limits>  // std::numeric_limits

TEST(universe_must_be_initialized_appropriately, headless)
{
    mock::MockApplication application;
    yli::ontology::Universe& universe = application.get_universe();
    ASSERT_EQ(reinterpret_cast<uintptr_t>(&universe) % alignof(yli::ontology::Universe), 0);

    // `Universe` member variables.
    ASSERT_FALSE(universe.is_invert_mouse_in_use);
    ASSERT_FALSE(universe.is_first_turbo_pressed);
    ASSERT_FALSE(universe.is_second_turbo_pressed);
    ASSERT_TRUE(universe.is_exit_requested);
    ASSERT_FALSE(universe.in_console);
    ASSERT_TRUE(universe.in_help_mode);
    ASSERT_TRUE(universe.can_display_help_screen);

    // `Universe` member functions.
    ASSERT_TRUE(universe.get_is_headless());
    ASSERT_EQ(universe.get_number_of_ecosystems(), 0);
    ASSERT_EQ(universe.get_number_of_scenes(), 0);
    ASSERT_EQ(universe.get_active_scene(), nullptr);

    // `Entity` member functions.
    ASSERT_EQ(universe.get_childID(), std::numeric_limits<std::size_t>::max());
    ASSERT_EQ(universe.get_type(), "yli::ontology::Universe*");
    ASSERT_FALSE(universe.get_can_be_erased());
    ASSERT_EQ(universe.get_scene(), nullptr);
    ASSERT_EQ(universe.get_parent(), nullptr);
    ASSERT_EQ(universe.get_number_of_non_variable_children(), 0);
}

TEST(universe_must_be_given_a_global_name_appropriately, headless)
{
    mock::MockApplication application;
    yli::ontology::Universe& universe = application.get_universe();
    ASSERT_EQ(universe.get_global_name(), "");
    ASSERT_EQ(universe.get_local_name(), "");

    universe.set_global_name("foo");
    ASSERT_EQ(universe.get_global_name(), "foo");
    ASSERT_EQ(universe.get_local_name(), "");
}

TEST(universe_must_not_accept_a_local_name_before_setting_a_global_name, headless)
{
    mock::MockApplication application;
    yli::ontology::Universe& universe = application.get_universe();
    ASSERT_EQ(universe.get_global_name(), "");
    ASSERT_EQ(universe.get_local_name(), "");

    universe.set_local_name("foo");
    ASSERT_EQ(universe.get_global_name(), "");
    ASSERT_EQ(universe.get_local_name(), "");
}

TEST(universe_must_not_accept_a_local_name_after_setting_a_global_name, headless)
{
    mock::MockApplication application;
    yli::ontology::Universe& universe = application.get_universe();
    ASSERT_EQ(universe.get_global_name(), "");
    ASSERT_EQ(universe.get_local_name(), "");

    universe.set_global_name("foo");
    universe.set_local_name("bar");
    ASSERT_EQ(universe.get_global_name(), "foo");
    ASSERT_EQ(universe.get_local_name(), "");
}
