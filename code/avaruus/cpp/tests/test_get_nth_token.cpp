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
#include "planetary_simulation.h"

#include <string_view> // std::string_view

extern "C"
{
    char* FortranCInterface_MODULE_(string_mod, get_nth_token, string_mod, get_nth_token)(const char* string, int sz, int token_i, int* next_i, int* token_sz);
}

TEST(get_nth_token_must_function_properly, empty_string_token_i_0_must_not_be_found)
{
    std::string_view string { "" };
    int token_i = 0;
    int next_i = 0;
    int token_sz = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_nth_token, string_mod, get_nth_token)(string.data(), string.size(), token_i, &next_i, &token_sz);
    std::string_view expected_token { "" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, -1); // No token found!
    ASSERT_EQ(token_sz, 0); // No token found!
}

TEST(get_nth_token_must_function_properly, empty_string_token_i_1_must_not_be_found)
{
    std::string_view string { "" };
    int token_i = 1;
    int next_i = 0;
    int token_sz = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_nth_token, string_mod, get_nth_token)(string.data(), string.size(), token_i, &next_i, &token_sz);
    std::string_view expected_token { "" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, -1); // No token found!
    ASSERT_EQ(token_sz, 0); // No token found!
}

TEST(get_nth_token_must_function_properly, a_string_token_i_1_must_be_found)
{
    std::string_view string { "a" };
    int token_i = 1;
    int next_i = 0;
    int token_sz = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_nth_token, string_mod, get_nth_token)(string.data(), string.size(), token_i, &next_i, &token_sz);
    std::string_view expected_token { "a" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, 2); // Searching for next token can begin from Fortran index 2.
    ASSERT_EQ(token_sz, 1); // Token size is 1.
}

TEST(get_nth_token_must_function_properly, foo_string_token_i_1_must_be_found)
{
    std::string_view string { "foo" };
    int token_i = 1;
    int next_i = 0;
    int token_sz = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_nth_token, string_mod, get_nth_token)(string.data(), string.size(), token_i, &next_i, &token_sz);
    std::string_view expected_token { "foo" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, 4); // Searching for next token can begin from Fortran index 4.
    ASSERT_EQ(token_sz, 3); // Token size is 3.
}

TEST(get_nth_token_must_function_properly, foo_string_token_i_2_must_not_be_found)
{
    std::string_view string { "foo" };
    int token_i = 2;
    int next_i = 0;
    int token_sz = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_nth_token, string_mod, get_nth_token)(string.data(), string.size(), token_i, &next_i, &token_sz);
    std::string_view expected_token { "" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, -1); // No token found!
    ASSERT_EQ(token_sz, 0); // No token found!
}

TEST(get_nth_token_must_function_properly, foo_bar_string_token_i_1_must_be_found)
{
    std::string_view string { "foo bar" };
    int token_i = 1;
    int next_i = 0;
    int token_sz = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_nth_token, string_mod, get_nth_token)(string.data(), string.size(), token_i, &next_i, &token_sz);
    std::string_view expected_token { "foo" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, 4); // Searching for next token can begin from Fortran index 4.
    ASSERT_EQ(token_sz, 3); // Token size is 3.
}

TEST(get_nth_token_must_function_properly, foo_bar_string_token_i_2_must_be_found)
{
    std::string_view string { "foo bar" };
    int token_i = 2;
    int next_i = 0;
    int token_sz = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_nth_token, string_mod, get_nth_token)(string.data(), string.size(), token_i, &next_i, &token_sz);
    std::string_view expected_token { "bar" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, 8); // Searching for next token can begin from Fortran index 8.
    ASSERT_EQ(token_sz, 3); // Token size is 3.
}

TEST(get_nth_token_must_function_properly, foo_bar_string_token_i_3_must_not_be_found)
{
    std::string_view string { "foo bar" };
    int token_i = 3;
    int next_i = 0;
    int token_sz = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_nth_token, string_mod, get_nth_token)(string.data(), string.size(), token_i, &next_i, &token_sz);
    std::string_view expected_token { "" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, -1); // No token found!
    ASSERT_EQ(token_sz, 0); // No token found!
}

TEST(get_nth_token_must_function_properly, newline_string_token_i_0_must_not_be_found)
{
    std::string_view string { "\n" };
    int token_i = 0;
    int next_i = 0;
    int token_sz = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_nth_token, string_mod, get_nth_token)(string.data(), string.size(), token_i, &next_i, &token_sz);
    std::string_view expected_token { "" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, -1); // No token found!
    ASSERT_EQ(token_sz, 0); // No token found!
}

TEST(get_nth_token_must_function_properly, newline_string_token_i_1_must_not_be_found)
{
    std::string_view string { "\n" };
    int token_i = 1;
    int next_i = 0;
    int token_sz = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_nth_token, string_mod, get_nth_token)(string.data(), string.size(), token_i, &next_i, &token_sz);
    std::string_view expected_token { "" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, -1); // No token found!
    ASSERT_EQ(token_sz, 0); // No token found!
}

TEST(get_nth_token_must_function_properly, newline_a_string_token_i_0_must_not_be_found)
{
    std::string_view string { "\na" };
    int token_i = 0;
    int next_i = 0;
    int token_sz = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_nth_token, string_mod, get_nth_token)(string.data(), string.size(), token_i, &next_i, &token_sz);
    std::string_view expected_token { "" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, -1); // No token found!
    ASSERT_EQ(token_sz, 0); // No token found!
}

TEST(get_nth_token_must_function_properly, newline_a_string_token_i_1_must_not_be_found)
{
    std::string_view string { "\na" };
    int token_i = 1;
    int next_i = 0;
    int token_sz = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_nth_token, string_mod, get_nth_token)(string.data(), string.size(), token_i, &next_i, &token_sz);
    std::string_view expected_token { "" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, -1); // No token found!
    ASSERT_EQ(token_sz, 0); // No token found!
}
