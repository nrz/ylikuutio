#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

// Include standard headers
#include <iostream>
#include <string>
#include <string.h>
#include <cstring>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // uint32_t etc.
#include <sstream>  // stringstream etc.
#include <iomanip>  // setw, setfill etc.

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h>
#endif

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp>
#endif

#include "globals.hpp"
#include "heightmap_loader.hpp"

#define SRTM_FILENAME_N_OF_LATITUDE_CHARS 2
#define SRTM_FILENAME_N_OF_LONGITUDE_CHARS 3

// #define USE_HEIGHT_AS_TEXTURE_COORDINATE
#define USE_REAL_TEXTURE_COORDINATES

// for bilinear interpolation.
#define SSW_CODE 0
#define WSW_CODE 1
#define WNW_CODE 2
#define NNW_CODE 3
#define NNE_CODE 4
#define ENE_CODE 5
#define ESE_CODE 6
#define SSE_CODE 7

// for southeast-northwest edges.
#define SSE_CODE_FOR_SE_NW 0
#define WNW_CODE_FOR_SE_NW 1
#define ESE_CODE_FOR_SE_NW 2
#define NNW_CODE_FOR_SE_NW 3
#define SW_CODE_FOR_SE_NW 4
#define NE_CODE_FOR_SE_NW 5

// for bilinear interpolation, southeast-northwest edges, and southwest-northeast edges.
#define SOUTHWEST (current_vertex_i - image_width - 1)
#define SOUTHEAST (current_vertex_i - image_width)
#define NORTHWEST (current_vertex_i - 1)
#define NORTHEAST (current_vertex_i)
// for bilinear interpolation.
#define CENTER (current_interpolated_vertex_i)

// for bilinear interpolation.
#define SOUTHWEST_Y (model::get_y(input_vertex_pointer, x - 1, z - 1, image_width))
#define SOUTHEAST_Y (model::get_y(input_vertex_pointer, x, z - 1, image_width))
#define NORTHWEST_Y (model::get_y(input_vertex_pointer, x - 1, z, image_width))
#define NORTHEAST_Y (model::get_y(input_vertex_pointer, x, z, image_width))
#define CENTER_Y ((SOUTHWEST_Y + SOUTHEAST_Y + NORTHWEST_Y + NORTHEAST_Y) / 4)

// for bilinear interpolation.
#define SSW_FACE_NORMAL (model::get_face_normal(face_normal_vector_vec3, x, z, SSW_CODE, image_width))
#define WSW_FACE_NORMAL (model::get_face_normal(face_normal_vector_vec3, x, z, WSW_CODE, image_width))
#define WNW_FACE_NORMAL (model::get_face_normal(face_normal_vector_vec3, x, z, WNW_CODE, image_width))
#define NNW_FACE_NORMAL (model::get_face_normal(face_normal_vector_vec3, x, z, NNW_CODE, image_width))
#define NNE_FACE_NORMAL (model::get_face_normal(face_normal_vector_vec3, x, z, NNE_CODE, image_width))
#define ENE_FACE_NORMAL (model::get_face_normal(face_normal_vector_vec3, x, z, ENE_CODE, image_width))
#define ESE_FACE_NORMAL (model::get_face_normal(face_normal_vector_vec3, x, z, ESE_CODE, image_width))
#define SSE_FACE_NORMAL (model::get_face_normal(face_normal_vector_vec3, x, z, SSE_CODE, image_width))

// for bilinear interpolation.
#define S_FACE_NORMAL (model::get_face_normal(face_normal_vector_vec3, x - 1, z - 1, ENE_CODE, image_width))
#define W_FACE_NORMAL (model::get_face_normal(face_normal_vector_vec3, x - 1, z - 1, NNE_CODE, image_width))
#define N_FACE_NORMAL (model::get_face_normal(face_normal_vector_vec3, x, z, WSW_CODE, image_width))
#define E_FACE_NORMAL (model::get_face_normal(face_normal_vector_vec3, x, z, SSW_CODE, image_width))

// for southeast-northwest edges.
#define SSE_FACE_NORMAL_FOR_SE_NW (model::get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, SSE_CODE_FOR_SE_NW, image_width))
#define WNW_FACE_NORMAL_FOR_SE_NW (model::get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, WNW_CODE_FOR_SE_NW, image_width))
#define ESE_FACE_NORMAL_FOR_SE_NW (model::get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, ESE_CODE_FOR_SE_NW, image_width))
#define NNW_FACE_NORMAL_FOR_SE_NW (model::get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, NNW_CODE_FOR_SE_NW, image_width))
#define SW_FACE_NORMAL_FOR_SE_NW (model::get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, SW_CODE_FOR_SE_NW, image_width))
#define NE_FACE_NORMAL_FOR_SE_NW (model::get_face_normal_for_SE_NW(face_normal_vector_vec3, x, z, NE_CODE_FOR_SE_NW, image_width))

namespace model
{
    // for bilinear interpolation.
    glm::vec3 get_face_normal(
            std::vector<glm::vec3> &face_normal_data,
            uint32_t x,
            uint32_t z,
            uint32_t compass_point_code,
            uint32_t image_width)
    {
        uint32_t face_normal_i;

        switch (compass_point_code)
        {
            case SSW_CODE:
                face_normal_i = 4 * (z - 1) * (image_width - 1) + (4 * x) - 1;
                break;
            case WSW_CODE:
                face_normal_i = 4 * (z - 1) * (image_width - 1) + (4 * x) - 2;
                break;
            case WNW_CODE:
                face_normal_i = 4 * z * (image_width - 1) + (4 * x) - 4;
                break;
            case NNW_CODE:
                face_normal_i = 4 * z * (image_width - 1) + (4 * x) - 1;
                break;
            case NNE_CODE:
                face_normal_i = 4 * z * (image_width - 1) + (4 * x) + 1;
                break;
            case ENE_CODE:
                face_normal_i = 4 * z * (image_width - 1) + (4 * x);
                break;
            case ESE_CODE:
                face_normal_i = 4 * (z - 1) * (image_width - 1) + (4 * x) + 2;
                break;
            case SSE_CODE:
                face_normal_i = 4 * (z - 1) * (image_width - 1) + (4 * x) + 1;
                break;
            default:
                std::cerr << "invalid compass point code!\n";
        }
        return face_normal_data[face_normal_i];
    }

    // Face indices example for a 4x4 image file and bilinear interpolation.
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
    //  |\  3  /|\  6  /|\ 10  /|
    //  | \   / | \   / | \   / |
    //  |  \ /  |  \ /  |  \ /  |
    //  |1  x  2|5  x  7|9  x 11|
    //  |  / \  |  / \  |  / \  |
    //  | /   \ | /   \ | /   \ |
    //  |/  0  \|/  4  \|/  8  \|
    //  +-------+-------+-------+

