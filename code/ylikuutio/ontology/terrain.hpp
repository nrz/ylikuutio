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

#ifndef YLIKUUTIO_ONTOLOGY_TERRAIN_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_TERRAIN_HPP_INCLUDED

#include "code/ylikuutio/ontology/object.hpp"

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

    class Terrain final : public yli::ontology::Object
    {
        public:
            explicit Terrain(
                    yli::core::Application& application,
                    yli::ontology::Universe& universe,
                    const yli::ontology::ObjectStruct& terrain_struct,
                    yli::ontology::GenericParentModule* const parent_module,
                    yli::ontology::GenericMasterModule* const mesh_master,
                    yli::ontology::GenericMasterModule* const /* brain_master */);

            ~Terrain() = default;

            Terrain(const Terrain&) = delete;            // Delete copy constructor.
            Terrain &operator=(const Terrain&) = delete; // Delete copy assignment.
    };
}

#endif
