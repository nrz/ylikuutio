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

#include "executor.hpp"
#include "code/ylikuutio/core/application.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/console.hpp"
#include "code/ylikuutio/ontology/lisp_function.hpp"

// Include standard headers
#include <optional> // std::optional
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::lisp
{
    std::optional<yli::data::AnyValue> execute(
            const yli::ontology::Console& console,
            const std::string& command,
            const std::vector<std::string>& parameter_vector)
    {
        // Call the corresponding `yli::ontology::LispFunction`, if there is one.
        // `LispFunction` itself takes care of resolving the correct overload
        // and binding the arguments and calling the overload with the arguments.

        yli::ontology::Universe& universe = console.get_application().get_universe();

        yli::ontology::Entity* const lisp_function_entity = universe.get_entity(command);

        if (lisp_function_entity != nullptr && lisp_function_entity->get_parent() == &console)
        {
            yli::ontology::LispFunction* const lisp_function =
                dynamic_cast<yli::ontology::LispFunction*>(lisp_function_entity);

            if (lisp_function != nullptr)
            {
                return lisp_function->execute(parameter_vector);
            }
        }

        return std::nullopt;
    }
}
