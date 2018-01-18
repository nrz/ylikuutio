#ifndef __SYMBIONT_SPECIES_STRUCT_HPP_INCLUDED
#define __SYMBIONT_SPECIES_STRUCT_HPP_INCLUDED

#include <ofbx.h>

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <limits>   // std::numeric_limits
#include <string>   // std::string

namespace ontology
{
    class Universe;
    class Shader;
    class SymbiontMaterial;
}

typedef struct SymbiontSpeciesStruct
{
    SymbiontSpeciesStruct(
            ontology::Universe* const universe,
            ontology::Shader* const shader,
            ontology::SymbiontMaterial* const parent,
            int32_t vertex_count,
            const ofbx::Vec3* vertices,
            const ofbx::Vec2* uvs,
            const ofbx::Vec3* normals,
            glm::vec3 light_position)
        : universe(nullptr), shader(nullptr), parent(nullptr), light_position(glm::vec3(0.0f, 0.0f, 0.0f))
    {
        // constructor.
    }
    // used for all files (for all species).
    ontology::Universe* universe;       // pointer to the `Scene` object.
    ontology::Shader* shader;           // pointer to the `Shader` object.
    ontology::SymbiontMaterial* parent; // pointer to `SymbiontMaterial` object.
    int32_t vertex_count;
    const ofbx::Vec3* vertices;
    const ofbx::Vec2* uvs;
    const ofbx::Vec3* normals;
    glm::vec3 light_position;                   // light position.
} SymbiontSpeciesStruct;

#endif
