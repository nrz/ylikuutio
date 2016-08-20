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
        this->next_row_i_to_populate = 0;
        this->next_column_i_to_populate = 0;
        this->is_fully_populated = false;

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

    void Matrix::operator<<(float rhs)
    {
        if (!this->is_square)
        {
            // TODO: Add support for non-square matrices!
            return;
        }

        while (!this->is_fully_populated)
        {
            switch (this->square_size)
            {
                case 1:
                    this->array_1x1[0][0] = rhs;
                    this->is_fully_populated = true;
                    return;
                case 2:
                    this->array_2x2[this->next_row_i_to_populate][this->next_column_i_to_populate++] = rhs;

                    if (this->next_column_i_to_populate >= this->width)
                    {
                        this->next_column_i_to_populate = 0;

                        if (++this->next_row_i_to_populate >= this->height)
                        {
                            this->is_fully_populated = true;
                            return;
                        }
                    }
                    break;
                case 3:
                    this->array_3x3[this->next_row_i_to_populate][this->next_column_i_to_populate++] = rhs;

                    if (this->next_column_i_to_populate >= this->width)
                    {
                        this->next_column_i_to_populate = 0;

                        if (++this->next_row_i_to_populate >= this->height)
                        {
                            this->is_fully_populated = true;
                            return;
                        }
                    }
                    break;
                case 4:
                    this->array_4x4[this->next_row_i_to_populate][this->next_column_i_to_populate++] = rhs;

                    if (this->next_column_i_to_populate >= this->width)
                    {
                        this->next_column_i_to_populate = 0;

                        if (++this->next_row_i_to_populate >= this->height)
                        {
                            this->is_fully_populated = true;
                            return;
                        }
                    }
                    break;
                default:
                    return;
            }
        }
    }

    bool Matrix::operator==(const Matrix& rhs)
    {
        // compare if matrices are equal.
        if (this->width != rhs.width ||
                this->height != rhs.height)
        {
            // Matrices are not equal, if they have different sizes.
            return false;
        }

        if (!this->is_square || !rhs.is_square)
        {
            // TODO: implement non-square matrices, if needed.
            return false;
        }

        if (this->square_size != rhs.square_size)
        {
            // If square sizes are different, square matrices are different.
            return false;
        }

        switch (this->square_size)
        {
            case 1:
                // Scalar (1x1 matrix).
                return (this->array_1x1[0][0] == rhs.array_1x1[0][0]);
            case 2:
                // 2x2 matrix.
                for (uint32_t y = 0; y < this->height; y++)
                {
                    for (uint32_t x = 0; y < this->height; y++)
                    {
                        if (this->array_2x2[y][x] != rhs.array_2x2[y][x])
                        {
                            return false;
                        }
                    }
                }
                return true;
            case 3:
                // 3x3 matrix.
                for (uint32_t y = 0; y < this->height; y++)
                {
                    for (uint32_t x = 0; y < this->height; y++)
                    {
                        if (this->array_3x3[y][x] != rhs.array_3x3[y][x])
                        {
                            return false;
                        }
                    }
                }
                return true;
            case 4:
                // 4x4 matrix.
                for (uint32_t y = 0; y < this->height; y++)
                {
                    for (uint32_t x = 0; y < this->height; y++)
                    {
                        if (this->array_4x4[y][x] != rhs.array_4x4[y][x])
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
