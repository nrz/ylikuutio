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
#include "code/ylikuutio/memory/constructible_module.hpp"

TEST(constructible_module_must_be_initialized_appropriately, constructible_module)
{
    // Some arbitrary values.
    const int datatype = 1001;
    const uint32_t storage_i = 2002;
    const uint32_t slot_i = 3003;

    yli::memory::ConstructibleModule constructible_module(datatype, storage_i, slot_i);
    ASSERT_EQ(constructible_module.datatype, datatype);
    ASSERT_EQ(constructible_module.storage_i, storage_i);
    ASSERT_EQ(constructible_module.slot_i, slot_i);
}
