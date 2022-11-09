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

#include "generic_lisp_function_overload.hpp"
#include "entity.hpp"
#include "entity_struct.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <cstddef> // std::size_t

namespace yli::ontology
{
    class GenericParentModule;
    class Entity;
    class Universe;
    class Scene;

    GenericLispFunctionOverload::GenericLispFunctionOverload(
            yli::ontology::Universe& universe,
            yli::ontology::GenericParentModule* const parent_module)
        : Entity(universe, yli::ontology::EntityStruct()),
        child_of_lisp_function(parent_module, this)
    {
        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "yli::ontology::GenericLispFunctionOverload*";
    }

    yli::ontology::Entity* GenericLispFunctionOverload::get_parent() const
    {
        return this->child_of_lisp_function.get_parent();
    }

    yli::ontology::Scene* GenericLispFunctionOverload::get_scene() const
    {
        const yli::ontology::Entity* const parent = this->get_parent();

        if (parent != nullptr)
        {
            return parent->get_scene();
        }

        return nullptr;
    }

    std::size_t GenericLispFunctionOverload::get_number_of_children() const
    {
        return 0; // `GenericLispFunctionOverload` has no children.
    }

    std::size_t GenericLispFunctionOverload::get_number_of_descendants() const
    {
        return 0; // `GenericLispFunctionOverload` has no children.
    }
}
