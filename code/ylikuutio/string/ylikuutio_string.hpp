// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
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

#ifndef __YLIKUUTIO_STRING_YLIKUUTIO_STRING_HPP_INCLUDED
#define __YLIKUUTIO_STRING_YLIKUUTIO_STRING_HPP_INCLUDED

// Include standard headers
#include <cstddef>   // std::size_t
#include <list>      // std::list
#include <stdint.h>  // uint32_t etc.
#include <string>    // std::string
#include <vector>    // std::vector

namespace yli::string
{
    bool check_and_report_if_some_string_matches(
            const char* const base_pointer,
            const char* const data_pointer,
            const std::size_t data_size,
            const std::vector<std::string>& identifier_strings_vector);

    bool check_and_report_if_some_string_matches(
            const std::string& data_string,
            const std::size_t data_index,
            const std::vector<std::string>& identifier_strings_vector);

    // All string extraction functions of `yli::string` advance either
    // `data_index` or `src_data_pointer` to the first character that
    // does not belong in the extracted string.
    // If no string is extracted, then `data_index` or `src_data_pointer`
    // (according to the function) is not modified.

    void extract_string(
            const std::string& data_string,
            std::size_t& data_index,
            std::string& dest_string,
            const char separator);

    void extract_string(
            const char* const src_base_pointer,
            const char*& src_data_pointer,
            const std::size_t src_data_size,
            const char* const dest_base_pointer,
            char* dest_data_pointer,
            const std::size_t dest_data_size,
            const char* const char_end_string);

    void extract_string_with_several_endings(
            const char* const src_base_pointer,
            const char*& src_data_pointer,
            const std::size_t src_data_size,
            const char* const dest_base_pointer,
            char* dest_data_pointer,
            const std::size_t dest_data_size,
            const char* const char_end_string);

    void extract_string_with_several_endings(
            const std::string& data_string,
            std::size_t& data_index,
            const char* const dest_base_pointer,
            char* dest_data_pointer,
            const std::size_t dest_data_size,
            const char* const char_end_string);

    void extract_string_with_several_endings(
            const std::string& data_string,
            std::size_t& data_index,
            std::string& dest_string,
            const char* const char_end_string);

    std::size_t extract_last_part_of_string(
            const char* const src_base_pointer,
            const std::size_t src_data_size,
            char* const dest_base_pointer,
            const std::size_t dest_data_size,
            const char separator);

    std::size_t extract_last_part_of_string(
            const std::string& data_string,
            std::string& dest_string,
            const char separator);

    void extract_value_from_string(
            const char* const src_base_pointer,
            const char*& src_data_pointer,
            const std::size_t src_data_size,
            const char* const char_end_string,
            const char* const description,
            int8_t& value);

    void extract_value_from_string(
            const std::string& data_string,
            std::size_t& data_index,
            const char* const char_end_string,
            const char* const description,
            int8_t& value);

    void extract_value_from_string(
            const char* const src_base_pointer,
            const char*& src_data_pointer,
            const std::size_t src_data_size,
            const char* const char_end_string,
            const char* const description,
            uint8_t& value);

    void extract_value_from_string(
            const std::string& data_string,
            std::size_t& data_index,
            const char* const char_end_string,
            const char* const description,
            uint8_t& value);

    void extract_value_from_string(
            const char* const src_base_pointer,
            const char*& src_data_pointer,
            const std::size_t src_data_size,
            const char* const char_end_string,
            const char* const description,
            int16_t& value);

    void extract_value_from_string(
            const std::string& data_string,
            std::size_t& data_index,
            const char* const char_end_string,
            const char* const description,
            int16_t& value);

    void extract_value_from_string(
            const char* const src_base_pointer,
            const char*& src_data_pointer,
            const std::size_t src_data_size,
            const char* const char_end_string,
            const char* const description,
            uint16_t& value);

    void extract_value_from_string(
            const std::string& data_string,
            std::size_t& data_index,
            const char* const char_end_string,
            const char* const description,
            uint16_t& value);

    void extract_value_from_string(
            const char* const src_base_pointer,
            const char*& src_data_pointer,
            const std::size_t src_data_size,
            const char* const char_end_string,
            const char* const description,
            int32_t& value);

    void extract_value_from_string(
            const std::string& data_string,
            std::size_t& data_index,
            const char* const char_end_string,
            const char* const description,
            int32_t& value);

    void extract_value_from_string(
            const char* const src_base_pointer,
            const char*& src_data_pointer,
            const std::size_t src_data_size,
            const char* const char_end_string,
            const char* const description,
            uint32_t& value);

    void extract_value_from_string(
            const std::string& data_string,
            std::size_t& data_index,
            const char* const char_end_string,
            const char* const description,
            uint32_t& value);

    void extract_value_from_string(
            const char* const src_base_pointer,
            const char*& src_data_pointer,
            const std::size_t src_data_size,
            const char* const char_end_string,
            const char* const description,
            float& value);

