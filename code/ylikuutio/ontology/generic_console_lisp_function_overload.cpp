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

#include "generic_console_lisp_function_overload.hpp"

// Include standard headers
#include <stdexcept> // std::runtime_error
#include <cstddef>   // std::size_t

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class GenericParentModule;
    class Entity;
    class GenericLispFunctionOverload;
    class Universe;
    class Scene;

    GenericConsoleLispFunctionOverload::GenericConsoleLispFunctionOverload(
            yli::core::Application& application,
            Universe& universe,
            GenericParentModule* const console_lisp_function_parent_module)
        : GenericLispFunctionOverload(application, universe),
        child_of_console_lisp_function(console_lisp_function_parent_module, *this)
    {
        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "yli::ontology::GenericConsoleLispFunctionOverload*";
    }

    Entity* GenericConsoleLispFunctionOverload::get_parent() const
    {
        return this->child_of_console_lisp_function.get_parent();
    }

    std::size_t GenericConsoleLispFunctionOverload::get_number_of_children() const
    {
        return 0; // `GenericConsoleLispFunctionOverload` has no children.
    }

    std::size_t GenericConsoleLispFunctionOverload::get_number_of_descendants() const
    {
        return 0; // `GenericConsoleLispFunctionOverload` has no children.
    }

    Scene* GenericConsoleLispFunctionOverload::get_scene() const
    {
        const Entity* const console_lisp_function_parent = this->get_parent();

        if (console_lisp_function_parent == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `GenericConsoleLispFunctionOverload::get_scene`: `console_lisp_function_parent` is `nullptr`!");
        }

        return console_lisp_function_parent->get_scene();
    }
}
