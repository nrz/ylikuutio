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

extern "C"
{
    char* FortranCInterface_MODULE_(file_mod, read_file, file_mod, read_file)(const char* file_content, int sz, int* file_sz);

    int FortranCInterface_MODULE_(parser_mod, parse, parser_mod, parse)(
            const char* content, int sz,
            int* begin_global_parameters_line_i, int* end_global_parameters_line_i,
            int* begin_objects_line_i, int* end_objects_line_i);
}

TEST(file_parsing_must_work_properly, empty_file)
{
    std::string_view file_name { "empty_file_for_testing.dat" };
    int file_sz = 0;
    char* content = FortranCInterface_MODULE_(file_mod, read_file, file_mod, read_file)(file_name.data(), file_name.size(), &file_sz);
    ASSERT_EQ(file_sz, 0); // File read successfully!

    int begin_global_parameters_line_i;
    int end_global_parameters_line_i;
    int begin_objects_line_i;
    int end_objects_line_i;
    int success = FortranCInterface_MODULE_(parser_mod, parse, parser_mod, parse)(
            content,
            file_sz,
            &begin_global_parameters_line_i,
            &end_global_parameters_line_i,
            &begin_objects_line_i,
            &end_objects_line_i);
    ASSERT_FALSE(success);
}

TEST(file_parsing_must_work_properly, invalid_file_one_line)
{
    std::string_view file_name { "one_line_for_testing.dat" };
    int file_sz = 0;
    char* content = FortranCInterface_MODULE_(file_mod, read_file, file_mod, read_file)(file_name.data(), file_name.size(), &file_sz);
    ASSERT_EQ(file_sz, 43); // File read successfully!
                            //
    int begin_global_parameters_line_i;
    int end_global_parameters_line_i;
    int begin_objects_line_i;
    int end_objects_line_i;
    int success = FortranCInterface_MODULE_(parser_mod, parse, parser_mod, parse)(
            content,
            file_sz,
            &begin_global_parameters_line_i,
            &end_global_parameters_line_i,
            &begin_objects_line_i,
            &end_objects_line_i);
    ASSERT_FALSE(success);
}

TEST(file_parsing_must_work_properly, invalid_file_multiple_lines)
{
    std::string_view file_name { "three_lines_for_testing.dat" };
    int file_sz = 0;
    char* content = FortranCInterface_MODULE_(file_mod, read_file, file_mod, read_file)(file_name.data(), file_name.size(), &file_sz);
    ASSERT_EQ(file_sz, 80); // File read successfully!

    int begin_global_parameters_line_i;
    int end_global_parameters_line_i;
    int begin_objects_line_i;
    int end_objects_line_i;
    int success = FortranCInterface_MODULE_(parser_mod, parse, parser_mod, parse)(
            content,
            file_sz,
            &begin_global_parameters_line_i,
            &end_global_parameters_line_i,
            &begin_objects_line_i,
            &end_objects_line_i);
    ASSERT_FALSE(success);
}

TEST(file_parsing_must_work_properly, valid_data)
{
    std::string_view file_name { "input.dat" };
    int file_sz = 0;
    char* content = FortranCInterface_MODULE_(file_mod, read_file, file_mod, read_file)(file_name.data(), file_name.size(), &file_sz);
    ASSERT_EQ(file_sz, 4505); // File read successfully!

    int begin_global_parameters_line_i;
    int end_global_parameters_line_i;
    int begin_objects_line_i;
    int end_objects_line_i;
    int success = FortranCInterface_MODULE_(parser_mod, parse, parser_mod, parse)(
            content,
            file_sz,
            &begin_global_parameters_line_i,
            &end_global_parameters_line_i,
            &begin_objects_line_i,
            &end_objects_line_i);
    ASSERT_TRUE(success);
    ASSERT_EQ(begin_global_parameters_line_i, 39);
    ASSERT_EQ(end_global_parameters_line_i, 42);
    ASSERT_EQ(begin_objects_line_i, 44);
    ASSERT_EQ(end_objects_line_i, 58);
}

TEST(file_parsing_must_work_properly, valid_data_again)
{
    std::string_view file_name { "input.dat" };
    int file_sz = 0;
    char* content = FortranCInterface_MODULE_(file_mod, read_file, file_mod, read_file)(file_name.data(), file_name.size(), &file_sz);
    ASSERT_EQ(file_sz, 4505); // File read successfully!

    int begin_global_parameters_line_i;
    int end_global_parameters_line_i;
    int begin_objects_line_i;
    int end_objects_line_i;
    int success = FortranCInterface_MODULE_(parser_mod, parse, parser_mod, parse)(
            content,
            file_sz,
            &begin_global_parameters_line_i,
            &end_global_parameters_line_i,
            &begin_objects_line_i,
            &end_objects_line_i);
    ASSERT_TRUE(success);
    ASSERT_EQ(begin_global_parameters_line_i, 39);
    ASSERT_EQ(end_global_parameters_line_i, 42);
    ASSERT_EQ(begin_objects_line_i, 44);
    ASSERT_EQ(end_objects_line_i, 58);
}
