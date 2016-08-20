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
}
