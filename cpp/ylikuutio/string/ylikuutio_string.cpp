#include "ylikuutio_string.hpp"

// Include standard headers
#include <cstdio>   // std::FILE, std::fclose, std::fopen, std::fread, std::getchar, std::printf etc.
#include <cstring>  // std::memcmp, std::strcmp, std::strlen, std::strncmp
#include <iostream> // std::cout, std::cin, std::cerr
#include <sstream>  // std::stringstream
#include <string>   // std::string
#include <vector>   // std::vector

namespace string
{
    bool check_and_report_if_some_string_matches(const char* SVG_base_pointer, char* SVG_data_pointer, std::vector<std::string> identifier_strings_vector)
    {
        for (std::string identifier_string : identifier_strings_vector)
        {
            const char* identifier_string_char = identifier_string.c_str();

            if (std::strncmp(SVG_data_pointer, identifier_string_char, std::strlen(identifier_string_char)) == 0)
            {
                const char* identifier_string_char = identifier_string.c_str();
                uint64_t offset = (uint64_t) SVG_data_pointer - (uint64_t) SVG_base_pointer;
                std::printf("%s found at file offset 0x%lx (memory address 0x%lx).\n", identifier_string_char, offset, (uint64_t) SVG_data_pointer);
                return true;
            }
        }
        return false;
    }

    void extract_string_with_several_endings(char* dest_mem_pointer, char*& src_mem_pointer, char* char_end_string)
    {
        // This function copies characters from `src_mem_pointer` until a character matches.

        while (true)
        {
            uint32_t n_of_ending_characters = std::strlen(char_end_string);
            char* end_char_pointer;
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

    int32_t extract_value_from_string(char*& vertex_data_pointer, char* char_end_string, const char* description)
    {
        char char_number_buffer[1024]; // FIXME: risk of buffer overflow.
        char* dest_mem_pointer;
        dest_mem_pointer = char_number_buffer;
        string::extract_string_with_several_endings(dest_mem_pointer, ++vertex_data_pointer, char_end_string);
        uint32_t value = std::atoi(dest_mem_pointer);
        std::printf("%s: %d\n", description, value);
        return value;
    }

    int32_t extract_unicode_value_from_string(char*& unicode_string_pointer)
    {
        if (*unicode_string_pointer == '\0')
        {
            unicode_string_pointer++;
            std::cerr << "Error: Unicode can not begin with \\0!\n";
            return 0xdfff; // invalid unicode!
        }

        if (*unicode_string_pointer != '&')
        {
            // it's just a character, so return its value,
            // and advance to the next character.
            return (int32_t) *unicode_string_pointer++;
        }

        if (*++unicode_string_pointer != '#')
        {
            // not valid format, must begin `"&#x"`.
            unicode_string_pointer++;
            std::cerr << "Error: Unicode string format not supported!\n";
            return 0xdfff; // invalid unicode!
        }

        if (*++unicode_string_pointer != 'x')
        {
            // not valid format, must begin `"&#x"`.
            unicode_string_pointer++;
            std::cerr << "Error: Unicode string format not supported!\n";
            return 0xdfff; // invalid unicode!
        }

        // valid format.
        std::string hex_string;

        // unicode string beginning with '&'
        while (*++unicode_string_pointer != ';')
        {
            if (*unicode_string_pointer == '\0')
            {
                std::cerr << "Error: Null character \\0 reached before end of Unicode string!\n";
                return 0xdfff; // invalid unicode!
            }

            char current_char = *unicode_string_pointer;
            hex_string.append(unicode_string_pointer);
        }

        // Advance to the next character.
        unicode_string_pointer++;

        // convert hexadecimal string to signed integer.
        // http://stackoverflow.com/questions/1070497/c-convert-hex-string-to-signed-integer/1070499#1070499
        uint32_t unicode_value;
        std::stringstream unicode_stringstream;
        unicode_stringstream << std::hex << hex_string;
        unicode_stringstream >> unicode_value;
        return unicode_value;
    }
}
