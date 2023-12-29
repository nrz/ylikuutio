#include "gtest/gtest.h"
#include "planetary_simulation.h"

extern "C"
{
    char* FortranCInterface_MODULE_(string_mod, get_first_token, string_mod, get_first_token)(const char* string, int sz);
}

#include <string_view> // std::string_view

TEST(get_first_token_must_work_properly, empty)
{
    std::string_view empty { "" };
    char* token = FortranCInterface_MODULE_(string_mod, get_first_token, string_mod, get_first_token)(empty.data(), empty.size());
    std::string expected_token { "" };
    ASSERT_TRUE(expected_token.compare(token));
    free(token);
}

TEST(get_first_token_must_work_properly, space)
{
    std::string_view space { " " };
    char* token = FortranCInterface_MODULE_(string_mod, get_first_token, string_mod, get_first_token)(space.data(), space.size());
    std::string expected_token { "" };
    ASSERT_TRUE(expected_token.compare(token));
    free(token);
}

TEST(get_first_token_must_work_properly, a)
{
    std::string_view a { "a" };
    char* token = FortranCInterface_MODULE_(string_mod, get_first_token, string_mod, get_first_token)(a.data(), a.size());
    std::string expected_token { "a" };
    ASSERT_TRUE(expected_token.compare(token));
    free(token);
}

TEST(get_first_token_must_work_properly, hash)
{
    std::string_view hash { "#" };
    char* token = FortranCInterface_MODULE_(string_mod, get_first_token, string_mod, get_first_token)(hash.data(), hash.size());
    std::string expected_token { "" };
    ASSERT_TRUE(expected_token.compare(token));
    free(token);
}

TEST(get_first_token_must_work_properly, newline)
{
    std::string_view newline { "\n" };
    char* token = FortranCInterface_MODULE_(string_mod, get_first_token, string_mod, get_first_token)(newline.data(), newline.size());
    std::string expected_token { "" };
    ASSERT_TRUE(expected_token.compare(token));
    free(token);
}

TEST(get_first_token_must_work_properly, space_a)
{
    std::string_view space_a { " a" };
    char* token = FortranCInterface_MODULE_(string_mod, get_first_token, string_mod, get_first_token)(space_a.data(), space_a.size());
    std::string expected_token { "a" };
    ASSERT_TRUE(expected_token.compare(token));
    free(token);
}

TEST(get_first_token_must_work_properly, space_hash)
{
    std::string_view space_hash { " #" };
    char* token = FortranCInterface_MODULE_(string_mod, get_first_token, string_mod, get_first_token)(space_hash.data(), space_hash.size());
    std::string expected_token { "a" };
    ASSERT_TRUE(expected_token.compare(token));
    free(token);
}

TEST(get_first_token_must_work_properly, a_space)
{
    std::string_view a_space { "a " };
    char* token = FortranCInterface_MODULE_(string_mod, get_first_token, string_mod, get_first_token)(a_space.data(), a_space.size());
    std::string expected_token { "a" };
    ASSERT_TRUE(expected_token.compare(token));
    free(token);
}

TEST(get_first_token_must_work_properly, a_hash)
{
    std::string_view a_hash { "a#" };
    char* token = FortranCInterface_MODULE_(string_mod, get_first_token, string_mod, get_first_token)(a_hash.data(), a_hash.size());
    std::string expected_token { "a" };
    ASSERT_TRUE(expected_token.compare(token));
    free(token);
}

TEST(get_first_token_must_work_properly, newline_a)
{
    std::string_view newline_a { "\na" };
    char* token = FortranCInterface_MODULE_(string_mod, get_first_token, string_mod, get_first_token)(newline_a.data(), newline_a.size());
    std::string expected_token { "" };
    ASSERT_TRUE(expected_token.compare(token));
    free(token);
}

TEST(get_first_token_must_work_properly, space_a_space)
{
    std::string_view space_a_space { " a " };
    char* token = FortranCInterface_MODULE_(string_mod, get_first_token, string_mod, get_first_token)(space_a_space.data(), space_a_space.size());
    std::string expected_token { "a" };
    ASSERT_TRUE(expected_token.compare(token));
    free(token);
}

TEST(get_first_token_must_work_properly, space_a_hash)
{
    std::string_view space_a_hash { " a#" };
    char* token = FortranCInterface_MODULE_(string_mod, get_first_token, string_mod, get_first_token)(space_a_hash.data(), space_a_hash.size());
    std::string expected_token { "a" };
    ASSERT_TRUE(expected_token.compare(token));
    free(token);
}

TEST(get_first_token_must_work_properly, a_space_a)
{
    std::string_view a_space_a { "a a" };
    char* token = FortranCInterface_MODULE_(string_mod, get_first_token, string_mod, get_first_token)(a_space_a.data(), a_space_a.size());
    std::string expected_token { "a" };
    ASSERT_TRUE(expected_token.compare(token));
    free(token);
}

TEST(get_first_token_must_work_properly, a_space_hash)
{
    std::string_view a_space_hash { "a #" };
    char* token = FortranCInterface_MODULE_(string_mod, get_first_token, string_mod, get_first_token)(a_space_hash.data(), a_space_hash.size());
    std::string expected_token { "a" };
    ASSERT_TRUE(expected_token.compare(token));
    free(token);
}

TEST(get_first_token_must_work_properly, abc)
{
    std::string_view abc { "abc" };
    char* token = FortranCInterface_MODULE_(string_mod, get_first_token, string_mod, get_first_token)(abc.data(), abc.size());
    std::string expected_token { "abc" };
    ASSERT_TRUE(expected_token.compare(token));
    free(token);
}

TEST(get_first_token_must_work_properly, abc_hash)
{
    std::string_view abc_hash { "abc#" };
    char* token = FortranCInterface_MODULE_(string_mod, get_first_token, string_mod, get_first_token)(abc_hash.data(), abc_hash.size());
    std::string expected_token { "abc" };
    ASSERT_TRUE(expected_token.compare(token));
    free(token);
}

TEST(get_first_token_must_work_properly, abc_newline)
{
    std::string_view abc_newline { "abc\n" };
    char* token = FortranCInterface_MODULE_(string_mod, get_first_token, string_mod, get_first_token)(abc_newline.data(), abc_newline.size());
    std::string expected_token { "abc" };
    ASSERT_TRUE(expected_token.compare(token));
    free(token);
}
