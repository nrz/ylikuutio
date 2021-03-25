// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef PI
#define PI 3.14159265359f
#endif

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

#include "png_heightmap_loader.hpp"
#include "heightmap_loader_struct.hpp"
#include "image_file_loader.hpp"
#include "code/ylikuutio/geometry/spherical_terrain_struct.hpp"
#include "code/ylikuutio/load/image_loader_struct.hpp"
#include "code/ylikuutio/memory/memory_templates.hpp"
#include "code/ylikuutio/triangulation/triangulate_quads_struct.hpp"
#include "code/ylikuutio/triangulation/quad_triangulation.hpp"
#include "code/ylikuutio/data/pi.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <memory>   // std::make_shared, std::shared_ptr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::load
{
    bool load_png_terrain(
            const yli::load::HeightmapLoaderStruct& heightmap_loader_struct,
            std::vector<glm::vec3>& out_vertices,
            std::vector<glm::vec2>& out_uvs,
            std::vector<glm::vec3>& out_normals,
            uint32_t& image_width,
            uint32_t& image_height,
            const std::string& color_channel)
    {
        if (heightmap_loader_struct.x_step < 1)
        {
            std::cerr << "ERROR: `yli::load::load_png_terrain`: `heightmap_loader_struct.x_step` is less than 1.\n";
            return false;
        }

        if (heightmap_loader_struct.z_step < 1)
        {
            std::cerr << "ERROR: `yli::load::load_png_terrain`: `heightmap_loader_struct.z_step` is less than 1.\n";
            return false;
        }

        uint32_t image_size = 0;

        std::shared_ptr<std::vector<uint8_t>> image_data = load_image_file(
                heightmap_loader_struct.filename,
                yli::load::ImageLoaderStruct(),
                image_width,
                image_height,
                image_size);

        if (image_data == nullptr)
        {
            std::cerr << "ERROR: `yli::load::load_png_terrain`: `image_data` is `nullptr`.\n";
            return false;
        }

        if (image_width < 2)
        {
            std::cerr << "ERROR: `yli::load::load_png_terrain`: image width is less than 2.\n";
            return false;
        }

        if (image_height < 2)
        {
            std::cerr << "ERROR: `yli::load::load_png_terrain`: image height is less than 2.\n";
            return false;
        }

        if (image_size != image_width * image_height)
        {
            std::cerr << "ERROR: `yli::load::load_png_terrain`: image size does not match image dimensions!\n";
            return false;
        }

        const uint32_t n_color_channels = image_data->size() / image_size;

        if (n_color_channels == 0)
        {
            std::cerr << "ERROR: `yli::load::load_png_terrain`: image data is too small for the image size!\n";
            return false;
        }

        if (n_color_channels * image_size != image_data->size())
        {
            std::cerr << "ERROR: `yli::load::load_png_terrain`: image data size does not match number of color channels and image size!\n";
            return false;
        }

        std::cout << n_color_channels << " color channel" << (n_color_channels > 1 ? "s" : "") << " in use.\n";
        yli::memory::flip_vertically(&(*image_data)[0], n_color_channels * image_width, image_height);

        // Define terrain size.
        const std::size_t terrain_size = image_width * image_height;

        const std::size_t line_size_in_bytes = n_color_channels * image_width;

        std::vector<float> vertex_data;
        vertex_data.reserve(terrain_size);

        // start processing image_data.
        for (std::size_t z = 0; z < image_height; z++)
        {
            const uint8_t* image_pointer = &(*image_data)[0] + z * line_size_in_bytes;

            for (std::size_t x = 0; x < image_width; x++)
            {
                std::size_t y;

                if (color_channel == "red")
                {
                    y = static_cast<float>(*(image_pointer));     // y-coordinate is the red (R) value.
                }
                else if (color_channel == "green" && n_color_channels >= 2)
                {
                    y = static_cast<float>(*(image_pointer + 1)); // y-coordinate is the green (G) value.
                }
                else if (color_channel == "blue" && n_color_channels >= 3)
                {
                    y = static_cast<float>(*image_pointer + 2);   // y-coordinate is the blue (B) value.
                }
                else if (color_channel == "mean" || color_channel == "all")
                {
                    float float_y { 0.0f };
                    for (std::size_t color_channel_i = 0; color_channel_i < n_color_channels; color_channel_i++)
                    {
                        float_y += static_cast<float>(*image_pointer + color_channel_i);
                    }

                    y = float_y / static_cast<float>(n_color_channels);
                }
                else
                {
                    std::cerr << "ERROR: invalid color channel: " << color_channel << "\n";
                    return false;
                }

                vertex_data.emplace_back(y);
                image_pointer += n_color_channels;
            }
        }

        std::cout << "color channel in use: " << color_channel << "\n";

        yli::triangulation::TriangulateQuadsStruct triangulate_quads_struct;
        triangulate_quads_struct.image_width = image_width;
        triangulate_quads_struct.image_height = image_height;
        triangulate_quads_struct.x_step = heightmap_loader_struct.x_step;
        triangulate_quads_struct.z_step = heightmap_loader_struct.z_step;
        triangulate_quads_struct.triangulation_type = heightmap_loader_struct.triangulation_type;
        triangulate_quads_struct.use_real_texture_coordinates = heightmap_loader_struct.use_real_texture_coordinates;

        return yli::triangulation::triangulate_quads(&vertex_data[0], triangulate_quads_struct, out_vertices, out_uvs, out_normals);
    }
}
