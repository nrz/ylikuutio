#ifndef __MATRIX_HPP_INCLUDED
#define __MATRIX_HPP_INCLUDED

// Include standard headers
#include <stdint.h> // uint32_t etc.

namespace linear_algebra
{
    class Matrix
    {
        public:
            // constructor.
            Matrix(uint32_t width, uint32_t height);

            // destructor.
            ~Matrix();

        private:
            bool is_square;
            uint32_t square_size;
            uint32_t width;
            uint32_t height;

    };
}

#endif
