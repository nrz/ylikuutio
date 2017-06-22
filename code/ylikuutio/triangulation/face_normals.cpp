#include "face_normals.hpp"
#include "triangulation_enums.hpp"
#include "indexing.hpp"

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
            int32_t actual_image_width,
            int32_t actual_image_height,
            bool is_bilinear_interpolation_in_use,
            bool is_southwest_northeast_edges_in_use,
            bool is_southeast_northwest_edges_in_use)
    {
        int32_t current_interpolated_vertex_i = actual_image_width * actual_image_height;

        if (actual_image_width < 2 || actual_image_height < 2)
        {
            // If width or height is < 2, there are no faces.
            return false;
        }

        for (int32_t z = 1; z < actual_image_height; z++)
        {
            for (int32_t x = 1; x < actual_image_width; x++)
            {
                int32_t current_vertex_i = actual_image_width * z + x;

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
                else
                {
                    std::cerr << "invalid triangulation type!\n";
                    return false;
                }
                current_interpolated_vertex_i++;
            }
        }
        return true;
    }

    // for bilinear interpolation.
    glm::vec3 get_face_normal(
            std::vector<glm::vec3>& face_normal_data,
            int32_t x,
            int32_t z,
            BilinearDirections compass_point_code,
            int32_t actual_image_width)
    {
        if (x < 0 || z < 0)
        {
            std::cerr << "negative coordinates are not supported!";
        }

        int32_t face_normal_i = get_face_normal_i(x, z, compass_point_code, actual_image_width);

        if (face_normal_i == -1)
        {
            std::cerr << "invalid compass point code!\n";
            return glm::vec3(NAN, NAN, NAN);
        }

        return face_normal_data[face_normal_i];
    }

    // for bilinear interpolation.
    // These functions exist to avoid need to remember
    // the array order when calling `geometry::get_face_normal`.
    glm::vec3 s_face_normal(std::vector<glm::vec3>& face_normal_vector_vec3, int32_t x, int32_t z, int32_t image_width)
    {
        return geometry::get_face_normal(face_normal_vector_vec3, x - 1, z - 1, ENE, image_width);
    }
    glm::vec3 w_face_normal(std::vector<glm::vec3>& face_normal_vector_vec3, int32_t x, int32_t z, int32_t image_width)
    {
        return geometry::get_face_normal(face_normal_vector_vec3, x - 1, z - 1, NNE, image_width);
    }
    glm::vec3 n_face_normal(std::vector<glm::vec3>& face_normal_vector_vec3, int32_t x, int32_t z, int32_t image_width)
    {
        return geometry::get_face_normal(face_normal_vector_vec3, x, z, WSW, image_width);
    }
    glm::vec3 e_face_normal(std::vector<glm::vec3>& face_normal_vector_vec3, int32_t x, int32_t z, int32_t image_width)
    {
        return geometry::get_face_normal(face_normal_vector_vec3, x, z, SSW, image_width);
    }

    // for southeast-northwest edges.
    glm::vec3 get_face_normal_for_SE_NW(
            std::vector<glm::vec3>& face_normal_data,
            int32_t x,
            int32_t z,
            SoutheastNorthwestEdgesDirections compass_point_code,
            int32_t image_width)
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
        return face_normal_data[face_normal_i];
    }

    // for southwest-northeast edges.
    glm::vec3 get_face_normal_for_SW_NE(
            std::vector<glm::vec3>& face_normal_data,
            int32_t x,
            int32_t z,
            SouthwestNortheastEdgesDirections compass_point_code,
            int32_t image_width)
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
        return face_normal_data[face_normal_i];
    }
}
