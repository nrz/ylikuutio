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

#ifndef YLIKUUTIO_ONTOLOGY_GENERIC_LISP_FUNCTION_OVERLOAD_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_GENERIC_LISP_FUNCTION_OVERLOAD_HPP_INCLUDED

#include "entity.hpp"
#include "result.hpp"

// Include standard headers
#include <cstddef>    // std::size_t
#include <string>     // std::string
#include <vector>     // std::vector

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class Universe;

    class GenericLispFunctionOverload : public Entity
    {
        protected:
            GenericLispFunctionOverload(yli::core::Application& application, Universe& universe);

        public:
            GenericLispFunctionOverload(const GenericLispFunctionOverload&) = delete;            // Delete copy constructor.
            GenericLispFunctionOverload& operator=(const GenericLispFunctionOverload&) = delete; // Delete copy assignment.

            virtual ~GenericLispFunctionOverload() = default;

            virtual Result execute(const std::vector<std::string>& parameter_vector) = 0;
    };
}

#endif
