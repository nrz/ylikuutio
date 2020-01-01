// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
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

#ifndef __FAMILY_TEMPLATES_HPP_INCLUDED
#define __FAMILY_TEMPLATES_HPP_INCLUDED

// Include standard headers
#include <cstddef>  // std::size_t
#include <vector>   // std::vector

namespace yli
{
    namespace ontology
    {
        template<class T1>
            std::size_t get_number_of_descendants(const std::vector<T1>& child_pointer_vector)
            {
                std::size_t number_of_descendants = 0;

                for (std::size_t child_i = 0; child_i < child_pointer_vector.size(); child_i++)
                {
                    T1 child_pointer = static_cast<T1>(child_pointer_vector[child_i]);

                    if (child_pointer != nullptr)
                    {
                        number_of_descendants += child_pointer->get_number_of_descendants() + 1; // +1 for the child itself.
                    }
                }

                return number_of_descendants;
            }
    }
}

#endif