    void extract_value_from_string(
            const std::string& data_string,
            std::size_t& data_index,
            const char* const char_end_string,
            const char* const description,
            float& value);

    int8_t extract_int8_t_value_from_string(
            const char* const src_base_pointer,
            const char*& src_data_pointer,
            const std::size_t src_data_size,
            const char* const char_end_string,
            const char* const description);

    int8_t extract_int8_t_value_from_string(
            const std::string& data_string,
            std::size_t& data_index,
            const char* const char_end_string,
            const char* const description);

    uint8_t extract_uint8_t_value_from_string(
            const char* const src_base_pointer,
            const char*& src_data_pointer,
            const std::size_t src_data_size,
            const char* const char_end_string,
            const char* const description);

    uint8_t extract_uint8_t_value_from_string(
            const std::string& data_string,
            std::size_t& data_index,
            const char* const char_end_string,
            const char* const description);

    int16_t extract_int16_t_value_from_string(
            const char* const src_base_pointer,
            const char*& src_data_pointer,
            const std::size_t src_data_size,
            const char* const char_end_string,
            const char* const description);

    int16_t extract_int16_t_value_from_string(
            const std::string& data_string,
            std::size_t& data_index,
            const char* const char_end_string,
            const char* const description);

    uint16_t extract_uint16_t_value_from_string(
            const char* const src_base_pointer,
            const char*& src_data_pointer,
            const std::size_t src_data_size,
            const char* const char_end_string,
            const char* const description);

    uint16_t extract_uint16_t_value_from_string(
            const std::string& data_string,
            std::size_t& data_index,
            const char* const char_end_string,
            const char* const description);

    int32_t extract_int32_t_value_from_string(
            const char* const src_base_pointer,
            const char*& src_data_pointer,
            const std::size_t src_data_size,
            const char* const char_end_string,
            const char* const description);

    int32_t extract_int32_t_value_from_string(
            const std::string& data_string,
            std::size_t& data_index,
            const char* const char_end_string,
            const char* const description);

    uint32_t extract_uint32_t_value_from_string(
            const char* const src_base_pointer,
            const char*& src_data_pointer,
            const std::size_t src_data_size,
            const char* const char_end_string,
            const char* const description);

    uint32_t extract_uint32_t_value_from_string(
            const std::string& data_string,
            std::size_t& data_index,
            const char* const char_end_string,
            const char* const description);

    float extract_float_value_from_string(
            const char* const src_base_pointer,
            const char*& src_data_pointer,
            const std::size_t src_data_size,
            const char* const char_end_string,
            const char* const description);

    float extract_float_value_from_string(
            const std::string& data_string,
            std::size_t& data_index,
            const char* const char_end_string,
            const char* const description);

    int32_t extract_unicode_value_from_string(const char*& unicode_char_pointer);

    template<typename Alloc, template<typename, typename> typename T1>
        std::string convert_char_container_to_std_string(
                const T1<char, Alloc>& char_container,
                const std::size_t first_line_length,
                const std::size_t line_length)
        {
            std::string my_string;
            std::size_t remaining_characters_on_this_line = first_line_length;

            for (auto it = char_container.begin(); it != char_container.end(); it++)
            {
                if (remaining_characters_on_this_line == 0)
                {
                    my_string.push_back('\\');
                    my_string.push_back('n');
                    remaining_characters_on_this_line = line_length;
                }

                my_string.push_back(*it);
                remaining_characters_on_this_line--;
            }

            return my_string;
        }

    template<typename Alloc, template<typename, typename> typename T1>
        std::vector<std::string> convert_char_container_to_std_vector_std_string(
                const T1<char, Alloc>& char_container,
                const std::size_t line_length)
        {
            std::vector<std::string> my_vector;
            std::string my_string;
            std::size_t remaining_characters_on_this_line = line_length;

            for (auto it = char_container.begin(); it != char_container.end(); it++)
            {
                if (remaining_characters_on_this_line == 0)
                {
                    my_vector.emplace_back(my_string);
                    my_string.clear();
                    remaining_characters_on_this_line = line_length;
                }

                my_string.push_back(*it);
                remaining_characters_on_this_line--;
            }

            if (my_string.size() > 0)
            {
                my_vector.emplace_back(my_string);
            }

            return my_vector;
        }

    bool check_if_float_string(const std::string& my_string);
    bool check_if_double_string(const std::string& my_string);
    bool check_if_floating_point_string(const std::string& my_string, const std::size_t safe_number_of_chars);

    bool check_if_signed_integer_string(const std::string& my_string);

    bool check_if_unsigned_integer_string(const std::string& my_string);

    void print_hexdump(const void* const start_address, const void* const end_address); // `begin` is inclusive, `end is exclusive.
    void print_hexdump(const std::string& my_string);
}

#endif
