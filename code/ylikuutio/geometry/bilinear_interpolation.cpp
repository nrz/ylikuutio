#include "bilinear_interpolation.hpp"
#include "triangulation_macros.cpp"
#include "code/ylikuutio/common/globals.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace geometry
{
    // for bilinear interpolation.
    glm::vec3 get_face_normal(
            std::vector<glm::vec3>& face_normal_data,
            uint32_t x,
            uint32_t z,
            BilinearDirections compass_point_code,
            uint32_t image_width)
    {
        uint32_t face_normal_i;

        switch (compass_point_code)
        {
            case SSW:
                face_normal_i = 4 * (z - 1) * (image_width - 1) + (4 * x) - 1;
                break;
            case WSW:
                face_normal_i = 4 * (z - 1) * (image_width - 1) + (4 * x) - 2;
                break;
            case WNW:
                face_normal_i = 4 * z * (image_width - 1) + (4 * x) - 4;
                break;
            case NNW:
                face_normal_i = 4 * z * (image_width - 1) + (4 * x) - 1;
                break;
            case NNE:
                face_normal_i = 4 * z * (image_width - 1) + (4 * x) + 1;
                break;
            case ENE:
                face_normal_i = 4 * z * (image_width - 1) + (4 * x);
                break;
            case ESE:
                face_normal_i = 4 * (z - 1) * (image_width - 1) + (4 * x) + 2;
                break;
            case SSE:
                face_normal_i = 4 * (z - 1) * (image_width - 1) + (4 * x) + 1;
                break;
            default:
                std::cerr << "invalid compass point code!\n";
                return glm::vec3(NAN, NAN, NAN);
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

    void interpolate_vertices_using_bilinear_interpolation(
            BilinearInterpolationStruct bilinear_interpolation_struct,
            std::vector<glm::vec3>& temp_vertices,
            std::vector<glm::vec2>& temp_UVs)
    {
        uint32_t* input_vertex_pointer = bilinear_interpolation_struct.input_vertex_pointer;
        uint32_t image_width = bilinear_interpolation_struct.image_width;
        uint32_t image_height = bilinear_interpolation_struct.image_height;

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

                if (bilinear_interpolation_struct.should_ylikuutio_use_real_texture_coordinates)
                {
                    uv.x = 0.5f;
                    uv.y = 0.5f;
                }
                else
                {
                    uv.x = y / 256;
                    uv.y = 0.0f;
                }

                temp_UVs.push_back(uv);
            }
        }
    }
}
