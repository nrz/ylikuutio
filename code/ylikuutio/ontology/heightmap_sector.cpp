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

#include "heightmap_sector.hpp"
#include "heightmap.hpp"
#include "heightmap_sector_struct.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <string_view> // std::string_view
#include <utility>     // std::move

namespace yli::core
{
    class Application;
}

namespace yli::memory
{
    struct AllocationData;
}

namespace yli::ontology
{
    class GenericParentModule;
    class GenericMasterModule;
    class Entity;
    class Universe;
    class Scene;

    Heightmap* HeightmapSector::get_heightmap() const
    {
        return static_cast<Heightmap*>(this->get_parent());
    }

    std::string_view HeightmapSector::get_type() const
    {
        return "yli::ontology::HeightmapSector*";
    }

    Entity* HeightmapSector::get_parent() const
    {
        return this->child_of_heightmap.get_parent();
    }

    HeightmapSector::HeightmapSector(
        memory::AllocationData&& allocation_data,
        core::Application& application,
        Universe& universe,
        const HeightmapSectorStruct& heightmap_sector_struct,
        GenericParentModule* scene_parent_module,
        GenericMasterModule* movable_controller_master_module)
        : AbstractMovable(
              std::move(allocation_data),
              application,
              universe,
              heightmap_sector_struct,
              movable_controller_master_module),
          child_of_heightmap(scene_parent_module, *this)
    {
    }

    std::size_t HeightmapSector::get_number_of_children() const
    {
        return 0; // `HeightmapSector` has no children.
    }

    std::size_t HeightmapSector::get_number_of_descendants() const
    {
        return 0; // `HeightmapSector` has no children.
    }

    Scene* HeightmapSector::get_scene() const
    {
        return this->child_of_heightmap.get_scene();
    }
}
