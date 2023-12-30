#include "gtest/gtest.h"
#include "planetary_simulation.h"

#include <string_view> // std::string_view

extern "C"
{
    char* FortranCInterface_MODULE_(string_mod, get_line, string_mod, get_line)(const char* string, int string_sz, int line_i, int* line_sz);
}

TEST(get_line_must_work_properly, empty_string_line_i_0_must_not_be_found)
{
    std::string_view string { "" };
    int line_i = 0;
    int line_sz = 0;
    char* line = FortranCInterface_MODULE_(string_mod, get_line, string_mod, get_line)(string.data(), string.size(), line_i, &line_sz);
    std::string_view expected_line { "" };
    ASSERT_EQ(expected_line.compare(line), 0);
    ASSERT_EQ(line_sz, -1); // No line found!
    free(line);
}

TEST(get_line_must_work_properly, empty_string_line_i_1_must_not_be_found)
{
    std::string_view string { "" };
    int line_i = 1;
    int line_sz = 0;
    char* line = FortranCInterface_MODULE_(string_mod, get_line, string_mod, get_line)(string.data(), string.size(), line_i, &line_sz);
    std::string_view expected_line { "" };
    ASSERT_EQ(expected_line.compare(line), 0);
    ASSERT_EQ(line_sz, -1); // No line found!
    free(line);
}

TEST(get_line_must_work_properly, empty_string_line_i_2_must_not_be_found)
{
    std::string_view string { "" };
    int line_i = 2;
    int line_sz = 0;
    char* line = FortranCInterface_MODULE_(string_mod, get_line, string_mod, get_line)(string.data(), string.size(), line_i, &line_sz);
    std::string_view expected_line { "" };
    ASSERT_EQ(expected_line.compare(line), 0);
    ASSERT_EQ(line_sz, -1); // No line found!
    free(line);
}

TEST(get_line_must_work_properly, a_string_line_i_0_must_not_be_found)
{
    std::string_view string { "a" };
    int line_i = 0;
    int line_sz = 0;
    char* line = FortranCInterface_MODULE_(string_mod, get_line, string_mod, get_line)(string.data(), string.size(), line_i, &line_sz);
    std::string_view expected_line { "" };
    ASSERT_EQ(expected_line.compare(line), 0);
    ASSERT_EQ(line_sz, -1); // No line found!
    free(line);
}

TEST(get_line_must_work_properly, a_string_line_i_1_must_be_found)
{
    std::string_view string { "a" };
    int line_i = 1;
    int line_sz = 0;
    char* line = FortranCInterface_MODULE_(string_mod, get_line, string_mod, get_line)(string.data(), string.size(), line_i, &line_sz);
    std::string_view expected_line { "a" };
    ASSERT_EQ(expected_line.compare(line), 0);
    ASSERT_EQ(line_sz, 1); // Line size is 1.
    free(line);
}

TEST(get_line_must_work_properly, aa_string_line_i_1_must_be_found)
{
    std::string_view string { "aa" };
    int line_i = 1;
    int line_sz = 0;
    char* line = FortranCInterface_MODULE_(string_mod, get_line, string_mod, get_line)(string.data(), string.size(), line_i, &line_sz);
    std::string_view expected_line { "aa" };
    ASSERT_EQ(expected_line.compare(line), 0);
    ASSERT_EQ(line_sz, 2); // Line size is 2.
    free(line);
}

TEST(get_line_must_work_properly, a_hash_string_line_i_1_must_be_found)
{
    std::string_view string { "a#" };
    int line_i = 1;
    int line_sz = 0;
    char* line = FortranCInterface_MODULE_(string_mod, get_line, string_mod, get_line)(string.data(), string.size(), line_i, &line_sz);
    std::string_view expected_line { "a#" };
    ASSERT_EQ(expected_line.compare(line), 0);
    ASSERT_EQ(line_sz, 2); // Line size is 2.
    free(line);
}

