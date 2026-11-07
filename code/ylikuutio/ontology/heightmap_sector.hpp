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

#ifndef YLI_ONTOLOGY_HEIGHTMAP_SECTOR_HPP_INCLUDED
#define YLI_ONTOLOGY_HEIGHTMAP_SECTOR_HPP_INCLUDED

#include "child_module.hpp"
#include "abstract_movable.hpp"
#include "heightmap_sector_struct.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <string_view> // std::string_view

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
    class Heightmap;
    struct HeightmapSectorStruct;

    class HeightmapSector final : public AbstractMovable
    {
    public:
        HeightmapSector(
            memory::AllocationData&& allocation_data,
            core::Application& application,
            Universe& universe,
            const HeightmapSectorStruct& heightmap_sector_struct,
            GenericParentModule* scene_parent_module,
            GenericMasterModule* movable_controller_master_module);

        HeightmapSector(const HeightmapSector&) = delete;            // Delete copy constructor.
        HeightmapSector& operator=(const HeightmapSector&) = delete; // Delete copy assignment.

        virtual ~HeightmapSector() = default;

        Heightmap* get_heightmap() const;

        std::string_view get_type() const override;

        Entity* get_parent() const override;

        std::size_t get_number_of_children() const override;

        std::size_t get_number_of_descendants() const override;

        Scene* get_scene() const override;

        ChildModule child_of_heightmap;
    };
}

#endif
