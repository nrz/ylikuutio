#include "gtest/gtest.h"
#include "planetary_simulation.h"

#include <string_view> // std::string_view

extern "C"
{
    int FortranCInterface_MODULE_(string_mod, get_has_line_code, string_mod, get_has_line_code)(const char* string, int sz);
}

TEST(get_has_line_code_must_work_properly, empty)
{
    std::string_view empty { "" };
    int has_line_code = FortranCInterface_MODULE_(string_mod, get_has_line_code, string_mod, get_has_line_code)(empty.data(), empty.size());
    ASSERT_FALSE(has_line_code);
}

TEST(get_has_line_code_must_work_properly, space)
{
    std::string_view space { " " };
    int has_line_code = FortranCInterface_MODULE_(string_mod, get_has_line_code, string_mod, get_has_line_code)(space.data(), space.size());
    ASSERT_FALSE(has_line_code);
}

TEST(get_has_line_code_must_work_properly, a)
{
    std::string_view a { "a" };
    int has_line_code = FortranCInterface_MODULE_(string_mod, get_has_line_code, string_mod, get_has_line_code)(a.data(), a.size());
    ASSERT_TRUE(has_line_code);
}

TEST(get_has_line_code_must_work_properly, hash)
{
    std::string_view hash { "#" };
    int has_line_code = FortranCInterface_MODULE_(string_mod, get_has_line_code, string_mod, get_has_line_code)(hash.data(), hash.size());
    ASSERT_FALSE(has_line_code);
}

TEST(get_has_line_code_must_work_properly, space_space)
{
    std::string_view space_space { "  " };
    int has_line_code = FortranCInterface_MODULE_(string_mod, get_has_line_code, string_mod, get_has_line_code)(space_space.data(), space_space.size());
    ASSERT_FALSE(has_line_code);
}

TEST(get_has_line_code_must_work_properly, space_a)
{
    std::string_view space_a { " a" };
    int has_line_code = FortranCInterface_MODULE_(string_mod, get_has_line_code, string_mod, get_has_line_code)(space_a.data(), space_a.size());
    ASSERT_TRUE(has_line_code);
}

TEST(get_has_line_code_must_work_properly, space_hash)
{
    std::string_view space_hash { " #" };
    int has_line_code = FortranCInterface_MODULE_(string_mod, get_has_line_code, string_mod, get_has_line_code)(space_hash.data(), space_hash.size());
    ASSERT_FALSE(has_line_code);
}

TEST(get_has_line_code_must_work_properly, a_space)
{
    std::string_view a_space { "a " };
    int has_line_code = FortranCInterface_MODULE_(string_mod, get_has_line_code, string_mod, get_has_line_code)(a_space.data(), a_space.size());
    ASSERT_TRUE(has_line_code);
}

TEST(get_has_line_code_must_work_properly, a_a)
{
    std::string_view a_a { "aa" };
    int has_line_code = FortranCInterface_MODULE_(string_mod, get_has_line_code, string_mod, get_has_line_code)(a_a.data(), a_a.size());
    ASSERT_TRUE(has_line_code);
}

TEST(get_has_line_code_must_work_properly, a_hash)
{
    std::string_view a_hash { "a#" };
    int has_line_code = FortranCInterface_MODULE_(string_mod, get_has_line_code, string_mod, get_has_line_code)(a_hash.data(), a_hash.size());
    ASSERT_TRUE(has_line_code);
}

TEST(get_has_line_code_must_work_properly, hash_space)
{
    std::string_view hash_space { "# " };
    int has_line_code = FortranCInterface_MODULE_(string_mod, get_has_line_code, string_mod, get_has_line_code)(hash_space.data(), hash_space.size());
    ASSERT_FALSE(has_line_code);
}

TEST(get_has_line_code_must_work_properly, hash_a)
{
    std::string_view hash_a { "#a" };
    int has_line_code = FortranCInterface_MODULE_(string_mod, get_has_line_code, string_mod, get_has_line_code)(hash_a.data(), hash_a.size());
    ASSERT_FALSE(has_line_code);
}

TEST(get_has_line_code_must_work_properly, hash_hash)
{
    std::string_view hash_hash { "##" };
    int has_line_code = FortranCInterface_MODULE_(string_mod, get_has_line_code, string_mod, get_has_line_code)(hash_hash.data(), hash_hash.size());
    ASSERT_FALSE(has_line_code);
}

TEST(get_has_line_code_must_work_properly, space_a_space)
{
    std::string_view space_a_space { " a " };
    int has_line_code = FortranCInterface_MODULE_(string_mod, get_has_line_code, string_mod, get_has_line_code)(space_a_space.data(), space_a_space.size());
    ASSERT_TRUE(has_line_code);
}

TEST(get_has_line_code_must_work_properly, a_space_a)
{
    std::string_view a_space_a { "a a" };
    int has_line_code = FortranCInterface_MODULE_(string_mod, get_has_line_code, string_mod, get_has_line_code)(a_space_a.data(), a_space_a.size());
    ASSERT_TRUE(has_line_code);
}

TEST(get_has_line_code_must_work_properly, space_hash_space)
{
    std::string_view space_hash_space { " # " };
    int has_line_code = FortranCInterface_MODULE_(string_mod, get_has_line_code, string_mod, get_has_line_code)(space_hash_space.data(), space_hash_space.size());
    ASSERT_FALSE(has_line_code);
}

TEST(get_has_line_code_must_work_properly, a_space_hash)
{
    std::string_view a_space_hash { "# #" };
    int has_line_code = FortranCInterface_MODULE_(string_mod, get_has_line_code, string_mod, get_has_line_code)(a_space_hash.data(), a_space_hash.size());
    ASSERT_FALSE(has_line_code);
}

TEST(get_has_line_code_must_work_properly, abc)
{
    std::string_view abc { "abc" };
    int has_line_code = FortranCInterface_MODULE_(string_mod, get_has_line_code, string_mod, get_has_line_code)(abc.data(), abc.size());
    ASSERT_TRUE(has_line_code);
}
