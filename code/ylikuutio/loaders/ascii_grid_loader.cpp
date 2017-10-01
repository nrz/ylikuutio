#ifndef PI
#define PI 3.14159265359f
#endif

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

#include "ascii_grid_loader.hpp"
#include "code/ylikuutio/geometry/spherical_world_struct.hpp"
#include "code/ylikuutio/triangulation/triangulate_quads_struct.hpp"
#include "code/ylikuutio/triangulation/quad_triangulation.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"
#include "code/ylikuutio/common/pi.hpp"

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
            const std::string& ASCII_grid_file_name,
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

        std::cout << "Loading ascii grid file " << ASCII_grid_file_name << " ...\n";

        // Open the file
        const char* char_ASCII_grid_file_name = ASCII_grid_file_name.c_str();
        std::FILE* file = std::fopen(char_ASCII_grid_file_name, "rb");
        if (!file)
        {
            std::cerr << ASCII_grid_file_name << " could not be opened.\n";
            return false;
        }

        // Find out file size.
        if (std::fseek(file, 0, SEEK_END) != 0)
        {
            std::cerr << "moving file pointer of file " << ASCII_grid_file_name << " failed!\n";
            std::fclose(file);
            return false;
        }

        int64_t file_size = std::ftell(file);

        if (file_size < 0)
        {
            std::cerr << "ftell failed for the file " << ASCII_grid_file_name << " !\n";
            std::fclose(file);
            return false;
        }

        // Move file pointer to the beginning of file.
        if (fseek(file, 0, SEEK_SET) != 0)
        {
            std::cerr << "moving file pointer of file " << ASCII_grid_file_name << " failed!\n";
            std::fclose(file);
            return false;
        }

        // Reserve enough memory.
        char* point_data = new char[file_size];

        if (point_data == nullptr)
        {
            std::cerr << "Reserving memory for point data failed.\n";
            std::fclose(file);
            return false;
        }

        char* point_data_pointer = point_data;

        // Read the point data from the file into the buffer.
        if (std::fread(point_data, 1, file_size, file) != file_size)
        {
            std::cerr << "Error while reading " << ASCII_grid_file_name << "\n";
            std::fclose(file);
            delete[] point_data;
            return false;
        }

        // Everything is in memory now, the file can be closed
        std::fclose(file);

        // All possible block identifier strings.
        std::vector<std::string> number_strings_vector = { "-", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

        while (!string::check_and_report_if_some_string_matches(point_data, ++point_data_pointer, file_size, number_strings_vector));
        int32_t image_width = string::extract_int32_t_value_from_string(
                point_data,
                --point_data_pointer,
                file_size,
                (const char* const) " \n",
                (const char* const) "ncols");

        while (!string::check_and_report_if_some_string_matches(point_data, ++point_data_pointer, file_size, number_strings_vector));
        int32_t image_height = string::extract_int32_t_value_from_string(
                point_data,
                --point_data_pointer,
                file_size,
                (const char* const) " \n",
                (const char* const) "nrows");

        while (!string::check_and_report_if_some_string_matches(point_data, ++point_data_pointer, file_size, number_strings_vector));
        string::extract_float_value_from_string(
                point_data,
                --point_data_pointer,
                file_size,
                (const char* const) " \n",
                (const char* const) "xllcorner");

        while (!string::check_and_report_if_some_string_matches(point_data, ++point_data_pointer, file_size, number_strings_vector));
        string::extract_float_value_from_string(
                point_data,
                --point_data_pointer,
                file_size,
                (const char* const) " \n",
                (const char* const) "yllcorner");

        while (!string::check_and_report_if_some_string_matches(point_data, ++point_data_pointer, file_size, number_strings_vector));
        string::extract_float_value_from_string(
                point_data,
                --point_data_pointer,
                file_size,
                (const char* const) " \n",
                (const char* const) "cellsize");

        while (!string::check_and_report_if_some_string_matches(point_data, ++point_data_pointer, file_size, number_strings_vector));
        string::extract_float_value_from_string(
                point_data,
                --point_data_pointer,
                file_size,
                (const char* const) " \n",
                (const char* const) "nodata_value");

        // note: the value of `image_height_in_use` can be adjusted here (for testing purposes).
        int32_t image_height_in_use = image_height;

        float* vertex_data = new float[image_width * image_height_in_use];

        if (vertex_data == nullptr)
        {
            std::cerr << "Reserving memory for vertex data failed.\n";
            delete[] point_data;
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
                while (!string::check_and_report_if_some_string_matches(point_data, point_data_pointer, file_size, number_strings_vector))
                {
                    point_data_pointer++;
                }
                *vertex_pointer++ = string::extract_float_value_from_string(
                        point_data,
                        --point_data_pointer,
                        file_size,
                        (const char* const) " \n",
                        (const char* const) nullptr);
            }
        }

        delete[] point_data;

        std::cout << "Triangulating ascii grid data.\n";

        geometry::TriangulateQuadsStruct triangulate_quads_struct;
        triangulate_quads_struct.image_width = image_width;
        triangulate_quads_struct.image_height = image_height_in_use;
        triangulate_quads_struct.x_step = x_step;
        triangulate_quads_struct.z_step = z_step;
        triangulate_quads_struct.triangulation_type = triangulation_type;
        triangulate_quads_struct.sphere_radius = NAN;
        triangulate_quads_struct.spherical_world_struct = geometry::SphericalWorldStruct(); // not used, but is needed in the function call.

        bool result = geometry::triangulate_quads(vertex_data, triangulate_quads_struct, out_vertices, out_UVs, out_normals);
        delete[] vertex_data;
        return result;
    }
}
