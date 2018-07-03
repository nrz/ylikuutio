#include "ylikuutio_string.hpp"

// Include standard headers
#include <algorithm> // std::copy
#include <cstddef>  // std::size_t
#include <cstdio>   // std::FILE, std::fclose, std::fopen, std::fread, std::getchar, std::printf etc.
#include <cstring>  // std::memcmp, std::memcpy, std::strcmp, std::strlen, std::strncmp
#include <iomanip>  // std::setfill, std::setw
#include <iostream> // std::cout, std::cin, std::cerr
#include <list>     // std::list
#include <stdint.h> // uint32_t etc.
#include <sstream>  // std::istringstream, std::ostringstream, std::stringstream
#include <string>   // std::string
#include <vector>   // std::vector

namespace ylikuutio
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
                uint32_t n_of_ending_characters = std::strlen(char_end_string);
                const char* end_char_pointer;
                end_char_pointer = char_end_string;

                // Check if current character is any of the ending characters.
                while (*end_char_pointer != '\0')
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
                uint32_t n_of_ending_characters = std::strlen(char_end_string);
                const char* end_char_pointer;
                end_char_pointer = char_end_string;
                const std::string current_char_string = data_string.substr(data_index, 1);

                // Check if current character is any of the ending characters.
                while (*end_char_pointer != '\0')
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
            std::size_t original_data_index = data_index;

            while (data_index < data_string.size())
            {
                uint32_t n_of_ending_characters = std::strlen(char_end_string);
                const char* end_char_pointer;
                end_char_pointer = char_end_string;
                const std::string current_char_string = data_string.substr(data_index, 1);

                // Check if current character is any of the ending characters.
                while (*end_char_pointer != '\0')
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

        int32_t extract_last_part_of_string(
                const char* const src_base_pointer,
                const std::size_t src_data_size,
                char* const dest_base_pointer,
                const std::size_t dest_data_size,
                const char separator)
        {
            char* src_data_pointer = const_cast<char*>(src_base_pointer);
            char* src_first_char_after_separator_pointer = nullptr;
            char* dest_data_pointer = dest_base_pointer;
            int32_t filename_length = 0; // length without trailing 0 byte.

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

            std::copy(src_first_char_after_separator_pointer, src_first_char_after_separator_pointer + filename_length, dest_base_pointer);
            dest_data_pointer += filename_length;
            *dest_data_pointer = '\0';
            return filename_length;
        }

        int32_t extract_int32_t_value_from_string(
                const char* const src_base_pointer,
                char*& src_data_pointer,
                const std::size_t src_data_size,
                const char* const char_end_string,
                const char* const description)
        {
            char char_number_buffer[1024];
            ylikuutio::string::extract_string_with_several_endings(
                    src_base_pointer,
                    ++src_data_pointer,
                    src_data_size,
                    char_number_buffer,
                    char_number_buffer,
                    sizeof(char_number_buffer),
                    char_end_string);

            int32_t value = std::strtol(char_number_buffer, nullptr, 10); // base 10.

            if (description != nullptr)
            {
                std::printf("%s: %d\n", description, value);
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
            ylikuutio::string::extract_string_with_several_endings(
                    data_string,
                    ++data_index,
                    char_number_buffer,
                    char_number_buffer,
                    sizeof(char_number_buffer),
                    char_end_string);

            int32_t value = std::strtol(char_number_buffer, nullptr, 10); // base 10.

            if (description != nullptr)
            {
                std::printf("%s: %d\n", description, value);
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
            ylikuutio::string::extract_string_with_several_endings(
                    src_base_pointer,
                    ++src_data_pointer,
                    src_data_size,
                    char_number_buffer,
                    char_number_buffer,
                    sizeof(char_number_buffer),
                    char_end_string);

            float value = std::strtof(char_number_buffer, nullptr);

            if (description != nullptr)
            {
                std::printf("%s: %f\n", description, value);
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
            ylikuutio::string::extract_string_with_several_endings(
                    data_string,
                    ++data_index,
                    char_number_buffer,
                    char_number_buffer,
                    sizeof(char_number_buffer),
                    char_end_string);

            float value = std::strtof(char_number_buffer, nullptr);

            if (description != nullptr)
            {
                std::printf("%s: %f\n", description, value);
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

                char current_char = *unicode_char_pointer;
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
                const uint32_t first_line_length,
                const uint32_t line_length)
        {
            std::string my_string;
            uint32_t remaining_characters_on_this_line = first_line_length;

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
                const uint32_t line_length)
        {
            std::vector<std::string> my_vector;
            std::string my_string;
            uint32_t remaining_characters_on_this_line = line_length;

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
            int32_t maximum_safe_length_for_float_string = 38;
            return check_if_floating_point_string(my_string, maximum_safe_length_for_float_string);
        }

        bool check_if_double_string(const std::string& my_string)
        {
            int32_t maximum_safe_length_for_double_string = 308;
            return check_if_floating_point_string(my_string, maximum_safe_length_for_double_string);
        }

        bool check_if_floating_point_string(const std::string& my_string, const int32_t safe_number_of_chars)
        {
            int32_t n_chars = 0;

            if (my_string.empty())
            {
                return false;
            }

            bool is_dot_found = false;

            for (int32_t i = 0; i < my_string.size(); i++)
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

            for (int32_t i = 0; i < my_string.size(); i++)
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

            for (int32_t i = 0; i < my_string.size(); i++)
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
            const int32_t line_width_in_bytes = 16;
            int32_t characters_on_this_line = 0;
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
                const int32_t size_of_each_bytes_hexdump = 3; // each byte's hexdump takes 3 characters.
                const int32_t number_of_spaces_needed = (line_width_in_bytes - characters_on_this_line) * size_of_each_bytes_hexdump + 1;
                std::cout << current_line_hex << std::string(number_of_spaces_needed, ' ') << current_line_ascii << "\n";
            }

            std::cout << "\n";
        }

        void print_hexdump(const std::string& my_string)
        {
            const int32_t line_width_in_bytes = 16;
            int32_t characters_on_this_line = 0;
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
                const int32_t size_of_each_bytes_hexdump = 3; // each byte's hexdump takes 3 characters.
                const int32_t number_of_spaces_needed = (line_width_in_bytes - characters_on_this_line) * size_of_each_bytes_hexdump + 1;
                std::cout << current_line_hex << std::string(number_of_spaces_needed, ' ') << current_line_ascii << "\n";
            }

            std::cout << "\n";
        }
    }
}
