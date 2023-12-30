#include "gtest/gtest.h"
#include "planetary_simulation.h"

#include <string_view> // std::string_view

extern "C"
{
    int FortranCInterface_MODULE_(string_mod, get_line_i_with_2_token_statement, string_mod, get_line_i_with_2_token_statement)(
            const char* string, int string_sz, const char* token1, int token1_sz, const char* token2, int token2_sz);
}

TEST(get_line_i_with_2_token_statement_must_work_properly, empty_string_empty_token1_empty_token2)
{
    std::string_view string { "" };
    std::string_view token1 { "" };
    std::string_view token2 { "" };
    int line_i = FortranCInterface_MODULE_(string_mod, get_line_i_with_2_token_statement, string_mod, get_line_i_with_2_token_statement)(
            string.data(), string.size(), token1.data(), token1.size(), token2.data(), token2.size());
    ASSERT_EQ(line_i, -1);
}

TEST(get_line_i_with_2_token_statement_must_work_properly, empty_string_a_token1_empty_token2)
{
    std::string_view string { "" };
    std::string_view token1 { "a" };
    std::string_view token2 { "" };
    int line_i = FortranCInterface_MODULE_(string_mod, get_line_i_with_2_token_statement, string_mod, get_line_i_with_2_token_statement)(
            string.data(), string.size(), token1.data(), token1.size(), token2.data(), token2.size());
    ASSERT_EQ(line_i, -1);
}

TEST(get_line_i_with_2_token_statement_must_work_properly, empty_string_empty_token1_a_token2)
{
    std::string_view string { "" };
    std::string_view token1 { "" };
    std::string_view token2 { "a" };
    int line_i = FortranCInterface_MODULE_(string_mod, get_line_i_with_2_token_statement, string_mod, get_line_i_with_2_token_statement)(
            string.data(), string.size(), token1.data(), token1.size(), token2.data(), token2.size());
    ASSERT_EQ(line_i, -1);
}

TEST(get_line_i_with_2_token_statement_must_work_properly, empty_string_a_token1_a_token2)
{
    std::string_view string { "" };
    std::string_view token1 { "a" };
    std::string_view token2 { "a" };
    int line_i = FortranCInterface_MODULE_(string_mod, get_line_i_with_2_token_statement, string_mod, get_line_i_with_2_token_statement)(
            string.data(), string.size(), token1.data(), token1.size(), token2.data(), token2.size());
    ASSERT_EQ(line_i, -1);
}

TEST(get_line_i_with_2_token_statement_must_work_properly, empty_string_a_token1_b_token2)
{
    std::string_view string { "" };
    std::string_view token1 { "a" };
    std::string_view token2 { "a" };
    int line_i = FortranCInterface_MODULE_(string_mod, get_line_i_with_2_token_statement, string_mod, get_line_i_with_2_token_statement)(
            string.data(), string.size(), token1.data(), token1.size(), token2.data(), token2.size());
    ASSERT_EQ(line_i, -1);
}

TEST(get_line_i_with_2_token_statement_must_work_properly, a_a_string_a_token1_a_token2)
{
    std::string_view string { "a a" };
    std::string_view token1 { "a" };
    std::string_view token2 { "a" };
    int line_i = FortranCInterface_MODULE_(string_mod, get_line_i_with_2_token_statement, string_mod, get_line_i_with_2_token_statement)(
            string.data(), string.size(), token1.data(), token1.size(), token2.data(), token2.size());
    ASSERT_EQ(line_i, 1);
}

TEST(get_line_i_with_2_token_statement_must_work_properly, a_a_string_a_token1_b_token2)
{
    std::string_view string { "a a" };
    std::string_view token1 { "a" };
    std::string_view token2 { "b" };
    int line_i = FortranCInterface_MODULE_(string_mod, get_line_i_with_2_token_statement, string_mod, get_line_i_with_2_token_statement)(
            string.data(), string.size(), token1.data(), token1.size(), token2.data(), token2.size());
    ASSERT_EQ(line_i, -1);
}

TEST(get_line_i_with_2_token_statement_must_work_properly, a_a_string_b_token1_a_token2)
{
    std::string_view string { "a a" };
    std::string_view token1 { "b" };
    std::string_view token2 { "a" };
    int line_i = FortranCInterface_MODULE_(string_mod, get_line_i_with_2_token_statement, string_mod, get_line_i_with_2_token_statement)(
            string.data(), string.size(), token1.data(), token1.size(), token2.data(), token2.size());
    ASSERT_EQ(line_i, -1);
}

