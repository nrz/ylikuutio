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
                const T1* const vertex_data,
                const int32_t x,
                const int32_t z,
                const int32_t image_width)
        {
            // This function returns the altitude value based on x & z coordinates.
            // This works only for a raw heightmap data (for a 2D array of altitudes).
            const T1* const vertex_pointer = vertex_data + z * image_width + x;
            return static_cast<T1>(*vertex_pointer);
        }

    // for bilinear interpolation.
    template<class T1>
        float southwest_y(const int32_t x, const int32_t z, const T1* const input_vertex_pointer, const int32_t image_width, const int32_t x_step, const int32_t z_step)
        {
            return static_cast<float>(geometry::get_y(input_vertex_pointer, x - x_step, z - z_step, image_width));
        }
    template<class T1>
        float southeast_y(const int32_t x, const int32_t z, const T1* const input_vertex_pointer, const int32_t image_width, const int32_t x_step, const int32_t z_step)
        {
            return static_cast<float>(geometry::get_y(input_vertex_pointer, x, z - z_step, image_width));
        }
    template<class T1>
        float northwest_y(const int32_t x, const int32_t z, const T1* const input_vertex_pointer, const int32_t image_width, const int32_t x_step, const int32_t z_step)
        {
            return static_cast<float>(geometry::get_y(input_vertex_pointer, x - x_step, z, image_width));
        }
    template<class T1>
        float northeast_y(const int32_t x, const int32_t z, const T1* const input_vertex_pointer, const int32_t image_width, const int32_t x_step, const int32_t z_step)
        {
            return static_cast<float>(geometry::get_y(input_vertex_pointer, x, z, image_width));
        }
    template<class T1>
        float center_y(const int32_t x, const int32_t z, const T1* const input_vertex_pointer, const int32_t image_width, const int32_t x_step, const int32_t z_step)
        {
            return static_cast<float>(southwest_y(x, z, input_vertex_pointer, image_width, x_step, z_step) +
                    southeast_y(x, z, input_vertex_pointer, image_width, x_step, z_step) +
                    northwest_y(x, z, input_vertex_pointer, image_width, x_step, z_step) +
                    northeast_y(x, z, input_vertex_pointer, image_width, x_step, z_step)) / 4.0f;
        }

    template<class T1>
        bool define_vertices(
                const T1* const input_vertex_pointer,
                const int32_t image_width,
                const int32_t image_height,
                const int32_t x_step,
                const int32_t z_step,
                const bool should_ylikuutio_use_real_texture_coordinates,
                std::vector<glm::vec3>& temp_vertices,
                std::vector<glm::vec2>& temp_UVs)
        {
            if (image_width < 0 || image_height < 0)
            {
                // Can not define vertices if image width < 0 or image height < 0.
                return false;
            }

            const int32_t actual_image_width = image_width / x_step;
            const int32_t actual_image_height = image_height / z_step;
            int32_t number_of_vertices = actual_image_width * actual_image_height;
            temp_vertices.reserve(number_of_vertices);
            temp_UVs.reserve(number_of_vertices);

            // Define the temporary vertices in a double loop.
            int32_t texture_y = 0;

            for (int32_t z = 0; z < image_height; z += z_step)
            {
                int32_t texture_x = 0;

                for (int32_t x = 0; x < image_width; x += x_step)
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

                    // `uv.x` is repeated 0, 1, 0, 1 ... when moving eastward.
                    // this causes the texture be mirrored horizontally for every other quad.
                    texture_x ^= 1;
                }

                // `uv.y` is repeated 0, 1, 0, 1 ... when moving southward.
                // this causes the texture be mirrored vertically for every other quad.
                texture_y ^= 1;
            }

            return true;
        }

    template<class T1>
        const bool interpolate_and_define_vertices_using_bilinear_interpolation(
                const T1* const input_vertex_pointer,
                const int32_t image_width,
                const int32_t image_height,
                const int32_t x_step,
                const int32_t z_step,
                const bool should_ylikuutio_use_real_texture_coordinates,
                std::vector<glm::vec3>& temp_vertices,
                std::vector<glm::vec2>& temp_UVs)
        {
            std::cout << "interpolating center vertices.\n";

            if (image_width < 2 || image_height < 2)
            {
                // Can not interpolate center vertices if image width < 2 or image height < 2.
                return false;
            }

            if (x_step <= 0 || z_step <= 0)
            {
                // Can not interpolate center vertices if x_step <= 0 or z_step <= 0.
                return false;
            }

            // Then, define the faces in a double loop.
            // Begin from index `z_step`.
            for (int32_t z = z_step; z < image_height; z += z_step)
            {
                // Begin from index `x_step`.
                for (int32_t x = x_step; x < image_width; x += x_step)
                {
                    // This corresponds to "f": specify a face (but here we specify 2 faces instead!).

                    // Interpolate y coordinate (altitude).
                    const float y = center_y(x, z, input_vertex_pointer, image_width, x_step, z_step);

                    // Create a new vertex using bilinear interpolation.
                    // This corresponds to "v": specify one vertex.
                    glm::vec3 vertex;
                    vertex.x = static_cast<GLfloat>(x) - 0.5f * x_step;
                    vertex.y = static_cast<GLfloat>(y);
                    vertex.z = static_cast<GLfloat>(z) - 0.5f * z_step;
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

            return true;
        }
}

#endif
