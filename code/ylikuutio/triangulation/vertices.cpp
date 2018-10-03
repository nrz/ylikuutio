#include "vertices.hpp"
#include "indexing.hpp"
#include "triangulate_quads_struct.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>  // std::size_t
#include <vector>   // std::vector

namespace yli
{
    namespace geometry
    {
        void output_triangle_vertices(
                const std::vector<glm::vec3>& temp_vertices,
                const std::vector<glm::vec2>& temp_UVs,
                const std::vector<glm::vec3>& temp_normals,
                const GLuint vertex_index[3],
                const GLuint uv_index[3],
                const GLuint normal_index[3],
                std::vector<glm::vec3>& out_vertices,
                std::vector<glm::vec2>& out_UVs,
                std::vector<glm::vec3>& out_normals)
        {
            out_vertices.push_back(temp_vertices[vertex_index[0]]);
            out_UVs.push_back(temp_UVs[uv_index[0]]);
            out_normals.push_back(temp_normals[normal_index[0]]);

            out_vertices.push_back(temp_vertices[vertex_index[1]]);
            out_UVs.push_back(temp_UVs[uv_index[1]]);
            out_normals.push_back(temp_normals[normal_index[1]]);

            out_vertices.push_back(temp_vertices[vertex_index[2]]);
            out_UVs.push_back(temp_UVs[uv_index[2]]);
            out_normals.push_back(temp_normals[normal_index[2]]);
        }

