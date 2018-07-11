#include "face_normals.hpp"
#include "triangulation_enums.hpp"
#include "indexing.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace yli
{
    namespace geometry
    {
        bool compute_face_normals(
                std::vector<glm::vec3>& temp_vertices,
                std::vector<glm::vec3>& face_normal_vector_vec3,
                const int32_t actual_image_width,
                const int32_t actual_image_height,
                const bool is_bilinear_interpolation_in_use,
                const bool is_southwest_northeast_edges_in_use,
                const bool is_southeast_northwest_edges_in_use)
        {
            std::size_t current_interpolated_vertex_i = actual_image_width * actual_image_height;

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
                if (temp_vertices.size() != actual_image_width * actual_image_height + (actual_image_width - 1) * (actual_image_height - 1))
                {
                    // Number of vertices must be correct.
                    return false;
                }

                // If bilinear interpolation is in use, then number of faces is:
                // 4 * (actual_image_width - 1) * (actual_image_height - 1)
                face_normal_vector_vec3.reserve(4 * (actual_image_width - 1) * (actual_image_height - 1));
            }
            else
            {
                if (temp_vertices.size() != actual_image_width * actual_image_height)
                {
                    // If number of face normals is not width * height, then the number of vertices is incorrect.
                    return false;
                }

                face_normal_vector_vec3.reserve(2 * (actual_image_width - 1) * (actual_image_height - 1));
            }

            for (std::size_t z = 1; z < actual_image_height; z++)
            {
                for (std::size_t x = 1; x < actual_image_width; x++)
                {
                    std::size_t current_vertex_i = actual_image_width * z + x;

                    // Computing of face normals depends on triangulation type.
                    if (is_bilinear_interpolation_in_use)
                    {
                        glm::vec3 edge1;
                        glm::vec3 edge2;
                        glm::vec3 face_normal;

                        // Compute the normal of S face.
                        edge1 = temp_vertices[southeast(current_vertex_i, actual_image_width)] - temp_vertices[current_interpolated_vertex_i];
                        edge2 = temp_vertices[southwest(current_vertex_i, actual_image_width)] - temp_vertices[current_interpolated_vertex_i];
                        face_normal = glm::normalize(glm::cross(edge1, edge2));
                        face_normal_vector_vec3.push_back(face_normal);

                        // Compute the normal of W face.
                        edge1 = temp_vertices[southwest(current_vertex_i, actual_image_width)] - temp_vertices[current_interpolated_vertex_i];
                        edge2 = temp_vertices[northwest(current_vertex_i, actual_image_width)] - temp_vertices[current_interpolated_vertex_i];
                        face_normal = glm::normalize(glm::cross(edge1, edge2));
                        face_normal_vector_vec3.push_back(face_normal);

                        // Compute the normal of N face.
                        edge1 = temp_vertices[northwest(current_vertex_i, actual_image_width)] - temp_vertices[current_interpolated_vertex_i];
                        edge2 = temp_vertices[northeast(current_vertex_i, actual_image_width)] - temp_vertices[current_interpolated_vertex_i];
                        face_normal = glm::normalize(glm::cross(edge1, edge2));
                        face_normal_vector_vec3.push_back(face_normal);

                        // Compute the normal of E face.
                        edge1 = temp_vertices[northeast(current_vertex_i, actual_image_width)] - temp_vertices[current_interpolated_vertex_i];
                        edge2 = temp_vertices[southeast(current_vertex_i, actual_image_width)] - temp_vertices[current_interpolated_vertex_i];
                        face_normal = glm::normalize(glm::cross(edge1, edge2));
                        face_normal_vector_vec3.push_back(face_normal);
                    }
                    else if (is_southwest_northeast_edges_in_use)
                    {
                        glm::vec3 edge1;
                        glm::vec3 edge2;
                        glm::vec3 face_normal;

                        // Compute the normal of SE face.
                        edge1 = temp_vertices[southwest(current_vertex_i, actual_image_width)] - temp_vertices[southeast(current_vertex_i, actual_image_width)];
                        edge2 = temp_vertices[northeast(current_vertex_i, actual_image_width)] - temp_vertices[southeast(current_vertex_i, actual_image_width)];
                        face_normal = glm::normalize(glm::cross(edge1, edge2));
                        face_normal_vector_vec3.push_back(face_normal);

                        // Compute the normal of NW face.
                        edge1 = temp_vertices[northeast(current_vertex_i, actual_image_width)] - temp_vertices[northwest(current_vertex_i, actual_image_width)];
                        edge2 = temp_vertices[southwest(current_vertex_i, actual_image_width)] - temp_vertices[northwest(current_vertex_i, actual_image_width)];
                        face_normal = glm::normalize(glm::cross(edge1, edge2));
                        face_normal_vector_vec3.push_back(face_normal);
                    }
                    else if (is_southeast_northwest_edges_in_use)
                    {
                        glm::vec3 edge1;
                        glm::vec3 edge2;
                        glm::vec3 face_normal;

                        // Compute the normal of SW face.
                        edge1 = temp_vertices[northwest(current_vertex_i, actual_image_width)] - temp_vertices[southwest(current_vertex_i, actual_image_width)];
                        edge2 = temp_vertices[southeast(current_vertex_i, actual_image_width)] - temp_vertices[southwest(current_vertex_i, actual_image_width)];
                        face_normal = glm::normalize(glm::cross(edge1, edge2));
                        face_normal_vector_vec3.push_back(face_normal);

                        // Compute the normal of NE face.
                        edge1 = temp_vertices[southeast(current_vertex_i, actual_image_width)] - temp_vertices[northeast(current_vertex_i, actual_image_width)];
                        edge2 = temp_vertices[northwest(current_vertex_i, actual_image_width)] - temp_vertices[northeast(current_vertex_i, actual_image_width)];
                        face_normal = glm::normalize(glm::cross(edge1, edge2));
                        face_normal_vector_vec3.push_back(face_normal);
                    }

                    current_interpolated_vertex_i++;
                }
            }
            return true;
        }

        // for bilinear interpolation.
        glm::vec3 get_face_normal(
                const std::vector<glm::vec3>& face_normal_data,
                const int32_t x,
                const int32_t z,
                const BilinearDirections compass_point_code,
                const int32_t actual_image_width)
        {
            if (x < 0 || z < 0)
            {
                std::cerr << "negative coordinates are not supported!";
                return glm::vec3(NAN, NAN, NAN);
            }

            const int32_t face_normal_i = get_face_normal_i(x, z, compass_point_code, actual_image_width);

            if (face_normal_i < 0)
            {
                std::cerr << "invalid compass point code!\n";
                return glm::vec3(NAN, NAN, NAN);
            }

            return face_normal_data[face_normal_i];
        }

        // for bilinear interpolation.
        // These functions exist to avoid need to remember
        // the array order when calling `yli::geometry::get_face_normal`.
        glm::vec3 s_face_normal(const std::vector<glm::vec3>& face_normal_vector_vec3, const int32_t x, const int32_t z, const int32_t image_width)
        {
            return yli::geometry::get_face_normal(face_normal_vector_vec3, x - 1, z - 1, ENE, image_width);
        }
        glm::vec3 w_face_normal(const std::vector<glm::vec3>& face_normal_vector_vec3, const int32_t x, const int32_t z, const int32_t image_width)
        {
            return yli::geometry::get_face_normal(face_normal_vector_vec3, x - 1, z - 1, NNE, image_width);
        }
        glm::vec3 n_face_normal(const std::vector<glm::vec3>& face_normal_vector_vec3, const int32_t x, const int32_t z, const int32_t image_width)
        {
            return yli::geometry::get_face_normal(face_normal_vector_vec3, x, z, WSW, image_width);
        }
        glm::vec3 e_face_normal(const std::vector<glm::vec3>& face_normal_vector_vec3, const int32_t x, const int32_t z, const int32_t image_width)
        {
            return yli::geometry::get_face_normal(face_normal_vector_vec3, x, z, SSW, image_width);
        }

        // for southeast-northwest edges.
        glm::vec3 get_face_normal_for_SE_NW(
                const std::vector<glm::vec3>& face_normal_data,
                const int32_t x,
                const int32_t z,
                const SoutheastNorthwestEdgesDirections compass_point_code,
                const int32_t image_width)
        {
            int32_t face_normal_i;

            switch (compass_point_code)
            {
                case SSE_CODE_FOR_SE_NW:
                    face_normal_i = 2 * (z - 1) * (image_width - 1) + 2 * x;
                    break;
                case WNW_CODE_FOR_SE_NW:
                    face_normal_i = 2 * z * (image_width - 1) + 2 * x - 2;
                    break;
                case ESE_CODE_FOR_SE_NW:
                    face_normal_i = 2 * (z - 1) * (image_width - 1) + 2 * x + 1;
                    break;
                case NNW_CODE_FOR_SE_NW:
                    face_normal_i = 2 * z * (image_width - 1) + 2 * x - 1;
                    break;
                case SW_CODE_FOR_SE_NW:
                    face_normal_i = 2 * (z - 1) * (image_width - 1) + 2 * x - 1;
                    break;
                case NE_CODE_FOR_SE_NW:
                    face_normal_i = 2 * z * (image_width - 1) + 2 * x;
                    break;
                default:
                    std::cerr << "invalid compass point code!\n";
                    return glm::vec3(NAN, NAN, NAN);
            }

            if (face_normal_i < 0)
            {
                // Face normal index can not be negative.
                return glm::vec3(NAN, NAN, NAN);
            }

            return face_normal_data[face_normal_i];
        }

        // for southwest-northeast edges.
        glm::vec3 get_face_normal_for_SW_NE(
                const std::vector<glm::vec3>& face_normal_data,
                const int32_t x,
                const int32_t z,
                const SouthwestNortheastEdgesDirections compass_point_code,
                const int32_t image_width)
        {
            int32_t face_normal_i;

            switch (compass_point_code)
            {
                case SSW_CODE_FOR_SW_NE:
                    face_normal_i = 2 * (z - 1) * (image_width - 1) + 2 * x - 2;
                    break;
                case ENE_CODE_FOR_SW_NE:
                    face_normal_i = 2 * z * (image_width - 1) + 2 * x;
                    break;
                case WSW_CODE_FOR_SW_NE:
                    face_normal_i = 2 * (z - 1) * (image_width - 1) + 2 * x - 1;
                    break;
                case NNE_CODE_FOR_SW_NE:
                    face_normal_i = 2 * z * (image_width - 1) + 2 * x + 1;
                    break;
                case SE_CODE_FOR_SW_NE:
                    face_normal_i = 2 * (z - 1) * (image_width - 1) + 2 * x + 1;
                    break;
                case NW_CODE_FOR_SW_NE:
                    face_normal_i = 2 * z * (image_width - 1) + 2 * x - 1;
                    break;
                default:
                    std::cerr << "invalid compass point code!\n";
                    return glm::vec3(NAN, NAN, NAN);
            }

            if (face_normal_i < 0)
            {
                // Face normal index can not be negative.
                return glm::vec3(NAN, NAN, NAN);
            }

            return face_normal_data[face_normal_i];
        }
    }
}
