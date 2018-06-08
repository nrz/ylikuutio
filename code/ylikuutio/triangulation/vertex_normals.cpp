#include "vertex_normals.hpp"
#include "face_normals.hpp"
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
    bool compute_vertex_normals(
            std::vector<glm::vec3>& temp_normals,
            std::vector<glm::vec3>& face_normal_vector_vec3,
            const int32_t actual_image_width,
            const int32_t actual_image_height,
            const bool is_bilinear_interpolation_in_use,
            const bool is_southwest_northeast_edges_in_use,
            const bool is_southeast_northwest_edges_in_use)
    {
        // 5. Compute the vertex normals for vertices loaded from file, `push_back` to `temp_normals`.

        if (actual_image_width < 2 || actual_image_height < 2)
        {
            // If width or height is < 2, there are no faces.
            return false;
        }

        if ((is_bilinear_interpolation_in_use && is_southwest_northeast_edges_in_use) ||
                (is_bilinear_interpolation_in_use && is_southeast_northwest_edges_in_use) ||
                (is_southwest_northeast_edges_in_use && is_southeast_northwest_edges_in_use) ||
                (!is_bilinear_interpolation_in_use && !is_southwest_northeast_edges_in_use && !is_southeast_northwest_edges_in_use))
        {
            // Exactly 1 triangulation method must be selected.
            return false;
        }

        if (is_bilinear_interpolation_in_use)
        {
            if (face_normal_vector_vec3.size() != 4 * (actual_image_width - 1) * (actual_image_height - 1))
            {
                // If number of face normals is not 4 * width * height, then the number of vertices is incorrect.
                return false;
            }

            // If bilinear interpolation is in use, then number of faces is:
            const int32_t number_of_interpolated_vertices = (actual_image_width - 1) * (actual_image_height - 1);
            temp_normals.reserve(actual_image_width * actual_image_height + number_of_interpolated_vertices);
        }
        else
        {
            if (face_normal_vector_vec3.size() != 2 * (actual_image_width - 1) * (actual_image_height - 1))
            {
                // If number of face normals is not 2 * width * height, then the number of vertices is incorrect.
                return false;
            }

            temp_normals.reserve(actual_image_width * actual_image_height);
        }

        if (is_bilinear_interpolation_in_use)
        {
            int32_t current_interpolated_vertex_i = actual_image_width * actual_image_height;
            int32_t x = 0;
            int32_t z = 0;

            // Compute the normal of the southwesternmost vertex.
            // Number of adjacent faces: 2.
            temp_normals.push_back(glm::normalize(
                        get_face_normal(face_normal_vector_vec3, x, z, NNE, actual_image_width) +
                        get_face_normal(face_normal_vector_vec3, x, z, ENE, actual_image_width)));

            // Compute the normals of southern vertices.
            for (x = 1; x < actual_image_width - 1; x++)
            {
                // Compute the normal of a southern vertex.
                // Number of adjacent faces: 4.
                temp_normals.push_back(glm::normalize(
                            get_face_normal(face_normal_vector_vec3, x, z, WNW, actual_image_width) +
                            get_face_normal(face_normal_vector_vec3, x, z, NNW, actual_image_width) +
                            get_face_normal(face_normal_vector_vec3, x, z, NNE, actual_image_width) +
                            get_face_normal(face_normal_vector_vec3, x, z, ENE, actual_image_width)));
            }

            // Compute the normal of the southeasternmost vertex.
            // Number of adjacent faces: 2.
            x = actual_image_width - 1;
            temp_normals.push_back(glm::normalize(
                        get_face_normal(face_normal_vector_vec3, x, z, WNW, actual_image_width) +
                        get_face_normal(face_normal_vector_vec3, x, z, NNW, actual_image_width)));

            // Then, define most normals in a double loop.
            for (z = 1; z < actual_image_height - 1; z++)
            {
                // Compute the normal of a western vertex.
                // Number of adjacent faces: 4.
                x = 0;
                temp_normals.push_back(glm::normalize(
                            get_face_normal(face_normal_vector_vec3, x, z, NNE, actual_image_width) +
                            get_face_normal(face_normal_vector_vec3, x, z, ENE, actual_image_width) +
                            get_face_normal(face_normal_vector_vec3, x, z, ESE, actual_image_width) +
                            get_face_normal(face_normal_vector_vec3, x, z, SSE, actual_image_width)));

                for (x = 1; x < actual_image_width - 1; x++)
                {
                    int32_t current_vertex_i = actual_image_width * z + x;

                    // Compute the normal of a central vertex.
                    // Number of adjacent faces: 8.
                    temp_normals.push_back(glm::normalize(
                                get_face_normal(face_normal_vector_vec3, x, z, SSW, actual_image_width) +
                                get_face_normal(face_normal_vector_vec3, x, z, WSW, actual_image_width) +
                                get_face_normal(face_normal_vector_vec3, x, z, WNW, actual_image_width) +
                                get_face_normal(face_normal_vector_vec3, x, z, NNW, actual_image_width) +
                                get_face_normal(face_normal_vector_vec3, x, z, NNE, actual_image_width) +
                                get_face_normal(face_normal_vector_vec3, x, z, ENE, actual_image_width) +
                                get_face_normal(face_normal_vector_vec3, x, z, ESE, actual_image_width) +
                                get_face_normal(face_normal_vector_vec3, x, z, SSE, actual_image_width)));
                }

                x = actual_image_width - 1;

                // Compute the normal of an eastern vertex.
                // Number of adjacent faces: 4.
                temp_normals.push_back(glm::normalize(
                            get_face_normal(face_normal_vector_vec3, x, z, SSW, actual_image_width) +
                            get_face_normal(face_normal_vector_vec3, x, z, WSW, actual_image_width) +
                            get_face_normal(face_normal_vector_vec3, x, z, WNW, actual_image_width) +
                            get_face_normal(face_normal_vector_vec3, x, z, NNW, actual_image_width)));
            }

            // Compute the normal of the northwesternmost vertex.
            // Number of adjacent faces: 2.
            x = 0;
            temp_normals.push_back(glm::normalize(
                        get_face_normal(face_normal_vector_vec3, x, z, SSE, actual_image_width) +
                        get_face_normal(face_normal_vector_vec3, x, z, ESE, actual_image_width)));

            // Compute the normals of northern vertices.
            for (x = 1; x < actual_image_width - 1; x++)
            {
                // Compute the normal of a northern vertex.
                // Number of adjacent faces: 4.
                temp_normals.push_back(glm::normalize(
                            get_face_normal(face_normal_vector_vec3, x, z, SSW, actual_image_width) +
                            get_face_normal(face_normal_vector_vec3, x, z, WSW, actual_image_width) +
                            get_face_normal(face_normal_vector_vec3, x, z, ESE, actual_image_width) +
                            get_face_normal(face_normal_vector_vec3, x, z, SSE, actual_image_width)));
            }

            // Compute the normal of the northeasternmost vertex.
            // Number of adjacent faces: 2.
            x = actual_image_width - 1;
            temp_normals.push_back(glm::normalize(
                        get_face_normal(face_normal_vector_vec3, x, z, SSW, actual_image_width) +
                        get_face_normal(face_normal_vector_vec3, x, z, WSW, actual_image_width)));

            // 6. Compute the vertices between, `push_back` to `temp_normals`.
            // Number of adjacent faces: 4.

            for (z = 1; z < actual_image_height; z++)
            {
                for (x = 1; x < actual_image_width; x++)
                {
                    temp_normals.push_back(glm::normalize(
                                s_face_normal(face_normal_vector_vec3, x, z, actual_image_width) +
                                w_face_normal(face_normal_vector_vec3, x, z, actual_image_width) +
                                n_face_normal(face_normal_vector_vec3, x, z, actual_image_width) +
                                e_face_normal(face_normal_vector_vec3, x, z, actual_image_width)));
                }
            }
        }
        else if (is_southwest_northeast_edges_in_use)
        {
            int32_t x = 0;
            int32_t z = 0;

            // Compute the normal of the southwesternmost vertex.
            // Number of adjacent faces: 2.
            glm::vec3 vertex_normal;

            temp_normals.push_back(glm::normalize(
                        get_face_normal_for_SW_NE(face_normal_vector_vec3, x, z, ENE_CODE_FOR_SW_NE, actual_image_width) +
                        get_face_normal_for_SW_NE(face_normal_vector_vec3, x, z, NNE_CODE_FOR_SW_NE, actual_image_width)));

            // Compute the normals of southern vertices.
            for (x = 1; x < actual_image_width - 1; x++)
            {
                // Compute the normal of a southern vertex.
                // Number of adjacent faces: 3.
                temp_normals.push_back(glm::normalize(
                            get_face_normal_for_SW_NE(face_normal_vector_vec3, x, z, ENE_CODE_FOR_SW_NE, actual_image_width) +
                            get_face_normal_for_SW_NE(face_normal_vector_vec3, x, z, NNE_CODE_FOR_SW_NE, actual_image_width) +
                            get_face_normal_for_SW_NE(face_normal_vector_vec3, x, z, NW_CODE_FOR_SW_NE, actual_image_width)));
            }

            // Compute the normal of the southeasternmost vertex.
            // Number of adjacent faces: 1.
            x = actual_image_width - 1;
            temp_normals.push_back(get_face_normal_for_SW_NE(face_normal_vector_vec3, x, z, NW_CODE_FOR_SW_NE, actual_image_width));

            // Then, define most normals in a double loop.
            for (z = 1; z < actual_image_height - 1; z++)
            {
                // Compute the normal of a western vertex.
                // Number of adjacent faces: 3.
                x = 0;
                temp_normals.push_back(glm::normalize(
                            get_face_normal_for_SW_NE(face_normal_vector_vec3, x, z, SE_CODE_FOR_SW_NE, actual_image_width) +
                            get_face_normal_for_SW_NE(face_normal_vector_vec3, x, z, ENE_CODE_FOR_SW_NE, actual_image_width) +
                            get_face_normal_for_SW_NE(face_normal_vector_vec3, x, z, NNE_CODE_FOR_SW_NE, actual_image_width)));

                for (x = 1; x < actual_image_width - 1; x++)
                {
                    int32_t current_vertex_i = actual_image_width * z + x;

                    // Compute the normal of a central vertex.
                    // Number of adjacent faces: 6.
                    temp_normals.push_back(glm::normalize(
                                get_face_normal_for_SW_NE(face_normal_vector_vec3, x, z, SE_CODE_FOR_SW_NE, actual_image_width) +
                                get_face_normal_for_SW_NE(face_normal_vector_vec3, x, z, SSW_CODE_FOR_SW_NE, actual_image_width) +
                                get_face_normal_for_SW_NE(face_normal_vector_vec3, x, z, WSW_CODE_FOR_SW_NE, actual_image_width) +
                                get_face_normal_for_SW_NE(face_normal_vector_vec3, x, z, NW_CODE_FOR_SW_NE, actual_image_width) +
                                get_face_normal_for_SW_NE(face_normal_vector_vec3, x, z, NNE_CODE_FOR_SW_NE, actual_image_width) +
                                get_face_normal_for_SW_NE(face_normal_vector_vec3, x, z, ENE_CODE_FOR_SW_NE, actual_image_width)));
                }

                x = actual_image_width - 1;

                // Compute the normal of an eastern vertex.
                // Number of adjacent faces: 3.
                temp_normals.push_back(glm::normalize(
                            get_face_normal_for_SW_NE(face_normal_vector_vec3, x, z, SSW_CODE_FOR_SW_NE, actual_image_width) +
                            get_face_normal_for_SW_NE(face_normal_vector_vec3, x, z, WSW_CODE_FOR_SW_NE, actual_image_width) +
                            get_face_normal_for_SW_NE(face_normal_vector_vec3, x, z, NW_CODE_FOR_SW_NE, actual_image_width)));
            }

            // Compute the normal of the northwesternmost vertex.
            // Number of adjacent faces: 1.
            x = 0;
            temp_normals.push_back(get_face_normal_for_SW_NE(face_normal_vector_vec3, x, z, SE_CODE_FOR_SW_NE, actual_image_width));

            // Compute the normals of northern vertices.
            for (x = 1; x < actual_image_width - 1; x++)
            {
                // Compute the normal of a northern vertex.
                // Number of adjacent faces: 3.
                temp_normals.push_back(glm::normalize(
                            get_face_normal_for_SW_NE(face_normal_vector_vec3, x, z, SE_CODE_FOR_SW_NE, actual_image_width) +
                            get_face_normal_for_SW_NE(face_normal_vector_vec3, x, z, SSW_CODE_FOR_SW_NE, actual_image_width) +
                            get_face_normal_for_SW_NE(face_normal_vector_vec3, x, z, WSW_CODE_FOR_SW_NE, actual_image_width)));
            }

            // Compute the normal of the northeasternmost vertex.
            // Number of adjacent faces: 2.
            x = actual_image_width - 1;
            temp_normals.push_back(glm::normalize(
                        get_face_normal_for_SW_NE(face_normal_vector_vec3, x, z, SSW_CODE_FOR_SW_NE, actual_image_width) +
                        get_face_normal_for_SW_NE(face_normal_vector_vec3, x, z, WSW_CODE_FOR_SW_NE, actual_image_width)));
        }
        else if (is_southeast_northwest_edges_in_use)
        {
            int32_t x = 0;
            int32_t z = 0;

            // Compute the normal of the southwesternmost vertex.
            // Number of adjacent faces: 1.
            glm::vec3 vertex_normal;
            temp_normals.push_back(get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, NE_CODE_FOR_SE_NW, actual_image_width));

            // Compute the normals of southern vertices.
            for (x = 1; x < actual_image_width - 1; x++)
            {
                // Compute the normal of a southern vertex.
                // Number of adjacent faces: 3.
                temp_normals.push_back(glm::normalize(
                            get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, WNW_CODE_FOR_SE_NW, actual_image_width) +
                            get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, NNW_CODE_FOR_SE_NW, actual_image_width) +
                            get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, NE_CODE_FOR_SE_NW, actual_image_width)));
            }

            // Compute the normal of the southeasternmost vertex.
            // Number of adjacent faces: 2.
            x = actual_image_width - 1;
            temp_normals.push_back(glm::normalize(
                        get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, WNW_CODE_FOR_SE_NW, actual_image_width) +
                        get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, NNW_CODE_FOR_SE_NW, actual_image_width)));

            // Then, define most normals in a double loop.
            for (z = 1; z < actual_image_height - 1; z++)
            {
                // Compute the normal of a western vertex.
                // Number of adjacent faces: 3.
                x = 0;
                temp_normals.push_back(glm::normalize(
                            get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, NE_CODE_FOR_SE_NW, actual_image_width) +
                            get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, ESE_CODE_FOR_SE_NW, actual_image_width) +
                            get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, SSE_CODE_FOR_SE_NW, actual_image_width)));

                for (x = 1; x < actual_image_width - 1; x++)
                {
                    int32_t current_vertex_i = actual_image_width * z + x;

                    // Compute the normal of a central vertex.
                    // Number of adjacent faces: 6.
                    temp_normals.push_back(glm::normalize(
                                get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, SSE_CODE_FOR_SE_NW, actual_image_width) +
                                get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, SW_CODE_FOR_SE_NW, actual_image_width) +
                                get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, WNW_CODE_FOR_SE_NW, actual_image_width) +
                                get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, NNW_CODE_FOR_SE_NW, actual_image_width) +
                                get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, NE_CODE_FOR_SE_NW, actual_image_width) +
                                get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, ESE_CODE_FOR_SE_NW, actual_image_width)));
                }

                x = actual_image_width - 1;

                // Compute the normal of an eastern vertex.
                // Number of adjacent faces: 3.
                temp_normals.push_back(glm::normalize(
                            get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, SW_CODE_FOR_SE_NW, actual_image_width) +
                            get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, WNW_CODE_FOR_SE_NW, actual_image_width) +
                            get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, NNW_CODE_FOR_SE_NW, actual_image_width)));
            }

            // Compute the normal of the northwesternmost vertex.
            // Number of adjacent faces: 2.
            x = 0;
            temp_normals.push_back(glm::normalize(
                        get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, SSE_CODE_FOR_SE_NW, actual_image_width) +
                        get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, ESE_CODE_FOR_SE_NW, actual_image_width)));

            // Compute the normals of northern vertices.
            for (x = 1; x < actual_image_width - 1; x++)
            {
                // Compute the normal of a northern vertex.
                // Number of adjacent faces: 3.
                temp_normals.push_back(glm::normalize(
                            get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, SW_CODE_FOR_SE_NW, actual_image_width) +
                            get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, ESE_CODE_FOR_SE_NW, actual_image_width) +
                            get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, SSE_CODE_FOR_SE_NW, actual_image_width)));
            }

            // Compute the normal of the northeasternmost vertex.
            // Number of adjacent faces: 1.
            x = actual_image_width - 1;
            temp_normals.push_back(glm::normalize(
                        get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, SW_CODE_FOR_SE_NW, actual_image_width)));
        }

        return true;
    }
}
