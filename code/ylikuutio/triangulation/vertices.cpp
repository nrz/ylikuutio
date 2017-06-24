#include "vertices.hpp"
#include "indexing.hpp"
#include "code/ylikuutio/common/globals.hpp"

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
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace geometry
{
    void output_triangle_vertices(
            std::vector<glm::vec3>& temp_vertices,
            std::vector<glm::vec2>& temp_UVs,
            std::vector<glm::vec3>& temp_normals,
            GLuint vertexIndex[3],
            GLuint uvIndex[3],
            GLuint normalIndex[3],
            std::vector<glm::vec3>& out_vertices,
            std::vector<glm::vec2>& out_UVs,
            std::vector<glm::vec3>& out_normals)
    {
        out_vertices.push_back(temp_vertices[vertexIndex[0]]);
        out_UVs.push_back(temp_UVs[uvIndex[0]]);
        out_normals.push_back(temp_normals[normalIndex[0]]);

        out_vertices.push_back(temp_vertices[vertexIndex[1]]);
        out_UVs.push_back(temp_UVs[uvIndex[1]]);
        out_normals.push_back(temp_normals[normalIndex[1]]);

        out_vertices.push_back(temp_vertices[vertexIndex[2]]);
        out_UVs.push_back(temp_UVs[uvIndex[2]]);
        out_normals.push_back(temp_normals[normalIndex[2]]);
    }

    bool define_vertices_UVs_and_normals(
            const TriangulateQuadsStruct triangulate_quads_struct,
            std::vector<glm::vec3>& temp_vertices,
            std::vector<glm::vec2>& temp_UVs,
            std::vector<glm::vec3>& temp_normals,
            GLuint vertexIndex[3],
            GLuint uvIndex[3],
            GLuint normalIndex[3],
            std::vector<glm::vec3>& out_vertices,
            std::vector<glm::vec2>& out_UVs,
            std::vector<glm::vec3>& out_normals,
            const int32_t actual_image_width,
            const int32_t actual_image_height,
            const bool is_bilinear_interpolation_in_use,
            const bool is_southwest_northeast_edges_in_use,
            const bool is_southeast_northwest_edges_in_use)
    {
        // 6. Loop through all vertices and `geometry::output_triangle_vertices`.

        if (actual_image_width < 2 || actual_image_height < 2)
        {
            // If width or height is < 2, there are no faces.
            return false;
        }

        if (is_bilinear_interpolation_in_use)
        {
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

            uint32_t triangle_i = 0;
            uint32_t current_interpolated_vertex_i = actual_image_width * actual_image_height;

            for (uint32_t z = 1; z < actual_image_height; z++)
            {
                // show progress in percents.
                int32_t current_percent = static_cast<int32_t>(floor(100.0f * ((double) z / (double) (actual_image_height - 1))));
                // std::cout << current_percent << "% ";

                for (uint32_t x = 1; x < actual_image_width; x++)
                {
                    uint32_t current_vertex_i = actual_image_width * z + x;

                    // This corresponds to "vn": specify normal of one vertex.

                    // Then, define the triangles (4 faces).
                    // Triangle order: S - W - N - E.
                    //
                    // First triangle: center, southeast, southwest.
                    // Second triangle: center, southwest, northwest.
                    // Third triangle: center, northwest, northeast.
                    // Fourth triangle: center, northeast, southeast.

                    // Define the first triangle, S: center, southeast, southwest.
                    vertexIndex[0] = current_interpolated_vertex_i;
                    vertexIndex[1] = southeast(current_vertex_i, actual_image_width);
                    vertexIndex[2] = southwest(current_vertex_i, actual_image_width);

                    normalIndex[0] = current_interpolated_vertex_i;
                    normalIndex[1] = southeast(current_vertex_i, actual_image_width);
                    normalIndex[2] = southwest(current_vertex_i, actual_image_width);

                    if (triangulate_quads_struct.should_ylikuutio_use_real_texture_coordinates)
                    {
                        uvIndex[0] = current_interpolated_vertex_i;
                        uvIndex[1] = southeast(current_vertex_i, actual_image_width);
                        uvIndex[2] = southwest(current_vertex_i, actual_image_width);
                    }
                    else
                    {
                        // Use altitude as texture coordinate (useful for elevation maps).
                        // uvIndex[0] = static_cast<GLuint>(center_y(x, z, input_vertex_pointer, actual_image_width));
                        // uvIndex[1] = static_cast<GLuint>(southeast_y(x, z, input_vertex_pointer, actual_image_width));
                        // uvIndex[2] = static_cast<GLuint>(southwest_y(x, z, input_vertex_pointer, actual_image_width));
                    }

                    geometry::output_triangle_vertices(
                            temp_vertices,
                            temp_UVs,
                            temp_normals,
                            vertexIndex,
                            uvIndex,
                            normalIndex,
                            out_vertices,
                            out_UVs,
                            out_normals);

                    // Define the second triangle, W: center, southwest, northwest.
                    vertexIndex[0] = current_interpolated_vertex_i;
                    vertexIndex[1] = southwest(current_vertex_i, actual_image_width);
                    vertexIndex[2] = northwest(current_vertex_i, actual_image_width);

                    normalIndex[0] = current_interpolated_vertex_i;
                    normalIndex[1] = southwest(current_vertex_i, actual_image_width);
                    normalIndex[2] = northwest(current_vertex_i, actual_image_width);

                    if (triangulate_quads_struct.should_ylikuutio_use_real_texture_coordinates)
                    {
                        uvIndex[0] = current_interpolated_vertex_i;
                        uvIndex[1] = southwest(current_vertex_i, actual_image_width);
                        uvIndex[2] = northwest(current_vertex_i, actual_image_width);
                    }
                    else
                    {
                        // Use altitude as texture coordinate (useful for elevation maps).
                        // uvIndex[0] = static_cast<GLuint>(center_y(x, z, input_vertex_pointer, actual_image_width));
                        // uvIndex[1] = static_cast<GLuint>(southwest_y(x, z, input_vertex_pointer, actual_image_width));
                        // uvIndex[2] = static_cast<GLuint>(northwest_y(x, z, input_vertex_pointer, actual_image_width));
                    }

                    geometry::output_triangle_vertices(
                            temp_vertices,
                            temp_UVs,
                            temp_normals,
                            vertexIndex,
                            uvIndex,
                            normalIndex,
                            out_vertices,
                            out_UVs,
                            out_normals);

                    // Define the third triangle, N: center, northwest, northeast.
                    vertexIndex[0] = current_interpolated_vertex_i;
                    vertexIndex[1] = northwest(current_vertex_i, actual_image_width);
                    vertexIndex[2] = northeast(current_vertex_i, actual_image_width);

                    normalIndex[0] = current_interpolated_vertex_i;
                    normalIndex[1] = northwest(current_vertex_i, actual_image_width);
                    normalIndex[2] = northeast(current_vertex_i, actual_image_width);

                    if (triangulate_quads_struct.should_ylikuutio_use_real_texture_coordinates)
                    {
                        uvIndex[0] = current_interpolated_vertex_i;
                        uvIndex[1] = northwest(current_vertex_i, actual_image_width);
                        uvIndex[2] = northeast(current_vertex_i, actual_image_width);
                    }
                    else
                    {
                        // Use altitude as texture coordinate (useful for elevation maps).
                        // uvIndex[0] = static_cast<GLuint>(center_y(x, z, input_vertex_pointer, actual_image_width));
                        // uvIndex[1] = static_cast<GLuint>(northwest_y(x, z, input_vertex_pointer, actual_image_width));
                        // uvIndex[2] = static_cast<GLuint>(northeast_y(x, z, input_vertex_pointer, actual_image_width));
                    }

                    geometry::output_triangle_vertices(
                            temp_vertices,
                            temp_UVs,
                            temp_normals,
                            vertexIndex,
                            uvIndex,
                            normalIndex,
                            out_vertices,
                            out_UVs,
                            out_normals);

                    // Define the fourth triangle, E: center, northeast, southeast.
                    vertexIndex[0] = current_interpolated_vertex_i;
                    vertexIndex[1] = northeast(current_vertex_i, actual_image_width);
                    vertexIndex[2] = southeast(current_vertex_i, actual_image_width);

                    normalIndex[0] = current_interpolated_vertex_i;
                    normalIndex[1] = northeast(current_vertex_i, actual_image_width);
                    normalIndex[2] = southeast(current_vertex_i, actual_image_width);

                    if (triangulate_quads_struct.should_ylikuutio_use_real_texture_coordinates)
                    {
                        uvIndex[0] = current_interpolated_vertex_i;
                        uvIndex[1] = northeast(current_vertex_i, actual_image_width);
                        uvIndex[2] = southeast(current_vertex_i, actual_image_width);
                    }
                    else
                    {
                        // Use altitude as texture coordinate (useful for elevation maps).
                        // uvIndex[0] = static_cast<GLuint>(center_y(x, z, input_vertex_pointer, actual_image_width));
                        // uvIndex[1] = static_cast<GLuint>(northeast_y(x, z, input_vertex_pointer, actual_image_width));
                        // uvIndex[2] = static_cast<GLuint>(southeast_y(x, z, input_vertex_pointer, actual_image_width));
                    }

                    geometry::output_triangle_vertices(
                            temp_vertices,
                            temp_UVs,
                            temp_normals,
                            vertexIndex,
                            uvIndex,
                            normalIndex,
                            out_vertices,
                            out_UVs,
                            out_normals);

                    current_interpolated_vertex_i++;
                }
            }
            // std::cout << "\n"; // a newline after percent progress meter.
        }
        else if (is_southwest_northeast_edges_in_use)
        {
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

            uint32_t x;
            uint32_t z;

            uint32_t triangle_i = 0;

            for (z = 1; z < actual_image_height; z++)
            {
                for (x = 1; x < actual_image_width; x++)
                {
                    uint32_t current_vertex_i = actual_image_width * z + x;

                    // This corresponds to "vn": specify normal of one vertex.

                    // Then, define the triangles (2 faces).
                    // Triangle order: SE - NW.
                    //
                    // First triangle: southeast, southwest, northeast.
                    // Second triangle: northwest, northeast, southwest.

                    // Define the first triangle, SE: southeast, southwest, northeast.
                    vertexIndex[0] = southeast(current_vertex_i, actual_image_width);
                    vertexIndex[1] = southwest(current_vertex_i, actual_image_width);
                    vertexIndex[2] = northeast(current_vertex_i, actual_image_width);

                    normalIndex[0] = southeast(current_vertex_i, actual_image_width);
                    normalIndex[1] = southwest(current_vertex_i, actual_image_width);
                    normalIndex[2] = northeast(current_vertex_i, actual_image_width);

                    if (triangulate_quads_struct.should_ylikuutio_use_real_texture_coordinates)
                    {
                        uvIndex[0] = southeast(current_vertex_i, actual_image_width);
                        uvIndex[1] = southwest(current_vertex_i, actual_image_width);
                        uvIndex[2] = northeast(current_vertex_i, actual_image_width);
                    }
                    else
                    {
                        // Use altitude as texture coordinate (useful for elevation maps).
                        // uvIndex[0] = static_cast<GLuint>(southeast_y(x, z, input_vertex_pointer, actual_image_width));
                        // uvIndex[1] = static_cast<GLuint>(southwest_y(x, z, input_vertex_pointer, actual_image_width));
                        // uvIndex[2] = static_cast<GLuint>(northeast_y(x, z, input_vertex_pointer, actual_image_width));
                    }

                    geometry::output_triangle_vertices(
                            temp_vertices,
                            temp_UVs,
                            temp_normals,
                            vertexIndex,
                            uvIndex,
                            normalIndex,
                            out_vertices,
                            out_UVs,
                            out_normals);

                    // Define the second triangle, NW: northwest, northeast, southwest.
                    vertexIndex[0] = northwest(current_vertex_i, actual_image_width);
                    vertexIndex[1] = northeast(current_vertex_i, actual_image_width);
                    vertexIndex[2] = southwest(current_vertex_i, actual_image_width);

                    normalIndex[0] = northwest(current_vertex_i, actual_image_width);
                    normalIndex[1] = northeast(current_vertex_i, actual_image_width);
                    normalIndex[2] = southwest(current_vertex_i, actual_image_width);

                    if (triangulate_quads_struct.should_ylikuutio_use_real_texture_coordinates)
                    {
                        uvIndex[0] = northwest(current_vertex_i, actual_image_width);
                        uvIndex[1] = northeast(current_vertex_i, actual_image_width);
                        uvIndex[2] = southwest(current_vertex_i, actual_image_width);
                    }
                    else
                    {
                        // Use altitude as texture coordinate (useful for elevation maps).
                        // uvIndex[0] = static_cast<GLuint>(northwest_y(x, z, input_vertex_pointer, actual_image_width));
                        // uvIndex[1] = static_cast<GLuint>(northeast_y(x, z, input_vertex_pointer, actual_image_width));
                        // uvIndex[2] = static_cast<GLuint>(southwest_y(x, z, input_vertex_pointer, actual_image_width));
                    }

                    geometry::output_triangle_vertices(
                            temp_vertices,
                            temp_UVs,
                            temp_normals,
                            vertexIndex,
                            uvIndex,
                            normalIndex,
                            out_vertices,
                            out_UVs,
                            out_normals);
                }
            }
        }
        else if (is_southeast_northwest_edges_in_use)
        {
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

            uint32_t x;
            uint32_t z;

            uint32_t triangle_i = 0;

            for (z = 1; z < actual_image_height; z++)
            {
                for (x = 1; x < actual_image_width; x++)
                {
                    uint32_t current_vertex_i = actual_image_width * z + x;

                    // This corresponds to "vn": specify normal of one vertex.

                    // Then, define the triangles (2 faces).
                    // Triangle order: SW - NE.
                    //
                    // First triangle: southwest, northwest, southeast.
                    // Second triangle: northeast, southeast, northwest.

                    // Define the first triangle, SW: southwest, northwest, southeast.
                    vertexIndex[0] = southwest(current_vertex_i, actual_image_width);
                    vertexIndex[1] = northwest(current_vertex_i, actual_image_width);
                    vertexIndex[2] = southeast(current_vertex_i, actual_image_width);

                    normalIndex[0] = southwest(current_vertex_i, actual_image_width);
                    normalIndex[1] = northwest(current_vertex_i, actual_image_width);
                    normalIndex[2] = southeast(current_vertex_i, actual_image_width);

                    if (triangulate_quads_struct.should_ylikuutio_use_real_texture_coordinates)
                    {
                        uvIndex[0] = southwest(current_vertex_i, actual_image_width);
                        uvIndex[1] = northwest(current_vertex_i, actual_image_width);
                        uvIndex[2] = southeast(current_vertex_i, actual_image_width);
                    }
                    else
                    {
                        // Use altitude as texture coordinate (useful for elevation maps).
                        // uvIndex[0] = static_cast<GLuint>(southwest_y(x, z, input_vertex_pointer, actual_image_width));
                        // uvIndex[1] = static_cast<GLuint>(northwest_y(x, z, input_vertex_pointer, actual_image_width));
                        // uvIndex[2] = static_cast<GLuint>(southeast_y(x, z, input_vertex_pointer, actual_image_width));
                    }

                    geometry::output_triangle_vertices(
                            temp_vertices,
                            temp_UVs,
                            temp_normals,
                            vertexIndex,
                            uvIndex,
                            normalIndex,
                            out_vertices,
                            out_UVs,
                            out_normals);

                    // Define the second triangle, NW: northeast, southeast, northwest.
                    vertexIndex[0] = northeast(current_vertex_i, actual_image_width);
                    vertexIndex[1] = southeast(current_vertex_i, actual_image_width);
                    vertexIndex[2] = northwest(current_vertex_i, actual_image_width);

                    normalIndex[0] = northeast(current_vertex_i, actual_image_width);
                    normalIndex[1] = southeast(current_vertex_i, actual_image_width);
                    normalIndex[2] = northwest(current_vertex_i, actual_image_width);

                    if (triangulate_quads_struct.should_ylikuutio_use_real_texture_coordinates)
                    {
                        uvIndex[0] = northeast(current_vertex_i, actual_image_width);
                        uvIndex[1] = southeast(current_vertex_i, actual_image_width);
                        uvIndex[2] = northwest(current_vertex_i, actual_image_width);
                    }
                    else
                    {
                        // Use altitude as texture coordinate (useful for elevation maps).
                        // uvIndex[0] = static_cast<GLuint>(northeast_y(x, z, input_vertex_pointer, actual_image_width));
                        // uvIndex[1] = static_cast<GLuint>(southeast_y(x, z, input_vertex_pointer, actual_image_width));
                        // uvIndex[2] = static_cast<GLuint>(northwest_y(x, z, input_vertex_pointer, actual_image_width));
                    }

                    geometry::output_triangle_vertices(
                            temp_vertices,
                            temp_UVs,
                            temp_normals,
                            vertexIndex,
                            uvIndex,
                            normalIndex,
                            out_vertices,
                            out_UVs,
                            out_normals);
                }
            }
        }

        return true;
    }
}
