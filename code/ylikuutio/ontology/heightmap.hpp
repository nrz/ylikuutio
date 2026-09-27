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

#ifndef YLIKUUTIO_ONTOLOGY_HEIGHTMAP_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_HEIGHTMAP_HPP_INCLUDED

#include "object.hpp"

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class GenericParentModule;
    class GenericMasterModule;
    class Universe;
    struct ObjectStruct;

    class Heightmap final : public Object
    {
        public:
            Heightmap(
                    core::Application& application,
                    Universe& universe,
                    const ObjectStruct& terrain_struct,
                    GenericParentModule* scene_parent_module,
                    GenericMasterModule* species_master_module,
                    GenericMasterModule* /* movable_controller_master_module */);

            ~Heightmap() override = default;

            Heightmap(const Heightmap&) = delete;            // Delete copy constructor.
            Heightmap &operator=(const Heightmap&) = delete; // Delete copy assignment.
    };
}

#endif
