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

#include "lisp_function.hpp"
#include "entity.hpp"
#include "generic_lisp_function_overload.hpp"
#include "result.hpp"
#include "lisp_function_struct.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <optional>   // std::optional
#include <string>     // std::string
#include <vector>     // std::vector

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class Entity;

    LispFunction::LispFunction(
            yli::core::Application& application,
            Universe& universe,
            const LispFunctionStruct& lisp_function_struct)
        : Entity(application, universe, lisp_function_struct)
    {
        // `Entity` member variables begin here.
        this->type_string = "yli::ontology::LispFunction*";
    }
}
