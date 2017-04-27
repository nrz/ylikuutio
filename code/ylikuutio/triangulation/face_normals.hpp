#ifndef __FACE_NORMALS_HPP_INCLUDED
#define __FACE_NORMALS_HPP_INCLUDED

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

#include "triangulation_enums.hpp"

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
            uint32_t x_step,
            uint32_t z_step,
            bool is_bilinear_interpolation_in_use,
            bool is_southwest_northeast_edges_in_use,
            bool is_southeast_northwest_edges_in_use);

    glm::vec3 get_face_normal(
            std::vector<glm::vec3>& face_normal_data,
            uint32_t x,
            uint32_t z,
            BilinearDirections compass_point_code,
            uint32_t image_width);

    // for bilinear interpolation.
    // These functions exist to avoid need to remember
    // the array order when calling `geometry::get_face_normal`.
    glm::vec3 s_face_normal(std::vector<glm::vec3>& face_normal_vector_vec3, uint32_t x, uint32_t z, uint32_t image_width);
    glm::vec3 w_face_normal(std::vector<glm::vec3>& face_normal_vector_vec3, uint32_t x, uint32_t z, uint32_t image_width);
    glm::vec3 n_face_normal(std::vector<glm::vec3>& face_normal_vector_vec3, uint32_t x, uint32_t z, uint32_t image_width);
    glm::vec3 e_face_normal(std::vector<glm::vec3>& face_normal_vector_vec3, uint32_t x, uint32_t z, uint32_t image_width);

    // for southeast-northwest edges.
    glm::vec3 get_face_normal_for_SE_NW(
            std::vector<glm::vec3>& face_normal_data,
            uint32_t x,
            uint32_t z,
            SoutheastNorthwestEdgesDirections compass_point_code,
            uint32_t image_width);

    // for southwest-northeast edges.
    glm::vec3 get_face_normal_for_SW_NE(
            std::vector<glm::vec3>& face_normal_data,
            uint32_t x,
            uint32_t z,
            SouthwestNortheastEdgesDirections compass_point_code,
            uint32_t image_width);
}

#endif
