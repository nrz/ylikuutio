#include "gtest/gtest.h"
#include "planetary_simulation.h"

extern "C"
{
    int FortranCInterface_MODULE_(string_mod, get_has_line_code, string_mod, get_has_line_code)(char* string, int sz);
}

#include <cstddef>  // std::size_t

TEST(get_has_line_code_must_work_properly, empty)
{
    char empty[] { "" };
    std::size_t sz = strlen(empty);
    int has_line_code = FortranCInterface_MODULE_(string_mod, get_has_line_code, string_mod, get_has_line_code)(empty, sz);
    ASSERT_FALSE(has_line_code);
}

TEST(get_has_line_code_must_work_properly, space)
{
    char space[] { " " };
    std::size_t sz = strlen(space);
    int has_line_code = FortranCInterface_MODULE_(string_mod, get_has_line_code, string_mod, get_has_line_code)(space, sz);
    ASSERT_FALSE(has_line_code);
}

TEST(get_has_line_code_must_work_properly, a)
{
    char a[] { "a" };
    std::size_t sz = strlen(a);
    int has_line_code = FortranCInterface_MODULE_(string_mod, get_has_line_code, string_mod, get_has_line_code)(a, sz);
    ASSERT_TRUE(has_line_code);
}

TEST(get_has_line_code_must_work_properly, hash)
{
    char hash[] { "#" };
    std::size_t sz = strlen(hash);
    int has_line_code = FortranCInterface_MODULE_(string_mod, get_has_line_code, string_mod, get_has_line_code)(hash, sz);
    ASSERT_FALSE(has_line_code);
}

TEST(get_has_line_code_must_work_properly, space_space)
{
    char space_space[] { "  " };
    std::size_t sz = strlen(space_space);
    int has_line_code = FortranCInterface_MODULE_(string_mod, get_has_line_code, string_mod, get_has_line_code)(space_space, sz);
    ASSERT_FALSE(has_line_code);
}

TEST(get_has_line_code_must_work_properly, space_a)
{
    char space_a[] { " a" };
    std::size_t sz = strlen(space_a);
    int has_line_code = FortranCInterface_MODULE_(string_mod, get_has_line_code, string_mod, get_has_line_code)(space_a, sz);
    ASSERT_TRUE(has_line_code);
}

TEST(get_has_line_code_must_work_properly, space_hash)
{
    char space_hash[] { " #" };
    std::size_t sz = strlen(space_hash);
    int has_line_code = FortranCInterface_MODULE_(string_mod, get_has_line_code, string_mod, get_has_line_code)(space_hash, sz);
    ASSERT_FALSE(has_line_code);
}

TEST(get_has_line_code_must_work_properly, a_space)
{
    char a_space[] { "a " };
    std::size_t sz = strlen(a_space);
    int has_line_code = FortranCInterface_MODULE_(string_mod, get_has_line_code, string_mod, get_has_line_code)(a_space, sz);
    ASSERT_TRUE(has_line_code);
}

TEST(get_has_line_code_must_work_properly, a_a)
{
    char a_a[] { "aa" };
    std::size_t sz = strlen(a_a);
    int has_line_code = FortranCInterface_MODULE_(string_mod, get_has_line_code, string_mod, get_has_line_code)(a_a, sz);
    ASSERT_TRUE(has_line_code);
}

TEST(get_has_line_code_must_work_properly, a_hash)
{
    char a_hash[] { "a#" };
    std::size_t sz = strlen(a_hash);
    int has_line_code = FortranCInterface_MODULE_(string_mod, get_has_line_code, string_mod, get_has_line_code)(a_hash, sz);
    ASSERT_TRUE(has_line_code);
}

TEST(get_has_line_code_must_work_properly, hash_space)
{
    char hash_space[] { "# " };
    std::size_t sz = strlen(hash_space);
    int has_line_code = FortranCInterface_MODULE_(string_mod, get_has_line_code, string_mod, get_has_line_code)(hash_space, sz);
    ASSERT_FALSE(has_line_code);
}

TEST(get_has_line_code_must_work_properly, hash_a)
{
    char hash_a[] { "#a" };
    std::size_t sz = strlen(hash_a);
    int has_line_code = FortranCInterface_MODULE_(string_mod, get_has_line_code, string_mod, get_has_line_code)(hash_a, sz);
    ASSERT_FALSE(has_line_code);
}

TEST(get_has_line_code_must_work_properly, hash_hash)
{
    char hash_hash[] { "##" };
    std::size_t sz = strlen(hash_hash);
    int has_line_code = FortranCInterface_MODULE_(string_mod, get_has_line_code, string_mod, get_has_line_code)(hash_hash, sz);
    ASSERT_FALSE(has_line_code);
}

TEST(get_has_line_code_must_work_properly, space_a_space)
{
    char space_a_space[] { " a " };
    std::size_t sz = strlen(space_a_space);
    int has_line_code = FortranCInterface_MODULE_(string_mod, get_has_line_code, string_mod, get_has_line_code)(space_a_space, sz);
    ASSERT_TRUE(has_line_code);
}

TEST(get_has_line_code_must_work_properly, a_space_a)
{
    char a_space_a[] { "a a" };
    std::size_t sz = strlen(a_space_a);
    int has_line_code = FortranCInterface_MODULE_(string_mod, get_has_line_code, string_mod, get_has_line_code)(a_space_a, sz);
    ASSERT_TRUE(has_line_code);
}

TEST(get_has_line_code_must_work_properly, space_hash_space)
{
    char space_hash_space[] { " # " };
    std::size_t sz = strlen(space_hash_space);
    int has_line_code = FortranCInterface_MODULE_(string_mod, get_has_line_code, string_mod, get_has_line_code)(space_hash_space, sz);
    ASSERT_FALSE(has_line_code);
}

TEST(get_has_line_code_must_work_properly, a_space_hash)
{
    char a_space_hash[] { "# #" };
    std::size_t sz = strlen(a_space_hash);
    int has_line_code = FortranCInterface_MODULE_(string_mod, get_has_line_code, string_mod, get_has_line_code)(a_space_hash, sz);
    ASSERT_FALSE(has_line_code);
}

TEST(get_has_line_code_must_work_properly, abc)
{
    char abc[] { "abc" };
    std::size_t sz = strlen(abc);
    int has_line_code = FortranCInterface_MODULE_(string_mod, get_has_line_code, string_mod, get_has_line_code)(abc, sz);
    ASSERT_TRUE(has_line_code);
}
