// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2026 Antti Nuortimo.
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
#include "code/ylikuutio/memory/allocation_data.hpp"
#include "code/ylikuutio/memory/handle.hpp"

// Include standard headers
#include <cstdint> // std::uint32_t

TEST(allocation_data_must_be_initialized_appropriately, allocation_data)
{
    yli::memory::MemoryAllocator memory_allocator(yli::data::Datatype::UNIVERSE);

    // Some arbitrary values.
    constexpr std::uint32_t type = 404;
    constexpr std::uint32_t slot_i = 3003;

    const yli::memory::Handle handle { type, slot_i };
    const yli::memory::AllocationData allocation_data { memory_allocator, handle };
    ASSERT_EQ(allocation_data.handle.get_type(), type);
    ASSERT_EQ(allocation_data.handle.get_slot_i(), slot_i);
}
