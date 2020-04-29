// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
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

#include "matrix_functions.hpp"
#include "matrix.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <cmath>    // NAN, std::isnan, std::pow
#include <memory>   // std::make_shared, std::shared_ptr

namespace yli::linear_algebra
{
    std::shared_ptr<yli::linear_algebra::Matrix> cat(std::size_t dimension, yli::linear_algebra::Matrix& old_matrix1, yli::linear_algebra::Matrix& old_matrix2)
    {
        // Matrices can be concatenated either vertically (`dimension` = 1)
        // or horizontally (`dimension` = 2).
        if (dimension == 1)
        {
            // Concatenate vertically.
            if (old_matrix1.width != old_matrix2.width)
            {
                // Matrix widths do not match, return 1x1 NAN matrix.
                std::shared_ptr<yli::linear_algebra::Matrix> tmp = std::make_shared<yli::linear_algebra::Matrix>(1, 1);
                *tmp << NAN;
                return tmp;
            }

            std::size_t new_height = old_matrix1.height + old_matrix2.height;
            std::size_t new_width = old_matrix1.width;

            std::shared_ptr<yli::linear_algebra::Matrix> new_matrix = std::make_shared<yli::linear_algebra::Matrix>(new_height, new_width);

            // Populate the newly created matrix with old values.

            for (std::size_t y = 0; y < old_matrix1.height; y++)
            {
                for (std::size_t x = 0; x < new_width; x++)
                {
                    *new_matrix << old_matrix1[y][x];
                }
            }

            for (std::size_t y = 0; y < old_matrix2.height; y++)
            {
                for (std::size_t x = 0; x < new_width; x++)
                {
                    *new_matrix << old_matrix2[y][x];
                }
            }

            return new_matrix;
        }
        else if (dimension == 2)
        {
            // Concatenate horizontally.
            if (old_matrix1.height != old_matrix2.height)
            {
                // Matrix heights do not match, return 1x1 NAN matrix.
                std::shared_ptr<yli::linear_algebra::Matrix> tmp = std::make_shared<yli::linear_algebra::Matrix>(1, 1);
                *tmp << NAN;
                return tmp;
            }

            std::size_t new_height = old_matrix1.height;
            std::size_t new_width = old_matrix1.width + old_matrix2.width;

            std::shared_ptr<yli::linear_algebra::Matrix> new_matrix = std::make_shared<yli::linear_algebra::Matrix>(new_height, new_width);

            // Populate the newly created matrix with old values.
            for (std::size_t y = 0; y < new_height; y++)
            {
                for (std::size_t x = 0; x < old_matrix1.width; x++)
                {
                    *new_matrix << old_matrix1[y][x];
                }

                for (std::size_t x = 0; x < old_matrix2.width; x++)
                {
                    *new_matrix << old_matrix2[y][x];
                }
            }

            return new_matrix;
        }

        // Invalid dimension, return 1x1 NAN matrix.
        std::shared_ptr<yli::linear_algebra::Matrix> tmp = std::make_shared<yli::linear_algebra::Matrix>(1, 1);
        *tmp << NAN;
        return tmp;
    }
}
