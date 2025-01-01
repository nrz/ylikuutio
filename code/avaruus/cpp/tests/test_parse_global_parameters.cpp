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
    char* FortranCInterface_MODULE_(file_mod, read_file, file_mod, read_file)(const char* file_content, int sz, int* file_sz);

    int FortranCInterface_MODULE_(parser_mod, parse, parser_mod, parse)(
            const char* content, int sz,
            int* begin_global_parameters_line_i, int* end_global_parameters_line_i,
            int* begin_objects_line_i, int* end_objects_line_i);

    int FortranCInterface_MODULE_(parser_mod, parse_global_parameters, parser_mod, parse_global_parameters)(
            const char* file_content, int file_sz,
            int begin_global_parameters_line_i,
            int end_global_parameters_line_i,
            int* global_parameters_header_line_i,
            int* global_parameters_value_line_i,
            int* n_objects,
            double* length_of_timestep,
            double* total_length_of_simulation,
            int *print_interval,
            int *save_interval);
}

TEST(global_parameters_parsing_must_work_properly, valid_data)
{
    std::string_view file_name { "input.dat" };
    int file_sz = 0;
    char* content = FortranCInterface_MODULE_(file_mod, read_file, file_mod, read_file)(file_name.data(), file_name.size(), &file_sz);
    ASSERT_GE(file_sz, 0); // File read successfully!

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

    ASSERT_GE(begin_global_parameters_line_i, 1);
    ASSERT_GT(end_global_parameters_line_i, begin_global_parameters_line_i);
    ASSERT_GT(begin_objects_line_i, end_global_parameters_line_i);
    ASSERT_GT(end_objects_line_i, begin_objects_line_i);

    int global_parameters_header_line_i = 0;
    int global_parameters_value_line_i = 0;
    int n_objects = 0;
    double length_of_timestep = 0.0;
    double total_length_of_simulation = 0.0;
    int print_interval = 0;
    int save_interval = 0;
    int global_parameters_parse_success = FortranCInterface_MODULE_(parser_mod, parse_global_parameters, parser_mod, parse_global_parameters)(
            content, file_sz,
            begin_global_parameters_line_i,
            end_global_parameters_line_i,
            &global_parameters_header_line_i,
            &global_parameters_value_line_i,
            &n_objects,
            &length_of_timestep,
            &total_length_of_simulation,
            &print_interval,
            &save_interval);

    ASSERT_NE(global_parameters_parse_success, 0);
    ASSERT_EQ(n_objects, 9);
    ASSERT_EQ(length_of_timestep, 24.00);
    ASSERT_EQ(total_length_of_simulation, 4331.00);
    ASSERT_EQ(print_interval, 10);
    ASSERT_EQ(save_interval, 10);
}
