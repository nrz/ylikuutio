// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
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

#include "ylikuutio_string.hpp"

// Include standard headers
#include <algorithm> // std::copy
#include <cstddef>   // std::size_t
#include <cstdlib>   // std::strtod, std::strtof, std::strtol, std::strtold, std::strtoll, std::strtoul, std::strtoull
#include <cstring>   // std::memcmp, std::memcpy, std::strcmp, std::strlen, std::strncmp
#include <iomanip>   // std::setfill, std::setw
#include <iostream>  // std::cout, std::cin, std::cerr
#include <limits>    // std::numeric_limits
#include <list>      // std::list
#include <sstream>   // std::istringstream, std::ostringstream, std::stringstream
#include <stdint.h>  // uint32_t etc.
#include <string>    // std::string
#include <vector>    // std::vector

namespace yli
{
    namespace string
    {
        bool check_and_report_if_some_string_matches(
                const char* const base_pointer,
                const char* const data_pointer,
                const std::size_t data_size,
                const std::vector<std::string> identifier_strings_vector)
        {
            for (const std::string& identifier_string : identifier_strings_vector)
            {
                const char* const identifier_string_char = identifier_string.c_str();

                if (data_pointer + identifier_string.size() > base_pointer + data_size)
                {
                    // If current `identifier_string` can't fit in the memory region,
                    // proceed to the next `identifier_string`, if there is any left.
                    continue;
                }

                if (std::strncmp(data_pointer, identifier_string_char, std::strlen(identifier_string_char)) == 0)
                {
                    return true;
                }
            }
            return false;
        }

