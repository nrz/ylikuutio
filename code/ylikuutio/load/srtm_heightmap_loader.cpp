// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif

#include "srtm_heightmap_loader.hpp"
#include "heightmap_loader_struct.hpp"
#include "code/ylikuutio/file/file_loader.hpp"
#include "code/ylikuutio/triangulation/triangulate_quads_struct.hpp"
#include "code/ylikuutio/triangulation/quad_triangulation.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>    // std::isnan
#include <iomanip>  // std::setfill, std::setw
#include <iostream> // std::cout, std::cerr
#include <optional> // std::optional
#include <sstream>  // std::stringstream
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::load
{
    bool load_srtm_terrain(
            const yli::load::HeightmapLoaderStruct& heightmap_loader_struct,
            const std::string& heightmap_directory,
            std::vector<glm::vec3>& out_vertices,
            std::vector<glm::vec2>& out_uvs,
            std::vector<glm::vec3>& out_normals,
            uint32_t& image_width,
            uint32_t& image_height)
    {
        // For SRTM worlds, the right heightmap filename must be resolved first.
        // The SRTM filenames contain always the southwest coordinate of the block.
        // Each single SRTM file contains 1 degree of latitude and 1 degree of longiture. File size is 1201x1201.
        // Precision is 3 arc-seconds in both latitude and longitude.

        // In coordinates (`latitude` and `longitude`) negative values mean south for latitude and west for longitude,
        // and positive value mean north for latitude and east for longitude.
        // Therefore the SRTM heightmap filename can be resolved by rounding both latitude and longitude down (towards negative infinity).

        if (heightmap_loader_struct.x_step < 1)
        {
            std::cerr << "ERROR: `yli::load::load_srtm_terrain`: `heightmap_loader_struct.x_step` is less than 1.\n";
            return false;
        }

        if (heightmap_loader_struct.y_step < 1)
        {
            std::cerr << "ERROR: `yli::load::load_srtm_terrain`: `heightmap_loader_struct.y_step` is less than 1.\n";
            return false;
        }

        const int32_t filename_latitude = std::floor(heightmap_loader_struct.latitude);
        const int32_t filename_longitude = std::floor(heightmap_loader_struct.longitude);

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

        const int SRTM_filename_n_of_latitude_chars = 2;
        const int SRTM_filename_n_of_longitude_chars = 3;

        latitude_stringstream << std::setw(SRTM_filename_n_of_latitude_chars) << std::setfill('0') << abs(filename_latitude);
        longitude_stringstream << std::setw(SRTM_filename_n_of_longitude_chars) << std::setfill('0') << abs(filename_longitude);

        const std::string latitude_string = latitude_stringstream.str();
        const std::string longitude_string = longitude_stringstream.str();

        const std::string hgt_suffix = ".hgt";

        const std::string abs_filename = heightmap_directory + south_north_char + latitude_string + west_east_char + longitude_string + hgt_suffix;

        std::cout << "Loading SRTM file " << abs_filename << " ...\n";

        const std::optional<std::vector<uint8_t>> file_content = yli::file::binary_slurp(abs_filename);

        if (!file_content || file_content->empty())
        {
            std::cerr << abs_filename << " could not be opened, or the file is empty.\n";
            return false;
        }

        const uint32_t true_image_width = 1201; // true image height is 1201 as well.
        image_width = 1200;  // rightmost column is not used (it is duplicated in the next SRTM file to the east).
        image_height = 1200; // bottom row is not used (it us duplicated in the next SRTM file to the south).

        std::vector<float> vertex_data;
        vertex_data.reserve(image_width * image_height);

        const uint8_t* image_pointer = &(*file_content)[0]; // start from northwestern corner.

        // start processing heightmap data.
        // 90 meters is for equator.

        std::cout << "Processing SRTM heightmap data.\n";

        {
            int32_t last_percent = -1;

            for (uint32_t y = 0; y < image_height; y++)
            {
                // show progress in percents.
                int32_t current_percent = static_cast<int32_t>(floor(100.0f * (static_cast<float>(y) / static_cast<float>(image_height - 1))));

                if (current_percent > last_percent)
                {
                    std::cout << current_percent << "% ";
                    last_percent = current_percent;
                }

                for (uint32_t x = 0; x < image_width; x++)
                {
                    uint32_t z = static_cast<uint32_t>(*image_pointer) << 8 | static_cast<uint32_t>(*(image_pointer + 1));

                    image_pointer += sizeof(int16_t);
                    vertex_data.emplace_back(static_cast<float>(z) / heightmap_loader_struct.divisor);
                }
                image_pointer += sizeof(int16_t) * (true_image_width - image_width);
            }
        }

        std::cout << "\n";

        yli::triangulation::TriangulateQuadsStruct triangulate_quads_struct;
        triangulate_quads_struct.image_width = image_width;
        triangulate_quads_struct.image_height = image_height;
        triangulate_quads_struct.x_step = heightmap_loader_struct.x_step;
        triangulate_quads_struct.y_step = heightmap_loader_struct.y_step;
        triangulate_quads_struct.use_real_texture_coordinates = heightmap_loader_struct.use_real_texture_coordinates;

        return yli::triangulation::triangulate_quads(&vertex_data[0], triangulate_quads_struct, out_vertices, out_uvs, out_normals);
    }
}
