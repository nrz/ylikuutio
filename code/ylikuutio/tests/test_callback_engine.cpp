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
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/callback_engine.hpp"
#include "code/ylikuutio/ontology/callback_engine_struct.hpp"

// Include standard headers
#include <cstddef> // uintptr_t

namespace yli::ontology
{
    class GenericParentModule;
    class Brain;
}

TEST(callback_engine_must_be_initialized_appropriately, headless_universe)
{
    mock::MockApplication application;

    yli::ontology::CallbackEngineStruct callback_engine_struct;
    yli::ontology::CallbackEngine* const callback_engine = application.get_generic_entity_factory().create_callback_engine(
            callback_engine_struct);
    ASSERT_NE(callback_engine, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(callback_engine) % alignof(yli::ontology::CallbackEngine), 0);

    for (int datatype = 0; datatype < yli::data::Datatype::MAX_VALUE; datatype++)
    {
        const yli::ontology::GenericParentModule* const generic_parent_module = callback_engine->get_generic_parent_module(datatype);

        if (datatype == yli::data::Datatype::CALLBACK_OBJECT)
        {
            ASSERT_NE(generic_parent_module, nullptr);
        }
        else
        {
            ASSERT_EQ(generic_parent_module, nullptr);
        }
    }

    ASSERT_NE(callback_engine->get_generic_master_module<yli::ontology::Brain>(), nullptr);

    // `Entity` member functions of `Universe`.
    ASSERT_EQ(application.get_universe().get_number_of_non_variable_children(), 1);

    // `Entity` member functions.
    ASSERT_EQ(callback_engine->get_childID(), 0);
    ASSERT_EQ(callback_engine->get_type(), "yli::ontology::CallbackEngine*");
    ASSERT_FALSE(callback_engine->get_can_be_erased());
    ASSERT_EQ(callback_engine->get_scene(), nullptr);
    ASSERT_EQ(callback_engine->get_parent(), &application.get_universe());
    ASSERT_EQ(callback_engine->get_number_of_non_variable_children(), 0);
}
