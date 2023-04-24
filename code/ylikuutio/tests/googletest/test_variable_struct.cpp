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
#include "code/mock/mock_application.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/universe_struct.hpp"
#include "code/ylikuutio/ontology/variable_struct.hpp"
#include "code/ylikuutio/render/graphics_api_backend.hpp"

TEST(variable_struct_must_be_initialized_appropriately, variable_struct_default_constructor)
{
    mock::MockApplication application;

    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(application, universe_struct);

    const yli::ontology::VariableStruct test_variable_struct(*universe, universe);
    ASSERT_EQ(test_variable_struct.parent, universe);
    ASSERT_EQ(test_variable_struct.activate_callback, nullptr);
    ASSERT_EQ(test_variable_struct.read_callback, nullptr);
    ASSERT_TRUE(test_variable_struct.should_call_activate_callback_now);
    ASSERT_EQ(test_variable_struct.global_name, "");
    ASSERT_EQ(test_variable_struct.local_name, "");
    ASSERT_TRUE(test_variable_struct.is_variable);
}

TEST(variable_struct_must_be_initialized_appropriately, variable_struct_copy_constructor)
{
    mock::MockApplication application;

    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(application, universe_struct);

    yli::ontology::VariableStruct original_variable_struct(*universe, universe);
    original_variable_struct.global_name = "foo";
    original_variable_struct.local_name = "bar";
    const yli::ontology::VariableStruct copy_variable_struct(original_variable_struct);
    ASSERT_EQ(copy_variable_struct.parent, universe);
    ASSERT_EQ(copy_variable_struct.activate_callback, nullptr);
    ASSERT_EQ(copy_variable_struct.read_callback, nullptr);
    ASSERT_TRUE(copy_variable_struct.should_call_activate_callback_now);
    ASSERT_EQ(copy_variable_struct.global_name, "foo");
    ASSERT_EQ(copy_variable_struct.local_name, "bar");
    ASSERT_TRUE(copy_variable_struct.is_variable);
}
