#ifndef __QUAD_TRIANGULATION_HPP_INCLUDED
#define __QUAD_TRIANGULATION_HPP_INCLUDED

#include "code/ylikuutio/common/globals.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace geometry
{
    bool triangulate_quads(
            uint32_t* input_vertex_pointer,
            TriangulateQuadsStruct triangulate_quads_struct,
            std::vector<glm::vec3>& out_vertices,
            std::vector<glm::vec2>& out_UVs,
            std::vector<glm::vec3>& out_normals);
}

#endif
