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

#include "png_loader.hpp"
#include "code/ylikuutio/load/image_loader_struct.hpp"
#include "code/ylikuutio/memory/memory_templates.hpp"

#include <png.h>

// Include standard headers
#include <algorithm> // std::copy
#include <array>     // std::array
#include <cstddef>   // std::size_t
#include <iostream>  // std::cout, std::cerr
#include <limits>    // std::numeric_limits
#include <memory>    // std::make_shared, std::shared_ptr
#include <stdint.h>  // uint32_t etc.
#include <string>    // std::string
#include <vector>    // std::vector

namespace yli::load
{
    std::shared_ptr<std::vector<uint8_t>> load_png_file(
            const std::string& filename,
            const yli::load::ImageLoaderStruct& image_loader_struct,
            uint32_t& image_width,
            uint32_t& image_height,
            uint32_t& image_size,
            uint32_t& n_color_channels)
    {
        std::cout << "Loading PNG file " << filename << " ...\n";

        FILE *fp = fopen(filename.c_str(), "rb");

        if (fp == nullptr)
        {
            std::cerr << filename << "ERROR: `yli::load::load_png_file`: opening file " << filename << " failed!\n";
            return nullptr;
        }

        png_voidp user_error_ptr = nullptr;
        png_error_ptr error_fn = nullptr;
        png_error_ptr warning_fn = nullptr;
        png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, user_error_ptr, error_fn, warning_fn);

        if (png_ptr == nullptr)
        {
            std::cerr << filename << "ERROR: `yli::load::load_png_file`: creating PNG read struct failed!\n";
            fclose(fp);
            return nullptr;
        }

        png_infop info_ptr = png_create_info_struct(png_ptr);

        if (info_ptr == nullptr)
        {
            std::cerr << filename << "ERROR: `yli::load::load_png_file`: creating PNG info struct failed!\n";
            png_destroy_read_struct(&png_ptr, (png_infopp) nullptr, (png_infopp) nullptr);
            fclose(fp);
            return nullptr;
        }

        // Note: no `setjmp` in use here.

        png_init_io(png_ptr, fp);

        // Check for magic number of the PNG file.

        constexpr std::size_t header_size_in_bytes { 4 };
        std::array<uint8_t, header_size_in_bytes> header  { 0x49, 'P', 'N', 'G' };
        if (fread(header.data(), 1, header_size_in_bytes, fp) != header_size_in_bytes)
        {
            std::cerr << filename << "ERROR: `yli::load::load_png_file`: reading header of " << filename << " failed!\n";
            png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
            fclose(fp);
            return nullptr;
        }

        if (png_sig_cmp(header.data(), 0, header_size_in_bytes))
        {
            std::cerr << filename << "ERROR: `yli::load::load_png_file`: file " << filename << " is not a PNG file!\n";
            png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
            fclose(fp);
            return nullptr;
        }

        png_set_sig_bytes(png_ptr, header_size_in_bytes);

        // Read the PNG file using high-level interface.
        int png_transforms = PNG_TRANSFORM_IDENTITY;

        if (image_loader_struct.should_convert_grayscale_to_rgb)
        {
            png_transforms |= PNG_TRANSFORM_GRAY_TO_RGB;
        }

        if (image_loader_struct.should_discard_alpha_channel)
        {
            png_transforms |= PNG_TRANSFORM_STRIP_ALPHA;
        }

        png_read_png(png_ptr, info_ptr, png_transforms, nullptr);

        image_width = png_get_image_width(png_ptr, info_ptr);
        std::cout << "Image width is " << image_width << " pixels.\n";
        image_height = png_get_image_height(png_ptr, info_ptr);
        std::cout << "Image width is " << image_width << " pixels.\n";
        image_size = image_width * image_height;

        const std::size_t line_width_in_bytes = png_get_rowbytes(png_ptr, info_ptr);

        png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);

        std::shared_ptr<std::vector<uint8_t>> image_data = std::make_shared<std::vector<uint8_t>>();
        image_data->resize(image_height * line_width_in_bytes);
        n_color_channels = (image_data->size() / image_size);
        uint8_t* image_data_pointer = &(*image_data)[0];

        for (uint32_t row_i = 0; row_i < image_height; row_i++)
        {
            uint8_t* row_pointer = row_pointers[row_i];

            if (row_pointer == nullptr)
            {
                std::cerr << filename << "ERROR: `yli::load::load_png_file`: row pointer is `nullptr`!\n";
                png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) nullptr);
                fclose(fp);
                return nullptr;
            }
                
            std::copy(row_pointer, row_pointer + line_width_in_bytes, image_data_pointer);
            image_data_pointer += line_width_in_bytes;
        }

        if (image_loader_struct.should_flip_vertically)
        {
            yli::memory::flip_vertically(&(*image_data)[0], line_width_in_bytes, image_height);
        }

        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);

        fclose(fp);
        return image_data;
    }
}
