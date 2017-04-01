#ifndef __QUAD_TRIANGULATION_HPP_INCLUDED
#define __QUAD_TRIANGULATION_HPP_INCLUDED

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

#include "face_normals.hpp"
#include "triangulation_enums.hpp"
#include "triangulation_templates.hpp"
#include "indexing.hpp"
#include "code/ylikuutio/geometry/transformation.hpp"
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
#include <cstring>  // std::memcmp, std::strcmp, std::strlen, std::strncmp
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
            std::vector<glm::vec3>& out_normals);

    template<class T1>
        bool triangulate_quads(
                T1* input_vertex_pointer,
                TriangulateQuadsStruct triangulate_quads_struct,
                std::vector<glm::vec3>& out_vertices,
                std::vector<glm::vec2>& out_UVs,
                std::vector<glm::vec3>& out_normals)
        {
            // Input vertices (`T1* input_vertex_pointer`)
            // can be `float`, `int32_t` or `uint32_t`.
            uint32_t image_width = triangulate_quads_struct.image_width;
            uint32_t image_height = triangulate_quads_struct.image_height;
            std::string triangulation_type = triangulate_quads_struct.triangulation_type;
            double sphere_radius = triangulate_quads_struct.sphere_radius;
            SphericalWorldStruct spherical_world_struct = triangulate_quads_struct.spherical_world_struct;

            const char* char_triangulation_type = triangulation_type.c_str();

            bool is_bilinear_interpolation_in_use = false;
            bool is_southwest_northeast_edges_in_use = false;
            bool is_southeast_northwest_edges_in_use = false;
            bool is_triangulation_type_valid = false;

            if (std::strcmp(char_triangulation_type, "bilinear_interpolation") == 0)
            {
                // *---*
                // |\ /|
                // | * |
                // |/ \|
                // *---*
                is_bilinear_interpolation_in_use = true;
                is_triangulation_type_valid = true;
            }
            else if ((std::strcmp(char_triangulation_type, "southwest_northeast_edges") == 0) || (std::strcmp(char_triangulation_type, "northeast_southwest_edges") == 0))
            {
                // *---*
                // |  /|
                // | / |
                // |/  |
                // *---*
                is_southwest_northeast_edges_in_use = true;
                is_triangulation_type_valid = true;
            }
            else if ((std::strcmp(char_triangulation_type, "southeast_northwest_edges") == 0) || (std::strcmp(char_triangulation_type, "northwest_southeast_edges") == 0))
            {
                // *---*
                // |\  |
                // | \ |
                // |  \|
                // *---*
                is_southeast_northwest_edges_in_use = true;
                is_triangulation_type_valid = true;
            }

            std::cout << "triangulation type in use: " << triangulation_type << "\n";

            if (!is_triangulation_type_valid)
            {
                std::cerr << "invalid triangulation type!\n";
                return false;
            }

            std::vector<GLuint> vertexIndices, uvIndices, normalIndices;
            std::vector<glm::vec3> temp_vertices;
            std::vector<glm::vec2> temp_UVs;
            std::vector<glm::vec3> temp_normals;

            uint32_t texture_x = 0;
            uint32_t texture_y = 0;

            // Processing stages:
            // 1. Define the (GLfloat) vertices for vertices loaded from file, `push_back` to `temp_vertices` and `temp_UVs`.
            // 2. Interpolate the (GLfloat) vertices between, using bilinear interpolation, `push_back` to `temp_vertices` and `temp_UVs`.
            // 3a. Transform spherical coordinates loaded from file (and computed this far as being in horizontal plane) to a curved surface.
            // 3b. For bilinear interpolation: Transform interpolated coordinates (and computed this far as being in horizontal plane) to a curved surface.
            // 4. Compute the face normals, `push_back` to `face_normals`.
            // 5. Compute the vertex normals for vertices loaded from file and for interpolated vertices (for `"bilinear_interpolation"`), `push_back` to `temp_normals`.
            // 6. Loop through all vertices and `geometry::output_triangle_vertices`.
            //
            // stg. `"bilinear_interpolation"`                                      `"southwest_northeast_edges"`               `"southeast_northwest_edges"`
            // 1.   `define_vertices`                                               `define_vertices`                           `define_vertices`
            // 2.   `interpolate_and_define_vertices_using_bilinear_interpolation`  N/A                                         N/A
            // 3.   `transform_coordinates_to_curved_surface`                       `transform_coordinates_to_curved_surface`   `transform_coordinates_to_curved_surface`
            // 4.   not refactored yet                                              not refactored yet                          not refactored yet
            // 5.   not refactored yet                                              not refactored yet                          not refactored yet
            // 6.   not refactored yet                                              not refactored yet                          not refactored yet
            //
            // stg. = stage

            // 1. Define the vertices for vertices loaded from file, `push_back` to `temp_vertices`.

            define_vertices(
                    input_vertex_pointer,
                    image_width,
                    image_height,
                    triangulate_quads_struct.should_ylikuutio_use_real_texture_coordinates,
                    temp_vertices,
                    temp_UVs);

            uint32_t n_faces_for_each_vertex;
            uint32_t n_faces;

            if (is_bilinear_interpolation_in_use)
            {
                n_faces_for_each_vertex = 4;
            }
            else if (is_southwest_northeast_edges_in_use || is_southeast_northwest_edges_in_use)
            {
                n_faces_for_each_vertex = 2;
            }

            n_faces = n_faces_for_each_vertex * (image_width - 1) * (image_height - 1);

            std::cout << "image width: " << image_width << " pixels.\n";
            std::cout << "image height: " << image_height << " pixels.\n";
            std::cout << "number of faces: " << n_faces << ".\n";

            uint32_t vertexIndex[3], uvIndex[3], normalIndex[3];

            if (is_bilinear_interpolation_in_use)
            {
                // 2. Interpolate the vertices between, using bilinear interpolation, `push_back` to `temp_vertices`.
                geometry::interpolate_and_define_vertices_using_bilinear_interpolation(
                        input_vertex_pointer,
                        image_width,
                        image_height,
                        triangulate_quads_struct.should_ylikuutio_use_real_texture_coordinates,
                        temp_vertices,
                        temp_UVs);
            }

            if (!std::isnan(sphere_radius))
            {
                // 3a. Transform spherical coordinates loaded from file (and computed this far as being in horizontal plane) to a curved surface.
                // 3b. For bilinear interpolation: Transform interpolated coordinates (and computed this far as being in horizontal plane) to a curved surface.
                //
                // Wikipedia:
                // https://en.wikipedia.org/wiki/List_of_common_coordinate_transformations#From_spherical_coordinates
                //
                // x = rho * sin(theta) * cos(phi)
                // y = rho * sin(theta) * sin(phi)
                // z = rho * cos(theta)

                TransformationStruct transformation_struct;
                transformation_struct.image_width = image_width;
                transformation_struct.image_height = image_height;
                transformation_struct.sphere_radius = sphere_radius;
                transformation_struct.is_bilinear_interpolation_in_use = is_bilinear_interpolation_in_use;
                transformation_struct.spherical_world_struct = spherical_world_struct;
                geometry::transform_coordinates_to_curved_surface(transformation_struct, temp_vertices);
            }
            else
            {
                std::cout << "no coordinate transformation is needed.\n";
            }

            // 4. Compute the face normals, `push_back` to `face_normals`.
            // Triangle order: S - W - N - E.
            //
            // First triangle: center, southeast, southwest.
            // Second triangle: center, southwest, northwest.
            // Third triangle: center, northwest, northeast.
            // Fourth triangle: center, northeast, southeast.
            std::cout << "computing face normals.\n";

            std::vector<glm::vec3> face_normal_vector_vec3;

            if (!compute_face_normals(
                        temp_vertices,
                        face_normal_vector_vec3,
                        image_width,
                        image_height,
                        is_bilinear_interpolation_in_use,
                        is_southwest_northeast_edges_in_use,
                        is_southeast_northwest_edges_in_use))
            {
                return false;
            }

            // 5. Compute the vertex normals for vertices loaded from file, `push_back` to `temp_normals`.
            std::cout << "computing vertex normals for vertices loaded from file.\n";

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
                for (x = 1; x < (image_width - 1); x++)
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
                for (z = 1; z < (image_height - 1); z++)
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

                    for (x = 1; x < (image_width - 1); x++)
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
                for (x = 1; x < (image_width - 1); x++)
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
                std::cout << "computing vertex normals for interpolated vertices.\n";

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
                for (x = 1; x < (image_width - 1); x++)
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
                for (z = 1; z < (image_height - 1); z++)
                {
                    // Compute the normal of a western vertex.
                    // Number of adjacent faces: 3.
                    x = 0;
                    vertex_normal = glm::normalize(
                            get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, NE_CODE_FOR_SE_NW, image_width) +
                            get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, ESE_CODE_FOR_SE_NW, image_width) +
                            get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, SSE_CODE_FOR_SE_NW, image_width));
                    temp_normals.push_back(vertex_normal);

                    for (x = 1; x < (image_width - 1); x++)
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
                for (x = 1; x < (image_width - 1); x++)
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

            // 6. Loop through all vertices and `geometry::output_triangle_vertices`.
            std::cout << "defining output vertices, UVs and normals.\n";

            if (is_bilinear_interpolation_in_use)
            {
                uint32_t triangle_i = 0;
                uint32_t current_interpolated_vertex_i = image_width * image_height;

                for (uint32_t z = 1; z < image_height; z++)
                {
                    // show progress in percents.
                    int32_t current_percent = static_cast<int32_t>(floor(100.0f * ((double) z / (double) (image_height - 1))));
                    std::cout << current_percent << "% ";

                    for (uint32_t x = 1; x < image_width; x++)
                    {
                        uint32_t current_vertex_i = image_width * z + x;

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
                        vertexIndex[1] = southeast(current_vertex_i, image_width);
                        vertexIndex[2] = southwest(current_vertex_i, image_width);

                        normalIndex[0] = current_interpolated_vertex_i;
                        normalIndex[1] = southeast(current_vertex_i, image_width);
                        normalIndex[2] = southwest(current_vertex_i, image_width);

                        if (triangulate_quads_struct.should_ylikuutio_use_real_texture_coordinates)
                        {
                            uvIndex[0] = current_interpolated_vertex_i;
                            uvIndex[1] = southeast(current_vertex_i, image_width);
                            uvIndex[2] = southwest(current_vertex_i, image_width);
                        }
                        else
                        {
                            // Use altitude as texture coordinate (useful for elevation maps).
                            uvIndex[0] = static_cast<GLuint>(center_y(x, z, input_vertex_pointer, image_width));
                            uvIndex[1] = static_cast<GLuint>(southeast_y(x, z, input_vertex_pointer, image_width));
                            uvIndex[2] = static_cast<GLuint>(southwest_y(x, z, input_vertex_pointer, image_width));
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
                        vertexIndex[1] = southwest(current_vertex_i, image_width);
                        vertexIndex[2] = northwest(current_vertex_i, image_width);

                        normalIndex[0] = current_interpolated_vertex_i;
                        normalIndex[1] = southwest(current_vertex_i, image_width);
                        normalIndex[2] = northwest(current_vertex_i, image_width);

                        if (triangulate_quads_struct.should_ylikuutio_use_real_texture_coordinates)
                        {
                            uvIndex[0] = current_interpolated_vertex_i;
                            uvIndex[1] = southwest(current_vertex_i, image_width);
                            uvIndex[2] = northwest(current_vertex_i, image_width);
                        }
                        else
                        {
                            // Use altitude as texture coordinate (useful for elevation maps).
                            uvIndex[0] = static_cast<GLuint>(center_y(x, z, input_vertex_pointer, image_width));
                            uvIndex[1] = static_cast<GLuint>(southwest_y(x, z, input_vertex_pointer, image_width));
                            uvIndex[2] = static_cast<GLuint>(northwest_y(x, z, input_vertex_pointer, image_width));
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
                        vertexIndex[1] = northwest(current_vertex_i, image_width);
                        vertexIndex[2] = northeast(current_vertex_i, image_width);

                        normalIndex[0] = current_interpolated_vertex_i;
                        normalIndex[1] = northwest(current_vertex_i, image_width);
                        normalIndex[2] = northeast(current_vertex_i, image_width);

                        if (triangulate_quads_struct.should_ylikuutio_use_real_texture_coordinates)
                        {
                            uvIndex[0] = current_interpolated_vertex_i;
                            uvIndex[1] = northwest(current_vertex_i, image_width);
                            uvIndex[2] = northeast(current_vertex_i, image_width);
                        }
                        else
                        {
                            // Use altitude as texture coordinate (useful for elevation maps).
                            uvIndex[0] = static_cast<GLuint>(center_y(x, z, input_vertex_pointer, image_width));
                            uvIndex[1] = static_cast<GLuint>(northwest_y(x, z, input_vertex_pointer, image_width));
                            uvIndex[2] = static_cast<GLuint>(northeast_y(x, z, input_vertex_pointer, image_width));
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
                        vertexIndex[1] = northeast(current_vertex_i, image_width);
                        vertexIndex[2] = southeast(current_vertex_i, image_width);

                        normalIndex[0] = current_interpolated_vertex_i;
                        normalIndex[1] = northeast(current_vertex_i, image_width);
                        normalIndex[2] = southeast(current_vertex_i, image_width);

                        if (triangulate_quads_struct.should_ylikuutio_use_real_texture_coordinates)
                        {
                            uvIndex[0] = current_interpolated_vertex_i;
                            uvIndex[1] = northeast(current_vertex_i, image_width);
                            uvIndex[2] = southeast(current_vertex_i, image_width);
                        }
                        else
                        {
                            // Use altitude as texture coordinate (useful for elevation maps).
                            uvIndex[0] = static_cast<GLuint>(center_y(x, z, input_vertex_pointer, image_width));
                            uvIndex[1] = static_cast<GLuint>(northeast_y(x, z, input_vertex_pointer, image_width));
                            uvIndex[2] = static_cast<GLuint>(southeast_y(x, z, input_vertex_pointer, image_width));
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
                std::cout << "\n"; // a newline after percent progress meter.
            }
            else if (is_southwest_northeast_edges_in_use)
            {
                // TODO: define output vertices, UVs and normals for `"southwest_northeast_edges"`.
            }
            else if (is_southeast_northwest_edges_in_use)
            {
                uint32_t x;
                uint32_t z;

                uint32_t triangle_i = 0;

                for (z = 1; z < image_height; z++)
                {
                    for (x = 1; x < image_width; x++)
                    {
                        uint32_t current_vertex_i = image_width * z + x;

                        // This corresponds to "vn": specify normal of one vertex.

                        // Then, define the triangles (2 faces).
                        // Triangle order: SW - NE.
                        //
                        // First triangle: southwest, northwest, southeast.
                        // Second triangle: northeast, southeast, northwest.

                        // Define the first triangle, SW: southwest, northwest, southeast.
                        vertexIndex[0] = southwest(current_vertex_i, image_width);
                        vertexIndex[1] = northwest(current_vertex_i, image_width);
                        vertexIndex[2] = southeast(current_vertex_i, image_width);

                        normalIndex[0] = southwest(current_vertex_i, image_width);
                        normalIndex[1] = northwest(current_vertex_i, image_width);
                        normalIndex[2] = southeast(current_vertex_i, image_width);

                        if (triangulate_quads_struct.should_ylikuutio_use_real_texture_coordinates)
                        {
                            uvIndex[0] = southwest(current_vertex_i, image_width);
                            uvIndex[1] = northwest(current_vertex_i, image_width);
                            uvIndex[2] = southeast(current_vertex_i, image_width);
                        }
                        else
                        {
                            // Use altitude as texture coordinate (useful for elevation maps).
                            uvIndex[0] = static_cast<GLuint>(southwest_y(x, z, input_vertex_pointer, image_width));
                            uvIndex[1] = static_cast<GLuint>(northwest_y(x, z, input_vertex_pointer, image_width));
                            uvIndex[2] = static_cast<GLuint>(southeast_y(x, z, input_vertex_pointer, image_width));
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
                        vertexIndex[0] = northeast(current_vertex_i, image_width);
                        vertexIndex[1] = southeast(current_vertex_i, image_width);
                        vertexIndex[2] = northwest(current_vertex_i, image_width);

                        normalIndex[0] = northeast(current_vertex_i, image_width);
                        normalIndex[1] = southeast(current_vertex_i, image_width);
                        normalIndex[2] = northwest(current_vertex_i, image_width);

                        if (triangulate_quads_struct.should_ylikuutio_use_real_texture_coordinates)
                        {
                            uvIndex[0] = northeast(current_vertex_i, image_width);
                            uvIndex[1] = southeast(current_vertex_i, image_width);
                            uvIndex[2] = northwest(current_vertex_i, image_width);
                        }
                        else
                        {
                            // Use altitude as texture coordinate (useful for elevation maps).
                            uvIndex[0] = static_cast<GLuint>(northeast_y(x, z, input_vertex_pointer, image_width));
                            uvIndex[1] = static_cast<GLuint>(southeast_y(x, z, input_vertex_pointer, image_width));
                            uvIndex[2] = static_cast<GLuint>(northwest_y(x, z, input_vertex_pointer, image_width));
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
            std::cout << "number of vertices: " << out_vertices.size() << ".\n";
            std::cout << "number of UVs: " << out_UVs.size() << ".\n";
            std::cout << "number of normals: " << out_normals.size() << ".\n";

            return true;
        }
}

#endif
