// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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

#ifndef YLIKUUTIO_ONTOLOGY_MISSION_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_MISSION_HPP_INCLUDED

#include "child_module.hpp"
#include "entity.hpp"

// Include standard headers
#include <cstddef> // std::size_t

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class GenericParentModule;
    class Universe;
    class Scene;
    struct MissionStruct;

    class Mission final : public Entity
    {
        private:
            Mission(
                    yli::core::Application& application,
                    Universe& universe,
                    const MissionStruct& mission_struct,
                    GenericParentModule* const universe_parent_module);

            virtual ~Mission() = default;

            Scene* get_scene() const override;

        public:
            Mission(const Mission&) = delete;            // Delete copy constructor.
            Mission &operator=(const Mission&) = delete; // Delete copy assignment.

            Entity* get_parent() const override;
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            ChildModule child_of_universe;
    };
}

#endif
