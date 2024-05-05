#include "gtest/gtest.h"
#include "planetary_simulation.h"

#include <string_view> // std::string_view

extern "C"
{
    int FortranCInterface_MODULE_(string_mod, get_n_of_code_lines_between, string_mod, get_n_of_code_lines_between)(
            const char* string, int sz, int begin_line, int end_line);
}

TEST(get_n_of_code_lines_between_must_work_properly, empty_string_begin_line_1_end_line_2)
{
    std::string_view string { "" };
    int begin_line_i = 1;
    int end_line_i = 2;
    int n_of_code_lines = FortranCInterface_MODULE_(string_mod, get_n_of_code_lines_between, string_mod, get_n_of_code_lines_between)(
            string.data(), string.size(), begin_line_i, end_line_i);
    ASSERT_EQ(n_of_code_lines, -1);
}

TEST(get_line_i_with_n_token_statement_must_work_properly, foo_bar_newline_baz_qux_newline_quux_string_begin_line_0_end_line_2)
{
    std::string_view string { "foo bar\nbaz qux\nquux" };
    int begin_line_i = 0;
    int end_line_i = 2;
    int n_of_code_lines = FortranCInterface_MODULE_(string_mod, get_n_of_code_lines_between, string_mod, get_n_of_code_lines_between)(
            string.data(), string.size(), begin_line_i, end_line_i);
    ASSERT_EQ(n_of_code_lines, -1);
}

TEST(get_line_i_with_n_token_statement_must_work_properly, foo_bar_newline_baz_qux_newline_quux_string_begin_line_1_end_line_2)
{
    std::string_view string { "foo bar\nbaz qux\nquux" };
    int begin_line_i = 1;
    int end_line_i = 2;
    int n_of_code_lines = FortranCInterface_MODULE_(string_mod, get_n_of_code_lines_between, string_mod, get_n_of_code_lines_between)(
            string.data(), string.size(), begin_line_i, end_line_i);
    ASSERT_EQ(n_of_code_lines, 0);
}

TEST(get_line_i_with_n_token_statement_must_work_properly, foo_bar_newline_baz_qux_newline_quux_string_begin_line_1_end_line_3)
{
    std::string_view string { "foo bar\nbaz qux\nquux" };
    int begin_line_i = 1;
    int end_line_i = 3;
    int n_of_code_lines = FortranCInterface_MODULE_(string_mod, get_n_of_code_lines_between, string_mod, get_n_of_code_lines_between)(
            string.data(), string.size(), begin_line_i, end_line_i);
    ASSERT_EQ(n_of_code_lines, 1);
}
