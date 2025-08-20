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
#include "code/ylikuutio/string/unicode.hpp"

// Include standard headers
#include <optional> // std::optional
#include <string>   // std::string, std::u32string

// Tests for conversion from UTF-8 to UTF-32

TEST(utf8_must_be_converted_to_utf32_appropriately, a)
{
    std::string input_string { "a" };
    std::u32string expected { U"a" };
    std::optional<std::u32string> result = yli::string::u8_to_u32(input_string);
    ASSERT_EQ(*result, expected);
}

TEST(utf8_must_be_converted_to_utf32_appropriately, ab)
{
    std::string input_string { "ab" };
    std::u32string expected { U"ab" };
    std::optional<std::u32string> result = yli::string::u8_to_u32(input_string);
    ASSERT_EQ(*result, expected);
}

TEST(utf8_must_be_converted_to_utf32_appropriately, o_with_dots)
{
    std::string input_string { "ö" };
    std::u32string expected { U"ö" };
    std::optional<std::u32string> result = yli::string::u8_to_u32(input_string);
    ASSERT_EQ(*result, expected);
}

TEST(utf8_must_be_converted_to_utf32_appropriately, tokyo_in_japanese)
{
    std::string input_string { "東京" }; // e6 9d b1 e4 ba ac (2 3-byte codepoints)
    std::u32string expected { U"東京" }; // 0x6771 0x4eac
    std::optional<std::u32string> result = yli::string::u8_to_u32(input_string);
    std::optional<std::u32string> u32 = yli::string::u8_to_u32(input_string);
    std::optional<std::string> u8 = yli::string::u32_to_u8(*u32);
    ASSERT_EQ(*result, expected);
}

TEST(utf8_must_be_converted_to_utf32_appropriately, mayan_zero)
{
    std::string input_string { "𝋠" }; // f0 9d 8b a0 (1 4-byte codepoint)
    std::u32string expected { U"𝋠" }; // 0x1d2e0
    std::optional<std::u32string> result = yli::string::u8_to_u32(input_string);
    ASSERT_EQ(result, expected);
}

// Tests for conversion from UTF-32 to UTF-8

TEST(utf32_must_be_converted_to_utf8_appropriately, a)
{
    std::u32string input_string { U"a" };
    std::string expected { "a" };
    std::optional<std::string> result = yli::string::u32_to_u8(input_string);
    ASSERT_EQ(result, expected);
}

TEST(utf32_must_be_converted_to_utf8_appropriately, ab)
{
    std::u32string input_string { U"ab" };
    std::string expected { "ab" };
    std::optional<std::string> result = yli::string::u32_to_u8(input_string);
    ASSERT_EQ(result, expected);
}

TEST(utf32_must_be_converted_to_utf8_appropriately, o_with_dots)
{
    std::u32string input_string { U"ö" };
    std::string expected { "ö" };
    std::optional<std::string> result = yli::string::u32_to_u8(input_string);
    ASSERT_EQ(result, expected);
}

TEST(utf32_must_be_converted_to_utf8_appropriately, tokyo_in_japanese)
{
    std::u32string input_string { U"東京" }; // 0x6771 0x4eac
    std::string expected { "東京" }; // e6 9d b1 e4 ba ac (2 3-byte codepoints)
    std::optional<std::string> result = yli::string::u32_to_u8(input_string);
    ASSERT_EQ(result, expected);
}

TEST(utf32_must_be_converted_to_utf8_appropriately, mayan_zero)
{
    std::u32string input_string { U"𝋠" }; // 0x1d2e0
    std::string expected { "𝋠" };         // f0 9d 8b a0 (1 4-byte codepoint)
    std::optional<std::string> result = yli::string::u32_to_u8(input_string);
    ASSERT_EQ(result, expected);
}
