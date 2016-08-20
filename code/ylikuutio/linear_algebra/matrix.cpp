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

    Matrix::~Matrix()
    {
        delete[] this->array_of_arrays;
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
}
