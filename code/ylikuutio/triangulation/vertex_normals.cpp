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
    void compute_vertex_normals(
            std::vector<glm::vec3>& temp_normals,
            std::vector<glm::vec3>& face_normal_vector_vec3,
            uint32_t image_width,
            uint32_t image_height,
            bool is_bilinear_interpolation_in_use,
            bool is_southwest_northeast_edges_in_use,
            bool is_southeast_northwest_edges_in_use)
    {
            // 5. Compute the vertex normals for vertices loaded from file, `push_back` to `temp_normals`.
            // std::cout << "computing vertex normals for vertices loaded from file.\n";

            if (is_bilinear_interpolation_in_use)
            {
                uint32_t current_interpolated_vertex_i = image_width * image_height;
                uint32_t x = 0;
                uint32_t z = 0;

                // Compute the normal of the southwesternmost vertex.
                // Number of adjacent faces: 2.
                glm::vec3 vertex_normal;

                vertex_normal = glm::normalize(
                        get_face_normal(face_normal_vector_vec3, x, z, NNE, image_width) +
                        get_face_normal(face_normal_vector_vec3, x, z, ENE, image_width));
                temp_normals.push_back(vertex_normal);

                // Compute the normals of southern vertices.
                for (x = 1; x < image_width - 1; x++)
                {
                    // Compute the normal of a southern vertex.
                    // Number of adjacent faces: 4.
                    vertex_normal = glm::normalize(
                            get_face_normal(face_normal_vector_vec3, x, z, WNW, image_width) +
                            get_face_normal(face_normal_vector_vec3, x, z, NNW, image_width) +
                            get_face_normal(face_normal_vector_vec3, x, z, NNE, image_width) +
                            get_face_normal(face_normal_vector_vec3, x, z, ENE, image_width));
                    temp_normals.push_back(vertex_normal);
                }

                // Compute the normal of the southeasternmost vertex.
                // Number of adjacent faces: 2.
                x = image_width - 1;
                vertex_normal = glm::normalize(
                        get_face_normal(face_normal_vector_vec3, x, z, WNW, image_width) +
                        get_face_normal(face_normal_vector_vec3, x, z, NNW, image_width));
                temp_normals.push_back(vertex_normal);

                // Then, define most normals in a double loop.
                for (z = 1; z < image_height - 1; z++)
                {
                    // Compute the normal of a western vertex.
                    // Number of adjacent faces: 4.
                    x = 0;
                    vertex_normal = glm::normalize(
                            get_face_normal(face_normal_vector_vec3, x, z, NNE, image_width) +
                            get_face_normal(face_normal_vector_vec3, x, z, ENE, image_width) +
                            get_face_normal(face_normal_vector_vec3, x, z, ESE, image_width) +
                            get_face_normal(face_normal_vector_vec3, x, z, SSE, image_width));
                    temp_normals.push_back(vertex_normal);

                    for (x = 1; x < image_width - 1; x++)
                    {
                        uint32_t current_vertex_i = image_width * z + x;

                        // Compute the normal of a central vertex.
                        // Number of adjacent faces: 8.
                        vertex_normal = glm::normalize(
                                get_face_normal(face_normal_vector_vec3, x, z, SSW, image_width) +
                                get_face_normal(face_normal_vector_vec3, x, z, WSW, image_width) +
                                get_face_normal(face_normal_vector_vec3, x, z, WNW, image_width) +
                                get_face_normal(face_normal_vector_vec3, x, z, NNW, image_width) +
                                get_face_normal(face_normal_vector_vec3, x, z, NNE, image_width) +
                                get_face_normal(face_normal_vector_vec3, x, z, ENE, image_width) +
                                get_face_normal(face_normal_vector_vec3, x, z, ESE, image_width) +
                                get_face_normal(face_normal_vector_vec3, x, z, SSE, image_width));
                        temp_normals.push_back(vertex_normal);
                    }

                    x = image_width - 1;

                    // Compute the normal of an eastern vertex.
                    // Number of adjacent faces: 4.
                    vertex_normal = glm::normalize(
                            get_face_normal(face_normal_vector_vec3, x, z, SSW, image_width) +
                            get_face_normal(face_normal_vector_vec3, x, z, WSW, image_width) +
                            get_face_normal(face_normal_vector_vec3, x, z, WNW, image_width) +
                            get_face_normal(face_normal_vector_vec3, x, z, NNW, image_width));
                    temp_normals.push_back(vertex_normal);
                }

                // Compute the normal of the northwesternmost vertex.
                // Number of adjacent faces: 2.
                x = 0;
                vertex_normal = glm::normalize(
                        get_face_normal(face_normal_vector_vec3, x, z, SSE, image_width) +
                        get_face_normal(face_normal_vector_vec3, x, z, ESE, image_width));
                temp_normals.push_back(vertex_normal);

                // Compute the normals of northern vertices.
                for (x = 1; x < image_width - 1; x++)
                {
                    // Compute the normal of a northern vertex.
                    // Number of adjacent faces: 4.
                    vertex_normal = glm::normalize(
                            get_face_normal(face_normal_vector_vec3, x, z, SSW, image_width) +
                            get_face_normal(face_normal_vector_vec3, x, z, WSW, image_width) +
                            get_face_normal(face_normal_vector_vec3, x, z, ESE, image_width) +
                            get_face_normal(face_normal_vector_vec3, x, z, SSE, image_width));
                    temp_normals.push_back(vertex_normal);
                }

                // Compute the normal of the northeasternmost vertex.
                // Number of adjacent faces: 2.
                x = image_width - 1;
                vertex_normal = glm::normalize(
                        get_face_normal(face_normal_vector_vec3, x, z, SSW, image_width) +
                        get_face_normal(face_normal_vector_vec3, x, z, WSW, image_width));
                temp_normals.push_back(vertex_normal);

                // 6. Compute the vertices between, `push_back` to `temp_normals`.
                // Number of adjacent faces: 4.
                // std::cout << "computing vertex normals for interpolated vertices.\n";

                for (z = 1; z < image_height; z++)
                {
                    for (x = 1; x < image_width; x++)
                    {
                        vertex_normal = glm::normalize(
                                s_face_normal(face_normal_vector_vec3, x, z, image_width) +
                                w_face_normal(face_normal_vector_vec3, x, z, image_width) +
                                n_face_normal(face_normal_vector_vec3, x, z, image_width) +
                                e_face_normal(face_normal_vector_vec3, x, z, image_width));
                        temp_normals.push_back(vertex_normal);
                    }
                }
            }
            else if (is_southwest_northeast_edges_in_use)
            {
                // TODO: compute vertex normals for `"southwest_northeast_edges"`.
            }
            else if (is_southeast_northwest_edges_in_use)
            {
                uint32_t x = 0;
                uint32_t z = 0;

                // Compute the normal of the southwesternmost vertex.
                // Number of adjacent faces: 1.
                glm::vec3 vertex_normal;
                vertex_normal = get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, NE_CODE_FOR_SE_NW, image_width);
                temp_normals.push_back(vertex_normal);

                // Compute the normals of southern vertices.
                for (x = 1; x < image_width - 1; x++)
                {
                    // Compute the normal of a southern vertex.
                    // Number of adjacent faces: 3.
                    vertex_normal = glm::normalize(
                            get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, WNW_CODE_FOR_SE_NW, image_width) +
                            get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, NNW_CODE_FOR_SE_NW, image_width) +
                            get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, NE_CODE_FOR_SE_NW, image_width));
                    temp_normals.push_back(vertex_normal);
                }

                // Compute the normal of the southeasternmost vertex.
                // Number of adjacent faces: 2.
                x = image_width - 1;
                vertex_normal = glm::normalize(
                        get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, WNW_CODE_FOR_SE_NW, image_width) +
                        get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, NNW_CODE_FOR_SE_NW, image_width));
                temp_normals.push_back(vertex_normal);

                // Then, define most normals in a double loop.
                for (z = 1; z < image_height - 1; z++)
                {
                    // Compute the normal of a western vertex.
                    // Number of adjacent faces: 3.
                    x = 0;
                    vertex_normal = glm::normalize(
                            get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, NE_CODE_FOR_SE_NW, image_width) +
                            get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, ESE_CODE_FOR_SE_NW, image_width) +
                            get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, SSE_CODE_FOR_SE_NW, image_width));
                    temp_normals.push_back(vertex_normal);

                    for (x = 1; x < image_width - 1; x++)
                    {
                        uint32_t current_vertex_i = image_width * z + x;

                        // Compute the normal of a central vertex.
                        // Number of adjacent faces: 6.
                        vertex_normal = glm::normalize(
                                get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, SSE_CODE_FOR_SE_NW, image_width) +
                                get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, SW_CODE_FOR_SE_NW, image_width) +
                                get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, WNW_CODE_FOR_SE_NW, image_width) +
                                get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, NNW_CODE_FOR_SE_NW, image_width) +
                                get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, NE_CODE_FOR_SE_NW, image_width) +
                                get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, ESE_CODE_FOR_SE_NW, image_width));
                        temp_normals.push_back(vertex_normal);
                    }

                    x = image_width - 1;

                    // Compute the normal of an eastern vertex.
                    // Number of adjacent faces: 3.
                    vertex_normal = glm::normalize(
                            get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, SW_CODE_FOR_SE_NW, image_width) +
                            get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, WNW_CODE_FOR_SE_NW, image_width) +
                            get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, NNW_CODE_FOR_SE_NW, image_width));
                    temp_normals.push_back(vertex_normal);
                }

                // Compute the normal of the northwesternmost vertex.
                // Number of adjacent faces: 2.
                x = 0;
                vertex_normal = glm::normalize(
                        get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, SSE_CODE_FOR_SE_NW, image_width) +
                        get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, ESE_CODE_FOR_SE_NW, image_width));
                temp_normals.push_back(vertex_normal);

                // Compute the normals of northern vertices.
                for (x = 1; x < image_width - 1; x++)
                {
                    // Compute the normal of a northern vertex.
                    // Number of adjacent faces: 3.
                    vertex_normal = glm::normalize(
                            get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, SW_CODE_FOR_SE_NW, image_width) +
                            get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, ESE_CODE_FOR_SE_NW, image_width) +
                            get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, SSE_CODE_FOR_SE_NW, image_width));
                    temp_normals.push_back(vertex_normal);
                }

                // Compute the normal of the northeasternmost vertex.
                // Number of adjacent faces: 1.
                x = image_width - 1;
                vertex_normal = glm::normalize(
                        get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, SW_CODE_FOR_SE_NW, image_width));
                temp_normals.push_back(vertex_normal);
            }
    }
}
