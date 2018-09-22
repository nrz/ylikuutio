#ifndef __GROUND_LEVEL_HPP_INCLUDED
#define __GROUND_LEVEL_HPP_INCLUDED

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

namespace yli
{
    namespace ontology
    {
        class Species;

        float get_ground_level(const yli::ontology::Species* const terrain_species, const glm::vec3& position);
        float get_floor_level(const yli::ontology::Species* const terrain_species, const glm::vec3& position);
    }
}

#endif
