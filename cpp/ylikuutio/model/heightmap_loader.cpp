#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

#include "heightmap_loader.hpp"
#include "cpp/ylikuutio/common/triangulation.hpp"
#include "cpp/ylikuutio/common/globals.hpp"

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
#include <cmath>    // NAN
#include <cstdio>   // std::FILE, std::fclose, std::fopen, std::fread, std::getchar, std::printf etc.
#include <cstring>  // strcmp
#include <iostream> // std::cout, std::cin, std::cerr
#include <string>   // std::string
#include <string.h> // memcmp, strcmp, strlen
#include <vector>   // std::vector
#include <stdint.h> // uint32_t etc.
#include <sstream>  // stringstream etc.
#include <iomanip>  // setw, setfill etc.

#define SRTM_FILENAME_N_OF_LATITUDE_CHARS 2
#define SRTM_FILENAME_N_OF_LONGITUDE_CHARS 3

namespace model
{
    bool load_BMP_world(
            std::string image_path,
            std::vector<glm::vec3> &out_vertices,
            std::vector<glm::vec2> &out_UVs,
            std::vector<glm::vec3> &out_normals,
            GLuint &image_width,
            GLuint &image_height,
            std::string color_channel,
            std::string triangulation_type)
    {
        std::cout << "Loading BMP file " << image_path << " ...\n";

        // Data read from the header of the BMP file
        unsigned char header[54];
        uint32_t dataPos;
        uint32_t imageSize;
        // Actual RGB image data.
        uint8_t *image_data;

        // Open the file
        const char* char_image_path = image_path.c_str();
        std::FILE* file = std::fopen(char_image_path, "rb");
        if (!file)
        {
            std::cerr << image_path << " could not be opened.\n";
            return false;
        }

        // Read the header, i.e. the 54 first bytes

        // If less than 54 bytes are read, it's a problem.
        if (std::fread(header, 1, 54, file) != 54)
        {
            std::cerr << "not a correct BMP file.\n";
            return false;
        }

        // A BMP files always begins with "BM"
        if ((header[0] != 'B') || (header[1] != 'M'))
        {
            std::cerr << "not a correct BMP file.\n";
            return false;
        }

        // Make sure this is a 24bpp file
        if (*(uint32_t*) & (header[0x1E]) != 0)
        {
            std::cerr << "not a correct BMP file.\n";
            return false;
        }

        if (*(uint32_t*) & (header[0x1C]) != 24)
        {
            std::cerr << "not a correct BMP file.\n";
            return false;
        }

        // Read the information about the image
        dataPos      = *(uint32_t*) & (header[0x0A]);
        imageSize    = *(uint32_t*) & (header[0x22]);
        image_width  = *(uint32_t*) & (header[0x12]);
        image_height = *(uint32_t*) & (header[0x16]);

        // Define world size.
        uint32_t world_size = image_width * image_height;

        // Some BMP files are misformatted, guess missing information
        if (imageSize == 0)
        {
            imageSize = image_width * image_height * 3; // 3 : one byte for each Red, Green and Blue component
        }

        if (dataPos == 0)
        {
            dataPos = 54; // The BMP header is done that way
        }

        // Create a buffer.
        image_data = new uint8_t [imageSize];

        // Read the actual image data from the file into the buffer.
        std::fread(image_data, 1, imageSize, file);

        // Everything is in memory now, the file can be closed
        std::fclose(file);

        GLuint* vertex_data;
        vertex_data = new GLuint [world_size];

        uint8_t *image_pointer;
        image_pointer = image_data;

        GLuint* vertex_pointer;
        vertex_pointer = vertex_data;

        const char* char_color_channel = color_channel.c_str();

        // start processing image_data.
        for (GLuint z = 0; z < image_height; z++)
        {
            for (GLuint x = 0; x < image_width; x++)
            {
                GLuint y;

                if (strcmp(char_color_channel, "blue") == 0)
                {
                    y = (GLuint) *image_pointer;       // y-coordinate is the blue (B) value.
                }
                else if (strcmp(char_color_channel, "green") == 0)
                {
                    y = (GLuint) *(image_pointer + 1); // y-coordinate is the green (G) value.
                }
                else if (strcmp(char_color_channel, "red") == 0)
                {
                    y = (GLuint) *(image_pointer + 2); // y-coordinate is the red (R) value.
                }
                // y-coordinate is the mean of R, G, & B.
                else if ((strcmp(char_color_channel, "mean") == 0) || (strcmp(char_color_channel, "all") == 0))
                {
                    y = (((GLuint) *image_pointer) + ((GLuint) *(image_pointer + 1)) + ((GLuint) *(image_pointer + 2))) / 3;
                }
                else
                {
                    std::cerr << "invalid color channel!\n";
                    return false;
                }

                // std::cout << color_channel << " color channel value at (" << x << ", " << z << "): " << y << ".\n";
                *vertex_pointer++ = y;
                image_pointer += 3; // R, G, & B.
            }
        }
        std::cout << "color channel in use: " << color_channel << "\n";

        TriangulateQuadsStruct triangulate_quads_struct;
        triangulate_quads_struct.input_vertex_pointer = vertex_data;
        triangulate_quads_struct.image_width = image_width;
        triangulate_quads_struct.image_height = image_height;
        triangulate_quads_struct.triangulation_type = triangulation_type;
        triangulate_quads_struct.sphere_radius = NAN;
        triangulate_quads_struct.spherical_world_struct = SphericalWorldStruct(); // not used, but is needed in the function call.

        return geometry::triangulate_quads(triangulate_quads_struct, out_vertices, out_UVs, out_normals);
    }

