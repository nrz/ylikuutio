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
#include "code/ylikuutio/string/ylikuutio_string.hpp"

TEST(unicode_value_from_string, char_only_a)
{
    const char text[] = "a";
    const char* text_pointer = text;
    ASSERT_EQ(yli::string::extract_unicode_value_from_string(text_pointer), 'a');
}

TEST(unicode_value_from_string, char_only_abc)
{
    const char text[] = "abc";
    const char* text_pointer = text;
    ASSERT_EQ(yli::string::extract_unicode_value_from_string(text_pointer), 'a');
    ASSERT_EQ(yli::string::extract_unicode_value_from_string(text_pointer), 'b');
    ASSERT_EQ(yli::string::extract_unicode_value_from_string(text_pointer), 'c');
}

TEST(unicode_value_from_string, unicode_a)
{
    const char text[] = "&#xa;";
    const char* text_pointer = text;
    ASSERT_EQ(yli::string::extract_unicode_value_from_string(text_pointer), 0xa);
}

TEST(unicode_value_from_string, unicode_deadbeef)
{
    const char text[] = "&#xdeadbeef;";
    const char* text_pointer = text;
    ASSERT_EQ(yli::string::extract_unicode_value_from_string(text_pointer), 0xdeadbeef);
}

TEST(unicode_value_from_string, iloinen_10cc1_01c00_ja_c1e1ece_caace101_kaikkialle)
{
    const char text[] = "iloinen&#x10cc1;&#x01c00;ja&#xc1e1ece;&#xcaace101;kaikkialle";
    const char* text_pointer = text;
    ASSERT_EQ(yli::string::extract_unicode_value_from_string(text_pointer), 'i');
    ASSERT_EQ(yli::string::extract_unicode_value_from_string(text_pointer), 'l');
    ASSERT_EQ(yli::string::extract_unicode_value_from_string(text_pointer), 'o');
    ASSERT_EQ(yli::string::extract_unicode_value_from_string(text_pointer), 'i');
    ASSERT_EQ(yli::string::extract_unicode_value_from_string(text_pointer), 'n');
    ASSERT_EQ(yli::string::extract_unicode_value_from_string(text_pointer), 'e');
    ASSERT_EQ(yli::string::extract_unicode_value_from_string(text_pointer), 'n');
    ASSERT_EQ(yli::string::extract_unicode_value_from_string(text_pointer), 0x10cc1);
    ASSERT_EQ(yli::string::extract_unicode_value_from_string(text_pointer), 0x01c00);
    ASSERT_EQ(yli::string::extract_unicode_value_from_string(text_pointer), 'j');
    ASSERT_EQ(yli::string::extract_unicode_value_from_string(text_pointer), 'a');
    ASSERT_EQ(yli::string::extract_unicode_value_from_string(text_pointer), 0xc1e1ece);
    ASSERT_EQ(yli::string::extract_unicode_value_from_string(text_pointer), 0xcaace101);
    ASSERT_EQ(yli::string::extract_unicode_value_from_string(text_pointer), 'k');
    ASSERT_EQ(yli::string::extract_unicode_value_from_string(text_pointer), 'a');
    ASSERT_EQ(yli::string::extract_unicode_value_from_string(text_pointer), 'i');
    ASSERT_EQ(yli::string::extract_unicode_value_from_string(text_pointer), 'k');
    ASSERT_EQ(yli::string::extract_unicode_value_from_string(text_pointer), 'k');
    ASSERT_EQ(yli::string::extract_unicode_value_from_string(text_pointer), 'i');
    ASSERT_EQ(yli::string::extract_unicode_value_from_string(text_pointer), 'a');
    ASSERT_EQ(yli::string::extract_unicode_value_from_string(text_pointer), 'l');
    ASSERT_EQ(yli::string::extract_unicode_value_from_string(text_pointer), 'l');
    ASSERT_EQ(yli::string::extract_unicode_value_from_string(text_pointer), 'e');
}
