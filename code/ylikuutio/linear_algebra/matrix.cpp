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
        this->array = new float[this->array_size];
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
        delete this->array;
    }

    void Matrix::operator<<(float rhs)
    {
        if (this->is_fully_populated)
        {
            return;
        }

        this->array[this->next_i_to_populate++] = rhs;

        if (this->next_i_to_populate >= this->array_size)
        {
            this->is_fully_populated = true;
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

        for (uint32_t i = 0; i < this->array_size; i++)
        {
            if (this->array[i] != rhs.array[i])
            {
                return false;
            }
        }
    }
}
