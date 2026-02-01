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
#include "planetary_simulation.h"

#include <string_view> // std::string_view

extern "C"
{
    int FortranCInterface_MODULE_(string_mod, get_line_i_with_n_token_statement, string_mod, get_line_i_with_n_token_statement)(
            const char* string, int string_sz, const char* tokens, int tokens_sz);
}

TEST(get_line_i_with_n_token_statement_must_work_properly, empty_string_empty_tokens)
{
    std::string_view string { "" };
    std::string_view tokens { "" };
    int line_i = FortranCInterface_MODULE_(string_mod, get_line_i_with_n_token_statement, string_mod, get_line_i_with_n_token_statement)(
            string.data(), string.size(), tokens.data(), tokens.size());
    ASSERT_EQ(line_i, -1);
}

TEST(get_line_i_with_n_token_statement_must_work_properly, empty_string_a_tokens)
{
    std::string_view string { "" };
    std::string_view tokens { "a" };
    int line_i = FortranCInterface_MODULE_(string_mod, get_line_i_with_n_token_statement, string_mod, get_line_i_with_n_token_statement)(
            string.data(), string.size(), tokens.data(), tokens.size());
    ASSERT_EQ(line_i, -1);
}

TEST(get_line_i_with_n_token_statement_must_work_properly, empty_string_a_a_tokens)
{
    std::string_view string { "" };
    std::string_view tokens { "a a" };
    int line_i = FortranCInterface_MODULE_(string_mod, get_line_i_with_n_token_statement, string_mod, get_line_i_with_n_token_statement)(
            string.data(), string.size(), tokens.data(), tokens.size());
    ASSERT_EQ(line_i, -1);
}

TEST(get_line_i_with_n_token_statement_must_work_properly, a_a_string_a_a_tokens)
{
    std::string_view string { "a a" };
    std::string_view tokens { "a a" };
    int line_i = FortranCInterface_MODULE_(string_mod, get_line_i_with_n_token_statement, string_mod, get_line_i_with_n_token_statement)(
            string.data(), string.size(), tokens.data(), tokens.size());
    ASSERT_EQ(line_i, 1);
}

TEST(get_line_i_with_n_token_statement_must_work_properly, a_a_string_a_b_tokens)
{
    std::string_view string { "a a" };
    std::string_view tokens { "a b" };
    int line_i = FortranCInterface_MODULE_(string_mod, get_line_i_with_n_token_statement, string_mod, get_line_i_with_n_token_statement)(
            string.data(), string.size(), tokens.data(), tokens.size());
    ASSERT_EQ(line_i, -1);
}

TEST(get_line_i_with_n_token_statement_must_work_properly, a_a_string_b_a_tokens)
{
    std::string_view string { "a a" };
    std::string_view tokens { "b a" };
    int line_i = FortranCInterface_MODULE_(string_mod, get_line_i_with_n_token_statement, string_mod, get_line_i_with_n_token_statement)(
            string.data(), string.size(), tokens.data(), tokens.size());
    ASSERT_EQ(line_i, -1);
}

TEST(get_line_i_with_n_token_statement_must_work_properly, a_b_string_a_b_tokens)
{
    std::string_view string { "a b" };
    std::string_view tokens { "a b" };
    int line_i = FortranCInterface_MODULE_(string_mod, get_line_i_with_n_token_statement, string_mod, get_line_i_with_n_token_statement)(
            string.data(), string.size(), tokens.data(), tokens.size());
    ASSERT_EQ(line_i, 1);
}

TEST(get_line_i_with_n_token_statement_must_work_properly, foo_bar_newline_baz_qux_newline_quux_string_foo_bar_tokens)
{
    std::string_view string { "foo bar\nbaz qux\nquux" };
    std::string_view tokens { "foo bar" };
    int line_i = FortranCInterface_MODULE_(string_mod, get_line_i_with_n_token_statement, string_mod, get_line_i_with_n_token_statement)(
            string.data(), string.size(), tokens.data(), tokens.size());
    ASSERT_EQ(line_i, 1);
}

TEST(get_line_i_with_n_token_statement_must_work_properly, foo_bar_newline_baz_qux_newline_quux_string_bar_bar_tokens)
{
    std::string_view string { "foo bar\nbaz qux\nquux" };
    std::string_view tokens { "bar bar" };
    int line_i = FortranCInterface_MODULE_(string_mod, get_line_i_with_n_token_statement, string_mod, get_line_i_with_n_token_statement)(
            string.data(), string.size(), tokens.data(), tokens.size());
    ASSERT_EQ(line_i, -1);
}

TEST(get_line_i_with_n_token_statement_must_work_properly, foo_bar_newline_baz_qux_newline_quux_string_bar_baz_tokens)
{
    std::string_view string { "foo bar\nbaz qux\nquux" };
    std::string_view tokens { "bar baz" };
    int line_i = FortranCInterface_MODULE_(string_mod, get_line_i_with_n_token_statement, string_mod, get_line_i_with_n_token_statement)(
            string.data(), string.size(), tokens.data(), tokens.size());
    ASSERT_EQ(line_i, -1);
}

TEST(get_line_i_with_n_token_statement_must_work_properly, foo_bar_newline_baz_qux_newline_quux_string_baz_qux_tokens)
{
    std::string_view string { "foo bar\nbaz qux\nquux" };
    std::string_view tokens { "baz qux" };
    int line_i = FortranCInterface_MODULE_(string_mod, get_line_i_with_n_token_statement, string_mod, get_line_i_with_n_token_statement)(
            string.data(), string.size(), tokens.data(), tokens.size());
    ASSERT_EQ(line_i, 2);
}

TEST(get_line_i_with_n_token_statement_must_work_properly, newline_foo_bar_newline_baz_qux_newline_quux_string_baz_qux_tokens)
{
    std::string_view string { "\nfoo bar\nbaz qux\nquux" };
    std::string_view tokens { "baz qux" };
    int line_i = FortranCInterface_MODULE_(string_mod, get_line_i_with_n_token_statement, string_mod, get_line_i_with_n_token_statement)(
            string.data(), string.size(), tokens.data(), tokens.size());
    ASSERT_EQ(line_i, 3);
}
