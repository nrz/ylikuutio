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
#include "code/ylikuutio/memory/handle.hpp"

// Include standard headers
#include <cstdint> // std::uint32_t

TEST(handle_must_be_initialized_appropriately, type_0_slot_0)
{
    constexpr std::uint32_t type { 0 };
    constexpr std::uint32_t slot_i { 0 };
    const yli::memory::Handle handle { type, slot_i };
    ASSERT_EQ(handle.get_type(), type);
    ASSERT_EQ(handle.get_slot_i(), slot_i);
}

TEST(handle_must_be_initialized_appropriately, type_0_slot_1)
{
    constexpr std::uint32_t type { 0 };
    constexpr std::uint32_t slot_i { 1 };
    const yli::memory::Handle handle { type, slot_i };
    ASSERT_EQ(handle.get_type(), type);
    ASSERT_EQ(handle.get_slot_i(), slot_i);
}

TEST(handle_must_be_initialized_appropriately, type_0_slot_2)
{
    constexpr std::uint32_t type { 0 };
    constexpr std::uint32_t slot_i { 2 };
    const yli::memory::Handle handle { type, slot_i };
    ASSERT_EQ(handle.get_type(), type);
    ASSERT_EQ(handle.get_slot_i(), slot_i);
}

TEST(handle_must_be_initialized_appropriately, type_0_slot_4194303)
{
    constexpr std::uint32_t type { 0 };
    constexpr std::uint32_t slot_i { 4194303 };
    const yli::memory::Handle handle { type, slot_i };
    ASSERT_EQ(handle.get_type(), type);
    ASSERT_EQ(handle.get_slot_i(), slot_i);
}

TEST(handle_must_be_initialized_appropriately, type_1_slot_0)
{
    constexpr std::uint32_t type { 1 };
    constexpr std::uint32_t slot_i { 0 };
    const yli::memory::Handle handle { type, slot_i };
    ASSERT_EQ(handle.get_type(), type);
    ASSERT_EQ(handle.get_slot_i(), slot_i);
}

TEST(handle_must_be_initialized_appropriately, type_1_slot_1)
{
    constexpr std::uint32_t type { 1 };
    constexpr std::uint32_t slot_i { 1 };
    const yli::memory::Handle handle { type, slot_i };
    ASSERT_EQ(handle.get_type(), type);
    ASSERT_EQ(handle.get_slot_i(), slot_i);
}

TEST(handle_must_be_initialized_appropriately, type_1_slot_2)
{
    constexpr std::uint32_t type { 1 };
    constexpr std::uint32_t slot_i { 2 };
    const yli::memory::Handle handle { type, slot_i };
    ASSERT_EQ(handle.get_type(), type);
    ASSERT_EQ(handle.get_slot_i(), slot_i);
}

TEST(handle_must_be_initialized_appropriately, type_1_slot_4194303)
{
    constexpr std::uint32_t type { 1 };
    constexpr std::uint32_t slot_i { 4194303 };
    const yli::memory::Handle handle { type, slot_i };
    ASSERT_EQ(handle.get_type(), type);
    ASSERT_EQ(handle.get_slot_i(), slot_i);
}

TEST(handle_must_be_initialized_appropriately, type_2_slot_0)
{
    constexpr std::uint32_t type { 2 };
    constexpr std::uint32_t slot_i { 0 };
    const yli::memory::Handle handle { type, slot_i };
    ASSERT_EQ(handle.get_type(), type);
    ASSERT_EQ(handle.get_slot_i(), slot_i);
}

TEST(handle_must_be_initialized_appropriately, type_2_slot_1)
{
    constexpr std::uint32_t type { 2 };
    constexpr std::uint32_t slot_i { 1 };
    const yli::memory::Handle handle { type, slot_i };
    ASSERT_EQ(handle.get_type(), type);
    ASSERT_EQ(handle.get_slot_i(), slot_i);
}

TEST(handle_must_be_initialized_appropriately, type_2_slot_2)
{
    constexpr std::uint32_t type { 2 };
    constexpr std::uint32_t slot_i { 2 };
    const yli::memory::Handle handle { type, slot_i };
    ASSERT_EQ(handle.get_type(), type);
    ASSERT_EQ(handle.get_slot_i(), slot_i);
}

TEST(handle_must_be_initialized_appropriately, type_2_slot_4194303)
{
    constexpr std::uint32_t type { 2 };
    constexpr std::uint32_t slot_i { 4194303 };
    const yli::memory::Handle handle { type, slot_i };
    ASSERT_EQ(handle.get_type(), type);
    ASSERT_EQ(handle.get_slot_i(), slot_i);
}

TEST(handle_must_be_initialized_appropriately, type_1023_slot_0)
{
    constexpr std::uint32_t type { 1023 };
    constexpr std::uint32_t slot_i { 0 };
    const yli::memory::Handle handle { type, slot_i };
    ASSERT_EQ(handle.get_type(), type);
    ASSERT_EQ(handle.get_slot_i(), slot_i);
}

TEST(handle_must_be_initialized_appropriately, type_1023_slot_1)
{
    constexpr std::uint32_t type { 1023 };
    constexpr std::uint32_t slot_i { 1 };
    const yli::memory::Handle handle { type, slot_i };
    ASSERT_EQ(handle.get_type(), type);
    ASSERT_EQ(handle.get_slot_i(), slot_i);
}

TEST(handle_must_be_initialized_appropriately, type_1023_slot_2)
{
    constexpr std::uint32_t type { 1023 };
    constexpr std::uint32_t slot_i { 2 };
    const yli::memory::Handle handle { type, slot_i };
    ASSERT_EQ(handle.get_type(), type);
    ASSERT_EQ(handle.get_slot_i(), slot_i);
}

TEST(handle_must_be_initialized_appropriately, type_1023_slot_4194303)
{
    constexpr std::uint32_t type { 1023 };
    constexpr std::uint32_t slot_i { 4194303 };
    const yli::memory::Handle handle { type, slot_i };
    ASSERT_EQ(handle.get_type(), type);
    ASSERT_EQ(handle.get_slot_i(), slot_i);
}
