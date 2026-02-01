// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2026 Antti Nuortimo.
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

#include "tensor3.hpp"
#include "matrix.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <vector>   // std::vector

namespace yli::linear_algebra
{
    // `class Tensor3` uses the same coordinate order as MATLAB,
    // to make testing easier. So: y, x, z.
    // y = 0 is the uppermost slice
    // x = 0 is the leftmost slice.
    // z = 0 is the front slice.

    Tensor3::Tensor3(std::size_t width, std::size_t height, std::size_t depth)
    {
        this->width = width;
        this->height = height;
        this->depth = depth;
        this->array_of_arrays_of_arrays.resize(this->width);

        for (std::size_t x = 0; x < this->width; x++)
        {
            this->array_of_arrays_of_arrays[x].resize(this->height);

            for (std::size_t y = 0; y < this->height; y++)
            {
                this->array_of_arrays_of_arrays[x][y].resize(this->depth);
            }
        }

        this->next_x_to_populate = 0;
        this->next_y_to_populate = 0;
        this->next_z_to_populate = 0;
        this->is_fully_populated = false;

        if (this->width == this->height && this->height == this->depth)
        {
            this->is_cube = true;
        }
        else
        {
            this->is_cube = false;
        }
    }

    Tensor3::Tensor3(const yli::linear_algebra::Matrix& old_matrix)
    {
        this->width = old_matrix.width;
        this->height = old_matrix.height;
        this->depth = 1;
        this->array_of_arrays_of_arrays.resize(this->width);

        for (std::size_t x = 0; x < this->width; x++)
        {
            this->array_of_arrays_of_arrays[x].resize(this->height);

            for (std::size_t y = 0; y < this->height; y++)
            {
                this->array_of_arrays_of_arrays[x][y].resize(this->depth);
            }
        }

        this->next_x_to_populate = 0;
        this->next_y_to_populate = 0;
        this->next_z_to_populate = 0;
        this->is_fully_populated = false;

        this->is_cube = false;
    }

    void Tensor3::operator<<(const float rhs)
    {
        if (this->is_fully_populated)
        {
            // Array is already fully populated. Nothing to do.
            return;
        }

        // First, get the slice.
        std::vector<std::vector<float>>& my_array_of_arrays = this->array_of_arrays_of_arrays[this->next_x_to_populate];
        std::vector<float>& my_array = my_array_of_arrays[this->next_y_to_populate];

        // Then store the value.
        my_array[this->next_z_to_populate] = rhs;

        if (++this->next_x_to_populate >= this->width)
        {
            this->next_x_to_populate = 0;

            if (++this->next_y_to_populate >= this->height)
            {
                this->next_y_to_populate = 0;

                if (++this->next_z_to_populate >= this->depth)
                {
                    this->is_fully_populated = true;
                }
            }
        }
    }

    void Tensor3::operator<<(const std::vector<float>& rhs)
    {
        std::size_t rhs_i = 0;

        while (!this->is_fully_populated && rhs_i < rhs.size())
        {
            // First, get the slice.
            std::vector<std::vector<float>>& my_array_of_arrays = this->array_of_arrays_of_arrays[this->next_x_to_populate];
            std::vector<float>& my_array = my_array_of_arrays[this->next_y_to_populate];

            // Then store the value.
            my_array[this->next_z_to_populate] = rhs[rhs_i++];

            if (++this->next_x_to_populate >= this->width)
            {
                this->next_x_to_populate = 0;

                if (++this->next_y_to_populate >= this->height)
                {
                    this->next_y_to_populate = 0;

                    if (++this->next_z_to_populate >= this->depth)
                    {
                        this->is_fully_populated = true;
                    }
                }
            }
        }
    }

    bool Tensor3::operator==(const yli::linear_algebra::Tensor3& rhs) const noexcept
    {
        // compare if tensors are equal.
        if (this->width != rhs.width ||
                this->height != rhs.height ||
                this->depth != rhs.depth)
        {
            // Tensors are not equal, if they have different sizes.
            return false;
        }

        for (std::size_t x = 0; x < this->width; x++)
        {
            // Get the slices of both arrays.
            const std::vector<std::vector<float>>& my_array_of_arrays = this->array_of_arrays_of_arrays[x];
            const std::vector<std::vector<float>>& other_array_of_arrays = rhs.array_of_arrays_of_arrays[x];

            for (std::size_t y = 0; y < this->height; y++)
            {
                const std::vector<float>& my_array = my_array_of_arrays[y];
                const std::vector<float>& other_array = other_array_of_arrays[y];

                for (std::size_t z = 0; z < this->depth; z++)
                {
                    if (my_array[z] != other_array[z])
                    {
                        // Arrays are not identical.
                        return false;
                    }
                }
            }
        }

        // Everything matches. Arrays are identical.
        return true;
    }
}
