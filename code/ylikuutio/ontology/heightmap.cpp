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

#include "heightmap.hpp"
#include "scene.hpp"
#include "heightmap_struct.hpp"
#include "get_number_of_descendants.hpp"

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

    Heightmap::Heightmap(
        core::Application& application,
        Universe& universe,
        const HeightmapStruct& heightmap_struct,
        GenericParentModule* const scene_parent_module,
        GenericMasterModule* const movable_controller_master_module)
        : Movable(
              application,
              universe,
              heightmap_struct,
              movable_controller_master_module),
          child_of_scene(scene_parent_module, *this),
          parent_of_heightmap_sheets(
              *this,
              this->registry,
              "heightmap_sheets")
    {
        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "yli::ontology::Heightmap*";
        this->can_be_erased = true;
    }

    Scene* Heightmap::get_scene() const
    {
        return static_cast<Scene*>(this->child_of_scene.get_parent());
    }

    Entity* Heightmap::get_parent() const
    {
        return this->child_of_scene.get_parent();
    }

    std::size_t Heightmap::get_number_of_children() const
    {
        return this->parent_of_heightmap_sheets.get_number_of_children();
    }

    std::size_t Heightmap::get_number_of_descendants() const
    {
        return ontology::get_number_of_descendants(this->parent_of_heightmap_sheets.child_pointer_vector);
    }
}
