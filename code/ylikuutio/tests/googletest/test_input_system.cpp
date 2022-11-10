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
#include "code/ylikuutio/input/input.hpp"
#include "code/ylikuutio/ontology/universe.hpp"

TEST(input_system_must_be_set_to_nullptr_in_headless_mode, universe)
{
    mock::MockApplication application;
    ASSERT_EQ(application.get_universe().get_input_system(), nullptr);
    ASSERT_EQ(application.get_universe().get_input_method(), yli::input::InputMethod::KEYBOARD);
}

TEST(input_system_must_be_set_to_nullptr_when_using_software_rendering, universe)
{
    mock::MockApplication application;
    ASSERT_EQ(application.get_universe().get_input_system(), nullptr);
    ASSERT_EQ(application.get_universe().get_input_method(), yli::input::InputMethod::KEYBOARD);
}
