// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2026 Antti Nuortimo.
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
#include <cmath>       // floor
#include <cstddef>     // std::size_t
#include <iostream>    // std::cout, std::cerr
#include <optional>    // std::optional
#include <stdint.h>    // uint32_t etc.
#include <string>      // std::string
#include <string_view> // std::string_view
#include <vector>      // std::vector

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
        // yllcorner       the y-coordinate of bottom left corner (note: consider this as y-coordinate in Ylikuutio)
        // cellsize        grid resolution in meters
        // NODATA_value    the value used to indicate a missing value

        std::cout << "Loading ASCII grid file " << heightmap_loader_struct.filename << " ...\n";

        if (heightmap_loader_struct.x_step < 1)
        {
            std::cerr << "ERROR: `yli::load::load_ascii_grid_terrain`: `heightmap_loader_struct.x_step` is less than 1.\n";
            return false;
        }

        if (heightmap_loader_struct.y_step < 1)
        {
            std::cerr << "ERROR: `yli::load::load_ascii_grid_terrain`: `heightmap_loader_struct.y_step` is less than 1.\n";
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

        while (!yli::string::check_and_report_if_some_string_matches<char>(*file_content, file_content_i, number_strings_vector))
        {
            file_content_i++;
        }

        std::optional<int32_t> image_width_int32_t = yli::string::extract_value_from_string<char, int32_t>(
                *file_content,
                file_content_i,
                " \n",
                "ncols");

        if (!image_width_int32_t.has_value())
        {
            std::cerr << "ERROR: `yli::load::load_ascii_grid_terrain`: extracting image width failed!\n";
            return false;
        }

        while (!yli::string::check_and_report_if_some_string_matches<char>(*file_content, file_content_i, number_strings_vector))
        {
            file_content_i++;
        }

        std::optional<int32_t> image_height_int32_t = yli::string::extract_value_from_string<char, int32_t>(
                *file_content,
                file_content_i,
                " \n",
                "nrows");

        if (!image_height_int32_t.has_value())
        {
            std::cerr << "ERROR: `yli::load::load_ascii_grid_terrain`: extracting image height failed!\n";
            return false;
        }

        while (!yli::string::check_and_report_if_some_string_matches<char>(*file_content, file_content_i, number_strings_vector))
        {
            file_content_i++;
        }

        yli::string::extract_value_from_string<char, float>(
                *file_content,
                file_content_i,
                " \n",
                "xllcorner");

        while (!yli::string::check_and_report_if_some_string_matches<char>(*file_content, file_content_i, number_strings_vector))
        {
            file_content_i++;
        }

        yli::string::extract_value_from_string<char, float>(
                *file_content,
                file_content_i,
                " \n",
                "yllcorner");

        while (!yli::string::check_and_report_if_some_string_matches<char>(*file_content, file_content_i, number_strings_vector))
        {
            file_content_i++;
        }

        yli::string::extract_value_from_string<char, float>(
                *file_content,
                file_content_i,
                " \n",
                "cellsize");

        while (!yli::string::check_and_report_if_some_string_matches<char>(*file_content, file_content_i, number_strings_vector))
        {
            file_content_i++;
        }

        yli::string::extract_value_from_string<char, float>(
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

        image_width = static_cast<uint32_t>(*image_width_int32_t);
        image_height = static_cast<uint32_t>(*image_height_int32_t);

        std::vector<float> vertex_data;
        vertex_data.reserve(static_cast<std::size_t>(image_width) * static_cast<std::size_t>(image_height));

        // start processing image_data.
        std::cout << "Processing image data.\n";

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
                    while (!yli::string::check_and_report_if_some_string_matches<char>(*file_content, file_content_i, number_strings_vector))
                    {
                        file_content_i++;
                    }

                    std::optional<float> z_coordinate = yli::string::extract_value_from_string<char, float>(
                            *file_content,
                            file_content_i,
                            " \n",
                            std::string_view(""));

                    if (!z_coordinate.has_value())
                    {
                        std::cerr << "ERROR: `yli::load::load_ascii_grid_terrain`: extracting z-coordinate failed!\n";
                        return false;
                    }

                    vertex_data.emplace_back(*z_coordinate);
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
            triangulate_quads_struct.y_step = heightmap_loader_struct.y_step;
            triangulate_quads_struct.use_real_texture_coordinates = heightmap_loader_struct.use_real_texture_coordinates;

            return yli::triangulation::triangulate_quads(&vertex_data[0], triangulate_quads_struct, out_vertices, out_uvs, out_normals);
        }

        // No triangulation.
        // Just copy the vertices loaded from file to `out_vertices`.

        for (std::size_t i = 0, y = 0; i < vertex_data.size() && y < image_height; y++)
        {
            const float scene_y = -1.0f * static_cast<float>(y);

            for (uint32_t x = 0; x < image_width; x++)
            {
                glm::vec3 vertex { static_cast<float>(x), scene_y, vertex_data[i++] };
                out_vertices.emplace_back(vertex);
            }
        }

        return true;
    }
}
