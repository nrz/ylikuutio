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
#include "code/ylikuutio/data/datatype.hpp"
#include "code/ylikuutio/memory/memory_allocator.hpp"
#include "code/ylikuutio/memory/memory_storage.hpp"
#include "code/ylikuutio/memory/constructible_module.hpp"

TEST(memory_storage_must_be_initialized_appropriately, default_memory_storage_storage_i_0)
{
    yli::memory::MemoryAllocator memory_allocator(yli::data::Datatype::UNIVERSE);

    yli::memory::MemoryStorage memory_storage(memory_allocator, 0);
    ASSERT_EQ(memory_storage.get_storage_id(), 0);
    ASSERT_EQ(memory_storage.get_number_of_instances(), 0);
}

TEST(memory_storage_must_be_initialized_appropriately, default_memory_storage_storage_i_1)
{
    yli::memory::MemoryAllocator memory_allocator(yli::data::Datatype::UNIVERSE);

    yli::memory::MemoryStorage memory_storage(memory_allocator, 1);
    ASSERT_EQ(memory_storage.get_storage_id(), 1);
    ASSERT_EQ(memory_storage.get_number_of_instances(), 0);
}
