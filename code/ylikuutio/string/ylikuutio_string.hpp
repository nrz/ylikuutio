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

#ifndef YLIKUUTIO_STRING_YLIKUUTIO_STRING_HPP_INCLUDED
#define YLIKUUTIO_STRING_YLIKUUTIO_STRING_HPP_INCLUDED

// Include standard headers
#include <cstddef>     // std::byte, std::size_t
#include <cstdlib>     // std::strtod, std::strtof, std::strtoll, std::strtoull
#include <iomanip>     // std::setfill, std::setw
#include <ios>         // std::hex
#include <iostream>    // std::cout, std::cerr
#include <limits>      // std::numeric_limits
#include <optional>    // std::nullopt, std::optional
#include <stdint.h>    // uint32_t etc.
#include <string>      // std::basic_string, std::string
#include <sstream>     // std::stringstream
#include <string_view> // std::basic_string_view, std::string_view
#include <vector>      // std::vector

namespace yli::string
{
    template<typename CharType>
        inline bool check_and_report_if_some_string_matches(
                std::basic_string_view<CharType> data_string,
                const std::size_t data_index,
                const std::vector<std::basic_string<CharType>>& identifier_strings_vector)
        {
            for (const std::basic_string<CharType>& identifier_string : identifier_strings_vector)
            {
                if (data_index + identifier_string.size() > data_string.size())
                {
                    // If current `identifier_string` can't fit in the memory region,
                    // proceed to the next `identifier_string`, if there is any left.
                    continue;
                }

                if (data_string.compare(data_index, identifier_string.size(), identifier_string) == 0)
                {
                    return true;
                }
            }

            return false;
        }

    // All string extraction functions of `yli::string` advance either
    // `data_index` or `src_data_pointer` to the first character that
    // does not belong in the extracted string.
    // If no string is extracted, then `data_index` or `src_data_pointer`
    // (according to the function) is not modified.

    template<typename CharType>
        inline std::basic_string<CharType> extract_string_with_several_endings(
                std::basic_string_view<CharType> data_string,
                std::size_t& data_index,
                std::basic_string_view<CharType> char_end_string)
        {
            // This function copies characters from `src_data_pointer` until a character matches.
            if (data_index >= data_string.size())
            {
                return "";
            }

            std::size_t original_data_index = data_index;

            while (data_index < data_string.size())
            {
                typename std::basic_string_view<CharType>::const_iterator end_char_it = char_end_string.begin();
                const CharType current_char = data_string.at(data_index);

                // Check if current character is any of the ending characters.
                while (end_char_it != char_end_string.end())
                {
                    if (current_char == *end_char_it)
                    {
                        return std::basic_string<CharType>(data_string.substr(original_data_index, data_index - original_data_index));
                    }
                    ++end_char_it;
                }

                // OK, current character is not any of the ending characters.
                data_index++;
            }

            return std::basic_string<CharType>(data_string.substr(original_data_index, data_index - original_data_index));
        }

    template<typename CharType>
        inline std::basic_string<CharType> extract_last_part_of_string(
                std::basic_string_view<CharType> data_string,
                const CharType separator)
        {
            std::size_t length_of_last_part_of_string = 0;
            auto separator_it = data_string.end(); // by default no last part.

            for (auto it = data_string.begin(); it != data_string.end(); ++it)
            {
                if (*it == separator)
                {
                    separator_it = it;
                    length_of_last_part_of_string = 0;
                }
                else
                {
                    length_of_last_part_of_string++;
                }
            }

            if (separator_it == data_string.end())
            {
                return "";
            }

            ++separator_it;
            return std::basic_string<CharType>(separator_it, data_string.end());
        }

    template<typename CharType>
        inline std::basic_string<CharType> extract_string(
                std::basic_string_view<CharType> data_string,
                std::size_t& data_index,
                const CharType separator)
        {
            return yli::string::extract_string_with_several_endings<CharType>(
                    data_string,
                    data_index,
                    std::basic_string<CharType>(1, separator));
        }

