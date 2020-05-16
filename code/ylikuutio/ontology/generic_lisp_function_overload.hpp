// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
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

#ifndef __GENERIC_LISP_FUNCTION_OVERLOAD_HPP_INCLUDED
#define __GENERIC_LISP_FUNCTION_OVERLOAD_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <functional> // std::function
#include <memory>     // std::make_shared, std::shared_ptr
#include <string>     // std::string
#include <utility>    // std::pair
#include <vector>     // std::vector

namespace yli::data
{
    class AnyValue;
}

namespace yli::ontology
{
    class Universe;
    class ParentModule;
    class Console;

    class GenericLispFunctionOverload: public yli::ontology::Entity
    {
        public:
            GenericLispFunctionOverload(
                    yli::ontology::Universe* const universe,
                    yli::ontology::ParentModule* const parent_module)
                : Entity(universe),
                child_of_console_command(parent_module, this)
            {
                // constructor.

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::GenericLispFunctionOverload*";
            }

            GenericLispFunctionOverload(const GenericLispFunctionOverload&) = delete;            // Delete copy constructor.
            GenericLispFunctionOverload &operator=(const GenericLispFunctionOverload&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~GenericLispFunctionOverload();

            yli::ontology::Entity* get_parent() const override;
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            virtual std::pair<bool, std::shared_ptr<yli::data::AnyValue>> execute(const std::vector<std::string>& parameter_vector) = 0;

            yli::ontology::ChildModule child_of_console_command;
    };
}

#endif
