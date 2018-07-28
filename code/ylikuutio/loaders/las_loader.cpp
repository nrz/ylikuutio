#ifndef PI
#define PI 3.14159265359f
#endif

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

#include "las_loader.hpp"
#include "code/ylikuutio/triangulation/quad_triangulation.hpp"
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
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli
{
    namespace loaders
    {
        bool load_LASF_data(
                const std::string laser_scaling_file_name,
                std::vector<glm::vec3>& laser_points)
        {
            std::cout << "Loading LASF file " << laser_scaling_file_name << " ...\n";

            // Data read from the header of the LASF file
            uint8_t header[227];

            // Open the file
            const char* char_laser_scaling_file_name = laser_scaling_file_name.c_str();
            std::FILE* file = std::fopen(char_laser_scaling_file_name, "rb");
            if (!file)
            {
                std::cerr << laser_scaling_file_name << " could not be opened.\n";
                return false;
            }

            // Read the header, i.e. the 227 first bytes

            // If less than 227 bytes are read, it's a problem.
            // TODO: move hard-coded value 227 to a variable.
            if (std::fread(header, 1, 227, file) != 227)
            {
                std::cerr << "Too few bytes read when reading the file header. " << laser_scaling_file_name << " is not a correct LASF file.\n";
                std::fclose(file);
                return false;
            }

            // A LASF files always begins with "LASF"
            if ((header[0] != 'L') || (header[1] != 'A') || (header[2] != 'S') || (header[3] != 'F'))
            {
                std::cerr << "No LASF signature. " << laser_scaling_file_name << " is not a correct LASF file.\n";
                std::fclose(file);
                return false;
            }

            const uint32_t max_number_of_returns = 4;

            uint32_t sizes_of_point_record_formats[4];
            sizes_of_point_record_formats[0] = 20; // 4 + 4 + 4 + 2 + 1* + 1 + 1 + 1 + 2. 1*) 3 bits + 3 bits + 1 bit + 1 bit. 
            sizes_of_point_record_formats[1] = 28; // 4 + 4 + 4 + 2 + 1* + 1 + 1 + 1 + 2 + 8. 1*) 3 bits + 3 bits + 1 bit + 1 bit. 
            sizes_of_point_record_formats[2] = 26; // 4 + 4 + 4 + 2 + 1* + 1 + 1 + 1 + 2 + 2 + 2 + 2. 1*) 3 bits + 3 bits + 1 bit + 1 bit. 
            sizes_of_point_record_formats[3] = 34; // 4 + 4 + 4 + 2 + 1* + 1 + 1 + 1 + 2 + 8 + 2 + 2 + 2. 1*) 3 bits + 3 bits + 1 bit + 1 bit. 

            uint16_t* pointer_to_16_bit_header_data = (uint16_t*) (header + 94);
            const uint16_t header_size_in_bytes = *pointer_to_16_bit_header_data++;

            if (header_size_in_bytes != 227)
            {
                std::cerr << "Invalid header size in file " << laser_scaling_file_name << " (" << header_size_in_bytes << " bytes). Header size must be 227 bytes.\n";
                std::fclose(file);
                return false;
            }

            uint32_t* pointer_to_32_bit_header_data = (uint32_t*) (header + 96);

            const uint32_t offset_to_point_data = *pointer_to_32_bit_header_data++;
            const uint32_t number_of_variable_length_records = *pointer_to_32_bit_header_data++;

            uint8_t* pointer_to_8_bit_header_data = (uint8_t*) pointer_to_32_bit_header_data;

            const uint8_t point_data_formatID = *pointer_to_8_bit_header_data++;

            if (point_data_formatID > 3)
            {
                std::cerr << "invalid point data format ID: " << static_cast<int16_t>(point_data_formatID) << " in file " << laser_scaling_file_name << "\n";
                std::fclose(file);
                return false;
            }

            // OK, the point data format ID is valid (0, 1, 2 or 3).

            pointer_to_16_bit_header_data = (uint16_t*) pointer_to_8_bit_header_data;

            const uint8_t point_data_record_length = *pointer_to_16_bit_header_data++;

            pointer_to_32_bit_header_data = (uint32_t*) pointer_to_16_bit_header_data;

            const uint32_t number_of_point_records = *pointer_to_32_bit_header_data++;
            uint32_t number_of_points_by_record[max_number_of_returns + 1];

            for (uint32_t n_returns = 0; n_returns <= max_number_of_returns; n_returns++)
            {
                number_of_points_by_record[n_returns] = *pointer_to_32_bit_header_data++;
            }

            double* pointer_to_double_header_data = (double*) pointer_to_32_bit_header_data;

            const double x_scale_factor = *pointer_to_double_header_data++;
            const double y_scale_factor = *pointer_to_double_header_data++;
            const double z_scale_factor = *pointer_to_double_header_data++;
            const double x_offset = *pointer_to_double_header_data++;
            const double y_offset = *pointer_to_double_header_data++;
            const double z_offset = *pointer_to_double_header_data++;
            const double max_x = *pointer_to_double_header_data++;
            const double min_x = *pointer_to_double_header_data++;
            const double max_y = *pointer_to_double_header_data++;
            const double min_y = *pointer_to_double_header_data++;
            const double max_z = *pointer_to_double_header_data++;
            const double min_z = *pointer_to_double_header_data++;

            // Create a buffer.
            uint32_t size_of_point_data_record = sizes_of_point_record_formats[point_data_formatID];
            uint64_t point_data_size = static_cast<uint64_t>(number_of_point_records) * static_cast<uint64_t>(size_of_point_data_record);
            uint8_t* point_data = new uint8_t[point_data_size];

            if (point_data == nullptr)
            {
                std::cerr << "Reserving memory for point data failed.\n";
                std::fclose(file);
                return false;
            }

            // Move file pointer to the beginning of point data.
            if (fseek(file, offset_to_point_data, SEEK_SET) != 0)
            {
                std::cerr << "moving file pointer of file " << laser_scaling_file_name << " failed!\n";
                delete[] point_data;
                std::fclose(file);
                return false;
            }

            // Read the actual image data from the file into the buffer.
            if (std::fread(point_data, 1, point_data_size, file) != point_data_size)
            {
                std::cerr << "Error while reading " << laser_scaling_file_name << "\n";
                delete[] point_data;
                std::fclose(file);
                return false;
            }

            // Everything is in memory now, the file can be closed
            std::fclose(file);

            // Loop through point data, convert coordinates to `float` and store them in `laser_points`.
            int32_t* pointer_to_signed_32_bit_header_data = (int32_t*) point_data;

            for (uint32_t laser_point_i = 0; laser_point_i < number_of_point_records; laser_point_i++)
            {
                int32_t x_from_record = *pointer_to_signed_32_bit_header_data++;
                int32_t y_from_record = *pointer_to_signed_32_bit_header_data++;
                int32_t z_from_record = *pointer_to_signed_32_bit_header_data++;

                float x = static_cast<float>(x_scale_factor * x_from_record + x_offset);
                float y = static_cast<float>(y_scale_factor * y_from_record + y_offset);
                float z = static_cast<float>(z_scale_factor * z_from_record + z_offset);
                laser_points.push_back(glm::vec3(x, y, z));
            }

            delete[] point_data;

            return true;
        }
    }
}