    // for southeast-northwest edges.
    glm::vec3 get_face_normal_for_SE_NW(
            std::vector<glm::vec3> &face_normal_data,
            uint32_t x,
            uint32_t z,
            uint32_t compass_point_code,
            uint32_t image_width)
    {
        uint32_t face_normal_i;

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
                face_normal_i = 2 * (z - 1) * (image_width - 1) + 2 * (x - 1) + 1;
                break;
            case NE_CODE_FOR_SE_NW:
                face_normal_i = 2 * z * (image_width - 1) + 2 * x;
                break;
            default:
                std::cerr << "invalid compass point code!\n";
        }
        return face_normal_data[face_normal_i];
    }

    GLuint get_y(
            GLuint *vertex_data,
            uint32_t x,
            uint32_t z,
            uint32_t image_width)
    {
        GLuint *vertex_pointer;
        vertex_pointer = vertex_data + z * image_width + x;
        return *vertex_pointer;
    }

    glm::vec3 transform_planar_world_vertex_into_cartesian_vertex(
            glm::vec3 planar_world_vertex,
            GLfloat sphere_radius)
    {
        SphericalCoordinatesStruct spherical_vertex;
        spherical_vertex.rho = planar_world_vertex.y;   // rho is altitude.
        // spherical_vertex.rho += sphere_radius;
        spherical_vertex.theta = planar_world_vertex.z; // theta is latitude.
        spherical_vertex.phi = planar_world_vertex.x;   // phi is longitude.

        glm::vec3 cartesian_vertex;
        cartesian_vertex.x = spherical_vertex.rho * sin(spherical_vertex.theta) * cos(spherical_vertex.phi);
        cartesian_vertex.y = spherical_vertex.rho * sin(spherical_vertex.theta) * sin(spherical_vertex.phi);
        cartesian_vertex.z = spherical_vertex.rho * cos(spherical_vertex.theta);
        return cartesian_vertex;
    };

    uint32_t output_triangle_vertices(
            std::vector<glm::vec3> &temp_vertices,
            std::vector<glm::vec2> &temp_UVs,
            std::vector<glm::vec3> &temp_normals,
            GLuint vertexIndex[3],
            GLuint uvIndex[3],
            GLuint normalIndex[3],
            std::vector<glm::vec3> &out_vertices,
            std::vector<glm::vec2> &out_UVs,
            std::vector<glm::vec3> &out_normals,
            uint32_t triangle_i)
    {
        glm::vec3 vertex;
        glm::vec2 uv;
        glm::vec3 normal;

        vertex = temp_vertices[vertexIndex[0]];
        out_vertices.push_back(vertex);
        uv = temp_UVs[uvIndex[0]];
        out_UVs.push_back(uv);
        normal = temp_normals[normalIndex[0]];
        out_normals.push_back(normal);

        // std::cout << "triangle " << triangle_i << ", vertex 0: (" << vertex.x << ", " << vertex.y << ", " << vertex.z << ").\n";

        vertex = temp_vertices[vertexIndex[1]];
        out_vertices.push_back(vertex);
        uv = temp_UVs[uvIndex[1]];
        out_UVs.push_back(uv);
        normal = temp_normals[normalIndex[1]];
        out_normals.push_back(normal);

        // std::cout << "triangle " << triangle_i << ", vertex 1: (" << vertex.x << ", " << vertex.y << ", " << vertex.z << ").\n";

        vertex = temp_vertices[vertexIndex[2]];
        out_vertices.push_back(vertex);
        uv = temp_UVs[uvIndex[2]];
        out_UVs.push_back(uv);
        normal = temp_normals[normalIndex[2]];
        out_normals.push_back(normal);

        // std::cout << "triangle " << triangle_i << ", vertex 2: (" << vertex.x << ", " << vertex.y << ", " << vertex.z << ").\n\n";
        return triangle_i++;
    }

    bool triangulate_quads(
            GLuint *input_vertex_pointer,
            uint32_t image_width,
            uint32_t image_height,
            std::vector<glm::vec3> &out_vertices,
            std::vector<glm::vec2> &out_UVs,
            std::vector<glm::vec3> &out_normals,
            std::string triangulation_type,
            GLfloat sphere_radius,
            SphericalWorldStruct spherical_world_struct)
    {

        std::vector<GLuint> vertexIndices, uvIndices, normalIndices;
        std::vector<glm::vec3> temp_vertices;
        std::vector<glm::vec2> temp_UVs;
        std::vector<glm::vec3> temp_normals;

        uint32_t texture_x = 0;
        uint32_t texture_y = 0;

        // Processing stages:
        // 1. Define the (GLfloat) vertices for vertices loaded from file, `push_back` to `temp_vertices`.
        // 2. Interpolate the (GLfloat) vertices between, using bilinear interpolation, `push_back` to `temp_vertices` and `temp_UVs`.
        // 3. Transform spherical coordinates loaded from file (and computed this far as being in horizontal plane) to a curved surface.
        // 4. Transform interpolated coordinates (and computed this far as being in horizontal plane) to a curved surface.
        // 5. Compute the face normals, `push_back` to `face_normals`.
        // 6. Compute the vertex normals for vertices loaded from file and for interpolated vertices (for `"bilinear_interpolation"`), `push_back` to `temp_normals`.
        // 7. Loop through all vertices and `model::output_triangle_vertices`.

        // 1. Define the vertices for vertices loaded from file, `push_back` to `temp_vertices`.
        // First, define the temporary vertices in a double loop.
        for (uint32_t z = 0; z < image_height; z++)
        {
            for (uint32_t x = 0; x < image_width; x++)
            {
                // current x,z coordinates).
                GLfloat y = (GLfloat) model::get_y(input_vertex_pointer, x, z, image_width);

                // This corresponds to "v": specify one vertex.
                glm::vec3 vertex;
                vertex.x = (GLfloat) x;
                vertex.y = y;
                vertex.z = (GLfloat) z;
                temp_vertices.push_back(vertex);

                // This corresponds to "vt": specify texture coordinates of one vertex.
                glm::vec2 uv;

#ifdef USE_HEIGHT_AS_TEXTURE_COORDINATE
                uv.x = y / 256;
                uv.y = 0.0f;
#endif

#ifdef USE_REAL_TEXTURE_COORDINATES
                uv.x = round((GLfloat) texture_x);
                uv.y = round((GLfloat) texture_y);
#endif

                temp_UVs.push_back(uv);

                texture_x ^= 1;
            }
            texture_y ^= 1;
        }

        const char *char_triangulation_type = triangulation_type.c_str();

        bool is_bilinear_interpolation_in_use = false;
        bool is_southwest_northeast_edges_in_use = false;
        bool is_southeast_northwest_edges_in_use = false;
        bool is_triangulation_type_valid = false;

        if (strcmp(char_triangulation_type, "bilinear_interpolation") == 0)
        {
            is_bilinear_interpolation_in_use = true;
            is_triangulation_type_valid = true;
        }
        else if ((strcmp(char_triangulation_type, "southwest_northeast_edges") == 0) || (strcmp(char_triangulation_type, "northeast_southwest_edges") == 0))
        {
            is_southwest_northeast_edges_in_use = true;
            is_triangulation_type_valid = true;
        }
        else if ((strcmp(char_triangulation_type, "southeast_northwest_edges") == 0) || (strcmp(char_triangulation_type, "northwest_southeast_edges") == 0))
        {
            is_southeast_northwest_edges_in_use = true;
            is_triangulation_type_valid = true;
        }

        std::cout << "triangulation type in use: " << triangulation_type << "\n";

        if (!is_triangulation_type_valid)
        {
            std::cerr << "invalid triangulation type!\n";
        }

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

        uint32_t triangle_i = 0;

        // 2. Interpolate the vertices between, using bilinear interpolation, `push_back` to `temp_vertices`.
        if (is_bilinear_interpolation_in_use)
        {
            std::cout << "interpolating center vertices.\n";

            // Then, define the faces in a double loop.
            // Begin from index 1.
            for (uint32_t z = 1; z < image_height; z++)
            {
                // Begin from index 1.
                for (uint32_t x = 1; x < image_width; x++)
                {
                    // This corresponds to "f": specify a face (but here we specify 2 faces instead!).
                    // std::cout << "Processing coordinate (" << x << ", " << z << ").\n";

                    uint32_t current_vertex_i = image_width * z + x;

                    // Interpolate y coordinate (altitude).
                    GLfloat y = ((GLfloat) SOUTHWEST_Y + SOUTHEAST_Y + NORTHWEST_Y + NORTHEAST_Y) / 4;

                    // Create a new vertex using bilinear interpolation.
                    // This corresponds to "v": specify one vertex.
                    glm::vec3 vertex;
                    vertex.x = (GLfloat) x - 0.5f;
                    vertex.y = y;
                    vertex.z = (GLfloat) z - 0.5f;
                    temp_vertices.push_back(vertex);

                    // This corresponds to "vt": specify texture coordinates of one vertex.
                    glm::vec2 uv;

#ifdef USE_HEIGHT_AS_TEXTURE_COORDINATE
                    uv.x = y / 256;
                    uv.y = 0.0f;
#endif

#ifdef USE_REAL_TEXTURE_COORDINATES
                    uv.x = 0.5f;
                    uv.y = 0.5f;
#endif

                    temp_UVs.push_back(uv);
                }
            }
        }
        else if (is_southwest_northeast_edges_in_use || is_southeast_northwest_edges_in_use)
        {
            // Then, define the faces in a double loop.
            // Begin from index 1.
            for (uint32_t z = 1; z < image_height; z++)
            {
                // Begin from index 1.
                for (uint32_t x = 1; x < image_width; x++)
                {
                    // This corresponds to "f": specify a face (but here we specify 2 faces instead!).
                    // std::cout << "Processing coordinate (" << x << ", " << z << ").\n";

                    uint32_t current_vertex_i = image_width * z + x;

                    if (is_southwest_northeast_edges_in_use)
                    {
                        // Define the triangles (2 faces).
                        // Triangle order: SE - NW.
                        //
                        // First triangle: 1, 4, 2 (southwest, northeast, southeast).
                        // Second triangle: 1, 3, 4 (southwest, northwest, northeast).
                        // 1, 4, 2 are relative vertex indices (base 1).
                        // 1, 3, 4 are relative vertex indices (base 1).

                        // Define the first triangle, SE: 1, 4, 2 (southwest, northeast, southeast).
                        // southwest: down and left from current coordinate.
                        // southeast: down from current coordinate.
                        // northeast: current coordinate.

                        vertexIndex[0] = SOUTHWEST;
                        vertexIndex[1] = NORTHEAST;
                        vertexIndex[2] = SOUTHEAST;

#ifdef USE_HEIGHT_AS_TEXTURE_COORDINATE
                        uvIndex[0] = SOUTHWEST_Y;
                        uvIndex[1] = NORTHEAST_Y;
                        uvIndex[2] = SOUTHEAST_Y;
#endif

#ifdef USE_REAL_TEXTURE_COORDINATES
                        uvIndex[0] = SOUTHWEST;
                        uvIndex[1] = NORTHEAST;
                        uvIndex[2] = SOUTHEAST;
#endif
                    }
                    else if (is_southeast_northwest_edges_in_use)
                    {

                        // Define the triangles (2 faces).
                        // Triangle order: SW - NE.
                        //
                        // First triangle: 2, 1, 3 (southeast, southwest, northwest).
                        // Second triangle: 2, 3, 4 (southeast, northwest, northeast).
                        // 2, 1, 3 are relative vertex indices (base 1).
                        // 2, 3, 4 are relative vertex indices (base 1).

                        // Define the first triangle, SW: 2, 1, 3 (southeast, southwest, northwest).
                        // southeast: down from current coordinate.
                        // southwest: down and left from current coordinate.
                        // northwest: left from current coordinate.

                        vertexIndex[0] = SOUTHEAST;
                        vertexIndex[1] = SOUTHWEST;
                        vertexIndex[2] = NORTHWEST;

#ifdef USE_HEIGHT_AS_TEXTURE_COORDINATE
                        uvIndex[0] = SOUTHEAST_Y;
                        uvIndex[1] = SOUTHWEST_Y;
                        uvIndex[2] = NORTHWEST_Y;
#endif

#ifdef USE_REAL_TEXTURE_COORDINATES
                        uvIndex[0] = SOUTHEAST;
                        uvIndex[1] = SOUTHWEST;
                        uvIndex[2] = NORTHWEST;
#endif
                    }

                    normalIndex[0] = 0; // TODO: add proper normal index.
                    normalIndex[1] = 0; // TODO: add proper normal index.
                    normalIndex[2] = 0; // TODO: add proper normal index.

                    // triangle_i = model::output_triangle_vertices(
                    //         temp_vertices,
                    //         temp_UVs,
                    //         temp_normals,
                    //         vertexIndex,
                    //         uvIndex,
                    //         normalIndex,
                    //         out_vertices,
                    //         out_UVs,
                    //         out_normals,
                    //         triangle_i);

                    if (is_southwest_northeast_edges_in_use)
                    {
                        // Define the second triangle, NW: 1, 3, 4 (southwest, northwest, northeast).
                        // southwest: down and left from current coordinate.
                        // northwest: left from current coordinate.
                        // northeast: current coordinate.

                        vertexIndex[0] = SOUTHWEST;
                        vertexIndex[1] = NORTHWEST;
                        vertexIndex[2] = NORTHEAST;

#ifdef USE_HEIGHT_AS_TEXTURE_COORDINATE
                        uvIndex[0] = SOUTHWEST_Y;
                        uvIndex[1] = NORTHWEST_Y;
                        uvIndex[2] = NORTHEAST_Y;
#endif

#ifdef USE_REAL_TEXTURE_COORDINATES
                        uvIndex[0] = SOUTHWEST;
                        uvIndex[1] = NORTHWEST;
                        uvIndex[2] = NORTHEAST;
#endif
                    }
                    else if (is_southeast_northwest_edges_in_use)
                    {
                        // Define the second triangle, NE: 2, 3, 4 (southeast, northwest, northeast).
                        // southeast: down from current coordinate.
                        // northwest: left from current coordinate.
                        // northeast: current coordinate.

                        vertexIndex[0] = SOUTHEAST;
                        vertexIndex[1] = NORTHWEST;
                        vertexIndex[2] = NORTHEAST;

#ifdef USE_HEIGHT_AS_TEXTURE_COORDINATE
                        uvIndex[0] = SOUTHEAST_Y;
                        uvIndex[1] = NORTHWEST_Y;
                        uvIndex[2] = NORTHEAST_Y;
#endif

#ifdef USE_REAL_TEXTURE_COORDINATES
                        uvIndex[0] = SOUTHEAST;
                        uvIndex[1] = NORTHWEST;
                        uvIndex[2] = NORTHEAST;
#endif
                    }

                    normalIndex[0] = 0; // TODO: add proper normal index.
                    normalIndex[1] = 0; // TODO: add proper normal index.
                    normalIndex[2] = 0; // TODO: add proper normal index.

                    // triangle_i = model::output_triangle_vertices(
                    //         temp_vertices,
                    //         temp_UVs,
                    //         temp_normals,
                    //         vertexIndex,
                    //         uvIndex,
                    //         normalIndex,
                    //         out_vertices,
                    //         out_UVs,
                    //         out_normals,
                    //         triangle_i);
                }
            }
        }
        else
        {
            std::cerr << "quad triangulation type " << triangulation_type << " not yet implemented!\n";
            return false;
        }

        if (!std::isnan(sphere_radius))
        {
            // 3. Transform spherical coordinates loaded from file (and computed this far as being in horizontal plane) to a curved surface.
            //
            // Wikipedia:
            // https://en.wikipedia.org/wiki/List_of_common_coordinate_transformations#From_spherical_coordinates
            //
            // x = rho * sin(theta) * cos(phi)
            // y = rho * sin(theta) * sin(phi)
            // z = rho * cos(theta)

#define SRTM_LATITUDE_STEP_IN_DEGREES (1.0f/1200.0f)
#define SRTM_LONGITUDE_STEP_IN_DEGREES (1.0f/1200.0f)

            std::cout << "transforming spherical coordinates loaded from file to cartesian coordinates.\n";
            std::cout << "radius: " << sphere_radius << "\n";

            double current_latitude = spherical_world_struct.northern_latitude;

            double latitude_step_in_degrees = SRTM_LATITUDE_STEP_IN_DEGREES;
            std::cout << "latitude step in degrees: " << SRTM_LATITUDE_STEP_IN_DEGREES << "\n";

            double longitude_step_in_degrees = SRTM_LONGITUDE_STEP_IN_DEGREES;
            std::cout << "longitude step in degrees: " << SRTM_LONGITUDE_STEP_IN_DEGREES << "\n";

            GLuint temp_vertices_i = 0;

            // Loop through `temp_vertices` and transform all vertices from spherical coordinates to cartesian coordinates.
            for (uint32_t z = 0; z < image_height; z++)
            {
                // loop through all latitudes.

                double current_longitude = spherical_world_struct.western_longitude;

                for (uint32_t x = 0; x < image_width; x++)
                {
                    temp_vertices[temp_vertices_i++] = transform_planar_world_vertex_into_cartesian_vertex(temp_vertices[temp_vertices_i], sphere_radius);
                }
            }

            if (is_bilinear_interpolation_in_use)
            {
                // 4. Transform interpolated coordinates (and computed this far as being in horizontal plane) to a curved surface.
                //
                // Wikipedia:
                // https://en.wikipedia.org/wiki/List_of_common_coordinate_transformations#From_spherical_coordinates
                //
                // x = rho * sin(theta) * cos(phi)
                // y = rho * sin(theta) * sin(phi)
                // z = rho * cos(theta)

                // 4. Transform interpolated coordinates (and computed this far as being in horizontal plane) to a curved surface.

                std::cout << "transforming interpolated spherical coordinates to cartesian coordinates.\n";
                std::cout << "radius: " << sphere_radius << "\n";

                for (uint32_t z = 1; z < image_height; z++)
                {
                    // loop through all latitudes.

                    double current_longitude = spherical_world_struct.western_longitude;

                    for (uint32_t x = 1; x < image_width; x++)
                    {
                        temp_vertices[temp_vertices_i++] = transform_planar_world_vertex_into_cartesian_vertex(temp_vertices[temp_vertices_i], sphere_radius);
                    }
                }
            }
        }
        else
        {
            std::cout << "no coordinate transformation is needed.\n";
        }

        // 5. Compute the face normals, `push_back` to `face_normals`.
        // Triangle order: S - W - N - E.
        //
        // First triangle: center, southeast, southwest.
        // Second triangle: center, southwest, northwest.
        // Third triangle: center, northwest, northeast.
        // Fourth triangle: center, northeast, southeast.
        std::cout << "computing face normals.\n";

        std::vector<glm::vec3> face_normal_vector_vec3;

        uint32_t current_interpolated_vertex_i;

        current_interpolated_vertex_i = image_width * image_height;

        for (uint32_t z = 1; z < image_height; z++)
        {
            for (uint32_t x = 1; x < image_width; x++)
            {
                uint32_t current_vertex_i = image_width * z + x;

                // Computing of face normals depends on triangulation type.
                if (is_bilinear_interpolation_in_use)
                {
                    glm::vec3 edge1;
                    glm::vec3 edge2;
                    glm::vec3 face_normal;

                    // Compute the normal of S face.
                    edge1 = temp_vertices[SOUTHEAST] - temp_vertices[CENTER];
                    edge2 = temp_vertices[SOUTHWEST] - temp_vertices[CENTER];
                    face_normal = glm::cross(edge1, edge2);
                    face_normal_vector_vec3.push_back(face_normal);

                    // Compute the normal of W face.
                    edge1 = temp_vertices[SOUTHWEST] - temp_vertices[CENTER];
                    edge2 = temp_vertices[NORTHWEST] - temp_vertices[CENTER];
                    face_normal = glm::cross(edge1, edge2);
                    face_normal_vector_vec3.push_back(face_normal);

                    // Compute the normal of N face.
                    edge1 = temp_vertices[NORTHWEST] - temp_vertices[CENTER];
                    edge2 = temp_vertices[NORTHEAST] - temp_vertices[CENTER];
                    face_normal = glm::cross(edge1, edge2);
                    face_normal_vector_vec3.push_back(face_normal);

                    // Compute the normal of E face.
                    edge1 = temp_vertices[NORTHEAST] - temp_vertices[CENTER];
                    edge2 = temp_vertices[SOUTHEAST] - temp_vertices[CENTER];
                    face_normal = glm::cross(edge1, edge2);
                    face_normal_vector_vec3.push_back(face_normal);
                }
                else if (is_southwest_northeast_edges_in_use)
                {
                    glm::vec3 edge1;
                    glm::vec3 edge2;
                    glm::vec3 face_normal;

                    // Compute the normal of SE face.
                    edge1 = temp_vertices[SOUTHEAST] - temp_vertices[NORTHEAST];
                    edge2 = temp_vertices[SOUTHWEST] - temp_vertices[NORTHEAST];
                    face_normal = glm::cross(edge1, edge2);
                    face_normal_vector_vec3.push_back(face_normal);

                    // Compute the normal of NW face.
                    edge1 = temp_vertices[SOUTHWEST] - temp_vertices[NORTHEAST];
                    edge2 = temp_vertices[NORTHWEST] - temp_vertices[NORTHEAST];
                    face_normal = glm::cross(edge1, edge2);
                    face_normal_vector_vec3.push_back(face_normal);
                }
                else if (is_southeast_northwest_edges_in_use)
                {
                    glm::vec3 edge1;
                    glm::vec3 edge2;
                    glm::vec3 face_normal;

                    // Compute the normal of SW face.
                    edge1 = temp_vertices[SOUTHEAST] - temp_vertices[NORTHWEST];
                    edge2 = temp_vertices[SOUTHWEST] - temp_vertices[NORTHWEST];
                    face_normal = glm::cross(edge1, edge2);
                    face_normal_vector_vec3.push_back(face_normal);

                    // Compute the normal of NE face.
                    edge1 = temp_vertices[NORTHEAST] - temp_vertices[NORTHWEST];
                    edge2 = temp_vertices[SOUTHEAST] - temp_vertices[NORTHWEST];
                    face_normal = glm::cross(edge1, edge2);
                    face_normal_vector_vec3.push_back(face_normal);
                }
                else
                {
                    std::cerr << "invalid triangulation type!\n";
                }
                current_interpolated_vertex_i++;
            }
        }

        // 6. Compute the vertex normals for vertices loaded from file, `push_back` to `temp_normals`.
        std::cout << "computing vertex normals for vertices loaded from file.\n";

        if (is_bilinear_interpolation_in_use)
        {
            current_interpolated_vertex_i = image_width * image_height;
            uint32_t x = 0;
            uint32_t z = 0;

            // Compute the normal of the southwesternmost vertex.
            // Number of adjacent faces: 2.
            glm::vec3 face_normal1;
            glm::vec3 face_normal2;
            glm::vec3 vertex_normal;

            vertex_normal = NNE_FACE_NORMAL + ENE_FACE_NORMAL;
            temp_normals.push_back(vertex_normal);

            // Compute the normals of southern vertices.
            for (x = 1; x < (image_width - 1); x++)
            {
                // Compute the normal of a southern vertex.
                // Number of adjacent faces: 4.
                vertex_normal = WNW_FACE_NORMAL + NNW_FACE_NORMAL + NNE_FACE_NORMAL + ENE_FACE_NORMAL;
                temp_normals.push_back(vertex_normal);
            }

            // Compute the normal of the southeasternmost vertex.
            // Number of adjacent faces: 2.
            x = image_width - 1;
            vertex_normal = WNW_FACE_NORMAL + NNW_FACE_NORMAL;
            temp_normals.push_back(vertex_normal);

            // Then, define most normals in a double loop.
            for (z = 1; z < (image_height - 1); z++)
            {
                // Compute the normal of a western vertex.
                // Number of adjacent faces: 4.
                x = 0;
                vertex_normal = NNE_FACE_NORMAL + ENE_FACE_NORMAL + ESE_FACE_NORMAL + SSE_FACE_NORMAL;
                temp_normals.push_back(vertex_normal);

                for (x = 1; x < (image_width - 1); x++)
                {
                    uint32_t current_vertex_i = image_width * z + x;

                    // Compute the normal of a central vertex.
                    // Number of adjacent faces: 8.
                    vertex_normal = SSW_FACE_NORMAL + WSW_FACE_NORMAL + WNW_FACE_NORMAL + NNW_FACE_NORMAL + NNE_FACE_NORMAL + ENE_FACE_NORMAL + ESE_FACE_NORMAL + SSE_FACE_NORMAL;
                    temp_normals.push_back(vertex_normal);
                }

                x = image_width - 1;

                // Compute the normal of an eastern vertex.
                // Number of adjacent faces: 4.
                vertex_normal = SSW_FACE_NORMAL + WSW_FACE_NORMAL + WNW_FACE_NORMAL + NNW_FACE_NORMAL;
                temp_normals.push_back(vertex_normal);
            }

            // Compute the normal of the northwesternmost vertex.
            // Number of adjacent faces: 2.
            x = 0;
            vertex_normal = SSE_FACE_NORMAL + ESE_FACE_NORMAL;
            temp_normals.push_back(vertex_normal);

            // Compute the normals of northern vertices.
            for (x = 1; x < (image_width - 1); x++)
            {
                // Compute the normal of a northern vertex.
                // Number of adjacent faces: 4.
                vertex_normal = SSW_FACE_NORMAL + WSW_FACE_NORMAL + ESE_FACE_NORMAL + SSE_FACE_NORMAL;
                temp_normals.push_back(vertex_normal);
            }

            // Compute the normal of the northeasternmost vertex.
            // Number of adjacent faces: 2.
            x = image_width - 1;
            vertex_normal = SSW_FACE_NORMAL + WSW_FACE_NORMAL;
            temp_normals.push_back(vertex_normal);

            // 6. Compute the vertices between, `push_back` to `temp_normals`.
            std::cout << "computing vertex normals for interpolated vertices.\n";

            for (z = 1; z < image_height; z++)
            {
                for (x = 1; x < image_width; x++)
                {
                    vertex_normal = S_FACE_NORMAL + W_FACE_NORMAL + N_FACE_NORMAL + E_FACE_NORMAL;
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
            vertex_normal = NE_FACE_NORMAL_FOR_SE_NW;
            temp_normals.push_back(vertex_normal);

            // Compute the normals of southern vertices.
            for (x = 1; x < (image_width - 1); x++)
            {
                // Compute the normal of a southern vertex.
                // Number of adjacent faces: 3.
                vertex_normal = WNW_FACE_NORMAL_FOR_SE_NW + NNW_FACE_NORMAL_FOR_SE_NW + NE_FACE_NORMAL_FOR_SE_NW;
                temp_normals.push_back(vertex_normal);
            }

            // Compute the normal of the southeasternmost vertex.
            // Number of adjacent faces: 2.
            x = image_width - 1;
            vertex_normal = WNW_FACE_NORMAL_FOR_SE_NW + NNW_FACE_NORMAL_FOR_SE_NW;
            temp_normals.push_back(vertex_normal);

            // Then, define most normals in a double loop.
            for (z = 1; z < (image_height - 1); z++)
            {
                // Compute the normal of a western vertex.
                // Number of adjacent faces: 3.
                x = 0;
                vertex_normal = NE_FACE_NORMAL_FOR_SE_NW + ESE_FACE_NORMAL_FOR_SE_NW + SSE_FACE_NORMAL_FOR_SE_NW;
                temp_normals.push_back(vertex_normal);

                for (x = 1; x < (image_width - 1); x++)
                {
                    uint32_t current_vertex_i = image_width * z + x;

                    // Compute the normal of a central vertex.
                    // Number of adjacent faces: 6.
                    vertex_normal = SSE_FACE_NORMAL_FOR_SE_NW + SW_FACE_NORMAL_FOR_SE_NW + WNW_FACE_NORMAL_FOR_SE_NW + NNW_FACE_NORMAL_FOR_SE_NW + NE_FACE_NORMAL_FOR_SE_NW + ESE_FACE_NORMAL_FOR_SE_NW;
                    temp_normals.push_back(vertex_normal);
                }

                x = image_width - 1;

                // Compute the normal of an eastern vertex.
                // Number of adjacent faces: 4.
                vertex_normal = SW_FACE_NORMAL_FOR_SE_NW + WNW_FACE_NORMAL_FOR_SE_NW + NNW_FACE_NORMAL_FOR_SE_NW;
                temp_normals.push_back(vertex_normal);
            }

            // Compute the normal of the northwesternmost vertex.
            // Number of adjacent faces: 2.
            x = 0;
            vertex_normal = SSE_FACE_NORMAL_FOR_SE_NW + ESE_FACE_NORMAL_FOR_SE_NW;
            temp_normals.push_back(vertex_normal);

            // Compute the normals of northern vertices.
            for (x = 1; x < (image_width - 1); x++)
            {
                // Compute the normal of a northern vertex.
                // Number of adjacent faces: 3.
                vertex_normal = SW_FACE_NORMAL_FOR_SE_NW + ESE_FACE_NORMAL_FOR_SE_NW + SSE_FACE_NORMAL_FOR_SE_NW;
                temp_normals.push_back(vertex_normal);
            }

            // Compute the normal of the northeasternmost vertex.
            // Number of adjacent faces: 1.
            x = image_width - 1;
            vertex_normal = SW_FACE_NORMAL_FOR_SE_NW;
            temp_normals.push_back(vertex_normal);
        }

        // 7. Loop through all vertices and `model::output_triangle_vertices`.
        std::cout << "defining output vertices, UVs and normals.\n";

        if (is_bilinear_interpolation_in_use)
        {
            uint32_t x;
            uint32_t z;

            triangle_i = 0;
            current_interpolated_vertex_i = image_width * image_height;

            for (z = 1; z < image_height; z++)
            {
                for (x = 1; x < image_width; x++)
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
                    vertexIndex[0] = CENTER;
                    vertexIndex[1] = SOUTHEAST;
                    vertexIndex[2] = SOUTHWEST;

#ifdef USE_HEIGHT_AS_TEXTURE_COORDINATE
                    uvIndex[0] = CENTER_Y;
                    uvIndex[1] = SOUTHEAST_y;
                    uvIndex[2] = SOUTHWEST_Y;
#endif

#ifdef USE_REAL_TEXTURE_COORDINATES
                    uvIndex[0] = CENTER;
                    uvIndex[1] = SOUTHEAST;
                    uvIndex[2] = SOUTHWEST;
#endif

                    normalIndex[0] = 0; // TODO: add proper normal index.
                    normalIndex[1] = 0; // TODO: add proper normal index.
                    normalIndex[2] = 0; // TODO: add proper normal index.

                    triangle_i = model::output_triangle_vertices(
                            temp_vertices,
                            temp_UVs,
                            temp_normals,
                            vertexIndex,
                            uvIndex,
                            normalIndex,
                            out_vertices,
                            out_UVs,
                            out_normals,
                            triangle_i);

                    // Define the second triangle, W: center, southwest, northwest.
                    vertexIndex[0] = CENTER;
                    vertexIndex[1] = SOUTHWEST;
                    vertexIndex[2] = NORTHWEST;

#ifdef USE_HEIGHT_AS_TEXTURE_COORDINATE
                    uvIndex[0] = CENTER_Y;
                    uvIndex[1] = SOUTHWEST_Y;
                    uvIndex[2] = NORTHWEST_Y;
#endif

#ifdef USE_REAL_TEXTURE_COORDINATES
                    uvIndex[0] = CENTER;
                    uvIndex[1] = SOUTHWEST;
                    uvIndex[2] = NORTHWEST;
#endif

                    normalIndex[0] = 0; // TODO: add proper normal index.
                    normalIndex[1] = 0; // TODO: add proper normal index.
                    normalIndex[2] = 0; // TODO: add proper normal index.

                    triangle_i = model::output_triangle_vertices(
                            temp_vertices,
                            temp_UVs,
                            temp_normals,
                            vertexIndex,
                            uvIndex,
                            normalIndex,
                            out_vertices,
                            out_UVs,
                            out_normals,
                            triangle_i);

                    // Define the third triangle, N: center, northwest, northeast.
                    vertexIndex[0] = CENTER;
                    vertexIndex[1] = NORTHWEST;
                    vertexIndex[2] = NORTHEAST;

#ifdef USE_HEIGHT_AS_TEXTURE_COORDINATE
                    uvIndex[0] = CENTER_Y;
                    uvIndex[1] = NORTHWEST_y;
                    uvIndex[2] = NORTHEAST_Y;
#endif

#ifdef USE_REAL_TEXTURE_COORDINATES
                    uvIndex[0] = CENTER;
                    uvIndex[1] = NORTHWEST;
                    uvIndex[2] = NORTHEAST;
#endif

                    normalIndex[0] = 0; // TODO: add proper normal index.
                    normalIndex[1] = 0; // TODO: add proper normal index.
                    normalIndex[2] = 0; // TODO: add proper normal index.

                    triangle_i = model::output_triangle_vertices(
                            temp_vertices,
                            temp_UVs,
                            temp_normals,
                            vertexIndex,
                            uvIndex,
                            normalIndex,
                            out_vertices,
                            out_UVs,
                            out_normals,
                            triangle_i);

                    // Define the fourth triangle, E: center, northeast, southeast.
                    vertexIndex[0] = CENTER;
                    vertexIndex[1] = NORTHEAST;
                    vertexIndex[2] = SOUTHEAST;

#ifdef USE_HEIGHT_AS_TEXTURE_COORDINATE
                    uvIndex[0] = CENTER_Y;
                    uvIndex[1] = NORTHEAST_y;
                    uvIndex[2] = SOUTHEAST_Y;
#endif

#ifdef USE_REAL_TEXTURE_COORDINATES
                    uvIndex[0] = CENTER;
                    uvIndex[1] = NORTHEAST;
                    uvIndex[2] = SOUTHEAST;
#endif

                    normalIndex[0] = 0; // TODO: add proper normal index.
                    normalIndex[1] = 0; // TODO: add proper normal index.
                    normalIndex[2] = 0; // TODO: add proper normal index.

                    triangle_i = model::output_triangle_vertices(
                            temp_vertices,
                            temp_UVs,
                            temp_normals,
                            vertexIndex,
                            uvIndex,
                            normalIndex,
                            out_vertices,
                            out_UVs,
                            out_normals,
                            triangle_i);

                    current_interpolated_vertex_i++;
                }
            }
        }
        else if (is_southwest_northeast_edges_in_use)
        {
            // TODO: define output vertices, UVs and normals for `"southwest_northeast_edges"`.
        }
        else if (is_southeast_northwest_edges_in_use)
        {
            uint32_t x;
            uint32_t z;

            triangle_i = 0;

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
                    vertexIndex[0] = SOUTHWEST;
                    vertexIndex[1] = NORTHWEST;
                    vertexIndex[2] = SOUTHEAST;

#ifdef USE_HEIGHT_AS_TEXTURE_COORDINATE
                    uvIndex[0] = SOUTHWEST_Y;
                    uvIndex[1] = NORTHWEST_y;
                    uvIndex[2] = SOUTHEAST_Y;
#endif

#ifdef USE_REAL_TEXTURE_COORDINATES
                    uvIndex[0] = SOUTHWEST;
                    uvIndex[1] = NORTHWEST;
                    uvIndex[2] = SOUTHEAST;
#endif

                    normalIndex[0] = 0; // TODO: add proper normal index.
                    normalIndex[1] = 0; // TODO: add proper normal index.
                    normalIndex[2] = 0; // TODO: add proper normal index.

                    triangle_i = model::output_triangle_vertices(
                            temp_vertices,
                            temp_UVs,
                            temp_normals,
                            vertexIndex,
                            uvIndex,
                            normalIndex,
                            out_vertices,
                            out_UVs,
                            out_normals,
                            triangle_i);

                    // Define the second triangle, NW: northeast, southeast, northwest.
                    vertexIndex[0] = NORTHEAST;
                    vertexIndex[1] = SOUTHEAST;
                    vertexIndex[2] = NORTHWEST;

#ifdef USE_HEIGHT_AS_TEXTURE_COORDINATE
                    uvIndex[0] = NORTHEAST_Y;
                    uvIndex[1] = SOUTHEAST_y;
                    uvIndex[2] = NORTHWEST_Y;
#endif

#ifdef USE_REAL_TEXTURE_COORDINATES
                    uvIndex[0] = NORTHEAST;
                    uvIndex[1] = SOUTHEAST;
                    uvIndex[2] = NORTHWEST;
#endif

                    normalIndex[0] = 0; // TODO: add proper normal index.
                    normalIndex[1] = 0; // TODO: add proper normal index.
                    normalIndex[2] = 0; // TODO: add proper normal index.

                    triangle_i = model::output_triangle_vertices(
                            temp_vertices,
                            temp_UVs,
                            temp_normals,
                            vertexIndex,
                            uvIndex,
                            normalIndex,
                            out_vertices,
                            out_UVs,
                            out_normals,
                            triangle_i);
                }
            }
        }

        return true;
    }

    bool load_BMP_world(
            std::string image_path,
            std::vector<glm::vec3> &out_vertices,
            std::vector<glm::vec2> &out_UVs,
            std::vector<glm::vec3> &out_normals,
            std::string color_channel)
    {
        std::cout << "Loading BMP file " << image_path << " ...\n";

        // Data read from the header of the BMP file
        unsigned char header[54];
        uint32_t dataPos;
        uint32_t imageSize;
        uint32_t image_width, image_height;
        // Actual RGB image data.
        uint8_t *image_data;

        // Open the file
        const char *char_image_path = image_path.c_str();
        FILE *file = fopen(char_image_path, "rb");
        if (!file)
        {
            std::cerr << image_path << " could not be opened.\n";
            getchar();
            return 0;
        }

        // Read the header, i.e. the 54 first bytes

        // If less than 54 bytes are read, it's a problem.
        if (fread(header, 1, 54, file) != 54)
        {
            std::cerr << "not a correct BMP file.\n";
            return 0;
        }

        // A BMP files always begins with "BM"
        if ((header[0] != 'B') || (header[1] != 'M'))
        {
            std::cerr << "not a correct BMP file.\n";
            return 0;
        }

        // Make sure this is a 24bpp file
        if (*(uint32_t*) & (header[0x1E]) != 0)
        {
            std::cerr << "not a correct BMP file.\n";
            return 0;
        }

        if (*(uint32_t*) & (header[0x1C]) != 24)
        {
            std::cerr << "not a correct BMP file.\n";
            return 0;
        }

        // Read the information about the image
        dataPos      = *(uint32_t*) & (header[0x0A]);
        imageSize    = *(uint32_t*) & (header[0x22]);
        image_width  = *(uint32_t*) & (header[0x12]);
        image_height = *(uint32_t*) & (header[0x16]);

        // Some BMP files are misformatted, guess missing information
        if (imageSize == 0)
        {
            imageSize = image_width * image_height * 3; // 3 : one byte for each Red, Green and Blue component
        }

        if (dataPos == 0)
        {
            dataPos = 54; // The BMP header is done that way
        }

        // Create a buffer.
        image_data = new uint8_t [imageSize];

        // Read the actual image data from the file into the buffer.
        fread(image_data, 1, imageSize, file);

        // Everything is in memory now, the file can be closed
        fclose(file);

        GLuint *vertex_data;
        vertex_data = new GLuint [imageSize];

        uint8_t *image_pointer;
        image_pointer = image_data;

        GLuint *vertex_pointer;
        vertex_pointer = vertex_data;

        const char *char_color_channel = color_channel.c_str();

        // start processing image_data.
        for (GLuint z = 0; z < image_height; z++)
        {
            for (GLuint x = 0; x < image_width; x++)
            {
                GLuint y;

                if (strcmp(char_color_channel, "red") == 0)
                {
                    y = (GLuint) *image_pointer;       // y-coordinate is the red (R) value.
                }
                else if (strcmp(char_color_channel, "green") == 0)
                {
                    y = (GLuint) *(image_pointer + 1); // y-coordinate is the green (G) value.
                }
                else if (strcmp(char_color_channel, "green") == 0)
                {
                    y = (GLuint) *(image_pointer + 2); // y-coordinate is the blue (B) value.
                }
                // y-coordinate is the mean of R, G, & B.
                else if ((strcmp(char_color_channel, "mean") == 0) || (strcmp(char_color_channel, "all") == 0))
                {
                    y = (((GLuint) *image_pointer) + ((GLuint) *(image_pointer + 1)) + ((GLuint) *(image_pointer + 2))) / 3;
                }
                else
                {
                    std::cerr << "invalid color channel!\n";
                }

                // std::cout << color_channel << " color channel value at (" << x << ", " << z << "): " << y << ".\n";
                *vertex_pointer++ = y;
                image_pointer += 3; // R, G, & B.
            }
        }
        std::cout << "color channel in use: " << color_channel << "\n";

        std::string triangulation_type = "bilinear_interpolation";
        // std::string triangulation_type = "southeast_northwest_edges"; // "northwest_southeast_edges" is equivalent.
        // std::string triangulation_type = "southwest_northeast_edges"; // "northeast_southwest_edges" is equivalent.

        bool triangulation_result = model::triangulate_quads(
                vertex_data,
                image_width,
                image_height,
                out_vertices,
                out_UVs,
                out_normals,
                triangulation_type,
                NAN,
                SphericalWorldStruct()); // not used, but is needed in the function call.
        return true;
    }

    bool load_SRTM_world(
            std::string image_path,
            double southern_latitude,
            double western_longitude,
            std::vector<glm::vec3> &out_vertices,
            std::vector<glm::vec2> &out_UVs,
            std::vector<glm::vec3> &out_normals)
    {
        // For SRTM worlds, the right heightmap filename must be resolved first.
        // The SRTM filenames contain always the southwest coordinate of the block.
        // Each single SRTM file contains 1 degree of latitude and 1 degree of longiture. File size is 1201x1201.
        // Precision is 3 arc-seconds in both latitude and longitude.

        // In coordinates (`latitude` and `longitude`) negative values mean south for latitude and west for longitude,
        // and positive value mean north for latitude and east for longitude.
        // Therefore the SRTM heightmap filename can be resolved by rounding both latitude and longitude down (towards negative infinity).

        int32_t filename_latitude = floor(southern_latitude);
        int32_t filename_longitude = floor(western_longitude);

        double northern_latitude = southern_latitude + 1.0f;
        double eastern_longitude = western_longitude + 1.0f;

        std::string south_north_char;
        std::string west_east_char;

        if (filename_latitude < 0)
        {
            // negative latitudes mean southern hemisphere.
            south_north_char = "S";
        }
        else
        {
            // positive latitudes mean northern hemisphere.
            south_north_char = "N";
        }

        if (filename_longitude < 0)
        {
            // negative longitudes mean western hemisphere.
            west_east_char = "W";
        }
        else
        {
            // positive longitudes mean eastern hemisphere.
            west_east_char = "E";
        }

        std::stringstream latitude_stringstream;
        std::stringstream longitude_stringstream;

        latitude_stringstream << std::setw(SRTM_FILENAME_N_OF_LATITUDE_CHARS) << std::setfill('0') << abs(filename_latitude);
        latitude_stringstream << std::setw(SRTM_FILENAME_N_OF_LONGITUDE_CHARS) << std::setfill('0') << abs(filename_longitude);

        std::cout << "Loading SRTM file " << image_path << " ...\n";

        uint32_t dataPos;
        uint32_t imageSize;
        uint32_t true_image_width, true_image_height, image_width_in_use, image_height_in_use;
        // Actual 16-bit big-endian signed integer heightmap data.
        uint8_t *image_data;

        // Open the file
        const char *char_image_path = image_path.c_str();
        FILE *file = fopen(char_image_path, "rb");
        if (!file)
        {
            std::cerr << image_path << " could not be opened.\n";
            getchar();
            return 0;
        }

        true_image_width  = 1201;
        true_image_height = 1201;
        image_width_in_use  = 70;
        image_height_in_use = 70;
        imageSize = sizeof(int16_t) * true_image_width * true_image_height;

        // Create a buffer.
        image_data = new uint8_t [imageSize];

        // Read the actual image data from the file into the buffer.
        fread(image_data, 1, imageSize, file);

        // Everything is in memory now, the file can be closed
        fclose(file);

        GLuint *vertex_data;
        vertex_data = new GLuint [image_width_in_use * image_height_in_use];

        uint8_t *image_pointer;
        image_pointer = image_data;

        GLuint *vertex_pointer;
        vertex_pointer = vertex_data;

        // start processing image_data.
        // 90 meters is for equator.

        // FIXME: this is a temporary testing code with a hardcoded start from the northwestern corner.
        // TODO: write a proper code for loading the appropriate chunks (based on real spherical coordinates) into VBOs!

        for (GLuint z = 0; z < image_height_in_use; z++)
        {
            for (GLuint x = 0; x < image_width_in_use; x++)
            {
                GLuint y;
                // y = ((((GLuint) *image_pointer) << 8) | ((GLuint) *(image_pointer + 1))) + (GLuint) EARTH_RADIUS;
                y = ((((GLuint) *image_pointer) << 8) | ((GLuint) *(image_pointer + 1)));

                image_pointer += sizeof(int16_t);
                *vertex_pointer++ = y;
            }
            image_pointer += sizeof(int16_t) * (true_image_width - image_width_in_use);
        }

        std::string triangulation_type = "bilinear_interpolation";
        // std::string triangulation_type = "southeast_northwest_edges"; // "northwest_southeast_edges" is equivalent.
        // std::string triangulation_type = "southwest_northeast_edges"; // "northeast_southwest_edges" is equivalent.

        SphericalWorldStruct spherical_world_struct;
        spherical_world_struct.southern_latitude = (double) southern_latitude; // must be double, though SRTM data is split between full degrees.
        spherical_world_struct.northern_latitude = (double) northern_latitude; // must be double, though SRTM data is split between full degrees.
        spherical_world_struct.western_longitude = (double) western_longitude; // must be double, though SRTM data is split between full degrees.
        spherical_world_struct.eastern_longitude = (double) eastern_longitude; // must be double, though SRTM data is split between full degrees.

        bool triangulation_result = model::triangulate_quads(
                vertex_data,
                image_width_in_use,
                image_height_in_use,
                out_vertices,
                out_UVs,
                out_normals,
                triangulation_type,
                EARTH_RADIUS,
                spherical_world_struct);
        return true;
    }
}
