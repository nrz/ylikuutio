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
        : original_scale_vector(glm::vec3(1.0f, 1.0f, 1.0f)),
        cartesian_coordinates(glm::vec3(NAN, NAN, NAN)),
        text_string_char(nullptr),
        parent(nullptr),
        rotate_angle(NAN)
    {
        // constructor.
    }

    glm::vec3 original_scale_vector;   // original scale vector.
    glm::vec3 cartesian_coordinates;   // coordinate vector.
    glm::vec3 rotate_vector;           // rotate vector.
    glm::vec3 translate_vector;        // translate vector.
    std::string text_string;
    const char* text_string_char;
    yli::ontology::VectorFont* parent; // pointer to the `VectorFont` (parent).
    float rotate_angle;                // rotate angle.
} Text3DStruct;

#endif
