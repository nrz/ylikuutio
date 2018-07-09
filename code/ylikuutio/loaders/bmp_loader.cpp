#include "bmp_loader.hpp"
#include "code/ylikuutio/file/file_loader.hpp"
#include "code/ylikuutio/memory/memory_templates.hpp"

// Include standard headers
#include <algorithm> // std::copy
#include <cstddef>  // std::size_t
#include <cstdio>   // std::FILE, std::fclose, std::fopen, std::fread, std::getchar, std::printf etc.
#include <iostream> // std::cout, std::cin, std::cerr
#include <limits>   // std::numeric_limits
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <vector>   // std::vector

namespace loaders
{
    uint8_t* load_BMP_file(
            const std::string& bmp_filename,
            int32_t& image_width,
            int32_t& image_height,
            std::size_t& image_size)
    {
        std::cout << "Loading BMP file " << bmp_filename << " ...\n";

        // Open the file
        const std::vector<uint8_t> file_content = yli::file::binary_slurp(bmp_filename);

        if (file_content.empty())
        {
            std::cerr << bmp_filename << " could not be opened, or the file is empty.\n";
            return nullptr;
        }

        const std::size_t header_size = 54;

        if (file_content.size() < header_size)
        {
            // BMP header size is 54 bytes.
            std::cerr << bmp_filename << " is not a correct BMP file.\n";
            return nullptr;
        }

        if (file_content[0] != 'B' || file_content[1] != 'M')
        {
            // BMP begins always with "BM".
            std::cerr << bmp_filename << " is not a correct BMP file.\n";
            return nullptr;
        }

        uint8_t* file_content_uint8_t = (uint8_t*) file_content.data();

        // The start offset of pixel array in file.
        uint32_t pixel_array_start_offset = yli::memory::read_nonaligned_32_bit<uint8_t, uint32_t>(file_content_uint8_t, 0x0a);

        if (pixel_array_start_offset >= file_content.size())
        {
            std::cerr << "is not a correct BMP file.\n";
            return nullptr;
        }

        // Make sure this is a 24bpp file
        uint32_t bits_per_pixel = yli::memory::read_nonaligned_32_bit<uint8_t, uint32_t>(file_content_uint8_t, 0x1c);

        if (bits_per_pixel != 24)
        {
            std::cerr << "not a correct 24-bit BMP file.\n";
            return nullptr;
        }

        uint32_t compression_type = yli::memory::read_nonaligned_32_bit<uint8_t, uint32_t>(file_content_uint8_t, 0x1e);

        if (compression_type != 0)
        {
            std::cerr << "not a correct uncompressed 24-bit BMP file.\n";
            return nullptr;
        }

        // Read the information about the image
        uint32_t image_size_uint32_t = yli::memory::read_nonaligned_32_bit<uint8_t, uint32_t>(file_content_uint8_t, 0x22);

        if (image_size_uint32_t > 2147483647)
        {
            std::cerr << "BMP file is too big, size: " << image_size_uint32_t << " bytes.\n";
            return nullptr;
        }

        image_size = static_cast<std::size_t>(image_size_uint32_t);
        std::cout << "image size is " << image_size << " bytes.\n";

        image_width = yli::memory::read_nonaligned_32_bit<uint8_t, int32_t>(file_content_uint8_t, 0x12);
        image_height = yli::memory::read_nonaligned_32_bit<uint8_t, int32_t>(file_content_uint8_t, 0x16);

        // Some BMP files are misformatted, guess missing information
        if (image_size == 0)
        {
            int64_t number_of_pixels = static_cast<int64_t>(image_width) * image_height;

            if (number_of_pixels > std::numeric_limits<std::size_t>::max() / 4)
            {
                std::cerr << "BMP file is too big, number of pixels: " << number_of_pixels << "\n";
                return nullptr;
            }

            image_size = number_of_pixels * 3; // 3 : one byte for each Red, Green and Blue component
        }

        // Create a buffer.
        uint8_t* image_data = new uint8_t[image_size];

        if (image_data == nullptr)
        {
            std::cerr << "Reserving memory for image data failed.\n";
            return nullptr;
        }

        std::copy(file_content.begin() + pixel_array_start_offset, file_content.end(), image_data);

        return image_data;
    }
}
