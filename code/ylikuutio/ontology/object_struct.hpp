#ifndef __OBJECT_STRUCT_HPP_INCLUDED
#define __OBJECT_STRUCT_HPP_INCLUDED

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

namespace ontology
{
    class Species;
    class Glyph;
    class Text3D;
}

typedef struct ObjectStruct
{
    ObjectStruct()
        : universe(nullptr), species_parent(nullptr), glyph_parent(nullptr), text3D_parent(nullptr), original_scale_vector(glm::vec3(1.0f, 1.0f, 1.0f)), rotate_angle(0.0f), is_character(false), quaternions_in_use(false), coordinate_vector(glm::vec3(0.0f, 0.0f, 0.0f)), rotate_vector(glm::vec3(0.0f, 0.0f, 0.0f)), translate_vector(glm::vec3(0.0f, 0.0f, 0.0f))
    {
        // constructor.
    }
    ontology::Universe* universe;      // pointer to the `Universe`.
    ontology::Species* species_parent; // pointer to the parent `Species`.
    ontology::Glyph* glyph_parent;     // pointer to the parent `Glyph`.
    ontology::Text3D* text3D_parent;   // pointer to the parent `Text3D`.
    glm::vec3 original_scale_vector; // original scale vector.
    float rotate_angle;              // rotate angle.
    bool is_character;               // The parent of a character object is a Glyph. The parent of a regular object is a Species.
    bool quaternions_in_use;
    glm::vec3 coordinate_vector;     // coordinate vector.
    glm::vec3 rotate_vector;         // rotate vector.
    glm::vec3 translate_vector;      // translate vector.
} ObjectStruct;

#endif
