#include "ylikuutio_string.hpp"

// Include standard headers
#include <cstdio>   // std::FILE, std::fclose, std::fopen, std::fread, std::getchar, std::printf etc.
#include <cstring>  // std::memcmp, std::strcmp, std::strlen, std::strncmp
#include <iostream> // std::cout, std::cin, std::cerr
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
}