        bool check_and_report_if_some_string_matches(
                const std::string& data_string,
                const std::size_t data_index,
                const std::vector<std::string> identifier_strings_vector)
        {
            for (const std::string& identifier_string : identifier_strings_vector)
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

        void extract_string(
                const std::string& data_string,
                std::size_t& data_index,
                std::string& dest_string,
                const char separator)
        {
            const char char_end_string[2] = { separator, '\0' };
            yli::string::extract_string_with_several_endings(
                    data_string,
                    data_index,
                    dest_string,
                    char_end_string);
        }

        void extract_string(
                const char* const src_base_pointer,
                char*& src_data_pointer,
                const std::size_t src_data_size,
                const char* const dest_base_pointer,
                char* dest_data_pointer,
                const std::size_t dest_data_size,
                const char* const char_end_string)
        {
            // + 1 needed for both source and dest because of the null terminator.
            while (src_data_pointer + 1 < src_base_pointer + src_data_size &&
                    dest_data_pointer + 1 < dest_base_pointer + dest_data_size &&
                    std::strncmp(src_data_pointer, char_end_string, std::strlen(char_end_string)) != 0)
            {
                strncpy(dest_data_pointer++, src_data_pointer++, 1);
            }
            *dest_data_pointer = '\0';
        }

        void extract_string_with_several_endings(
                const char* const src_base_pointer,
                char*& src_data_pointer,
                const std::size_t src_data_size,
                const char* const dest_base_pointer,
                char* dest_data_pointer,
                const std::size_t dest_data_size,
                const char* const char_end_string)
        {
            // This function copies characters from `src_data_pointer` until a character matches.

            // + 1 needed for both source and dest because of the null terminator.
            while (src_data_pointer + 1 < src_base_pointer + src_data_size &&
                    dest_data_pointer + 1 < dest_base_pointer + dest_data_size)
            {
                const char* end_char_pointer;
                end_char_pointer = char_end_string;

                // Check if current character is any of the ending characters.
                while (end_char_pointer != nullptr && *end_char_pointer != '\0')
                {
                    if (std::strncmp(src_data_pointer, end_char_pointer, 1) == 0)
                    {
                        *dest_data_pointer = '\0';
                        return;
                    }
                    end_char_pointer++;
                }

                // OK, current character is not any of the ending characters.
                // Copy it and advance the pointers accordingly.
                strncpy(dest_data_pointer++, src_data_pointer++, 1);
            }

            *dest_data_pointer = '\0';
            return;
        }

        void extract_string_with_several_endings(
                const std::string& data_string,
                std::size_t& data_index,
                const char* const dest_base_pointer,
                char* dest_data_pointer,
                const std::size_t dest_data_size,
                const char* const char_end_string)
        {
            // This function copies characters from `src_data_pointer` until a character matches.

            while (data_index < data_string.size() &&
                    dest_data_pointer + 1 < dest_base_pointer + dest_data_size)
            {
                const char* end_char_pointer;
                end_char_pointer = char_end_string;
                const std::string current_char_string = data_string.substr(data_index, 1);

                // Check if current character is any of the ending characters.
                while (end_char_pointer != nullptr && *end_char_pointer != '\0')
                {
                    if (std::strncmp(current_char_string.c_str(), end_char_pointer, 1) == 0)
                    {
                        *dest_data_pointer = '\0';
                        return;
                    }
                    end_char_pointer++;
                }

                // OK, current character is not any of the ending characters.
                // Copy it and advance `dest_data_pointer` and `data_index` accordingly.
                strncpy(dest_data_pointer++, current_char_string.c_str(), 1);
                data_index++;
            }

            *dest_data_pointer = '\0';
            return;
        }

        void extract_string_with_several_endings(
                const std::string& data_string,
                std::size_t& data_index,
                std::string& dest_string,
                const char* const char_end_string)
        {
            // This function copies characters from `src_data_pointer` until a character matches.
            if (data_index >= data_string.size())
            {
                return;
            }

            std::size_t original_data_index = data_index;

            while (data_index < data_string.size())
            {
                const char* end_char_pointer;
                end_char_pointer = char_end_string;
                const std::string current_char_string = data_string.substr(data_index, 1);

                // Check if current character is any of the ending characters.
                while (end_char_pointer != nullptr && *end_char_pointer != '\0')
                {
                    if (std::strncmp(current_char_string.c_str(), end_char_pointer, 1) == 0)
                    {
                        dest_string = data_string.substr(original_data_index, data_index - original_data_index);
                        return;
                    }
                    end_char_pointer++;
                }

                // OK, current character is not any of the ending characters.
                data_index++;
            }

            dest_string = data_string.substr(original_data_index, data_index - original_data_index);
        }

        std::size_t extract_last_part_of_string(
                const char* const src_base_pointer,
                const std::size_t src_data_size,
                char* const dest_base_pointer,
                const std::size_t dest_data_size,
                const char separator)
        {
            char* src_data_pointer = const_cast<char*>(src_base_pointer);
            char* src_first_char_after_separator_pointer = nullptr;
            char* dest_data_pointer = dest_base_pointer;
            std::size_t filename_length = 0; // length without trailing null byte.

            // + 1 needed for both source and dest because of the null terminator.
            for ( ; src_data_pointer < src_base_pointer + src_data_size && dest_data_pointer + 1 < dest_base_pointer + dest_data_size; src_data_pointer++)
            {
                if (*src_data_pointer == static_cast<char>(separator))
                {
                    src_first_char_after_separator_pointer = src_data_pointer + 1;
                    filename_length = 0;
                }
                else if (src_first_char_after_separator_pointer != nullptr)
                {
                    // separator pointer found.
                    filename_length++;
                }
            }

            if (src_first_char_after_separator_pointer != nullptr)
            {
                std::copy(src_first_char_after_separator_pointer, src_first_char_after_separator_pointer + filename_length, dest_base_pointer);
            }

            dest_data_pointer += filename_length;
            *dest_data_pointer = '\0';
            return filename_length;
        }

        std::size_t extract_last_part_of_string(
                const std::string& data_string,
                std::string& dest_string,
                const char separator)
        {
            std::size_t filename_length = 0;
            auto separator_it = data_string.end(); // by default no last part.

            for (auto it = data_string.begin(); it != data_string.end(); it++)
            {
                if (*it == separator)
                {
                    separator_it = it;
                    filename_length = 0;
                }
                else
                {
                    filename_length++;
                }
            }

            if (separator_it == data_string.end())
            {
                dest_string = "";
                return 0;
            }

            separator_it++;
            dest_string = std::string(separator_it, data_string.end());
            return filename_length;
        }

        void extract_value_from_string(
                const char* const src_base_pointer,
                char*& src_data_pointer,
                const std::size_t src_data_size,
                const char* const char_end_string,
                const char* const description,
                int8_t& value)
        {
            value = yli::string::extract_int8_t_value_from_string(
                    src_base_pointer,
                    src_data_pointer,
                    src_data_size,
                    char_end_string,
                    description);
        }

        void extract_value_from_string(
                const std::string& data_string,
                std::size_t& data_index,
                const char* const char_end_string,
                const char* const description,
                int8_t& value)
        {
            value = yli::string::extract_int8_t_value_from_string(
                    data_string,
                    data_index,
                    char_end_string,
                    description);
        }

        void extract_value_from_string(
                const char* const src_base_pointer,
                char*& src_data_pointer,
                const std::size_t src_data_size,
                const char* const char_end_string,
                const char* const description,
                uint8_t& value)
        {
            value = yli::string::extract_uint8_t_value_from_string(
                    src_base_pointer,
                    src_data_pointer,
                    src_data_size,
                    char_end_string,
                    description);
        }

        void extract_value_from_string(
                const std::string& data_string,
                std::size_t& data_index,
                const char* const char_end_string,
                const char* const description,
                uint8_t& value)
        {
            value = yli::string::extract_uint8_t_value_from_string(
                    data_string,
                    data_index,
                    char_end_string,
                    description);
        }

        void extract_value_from_string(
                const char* const src_base_pointer,
                char*& src_data_pointer,
                const std::size_t src_data_size,
                const char* const char_end_string,
                const char* const description,
                int16_t& value)
        {
            value = yli::string::extract_int16_t_value_from_string(
                    src_base_pointer,
                    src_data_pointer,
                    src_data_size,
                    char_end_string,
                    description);
        }

        void extract_value_from_string(
                const std::string& data_string,
                std::size_t& data_index,
                const char* const char_end_string,
                const char* const description,
                int16_t& value)
        {
            value = yli::string::extract_int16_t_value_from_string(
                    data_string,
                    data_index,
                    char_end_string,
                    description);
        }

        void extract_value_from_string(
                const char* const src_base_pointer,
                char*& src_data_pointer,
                const std::size_t src_data_size,
                const char* const char_end_string,
                const char* const description,
                uint16_t& value)
        {
            value = yli::string::extract_uint16_t_value_from_string(
                    src_base_pointer,
                    src_data_pointer,
                    src_data_size,
                    char_end_string,
                    description);
        }

        void extract_value_from_string(
                const std::string& data_string,
                std::size_t& data_index,
                const char* const char_end_string,
                const char* const description,
                uint16_t& value)
        {
            value = yli::string::extract_uint16_t_value_from_string(
                    data_string,
                    data_index,
                    char_end_string,
                    description);
        }

        void extract_value_from_string(
                const char* const src_base_pointer,
                char*& src_data_pointer,
                const std::size_t src_data_size,
                const char* const char_end_string,
                const char* const description,
                int32_t& value)
        {
            value = yli::string::extract_int32_t_value_from_string(
                    src_base_pointer,
                    src_data_pointer,
                    src_data_size,
                    char_end_string,
                    description);
        }

        void extract_value_from_string(
                const std::string& data_string,
                std::size_t& data_index,
                const char* const char_end_string,
                const char* const description,
                int32_t& value)
        {
            value = yli::string::extract_int32_t_value_from_string(
                    data_string,
                    data_index,
                    char_end_string,
                    description);
        }

        void extract_value_from_string(
                const char* const src_base_pointer,
                char*& src_data_pointer,
                const std::size_t src_data_size,
                const char* const char_end_string,
                const char* const description,
                uint32_t& value)
        {
            value = yli::string::extract_uint32_t_value_from_string(
                    src_base_pointer,
                    src_data_pointer,
                    src_data_size,
                    char_end_string,
                    description);
        }

        void extract_value_from_string(
                const std::string& data_string,
                std::size_t& data_index,
                const char* const char_end_string,
                const char* const description,
                uint32_t& value)
        {
            value = yli::string::extract_uint32_t_value_from_string(
                    data_string,
                    data_index,
                    char_end_string,
                    description);
        }

        void extract_value_from_string(
                const char* const src_base_pointer,
                char*& src_data_pointer,
                const std::size_t src_data_size,
                const char* const char_end_string,
                const char* const description,
                float& value)
        {
            value = yli::string::extract_float_value_from_string(
                    src_base_pointer,
                    src_data_pointer,
                    src_data_size,
                    char_end_string,
                    description);
        }

        void extract_value_from_string(
                const std::string& data_string,
                std::size_t& data_index,
                const char* const char_end_string,
                const char* const description,
                float& value)
        {
            value = yli::string::extract_float_value_from_string(
                    data_string,
                    data_index,
                    char_end_string,
                    description);
        }

        int8_t extract_int8_t_value_from_string(
                const char* const src_base_pointer,
                char*& src_data_pointer,
                const std::size_t src_data_size,
                const char* const char_end_string,
                const char* const description)
        {
            char char_number_buffer[1024];
            yli::string::extract_string_with_several_endings(
                    src_base_pointer,
                    src_data_pointer,
                    src_data_size,
                    char_number_buffer,
                    char_number_buffer,
                    sizeof(char_number_buffer),
                    char_end_string);

            int32_t value = std::strtol(char_number_buffer, nullptr, 10); // base 10.
            int8_t int8_t_value = 0;

            if (value < std::numeric_limits<int8_t>::min())
            {
                std::cerr << "ERROR: `value` " << value << " is too small for `int8_t`! 0 returned.\n";
            }
            else if (value > std::numeric_limits<int8_t>::max())
            {
                std::cerr << "ERROR: `value` " << value << " is too big for `int8_t`! 0 returned.\n";
            }
            else
            {
                int8_t_value = static_cast<int8_t>(value);
            }

            if (description != nullptr)
            {
                std::cout << description << ": " << value << "\n";
            }
            return int8_t_value;
        }

        int8_t extract_int8_t_value_from_string(
                const std::string& data_string,
                std::size_t& data_index,
                const char* const char_end_string,
                const char* const description)
        {
            char char_number_buffer[1024];
            yli::string::extract_string_with_several_endings(
                    data_string,
                    data_index,
                    char_number_buffer,
                    char_number_buffer,
                    sizeof(char_number_buffer),
                    char_end_string);

            int32_t value = std::strtol(char_number_buffer, nullptr, 10); // base 10.
            int8_t int8_t_value = 0;

            if (value < std::numeric_limits<int8_t>::min())
            {
                std::cerr << "ERROR: `value` " << value << " is too small for `int8_t`! 0 returned.\n";
            }
            else if (value > std::numeric_limits<int8_t>::max())
            {
                std::cerr << "ERROR: `value` " << value << " is too big for `int8_t`! 0 returned.\n";
            }
            else
            {
                int8_t_value = static_cast<int8_t>(value);
            }

            if (description != nullptr)
            {
                std::cout << description << ": " << value << "\n";
            }
            return int8_t_value;
        }

        uint8_t extract_uint8_t_value_from_string(
                const char* const src_base_pointer,
                char*& src_data_pointer,
                const std::size_t src_data_size,
                const char* const char_end_string,
                const char* const description)
        {
            char char_number_buffer[1024];
            yli::string::extract_string_with_several_endings(
                    src_base_pointer,
                    src_data_pointer,
                    src_data_size,
                    char_number_buffer,
                    char_number_buffer,
                    sizeof(char_number_buffer),
                    char_end_string);

            uint32_t value = std::strtoul(char_number_buffer, nullptr, 10); // base 10.
            uint8_t uint8_t_value = 0;

            if (value > std::numeric_limits<uint8_t>::max())
            {
                std::cerr << "ERROR: `value` " << value << " is too big for `uint8_t`! 0 returned.\n";
            }
            else
            {
                uint8_t_value = static_cast<uint8_t>(value);
            }

            if (description != nullptr)
            {
                std::cout << description << ": " << value << "\n";
            }
            return uint8_t_value;
        }

        uint8_t extract_uint8_t_value_from_string(
                const std::string& data_string,
                std::size_t& data_index,
                const char* const char_end_string,
                const char* const description)
        {
            char char_number_buffer[1024];
            yli::string::extract_string_with_several_endings(
                    data_string,
                    data_index,
                    char_number_buffer,
                    char_number_buffer,
                    sizeof(char_number_buffer),
                    char_end_string);

            uint32_t value = std::strtoul(char_number_buffer, nullptr, 10); // base 10.
            uint8_t uint8_t_value = 0;

            if (value > std::numeric_limits<uint8_t>::max())
            {
                std::cerr << "ERROR: `value` " << value << " is too big for `uint8_t`! 0 returned.\n";
            }
            else
            {
                uint8_t_value = static_cast<uint8_t>(value);
            }

            if (description != nullptr)
            {
                std::cout << description << ": " << value << "\n";
            }
            return uint8_t_value;
        }

        int16_t extract_int16_t_value_from_string(
                const char* const src_base_pointer,
                char*& src_data_pointer,
                const std::size_t src_data_size,
                const char* const char_end_string,
                const char* const description)
        {
            char char_number_buffer[1024];
            yli::string::extract_string_with_several_endings(
                    src_base_pointer,
                    src_data_pointer,
                    src_data_size,
                    char_number_buffer,
                    char_number_buffer,
                    sizeof(char_number_buffer),
                    char_end_string);

            int32_t value = std::strtol(char_number_buffer, nullptr, 10); // base 10.
            int16_t int16_t_value = 0;

            if (value < std::numeric_limits<int16_t>::min())
            {
                std::cerr << "ERROR: `value` " << value << " is too small for `int16_t`! 0 returned.\n";
            }
            else if (value > std::numeric_limits<int16_t>::max())
            {
                std::cerr << "ERROR: `value` " << value << " is too big for `int16_t`! 0 returned.\n";
            }
            else
            {
                int16_t_value = static_cast<int16_t>(value);
            }

            if (description != nullptr)
            {
                std::cout << description << ": " << value << "\n";
            }
            return int16_t_value;
        }

        int16_t extract_int16_t_value_from_string(
                const std::string& data_string,
                std::size_t& data_index,
                const char* const char_end_string,
                const char* const description)
        {
            char char_number_buffer[1024];
            yli::string::extract_string_with_several_endings(
                    data_string,
                    data_index,
                    char_number_buffer,
                    char_number_buffer,
                    sizeof(char_number_buffer),
                    char_end_string);

            int32_t value = std::strtol(char_number_buffer, nullptr, 10); // base 10.
            int16_t int16_t_value = 0;

            if (value < std::numeric_limits<int16_t>::min())
            {
                std::cerr << "ERROR: `value` " << value << " is too small for `int16_t`! 0 returned.\n";
            }
            else if (value > std::numeric_limits<int16_t>::max())
            {
                std::cerr << "ERROR: `value` " << value << " is too big for `int16_t`! 0 returned.\n";
            }
            else
            {
                int16_t_value = static_cast<int16_t>(value);
            }

            if (description != nullptr)
            {
                std::cout << description << ": " << value << "\n";
            }
            return int16_t_value;
        }

        uint16_t extract_uint16_t_value_from_string(
                const char* const src_base_pointer,
                char*& src_data_pointer,
                const std::size_t src_data_size,
                const char* const char_end_string,
                const char* const description)
        {
            char char_number_buffer[1024];
            yli::string::extract_string_with_several_endings(
                    src_base_pointer,
                    src_data_pointer,
                    src_data_size,
                    char_number_buffer,
                    char_number_buffer,
                    sizeof(char_number_buffer),
                    char_end_string);

            uint32_t value = std::strtoul(char_number_buffer, nullptr, 10); // base 10.
            uint16_t uint16_t_value = 0;

            if (value > std::numeric_limits<uint16_t>::max())
            {
                std::cerr << "ERROR: `value` " << value << " is too big for `uint16_t`! 0 returned.\n";
            }
            else
            {
                uint16_t_value = static_cast<uint16_t>(value);
            }

            if (description != nullptr)
            {
                std::cout << description << ": " << value << "\n";
            }
            return uint16_t_value;
        }

        uint16_t extract_uint16_t_value_from_string(
                const std::string& data_string,
                std::size_t& data_index,
                const char* const char_end_string,
                const char* const description)
        {
            char char_number_buffer[1024];
            yli::string::extract_string_with_several_endings(
                    data_string,
                    data_index,
                    char_number_buffer,
                    char_number_buffer,
                    sizeof(char_number_buffer),
                    char_end_string);

            uint32_t value = std::strtoul(char_number_buffer, nullptr, 10); // base 10.
            uint16_t uint16_t_value = 0;

            if (value > std::numeric_limits<uint16_t>::max())
            {
                std::cerr << "ERROR: `value` " << value << " is too big for `uint16_t`! 0 returned.\n";
            }
            else
            {
                uint16_t_value = static_cast<uint16_t>(value);
            }

            if (description != nullptr)
            {
                std::cout << description << ": " << value << "\n";
            }
            return uint16_t_value;
        }

        int32_t extract_int32_t_value_from_string(
                const char* const src_base_pointer,
                char*& src_data_pointer,
                const std::size_t src_data_size,
                const char* const char_end_string,
                const char* const description)
        {
            char char_number_buffer[1024];
            yli::string::extract_string_with_several_endings(
                    src_base_pointer,
                    src_data_pointer,
                    src_data_size,
                    char_number_buffer,
                    char_number_buffer,
                    sizeof(char_number_buffer),
                    char_end_string);

            int32_t value = std::strtol(char_number_buffer, nullptr, 10); // base 10.

            if (description != nullptr)
            {
                std::cout << description << ": " << value << "\n";
            }
            return value;
        }

        int32_t extract_int32_t_value_from_string(
                const std::string& data_string,
                std::size_t& data_index,
                const char* const char_end_string,
                const char* const description)
        {
            char char_number_buffer[1024];
            yli::string::extract_string_with_several_endings(
                    data_string,
                    data_index,
                    char_number_buffer,
                    char_number_buffer,
                    sizeof(char_number_buffer),
                    char_end_string);

            int32_t value = std::strtol(char_number_buffer, nullptr, 10); // base 10.

            if (description != nullptr)
            {
                std::cout << description << ": " << value << "\n";
            }
            return value;
        }

        uint32_t extract_uint32_t_value_from_string(
                const char* const src_base_pointer,
                char*& src_data_pointer,
                const std::size_t src_data_size,
                const char* const char_end_string,
                const char* const description)
        {
            char char_number_buffer[1024];
            yli::string::extract_string_with_several_endings(
                    src_base_pointer,
                    src_data_pointer,
                    src_data_size,
                    char_number_buffer,
                    char_number_buffer,
                    sizeof(char_number_buffer),
                    char_end_string);

            uint32_t value = std::strtoul(char_number_buffer, nullptr, 10); // base 10.

            if (description != nullptr)
            {
                std::cout << description << ": " << value << "\n";
            }
            return value;
        }

        uint32_t extract_uint32_t_value_from_string(
                const std::string& data_string,
                std::size_t& data_index,
                const char* const char_end_string,
                const char* const description)
        {
            char char_number_buffer[1024];
            yli::string::extract_string_with_several_endings(
                    data_string,
                    data_index,
                    char_number_buffer,
                    char_number_buffer,
                    sizeof(char_number_buffer),
                    char_end_string);

            uint32_t value = std::strtoul(char_number_buffer, nullptr, 10); // base 10.

            if (description != nullptr)
            {
                std::cout << description << ": " << value << "\n";
            }
            return value;
        }

        float extract_float_value_from_string(
                const char* const src_base_pointer,
                char*& src_data_pointer,
                const std::size_t src_data_size,
                const char* const char_end_string,
                const char* const description)
        {
            char char_number_buffer[1024];
            yli::string::extract_string_with_several_endings(
                    src_base_pointer,
                    src_data_pointer,
                    src_data_size,
                    char_number_buffer,
                    char_number_buffer,
                    sizeof(char_number_buffer),
                    char_end_string);

            float value = std::strtof(char_number_buffer, nullptr);

            if (description != nullptr)
            {
                std::cout << description << ": " << value << "\n";
            }
            return value;
        }

        float extract_float_value_from_string(
                const std::string& data_string,
                std::size_t& data_index,
                const char* const char_end_string,
                const char* const description)
        {
            char char_number_buffer[1024];
            yli::string::extract_string_with_several_endings(
                    data_string,
                    data_index,
                    char_number_buffer,
                    char_number_buffer,
                    sizeof(char_number_buffer),
                    char_end_string);

            float value = std::strtof(char_number_buffer, nullptr);

            if (description != nullptr)
            {
                std::cout << description << ": " << value << "\n";
            }
            return value;
        }

        int32_t extract_unicode_value_from_string(const char*& unicode_char_pointer)
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
            std::string hex_string;

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

        std::string convert_std_list_char_to_std_string(const std::list<char>& std_list_char)
        {
            std::string my_string;

            for (std::list<char>::const_iterator it = std_list_char.begin(); it != std_list_char.end(); it++)
            {
                my_string.push_back(*it);
            }

            return my_string;
        }

        std::string convert_std_list_char_to_std_string(
                const std::list<char>& std_list_char,
                const std::size_t first_line_length,
                const std::size_t line_length)
        {
            std::string my_string;
            std::size_t remaining_characters_on_this_line = first_line_length;

            for (std::list<char>::const_iterator it = std_list_char.begin(); it != std_list_char.end(); it++)
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

        std::vector<std::string> convert_std_list_char_to_std_vector_std_string(
                const std::list<char>& std_list_char,
                const std::size_t line_length)
        {
            std::vector<std::string> my_vector;
            std::string my_string;
            std::size_t remaining_characters_on_this_line = line_length;

            for (std::list<char>::const_iterator it = std_list_char.begin(); it != std_list_char.end(); it++)
            {
                if (remaining_characters_on_this_line == 0)
                {
                    my_vector.push_back(my_string);
                    my_string.clear();
                    remaining_characters_on_this_line = line_length;
                }
                my_string.push_back(*it);
                remaining_characters_on_this_line--;
            }

            if (my_string.size() > 0)
            {
                my_vector.push_back(my_string);
            }

            return my_vector;
        }

        bool check_if_float_string(const std::string& my_string)
        {
            const std::size_t maximum_safe_length_for_float_string = 38;
            return check_if_floating_point_string(my_string, maximum_safe_length_for_float_string);
        }

        bool check_if_double_string(const std::string& my_string)
        {
            const std::size_t maximum_safe_length_for_double_string = 308;
            return check_if_floating_point_string(my_string, maximum_safe_length_for_double_string);
        }

        bool check_if_floating_point_string(const std::string& my_string, const std::size_t safe_number_of_chars)
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

        bool check_if_signed_integer_string(const std::string& my_string)
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

        bool check_if_unsigned_integer_string(const std::string& my_string)
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

        void print_hexdump(const void* const start_address, const void* const end_address) // `begin` is inclusive, `end` is exclusive.
        {
            void* void_start_address = const_cast<void*>(start_address);
            const std::size_t line_width_in_bytes = 16;
            std::size_t characters_on_this_line = 0;
            std::string current_line_ascii = "";
            std::string current_line_hex = "";

            for (uint8_t* data_pointer = static_cast<uint8_t*>(void_start_address); data_pointer < end_address; data_pointer++)
            {
                const uint8_t data_byte = static_cast<uint8_t>(*data_pointer);
                const char data_char = (data_byte >= 0x20 && data_byte <= 0x7f ? static_cast<char>(data_byte) : '.');
                current_line_ascii += data_char;

                uint32_t data_32_bit = static_cast<uint32_t>(data_byte); // to get the hexadecimal representation instead of the actual value.
                std::stringstream my_stream;
                my_stream << std::setfill('0') << std::setw(2) << std::hex << data_32_bit << std::dec; // std::hex does not work on char values.
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
                const std::size_t size_of_each_bytes_hexdump = 3; // each byte's hexdump takes 3 characters.
                const std::size_t number_of_spaces_needed = (line_width_in_bytes - characters_on_this_line) * size_of_each_bytes_hexdump + 1;
                std::cout << current_line_hex << std::string(number_of_spaces_needed, ' ') << current_line_ascii << "\n";
            }

            std::cout << "\n";
        }

        void print_hexdump(const std::string& my_string)
        {
            const std::size_t line_width_in_bytes = 16;
            std::size_t characters_on_this_line = 0;
            std::string current_line_ascii = "";
            std::string current_line_hex = "";

            for (auto it = my_string.begin(); it != my_string.end(); it++)
            {
                const uint8_t data_byte = static_cast<uint8_t>(*it);
                const char data_char = (data_byte >= 0x20 && data_byte <= 0x7f ? static_cast<char>(data_byte) : '.');
                current_line_ascii += data_char;

                uint32_t data_32_bit = static_cast<uint32_t>(data_byte); // to get the hexadecimal representation instead of the actual value.
                std::stringstream my_stream;
                my_stream << std::setfill('0') << std::setw(2) << std::hex << data_32_bit << std::dec; // std::hex does not work on char values.
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
                const std::size_t size_of_each_bytes_hexdump = 3; // each byte's hexdump takes 3 characters.
                const std::size_t number_of_spaces_needed = (line_width_in_bytes - characters_on_this_line) * size_of_each_bytes_hexdump + 1;
                std::cout << current_line_hex << std::string(number_of_spaces_needed, ' ') << current_line_ascii << "\n";
            }

            std::cout << "\n";
        }
    }
}
