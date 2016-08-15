#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

#include "ascii_grid_loader.hpp"
#include "code/ylikuutio/triangulation/quad_triangulation.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"
#include "code/ylikuutio/common/globals.hpp"
#include "code/ylikuutio/common/global_variables.hpp"

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
    bool load_ascii_grid(
            std::string ascii_grid_file_name,
            std::vector<glm::vec3>& out_vertices,
            std::vector<glm::vec2>& out_UVs,
            std::vector<glm::vec3>& out_normals,
            std::string triangulation_type)
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

        std::cout << "Loading ascii grid file " << ascii_grid_file_name << " ...\n";

        // Open the file
        const char* char_ascii_grid_file_name = ascii_grid_file_name.c_str();
        std::FILE* file = std::fopen(char_ascii_grid_file_name, "rb");
        if (!file)
        {
            std::cerr << ascii_grid_file_name << " could not be opened.\n";
            return false;
        }

        // Find out file size.
        if (std::fseek(file, 0, SEEK_END) != 0)
        {
            std::cerr << "moving file pointer of file " << ascii_grid_file_name << " failed!\n";
            std::fclose(file);
            return false;
        }

        uint64_t file_size = std::ftell(file);

        // Move file pointer to the beginning of file.
        if (fseek(file, 0, SEEK_SET) != 0)
        {
            std::cerr << "moving file pointer of file " << ascii_grid_file_name << " failed!\n";
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
        std::fread(point_data, 1, file_size, file);

        // Everything is in memory now, the file can be closed
        std::fclose(file);

        // All possible block identifier strings.
        std::vector<std::string> number_strings_vector = { "-", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

        while (!string::check_and_report_if_some_string_matches(point_data, point_data_pointer, number_strings_vector))
        {
            point_data_pointer++;
        }
        int32_t image_width = string::extract_int32_t_value_from_string(--point_data_pointer, (char*) " \n", (const char*) "ncols");

        while (!string::check_and_report_if_some_string_matches(point_data, point_data_pointer, number_strings_vector))
        {
            point_data_pointer++;
        }
        int32_t image_height = string::extract_int32_t_value_from_string(--point_data_pointer, (char*) " \n", (const char*) "nrows");

        while (!string::check_and_report_if_some_string_matches(point_data, point_data_pointer, number_strings_vector))
        {
            point_data_pointer++;
        }
        float xllcorner = string::extract_float_value_from_string(--point_data_pointer, (char*) " \n", (const char*) "xllcorner");

        while (!string::check_and_report_if_some_string_matches(point_data, point_data_pointer, number_strings_vector))
        {
            point_data_pointer++;
        }
        float yllcorner = string::extract_float_value_from_string(--point_data_pointer, (char*) " \n", (const char*) "yllcorner");

        while (!string::check_and_report_if_some_string_matches(point_data, point_data_pointer, number_strings_vector))
        {
            point_data_pointer++;
        }
        float cellsize = string::extract_float_value_from_string(--point_data_pointer, (char*) " \n", (const char*) "cellsize");

        while (!string::check_and_report_if_some_string_matches(point_data, point_data_pointer, number_strings_vector))
        {
            point_data_pointer++;
        }
        float nodata_value = string::extract_float_value_from_string(--point_data_pointer, (char*) " \n", (const char*) "nodata_value");

        uint32_t image_height_in_use = 2000;

        float* vertex_data;
        vertex_data = new float[image_width * image_height_in_use];

        if (vertex_data == nullptr)
        {
            std::cerr << "Reserving memory for vertex data failed.\n";
            delete point_data;
            return false;
        }

        float* vertex_pointer;
        vertex_pointer = vertex_data;

        // start processing image_data.

        for (uint32_t z = 0; z < image_height_in_use; z++)
        {
            for (uint32_t x = 0; x < image_width; x++)
            {
                while (!string::check_and_report_if_some_string_matches(point_data, point_data_pointer, number_strings_vector))
                {
                    point_data_pointer++;
                }
                *vertex_pointer++ = string::extract_float_value_from_string(point_data_pointer, (char*) " \n", (const char*) nullptr);
            }
        }

        delete point_data;

        std::cout << "Triangulating ascii grid data.\n";

        TriangulateQuadsStruct triangulate_quads_struct;
        triangulate_quads_struct.image_width = image_width;
        triangulate_quads_struct.image_height = image_height_in_use;
        triangulate_quads_struct.triangulation_type = triangulation_type;
        triangulate_quads_struct.sphere_radius = NAN;
        triangulate_quads_struct.spherical_world_struct = SphericalWorldStruct(); // not used, but is needed in the function call.

        bool result = geometry::triangulate_quads(vertex_data, triangulate_quads_struct, out_vertices, out_UVs, out_normals);
        delete vertex_data;
        return true;
    }
}
