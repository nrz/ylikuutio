// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2026 Antti Nuortimo.
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

#ifndef YLIKUUTIO_ONTOLOGY_WAYPOINT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_WAYPOINT_HPP_INCLUDED

#include "child_module.hpp"
#include "movable.hpp"

// Include standard headers
#include <cstddef> // std::size_t

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class GenericParentModule;
    class GenericMasterModule;
    class Entity;
    class Universe;
    class Scene;
    struct WaypointStruct;

    class Waypoint final : public Movable
    {
        public:
            Waypoint(
                    yli::core::Application& application,
                    Universe& universe,
                    const WaypointStruct& waypoint_struct,
                    GenericParentModule* const parent_module,
                    GenericMasterModule* const brain_master_module);

            Waypoint(const Waypoint&) = delete;            // Delete copy constructor.
            Waypoint &operator=(const Waypoint&) = delete; // Delete copy assignment.

            virtual ~Waypoint() = default;

            Entity* get_parent() const override;
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            Scene* get_scene() const override;

            ChildModule child_of_scene;
    };
}

#endif
