#ifndef __TEXT3D_STRUCT_HPP_INCLUDED
#define __TEXT3D_STRUCT_HPP_INCLUDED

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <string>   // std::string

namespace yli
{
    namespace ontology
    {
        class VectorFont;
    }
}

typedef struct Text3DStruct
{
    Text3DStruct()
        : parent(nullptr),
        text_string_char(nullptr),
        original_scale_vector(glm::vec3(1.0f, 1.0f, 1.0f)),
        rotate_angle(NAN),
        cartesian_coordinates(glm::vec3(NAN, NAN, NAN))
    {
        // constructor.
    }
    yli::ontology::VectorFont* parent; // pointer to the parent `VectorFont`.
    std::string text_string;
    const char* text_string_char;
    glm::vec3 original_scale_vector;      // original scale vector.
    float rotate_angle;                   // rotate angle.
    glm::vec3 cartesian_coordinates;      // coordinate vector.
    glm::vec3 rotate_vector;              // rotate vector.
    glm::vec3 translate_vector;           // translate vector.
} Text3DStruct;

#endif
