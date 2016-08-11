#ifndef __FACE_NORMALS_HPP_INCLUDED
#define __FACE_NORMALS_HPP_INCLUDED

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
    bool compute_face_normals(
            std::vector<glm::vec3>& temp_vertices,
            std::vector<glm::vec3>& face_normal_vector_vec3,
            uint32_t image_width,
            uint32_t image_height,
            bool is_bilinear_interpolation_in_use,
            bool is_southwest_northeast_edges_in_use,
            bool is_southeast_northwest_edges_in_use);
}

#endif