    bool load_SRTM_world(
            std::string image_path,
            double latitude,
            double longitude,
            std::vector<glm::vec3> &out_vertices,
            std::vector<glm::vec2> &out_UVs,
            std::vector<glm::vec3> &out_normals,
            std::string triangulation_type)
    {
        // For SRTM worlds, the right heightmap filename must be resolved first.
        // The SRTM filenames contain always the southwest coordinate of the block.
        // Each single SRTM file contains 1 degree of latitude and 1 degree of longiture. File size is 1201x1201.
        // Precision is 3 arc-seconds in both latitude and longitude.

        // In coordinates (`latitude` and `longitude`) negative values mean south for latitude and west for longitude,
        // and positive value mean north for latitude and east for longitude.
        // Therefore the SRTM heightmap filename can be resolved by rounding both latitude and longitude down (towards negative infinity).

        int32_t filename_latitude = floor(latitude);
        int32_t filename_longitude = floor(longitude);

        double southern_latitude = floor(latitude);
        double western_longitude = floor(longitude);

        double northern_latitude = southern_latitude + 1.0f;
        double eastern_longitude = western_longitude + 1.0f;

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

        latitude_stringstream << std::setw(SRTM_FILENAME_N_OF_LATITUDE_CHARS) << std::setfill('0') << abs(filename_latitude);
        longitude_stringstream << std::setw(SRTM_FILENAME_N_OF_LONGITUDE_CHARS) << std::setfill('0') << abs(filename_longitude);

        std::string latitude_string = latitude_stringstream.str();
        std::string longitude_string = longitude_stringstream.str();

        std::string hgt_suffix = ".hgt";

        std::string abs_image_path = image_path + south_north_char + latitude_string + west_east_char + longitude_string + hgt_suffix;

        std::cout << "Loading SRTM file " << abs_image_path << " ...\n";

        uint32_t dataPos;
        uint32_t imageSize;
        uint32_t true_image_width, true_image_height, image_width_in_use, image_height_in_use;
        // Actual 16-bit big-endian signed integer heightmap data.
        uint8_t *image_data;

        // Open the file
        const char* char_image_path = abs_image_path.c_str();
        std::FILE* file = std::fopen(char_image_path, "rb");
        if (!file)
        {
            std::cerr << abs_image_path << " could not be opened.\n";
            return false;
        }

        true_image_width  = 1201;
        true_image_height = 1201;
        image_width_in_use  = 1200;
        image_height_in_use = 1200;
        imageSize = sizeof(int16_t) * true_image_width * true_image_height;

        // Create a buffer.
        image_data = new uint8_t [imageSize];

        // Read the actual image data from the file into the buffer.
        std::fread(image_data, 1, imageSize, file);

        // Everything is in memory now, the file can be closed
        std::fclose(file);

        GLuint* vertex_data;
        vertex_data = new GLuint [image_width_in_use * image_height_in_use];

        uint8_t *image_pointer;
        image_pointer = image_data + sizeof(int16_t) * (true_image_height - 1) * true_image_width; // start from southwestern corner.

        GLuint* vertex_pointer;
        vertex_pointer = vertex_data;

        // start processing image_data.
        // 90 meters is for equator.

        // FIXME: this is a temporary testing code with a hardcoded start from the southwestern corner.
        // TODO: write a proper code for loading the appropriate chunks (based on real spherical coordinates) into VBOs!

        for (GLuint z = 0; z < image_height_in_use; z++)
        {
            for (GLuint x = 0; x < image_width_in_use; x++)
            {
                GLuint y;
                y = ((((GLuint) *image_pointer) << 8) | ((GLuint) *(image_pointer + 1)));

                image_pointer += sizeof(int16_t);
                *vertex_pointer++ = y;
            }
            image_pointer -= sizeof(int16_t) * (image_width_in_use + true_image_width);
        }

        SphericalWorldStruct spherical_world_struct;
        spherical_world_struct.southern_latitude = southern_latitude; // must be double, though SRTM data is split between full degrees.
        spherical_world_struct.northern_latitude = northern_latitude; // must be double, though SRTM data is split between full degrees.
        spherical_world_struct.western_longitude = western_longitude; // must be double, though SRTM data is split between full degrees.
        spherical_world_struct.eastern_longitude = eastern_longitude; // must be double, though SRTM data is split between full degrees.

        TriangulateQuadsStruct triangulate_quads_struct;
        triangulate_quads_struct.input_vertex_pointer = vertex_data;
        triangulate_quads_struct.image_width = image_width_in_use;
        triangulate_quads_struct.image_height = image_height_in_use;
        triangulate_quads_struct.triangulation_type = triangulation_type;
        triangulate_quads_struct.sphere_radius = EARTH_RADIUS;
        triangulate_quads_struct.spherical_world_struct = spherical_world_struct;

        return geometry::triangulate_quads(triangulate_quads_struct, out_vertices, out_UVs, out_normals);
    }
}
