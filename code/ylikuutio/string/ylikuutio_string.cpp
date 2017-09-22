#include "ylikuutio_string.hpp"

// Include standard headers
#include <cstdio>   // std::FILE, std::fclose, std::fopen, std::fread, std::getchar, std::printf etc.
#include <cstring>  // std::memcmp, std::strcmp, std::strlen, std::strncmp
#include <iostream> // std::cout, std::cin, std::cerr
#include <list>     // std::list
#include <stdint.h> // uint32_t etc.
#include <sstream>  // std::istringstream, std::ostringstream, std::stringstream
#include <string>   // std::string
#include <vector>   // std::vector

namespace string
{
    bool check_and_report_if_some_string_matches(
            const char* const base_pointer,
            const char* const data_pointer,
            const std::vector<std::string> identifier_strings_vector)
    {
        for (std::string identifier_string : identifier_strings_vector)
        {
            const char* const identifier_string_char = identifier_string.c_str();

            if (std::strncmp(data_pointer, identifier_string_char, std::strlen(identifier_string_char)) == 0)
            {
                const char* const identifier_string_char = identifier_string.c_str();
                return true;
            }
        }
        return false;
    }

    void extract_string(
            char* dest_mem_pointer,
            char*& src_mem_pointer,
            const char* const char_end_string)
    {
        while (std::strncmp(src_mem_pointer, char_end_string, std::strlen(char_end_string)) != 0)
        {
            strncpy(dest_mem_pointer++, src_mem_pointer++, 1);
        }
        *dest_mem_pointer = '\0';
    }

    void extract_string_with_several_endings(
            char* dest_mem_pointer,
            char*& src_mem_pointer,
            const char* const char_end_string)
    {
        // This function copies characters from `src_mem_pointer` until a character matches.

        while (true)
        {
            uint32_t n_of_ending_characters = std::strlen(char_end_string);
            const char* end_char_pointer;
            end_char_pointer = char_end_string;

            // Check if current character is any of the ending characters.
            while (*end_char_pointer != '\0')
            {
                if (std::strncmp(src_mem_pointer, end_char_pointer, 1) == 0)
                {
                    *dest_mem_pointer = '\0';
                    return;
                }
                end_char_pointer++;
            }

            // OK, current character is not any of the ending characters.
            // Copy it and advance the pointers accordingly.
            strncpy(dest_mem_pointer++, src_mem_pointer++, 1);
        }
    }

    int32_t extract_int32_t_value_from_string(
            char*& data_pointer,
            char* char_end_string,
            const char* const description)
    {
        char char_number_buffer[1024]; // FIXME: risk of buffer overflow.
        char* dest_mem_pointer;
        dest_mem_pointer = char_number_buffer;
        string::extract_string_with_several_endings(dest_mem_pointer, ++data_pointer, char_end_string);
        uint32_t value = std::atoi(dest_mem_pointer);
        if (description != nullptr)
        {
            std::printf("%s: %d\n", description, value);
        }
        return value;
    }

    float extract_float_value_from_string(
            char*& data_pointer,
            char* char_end_string,
            const char* const description)
    {
        char char_number_buffer[1024]; // FIXME: risk of buffer overflow.
        char* dest_mem_pointer;
        dest_mem_pointer = char_number_buffer;
        string::extract_string_with_several_endings(dest_mem_pointer, ++data_pointer, char_end_string);
        float value = std::atof(dest_mem_pointer);

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

    bool check_if_float_string(const std::string& my_string)
    {
        if (my_string.empty())
        {
            return false;
        }

        bool is_dot_found = false;

        for (int32_t i = 0; i < my_string.length(); i++)
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

                if (i == my_string.length() - 1)
                {
                    // Last character is dot.
                    return false;
                }

                // OK, decimal point here.
                is_dot_found = true;
            }

            else if (my_string.at(i) < '0' || my_string.at(i) > '9')
            {
                return false;
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

        for (int32_t i = 0; i < my_string.length(); i++)
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

        for (int32_t i = 0; i < my_string.length(); i++)
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
}
