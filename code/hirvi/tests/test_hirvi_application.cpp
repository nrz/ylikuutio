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
#include "code/hirvi/hirvi.hpp"
#include "code/hirvi/data/datatype.hpp"
#include "code/ylikuutio/memory/memory_system.hpp"
#include "code/ylikuutio/ontology/universe.hpp"

// Include standard headers
#include <cstddef> // uintptr_t

TEST(hirvi_application_must_be_initialized_appropriately, hirvi_application)
{
    const int argc { 0 };
    const char** const argv { nullptr };
    hirvi::HirviApplication hirvi_application(argc, argv);
    ASSERT_EQ(hirvi_application.get_memory_system().get_universe_datatype(), hirvi::Datatype::UNIVERSE);

    yli::ontology::Universe& universe = hirvi_application.entity_factory.get_universe();
    ASSERT_EQ(universe, hirvi_application.get_universe());
    ASSERT_EQ(reinterpret_cast<uintptr_t>(&universe) % alignof(yli::ontology::Universe), 0);
}
