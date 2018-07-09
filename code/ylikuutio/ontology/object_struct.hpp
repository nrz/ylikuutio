#ifndef __OBJECT_STRUCT_HPP_INCLUDED
#define __OBJECT_STRUCT_HPP_INCLUDED

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
        class Species;
        class Glyph;
        class Text3D;
    }
}

typedef struct ObjectStruct
{
    ObjectStruct()
        : species_parent(nullptr),
        glyph_parent(nullptr),
        text3D_parent(nullptr),
        original_scale_vector(glm::vec3(1.0f, 1.0f, 1.0f)),
        rotate_angle(0.0f),
        initial_rotate_angle(PI),
        is_character(false),
        is_symbiosis_object(false),
        quaternions_in_use(false),
        cartesian_coordinates(glm::vec3(NAN, NAN, NAN)),
        rotate_vector(glm::vec3(0.0f, 0.0f, 0.0f)),
        initial_rotate_vector(glm::vec3(0.0f, 1.0f, 1.0f)),
        translate_vector(glm::vec3(0.0f, 0.0f, 0.0f))
    {
        // constructor.
    }
    yli::ontology::Species* species_parent;     // pointer to the parent `Species`.
    yli::ontology::Glyph* glyph_parent;     // pointer to the parent `Glyph`.
    yli::ontology::Text3D* text3D_parent;   // pointer to the parent `Text3D`.
    glm::vec3 original_scale_vector; // original scale vector.
    float rotate_angle;              // rotate angle.
    float initial_rotate_angle;      // initial rotate angle.
    bool is_character;               // The parent of a character object is a `Glyph`. The parent of a regular object is a `Species`.
    bool is_symbiosis_object;        // The parent of a `SymbiosisObject` is a `Symbiosis`.
    bool quaternions_in_use;
    glm::vec3 cartesian_coordinates; // coordinate vector.
    glm::vec3 rotate_vector;         // rotate vector.
    glm::vec3 initial_rotate_vector; // initial rotate vector.
    glm::vec3 translate_vector;      // translate vector.
} ObjectStruct;

#endif
