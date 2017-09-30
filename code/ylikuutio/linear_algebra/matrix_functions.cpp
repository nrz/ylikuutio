#include "matrix_functions.hpp"
#include "matrix.hpp"

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <stdint.h> // uint32_t etc.

namespace linear_algebra
{
    std::shared_ptr<linear_algebra::Matrix> cat(uint32_t dimension, linear_algebra::Matrix& old_matrix1, linear_algebra::Matrix& old_matrix2)
    {
        // Matrices can be concatenated either vertically (`dimension` = 1)
        // or horizontally (`dimension` = 2).
        if (dimension == 1)
        {
            // Concatenate vertically.
            if (old_matrix1.width != old_matrix2.width)
            {
                // Matrix widths do not match, return 1x1 NAN matrix.
                std::shared_ptr<linear_algebra::Matrix> tmp = std::make_shared<linear_algebra::Matrix>(1, 1);
                *tmp << NAN;
                return tmp;
            }

            uint32_t new_height = old_matrix1.height + old_matrix2.height;
            uint32_t new_width = old_matrix1.width;

            std::shared_ptr<linear_algebra::Matrix> new_matrix = std::make_shared<linear_algebra::Matrix>(new_height, new_width);

            // Populate the newly created matrix with old values.

            for (uint32_t y = 0; y < old_matrix1.height; y++)
            {
                for (uint32_t x = 0; x < new_width; x++)
                {
                    *new_matrix << old_matrix1[y][x];
                }
            }

            for (uint32_t y = 0; y < old_matrix2.height; y++)
            {
                for (uint32_t x = 0; x < new_width; x++)
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
                std::shared_ptr<linear_algebra::Matrix> tmp = std::make_shared<linear_algebra::Matrix>(1, 1);
                *tmp << NAN;
                return tmp;
            }

            uint32_t new_height = old_matrix1.height;
            uint32_t new_width = old_matrix1.width + old_matrix2.width;

            std::shared_ptr<linear_algebra::Matrix> new_matrix = std::make_shared<linear_algebra::Matrix>(new_height, new_width);

            // Populate the newly created matrix with old values.
            for (uint32_t y = 0; y < new_height; y++)
            {
                for (uint32_t x = 0; x < old_matrix1.width; x++)
                {
                    *new_matrix << old_matrix1[y][x];
                }

                for (uint32_t x = 0; x < old_matrix2.width; x++)
                {
                    *new_matrix << old_matrix2[y][x];
                }
            }

            return new_matrix;
        }

        // Invalid dimension, return 1x1 NAN matrix.
        std::shared_ptr<linear_algebra::Matrix> tmp = std::make_shared<linear_algebra::Matrix>(1, 1);
        *tmp << NAN;
        return tmp;
    }
}