    template<typename CharType>
        inline std::optional<int32_t> extract_unicode_value_from_string(const CharType*& unicode_char_pointer)
        {
            if (*unicode_char_pointer == '\0')
            {
                unicode_char_pointer++;
                std::cerr << "Error: Unicode can not begin with \\0!\n";
                return 0xdfff; // invalid unicode!
            }

            if (*unicode_char_pointer != '&')
            {
                // it's just a character, so return its value,
                // and advance to the next character.
                return (int32_t) *unicode_char_pointer++;
            }

            if (*++unicode_char_pointer != '#')
            {
                // not valid format, must begin `"&#x"`.
                unicode_char_pointer++;
                std::cerr << "Error: Unicode string format not supported!\n";
                return 0xdfff; // invalid unicode!
            }

            if (*++unicode_char_pointer != 'x')
            {
                // not valid format, must begin `"&#x"`.
                unicode_char_pointer++;
                std::cerr << "Error: Unicode string format not supported!\n";
                return 0xdfff; // invalid unicode!
            }

            // valid format.
            std::basic_string<CharType> hex_string;

            // unicode string beginning with '&'
            while (*++unicode_char_pointer != ';')
            {
                if (*unicode_char_pointer == '\0')
                {
                    std::cerr << "Error: Null character \\0 reached before end of Unicode string!\n";
                    return 0xdfff; // invalid unicode!
                }

                hex_string.append(unicode_char_pointer);
            }

            // Advance to the next character.
            unicode_char_pointer++;

            // convert hexadecimal string to signed integer.
            // http://stackoverflow.com/questions/1070497/c-convert-hex-string-to-signed-integer/1070499#1070499
            uint32_t unicode_value;
            std::stringstream unicode_stringstream;
            unicode_stringstream << std::hex << hex_string;
            unicode_stringstream >> unicode_value;
            return unicode_value;
        }

