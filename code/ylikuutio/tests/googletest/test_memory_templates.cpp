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
#include "code/ylikuutio/memory/memory_templates.hpp"

// Include standard headers
#include <array>    // std::array
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

TEST(copy_circular_buffer_into_vector_must_function_properly, offset_0_size_0)
{
    const std::array<uint32_t, 0> buffer {};
    std::vector<uint32_t> copy = yli::memory::copy_circular_buffer_into_vector(buffer, 0, 0);
    ASSERT_EQ(copy.size(), 0);
}

TEST(copy_circular_buffer_into_vector_must_function_properly, offset_0_size_1)
{
    const std::array<uint32_t, 1> buffer { 10 };
    std::vector<uint32_t> copy = yli::memory::copy_circular_buffer_into_vector(buffer, 0, 1);
    ASSERT_EQ(copy.size(), 1);
    ASSERT_EQ(copy.at(0), 10);
}

TEST(copy_circular_buffer_into_vector_must_function_properly, offset_0_size_2)
{
    const std::array<uint32_t, 2> buffer { 10, 20 };
    std::vector<uint32_t> copy = yli::memory::copy_circular_buffer_into_vector(buffer, 0, 2);
    ASSERT_EQ(copy.size(), 2);
    ASSERT_EQ(copy.at(0), 10);
    ASSERT_EQ(copy.at(1), 20);
}

TEST(copy_circular_buffer_into_vector_must_function_properly, offset_1_size_2)
{
    const std::array<uint32_t, 2> buffer { 20, 10 };
    std::vector<uint32_t> copy = yli::memory::copy_circular_buffer_into_vector(buffer, 1, 2);
    ASSERT_EQ(copy.size(), 2);
    ASSERT_EQ(copy.at(0), 10);
    ASSERT_EQ(copy.at(1), 20);
}

TEST(copy_circular_buffer_into_vector_must_function_properly, offset_0_size_3)
{
    const std::array<uint32_t, 3> buffer { 10, 20, 30 };
    std::vector<uint32_t> copy = yli::memory::copy_circular_buffer_into_vector(buffer, 0, 3);
    ASSERT_EQ(copy.size(), 3);
    ASSERT_EQ(copy.at(0), 10);
    ASSERT_EQ(copy.at(1), 20);
    ASSERT_EQ(copy.at(2), 30);
}

TEST(copy_circular_buffer_into_vector_must_function_properly, offset_1_size_3)
{
    const std::array<uint32_t, 3> buffer { 30, 10, 20 };
    std::vector<uint32_t> copy = yli::memory::copy_circular_buffer_into_vector(buffer, 1, 3);
    ASSERT_EQ(copy.size(), 3);
    ASSERT_EQ(copy.at(0), 10);
    ASSERT_EQ(copy.at(1), 20);
    ASSERT_EQ(copy.at(2), 30);
}

TEST(copy_circular_buffer_into_vector_must_function_properly, offset_2_size_3)
{
    const std::array<uint32_t, 3> buffer { 20, 30, 10 };
    std::vector<uint32_t> copy = yli::memory::copy_circular_buffer_into_vector(buffer, 2, 3);
    ASSERT_EQ(copy.size(), 3);
    ASSERT_EQ(copy.at(0), 10);
    ASSERT_EQ(copy.at(1), 20);
    ASSERT_EQ(copy.at(2), 30);
}

TEST(copy_circular_buffer_into_vector_must_function_properly, offset_0_size_4)
{
    const std::array<uint32_t, 4> buffer { 10, 20, 30, 40 };
    std::vector<uint32_t> copy = yli::memory::copy_circular_buffer_into_vector(buffer, 0, 4);
    ASSERT_EQ(copy.size(), 4);
    ASSERT_EQ(copy.at(0), 10);
    ASSERT_EQ(copy.at(1), 20);
    ASSERT_EQ(copy.at(2), 30);
    ASSERT_EQ(copy.at(3), 40);
}

TEST(copy_circular_buffer_into_vector_must_function_properly, offset_1_size_4)
{
    const std::array<uint32_t, 4> buffer { 40, 10, 20, 30 };
    std::vector<uint32_t> copy = yli::memory::copy_circular_buffer_into_vector(buffer, 1, 4);
    ASSERT_EQ(copy.size(), 4);
    ASSERT_EQ(copy.at(0), 10);
    ASSERT_EQ(copy.at(1), 20);
    ASSERT_EQ(copy.at(2), 30);
    ASSERT_EQ(copy.at(3), 40);
}

TEST(copy_circular_buffer_into_vector_must_function_properly, offset_2_size_4)
{
    const std::array<uint32_t, 4> buffer { 30, 40, 10, 20 };
    std::vector<uint32_t> copy = yli::memory::copy_circular_buffer_into_vector(buffer, 2, 4);
    ASSERT_EQ(copy.size(), 4);
    ASSERT_EQ(copy.at(0), 10);
    ASSERT_EQ(copy.at(1), 20);
    ASSERT_EQ(copy.at(2), 30);
    ASSERT_EQ(copy.at(3), 40);
}

TEST(copy_circular_buffer_into_vector_must_function_properly, offset_3_size_4)
{
    const std::array<uint32_t, 4> buffer { 20, 30, 40, 10 };
    std::vector<uint32_t> copy = yli::memory::copy_circular_buffer_into_vector(buffer, 3, 4);
    ASSERT_EQ(copy.size(), 4);
    ASSERT_EQ(copy.at(0), 10);
    ASSERT_EQ(copy.at(1), 20);
    ASSERT_EQ(copy.at(2), 30);
    ASSERT_EQ(copy.at(3), 40);
}
