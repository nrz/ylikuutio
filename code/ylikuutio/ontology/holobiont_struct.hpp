#ifndef __HOLOBIONT_STRUCT_HPP_INCLUDED
#define __HOLOBIONT_STRUCT_HPP_INCLUDED

#ifndef PI
#define PI 3.14159265359f
#endif

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath> // NAN, std::isnan, std::pow

namespace yli
{
    namespace ontology
    {
        class Symbiosis;
    }
}

typedef struct HolobiontStruct
{
    HolobiontStruct()
        : original_scale_vector(glm::vec3(1.0f, 1.0f, 1.0f)),
        cartesian_coordinates(glm::vec3(NAN, NAN, NAN)),
        rotate_vector(glm::vec3(0.0f, 0.0f, 0.0f)),
        initial_rotate_vector(glm::vec3(0.0f, 1.0f, 1.0f)),
        translate_vector(glm::vec3(0.0f, 0.0f, 0.0f)),
        symbiosis_parent(nullptr),
        rotate_angle(0.0f),
        initial_rotate_angle(PI),
        quaternions_in_use(false)
    {
        // constructor.
    }

    glm::vec3 original_scale_vector; // original scale vector.
    glm::vec3 cartesian_coordinates; // coordinate vector.
    glm::vec3 rotate_vector;         // rotate vector.
    glm::vec3 initial_rotate_vector; // initial rotate vector.
    glm::vec3 translate_vector;      // translate vector.
    yli::ontology::Symbiosis* symbiosis_parent; // pointer to the parent `Symbiosis`.
    float rotate_angle;              // rotate angle.
    float initial_rotate_angle;      // initial rotate angle.
    bool quaternions_in_use;
} HolobiontStruct;

#endif
