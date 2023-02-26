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
#include "code/ylikuutio/ontology/callback_engine.hpp"
#include "code/ylikuutio/ontology/universe_struct.hpp"
#include "code/ylikuutio/render/graphics_api_backend.hpp"

TEST(callback_engine_must_be_initialized_appropriately, headless_universe)
{
    yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::HEADLESS);
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    yli::ontology::CallbackEngine* const callback_engine = new yli::ontology::CallbackEngine(
            *universe,
            &universe->parent_of_callback_engines);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(universe->get_number_of_non_variable_children(), 1);

    // `Entity` member functions.
    ASSERT_EQ(callback_engine->get_childID(), 0);
    ASSERT_EQ(callback_engine->get_type(), "yli::ontology::CallbackEngine*");
    ASSERT_FALSE(callback_engine->get_can_be_erased());
    ASSERT_EQ(&(callback_engine->get_universe()), universe);
    ASSERT_EQ(callback_engine->get_scene(), nullptr);
    ASSERT_EQ(callback_engine->get_parent(), universe);
    ASSERT_EQ(callback_engine->get_number_of_non_variable_children(), 0);
}
