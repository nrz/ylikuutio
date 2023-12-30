#include "gtest/gtest.h"
#include "planetary_simulation.h"

#include <string_view> // std::string_view

extern "C"
{
    char* FortranCInterface_MODULE_(string_mod, get_nth_token, string_mod, get_nth_token)(const char* string, int sz, int token_i, int* next_i);
}

TEST(get_nth_token_must_function_properly, empty_string_token_i_0_must_not_be_found)
{
    std::string_view string { "" };
    int token_i = 0;
    int next_i = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_nth_token, string_mod, get_nth_token)(string.data(), string.size(), token_i, &next_i);
    std::string_view expected_token { "" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, -1); // No token found!
    free(token);
}

TEST(get_nth_token_must_function_properly, empty_string_token_i_1_must_not_be_found)
{
    std::string_view string { "" };
    int token_i = 1;
    int next_i = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_nth_token, string_mod, get_nth_token)(string.data(), string.size(), token_i, &next_i);
    std::string_view expected_token { "" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, -1); // No token found!
    free(token);
}

TEST(get_nth_token_must_function_properly, a_string_token_i_1_must_be_found)
{
    std::string_view string { "a" };
    int token_i = 1;
    int next_i = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_nth_token, string_mod, get_nth_token)(string.data(), string.size(), token_i, &next_i);
    std::string_view expected_token { "a" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, 2); // Searching for next token can begin from Fortran index 2.
    free(token);
}

TEST(get_nth_token_must_function_properly, foo_string_token_i_1_must_be_found)
{
    std::string_view string { "foo" };
    int token_i = 1;
    int next_i = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_nth_token, string_mod, get_nth_token)(string.data(), string.size(), token_i, &next_i);
    std::string_view expected_token { "foo" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, 4); // Searching for next token can begin from Fortran index 4.
    free(token);
}

TEST(get_nth_token_must_function_properly, foo_string_token_i_2_must_not_be_found)
{
    std::string_view string { "foo" };
    int token_i = 2;
    int next_i = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_nth_token, string_mod, get_nth_token)(string.data(), string.size(), token_i, &next_i);
    std::string_view expected_token { "" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, -1); // No token found!
    free(token);
}

TEST(get_nth_token_must_function_properly, foo_bar_string_token_i_1_must_be_found)
{
    std::string_view string { "foo bar" };
    int token_i = 1;
    int next_i = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_nth_token, string_mod, get_nth_token)(string.data(), string.size(), token_i, &next_i);
    std::string_view expected_token { "foo" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, 4); // Searching for next token can begin from Fortran index 4.
    free(token);
}

TEST(get_nth_token_must_function_properly, foo_bar_string_token_i_2_must_be_found)
{
    std::string_view string { "foo bar" };
    int token_i = 2;
    int next_i = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_nth_token, string_mod, get_nth_token)(string.data(), string.size(), token_i, &next_i);
    std::string_view expected_token { "bar" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, 8); // Searching for next token can begin from Fortran index 8.
    free(token);
}

TEST(get_nth_token_must_function_properly, foo_bar_string_token_i_3_must_not_be_found)
{
    std::string_view string { "foo bar" };
    int token_i = 3;
    int next_i = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_nth_token, string_mod, get_nth_token)(string.data(), string.size(), token_i, &next_i);
    std::string_view expected_token { "" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, -1); // No token found!
    free(token);
}

TEST(get_nth_token_must_function_properly, newline_string_token_i_0_must_not_be_found)
{
    std::string_view string { "\n" };
    int token_i = 0;
    int next_i = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_nth_token, string_mod, get_nth_token)(string.data(), string.size(), token_i, &next_i);
    std::string_view expected_token { "" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, -1); // No token found!
    free(token);
}

TEST(get_nth_token_must_function_properly, newline_string_token_i_1_must_not_be_found)
{
    std::string_view string { "\n" };
    int token_i = 1;
    int next_i = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_nth_token, string_mod, get_nth_token)(string.data(), string.size(), token_i, &next_i);
    std::string_view expected_token { "" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, -1); // No token found!
    free(token);
}

TEST(get_nth_token_must_function_properly, newline_a_string_token_i_0_must_not_be_found)
{
    std::string_view string { "\na" };
    int token_i = 0;
    int next_i = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_nth_token, string_mod, get_nth_token)(string.data(), string.size(), token_i, &next_i);
    std::string_view expected_token { "" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, -1); // No token found!
    free(token);
}

TEST(get_nth_token_must_function_properly, newline_a_string_token_i_1_must_not_be_found)
{
    std::string_view string { "\na" };
    int token_i = 1;
    int next_i = 0;
    char* token = FortranCInterface_MODULE_(string_mod, get_nth_token, string_mod, get_nth_token)(string.data(), string.size(), token_i, &next_i);
    std::string_view expected_token { "" };
    ASSERT_EQ(expected_token.compare(token), 0);
    ASSERT_EQ(next_i, -1); // No token found!
    free(token);
}
