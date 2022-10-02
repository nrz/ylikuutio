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

#ifndef YLIKUUTIO_ONTOLOGY_LISP_FUNCTION_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_LISP_FUNCTION_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "generic_parent_module.hpp"
#include "lisp_function_struct.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <cstddef>    // std::size_t
#include <optional>   // std::optional
#include <string>     // std::string
#include <vector>     // std::vector

namespace yli::ontology
{
    class Universe;
    class Scene;
    class Console;

    class LispFunction final : public yli::ontology::Entity
    {
        public:
            LispFunction(
                    yli::ontology::Universe& universe,
                    const yli::ontology::LispFunctionStruct& lisp_function_struct,
                    yli::ontology::GenericParentModule* const parent_module)
                : Entity(universe, lisp_function_struct),
                child_of_console(parent_module, this),
                parent_of_generic_lisp_function_overloads(this, &this->registry, "generic_lisp_functions")
            {
                // constructor.

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::LispFunction*";
            }

            LispFunction(const LispFunction&) = delete;            // Delete copy constructor.
            LispFunction& operator=(const LispFunction&) = delete; // Delete copy assignment.

            // destructor.
            ~LispFunction() = default;

            yli::ontology::Entity* get_parent() const override;

            std::optional<yli::data::AnyValue> execute(const std::vector<std::string>& parameter_vector);

            yli::ontology::ChildModule child_of_console;
            yli::ontology::GenericParentModule parent_of_generic_lisp_function_overloads;

        private:
            yli::ontology::Scene* get_scene() const override;
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;
    };
}

#endif
