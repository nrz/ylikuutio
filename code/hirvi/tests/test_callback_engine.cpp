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
#include "code/hirvi/hirvi.hpp"
#include "code/ylikuutio/snippets/brain_snippets.hpp"
#include "code/ylikuutio/memory/constructible_module.hpp"
#include "code/ylikuutio/ontology/callback_engine.hpp"

// Include standard headers
#include <cstddef> // uintptr_t

TEST(callback_engine_must_be_initialized_appropriately, hirvi_callback_engine)
{
    const int argc { 0 };
    const char** const argv { nullptr };
    hirvi::HirviApplication hirvi_application(argc, argv);

    yli::ontology::CallbackEngineStruct rest_callback_engine_struct;
    yli::ontology::CallbackEngine* const rest_callback_engine = hirvi_application.get_entity_factory().create_callback_engine(rest_callback_engine_struct);
    rest_callback_engine->create_callback_object(&yli::snippets::rest);
    ASSERT_NE(rest_callback_engine, nullptr);
    ASSERT_EQ(reinterpret_cast<uintptr_t>(rest_callback_engine) % alignof(yli::ontology::CallbackEngine), 0);
    yli::memory::ConstructibleModule callback_engine_constructible_module = rest_callback_engine->get_constructible_module();
    ASSERT_EQ(callback_engine_constructible_module.storage_i, 0);
    ASSERT_EQ(callback_engine_constructible_module.slot_i, 0);
    ASSERT_EQ(callback_engine_constructible_module.alive, true);
}
