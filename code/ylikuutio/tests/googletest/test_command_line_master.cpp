#include "gtest/gtest.h"
#include "code/ylikuutio/command_line/command_line_master.hpp"

TEST(is_key_must_function_properly, no_keys)
{
    const int argc = 1; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    const char* argv[] = { first_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
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
    ASSERT_FALSE(command_line_master.is_key("foo_executable"));
    ASSERT_FALSE(command_line_master.is_key("foo"));
    ASSERT_TRUE(command_line_master.is_key("bar"));
    ASSERT_FALSE(command_line_master.is_key("baz"));
}

TEST(is_key_must_function_properly, one_key_with_value)
{
    const int argc = 2; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "bar=baz";
    const char* argv[] = { first_arg, second_arg };
    yli::command_line::CommandLineMaster command_line_master(argc, argv);
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

TEST(get_value_must_function_properly, one_key_with_value)
{
    const int argc = 2; // the executable itself is also in `argv`.
    char first_arg[] = "foo_executable";
    char second_arg[] = "bar=baz";
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
    ASSERT_EQ(command_line_master.get_value("bar"), "baz");
    ASSERT_EQ(command_line_master.get_value("baz"), "");
    ASSERT_EQ(command_line_master.get_value("qux"), "quux");
    ASSERT_EQ(command_line_master.get_value("quux"), "");
}
