// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
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

#include "lisp_function.hpp"
#include "generic_lisp_function_overload.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <cstddef>    // std::size_t
#include <optional>   // std::optional
#include <string>     // std::string
#include <vector>     // std::vector

namespace yli::ontology
{
    class Entity;
    class Scene;

    LispFunction::~LispFunction()
    {
        // destructor.
    }

    yli::ontology::Entity* LispFunction::get_parent() const
    {
        return this->child_of_console.get_parent();
    }

    yli::ontology::Scene* LispFunction::get_scene() const
    {
        // `LispFunction` does not belong in any `Scene`.
        return nullptr;
    }

    std::size_t LispFunction::get_number_of_children() const
    {
        return this->parent_of_generic_lisp_function_overloads.get_number_of_children();
    }

    std::size_t LispFunction::get_number_of_descendants() const
    {
        return yli::ontology::get_number_of_descendants(this->parent_of_generic_lisp_function_overloads.child_pointer_vector);
    }

    std::optional<yli::data::AnyValue> LispFunction::execute(const std::vector<std::string>& parameter_vector)
    {
        // The execution of a `LispFunction` proceeds as follows:
        // The execution of `GenericLispFunctionOverload` children of
        // this `LispFunction` is attempted in ID order, in
        // the order of the child pointer vector.
        //
        // If the variable binding succeeds, then that
        // `GenericLispFunctionOverload` is called and its return value
        // is returned.
        //
        // If the variable binding fails, then next
        // `GenericLispFunctionOverload` in attempted etc.
        //
        // If variable binding fails for all `GenericLispFunctionOverload`s,
        // then 'std::nullopt` is returned.
        //
        // If there is are `GenericLispFunctionOverload`s,
        // then `std::nullopt` is returned as well.

        for (std::vector<yli::ontology::Entity*>::const_iterator it = this->parent_of_generic_lisp_function_overloads.child_pointer_vector.begin();
                it != this->parent_of_generic_lisp_function_overloads.child_pointer_vector.end();
                ++it)
        {
            std::optional<yli::data::AnyValue> result = static_cast<yli::ontology::GenericLispFunctionOverload*>(*it)->execute(parameter_vector);

            if (result)
            {
                return result;
            }
        }

        return std::nullopt;
    }
}
