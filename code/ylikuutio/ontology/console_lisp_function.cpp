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

#include "console_lisp_function.hpp"
#include "console.hpp"
#include "generic_console_lisp_function_overload.hpp"
#include "result.hpp"
#include "console_lisp_function_struct.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <optional> // std::optional
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class GenericParentModule;
    class Entity;
    class Universe;
    class Scene;

    Console* ConsoleLispFunction::get_console() const
    {
        return static_cast<Console*>(this->get_parent());
    }

    Entity* ConsoleLispFunction::get_parent() const
    {
        return this->child_of_console.get_parent();
    }

    ConsoleLispFunction::ConsoleLispFunction(
            yli::core::Application& application,
            Universe& universe,
            const ConsoleLispFunctionStruct& console_lisp_function_struct,
            GenericParentModule* const console_parent_module)
        : LispFunction(application, universe, console_lisp_function_struct),
        child_of_console(console_parent_module, *this),
        parent_of_generic_console_lisp_function_overloads(
                *this,
                this->registry,
                "generic_console_lisp_function_overloads")
    {
        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "yli::ontology::ConsoleLispFunction*";
    }

    std::size_t ConsoleLispFunction::get_number_of_children() const
    {
        return this->parent_of_generic_console_lisp_function_overloads.get_number_of_children();
    }

    std::size_t ConsoleLispFunction::get_number_of_descendants() const
    {
        return yli::ontology::get_number_of_descendants(this->parent_of_generic_console_lisp_function_overloads.child_pointer_vector);
    }

    Scene* ConsoleLispFunction::get_scene() const
    {
        // `ConsoleLispFunction` does not belong in any `Scene`.
        return nullptr;
    }

    std::optional<yli::data::AnyValue> ConsoleLispFunction::execute(const std::vector<std::string>& parameter_vector)
    {
        // The execution of a `ConsoleLispFunction` proceeds as follows:
        // The execution of `GenericConsoleLispFunctionOverload` children of
        // this `ConsoleLispFunction` is attempted in ID order, in
        // the order of the child pointer vector.
        //
        // If the variable binding succeeds, then that
        // `GenericConsoleLispFunctionOverload` is called and its return value
        // is returned.
        //
        // If the variable binding fails, then next
        // `GenericConsoleLispFunctionOverload` in attempted etc.
        //
        // If variable binding fails for all `GenericConsoleLispFunctionOverload`s,
        // then `std::nullopt` is returned.
        //
        // If there are no `GenericConsoleLispFunctionOverload`s,
        // then `std::nullopt` is returned as well.

        for (std::vector<Entity*>::const_iterator it = this->parent_of_generic_console_lisp_function_overloads.child_pointer_vector.begin();
                it != this->parent_of_generic_console_lisp_function_overloads.child_pointer_vector.end();
                ++it)
        {
            Result result =
                static_cast<GenericConsoleLispFunctionOverload*>(*it)->execute(parameter_vector);

            if (result)
            {
                return std::get<std::optional<yli::data::AnyValue>>(result.data);
            }
        }

        return std::nullopt;
    }
}
