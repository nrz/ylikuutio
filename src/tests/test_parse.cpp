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
    free(content);
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
    free(content);
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
    free(content);
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
    free(content);
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
    free(content);
}
