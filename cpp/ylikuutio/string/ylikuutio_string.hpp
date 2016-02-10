#ifndef __YLIKUUTIO_STRING_HPP_INCLUDED
#define __YLIKUUTIO_STRING_HPP_INCLUDED

// Include standard headers
#include <string>    // std::string
#include <vector>    // std::vector

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

namespace string
{
    bool check_and_report_if_some_string_matches(const char* SVG_base_pointer, char* SVG_data_pointer, std::vector<std::string> identifier_strings_vector);
}

#endif
