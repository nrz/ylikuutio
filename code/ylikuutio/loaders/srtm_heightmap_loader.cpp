#ifndef PI
#define PI 3.14159265359f
#endif

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

#include "srtm_heightmap_loader.hpp"
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
#include <cstdio>   // std::FILE, std::fclose, std::fopen, std::fread, std::getchar, std::printf etc.
#include <iomanip>  // std::setfill, std::setw
#include <iostream> // std::cout, std::cin, std::cerr
#include <sstream>  // std::istringstream, std::ostringstream, std::stringstream
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace loaders
{
    bool load_SRTM_terrain(
            const std::string& image_path,
            const float latitude,
            const float longitude,
            const float planet_radius,
            const float divisor,
            std::vector<glm::vec3>& out_vertices,
            std::vector<glm::vec2>& out_UVs,
            std::vector<glm::vec3>& out_normals,
            const uint32_t x_step,
            const uint32_t z_step,
            const std::string& triangulation_type)
    {
        // For SRTM worlds, the right heightmap filename must be resolved first.
        // The SRTM filenames contain always the southwest coordinate of the block.
        // Each single SRTM file contains 1 degree of latitude and 1 degree of longiture. File size is 1201x1201.
        // Precision is 3 arc-seconds in both latitude and longitude.

        // In coordinates (`latitude` and `longitude`) negative values mean south for latitude and west for longitude,
        // and positive value mean north for latitude and east for longitude.
        // Therefore the SRTM heightmap filename can be resolved by rounding both latitude and longitude down (towards negative infinity).

        int32_t filename_latitude = std::floor(latitude);
        int32_t filename_longitude = std::floor(longitude);

        float southern_latitude = std::floor(latitude);
        float western_longitude = std::floor(longitude);

        float northern_latitude = southern_latitude + 1.0f;
        float eastern_longitude = western_longitude + 1.0f;

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

        uint32_t SRTM_filename_n_of_latitude_chars = 2;
        uint32_t SRTM_filename_n_of_longitude_chars = 3;

        latitude_stringstream << std::setw(SRTM_filename_n_of_latitude_chars) << std::setfill('0') << abs(filename_latitude);
        longitude_stringstream << std::setw(SRTM_filename_n_of_longitude_chars) << std::setfill('0') << abs(filename_longitude);

        std::string latitude_string = latitude_stringstream.str();
        std::string longitude_string = longitude_stringstream.str();

        std::string hgt_suffix = ".hgt";

        std::string abs_image_path = image_path + south_north_char + latitude_string + west_east_char + longitude_string + hgt_suffix;

        std::cout << "Loading SRTM file " << abs_image_path << " ...\n";

        // Open the file
        const char* char_image_path = abs_image_path.c_str();
        std::FILE* file = std::fopen(char_image_path, "rb");
        if (!file)
        {
            std::cerr << abs_image_path << " could not be opened.\n";
            return false;
        }

        uint32_t true_image_width = 1201;
        uint32_t true_image_height = 1201;
        uint32_t image_width_in_use = 1200;
        uint32_t image_height_in_use = 1200;
        uint32_t image_size = sizeof(int16_t) * true_image_width * true_image_height;

        // Create a buffer.
        // Actual 16-bit big-endian signed integer heightmap data.
        uint8_t* image_data = new uint8_t[image_size];

        if (image_data == nullptr)
        {
            std::cerr << "Reserving memory for image data failed.\n";
            std::fclose(file);
            return false;
        }

        // Read the actual image data from the file into the buffer.
        if (std::fread(image_data, 1, image_size, file) != image_size)
        {
            std::cerr << "Error while reading " << image_path << "\n";
            std::fclose(file);
            delete[] image_data;
            return false;
        }

        // Everything is in memory now, the file can be closed
        std::fclose(file);

        float* vertex_data = new float[image_width_in_use * image_height_in_use];

        if (vertex_data == nullptr)
        {
            std::cerr << "Reserving memory for vertex data failed.\n";
            delete[] image_data;
            std::fclose(file);
            return false;
        }

        uint8_t *image_pointer;
        image_pointer = image_data + sizeof(int16_t) * (true_image_height - 1) * true_image_width; // start from southwestern corner.

        float* vertex_pointer;
        vertex_pointer = vertex_data;

        // start processing image_data.
        // 90 meters is for equator.

        // FIXME: this is a temporary testing code with a hardcoded start from the southwestern corner.
        // TODO: write a proper code for loading the appropriate chunks (based on real spherical coordinates) into VBOs!

        // start processing image_data.
        std::cout << "Processing SRTM heightmap data.\n";

        int32_t last_percent = -1;
        int32_t current_percent = -1;

        for (uint32_t z = 0; z < image_height_in_use; z++)
        {
            // show progress in percents.
            current_percent = static_cast<int32_t>(floor(100.0f * ((double) z / (double) (image_height_in_use - 1))));

            if (current_percent > last_percent)
            {
                std::cout << current_percent << "% ";
                last_percent = current_percent;
            }

            for (uint32_t x = 0; x < image_width_in_use; x++)
            {
                uint32_t y;
                y = static_cast<uint32_t>(*image_pointer) << 8 | static_cast<uint32_t>(*(image_pointer + 1));

                image_pointer += sizeof(int16_t);
                *vertex_pointer++ = static_cast<float>(y) / divisor;
            }
            image_pointer -= sizeof(int16_t) * (image_width_in_use + true_image_width);
        }

        std::cout << "\n";

        delete[] image_data;

        yli::geometry::SphericalTerrainStruct spherical_terrain_struct;
        spherical_terrain_struct.southern_latitude = southern_latitude; // must be float, though SRTM data is split between full degrees.
        spherical_terrain_struct.northern_latitude = northern_latitude; // must be float, though SRTM data is split between full degrees.
        spherical_terrain_struct.western_longitude = western_longitude; // must be float, though SRTM data is split between full degrees.
        spherical_terrain_struct.eastern_longitude = eastern_longitude; // must be float, though SRTM data is split between full degrees.

        yli::geometry::TriangulateQuadsStruct triangulate_quads_struct;
        triangulate_quads_struct.image_width = image_width_in_use;
        triangulate_quads_struct.image_height = image_height_in_use;
        triangulate_quads_struct.x_step = x_step;
        triangulate_quads_struct.z_step = z_step;
        triangulate_quads_struct.triangulation_type = triangulation_type;
        triangulate_quads_struct.sphere_radius = planet_radius;
        triangulate_quads_struct.spherical_terrain_struct = spherical_terrain_struct;

        bool result = yli::geometry::triangulate_quads(vertex_data, triangulate_quads_struct, out_vertices, out_UVs, out_normals);
        delete[] vertex_data;
        return result;
    }
}
