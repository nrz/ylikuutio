#ifndef __INFO_STRUCT_HPP_INCLUDED
#define __INFO_STRUCT_HPP_INCLUDED

#include "code/ylikuutio/common/any_value.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

namespace ontology
{
    class Scene;
}

typedef struct InfoStruct
{
    InfoStruct()
        : memory_address(nullptr), childID(-1), name(""), coordinate_vector(glm::vec3(NAN, NAN, NAN))
    {
        // constructor.
    }
    datatypes::AnyValue* memory_address;
    uint32_t childID;
    std::string name;
    glm::vec3 coordinate_vector;
} InfoStruct;

#endif
