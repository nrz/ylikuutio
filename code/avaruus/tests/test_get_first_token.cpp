// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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
    char* FortranCInterface_MODULE_(string_mod, get_first_token, string_mod, get_first_token)(const char* string, int sz, int* next_i, int* token_sz);
}

TEST(get_first_token_must_work_properly, empty)
{
    std::string_view empty { "" };
    int next_i = 0;
    int token_sz = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_first_token, string_mod, get_first_token)(empty.data(), empty.size(), &next_i, &token_sz);
    std::string_view expected_token { "" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, -1); // No token found!
    ASSERT_EQ(token_sz, 0); // No token found!
    free(token);
}

TEST(get_first_token_must_work_properly, space)
{
    std::string_view space { " " };
    int next_i = 0;
    int token_sz = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_first_token, string_mod, get_first_token)(space.data(), space.size(), &next_i, &token_sz);
    std::string_view expected_token { "" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, -1); // No token found!
    ASSERT_EQ(token_sz, 0); // No token found!
    free(token);
}

TEST(get_first_token_must_work_properly, a)
{
    std::string_view a { "a" };
    int next_i = 0;
    int token_sz = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_first_token, string_mod, get_first_token)(a.data(), a.size(), &next_i, &token_sz);
    std::string_view expected_token { "a" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, 2); // Searching for next token can begin from Fortran index 2.
    ASSERT_EQ(token_sz, 1); // Token size is 1.
    free(token);
}

TEST(get_first_token_must_work_properly, hash)
{
    std::string_view hash { "#" };
    int next_i = 0;
    int token_sz = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_first_token, string_mod, get_first_token)(hash.data(), hash.size(), &next_i, &token_sz);
    std::string_view expected_token { "" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, -1); // No token found!
    ASSERT_EQ(token_sz, 0); // No token found!
    free(token);
}

TEST(get_first_token_must_work_properly, newline)
{
    std::string_view newline { "\n" };
    int next_i = 0;
    int token_sz = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_first_token, string_mod, get_first_token)(newline.data(), newline.size(), &next_i, &token_sz);
    std::string_view expected_token { "" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, -1); // No token found!
    ASSERT_EQ(token_sz, 0); // No token found!
    free(token);
}

TEST(get_first_token_must_work_properly, space_a)
{
    std::string_view space_a { " a" };
    int next_i = 0;
    int token_sz = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_first_token, string_mod, get_first_token)(space_a.data(), space_a.size(), &next_i, &token_sz);
    std::string_view expected_token { "a" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, 3); // Searching for next token can begin from Fortran index 3.
    ASSERT_EQ(token_sz, 1); // Token size is 1.
    free(token);
}

TEST(get_first_token_must_work_properly, space_hash)
{
    std::string_view space_hash { " #" };
    int next_i = 0;
    int token_sz = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_first_token, string_mod, get_first_token)(space_hash.data(), space_hash.size(), &next_i, &token_sz);
    std::string_view expected_token { "" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, -1); // No token found!
    ASSERT_EQ(token_sz, 0); // No token found!
    free(token);
}

TEST(get_first_token_must_work_properly, a_space)
{
    std::string_view a_space { "a " };
    int next_i = 0;
    int token_sz = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_first_token, string_mod, get_first_token)(a_space.data(), a_space.size(), &next_i, &token_sz);
    std::string_view expected_token { "a" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, 2); // Searching for next token can begin from Fortran index 2.
    ASSERT_EQ(token_sz, 1); // Token size is 1.
    free(token);
}

TEST(get_first_token_must_work_properly, a_hash)
{
    std::string_view a_hash { "a#" };
    int next_i = 0;
    int token_sz = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_first_token, string_mod, get_first_token)(a_hash.data(), a_hash.size(), &next_i, &token_sz);
    std::string_view expected_token { "a" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, 2); // Searching for next token can begin from Fortran index 2.
    ASSERT_EQ(token_sz, 1); // Token size is 1.
    free(token);
}

TEST(get_first_token_must_work_properly, a_newline)
{
    std::string_view a_newline { "a\n" };
    int next_i = 0;
    int token_sz = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_first_token, string_mod, get_first_token)(a_newline.data(), a_newline.size(), &next_i, &token_sz);
    std::string_view expected_token { "a" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, 2); // Searching for next token can begin from Fortran index 2.
    ASSERT_EQ(token_sz, 1); // Token size is 1.
    free(token);
}