TEST(get_line_i_with_2_token_statement_must_work_properly, a_b_string_a_token1_a_token2)
{
    std::string_view string { "a b" };
    std::string_view token1 { "a" };
    std::string_view token2 { "a" };
    int line_i = FortranCInterface_MODULE_(string_mod, get_line_i_with_2_token_statement, string_mod, get_line_i_with_2_token_statement)(
            string.data(), string.size(), token1.data(), token1.size(), token2.data(), token2.size());
    ASSERT_EQ(line_i, -1);
}

TEST(get_line_i_with_2_token_statement_must_work_properly, a_b_string_a_token1_b_token2)
{
    std::string_view string { "a b" };
    std::string_view token1 { "a" };
    std::string_view token2 { "b" };
    int line_i = FortranCInterface_MODULE_(string_mod, get_line_i_with_2_token_statement, string_mod, get_line_i_with_2_token_statement)(
            string.data(), string.size(), token1.data(), token1.size(), token2.data(), token2.size());
    ASSERT_EQ(line_i, 1);
}

TEST(get_line_i_with_2_token_statement_must_work_properly, a_b_string_b_token1_a_token2)
{
    std::string_view string { "a b" };
    std::string_view token1 { "b" };
    std::string_view token2 { "a" };
    int line_i = FortranCInterface_MODULE_(string_mod, get_line_i_with_2_token_statement, string_mod, get_line_i_with_2_token_statement)(
            string.data(), string.size(), token1.data(), token1.size(), token2.data(), token2.size());
    ASSERT_EQ(line_i, -1);
}

TEST(get_line_i_with_2_token_statement_must_work_properly, foo_bar_newline_baz_qux_newline_quux_string_foo_token1_bar_token2)
{
    std::string_view string { "foo bar\nbaz qux\nquux" };
    std::string_view token1 { "foo" };
    std::string_view token2 { "bar" };
    int line_i = FortranCInterface_MODULE_(string_mod, get_line_i_with_2_token_statement, string_mod, get_line_i_with_2_token_statement)(
            string.data(), string.size(), token1.data(), token1.size(), token2.data(), token2.size());
    ASSERT_EQ(line_i, 1);
}

TEST(get_line_i_with_2_token_statement_must_work_properly, foo_bar_newline_baz_qux_newline_quux_string_bar_token1_bar_token2)
{
    std::string_view string { "foo bar\nbaz qux\nquux" };
    std::string_view token1 { "bar" };
    std::string_view token2 { "bar" };
    int line_i = FortranCInterface_MODULE_(string_mod, get_line_i_with_2_token_statement, string_mod, get_line_i_with_2_token_statement)(
            string.data(), string.size(), token1.data(), token1.size(), token2.data(), token2.size());
    ASSERT_EQ(line_i, -1);
}

TEST(get_line_i_with_2_token_statement_must_work_properly, foo_bar_newline_baz_qux_newline_quux_string_bar_token1_baz_token2)
{
    std::string_view string { "foo bar\nbaz qux\nquux" };
    std::string_view token1 { "bar" };
    std::string_view token2 { "baz" };
    int line_i = FortranCInterface_MODULE_(string_mod, get_line_i_with_2_token_statement, string_mod, get_line_i_with_2_token_statement)(
            string.data(), string.size(), token1.data(), token1.size(), token2.data(), token2.size());
    ASSERT_EQ(line_i, -1);
}

TEST(get_line_i_with_2_token_statement_must_work_properly, foo_bar_newline_baz_qux_newline_quux_string_baz_token1_qux_token2)
{
    std::string_view string { "foo bar\nbaz qux\nquux" };
    std::string_view token1 { "baz" };
    std::string_view token2 { "qux" };
    int line_i = FortranCInterface_MODULE_(string_mod, get_line_i_with_2_token_statement, string_mod, get_line_i_with_2_token_statement)(
            string.data(), string.size(), token1.data(), token1.size(), token2.data(), token2.size());
    ASSERT_EQ(line_i, 2);
}

TEST(get_line_i_with_2_token_statement_must_work_properly, newline_foo_bar_newline_baz_qux_newline_quux_string_baz_token1_qux_token2)
{
    std::string_view string { "\nfoo bar\nbaz qux\nquux" };
    std::string_view token1 { "baz" };
    std::string_view token2 { "qux" };
    int line_i = FortranCInterface_MODULE_(string_mod, get_line_i_with_2_token_statement, string_mod, get_line_i_with_2_token_statement)(
            string.data(), string.size(), token1.data(), token1.size(), token2.data(), token2.size());
    ASSERT_EQ(line_i, 3);
}
