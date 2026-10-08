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

#ifndef YLI_ONTOLOGY_HEIGHTMAP_HPP_INCLUDED
#define YLI_ONTOLOGY_HEIGHTMAP_HPP_INCLUDED

#include "child_module.hpp"
#include "generic_parent_module.hpp"
#include "movable.hpp"

// Include standard headers
#include <cstddef> // std::size_t

namespace yli::core
{
    class Application;
}

namespace yli::memory
{
    template<typename T1, std::size_t DataSize>
    class MemoryStorage;
}

namespace yli::ontology
{
    class GenericMasterModule;
    class Entity;
    class Universe;
    class Scene;
    class HeightmapSheet;
    struct HeightmapStruct;

    class Heightmap final : public Movable
    {
    public:
        Heightmap(
            core::Application& application,
            Universe& universe,
            const HeightmapStruct& heightmap_struct,
            GenericParentModule* scene_parent_module,
            GenericMasterModule* movable_controller_master_module);

        Heightmap(const Heightmap&) = delete;            // Delete copy constructor.
        Heightmap& operator=(const Heightmap&) = delete; // Delete copy assignment.

        virtual ~Heightmap() = default;

        Scene* get_scene() const override;

        Entity* get_parent() const override;

        std::size_t get_number_of_children() const override;

        std::size_t get_number_of_descendants() const override;

        template<typename ChildType>
        GenericParentModule* get_generic_parent_module() = delete;

        template<typename T1, std::size_t DataSize>
        friend class memory::MemoryStorage;

        ChildModule child_of_scene;
        GenericParentModule parent_of_heightmap_sheets;
    };

    template<>
    inline GenericParentModule* Heightmap::get_generic_parent_module<HeightmapSheet>()
    {
        return &this->parent_of_heightmap_sheets;
    }
}

#endif
