#ifndef __YLIKUUTIO_STRING_HPP_INCLUDED
#define __YLIKUUTIO_STRING_HPP_INCLUDED

// Include standard headers
#include <list>      // std::list
#include <string>    // std::string
#include <vector>    // std::vector

namespace string
{
    bool check_and_report_if_some_string_matches(const char* const file_base_pointer, const char* const file_data_pointer, std::vector<std::string> identifier_strings_vector);

    void extract_string(char* dest_mem_pointer, char*& src_mem_pointer, const char* const char_end_string);

    void extract_string_with_several_endings(char* dest_mem_pointer, char*& src_mem_pointer, const char* const char_end_string);

    int32_t extract_int32_t_value_from_string(char*& data_pointer, char* char_end_string, const char* const description);

    float extract_float_value_from_string(char*& data_pointer, char* char_end_string, const char* const description);

    int32_t extract_unicode_value_from_string(const char*& unicode_char_pointer);

    std::string convert_std_list_char_to_std_string(const std::list<char>& std_list_char);

    std::string convert_std_list_char_to_std_string(const std::list<char>& std_list_char, uint32_t first_line_length, uint32_t line_length);
}

#endif
