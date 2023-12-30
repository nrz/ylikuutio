#include "gtest/gtest.h"
#include "planetary_simulation.h"

#include <string_view> // std::string_view

extern "C"
{
    char* FortranCInterface_MODULE_(file_mod, read_file, file_mod, read_file)(const char* string, int sz, int* status);
}

TEST(read_file_must_work_properly, empty_filename_string)
{
    std::string_view file_name { "" };
    int status = 0;
    char* content = FortranCInterface_MODULE_(file_mod, read_file, file_mod, read_file)(file_name.data(), file_name.size(), &status);
    std::string_view expected_content { "" };
    ASSERT_EQ(expected_content.compare(content), 0);
    ASSERT_EQ(status, -1); // File not found!
    free(content);
}

TEST(read_file_must_work_properly, empty_file)
{
    std::string_view file_name { "empty_file_for_testing.dat" };
    int status = 0;
    char* content = FortranCInterface_MODULE_(file_mod, read_file, file_mod, read_file)(file_name.data(), file_name.size(), &status);
    std::string_view expected_content { "" };
    ASSERT_EQ(expected_content.compare(content), 0);
    ASSERT_EQ(status, 1); // File read successfully!
    free(content);
}

TEST(read_file_must_work_properly, one_line)
{
    std::string_view file_name { "one_line_for_testing.dat" };
    int status = 0;
    char* content = FortranCInterface_MODULE_(file_mod, read_file, file_mod, read_file)(file_name.data(), file_name.size(), &status);
    std::string_view expected_content { "# Hello! This file is used for unit tests!\n" };
    ASSERT_EQ(expected_content.compare(content), 0);
    ASSERT_EQ(status, 1); // File read successfully!
    free(content);
}

TEST(read_file_must_work_properly, multiple_lines)
{
    std::string_view file_name { "three_lines_for_testing.dat" };
    int status = 0;
    char* content = FortranCInterface_MODULE_(file_mod, read_file, file_mod, read_file)(file_name.data(), file_name.size(), &status);
    std::string_view expected_content { "# Hello! This file is used for unit tests!\n# Second line!\n# Third line as well!\n" };
    ASSERT_EQ(expected_content.compare(content), 0);
    ASSERT_EQ(status, 1); // File read successfully!
    free(content);
}
