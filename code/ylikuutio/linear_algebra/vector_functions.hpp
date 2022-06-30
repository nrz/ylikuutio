// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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

#ifndef __YLIKUUTIO_LINEAR_ALGEBRA_VECTOR_FUNCTIONS_HPP_INCLUDED
#define __YLIKUUTIO_LINEAR_ALGEBRA_VECTOR_FUNCTIONS_HPP_INCLUDED

// Include standard headers
#include <vector> // std::vector

namespace yli::linear_algebra
{
    template<typename T1>
        std::vector<T1> insert_elements(
                const std::vector<T1>& data_vector,
                const std::vector<T1>& left_filler_vector,
                const std::vector<T1>& right_filler_vector)
        {
            std::vector<T1> output_vector;

            for (const T1& data : data_vector)
            {
                for (const T1& left_value : left_filler_vector)
                {
                    output_vector.emplace_back(left_value);
                }

                output_vector.emplace_back(data);

                for (const T1& right_value : right_filler_vector)
                {
                    output_vector.emplace_back(right_value);
                }
            }

            return output_vector;
        }
}

#endif
