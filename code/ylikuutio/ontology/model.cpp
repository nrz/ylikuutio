#include "model.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace ontology
{
    class Universe;

    Model::~Model()
    {
        // destructor.
    }

    int32_t Model::get_number_of_children() const
    {
        return this->number_of_objects;
    }

    int32_t Model::get_number_of_descendants() const
    {
        return -1;
    }

    std::vector<glm::vec3> Model::get_vertices() const
    {
        return this->vertices;
    }
}
