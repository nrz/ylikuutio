// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef YLIKUUTIO_LINEAR_ALGEBRA_MATRIX_HPP_INCLUDED
#define YLIKUUTIO_LINEAR_ALGEBRA_MATRIX_HPP_INCLUDED

// Include standard headers
#include <cstddef>  // std::size_t
#include <vector>   // std::vector

namespace yli::linear_algebra
{
    class Tensor3;

    class Matrix final
    {
        public:
            Matrix(std::size_t height, std::size_t width);

            ~Matrix() = default;

            // copy constructor.
            Matrix(const yli::linear_algebra::Matrix& old_matrix) = default;

            // Inspired by http://stackoverflow.com/questions/6969881/operator-overload/6969904#6969904
            class Proxy
            {
                public:
                    explicit Proxy(std::vector<float>& proxy_array)
                        : proxy_array(proxy_array)
                    {
                    }

                    float& operator[](const std::size_t index)
                    {
                        return this->proxy_array[index];
                    }

                private:
                    std::vector<float>& proxy_array;
            };

            void operator<<(const float rhs);
            void operator<<(const std::vector<float>& rhs);
            bool operator==(const yli::linear_algebra::Matrix& rhs) const noexcept;
            bool operator!=(const yli::linear_algebra::Matrix& rhs) const = default;
            yli::linear_algebra::Matrix& operator=(const yli::linear_algebra::Matrix& rhs) = default;
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
            float get_value(const std::size_t y, const std::size_t x) const;

            yli::linear_algebra::Matrix transpose();
            float det();

            friend class yli::linear_algebra::Tensor3;
            friend yli::linear_algebra::Matrix operator+(yli::linear_algebra::Matrix& lhs, yli::linear_algebra::Matrix& rhs);
            friend yli::linear_algebra::Matrix operator-(yli::linear_algebra::Matrix& lhs, yli::linear_algebra::Matrix& rhs);
            friend yli::linear_algebra::Matrix operator*(yli::linear_algebra::Matrix& lhs, yli::linear_algebra::Matrix& rhs);
            friend yli::linear_algebra::Matrix cat(std::size_t dimension, yli::linear_algebra::Matrix& old_matrix1, yli::linear_algebra::Matrix& old_matrix2);

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

#endif
