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

#ifndef YLIKUUTIO_ONTOLOGY_ABSTRACT_LISP_FUNCTION_OVERLOAD_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_ABSTRACT_LISP_FUNCTION_OVERLOAD_HPP_INCLUDED

#include "entity.hpp"
#include "result.hpp"

// Include standard headers
#include <string>     // std::string
#include <vector>     // std::vector

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class Universe;

    class AbstractLispFunctionOverload : public Entity
    {
    protected:
        AbstractLispFunctionOverload(core::Application& application, Universe& universe);

    public:
        AbstractLispFunctionOverload(const AbstractLispFunctionOverload&) = delete; // Delete copy constructor.
        AbstractLispFunctionOverload& operator=(const AbstractLispFunctionOverload&) = delete; // Delete copy assignment.

        ~AbstractLispFunctionOverload() override = default;

        virtual Result execute(const std::vector<std::string>& parameter_vector) = 0;
    };
}

#endif
