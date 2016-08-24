#ifndef __MATRIX_HPP_INCLUDED
#define __MATRIX_HPP_INCLUDED

// Include standard headers
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace linear_algebra
{
    class Matrix
    {
        public:
            // constructor.
            Matrix(uint32_t height, uint32_t width);

            // copy constructor.
            Matrix(const Matrix& old_matrix);

            // destructor.
            ~Matrix();

            // Inspired by http://stackoverflow.com/questions/6969881/operator-overload/6969904#6969904
            class Proxy
            {
                public:
                    Proxy(float* proxy_array) : proxy_array(proxy_array) { }

                    float& operator[](const uint32_t index)
                    {
                        return proxy_array[index];
                    }

                private:
                    float* proxy_array;
            };

            void operator<<(const float rhs);
            void operator<<(const std::vector<float>& rhs);
            bool operator==(const Matrix& rhs);
            Matrix& operator++();
            Matrix operator++(const int);
            Matrix& operator--();
            Matrix operator--(const int);
            Matrix& operator+=(const float rhs);
            Matrix& operator-=(const float rhs);
            Matrix& operator*=(const float rhs);
            Matrix& operator/=(const float rhs);
            Matrix& operator+=(const Matrix& rhs);
            Matrix& operator-=(const Matrix& rhs);
            Proxy operator[](const uint32_t index)
            {
                return Proxy(array_of_arrays[index]);
            }

            float det();

            friend Matrix linear_algebra::operator+(Matrix& lhs, Matrix& rhs);
            friend Matrix linear_algebra::operator-(Matrix& lhs, Matrix& rhs);
            friend Matrix linear_algebra::operator*(Matrix& lhs, Matrix& rhs);

        private:
            bool is_square;
            uint32_t width;
            uint32_t height;

            bool is_fully_populated;
            int32_t next_y_to_populate;
            int32_t next_x_to_populate;

            float** array_of_arrays;
    };

    Matrix operator+(const Matrix& lhs, const Matrix& rhs);
    Matrix operator-(const Matrix& lhs, const Matrix& rhs);
    Matrix operator*(const Matrix& lhs, const Matrix& rhs);
}

#endif
