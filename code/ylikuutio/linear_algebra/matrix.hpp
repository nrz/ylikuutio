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

            friend bool operator==(const Matrix& lhs, const Matrix& rhs);

        private:
            bool is_square;
            uint32_t square_size;
            uint32_t width;
            uint32_t height;

            float array_1x1[1][1];
            float array_2x2[2][2];
            float array_3x3[3][3];
            float array_4x4[4][4];
    };

    bool operator==(const Matrix& lhs, const Matrix& rhs);
}

#endif
