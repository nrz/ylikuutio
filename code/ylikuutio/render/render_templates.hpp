// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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

#ifndef YLIKUUTIO_RENDER_RENDER_TEMPLATES_HPP_INCLUDED
#define YLIKUUTIO_RENDER_RENDER_TEMPLATES_HPP_INCLUDED

#include "code/ylikuutio/ontology/apprentice_module.hpp"

// Include standard headers
#include <type_traits> // std::decay

namespace yli::ontology
{
    class Scene;
}

namespace yli::render
{
    template<typename T>
        using SomeIterator = typename std::decay<T>::type::iterator;

    template<typename ContainerType, typename CastType>
        void render_children(ContainerType& child_container)
        {
            for (SomeIterator<ContainerType&> it = child_container.begin(); it != child_container.end(); ++it)
            {
                CastType child_pointer = static_cast<CastType>(*it);

                if (child_pointer != nullptr && child_pointer->should_render)
                {
                    child_pointer->render();
                }
            }
        }

    template<typename ContainerType, typename CastType>
        void render_children_of_given_scene_or_of_all_scenes(
                ContainerType& child_container,
                const yli::ontology::Scene* const scene)
        {
            for (SomeIterator<ContainerType&> it = child_container.begin(); it != child_container.end(); ++it)
            {
                CastType child_pointer = static_cast<CastType>(*it);

                if (child_pointer != nullptr && child_pointer->should_render)
                {
                    yli::ontology::Scene* const scene_of_child = child_pointer->get_scene();

                    if (scene_of_child == scene || scene == nullptr)
                    {
                        // Set `Scene` of the child as the chosen `Scene`.
                        child_pointer->render(scene_of_child);
                    }
                    else if (scene_of_child == nullptr)
                    {
                        // Keep the chosen `Scene` as a requirement.
                        child_pointer->render(scene);
                    }
                }
            }
        }

    template<typename ContainerType, typename CastType>
        void render_apprentices(ContainerType& apprentice_container, const yli::ontology::Scene* const scene)
        {
            // Render apprentices of the given `Scene` (`scene`) or of all `Scene`s.
            for (SomeIterator<ContainerType&> it = apprentice_container.begin(); it != apprentice_container.end(); ++it)
            {
                if (*it != nullptr)
                {
                    CastType apprentice_pointer = static_cast<CastType>(*it);

                    if (apprentice_pointer != nullptr && apprentice_pointer->should_render)
                    {
                        yli::ontology::Scene* const scene_of_apprentice = apprentice_pointer->get_scene();

                        if (scene_of_apprentice == scene || scene == nullptr)
                        {
                            // Set `Scene` of the apprentice as the chosen `Scene`.
                            apprentice_pointer->render(scene_of_apprentice);
                        }
                        else if (scene_of_apprentice == nullptr)
                        {
                            // Keep the chosen `Scene` as a requirement.
                            apprentice_pointer->render(scene);
                        }
                    }
                }
            }
        }
}

#endif
