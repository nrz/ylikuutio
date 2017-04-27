#ifndef __TRIANGULATION_TEMPLATES_HPP_INCLUDED
#define __TRIANGULATION_TEMPLATES_HPP_INCLUDED

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
    template<class T1>
        T1 get_y(
                T1* vertex_data,
                uint32_t x,
                uint32_t z,
                uint32_t image_width)
        {
            // This function returns the altitude value based on x & z coordinates.
            // This works only for a raw heightmap data (for a 2D array of altitudes).
            T1* vertex_pointer;
            vertex_pointer = vertex_data + z * image_width + x;
            return static_cast<T1>(*vertex_pointer);
        }

    // for bilinear interpolation.
    template<class T1>
        float southwest_y(uint32_t x, uint32_t z, T1* input_vertex_pointer, uint32_t image_width, uint32_t x_step, uint32_t z_step)
        {
            return static_cast<float>(geometry::get_y(input_vertex_pointer, x - 1, z - 1, image_width));
        }
    template<class T1>
        float southeast_y(uint32_t x, uint32_t z, T1* input_vertex_pointer, uint32_t image_width, uint32_t x_step, uint32_t z_step)
        {
            return static_cast<float>(geometry::get_y(input_vertex_pointer, x, z - 1, image_width));
        }
    template<class T1>
        float northwest_y(uint32_t x, uint32_t z, T1* input_vertex_pointer, uint32_t image_width, uint32_t x_step, uint32_t z_step)
        {
            return static_cast<float>(geometry::get_y(input_vertex_pointer, x - 1, z, image_width));
        }
    template<class T1>
        float northeast_y(uint32_t x, uint32_t z, T1* input_vertex_pointer, uint32_t image_width, uint32_t x_step, uint32_t z_step)
        {
            return static_cast<float>(geometry::get_y(input_vertex_pointer, x, z, image_width));
        }
    template<class T1>
        float center_y(uint32_t x, uint32_t z, T1* input_vertex_pointer, uint32_t image_width, uint32_t x_step, uint32_t z_step)
        {
            return static_cast<float>(southwest_y(x, z, input_vertex_pointer, image_width, x_step, z_step) +
                    southeast_y(x, z, input_vertex_pointer, image_width, x_step, z_step) +
                    northwest_y(x, z, input_vertex_pointer, image_width, x_step, z_step) +
                    northeast_y(x, z, input_vertex_pointer, image_width, x_step, z_step)) / 4.0f;
        }

    template<class T1>
        void define_vertices(
                T1* input_vertex_pointer,
                uint32_t image_width,
                uint32_t image_height,
                uint32_t x_step,
                uint32_t z_step,
                bool should_ylikuutio_use_real_texture_coordinates,
                std::vector<glm::vec3>& temp_vertices,
                std::vector<glm::vec2>& temp_UVs)
        {
            // Define the temporary vertices in a double loop.
            uint32_t texture_y = 0;

            for (uint32_t z = 0; z < image_height; z++)
            {
                uint32_t texture_x = 0;

                for (uint32_t x = 0; x < image_width; x++)
                {
                    // current x,z coordinates).
                    float y = static_cast<float>(geometry::get_y(input_vertex_pointer, x, z, image_width));

                    // This corresponds to "v": specify one vertex.
                    glm::vec3 vertex;
                    vertex.x = static_cast<GLfloat>(x);
                    vertex.y = static_cast<GLfloat>(y);
                    vertex.z = static_cast<GLfloat>(z);
                    temp_vertices.push_back(vertex);

                    // This corresponds to "vt": specify texture coordinates of one vertex.
                    glm::vec2 uv;

                    if (should_ylikuutio_use_real_texture_coordinates)
                    {
                        uv.x = round(static_cast<GLfloat>(texture_x));
                        uv.y = round(static_cast<GLfloat>(texture_y));
                    }
                    else
                    {
                        uv.x = static_cast<GLfloat>(y) / 256.0f;
                        uv.y = 0.0f;
                    }

                    temp_UVs.push_back(uv);

                    texture_x ^= 1;
                }
                texture_y ^= 1;
            }
        }

    template<class T1>
        void interpolate_and_define_vertices_using_bilinear_interpolation(
                T1* input_vertex_pointer,
                uint32_t image_width,
                uint32_t image_height,
                uint32_t x_step,
                uint32_t z_step,
                bool should_ylikuutio_use_real_texture_coordinates,
                std::vector<glm::vec3>& temp_vertices,
                std::vector<glm::vec2>& temp_UVs)
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
                    float y = center_y(x, z, input_vertex_pointer, image_width, x_step, z_step);

                    // Create a new vertex using bilinear interpolation.
                    // This corresponds to "v": specify one vertex.
                    glm::vec3 vertex;
                    vertex.x = static_cast<GLfloat>(x) - 0.5f;
                    vertex.y = static_cast<GLfloat>(y);
                    vertex.z = static_cast<GLfloat>(z) - 0.5f;
                    temp_vertices.push_back(vertex);

                    // This corresponds to "vt": specify texture coordinates of one vertex.
                    glm::vec2 uv;

                    if (should_ylikuutio_use_real_texture_coordinates)
                    {
                        uv.x = 0.5f;
                        uv.y = 0.5f;
                    }
                    else
                    {
                        uv.x = y / 256.0f;
                        uv.y = 0.0f;
                    }

                    temp_UVs.push_back(uv);
                }
            }
        }
}

#endif
