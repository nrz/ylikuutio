#include "matrix.hpp"

// Include standard headers
#include <cmath>    // NAN, std::isnan, std::pow
#include <stdint.h> // uint32_t etc.

namespace linear_algebra
{
    Matrix::Matrix(uint32_t height, uint32_t width)
    {
        // constructor.
        this->width = width;
        this->height = height;
        this->array_size = this->width * this->height;
        this->array_of_arrays = new float*[this->height];

        for (uint32_t i = 0; i < this->height; i++)
        {
            this->array_of_arrays[i] = new float[this->width];
        }

        this->next_y_to_populate = 0;
        this->next_x_to_populate = 0;
        this->is_fully_populated = false;

        if (this->width == this->height)
        {
            this->is_square = true;
        }
        else
        {
            this->is_square = false;
        }
    }

    Matrix::Matrix(Matrix& old_matrix)
    {
        // copy constructor.
        this->width = old_matrix.width;
        this->height = old_matrix.height;
        this->array_size = this->width * this->height;
        this->array_of_arrays = new float*[this->height];

        for (uint32_t i = 0; i < this->height; i++)
        {
            this->array_of_arrays[i] = new float[this->width];
        }

        this->next_y_to_populate = old_matrix.next_y_to_populate;
        this->next_x_to_populate = old_matrix.next_x_to_populate;
        this->is_fully_populated = old_matrix.is_fully_populated;

        // Copy values from old matrix (deep copy).
        // Don't care whether `old_matrix` is fully populated or not.
        for (uint32_t y = 0; y < this->height; y++)
        {
            // Get the slices of both arrays.
            float* my_array = this->array_of_arrays[y];
            float* other_array = old_matrix.array_of_arrays[y];

            for (uint32_t x = 0; x < this->width; x++)
            {
                my_array[x] = other_array[x];
            }
        }

        if (this->width == this->height)
        {
            this->is_square = true;
        }
        else
        {
            this->is_square = false;
        }
    }

    Matrix::~Matrix()
    {
        // delete this->array_of_arrays;
    }

    float Matrix::det()
    {
        if (!this->is_square)
        {
            // Non-square matrices do not have determinant.
            return NAN;
        }

        switch (this->width)
        {
            case 1:
                // det(scalar) = scalar
                return this->array_of_arrays[0][0];
            case 2:
                //     | a b |
                // det |     | = ad - bc
                //     | c d |
                return this->array_of_arrays[0][0] * this->array_of_arrays[1][1] - this->array_of_arrays[0][1] * this->array_of_arrays[1][0];
            case 3:
                //     | a b c |
                // det | d e f | = aei + bfg + cdh - ceg - bdi - afh
                //     | g h i |
                return this->array_of_arrays[0][0] * this->array_of_arrays[1][1] * this->array_of_arrays[2][2] + // aei +
                    this->array_of_arrays[0][1] * this->array_of_arrays[1][2] * this->array_of_arrays[2][0] +    // bfg +
                    this->array_of_arrays[0][2] * this->array_of_arrays[1][0] * this->array_of_arrays[2][1] -    // cdh -
                    this->array_of_arrays[0][2] * this->array_of_arrays[1][1] * this->array_of_arrays[2][0] -    // ceg -
                    this->array_of_arrays[0][1] * this->array_of_arrays[1][0] * this->array_of_arrays[2][2] -    // bdi -
                    this->array_of_arrays[0][0] * this->array_of_arrays[1][2] * this->array_of_arrays[2][1];     // afh
            default:
                // TODO: implement determinant for larger matrices!
                return NAN;
        }
    }

