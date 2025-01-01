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

#include "shapeshifter.hpp"
#include "scene.hpp"
#include "shapeshifter_struct.hpp"

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

    Entity* Shapeshifter::get_parent() const
    {
        return this->child_of_scene.get_parent();
    }

    Shapeshifter::Shapeshifter(
            yli::core::Application& application,
            Universe& universe,
            const ShapeshifterStruct& shapeshifter_struct,
            GenericParentModule* const scene_parent_module,
            GenericMasterModule* const brain_master_module,
            GenericMasterModule* const shapeshifter_sequence_master_module)
        : Movable(
                application,
                universe,
                shapeshifter_struct,
                brain_master_module),
        child_of_scene(scene_parent_module, *this),
        apprentice_of_shapeshifter_sequence(shapeshifter_sequence_master_module, this)
    {
        // `Entity` member variables begin here.
        this->type_string = "yli::ontology::Shapeshifter*";
        this->can_be_erased = true;
    }

    std::size_t Shapeshifter::get_number_of_children() const
    {
        return 0; // `Shapeshifter` has no children.
    }

    std::size_t Shapeshifter::get_number_of_descendants() const
    {
        return 0; // `Shapeshifter` has no children.
    }

    Scene* Shapeshifter::get_scene() const
    {
        return this->child_of_scene.get_scene();
    }
}
