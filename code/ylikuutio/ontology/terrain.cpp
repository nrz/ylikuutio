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

#include "terrain.hpp"
#include "object.hpp"

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class Universe;
    class GenericParentModule;
    class GenericMasterModule;
    struct HolobiontStruct;

    Terrain::Terrain(
            yli::core::Application& application,
            Universe& universe,
            const ObjectStruct& terrain_struct,
            GenericParentModule* const scene_parent_module,
            GenericMasterModule* const species_master_module,
            GenericMasterModule* const /* brain_master_module */)
        : Object(application, universe, terrain_struct, scene_parent_module, species_master_module, nullptr)
    {
        // `Entity` member variables begin here.
        this->type_string = "yli::ontology::Terrain*";
    }
}
