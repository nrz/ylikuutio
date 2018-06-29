#ifndef PI
#define PI 3.14159265359f
#endif

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

#include "ascii_grid_loader.hpp"
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
#include <cmath>    // NAN, std::isnan, std::pow
#include <cstdio>   // std::FILE, std::fclose, std::fopen, std::fread, std::getchar, std::printf etc.
#include <iostream> // std::cout, std::cin, std::cerr
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string, std::stoi
#include <vector>   // std::vector

namespace loaders
{
    bool load_ASCII_grid(
            const std::string& ascii_grid_filename,
            std::vector<glm::vec3>& out_vertices,
            std::vector<glm::vec2>& out_UVs,
            std::vector<glm::vec3>& out_normals,
            const int32_t x_step,
            const int32_t z_step,
            const std::string& triangulation_type)
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

        std::cout << "Loading ASCII grid file " << ascii_grid_filename << " ...\n";

        // Open the file
        const std::string file_content = file::slurp(ascii_grid_filename);

        if (file_content.empty())
        {
            std::cerr << ascii_grid_filename << " could not be opened, or the file is empty.\n";
            return false;
        }

        std::size_t file_content_i = 0;

        // All possible block identifier strings.
        const std::vector<std::string> number_strings_vector = { "-", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

        while (!ylikuutio::string::check_and_report_if_some_string_matches(file_content, ++file_content_i, number_strings_vector));
        const int32_t image_width = ylikuutio::string::extract_int32_t_value_from_string(
                file_content,
                --file_content_i,
                (const char* const) " \n",
                (const char* const) "ncols");

        while (!ylikuutio::string::check_and_report_if_some_string_matches(file_content, ++file_content_i, number_strings_vector));
        const int32_t image_height = ylikuutio::string::extract_int32_t_value_from_string(
                file_content,
                --file_content_i,
                (const char* const) " \n",
                (const char* const) "nrows");

        while (!ylikuutio::string::check_and_report_if_some_string_matches(file_content, ++file_content_i, number_strings_vector));
        ylikuutio::string::extract_float_value_from_string(
                file_content,
                --file_content_i,
                (const char* const) " \n",
                (const char* const) "xllcorner");

        while (!ylikuutio::string::check_and_report_if_some_string_matches(file_content, ++file_content_i, number_strings_vector));
        ylikuutio::string::extract_float_value_from_string(
                file_content,
                --file_content_i,
                (const char* const) " \n",
                (const char* const) "yllcorner");

        while (!ylikuutio::string::check_and_report_if_some_string_matches(file_content, ++file_content_i, number_strings_vector));
        ylikuutio::string::extract_float_value_from_string(
                file_content,
                --file_content_i,
                (const char* const) " \n",
                (const char* const) "cellsize");

        while (!ylikuutio::string::check_and_report_if_some_string_matches(file_content, ++file_content_i, number_strings_vector));
        ylikuutio::string::extract_float_value_from_string(
                file_content,
                --file_content_i,
                (const char* const) " \n",
                (const char* const) "nodata_value");

        // note: the value of `image_height_in_use` can be adjusted here (for testing purposes).
        const int32_t image_height_in_use = image_height;

        float* vertex_data = new float[image_width * image_height_in_use];

        if (vertex_data == nullptr)
        {
            std::cerr << "Reserving memory for vertex data failed.\n";
            return false;
        }

        float* vertex_pointer = vertex_data;

        // start processing image_data.
        std::cout << "Processing image data.\n";

        int32_t last_percent = -1;
        int32_t current_percent = -1;

        for (int32_t z = 0; z < image_height_in_use; z++)
        {
            // show progress in percents.
            current_percent = static_cast<int32_t>(floor(100.0f * ((double) z / (double) (image_height_in_use - 1))));

            if (current_percent > last_percent)
            {
                std::cout << current_percent << "% ";
                last_percent = current_percent;
            }

            for (int32_t x = 0; x < image_width; x++)
            {
                while (!ylikuutio::string::check_and_report_if_some_string_matches(file_content, file_content_i, number_strings_vector))
                {
                    file_content_i++;
                }
                *vertex_pointer++ = ylikuutio::string::extract_float_value_from_string(
                        file_content,
                        --file_content_i,
                        (const char* const) " \n",
                        (const char* const) nullptr);
            }
        }

        std::cout << "\n";

        std::cout << "Triangulating ascii grid data.\n";

        geometry::TriangulateQuadsStruct triangulate_quads_struct;
        triangulate_quads_struct.image_width = image_width;
        triangulate_quads_struct.image_height = image_height_in_use;
        triangulate_quads_struct.x_step = x_step;
        triangulate_quads_struct.z_step = z_step;
        triangulate_quads_struct.triangulation_type = triangulation_type;
        triangulate_quads_struct.sphere_radius = NAN;
        triangulate_quads_struct.spherical_terrain_struct = geometry::SphericalTerrainStruct(); // not used, but is needed in the function call.

        bool result = geometry::triangulate_quads(vertex_data, triangulate_quads_struct, out_vertices, out_UVs, out_normals);
        delete[] vertex_data;
        return result;
    }
}
