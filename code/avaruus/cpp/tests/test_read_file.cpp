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
    char* FortranCInterface_MODULE_(file_mod, read_file, file_mod, read_file)(const char* string, int sz, int* file_sz);
}

TEST(read_file_must_work_properly, empty_filename_string)
{
    std::string_view file_name { "" };
    int file_sz = 0;
    char* content = FortranCInterface_MODULE_(file_mod, read_file, file_mod, read_file)(file_name.data(), file_name.size(), &file_sz);
    std::string_view expected_content { "" };
    ASSERT_EQ(expected_content.compare(content), 0);
    ASSERT_EQ(file_sz, -1); // File not found!
}

TEST(read_file_must_work_properly, empty_file)
{
    std::string_view file_name { "empty_file_for_testing.dat" };
    int file_sz = 0;
    char* content = FortranCInterface_MODULE_(file_mod, read_file, file_mod, read_file)(file_name.data(), file_name.size(), &file_sz);
    std::string_view expected_content { "" };
    ASSERT_EQ(expected_content.compare(content), 0);
    ASSERT_EQ(file_sz, 0); // File read successfully!
}

TEST(read_file_must_work_properly, one_line)
{
    std::string_view file_name { "one_line_for_testing.dat" };
    int file_sz = 0;
    char* content = FortranCInterface_MODULE_(file_mod, read_file, file_mod, read_file)(file_name.data(), file_name.size(), &file_sz);
    std::string_view expected_content { "# Hello! This file is used for unit tests!\n" };
    ASSERT_EQ(expected_content.compare(content), 0);
    ASSERT_EQ(file_sz, 43); // File read successfully!
}

TEST(read_file_must_work_properly, multiple_lines)
{
    std::string_view file_name { "three_lines_for_testing.dat" };
    int file_sz = 0;
    char* content = FortranCInterface_MODULE_(file_mod, read_file, file_mod, read_file)(file_name.data(), file_name.size(), &file_sz);
    std::string_view expected_content { "# Hello! This file is used for unit tests!\n# Second line!\n# Third line as well!\n" };
    ASSERT_EQ(expected_content.compare(content), 0);
    ASSERT_EQ(file_sz, 80); // File read successfully!
}
