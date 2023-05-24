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
#include "code/ylikuutio/memory/memory_templates.hpp"

// Include standard headers
#include <stdint.h> // uint32_t etc.

TEST(read_nonaligned_32_bit_read_must_function_properly, offset_0)
{
    uint8_t bytes[] = { 0xef, 0xbe, 0xad, 0xde };
    uint32_t value = yli::memory::read_nonaligned_32_bit<uint8_t, uint32_t>(bytes, 0);
    ASSERT_EQ(value, 0xdeadbeef);
}

TEST(read_nonaligned_32_bit_read_must_function_properly, offset_1)
{
    uint8_t bytes[] = { 0x00, 0xef, 0xbe, 0xad, 0xde };
    uint32_t value = yli::memory::read_nonaligned_32_bit<uint8_t, uint32_t>(bytes, 1);
    ASSERT_EQ(value, 0xdeadbeef);
}

TEST(read_nonaligned_32_bit_read_must_function_properly, offset_2)
{
    uint8_t bytes[] = { 0x00, 0x00, 0xef, 0xbe, 0xad, 0xde };
    uint32_t value = yli::memory::read_nonaligned_32_bit<uint8_t, uint32_t>(bytes, 2);
    ASSERT_EQ(value, 0xdeadbeef);
}

TEST(read_nonaligned_32_bit_read_must_function_properly, offset_3)
{
    uint8_t bytes[] = { 0x00, 0x00, 0x00, 0xef, 0xbe, 0xad, 0xde };
    uint32_t value = yli::memory::read_nonaligned_32_bit<uint8_t, uint32_t>(bytes, 3);
    ASSERT_EQ(value, 0xdeadbeef);
}