TEST(get_first_token_must_work_properly, newline_a)
{
    std::string_view newline_a { "\na" };
    int next_i = 0;
    int token_sz = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_first_token, string_mod, get_first_token)(newline_a.data(), newline_a.size(), &next_i, &token_sz);
    std::string_view expected_token { "" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, -1); // No token found!
    ASSERT_EQ(token_sz, 0); // No token found!
    free(token);
}

TEST(get_first_token_must_work_properly, space_a_space)
{
    std::string_view space_a_space { " a " };
    int next_i = 0;
    int token_sz = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_first_token, string_mod, get_first_token)(space_a_space.data(), space_a_space.size(), &next_i, &token_sz);
    std::string_view expected_token { "a" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, 3); // Searching for next token can begin from Fortran index 3.
    ASSERT_EQ(token_sz, 1); // Token size is 1.
    free(token);
}

TEST(get_first_token_must_work_properly, space_a_hash)
{
    std::string_view space_a_hash { " a#" };
    int next_i = 0;
    int token_sz = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_first_token, string_mod, get_first_token)(space_a_hash.data(), space_a_hash.size(), &next_i, &token_sz);
    std::string_view expected_token { "a" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, 3); // Searching for next token can begin from Fortran index 3.
    ASSERT_EQ(token_sz, 1); // Token size is 1.
    free(token);
}

TEST(get_first_token_must_work_properly, a_space_a)
{
    std::string_view a_space_a { "a a" };
    int next_i = 0;
    int token_sz = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_first_token, string_mod, get_first_token)(a_space_a.data(), a_space_a.size(), &next_i, &token_sz);
    std::string_view expected_token { "a" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, 2); // Searching for next token can begin from Fortran index 2.
    ASSERT_EQ(token_sz, 1); // Token size is 1.
    free(token);
}

TEST(get_first_token_must_work_properly, a_space_hash)
{
    std::string_view a_space_hash { "a #" };
    int next_i = 0;
    int token_sz = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_first_token, string_mod, get_first_token)(a_space_hash.data(), a_space_hash.size(), &next_i, &token_sz);
    std::string_view expected_token { "a" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, 2); // Searching for next token can begin from Fortran index 2.
    ASSERT_EQ(token_sz, 1); // Token size is 1.
    free(token);
}

TEST(get_first_token_must_work_properly, abc)
{
    std::string_view abc { "abc" };
    int next_i = 0;
    int token_sz = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_first_token, string_mod, get_first_token)(abc.data(), abc.size(), &next_i, &token_sz);
    std::string_view expected_token { "abc" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, 4); // Searching for next token can begin from Fortran index 4.
    ASSERT_EQ(token_sz, 3); // Token size is 3.
    free(token);
}

TEST(get_first_token_must_work_properly, abc_space)
{
    std::string_view abc_space { "abc " };
    int next_i = 0;
    int token_sz = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_first_token, string_mod, get_first_token)(abc_space.data(), abc_space.size(), &next_i, &token_sz);
    std::string_view expected_token { "abc" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, 4); // Searching for next token can begin from Fortran index 4.
    ASSERT_EQ(token_sz, 3); // Token size is 3.
    free(token);
}

TEST(get_first_token_must_work_properly, abc_hash)
{
    std::string_view abc_hash { "abc#" };
    int next_i = 0;
    int token_sz = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_first_token, string_mod, get_first_token)(abc_hash.data(), abc_hash.size(), &next_i, &token_sz);
    std::string_view expected_token { "abc" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, 4); // Searching for next token can begin from Fortran index 4.
    ASSERT_EQ(token_sz, 3); // Token size is 3.
    free(token);
}

TEST(get_first_token_must_work_properly, abc_newline)
{
    std::string_view abc_newline { "abc\n" };
    int next_i = 0;
    int token_sz = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_first_token, string_mod, get_first_token)(abc_newline.data(), abc_newline.size(), &next_i, &token_sz);
    std::string_view expected_token { "abc" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, 4); // Searching for next token can begin from Fortran index 4.
    ASSERT_EQ(token_sz, 3); // Token size is 3.
    free(token);
}
