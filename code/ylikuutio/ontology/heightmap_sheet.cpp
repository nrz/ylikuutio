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

#include "heightmap_sheet.hpp"
#include "heightmap.hpp"
#include "heightmap_sheet_struct.hpp"

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

    Heightmap* HeightmapSheet::get_heightmap() const
    {
        return static_cast<Heightmap*>(this->get_parent());
    }

    Entity* HeightmapSheet::get_parent() const
    {
        return this->child_of_heightmap.get_parent();
    }

    HeightmapSheet::HeightmapSheet(
        core::Application& application,
        Universe& universe,
        const HeightmapSheetStruct& heightmap_sheet_struct,
        GenericParentModule* scene_parent_module,
        GenericMasterModule* movable_controller_master_module)
        : Movable(
              application,
              universe,
              heightmap_sheet_struct,
              movable_controller_master_module),
          child_of_heightmap(scene_parent_module, *this)
    {
        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "yli::ontology::HeightmapSheet*";
    }

    std::size_t HeightmapSheet::get_number_of_children() const
    {
        return 0; // `HeightmapSheet` has no children.
    }

    std::size_t HeightmapSheet::get_number_of_descendants() const
    {
        return 0; // `HeightmapSheet` has no children.
    }

    Scene* HeightmapSheet::get_scene() const
    {
        return this->child_of_heightmap.get_scene();
    }
}
