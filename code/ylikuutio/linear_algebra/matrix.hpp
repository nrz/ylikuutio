#ifndef __MATRIX_HPP_INCLUDED
#define __MATRIX_HPP_INCLUDED

// Include standard headers
#include <cstddef>  // std::size_t
#include <memory>   // std::make_shared, std::shared_ptr
#include <vector>   // std::vector

namespace linear_algebra
{
    class Tensor3;

    class Matrix
    {
        public:
            // constructor.
            Matrix(std::size_t height, std::size_t width);

            // copy constructor.
            Matrix(linear_algebra::Matrix& old_matrix);
            Matrix(std::shared_ptr<linear_algebra::Matrix> old_matrix)
                : Matrix(*old_matrix) { }

            // Inspired by http://stackoverflow.com/questions/6969881/operator-overload/6969904#6969904
            class Proxy
            {
                public:
                    Proxy(std::vector<float>& proxy_array) : proxy_array(proxy_array) { }

                    float& operator[](const std::size_t index)
                    {
                        return proxy_array.at(index);
                    }

                private:
                    std::vector<float>& proxy_array;
            };

            void operator<<(const float rhs);
            void operator<<(const std::vector<float>& rhs);
            bool operator==(linear_algebra::Matrix& rhs);
            bool operator!=(linear_algebra::Matrix& rhs);
            linear_algebra::Matrix& operator++();
            linear_algebra::Matrix operator++(const int);
            linear_algebra::Matrix& operator--();
            linear_algebra::Matrix operator--(const int);
            linear_algebra::Matrix& operator+=(const float rhs);
            linear_algebra::Matrix& operator-=(const float rhs);
            linear_algebra::Matrix& operator*=(const float rhs);
            linear_algebra::Matrix& operator/=(const float rhs);
            linear_algebra::Matrix& operator+=(linear_algebra::Matrix& rhs);
            linear_algebra::Matrix& operator-=(linear_algebra::Matrix& rhs);
            Proxy operator[](const std::size_t index)
            {
                return Proxy(array_of_arrays[index]);
            }

            std::shared_ptr<linear_algebra::Matrix> transpose();
            float det();

            friend class linear_algebra::Tensor3;
            friend linear_algebra::Matrix operator+(linear_algebra::Matrix& lhs, linear_algebra::Matrix& rhs);
            friend linear_algebra::Matrix operator-(linear_algebra::Matrix& lhs, linear_algebra::Matrix& rhs);
            friend linear_algebra::Matrix operator*(linear_algebra::Matrix& lhs, linear_algebra::Matrix& rhs);
            friend std::shared_ptr<linear_algebra::Matrix> cat(std::size_t dimension, linear_algebra::Matrix& old_matrix1, linear_algebra::Matrix& old_matrix2);

            bool is_square;
            std::size_t width;
            std::size_t height;

        private:
            bool is_fully_populated;
            std::size_t next_y_to_populate;
            std::size_t next_x_to_populate;

            std::vector<std::vector<float>> array_of_arrays;
    };

    linear_algebra::Matrix operator+(linear_algebra::Matrix& lhs, linear_algebra::Matrix& rhs);
    linear_algebra::Matrix operator-(linear_algebra::Matrix& lhs, linear_algebra::Matrix& rhs);
    linear_algebra::Matrix operator*(linear_algebra::Matrix& lhs, linear_algebra::Matrix& rhs);
}

#endif