    template<typename T>
        std::optional<T> convert_string_to_signed_integer(std::string_view string)
        {
            const int64_t value = std::strtoll(std::string(string).c_str(), nullptr, 10); // base 10.

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
            const uint64_t value = std::strtoull(std::string(string).c_str(), nullptr, 10); // base 10.

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
        inline std::optional<int64_t> convert_string_to_value<int64_t>(std::string_view string)
        {
            return yli::string::convert_string_to_signed_integer<int64_t>(string);
        }

    template<>
        inline std::optional<uint64_t> convert_string_to_value<uint64_t>(std::string_view string)
        {
            return yli::string::convert_string_to_unsigned_integer<uint64_t>(string);
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

    template<typename CharType, typename ValueType>
        std::optional<ValueType> extract_value_from_string(
                std::string_view data_string,
                std::size_t& data_index,
                std::string_view char_end_string,
                std::string_view description)
        {
            std::string string = yli::string::extract_string_with_several_endings<CharType>(
                    data_string,
                    data_index,
                    char_end_string);

            std::optional<ValueType> value = yli::string::convert_string_to_value<ValueType>(string);

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

    template<typename CharType, typename ValueType>
        ValueType extract_value_or_throw(
                std::basic_string_view<CharType> data_string,
                std::size_t& data_index,
                std::basic_string_view<CharType> char_end_string,
                std::basic_string_view<CharType> description)
        {
            std::optional<ValueType> value = yli::string::extract_value_from_string<CharType, ValueType>(data_string, data_index, char_end_string, description);

            if (!value)
            {
                throw std::runtime_error("ERROR: `yli::string::extract_value_or_throw`: extracting value failed!");
            }

            return *value;
        }

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

    template<typename CharType>
        inline bool check_if_floating_point_string(std::basic_string_view<CharType> my_string, const std::size_t safe_number_of_chars)
        {
            std::size_t n_chars = 0;

            if (my_string.empty())
            {
                return false;
            }

            bool is_dot_found = false;

            for (std::size_t i = 0; i < my_string.size(); i++)
            {
                // Each of the characters must be one of the following:
                // 0123456789.-
                //
                // Besides, there may be only 1 dot. The dot may not be the last character.
                // Besides, there may be only 1 minus sign. The minus sign must be the first character.

                if (my_string.at(i) == '-' && i == 0)
                {
                    // Minus sign is OK.
                    continue;
                }

                if (my_string.at(i) == '.')
                {
                    if (is_dot_found)
                    {
                        // Two or more dots.
                        return false;
                    }

                    if (i == my_string.size() - 1)
                    {
                        // Last character is dot.
                        return false;
                    }

                    // OK, decimal point here.
                    is_dot_found = true;
                    continue;
                }

                if (my_string.at(i) < '0' || my_string.at(i) > '9')
                {
                    return false;
                }

                if (!is_dot_found)
                {
                    if (++n_chars > safe_number_of_chars)
                    {
                        // Too many characters, maximum safe number is 38 characters for float, 308 for double.
                        return false;
                    }
                }
            }

            return true;
        }

    template<typename CharType>
        inline bool check_if_signed_integer_string(std::basic_string_view<CharType> my_string)
        {
            if (my_string.empty())
            {
                return false;
            }

            for (std::size_t i = 0; i < my_string.size(); i++)
            {
                // Each of the characters must be one of the following:
                // 0123456789
                if (my_string.at(i) == '-' && i == 0)
                {
                    // Minus sign is OK.
                    continue;
                }

                if (my_string.at(i) < '0' || my_string.at(i) > '9')
                {
                    return false;
                }
            }

            return true;
        }

    template<typename CharType>
        inline bool check_if_unsigned_integer_string(std::basic_string_view<CharType> my_string)
        {
            if (my_string.empty())
            {
                return false;
            }

            for (std::size_t i = 0; i < my_string.size(); i++)
            {
                // Each of the characters must be one of the following:
                // 0123456789

                if (my_string.at(i) < '0' || my_string.at(i) > '9')
                {
                    return false;
                }
            }

            return true;
        }

    template<typename CharType>
        inline bool check_if_float_string(std::basic_string_view<CharType> my_string)
        {
            const std::size_t maximum_safe_length_for_float_string = 38;
            return check_if_floating_point_string(my_string, maximum_safe_length_for_float_string);
        }

    template<typename CharType>
        inline bool check_if_double_string(std::basic_string_view<CharType> my_string)
        {
            const std::size_t maximum_safe_length_for_double_string = 308;
            return check_if_floating_point_string(my_string, maximum_safe_length_for_double_string);
        }

    void print_hexdump(const std::byte* const start_address, const std::byte* const end_address); // `begin` is inclusive, `end is exclusive.

    template<typename CharType>
        inline void print_hexdump(std::basic_string_view<CharType> my_string)
        {
            const std::size_t line_width_in_bytes = 16 / sizeof(CharType);
            std::size_t characters_on_this_line = 0;
            std::string current_line_ascii = "";
            std::string current_line_hex = "";

            for (auto it = my_string.begin(); it != my_string.end(); ++it)
            {
                const CharType data_byte = *it;
                const char data_char = (data_byte >= 0x20 && data_byte <= 0x7f ? static_cast<char>(data_byte) : '.');
                current_line_ascii += data_char;

                const uint32_t data_32_bit = static_cast<uint32_t>(data_byte); // to get the hexadecimal representation instead of the actual value.
                std::stringstream my_stream;
                my_stream << std::setfill('0') << std::setw(sizeof(CharType) / 4) << std::hex << data_32_bit << std::dec; // std::hex does not work on char values.
                current_line_hex += my_stream.str();
                current_line_hex += " ";

                if (++characters_on_this_line >= line_width_in_bytes)
                {
                    std::cout << current_line_hex << " " << current_line_ascii << "\n";
                    current_line_hex = "";
                    current_line_ascii = "";
                    characters_on_this_line = 0;
                }
            }

            if (characters_on_this_line > 0)
            {
                const std::size_t size_of_each_bytes_hexdump = sizeof(CharType) / 4 + 1; // each byte's hexdump takes some characters.
                const std::size_t number_of_spaces_needed = (line_width_in_bytes - characters_on_this_line) * size_of_each_bytes_hexdump + 1;
                std::cout << current_line_hex << std::string(number_of_spaces_needed, ' ') << current_line_ascii << "\n";
            }

            std::cout << "\n";
        }
}

#endif
