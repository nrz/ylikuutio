#include "ylikuutio_string.hpp"

// Include standard headers
#include <iostream>  // std::cout, std::cin, std::cerr
#include <string>    // std::string
#include <vector>    // std::vector
#include <string.h>  // strcmp, strlen

namespace string
{
    bool check_and_report_if_some_string_matches(const char* SVG_base_pointer, char* SVG_data_pointer, std::vector<std::string> identifier_strings_vector)
    {
        for (std::string identifier_string : identifier_strings_vector)
        {
            const char* identifier_string_char = identifier_string.c_str();

            if (strncmp(SVG_data_pointer, identifier_string_char, strlen(identifier_string_char)) == 0)
            {
                const char* identifier_string_char = identifier_string.c_str();
                uint64_t offset = (uint64_t) SVG_data_pointer - (uint64_t) SVG_base_pointer;
                printf("%s found at file offset 0x%lx (memory address 0x%lx). ", identifier_string_char, offset, (uint64_t) SVG_data_pointer);
                return true;
            }
        }
        return false;
    }
}
