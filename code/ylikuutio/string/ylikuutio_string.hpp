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

#ifndef YLIKUUTIO_STRING_YLIKUUTIO_STRING_HPP_INCLUDED
#define YLIKUUTIO_STRING_YLIKUUTIO_STRING_HPP_INCLUDED

// Include standard headers
#include <cstddef>     // std::byte, std::size_t
#include <cstdlib>     // std::strtod, std::strtof, std::strtol, std::strtoul
#include <iostream>    // std::cout, std::cerr
#include <limits>      // std::numeric_limits
#include <stdint.h>    // uint32_t etc.
#include <optional>    // std::nullopt, std::optional
#include <string>      // std::string
#include <string_view> // std::string_view
#include <vector>      // std::vector

namespace yli::string
{
    bool check_and_report_if_some_string_matches(
            std::string_view data_string,
            const std::size_t data_index,
            const std::vector<std::string>& identifier_strings_vector);

    // All string extraction functions of `yli::string` advance either
    // `data_index` or `src_data_pointer` to the first character that
    // does not belong in the extracted string.
    // If no string is extracted, then `data_index` or `src_data_pointer`
    // (according to the function) is not modified.

    std::string extract_string(
            std::string_view data_string,
            std::size_t& data_index,
            const char separator);

    std::string extract_string_with_several_endings(
            std::string_view data_string,
            std::size_t& data_index,
            std::string_view char_end_string);

    std::string extract_last_part_of_string(
            std::string_view data_string,
            const char separator);

    template<typename T>
        std::optional<T> convert_string_to_signed_integer(std::string_view string)
        {
            int32_t value = std::strtol(std::string(string).c_str(), nullptr, 10); // base 10.

            if (value < std::numeric_limits<T>::min())
            {
                std::cerr << "ERROR: `yli::string::convert_string_to_signed_integer`: value " << value << " is too small for the type!\n";
                return std::nullopt;
            }
            else if (value > std::numeric_limits<T>::max())
            {
                std::cerr << "ERROR: `yli::string::convert_string_to_signed_integer`: value " << value << " is too big for the type!\n";
                return std::nullopt;
            }

            return static_cast<T>(value);
        }

    template<typename T>
        std::optional<T> convert_string_to_unsigned_integer(std::string_view string)
        {
            uint32_t value = std::strtoul(std::string(string).c_str(), nullptr, 10); // base 10.

            if (value > std::numeric_limits<T>::max())
            {
                std::cerr << "ERROR: `yli::string::convert_string_to_unsigned_integer`: value " << value << " is too big for the type!\n";
                return std::nullopt;
            }

            return static_cast<T>(value);
        }

    template<typename T>
        std::optional<T> convert_string_to_value(std::string_view string) = delete;

    template<>
        inline std::optional<int8_t> convert_string_to_value<int8_t>(std::string_view string)
        {
            return yli::string::convert_string_to_signed_integer<int8_t>(string);
        }

    template<>
        inline std::optional<uint8_t> convert_string_to_value<uint8_t>(std::string_view string)
        {
            return yli::string::convert_string_to_unsigned_integer<uint8_t>(string);
        }

    template<>
        inline std::optional<int16_t> convert_string_to_value<int16_t>(std::string_view string)
        {
            return yli::string::convert_string_to_signed_integer<int16_t>(string);
        }

    template<>
        inline std::optional<uint16_t> convert_string_to_value<uint16_t>(std::string_view string)
        {
            return yli::string::convert_string_to_unsigned_integer<uint16_t>(string);
        }

    template<>
        inline std::optional<int32_t> convert_string_to_value<int32_t>(std::string_view string)
        {
            return yli::string::convert_string_to_signed_integer<int32_t>(string);
        }

    template<>
        inline std::optional<uint32_t> convert_string_to_value<uint32_t>(std::string_view string)
        {
            return yli::string::convert_string_to_unsigned_integer<uint32_t>(string);
        }

    template<>
        inline std::optional<float> convert_string_to_value<float>(std::string_view string)
        {
            return std::strtof(std::string(string).c_str(), nullptr);
        }

    template<>
        inline std::optional<double> convert_string_to_value<double>(std::string_view string)
        {
            return std::strtod(std::string(string).c_str(), nullptr);
        }

    template<typename T>
        std::optional<T> extract_value_from_string(
                std::string_view data_string,
                std::size_t& data_index,
                std::string_view char_end_string,
                std::string_view description)
        {
            std::string string = yli::string::extract_string_with_several_endings(
                    data_string,
                    data_index,
                    char_end_string);

            std::optional<T> value = yli::string::convert_string_to_value<T>(string);

            if (!value)
            {
                std::cerr << "ERROR: `yli::string::extract_value_from_string`: converting string to value failed!\n";
                return std::nullopt;
            }

            if (!description.empty())
            {
                std::cout << description << ": " << *value << "\n";
            }
            return value;
        }

    template<typename T>
        T extract_value_or_throw(
                std::string_view data_string,
                std::size_t& data_index,
                std::string_view char_end_string,
                std::string_view description)
        {
            std::optional<T> value = yli::string::extract_value_from_string<T>(data_string, data_index, char_end_string, description);

            if (!value)
            {
                throw std::runtime_error("ERROR: `yli::string::extract_value_or_throw`: extracting value failed!");
            }

            return *value;
        }

    std::optional<int32_t> extract_unicode_value_from_string(const char*& unicode_char_pointer);

    template<typename Alloc, template<typename, typename> typename T1>
        std::string convert_char_container_to_std_string(
                const T1<char, Alloc>& char_container,
                const std::size_t first_line_length,
                const std::size_t line_length)
        {
            std::string my_string;
            std::size_t remaining_characters_on_this_line = first_line_length;

            for (auto it = char_container.begin(); it != char_container.end(); ++it)
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

            for (auto it = char_container.begin(); it != char_container.end(); ++it)
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

    bool check_if_float_string(std::string_view my_string);
    bool check_if_double_string(std::string_view my_string);
    bool check_if_floating_point_string(std::string_view my_string, const std::size_t safe_number_of_chars);

    bool check_if_signed_integer_string(std::string_view my_string);

    bool check_if_unsigned_integer_string(std::string_view my_string);

    void print_hexdump(const std::byte* const start_address, const std::byte* const end_address); // `begin` is inclusive, `end is exclusive.
    void print_hexdump(std::string_view my_string);
}

#endif
