#include "matrix.hpp"

// Include standard headers
#include <stdint.h> // uint32_t etc.

namespace linear_algebra
{
    Matrix::Matrix(uint32_t width, uint32_t height)
    {
        // constructor.
        this->width = width;
        this->height = height;

        if (this->width == this->height)
        {
            this->is_square = true;
            this->square_size = this->width;
        }
        else
        {
            this->is_square = false;
            this->square_size = 0;
        }
    }

    Matrix::~Matrix()
    {
    }

    bool operator==(const Matrix& lhs, const Matrix& rhs)
    {
        // compare if matrices are equal.
        if (lhs.width != rhs.width ||
                lhs.height != rhs.height)
        {
            // Matrices are not equal, if they have different sizes.
            return false;
        }

        if (!lhs.is_square || !rhs.is_square)
        {
            // TODO: implement non-square matrices, if needed.
            return false;
        }

        if (lhs.square_size != rhs.square_size)
        {
            // If square sizes are different, square matrices are different.
            return false;
        }

        switch (lhs.square_size)
        {
            case 1:
                // Scalar (1x1 matrix).
                return (lhs.array_1x1[0][0] == rhs.array_1x1[0][0]);
            case 2:
                // 2x2 matrix.
                for (uint32_t y = 0; y < lhs.height; y++)
                {
                    for (uint32_t x = 0; y < lhs.height; y++)
                    {
                        if (lhs.array_2x2[y][x] != rhs.array_2x2[y][x])
                        {
                            return false;
                        }
                    }
                }
                return true;
            case 3:
                // 3x3 matrix.
                for (uint32_t y = 0; y < lhs.height; y++)
                {
                    for (uint32_t x = 0; y < lhs.height; y++)
                    {
                        if (lhs.array_3x3[y][x] != rhs.array_3x3[y][x])
                        {
                            return false;
                        }
                    }
                }
                return true;
            case 4:
                // 4x4 matrix.
                for (uint32_t y = 0; y < lhs.height; y++)
                {
                    for (uint32_t x = 0; y < lhs.height; y++)
                    {
                        if (lhs.array_4x4[y][x] != rhs.array_4x4[y][x])
                        {
                            return false;
                        }
                    }
                }
                return true;
            default:
                return false;
        }
    }
}
