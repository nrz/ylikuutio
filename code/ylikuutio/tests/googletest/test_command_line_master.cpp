// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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
#include "code/ylikuutio/command_line/command_line_master.hpp"

TEST(is_key_must_function_properly, no_keys)
{
    const int argc = 1; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    const char* argv[] = { first_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_TRUE(command_line_master.get_are_arguments_valid());
    ASSERT_FALSE(command_line_master.is_key("foo_executable"));
    ASSERT_FALSE(command_line_master.is_key("foo"));
    ASSERT_FALSE(command_line_master.is_key("bar"));
}

TEST(is_key_must_function_properly, one_key_without_value)
{
    const int argc = 2; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "bar";
    const char* argv[] = { first_arg, second_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_FALSE(command_line_master.get_are_arguments_valid());
    ASSERT_FALSE(command_line_master.is_key("foo_executable"));
    ASSERT_FALSE(command_line_master.is_key("foo"));
    ASSERT_FALSE(command_line_master.is_key("bar"));
    ASSERT_FALSE(command_line_master.is_key("baz"));
}

TEST(is_key_must_function_properly, one_key_without_value_double_dash)
{
    const int argc = 2; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "--bar";
    const char* argv[] = { first_arg, second_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_TRUE(command_line_master.get_are_arguments_valid());
    ASSERT_FALSE(command_line_master.is_key("foo_executable"));
    ASSERT_FALSE(command_line_master.is_key("foo"));
    ASSERT_TRUE(command_line_master.is_key("bar"));
    ASSERT_FALSE(command_line_master.is_key("-bar"));
    ASSERT_FALSE(command_line_master.is_key("--bar"));
    ASSERT_FALSE(command_line_master.is_key("baz"));
}

TEST(is_key_must_function_properly, one_key_without_value_triple_dash)
{
    const int argc = 2; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "---bar";
    const char* argv[] = { first_arg, second_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_FALSE(command_line_master.get_are_arguments_valid());
    ASSERT_FALSE(command_line_master.is_key("foo_executable"));
    ASSERT_FALSE(command_line_master.is_key("foo"));
    ASSERT_FALSE(command_line_master.is_key("bar"));
    ASSERT_FALSE(command_line_master.is_key("-bar"));
    ASSERT_FALSE(command_line_master.is_key("--bar"));
    ASSERT_FALSE(command_line_master.is_key("---bar"));
    ASSERT_FALSE(command_line_master.is_key("baz"));
}

TEST(is_key_must_function_properly, one_key_with_value)
{
    const int argc = 2; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "bar=baz";
    const char* argv[] = { first_arg, second_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_FALSE(command_line_master.get_are_arguments_valid());
    ASSERT_FALSE(command_line_master.is_key("foo_executable"));
    ASSERT_FALSE(command_line_master.is_key("foo"));
    ASSERT_FALSE(command_line_master.is_key("bar"));
    ASSERT_FALSE(command_line_master.is_key("bar="));
    ASSERT_FALSE(command_line_master.is_key("=bar"));
    ASSERT_FALSE(command_line_master.is_key("bar=baz"));
    ASSERT_FALSE(command_line_master.is_key("=bar=baz"));
    ASSERT_FALSE(command_line_master.is_key("baz"));
    ASSERT_FALSE(command_line_master.is_key("=baz"));
    ASSERT_FALSE(command_line_master.is_key("baz=baz"));
    ASSERT_FALSE(command_line_master.is_key("qux"));
}

TEST(is_key_must_function_properly, one_key_with_value_double_dash)
{
    const int argc = 2; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "--bar=baz";
    const char* argv[] = { first_arg, second_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_TRUE(command_line_master.get_are_arguments_valid());
    ASSERT_FALSE(command_line_master.is_key("foo_executable"));
    ASSERT_FALSE(command_line_master.is_key("foo"));
    ASSERT_TRUE(command_line_master.is_key("bar"));
    ASSERT_FALSE(command_line_master.is_key("bar="));
    ASSERT_FALSE(command_line_master.is_key("=bar"));
    ASSERT_FALSE(command_line_master.is_key("bar=baz"));
    ASSERT_FALSE(command_line_master.is_key("=bar=baz"));
    ASSERT_FALSE(command_line_master.is_key("baz"));
    ASSERT_FALSE(command_line_master.is_key("=baz"));
    ASSERT_FALSE(command_line_master.is_key("baz=baz"));
    ASSERT_FALSE(command_line_master.is_key("qux"));
}

TEST(is_key_must_function_properly, two_keys_without_value)
{
    const int argc = 3; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "bar";
    char third_arg[] = "baz";
    const char* argv[] = { first_arg, second_arg, third_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_FALSE(command_line_master.get_are_arguments_valid());
    ASSERT_FALSE(command_line_master.is_key("foo_executable"));
    ASSERT_FALSE(command_line_master.is_key("foo"));
    ASSERT_FALSE(command_line_master.is_key("bar"));
    ASSERT_FALSE(command_line_master.is_key("baz"));
    ASSERT_FALSE(command_line_master.is_key("qux"));
}

TEST(is_key_must_function_properly, two_keys_without_value_first_with_double_dash)
{
    const int argc = 3; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "--bar";
    char third_arg[] = "baz";
    const char* argv[] = { first_arg, second_arg, third_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_TRUE(command_line_master.get_are_arguments_valid());
    ASSERT_FALSE(command_line_master.is_key("foo_executable"));
    ASSERT_FALSE(command_line_master.is_key("foo"));
    ASSERT_TRUE(command_line_master.is_key("bar"));
    ASSERT_FALSE(command_line_master.is_key("baz"));
    ASSERT_FALSE(command_line_master.is_key("qux"));
}

TEST(is_key_must_function_properly, two_keys_without_value_second_with_double_dash)
{
    const int argc = 3; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "bar";
    char third_arg[] = "--baz";
    const char* argv[] = { first_arg, second_arg, third_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_FALSE(command_line_master.get_are_arguments_valid());
    ASSERT_FALSE(command_line_master.is_key("foo_executable"));
    ASSERT_FALSE(command_line_master.is_key("foo"));
    ASSERT_FALSE(command_line_master.is_key("bar"));
    ASSERT_TRUE(command_line_master.is_key("baz"));
    ASSERT_FALSE(command_line_master.is_key("qux"));
}

TEST(is_key_must_function_properly, two_keys_without_value_both_with_double_dash)
{
    const int argc = 3; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "--bar";
    char third_arg[] = "--baz";
    const char* argv[] = { first_arg, second_arg, third_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_TRUE(command_line_master.get_are_arguments_valid());
    ASSERT_FALSE(command_line_master.is_key("foo_executable"));
    ASSERT_FALSE(command_line_master.is_key("foo"));
    ASSERT_TRUE(command_line_master.is_key("bar"));
    ASSERT_TRUE(command_line_master.is_key("baz"));
    ASSERT_FALSE(command_line_master.is_key("qux"));
}

TEST(is_key_must_function_properly, two_keys_with_value)
{
    const int argc = 3; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "bar=baz";
    char third_arg[] = "qux=quux";
    const char* argv[] = { first_arg, second_arg, third_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_FALSE(command_line_master.get_are_arguments_valid());
    ASSERT_FALSE(command_line_master.is_key("foo_executable"));
    ASSERT_FALSE(command_line_master.is_key("foo"));
    ASSERT_FALSE(command_line_master.is_key("bar"));
    ASSERT_FALSE(command_line_master.is_key("bar="));
    ASSERT_FALSE(command_line_master.is_key("=bar"));
    ASSERT_FALSE(command_line_master.is_key("bar=baz"));
    ASSERT_FALSE(command_line_master.is_key("baz"));
    ASSERT_FALSE(command_line_master.is_key("=baz"));
    ASSERT_FALSE(command_line_master.is_key("baz=baz"));
    ASSERT_FALSE(command_line_master.is_key("qux"));
    ASSERT_FALSE(command_line_master.is_key("qux="));
    ASSERT_FALSE(command_line_master.is_key("=qux"));
    ASSERT_FALSE(command_line_master.is_key("qux=quux"));
    ASSERT_FALSE(command_line_master.is_key("quux"));
    ASSERT_FALSE(command_line_master.is_key("quux="));
    ASSERT_FALSE(command_line_master.is_key("=quux"));
}

TEST(is_key_must_function_properly, two_keys_with_value_first_with_double_dash)
{
    const int argc = 3; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "--bar=baz";
    char third_arg[] = "qux=quux";
    const char* argv[] = { first_arg, second_arg, third_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_FALSE(command_line_master.get_are_arguments_valid());
    ASSERT_FALSE(command_line_master.is_key("foo_executable"));
    ASSERT_FALSE(command_line_master.is_key("foo"));
    ASSERT_TRUE(command_line_master.is_key("bar"));
    ASSERT_FALSE(command_line_master.is_key("bar="));
    ASSERT_FALSE(command_line_master.is_key("=bar"));
    ASSERT_FALSE(command_line_master.is_key("bar=baz"));
    ASSERT_FALSE(command_line_master.is_key("baz"));
    ASSERT_FALSE(command_line_master.is_key("=baz"));
    ASSERT_FALSE(command_line_master.is_key("baz=baz"));
    ASSERT_FALSE(command_line_master.is_key("qux"));
    ASSERT_FALSE(command_line_master.is_key("qux="));
    ASSERT_FALSE(command_line_master.is_key("=qux"));
    ASSERT_FALSE(command_line_master.is_key("qux=quux"));
    ASSERT_FALSE(command_line_master.is_key("quux"));
    ASSERT_FALSE(command_line_master.is_key("quux="));
    ASSERT_FALSE(command_line_master.is_key("=quux"));
}

TEST(is_key_must_function_properly, two_keys_with_value_second_with_double_dash)
{
    const int argc = 3; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "bar=baz";
    char third_arg[] = "--qux=quux";
    const char* argv[] = { first_arg, second_arg, third_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_FALSE(command_line_master.get_are_arguments_valid());
    ASSERT_FALSE(command_line_master.is_key("foo_executable"));
    ASSERT_FALSE(command_line_master.is_key("foo"));
    ASSERT_FALSE(command_line_master.is_key("bar"));
    ASSERT_FALSE(command_line_master.is_key("bar="));
    ASSERT_FALSE(command_line_master.is_key("=bar"));
    ASSERT_FALSE(command_line_master.is_key("bar=baz"));
    ASSERT_FALSE(command_line_master.is_key("baz"));
    ASSERT_FALSE(command_line_master.is_key("=baz"));
    ASSERT_FALSE(command_line_master.is_key("baz=baz"));
    ASSERT_TRUE(command_line_master.is_key("qux"));
    ASSERT_FALSE(command_line_master.is_key("qux="));
    ASSERT_FALSE(command_line_master.is_key("=qux"));
    ASSERT_FALSE(command_line_master.is_key("qux=quux"));
    ASSERT_FALSE(command_line_master.is_key("quux"));
    ASSERT_FALSE(command_line_master.is_key("quux="));
    ASSERT_FALSE(command_line_master.is_key("=quux"));
}

TEST(is_key_must_function_properly, two_keys_with_value_both_with_double_dash)
{
    const int argc = 3; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "--bar=baz";
    char third_arg[] = "--qux=quux";
    const char* argv[] = { first_arg, second_arg, third_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_TRUE(command_line_master.get_are_arguments_valid());
    ASSERT_FALSE(command_line_master.is_key("foo_executable"));
    ASSERT_FALSE(command_line_master.is_key("foo"));
    ASSERT_TRUE(command_line_master.is_key("bar"));
    ASSERT_FALSE(command_line_master.is_key("bar="));
    ASSERT_FALSE(command_line_master.is_key("=bar"));
    ASSERT_FALSE(command_line_master.is_key("bar=baz"));
    ASSERT_FALSE(command_line_master.is_key("baz"));
    ASSERT_FALSE(command_line_master.is_key("=baz"));
    ASSERT_FALSE(command_line_master.is_key("baz=baz"));
    ASSERT_TRUE(command_line_master.is_key("qux"));
    ASSERT_FALSE(command_line_master.is_key("qux="));
    ASSERT_FALSE(command_line_master.is_key("=qux"));
    ASSERT_FALSE(command_line_master.is_key("qux=quux"));
    ASSERT_FALSE(command_line_master.is_key("quux"));
    ASSERT_FALSE(command_line_master.is_key("quux="));
    ASSERT_FALSE(command_line_master.is_key("=quux"));
}

TEST(is_key_must_function_properly, three_keys_without_value_first_and_third_with_double_dash)
{
    const int argc = 4; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "--bar";
    char third_arg[] = "baz";
    char fourth_arg[] = "--qux";
    const char* argv[] = { first_arg, second_arg, third_arg, fourth_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_TRUE(command_line_master.get_are_arguments_valid());
    ASSERT_FALSE(command_line_master.is_key("foo_executable"));
    ASSERT_FALSE(command_line_master.is_key("foo"));
    ASSERT_TRUE(command_line_master.is_key("bar"));
    ASSERT_FALSE(command_line_master.is_key("bar="));
    ASSERT_FALSE(command_line_master.is_key("=bar"));
    ASSERT_FALSE(command_line_master.is_key("bar=baz"));
    ASSERT_FALSE(command_line_master.is_key("baz"));
    ASSERT_FALSE(command_line_master.is_key("=baz"));
    ASSERT_FALSE(command_line_master.is_key("baz=baz"));
    ASSERT_TRUE(command_line_master.is_key("qux"));
    ASSERT_FALSE(command_line_master.is_key("qux="));
    ASSERT_FALSE(command_line_master.is_key("=qux"));
    ASSERT_FALSE(command_line_master.is_key("qux=quux"));
    ASSERT_FALSE(command_line_master.is_key("quux"));
    ASSERT_FALSE(command_line_master.is_key("quux="));
    ASSERT_FALSE(command_line_master.is_key("=quux"));
}

TEST(get_value_must_function_properly, no_keys)
{
    const int argc = 1; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    const char* argv[] = { first_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_EQ(command_line_master.get_value("foo_executable"), "");
    ASSERT_EQ(command_line_master.get_value("foo"), "");
    ASSERT_EQ(command_line_master.get_value("bar"), "");
}

TEST(get_value_must_function_properly, one_key_without_value)
{
    const int argc = 2; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "bar";
    const char* argv[] = { first_arg, second_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_EQ(command_line_master.get_value("foo_executable"), "");
    ASSERT_EQ(command_line_master.get_value("foo"), "");
    ASSERT_EQ(command_line_master.get_value("bar"), "");
    ASSERT_EQ(command_line_master.get_value("baz"), "");
}

TEST(get_value_must_function_properly, one_key_without_value_double_dash)
{
    const int argc = 2; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "--bar";
    const char* argv[] = { first_arg, second_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_EQ(command_line_master.get_value("foo_executable"), "");
    ASSERT_EQ(command_line_master.get_value("foo"), "");
    ASSERT_EQ(command_line_master.get_value("bar"), "");
    ASSERT_EQ(command_line_master.get_value("baz"), "");
}

TEST(get_value_must_function_properly, one_key_without_value_triple_dash)
{
    const int argc = 2; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "---bar";
    const char* argv[] = { first_arg, second_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_EQ(command_line_master.get_value("foo_executable"), "");
    ASSERT_EQ(command_line_master.get_value("foo"), "");
    ASSERT_EQ(command_line_master.get_value("bar"), "");
    ASSERT_EQ(command_line_master.get_value("baz"), "");
}

TEST(get_value_must_function_properly, one_key_with_value)
{
    const int argc = 2; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "bar=baz";
    const char* argv[] = { first_arg, second_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_EQ(command_line_master.get_value("foo_executable"), "");
    ASSERT_EQ(command_line_master.get_value("foo"), "");
    ASSERT_EQ(command_line_master.get_value("bar"), "");
    ASSERT_EQ(command_line_master.get_value("baz"), "");
    ASSERT_EQ(command_line_master.get_value("qux"), "");
}

TEST(get_value_must_function_properly, one_key_with_value_double_dash)
{
    const int argc = 2; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "--bar=baz";
    const char* argv[] = { first_arg, second_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_EQ(command_line_master.get_value("foo_executable"), "");
    ASSERT_EQ(command_line_master.get_value("foo"), "");
    ASSERT_EQ(command_line_master.get_value("bar"), "baz");
    ASSERT_EQ(command_line_master.get_value("baz"), "");
    ASSERT_EQ(command_line_master.get_value("qux"), "");
}

TEST(get_value_must_function_properly, two_keys_with_value)
{
    const int argc = 3; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "bar=baz";
    char third_arg[] = "qux=quux";
    const char* argv[] = { first_arg, second_arg, third_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_EQ(command_line_master.get_value("foo_executable"), "");
    ASSERT_EQ(command_line_master.get_value("foo"), "");
    ASSERT_EQ(command_line_master.get_value("bar"), "");
    ASSERT_EQ(command_line_master.get_value("baz"), "");
    ASSERT_EQ(command_line_master.get_value("qux"), "");
    ASSERT_EQ(command_line_master.get_value("quux"), "");
}

TEST(get_value_must_function_properly, two_keys_with_value_first_with_double_dash)
{
    const int argc = 3; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "--bar=baz";
    char third_arg[] = "qux=quux";
    const char* argv[] = { first_arg, second_arg, third_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_EQ(command_line_master.get_value("foo_executable"), "");
    ASSERT_EQ(command_line_master.get_value("foo"), "");
    ASSERT_EQ(command_line_master.get_value("bar"), "baz");
    ASSERT_EQ(command_line_master.get_value("baz"), "");
    ASSERT_EQ(command_line_master.get_value("qux"), "");
    ASSERT_EQ(command_line_master.get_value("quux"), "");
}
TEST(get_value_must_function_properly, two_keys_with_value_second_with_double_dash)
{
    const int argc = 3; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "bar=baz";
    char third_arg[] = "--qux=quux";
    const char* argv[] = { first_arg, second_arg, third_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_EQ(command_line_master.get_value("foo_executable"), "");
    ASSERT_EQ(command_line_master.get_value("foo"), "");
    ASSERT_EQ(command_line_master.get_value("bar"), "");
    ASSERT_EQ(command_line_master.get_value("baz"), "");
    ASSERT_EQ(command_line_master.get_value("qux"), "quux");
    ASSERT_EQ(command_line_master.get_value("quux"), "");
}
TEST(get_value_must_function_properly, two_keys_with_value_both_with_double_dash)
{
    const int argc = 3; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "--bar=baz";
    char third_arg[] = "--qux=quux";
    const char* argv[] = { first_arg, second_arg, third_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_EQ(command_line_master.get_value("foo_executable"), "");
    ASSERT_EQ(command_line_master.get_value("foo"), "");
    ASSERT_EQ(command_line_master.get_value("bar"), "baz");
    ASSERT_EQ(command_line_master.get_value("baz"), "");
    ASSERT_EQ(command_line_master.get_value("qux"), "quux");
    ASSERT_EQ(command_line_master.get_value("quux"), "");
}

TEST(get_value_must_function_properly, two_keys_without_value_first_with_double_dash)
{
    const int argc = 3; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "--bar";
    char third_arg[] = "baz";
    const char* argv[] = { first_arg, second_arg, third_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_EQ(command_line_master.get_value("foo_executable"), "");
    ASSERT_EQ(command_line_master.get_value("foo"), "");
    ASSERT_EQ(command_line_master.get_value("bar"), "baz");
    ASSERT_EQ(command_line_master.get_value("baz"), "");
    ASSERT_EQ(command_line_master.get_value("qux"), "");
    ASSERT_EQ(command_line_master.get_value("quux"), "");
}

TEST(get_value_must_function_properly, three_keys_without_value_first_and_third_with_double_dash)
{
    const int argc = 4; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "--bar";
    char third_arg[] = "baz";
    char fourth_arg[] = "--qux";
    const char* argv[] = { first_arg, second_arg, third_arg, fourth_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_EQ(command_line_master.get_value("foo_executable"), "");
    ASSERT_EQ(command_line_master.get_value("foo"), "");
    ASSERT_EQ(command_line_master.get_value("bar"), "baz");
    ASSERT_EQ(command_line_master.get_value("baz"), "");
    ASSERT_EQ(command_line_master.get_value("qux"), "");
    ASSERT_EQ(command_line_master.get_value("quux"), "");
}

TEST(get_invalid_keys_must_function_properly, no_keys_no_valid_keys)
{
    const int argc = 1; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    const char* argv[] = { first_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_TRUE(command_line_master.get_are_arguments_valid());

    std::vector<std::string> valid_keys;
    ASSERT_TRUE(command_line_master.get_invalid_keys(valid_keys).empty());
}

TEST(get_invalid_keys_must_function_properly, no_keys_one_valid_key)
{
    const int argc = 1; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    const char* argv[] = { first_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_TRUE(command_line_master.get_are_arguments_valid());

    std::vector<std::string> valid_keys { "foo" };
    ASSERT_TRUE(command_line_master.get_invalid_keys(valid_keys).empty());
}

TEST(get_invalid_keys_must_function_properly, no_keys_two_valid_keys)
{
    const int argc = 1; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    const char* argv[] = { first_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_TRUE(command_line_master.get_are_arguments_valid());

    std::vector<std::string> valid_keys { "foo", "bar" };
    ASSERT_TRUE(command_line_master.get_invalid_keys(valid_keys).empty());
}

TEST(get_invalid_keys_must_function_properly, one_key_with_double_dash_no_valid_keys)
{
    const int argc = 2; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "--bar";
    const char* argv[] = { first_arg, second_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_TRUE(command_line_master.get_are_arguments_valid());

    std::vector<std::string> valid_keys;
    std::vector<std::string> invalid_keys = command_line_master.get_invalid_keys(valid_keys);
    ASSERT_FALSE(invalid_keys.empty());

    ASSERT_EQ(invalid_keys.size(), 1);
    ASSERT_EQ(invalid_keys[0], "bar");
}

TEST(get_invalid_keys_must_function_properly, two_keys_with_double_dash_no_valid_keys)
{
    const int argc = 3; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "--bar";
    char third_arg[] = "--baz";
    const char* argv[] = { first_arg, second_arg, third_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_TRUE(command_line_master.get_are_arguments_valid());

    std::vector<std::string> valid_keys;
    std::vector<std::string> invalid_keys = command_line_master.get_invalid_keys(valid_keys);
    ASSERT_FALSE(invalid_keys.empty());

    ASSERT_EQ(invalid_keys.size(), 2);
    ASSERT_EQ(invalid_keys[0], "bar");
    ASSERT_EQ(invalid_keys[1], "baz");
}

TEST(get_invalid_keys_must_function_properly, one_key_with_double_dash_one_matching_valid_key)
{
    const int argc = 2; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "--bar";
    const char* argv[] = { first_arg, second_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_TRUE(command_line_master.get_are_arguments_valid());

    std::vector<std::string> valid_keys { "bar" };
    std::vector<std::string> invalid_keys = command_line_master.get_invalid_keys(valid_keys);
    ASSERT_TRUE(invalid_keys.empty());
}

TEST(get_invalid_keys_must_function_properly, one_key_with_double_dash_one_nonmatching_valid_key)
{
    const int argc = 2; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "--bar";
    const char* argv[] = { first_arg, second_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_TRUE(command_line_master.get_are_arguments_valid());

    std::vector<std::string> valid_keys { "baz" };
    std::vector<std::string> invalid_keys = command_line_master.get_invalid_keys(valid_keys);
    ASSERT_FALSE(invalid_keys.empty());

    ASSERT_EQ(invalid_keys.size(), 1);
    ASSERT_EQ(invalid_keys[0], "bar");
}

TEST(get_invalid_keys_must_function_properly, one_key_with_double_dash_one_matching_valid_key_and_one_nonmatching_valid_key)
{
    const int argc = 2; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "--bar";
    const char* argv[] = { first_arg, second_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_TRUE(command_line_master.get_are_arguments_valid());

    std::vector<std::string> valid_keys { "bar", "baz" };
    std::vector<std::string> invalid_keys = command_line_master.get_invalid_keys(valid_keys);
    ASSERT_TRUE(invalid_keys.empty());
}

TEST(get_invalid_keys_must_function_properly, one_key_with_double_dash_one_nonmatching_valid_key_and_one_matching_valid_key)
{
    const int argc = 2; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "--bar";
    const char* argv[] = { first_arg, second_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_TRUE(command_line_master.get_are_arguments_valid());

    std::vector<std::string> valid_keys { "baz", "bar" };
    std::vector<std::string> invalid_keys = command_line_master.get_invalid_keys(valid_keys);
    ASSERT_TRUE(invalid_keys.empty());
}

TEST(get_invalid_keys_must_function_properly, two_keys_with_double_dash_one_valid_key_matching_first_key)
{
    const int argc = 3; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "--bar";
    char third_arg[] = "--baz";
    const char* argv[] = { first_arg, second_arg, third_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_TRUE(command_line_master.get_are_arguments_valid());

    std::vector<std::string> valid_keys { "bar" };
    std::vector<std::string> invalid_keys = command_line_master.get_invalid_keys(valid_keys);
    ASSERT_FALSE(invalid_keys.empty());

    ASSERT_EQ(invalid_keys.size(), 1);
    ASSERT_EQ(invalid_keys[0], "baz");
}

TEST(get_invalid_keys_must_function_properly, two_keys_with_double_dash_one_valid_key_matching_second_key)
{
    const int argc = 3; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "--bar";
    char third_arg[] = "--baz";
    const char* argv[] = { first_arg, second_arg, third_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_TRUE(command_line_master.get_are_arguments_valid());

    std::vector<std::string> valid_keys { "baz" };
    std::vector<std::string> invalid_keys = command_line_master.get_invalid_keys(valid_keys);
    ASSERT_FALSE(invalid_keys.empty());

    ASSERT_EQ(invalid_keys.size(), 1);
    ASSERT_EQ(invalid_keys[0], "bar");
}

TEST(get_invalid_keys_must_function_properly, two_keys_with_double_dash_one_valid_key_matching_first_key_and_one_nonmatching_valid_key)
{
    const int argc = 3; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "--bar";
    char third_arg[] = "--baz";
    const char* argv[] = { first_arg, second_arg, third_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_TRUE(command_line_master.get_are_arguments_valid());

    std::vector<std::string> valid_keys { "bar", "qux" };
    std::vector<std::string> invalid_keys = command_line_master.get_invalid_keys(valid_keys);
    ASSERT_FALSE(invalid_keys.empty());

    ASSERT_EQ(invalid_keys.size(), 1);
    ASSERT_EQ(invalid_keys[0], "baz");
}

TEST(get_invalid_keys_must_function_properly, two_keys_with_double_dash_one_valid_key_matching_second_key_and_one_nonmatching_valid_key)
{
    const int argc = 3; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "--bar";
    char third_arg[] = "--baz";
    const char* argv[] = { first_arg, second_arg, third_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_TRUE(command_line_master.get_are_arguments_valid());

    std::vector<std::string> valid_keys { "baz", "qux" };
    std::vector<std::string> invalid_keys = command_line_master.get_invalid_keys(valid_keys);
    ASSERT_FALSE(invalid_keys.empty());

    ASSERT_EQ(invalid_keys.size(), 1);
    ASSERT_EQ(invalid_keys[0], "bar");
}

TEST(get_invalid_keys_must_function_properly, two_keys_with_double_dash_one_nonmatching_valid_key_and_one_valid_key_matching_first_key)
{
    const int argc = 3; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "--bar";
    char third_arg[] = "--baz";
    const char* argv[] = { first_arg, second_arg, third_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_TRUE(command_line_master.get_are_arguments_valid());

    std::vector<std::string> valid_keys { "qux", "bar" };
    std::vector<std::string> invalid_keys = command_line_master.get_invalid_keys(valid_keys);
    ASSERT_FALSE(invalid_keys.empty());

    ASSERT_EQ(invalid_keys.size(), 1);
    ASSERT_EQ(invalid_keys[0], "baz");
}

TEST(get_invalid_keys_must_function_properly, two_keys_with_double_dash_one_nonmatching_valid_key_and_one_valid_key_matching_second_key)
{
    const int argc = 3; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "--bar";
    char third_arg[] = "--baz";
    const char* argv[] = { first_arg, second_arg, third_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_TRUE(command_line_master.get_are_arguments_valid());

    std::vector<std::string> valid_keys { "qux", "baz" };
    std::vector<std::string> invalid_keys = command_line_master.get_invalid_keys(valid_keys);
    ASSERT_FALSE(invalid_keys.empty());

    ASSERT_EQ(invalid_keys.size(), 1);
    ASSERT_EQ(invalid_keys[0], "bar");
}

TEST(get_invalid_keys_must_function_properly, two_keys_with_double_dash_one_valid_key_matching_first_key_and_two_nonmatching_valid_keys)
{
    const int argc = 3; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "--bar";
    char third_arg[] = "--baz";
    const char* argv[] = { first_arg, second_arg, third_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_TRUE(command_line_master.get_are_arguments_valid());

    std::vector<std::string> valid_keys { "bar", "qux", "quux" };
    std::vector<std::string> invalid_keys = command_line_master.get_invalid_keys(valid_keys);
    ASSERT_FALSE(invalid_keys.empty());

    ASSERT_EQ(invalid_keys.size(), 1);
    ASSERT_EQ(invalid_keys[0], "baz");
}

TEST(get_invalid_keys_must_function_properly, two_keys_with_double_dash_one_valid_key_matching_second_key_and_two_nonmatching_valid_keys)
{
    const int argc = 3; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "--bar";
    char third_arg[] = "--baz";
    const char* argv[] = { first_arg, second_arg, third_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_TRUE(command_line_master.get_are_arguments_valid());

    std::vector<std::string> valid_keys { "baz", "qux", "quux" };
    std::vector<std::string> invalid_keys = command_line_master.get_invalid_keys(valid_keys);
    ASSERT_FALSE(invalid_keys.empty());

    ASSERT_EQ(invalid_keys.size(), 1);
    ASSERT_EQ(invalid_keys[0], "bar");
}

TEST(get_invalid_keys_must_function_properly, two_keys_with_double_dash_two_valid_keys_matching_first_key)
{
    const int argc = 3; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "--bar";
    char third_arg[] = "--baz";
    const char* argv[] = { first_arg, second_arg, third_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_TRUE(command_line_master.get_are_arguments_valid());

    std::vector<std::string> valid_keys { "bar", "bar" };
    std::vector<std::string> invalid_keys = command_line_master.get_invalid_keys(valid_keys);
    ASSERT_FALSE(invalid_keys.empty());

    ASSERT_EQ(invalid_keys.size(), 1);
    ASSERT_EQ(invalid_keys[0], "baz");
}

TEST(get_invalid_keys_must_function_properly, two_keys_with_double_dash_two_valid_keys_matching_second_key)
{
    const int argc = 3; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "--bar";
    char third_arg[] = "--baz";
    const char* argv[] = { first_arg, second_arg, third_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_TRUE(command_line_master.get_are_arguments_valid());

    std::vector<std::string> valid_keys { "baz", "baz" };
    std::vector<std::string> invalid_keys = command_line_master.get_invalid_keys(valid_keys);
    ASSERT_FALSE(invalid_keys.empty());

    ASSERT_EQ(invalid_keys.size(), 1);
    ASSERT_EQ(invalid_keys[0], "bar");
}

TEST(get_invalid_keys_must_function_properly, two_keys_with_double_dash_two_valid_keys_matching_first_and_second_key)
{
    const int argc = 3; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "--bar";
    char third_arg[] = "--baz";
    const char* argv[] = { first_arg, second_arg, third_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_TRUE(command_line_master.get_are_arguments_valid());

    std::vector<std::string> valid_keys { "bar", "baz" };
    std::vector<std::string> invalid_keys = command_line_master.get_invalid_keys(valid_keys);
    ASSERT_TRUE(invalid_keys.empty());
}

TEST(check_keys_must_function_properly, no_keys_no_valid_keys)
{
    const int argc = 1; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    const char* argv[] = { first_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_TRUE(command_line_master.get_are_arguments_valid());

    std::vector<std::string> valid_keys;
    ASSERT_TRUE(command_line_master.check_keys(valid_keys));
}

TEST(check_keys_must_function_properly, no_keys_one_valid_key)
{
    const int argc = 1; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    const char* argv[] = { first_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_TRUE(command_line_master.get_are_arguments_valid());

    std::vector<std::string> valid_keys { "foo" };
    ASSERT_TRUE(command_line_master.check_keys(valid_keys));
}

TEST(check_keys_must_function_properly, no_keys_two_valid_keys)
{
    const int argc = 1; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    const char* argv[] = { first_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_TRUE(command_line_master.get_are_arguments_valid());

    std::vector<std::string> valid_keys { "foo", "bar" };
    ASSERT_TRUE(command_line_master.check_keys(valid_keys));
}

TEST(check_keys_must_function_properly, one_key_with_double_dash_no_valid_keys)
{
    const int argc = 2; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "--bar";
    const char* argv[] = { first_arg, second_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
    ASSERT_TRUE(command_line_master.get_are_arguments_valid());

    std::vector<std::string> valid_keys;
    ASSERT_FALSE(command_line_master.check_keys(valid_keys));
}
