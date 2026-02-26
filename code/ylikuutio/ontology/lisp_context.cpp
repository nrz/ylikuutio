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

#include "lisp_context.hpp"
#include "universe.hpp"
#include "lisp_context_struct.hpp"
#include "family_templates.hpp"

// Include standard headers
#include <cstddef> // std::size_t

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class GenericParentModule;
    class Entity;
    class Scene;

    Entity* LispContext::get_parent() const
    {
        return nullptr;
    }

    LispContext::LispContext(
            yli::core::Application& application,
            Universe& universe,
            const LispContextStruct& lisp_context_struct)
        : Entity(application, universe, lisp_context_struct),
        parent_of_lisp_functions(
                *this,
                this->registry,
                "lisp_functions")
    {
        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "yli::ontology::LispContext*";
        this->can_be_erased = true;
    }

    std::size_t LispContext::get_number_of_children() const
    {
        return this->parent_of_lisp_functions.get_number_of_children();
    }

    std::size_t LispContext::get_number_of_descendants() const
    {
        return yli::ontology::get_number_of_descendants(this->parent_of_lisp_functions.child_pointer_vector);
    }

    Scene* LispContext::get_scene() const
    {
        // `LispContext` does not belong in any `Scene`.
        return nullptr;
    }
}
