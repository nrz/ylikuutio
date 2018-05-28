#include "bmp_loader.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <cstdio>   // std::FILE, std::fclose, std::fopen, std::fread, std::getchar, std::printf etc.
#include <iostream> // std::cout, std::cin, std::cerr
#include <limits>   // std::numeric_limits
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string

namespace loaders
{
    uint8_t* load_BMP_file(
            const std::string image_path,
            int32_t& image_width,
            int32_t& image_height,
            std::size_t& image_size)
    {
        std::cout << "Loading BMP file " << image_path << " ...\n";

        const uint32_t header_size = 54;

        // Data read from the header of the BMP file
        uint8_t header[header_size];
        // Actual RGB image data.
        uint8_t* image_data;

        // Open the file
        const char* char_image_path = image_path.c_str();
        std::FILE* file = std::fopen(char_image_path, "rb");
        if (!file)
        {
            std::cerr << image_path << " could not be opened.\n";
            return nullptr;
        }

        // Read the header, i.e. the 54 first bytes

        // If less than 54 bytes are read, it's a problem.
        if (std::fread(header, 1, header_size, file) != header_size)
        {
            std::cerr << "not a correct BMP file.\n";
            std::fclose(file);
            return nullptr;
        }

        // The start offset of pixel array in file.
        uint32_t pixel_array_start_offset = header[0x0a];

        // A BMP files always begins with "BM"
        if ((header[0] != 'B') || (header[1] != 'M'))
        {
            std::cerr << "not a correct BMP file.\n";
            std::fclose(file);
            return nullptr;
        }

        // Make sure this is a 24bpp file
        if (*(uint32_t*) &header[0x1e] != 0)
        {
            std::cerr << "not a correct BMP file.\n";
            std::fclose(file);
            return nullptr;
        }

        if (*(uint32_t*) &header[0x1c] != 24)
        {
            std::cerr << "not a correct BMP file.\n";
            std::fclose(file);
            return nullptr;
        }

        // Read the information about the image
        uint32_t image_size_uint32_t = *(uint32_t*) &header[0x22];
        if (image_size_uint32_t > 2147483647)
        {
            std::cerr << "BMP file is too big, size: " << image_size_uint32_t << " bytes.\n";
            std::fclose(file);
            return nullptr;
        }

        image_size = static_cast<std::size_t>(image_size_uint32_t);
        image_width = *(int32_t*) &header[0x12];
        image_height = *(int32_t*) &header[0x16];

        std::cout << "image size is " << image_size << " bytes.\n";

        // Some BMP files are misformatted, guess missing information
        if (image_size == 0)
        {
            int64_t number_of_pixels = static_cast<int64_t>(image_width) * image_height;

            if (number_of_pixels > std::numeric_limits<std::size_t>::max() / 4)
            {
                std::cerr << "BMP file is too big, number of pixels: " << number_of_pixels << "\n";
                std::fclose(file);
                return nullptr;
            }

            image_size = number_of_pixels * 3; // 3 : one byte for each Red, Green and Blue component
        }

        // Create a buffer.
        image_data = new uint8_t[image_size];

        if (image_data == nullptr)
        {
            std::cerr << "Reserving memory for image data failed.\n";
            std::fclose(file);
            return nullptr;
        }

        // Move file pointer to the start of the pixel array.
        if (std::fseek(file, pixel_array_start_offset, SEEK_SET) != 0)
        {
            std::cerr << "Moving BMP file position indicator failed.\n";
            std::fclose(file);
            delete[] image_data;
            return nullptr;
        }

        // Read the actual image data from the file into the buffer.
        if (std::fread(image_data, 1, image_size, file) != image_size)
        {
            std::cerr << "Reading image data from file failed.\n";
            std::fclose(file);
            delete[] image_data;
            return nullptr;
        }

        // Everything is in memory now, so the file can be closed.
        std::fclose(file);

        return image_data;
    }
}
