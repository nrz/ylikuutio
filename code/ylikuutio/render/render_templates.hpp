// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
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

#ifndef __YLIKUUTIO_RENDER_RENDER_TEMPLATES_HPP_INCLUDED
#define __YLIKUUTIO_RENDER_RENDER_TEMPLATES_HPP_INCLUDED

#include "code/ylikuutio/ontology/apprentice_module.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <type_traits> // std::decay
#include <vector>  // std::vector

namespace yli::render
{
    template<typename T>
        using SomeIterator = typename std::decay<T>::type::iterator;

    template<typename ContainerType, typename StoredType, typename CastType>
        void render_children(ContainerType& child_container)
        {
            for (SomeIterator<ContainerType&> it = child_container.begin(); it != child_container.end(); it++)
            {
                CastType child_pointer = static_cast<CastType>(*it);

                if (child_pointer != nullptr && child_pointer->should_be_rendered)
                {
                    child_pointer->render();
                }
            }
        }

    template<typename T1>
        void render_apprentices(const std::vector<yli::ontology::ApprenticeModule*>& apprentice_pointer_vector)
        {
            for (std::size_t apprentice_i = 0; apprentice_i < apprentice_pointer_vector.size(); apprentice_i++)
            {
                yli::ontology::ApprenticeModule* const apprentice_module = apprentice_pointer_vector[apprentice_i];

                if (apprentice_module != nullptr)
                {
                    T1 apprentice_pointer = static_cast<T1>(apprentice_module->get_apprentice());

                    if (apprentice_pointer != nullptr && apprentice_pointer->should_be_rendered)
                    {
                        apprentice_pointer->render();
                    }
                }
            }
        }
}

#endif
