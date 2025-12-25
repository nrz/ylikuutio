// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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

#ifndef YLIKUUTIO_MEMORY_MEMORY_TEMPLATES_HPP_INCLUDED
#define YLIKUUTIO_MEMORY_MEMORY_TEMPLATES_HPP_INCLUDED

// Include standard headers
#include <algorithm> // std::copy
#include <array>     // std::array
#include <cstddef>   // std::size_t
#include <iostream>  // std::cerr
#include <iterator>  // std::back_inserter
#include <limits>    // std::numeric_limits
#include <stdint.h>  // uint32_t etc.
#include <vector>    // std::vector

namespace yli::memory
{
    template<typename T1, typename T2>
        T2 read_nonaligned_32_bit(T1* src_data, const std::size_t offset)
        {
            uint8_t* src_data_uint8_t = (uint8_t*) src_data;
            T2 value_32_bit = static_cast<T2>(src_data_uint8_t[offset + 3]);
            value_32_bit = value_32_bit << 8 | static_cast<T2>(src_data_uint8_t[offset + 2]);
            value_32_bit = value_32_bit << 8 | static_cast<T2>(src_data_uint8_t[offset + 1]);
            value_32_bit = value_32_bit << 8 | static_cast<T2>(src_data_uint8_t[offset]);
            return value_32_bit;
        }

    template<typename T1>
        void flip_vertically(T1* src_data, const std::size_t image_width, const std::size_t image_height)
        {
            for (std::size_t y = 0; y < image_height / 2; y++)
            {
                for (std::size_t x = 0; x < image_width; x++)
                {
                    std::size_t upper_index = image_width * y + x;
                    std::size_t lower_index = image_width * (image_height - y - 1) + x;
                    T1 temp = src_data[upper_index];
                    src_data[upper_index] = src_data[lower_index];
                    src_data[lower_index] = temp;
                }
            }
        }

    template<typename T1, std::size_t DataSize>
        std::vector<T1> copy_circular_buffer_into_vector(const std::array<T1, DataSize>& buffer, const std::size_t start_i, const std::size_t buffer_size)
        {
            if (buffer_size > buffer.size())
            {
                std::cerr << "ERROR: `yli::memory::copy_circular_buffer_into_vector`: `buffer_size > buffer.size()`\n";
                return {};
            }

            if (buffer_size == 0)
            {
                return {};
            }

            std::vector<T1> dest;
            dest.reserve(buffer_size);

            std::size_t n_values_to_copy_first_part { buffer_size <= DataSize - start_i ? buffer_size : DataSize - start_i };
            std::copy(&buffer.at(start_i), buffer.end(), std::back_inserter(dest));

            if (n_values_to_copy_first_part < buffer_size)
            {
                // Copy the remaining values.
                std::copy(buffer.begin(), &buffer.at(buffer_size - n_values_to_copy_first_part), std::back_inserter(dest));
            }

            return dest;
        }

    template<typename T1, std::size_t DataSize>
        void copy_circular_buffer_into_begin(std::array<T1, DataSize>& buffer, const std::size_t start_i, const std::size_t buffer_size)
        {
            if (buffer_size > buffer.size())
            {
                std::cerr << "ERROR: `yli::memory::copy_circular_buffer_into_begin`: `buffer_size > buffer.size()`\n";
                return;
            }

            if (start_i == 0 || buffer_size == 0 || DataSize == 0) [[unlikely]]
            {
                return;
            }

            std::size_t temp_dest_i = (start_i > 0 ? start_i - 1 : buffer_size - 1);
            T1 temp = buffer[temp_dest_i]; // One value needs to be kept in a temp.

            // Without additional memory allocations the copy is done backwards one element at a time.
            // Time complexity: O(n^2).
            // We need as many iterations as far as `start_i` is from array index 0.
            for (std::size_t iteration_i = 0, iteration_start_i = start_i; iteration_i < start_i; iteration_i++, iteration_start_i--)
            {
                if (const std::size_t max_value = std::numeric_limits<std::size_t>::max(); iteration_start_i == max_value) [[unlikely]]
                {
                    // Overflow. Adjust appropriately.
                    iteration_start_i = buffer_size - 1;
                }

                for (
                        std::size_t src_i = iteration_start_i, dest_i = (src_i > 0 ? src_i - 1 : buffer_size - 1), counter = 0;
                        counter < buffer_size;
                        counter++, src_i++, dest_i++)
                {
                    if (src_i == buffer_size) [[unlikely]]
                    {
                        // Past end of buffer. Adjust appropriately.
                        src_i = 0;
                    }

                    if (dest_i == buffer_size) [[unlikely]]
                    {
                        // Past end of buffer. Adjust appropriately.
                        dest_i = 0;
                    }

                    buffer[dest_i] = buffer[src_i];
                }
            }

            buffer[buffer_size - 1] = temp;
        }
}

#endif
