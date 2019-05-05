#ifndef __MATRIX_HPP_INCLUDED
#define __MATRIX_HPP_INCLUDED

// Include standard headers
#include <cstddef>  // std::size_t
#include <memory>   // std::make_shared, std::shared_ptr
#include <vector>   // std::vector

namespace yli
{
    namespace linear_algebra
    {
        class Tensor3;

        class Matrix
        {
            public:
                // constructor.
                Matrix(std::size_t height, std::size_t width);

                // copy constructor.
                Matrix(const yli::linear_algebra::Matrix& old_matrix);
                Matrix(std::shared_ptr<yli::linear_algebra::Matrix> old_matrix)
                    : Matrix(*old_matrix) { }

                // Inspired by http://stackoverflow.com/questions/6969881/operator-overload/6969904#6969904
                class Proxy
                {
                    public:
                        Proxy(std::vector<float>& proxy_array) : proxy_array(proxy_array) { }

                        float& operator[](const std::size_t index)
                        {
                            return this->proxy_array[index];
                        }

                    private:
                        std::vector<float>& proxy_array;
                };

                void operator<<(const float rhs);
                void operator<<(const std::vector<float>& rhs);
                bool operator==(const yli::linear_algebra::Matrix& rhs) const;
                bool operator!=(const yli::linear_algebra::Matrix& rhs) const;
                yli::linear_algebra::Matrix& operator++();
                yli::linear_algebra::Matrix operator++(const int);
                yli::linear_algebra::Matrix& operator--();
                yli::linear_algebra::Matrix operator--(const int);
                yli::linear_algebra::Matrix& operator+=(const float rhs);
                yli::linear_algebra::Matrix& operator-=(const float rhs);
                yli::linear_algebra::Matrix& operator*=(const float rhs);
                yli::linear_algebra::Matrix& operator/=(const float rhs);
                yli::linear_algebra::Matrix& operator+=(yli::linear_algebra::Matrix& rhs);
                yli::linear_algebra::Matrix& operator-=(yli::linear_algebra::Matrix& rhs);
                Proxy operator[](const std::size_t index)
                {
                    return Proxy(array_of_arrays[index]);
                }

                bool get_is_square() const;
                std::size_t get_width() const;
                std::size_t get_height() const;

                std::shared_ptr<yli::linear_algebra::Matrix> transpose();
                float det();

                friend class yli::linear_algebra::Tensor3;
                friend yli::linear_algebra::Matrix operator+(yli::linear_algebra::Matrix& lhs, yli::linear_algebra::Matrix& rhs);
                friend yli::linear_algebra::Matrix operator-(yli::linear_algebra::Matrix& lhs, yli::linear_algebra::Matrix& rhs);
                friend yli::linear_algebra::Matrix operator*(yli::linear_algebra::Matrix& lhs, yli::linear_algebra::Matrix& rhs);
                friend std::shared_ptr<yli::linear_algebra::Matrix> cat(std::size_t dimension, yli::linear_algebra::Matrix& old_matrix1, yli::linear_algebra::Matrix& old_matrix2);

                bool is_square;
                std::size_t width;
                std::size_t height;

            private:
                bool is_fully_populated;
                std::size_t next_y_to_populate;
                std::size_t next_x_to_populate;

                std::vector<std::vector<float>> array_of_arrays;
        };

        yli::linear_algebra::Matrix operator+(yli::linear_algebra::Matrix& lhs, yli::linear_algebra::Matrix& rhs);
        yli::linear_algebra::Matrix operator-(yli::linear_algebra::Matrix& lhs, yli::linear_algebra::Matrix& rhs);
        yli::linear_algebra::Matrix operator*(yli::linear_algebra::Matrix& lhs, yli::linear_algebra::Matrix& rhs);
    }
}

#endif