TEST(get_line_must_work_properly, newline_a_string_line_i_1_must_be_found)
{
    std::string_view string { "\na" };
    int line_i = 1;
    int line_sz = 0;
    char* line = FortranCInterface_MODULE_(string_mod, get_line, string_mod, get_line)(string.data(), string.size(), line_i, &line_sz);
    std::string_view expected_line { "\n" };
    ASSERT_EQ(expected_line.compare(line), 0);
    ASSERT_EQ(line_sz, 1); // Line size is 1.
    free(line);
}

TEST(get_line_must_work_properly, newline_a_string_line_i_2_must_be_found)
{
    std::string_view string { "\na" };
    int line_i = 2;
    int line_sz = 0;
    char* line = FortranCInterface_MODULE_(string_mod, get_line, string_mod, get_line)(string.data(), string.size(), line_i, &line_sz);
    std::string_view expected_line { "a" };
    ASSERT_EQ(expected_line.compare(line), 0);
    ASSERT_EQ(line_sz, 1); // Line size is 1.
    free(line);
}

TEST(get_line_must_work_properly, newline_a_newline_string_line_i_2_must_be_found)
{
    std::string_view string { "\na\n" };
    int line_i = 2;
    int line_sz = 0;
    char* line = FortranCInterface_MODULE_(string_mod, get_line, string_mod, get_line)(string.data(), string.size(), line_i, &line_sz);
    std::string_view expected_line { "a\n" };
    ASSERT_EQ(expected_line.compare(line), 0);
    ASSERT_EQ(line_sz, 2); // Line size is 2.
    free(line);
}

TEST(get_line_must_work_properly, newline_a_newline_b_string_line_i_2_must_be_found)
{
    std::string_view string { "\na\nb" };
    int line_i = 2;
    int line_sz = 0;
    char* line = FortranCInterface_MODULE_(string_mod, get_line, string_mod, get_line)(string.data(), string.size(), line_i, &line_sz);
    std::string_view expected_line { "a\n" };
    ASSERT_EQ(expected_line.compare(line), 0);
    ASSERT_EQ(line_sz, 2); // Line size is 2.
    free(line);
}

TEST(get_line_must_work_properly, newline_a_newline_b_string_line_i_3_must_be_found)
{
    std::string_view string { "\na\nb" };
    int line_i = 3;
    int line_sz = 0;
    char* line = FortranCInterface_MODULE_(string_mod, get_line, string_mod, get_line)(string.data(), string.size(), line_i, &line_sz);
    std::string_view expected_line { "b" };
    ASSERT_EQ(expected_line.compare(line), 0);
    ASSERT_EQ(line_sz, 1); // Line size is 1.
    free(line);
}

TEST(get_line_must_work_properly, newline_foo_space_bar_newline_bar_space_qux_new_linestring_line_i_2_must_be_found)
{
    std::string_view string { "\nfoo bar\nbaz qux\n" };
    int line_i = 2;
    int line_sz = 0;
    char* line = FortranCInterface_MODULE_(string_mod, get_line, string_mod, get_line)(string.data(), string.size(), line_i, &line_sz);
    std::string_view expected_line { "foo bar\n" };
    ASSERT_EQ(expected_line.compare(line), 0);
    ASSERT_EQ(line_sz, 8); // Line size is 8.
    free(line);
}

TEST(get_line_must_work_properly, newline_foo_space_bar_newline_bar_space_qux_new_linestring_line_i_3_must_be_found)
{
    std::string_view string { "\nfoo bar\nbaz qux\n" };
    int line_i = 3;
    int line_sz = 0;
    char* line = FortranCInterface_MODULE_(string_mod, get_line, string_mod, get_line)(string.data(), string.size(), line_i, &line_sz);
    std::string_view expected_line { "baz qux\n" };
    ASSERT_EQ(expected_line.compare(line), 0);
    ASSERT_EQ(line_sz, 8); // Line size is 8.
    free(line);
}
