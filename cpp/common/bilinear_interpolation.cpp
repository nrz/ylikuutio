#include "bilinear_interpolation.hpp"
#include "indexing.hpp"
#include "triangulation_macros.cpp"
#include "globals.hpp"

// Include GLEW
#ifndef __GL_GLEW_H_INCLUDED
#define __GL_GLEW_H_INCLUDED
#include <GL/glew.h> // GLfloat, GLuint etc.
#endif

// Include standard headers
#include <iostream>
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace geometry
{
    void interpolate_vertices_using_bilinear_interpolation(
            BilinearInterpolationStruct bilinear_interpolation_struct,
            std::vector<glm::vec3> &temp_vertices,
            std::vector<glm::vec2> &temp_UVs)
    {
        GLuint* input_vertex_pointer = bilinear_interpolation_struct.input_vertex_pointer;
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
