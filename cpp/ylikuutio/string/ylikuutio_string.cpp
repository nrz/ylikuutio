#include "ylikuutio_string.hpp"

// Include standard headers
#include <cstdio>   // std::FILE, std::fclose, std::fopen, std::fread, std::getchar, std::printf etc.
#include <iostream> // std::cout, std::cin, std::cerr
#include <string>   // std::string
#include <cstring> // std::memcmp, std::strcmp, std::strlen
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
}
