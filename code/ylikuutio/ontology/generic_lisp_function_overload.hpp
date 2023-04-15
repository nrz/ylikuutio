// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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

#ifndef YLIKUUTIO_ONTOLOGY_GENERIC_LISP_FUNCTION_OVERLOAD_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_GENERIC_LISP_FUNCTION_OVERLOAD_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <cstddef>    // std::size_t
#include <functional> // std::function
#include <optional>   // std::optional
#include <string>     // std::string
#include <vector>     // std::vector

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class GenericParentModule;
    class Universe;
    class Scene;
    class Console;

    class GenericLispFunctionOverload: public yli::ontology::Entity
    {
        public:
            GenericLispFunctionOverload(
                    yli::core::Application& application,
                    yli::ontology::Universe& universe,
                    yli::ontology::GenericParentModule* const parent_module);

            GenericLispFunctionOverload(const GenericLispFunctionOverload&) = delete;            // Delete copy constructor.
            GenericLispFunctionOverload& operator=(const GenericLispFunctionOverload&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~GenericLispFunctionOverload() = default;

            yli::ontology::Entity* get_parent() const override;

            virtual std::optional<yli::data::AnyValue> execute(const std::vector<std::string>& parameter_vector) = 0;

            yli::ontology::ChildModule child_of_lisp_function;

        private:
            yli::ontology::Scene* get_scene() const override;
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;
    };
}

#endif
