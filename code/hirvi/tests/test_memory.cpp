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
#include "code/hirvi/datatype.hpp"
#include "code/ylikuutio/memory/generic_memory_system.hpp"
#include "code/ylikuutio/memory/memory_system.hpp"

// Include standard headers
#include <cstddef> // std::size_t

TEST(memory_system_must_be_initialized_appropriately, hirvi_application)
{
    const int argc { 0 };
    const char** const argv { nullptr };
    hirvi::HirviApplication hirvi_application(argc, argv);

    const auto& memory_system = static_cast<yli::memory::MemorySystem<hirvi::Datatype>&>(hirvi_application.get_memory_system());
    hirvi::Datatype universe_datatype = memory_system.get_universe_datatype();
    ASSERT_EQ(universe_datatype, hirvi::Datatype::UNIVERSE);

    std::size_t n_allocators { 0 };

    for (int datatype = 0; datatype < hirvi::Datatype::MAX_VALUE; datatype++)
    {
        bool has_allocator = memory_system.has_allocator(datatype);

        if (has_allocator)
        {
            n_allocators++;
            const auto& memory_allocator = memory_system.get_allocator(datatype);

            if (datatype == hirvi::Datatype::UNIVERSE)
            {
                // `Universe` gets created by the `HirviApplication` constructor.
                ASSERT_EQ(memory_allocator.get_number_of_storages(), 1);
                ASSERT_EQ(memory_allocator.get_number_of_instances(), 1);
            }
            else if (datatype == hirvi::Datatype::VARIABLE)
            {
                // `Variable` called `should_render` gets created by the `HirviApplication` constructor.
                ASSERT_EQ(memory_allocator.get_number_of_storages(), 1);
                ASSERT_EQ(memory_allocator.get_number_of_instances(), 1);
            }
            else if (datatype == hirvi::Datatype::AUDIO_SYSTEM)
            {
                // `AudioSystem` gets created by the `HirviApplication` constructor.
                ASSERT_EQ(memory_allocator.get_number_of_storages(), 1);
                ASSERT_EQ(memory_allocator.get_number_of_instances(), 1);
            }
            else
            {
                // At this point there should be no other instances.
                ASSERT_EQ(memory_allocator.get_number_of_storages(), 0);
                ASSERT_EQ(memory_allocator.get_number_of_instances(), 0);
            }
        }
    }

    ASSERT_EQ(memory_system.get_number_of_allocators(), n_allocators);
}
