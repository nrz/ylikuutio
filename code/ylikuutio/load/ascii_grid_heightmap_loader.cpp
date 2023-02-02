// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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

#include "ascii_grid_heightmap_loader.hpp"
#include "heightmap_loader_struct.hpp"
#include "code/ylikuutio/geometry/spherical_terrain_struct.hpp"
#include "code/ylikuutio/triangulation/triangulate_quads_struct.hpp"
#include "code/ylikuutio/triangulation/quad_triangulation.hpp"
#include "code/ylikuutio/file/file_loader.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow, floor, ceil
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string, std::stoi
#include <vector>   // std::vector

namespace yli::load
{
    bool load_ascii_grid_terrain(
            const yli::load::HeightmapLoaderStruct& heightmap_loader_struct,
            std::vector<glm::vec3>& out_vertices,
            std::vector<glm::vec2>& out_uvs,
            std::vector<glm::vec3>& out_normals,
            uint32_t& image_width,
            uint32_t& image_height)
    {
        // Beginning of `L4133D.asc`.
        //
        // ncols        3000
        // nrows        3000
        // xllcorner    386000.000000000000
        // yllcorner    6672000.000000000000
        // cellsize     2.000000000000
        // NODATA_value  -9999.000
        // 34.315 34.467 34.441 34.260 33.972 33.564 33.229 33.130 33.102 33.024 32.902 32.669 32.305 32.013 31.937 31.893 31.831 31.832

        // Notes:
        // field           meaning
        // ncols           number of columns
        // nrows           number of rows
        // xllcorner       the x-coordinate of bottom left corner
        // yllcorner       the y-coordinate of bottom left corner (note: consider this as z-coordinate in Ylikuutio)
        // cellsize        grid resolution in meters
        // NODATA_value    the value used to indicate a missing value

        std::cout << "Loading ASCII grid file " << heightmap_loader_struct.filename << " ...\n";

        if (heightmap_loader_struct.x_step < 1)
        {
            std::cerr << "ERROR: `yli::load::load_ascii_grid_terrain`: `heightmap_loader_struct.x_step` is less than 1.\n";
            return false;
        }

        if (heightmap_loader_struct.z_step < 1)
        {
            std::cerr << "ERROR: `yli::load::load_ascii_grid_terrain`: `heightmap_loader_struct.z_step` is less than 1.\n";
            return false;
        }

        // Open the file
        const std::optional<std::string> file_content = yli::file::slurp(heightmap_loader_struct.filename);

        if (!file_content || file_content->empty())
        {
            std::cerr << "ERROR: " << heightmap_loader_struct.filename << " could not be opened, or the file is empty.\n";
            return false;
        }

        std::size_t file_content_i = 0;

        // All possible block identifier strings.
        const std::vector<std::string> number_strings_vector = { "-", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

        while (!yli::string::check_and_report_if_some_string_matches(*file_content, file_content_i, number_strings_vector))
        {
            file_content_i++;
        }

        const int32_t image_width_int32_t = yli::string::extract_int32_t_value_from_string(
                *file_content,
                file_content_i,
                " \n",
                "ncols");

        while (!yli::string::check_and_report_if_some_string_matches(*file_content, file_content_i, number_strings_vector))
        {
            file_content_i++;
        }

        const int32_t image_height_int32_t = yli::string::extract_int32_t_value_from_string(
                *file_content,
                file_content_i,
                " \n",
                "nrows");

        while (!yli::string::check_and_report_if_some_string_matches(*file_content, file_content_i, number_strings_vector))
        {
            file_content_i++;
        }

        yli::string::extract_float_value_from_string(
                *file_content,
                file_content_i,
                " \n",
                "xllcorner");

        while (!yli::string::check_and_report_if_some_string_matches(*file_content, file_content_i, number_strings_vector))
        {
            file_content_i++;
        }

        yli::string::extract_float_value_from_string(
                *file_content,
                file_content_i,
                " \n",
                "yllcorner");

        while (!yli::string::check_and_report_if_some_string_matches(*file_content, file_content_i, number_strings_vector))
        {
            file_content_i++;
        }

        yli::string::extract_float_value_from_string(
                *file_content,
                file_content_i,
                " \n",
                "cellsize");

        while (!yli::string::check_and_report_if_some_string_matches(*file_content, file_content_i, number_strings_vector))
        {
            file_content_i++;
        }

        yli::string::extract_float_value_from_string(
                *file_content,
                file_content_i,
                " \n",
                "nodata_value");

        if (image_width_int32_t < 2)
        {
            std::cerr << "ERROR: image width is less than 2.\n";
            return false;
        }

        if (image_height_int32_t < 2)
        {
            std::cerr << "ERROR: image height is less than 2.\n";
            return false;
        }

        image_width = static_cast<uint32_t>(image_width_int32_t);
        image_height = static_cast<uint32_t>(image_height_int32_t);

        std::vector<float> vertex_data;
        vertex_data.reserve(static_cast<std::size_t>(image_width) * static_cast<std::size_t>(image_height));

        // start processing image_data.
        std::cout << "Processing image data.\n";

        {
            int32_t last_percent = -1;

            for (uint32_t z = 0; z < image_height; z++)
            {
                // show progress in percents.
                int32_t current_percent = static_cast<int32_t>(floor(100.0f * (static_cast<float>(z) / static_cast<float>(image_height - 1))));

                if (current_percent > last_percent)
                {
                    std::cout << current_percent << "% ";
                    last_percent = current_percent;
                }

                for (uint32_t x = 0; x < image_width; x++)
                {
                    while (!yli::string::check_and_report_if_some_string_matches(*file_content, file_content_i, number_strings_vector))
                    {
                        file_content_i++;
                    }

                    vertex_data.emplace_back(yli::string::extract_float_value_from_string(
                                *file_content,
                                file_content_i,
                                " \n",
                                nullptr));
                }
            }
        }

        std::cout << "\n";

        if (heightmap_loader_struct.triangulate)
        {
            std::cout << "Triangulating ASCII grid data.\n";

            yli::triangulation::TriangulateQuadsStruct triangulate_quads_struct;
            triangulate_quads_struct.image_width = image_width;
            triangulate_quads_struct.image_height = image_height;
            triangulate_quads_struct.x_step = heightmap_loader_struct.x_step;
            triangulate_quads_struct.z_step = heightmap_loader_struct.z_step;
            triangulate_quads_struct.triangulation_type = heightmap_loader_struct.triangulation_type;
            triangulate_quads_struct.use_real_texture_coordinates = heightmap_loader_struct.use_real_texture_coordinates;

            return yli::triangulation::triangulate_quads(&vertex_data[0], triangulate_quads_struct, out_vertices, out_uvs, out_normals);
        }

        // No triangulation.
        // Just copy the vertices loaded from file to `out_vertices`.

        for (std::size_t i = 0, z = 0; i < vertex_data.size() && z < image_height; z++)
        {
            for (uint32_t x = 0; x < image_width; x++)
            {
                glm::vec3 vertex { static_cast<float>(x), vertex_data[i++], static_cast<float>(z) };
                out_vertices.emplace_back(vertex);
            }
        }

        return true;
    }
}
