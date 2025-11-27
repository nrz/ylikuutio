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
#include <string_view> // std::string_view

// Tests for conversion from UTF-8 to UTF-32

TEST(utf8_must_be_read_appropriately, a)
{
    std::string_view input_string { "a" };
    std::string_view::const_iterator it = input_string.cbegin();
    {
        std::optional<char32_t> codepoint = yli::string::read_codepoint(it, input_string.cend());
        ASSERT_EQ(codepoint, U'a');
    }
    ASSERT_EQ(it, input_string.cend());
}

TEST(utf8_must_be_read_appropriately, ab)
{
    std::string_view input_string { "ab" };
    std::string_view::const_iterator it = input_string.cbegin();
    {
        std::optional<char32_t> codepoint = yli::string::read_codepoint(it, input_string.cend());
        ASSERT_EQ(codepoint, U'a');
    }
    {
        std::optional<char32_t> codepoint = yli::string::read_codepoint(it, input_string.cend());
        ASSERT_EQ(codepoint, U'b');
    }
    ASSERT_EQ(it, input_string.cend());
}

TEST(utf8_must_be_read_appropriately, o_with_dots)
{
    std::string_view input_string { "ö" };
    std::string_view::const_iterator it = input_string.cbegin();
    {
        std::optional<char32_t> codepoint = yli::string::read_codepoint(it, input_string.cend());
        ASSERT_EQ(codepoint, U'ö');
    }
    ASSERT_EQ(it, input_string.cend());
}

TEST(utf8_must_be_read_appropriately, tokyo_in_japanese)
{
    std::string_view input_string { "東京" };
    std::string_view::const_iterator it = input_string.cbegin();
    {
        std::optional<char32_t> codepoint = yli::string::read_codepoint(it, input_string.cend());
        ASSERT_EQ(codepoint, U'東');
    }
    {
        std::optional<char32_t> codepoint = yli::string::read_codepoint(it, input_string.cend());
        ASSERT_EQ(codepoint, U'京');
    }
    ASSERT_EQ(it, input_string.cend());
}

TEST(utf8_must_be_read_appropriately, mayan_zero)
{
    std::string_view input_string { "𝋠" };
    std::string_view::const_iterator it = input_string.cbegin();
    {
        std::optional<char32_t> codepoint = yli::string::read_codepoint(it, input_string.cend());
        ASSERT_EQ(codepoint, U'𝋠');
    }
    ASSERT_EQ(it, input_string.cend());
}

TEST(utf8_must_be_converted_to_utf32_appropriately, a)
{
    std::string_view input_string { "a" };
    std::u32string expected { U"a" };
    std::optional<std::u32string> result = yli::string::u8_to_u32(input_string);
    ASSERT_EQ(*result, expected);
}

TEST(utf8_must_be_converted_to_utf32_appropriately, ab)
{
    std::string_view input_string { "ab" };
    std::u32string expected { U"ab" };
    std::optional<std::u32string> result = yli::string::u8_to_u32(input_string);
    ASSERT_EQ(*result, expected);
}

TEST(utf8_must_be_converted_to_utf32_appropriately, o_with_dots)
{
    std::string_view input_string { "ö" };
    std::u32string expected { U"ö" };
    std::optional<std::u32string> result = yli::string::u8_to_u32(input_string);
    ASSERT_EQ(*result, expected);
}

TEST(utf8_must_be_converted_to_utf32_appropriately, tokyo_in_japanese)
{
    std::string_view input_string { "東京" }; // e6 9d b1 e4 ba ac (2 3-byte codepoints)
    std::u32string expected { U"東京" }; // 0x6771 0x4eac
    std::optional<std::u32string> result = yli::string::u8_to_u32(input_string);
    std::optional<std::u32string> u32 = yli::string::u8_to_u32(input_string);
    std::optional<std::string> u8 = yli::string::u32_to_u8(*u32);
    ASSERT_EQ(*result, expected);
}

TEST(utf8_must_be_converted_to_utf32_appropriately, mayan_zero)
{
    std::string_view input_string { "𝋠" }; // f0 9d 8b a0 (1 4-byte codepoint)
    std::u32string expected { U"𝋠" }; // 0x1d2e0
    std::optional<std::u32string> result = yli::string::u8_to_u32(input_string);
    ASSERT_EQ(result, expected);
}

// Tests for conversion from UTF-32 to UTF-8

TEST(utf32_must_be_converted_to_utf8_appropriately, a)
{
    std::u32string input_string { U"a" };
    std::string_view expected { "a" };
    std::optional<std::string> result = yli::string::u32_to_u8(input_string);
    ASSERT_EQ(result, expected);
}

TEST(utf32_must_be_converted_to_utf8_appropriately, ab)
{
    std::u32string input_string { U"ab" };
    std::string_view expected { "ab" };
    std::optional<std::string> result = yli::string::u32_to_u8(input_string);
    ASSERT_EQ(result, expected);
}

TEST(utf32_must_be_converted_to_utf8_appropriately, o_with_dots)
{
    std::u32string input_string { U"ö" };
    std::string_view expected { "ö" };
    std::optional<std::string> result = yli::string::u32_to_u8(input_string);
    ASSERT_EQ(result, expected);
}

TEST(utf32_must_be_converted_to_utf8_appropriately, tokyo_in_japanese)
{
    std::u32string input_string { U"東京" }; // 0x6771 0x4eac
    std::string_view expected { "東京" }; // e6 9d b1 e4 ba ac (2 3-byte codepoints)
    std::optional<std::string> result = yli::string::u32_to_u8(input_string);
    ASSERT_EQ(result, expected);
}

TEST(utf32_must_be_converted_to_utf8_appropriately, mayan_zero)
{
    std::u32string input_string { U"𝋠" }; // 0x1d2e0
    std::string_view expected { "𝋠" };         // f0 9d 8b a0 (1 4-byte codepoint)
    std::optional<std::string> result = yli::string::u32_to_u8(input_string);
    ASSERT_EQ(result, expected);
}