        bool define_vertices_UVs_and_normals(
                const yli::geometry::TriangulateQuadsStruct& triangulate_quads_struct,
                const std::vector<glm::vec3>& temp_vertices,
                const std::vector<glm::vec2>& temp_UVs,
                const std::vector<glm::vec3>& temp_normals,
                std::vector<glm::vec3>& out_vertices,
                std::vector<glm::vec2>& out_UVs,
                std::vector<glm::vec3>& out_normals,
                const std::size_t actual_image_width,
                const std::size_t actual_image_height,
                const bool is_bilinear_interpolation_in_use,
                const bool is_southwest_northeast_edges_in_use,
                const bool is_southeast_northwest_edges_in_use)
        {
            // 6. Loop through all vertices and `yli::geometry::output_triangle_vertices`.

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

                // Face indices example for a 4x4 image file using bilinear interpolation.
                //
                //  +-------+-------+-------+
                //  |\ 26  /|\ 30  /|\ 34  /|
                //  | \   / | \   / | \   / |
                //  |  \ /  |  \ /  |  \ /  |
                //  |25 x 27|29 x 31|33 x 35|
                //  |  / \  |  / \  |  / \  |
                //  | /   \ | /   \ | /   \ |
                //  |/ 24  \|/ 28  \|/ 32  \|
                //  +-------+-------+-------+
                //  |\ 14  /|\ 18  /|\ 22  /|
                //  | \   / | \   / | \   / |
                //  |  \ /  |  \ /  |  \ /  |
                //  |13 x 15|17 x 19|21 x 23|
                //  |  / \  |  / \  |  / \  |
                //  | /   \ | /   \ | /   \ |
                //  |/ 12  \|/ 16  \|/ 20  \|
                //  +-------+-------+-------+
                //  |\  2  /|\  6  /|\ 10  /|
                //  | \   / | \   / | \   / |
                //  |  \ /  |  \ /  |  \ /  |
                //  |1  x  3|5  x  7|9  x 11|
                //  |  / \  |  / \  |  / \  |
                //  | /   \ | /   \ | /   \ |
                //  |/  0  \|/  4  \|/  8  \|
                //  +-------+-------+-------+

                std::size_t current_interpolated_vertex_i = actual_image_width * actual_image_height;

                for (std::size_t z = 1; z < actual_image_height; z++)
                {
                    for (std::size_t x = 1; x < actual_image_width; x++)
                    {
                        std::size_t current_vertex_i = actual_image_width * z + x;

                        GLuint vertex_index[3];
                        GLuint uv_index[3];
                        GLuint normal_index[3];

                        // This corresponds to "vn": specify normal of one vertex.

                        // Then, define the triangles (4 faces).
                        // Triangle order: S - W - N - E.
                        //
                        // First triangle: center, southeast, southwest.
                        // Second triangle: center, southwest, northwest.
                        // Third triangle: center, northwest, northeast.
                        // Fourth triangle: center, northeast, southeast.

                        // Define the first triangle, S: center, southeast, southwest.
                        vertex_index[0] = current_interpolated_vertex_i;
                        vertex_index[1] = southeast(current_vertex_i, actual_image_width);
                        vertex_index[2] = southwest(current_vertex_i, actual_image_width);

                        normal_index[0] = current_interpolated_vertex_i;
                        normal_index[1] = southeast(current_vertex_i, actual_image_width);
                        normal_index[2] = southwest(current_vertex_i, actual_image_width);

                        uv_index[0] = current_interpolated_vertex_i;
                        uv_index[1] = southeast(current_vertex_i, actual_image_width);
                        uv_index[2] = southwest(current_vertex_i, actual_image_width);

                        yli::geometry::output_triangle_vertices(
                                temp_vertices,
                                temp_UVs,
                                temp_normals,
                                vertex_index,
                                uv_index,
                                normal_index,
                                out_vertices,
                                out_UVs,
                                out_normals);

                        // Define the second triangle, W: center, southwest, northwest.
                        vertex_index[0] = current_interpolated_vertex_i;
                        vertex_index[1] = southwest(current_vertex_i, actual_image_width);
                        vertex_index[2] = northwest(current_vertex_i, actual_image_width);

                        normal_index[0] = current_interpolated_vertex_i;
                        normal_index[1] = southwest(current_vertex_i, actual_image_width);
                        normal_index[2] = northwest(current_vertex_i, actual_image_width);

                        uv_index[0] = current_interpolated_vertex_i;
                        uv_index[1] = southwest(current_vertex_i, actual_image_width);
                        uv_index[2] = northwest(current_vertex_i, actual_image_width);

                        yli::geometry::output_triangle_vertices(
                                temp_vertices,
                                temp_UVs,
                                temp_normals,
                                vertex_index,
                                uv_index,
                                normal_index,
                                out_vertices,
                                out_UVs,
                                out_normals);

                        // Define the third triangle, N: center, northwest, northeast.
                        vertex_index[0] = current_interpolated_vertex_i;
                        vertex_index[1] = northwest(current_vertex_i, actual_image_width);
                        vertex_index[2] = northeast(current_vertex_i, actual_image_width);

                        normal_index[0] = current_interpolated_vertex_i;
                        normal_index[1] = northwest(current_vertex_i, actual_image_width);
                        normal_index[2] = northeast(current_vertex_i, actual_image_width);

                        uv_index[0] = current_interpolated_vertex_i;
                        uv_index[1] = northwest(current_vertex_i, actual_image_width);
                        uv_index[2] = northeast(current_vertex_i, actual_image_width);

                        yli::geometry::output_triangle_vertices(
                                temp_vertices,
                                temp_UVs,
                                temp_normals,
                                vertex_index,
                                uv_index,
                                normal_index,
                                out_vertices,
                                out_UVs,
                                out_normals);

                        // Define the fourth triangle, E: center, northeast, southeast.
                        vertex_index[0] = current_interpolated_vertex_i;
                        vertex_index[1] = northeast(current_vertex_i, actual_image_width);
                        vertex_index[2] = southeast(current_vertex_i, actual_image_width);

                        normal_index[0] = current_interpolated_vertex_i;
                        normal_index[1] = northeast(current_vertex_i, actual_image_width);
                        normal_index[2] = southeast(current_vertex_i, actual_image_width);

                        uv_index[0] = current_interpolated_vertex_i;
                        uv_index[1] = northeast(current_vertex_i, actual_image_width);
                        uv_index[2] = southeast(current_vertex_i, actual_image_width);

                        yli::geometry::output_triangle_vertices(
                                temp_vertices,
                                temp_UVs,
                                temp_normals,
                                vertex_index,
                                uv_index,
                                normal_index,
                                out_vertices,
                                out_UVs,
                                out_normals);

                        current_interpolated_vertex_i++;
                    }
                }
            }
            else if (is_southwest_northeast_edges_in_use)
            {
                if (temp_vertices.size() != actual_image_width * actual_image_height)
                {
                    // If number of face normals is not width * height, then the number of vertices is incorrect.
                    return false;
                }

                // Face indices example for a 4x4 image file using southwest-northeast edges.
                //
                // +---+---+---+
                // |13/|15/|17/|
                // | / | / | / |
                // |/12|/14|/16|
                // +---+---+---+
                // |7 /|9 /|11/|
                // | / | / | / |
                // |/ 6|/ 8|/10|
                // +---+---+---+
                // |1 /|3 /|5 /|
                // | / | / | / |
                // |/ 0|/ 2|/ 4|
                // +---+---+---+
                // southwest northeast edges.

                for (std::size_t z = 1; z < actual_image_height; z++)
                {
                    for (std::size_t x = 1; x < actual_image_width; x++)
                    {
                        std::size_t current_vertex_i = actual_image_width * z + x;

                        GLuint vertex_index[3];
                        GLuint uv_index[3];
                        GLuint normal_index[3];

                        // This corresponds to "vn": specify normal of one vertex.

                        // Then, define the triangles (2 faces).
                        // Triangle order: SE - NW.
                        //
                        // First triangle: southeast, southwest, northeast.
                        // Second triangle: northwest, northeast, southwest.

                        // Define the first triangle, SE: southeast, southwest, northeast.
                        vertex_index[0] = southeast(current_vertex_i, actual_image_width);
                        vertex_index[1] = southwest(current_vertex_i, actual_image_width);
                        vertex_index[2] = northeast(current_vertex_i, actual_image_width);

                        normal_index[0] = southeast(current_vertex_i, actual_image_width);
                        normal_index[1] = southwest(current_vertex_i, actual_image_width);
                        normal_index[2] = northeast(current_vertex_i, actual_image_width);

                        uv_index[0] = southeast(current_vertex_i, actual_image_width);
                        uv_index[1] = southwest(current_vertex_i, actual_image_width);
                        uv_index[2] = northeast(current_vertex_i, actual_image_width);

                        yli::geometry::output_triangle_vertices(
                                temp_vertices,
                                temp_UVs,
                                temp_normals,
                                vertex_index,
                                uv_index,
                                normal_index,
                                out_vertices,
                                out_UVs,
                                out_normals);

                        // Define the second triangle, NW: northwest, northeast, southwest.
                        vertex_index[0] = northwest(current_vertex_i, actual_image_width);
                        vertex_index[1] = northeast(current_vertex_i, actual_image_width);
                        vertex_index[2] = southwest(current_vertex_i, actual_image_width);

                        normal_index[0] = northwest(current_vertex_i, actual_image_width);
                        normal_index[1] = northeast(current_vertex_i, actual_image_width);
                        normal_index[2] = southwest(current_vertex_i, actual_image_width);

                        uv_index[0] = northwest(current_vertex_i, actual_image_width);
                        uv_index[1] = northeast(current_vertex_i, actual_image_width);
                        uv_index[2] = southwest(current_vertex_i, actual_image_width);

                        yli::geometry::output_triangle_vertices(
                                temp_vertices,
                                temp_UVs,
                                temp_normals,
                                vertex_index,
                                uv_index,
                                normal_index,
                                out_vertices,
                                out_UVs,
                                out_normals);
                    }
                }
            }
            else if (is_southeast_northwest_edges_in_use)
            {
                if (temp_vertices.size() != actual_image_width * actual_image_height)
                {
                    // If number of face normals is not width * height, then the number of vertices is incorrect.
                    return false;
                }

                // Face indices example for a 4x4 image file using southeast-northwest edges.
                //
                // +---+---+---+
                // |\13|\15|\17|
                // | \ | \ | \ |
                // |12\|14\|16\|
                // +---+---+---+
                // |\ 7|\ 9|\11|
                // | \ | \ | \ |
                // |6 \|8 \|10\|
                // +---+---+---+
                // |\ 1|\ 3|\ 5|
                // | \ | \ | \ |
                // |0 \|2 \|4 \|
                // +---+---+---+
                // southeast northwest edges.

                for (std::size_t z = 1; z < actual_image_height; z++)
                {
                    for (std::size_t x = 1; x < actual_image_width; x++)
                    {
                        std::size_t current_vertex_i = actual_image_width * z + x;

                        GLuint vertex_index[3];
                        GLuint uv_index[3];
                        GLuint normal_index[3];

                        // This corresponds to "vn": specify normal of one vertex.

                        // Then, define the triangles (2 faces).
                        // Triangle order: SW - NE.
                        //
                        // First triangle: southwest, northwest, southeast.
                        // Second triangle: northeast, southeast, northwest.

                        // Define the first triangle, SW: southwest, northwest, southeast.
                        vertex_index[0] = southwest(current_vertex_i, actual_image_width);
                        vertex_index[1] = northwest(current_vertex_i, actual_image_width);
                        vertex_index[2] = southeast(current_vertex_i, actual_image_width);

                        normal_index[0] = southwest(current_vertex_i, actual_image_width);
                        normal_index[1] = northwest(current_vertex_i, actual_image_width);
                        normal_index[2] = southeast(current_vertex_i, actual_image_width);

                        uv_index[0] = southwest(current_vertex_i, actual_image_width);
                        uv_index[1] = northwest(current_vertex_i, actual_image_width);
                        uv_index[2] = southeast(current_vertex_i, actual_image_width);

                        yli::geometry::output_triangle_vertices(
                                temp_vertices,
                                temp_UVs,
                                temp_normals,
                                vertex_index,
                                uv_index,
                                normal_index,
                                out_vertices,
                                out_UVs,
                                out_normals);

                        // Define the second triangle, NW: northeast, southeast, northwest.
                        vertex_index[0] = northeast(current_vertex_i, actual_image_width);
                        vertex_index[1] = southeast(current_vertex_i, actual_image_width);
                        vertex_index[2] = northwest(current_vertex_i, actual_image_width);

                        normal_index[0] = northeast(current_vertex_i, actual_image_width);
                        normal_index[1] = southeast(current_vertex_i, actual_image_width);
                        normal_index[2] = northwest(current_vertex_i, actual_image_width);

                        uv_index[0] = northeast(current_vertex_i, actual_image_width);
                        uv_index[1] = southeast(current_vertex_i, actual_image_width);
                        uv_index[2] = northwest(current_vertex_i, actual_image_width);

                        yli::geometry::output_triangle_vertices(
                                temp_vertices,
                                temp_UVs,
                                temp_normals,
                                vertex_index,
                                uv_index,
                                normal_index,
                                out_vertices,
                                out_UVs,
                                out_normals);
                    }
                }
            }

            return true;
        }
    }
}
