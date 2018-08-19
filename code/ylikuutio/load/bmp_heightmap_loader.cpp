#ifndef PI
#define PI 3.14159265359f
#endif

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

#include "bmp_heightmap_loader.hpp"
#include "bmp_loader.hpp"
#include "code/ylikuutio/geometry/spherical_terrain_struct.hpp"
#include "code/ylikuutio/triangulation/triangulate_quads_struct.hpp"
#include "code/ylikuutio/triangulation/quad_triangulation.hpp"
#include "code/ylikuutio/common/pi.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <cstddef>  // std::size_t
#include <cstdio>   // std::FILE, std::fclose, std::fopen, std::fread, std::getchar, std::printf etc.
#include <cstring>  // std::memcmp, std::strcmp, std::strlen, std::strncmp
#include <iostream> // std::cout, std::cin, std::cerr
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace load
    {
        bool load_BMP_terrain(
                const std::string& image_path,
                std::vector<glm::vec3>& out_vertices,
                std::vector<glm::vec2>& out_UVs,
                std::vector<glm::vec3>& out_normals,
                std::size_t* image_width_pointer,
                std::size_t* image_height_pointer,
                const std::string& color_channel,
                const std::size_t x_step,
                const std::size_t z_step,
                const std::string& triangulation_type)
        {
            if (x_step < 1 || z_step < 1)
            {
                return false;
            }

            if (image_width_pointer == nullptr || image_height_pointer == nullptr)
            {
                return false;
            }

            std::size_t image_size;

            std::size_t image_width;
            std::size_t image_height;

            uint8_t* image_data = load_BMP_file(image_path, image_width, image_height, image_size);

            *image_width_pointer = image_width;
            *image_height_pointer = image_height;

            if (image_width < 2 || image_height < 2)
            {
                delete[] image_data;
                return false;
            }

            // Define terrain size.
            std::size_t terrain_size = image_width * image_height;

            std::size_t line_size_in_bytes = image_size / image_height;

            uint8_t *image_pointer;
            image_pointer = image_data;

            float* vertex_data = new float[terrain_size];

            if (vertex_data == nullptr)
            {
                std::cerr << "Reserving memory for vertex data failed.\n";
                delete[] image_data;
                return false;
            }

            float* vertex_pointer;
            vertex_pointer = vertex_data;

            const char* char_color_channel = color_channel.c_str();

            // start processing image_data.
            for (std::size_t z = 0; z < image_height; z++)
            {
                image_pointer = image_data + z * line_size_in_bytes;

                for (std::size_t x = 0; x < image_width; x++)
                {
                    std::size_t y;

                    if (std::strcmp(char_color_channel, "blue") == 0)
                    {
                        y = static_cast<float>(*image_pointer);       // y-coordinate is the blue (B) value.
                    }
                    else if (std::strcmp(char_color_channel, "green") == 0)
                    {
                        y = static_cast<float>(*(image_pointer + 1)); // y-coordinate is the green (G) value.
                    }
                    else if (std::strcmp(char_color_channel, "red") == 0)
                    {
                        y = static_cast<float>(*(image_pointer + 2)); // y-coordinate is the red (R) value.
                    }

                    // y-coordinate is the mean of R, G, & B.
                    else if ((std::strcmp(char_color_channel, "mean") == 0) || (std::strcmp(char_color_channel, "all") == 0))
                    {
                        y = (static_cast<float>(*image_pointer) + static_cast<float>(*(image_pointer + 1)) + static_cast<float>(*(image_pointer + 2))) / 3.0f;
                    }
                    else
                    {
                        std::cerr << "invalid color channel!\n";
                        delete[] image_data;
                        delete[] vertex_data;
                        return false;
                    }

                    *vertex_pointer++ = y;
                    image_pointer += 3; // R, G, & B.
                }
            }

            delete[] image_data;

            std::cout << "color channel in use: " << color_channel << "\n";

            yli::geometry::TriangulateQuadsStruct triangulate_quads_struct;
            triangulate_quads_struct.image_width = image_width;
            triangulate_quads_struct.image_height = image_height;
            triangulate_quads_struct.x_step = x_step;
            triangulate_quads_struct.z_step = z_step;
            triangulate_quads_struct.triangulation_type = triangulation_type;
            triangulate_quads_struct.sphere_radius = NAN;
            triangulate_quads_struct.spherical_terrain_struct = yli::geometry::SphericalTerrainStruct(); // not used, but is needed in the function call.

            bool result = yli::geometry::triangulate_quads(vertex_data, triangulate_quads_struct, out_vertices, out_UVs, out_normals);
            delete[] vertex_data;
            return result;
        }
    }
}