    void Matrix::operator<<(const float rhs)
    {
        if (this->is_fully_populated)
        {
            // Array is already fully populated. Nothing to do.
            return;
        }

        // First, get the slice.
        float* my_array = this->array_of_arrays[this->next_y_to_populate];

        // Then store the value.
        my_array[this->next_x_to_populate++] = rhs;

        if (this->next_x_to_populate >= this->width)
        {
            this->next_x_to_populate = 0;

            if (++this->next_y_to_populate >= this->height)
            {
                this->is_fully_populated = true;
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

        for (uint32_t y = 0; y < this->height; y++)
        {
            // Get the slices of both arrays.
            float* my_array = this->array_of_arrays[y];
            float* other_array = rhs.array_of_arrays[y];

            for (uint32_t x = 0; x < this->width; x++)
            {
                if (my_array[x] != other_array[x])
                {
                    // Arrays are not identical.
                    return false;
                }
            }
        }
        // Everything matches. Arrays are identical.
        return true;
    }

    Matrix& Matrix::operator++()
    {
        for (uint32_t y = 0; y < this->height; y++)
        {
            // Get the slice.
            float* my_array = this->array_of_arrays[y];

            for (uint32_t x = 0; x < this->width; x++)
            {
                my_array[x]++;
            }
        }
        return *this;
    }

    Matrix Matrix::operator++(const int)
    {
        Matrix tmp(*this); // Make a copy.
        this->operator++();
        return tmp; // Return old matrix.
    }

    Matrix& Matrix::operator--()
    {
        for (uint32_t y = 0; y < this->height; y++)
        {
            // Get the slice.
            float* my_array = this->array_of_arrays[y];

            for (uint32_t x = 0; x < this->width; x++)
            {
                my_array[x]--;
            }
        }
        return *this;
    }

    Matrix Matrix::operator--(const int)
    {
        Matrix tmp(*this); // Make a copy.
        this->operator--();
        return tmp; // Return old matrix.
    }

    Matrix& Matrix::operator+=(const float rhs)
    {
        for (uint32_t y = 0; y < this->height; y++)
        {
            // Get the slice.
            float* my_array = this->array_of_arrays[y];

            for (uint32_t x = 0; x < this->width; x++)
            {
                my_array[x] += rhs;
            }
        }
        return *this;
    }

    Matrix& Matrix::operator-=(const float rhs)
    {
        for (uint32_t y = 0; y < this->height; y++)
        {
            // Get the slice.
            float* my_array = this->array_of_arrays[y];

            for (uint32_t x = 0; x < this->width; x++)
            {
                my_array[x] -= rhs;
            }
        }
        return *this;
    }

    Matrix& Matrix::operator*=(const float rhs)
    {
        for (uint32_t y = 0; y < this->height; y++)
        {
            // Get the slice.
            float* my_array = this->array_of_arrays[y];

            for (uint32_t x = 0; x < this->width; x++)
            {
                my_array[x] *= rhs;
            }
        }
        return *this;
    }

    Matrix& Matrix::operator/=(const float rhs)
    {
        for (uint32_t y = 0; y < this->height; y++)
        {
            // Get the slice.
            float* my_array = this->array_of_arrays[y];

            for (uint32_t x = 0; x < this->width; x++)
            {
                my_array[x] *= rhs;
            }
        }
        return *this;
    }

    Matrix& Matrix::operator+=(const Matrix& rhs)
    {
        for (uint32_t y = 0; y < this->height; y++)
        {
            // Get the slices of both arrays.
            float* my_array = this->array_of_arrays[y];
            float* other_array = rhs.array_of_arrays[y];

            for (uint32_t x = 0; x < this->width; x++)
            {
                my_array[x] += other_array[x];
            }
        }
        return *this;
    }

    Matrix& Matrix::operator-=(const Matrix& rhs)
    {
        for (uint32_t y = 0; y < this->height; y++)
        {
            // Get the slices of both arrays.
            float* my_array = this->array_of_arrays[y];
            float* other_array = rhs.array_of_arrays[y];

            for (uint32_t x = 0; x < this->width; x++)
            {
                my_array[x] -= other_array[x];
            }
        }
        return *this;
    }
}
