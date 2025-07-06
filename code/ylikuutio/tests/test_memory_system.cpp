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
#include "code/ylikuutio/data/datatype.hpp"
#include "code/ylikuutio/memory/memory_allocator.hpp"
#include "code/ylikuutio/memory/memory_system.hpp"
#include "code/ylikuutio/memory/memory_storage.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/scene.hpp"

namespace yli::memory
{
    class GenericMemoryAllocator;
}

TEST(memory_system_must_be_initialized_appropriately, default_memory_system_no_application)
{
    yli::memory::MemorySystem memory_system(yli::data::Datatype::UNIVERSE);
    ASSERT_FALSE(memory_system.has_allocator(yli::data::Datatype::UNIVERSE));
    ASSERT_EQ(memory_system.get_number_of_allocators(), 0);
    ASSERT_EQ(memory_system.get_universe_datatype(), yli::data::Datatype::UNIVERSE);
}
