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

#ifndef __YLIKUUTIO_ONTOLOGY_ENTITY_FACTORY_TEMPLATES_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_ENTITY_FACTORY_TEMPLATES_HPP_INCLUDED

#include "universe.hpp"
#include "console.hpp"
#include "lisp_function.hpp"
#include "lisp_function_overload.hpp"
#include "generic_lisp_function_overload.hpp"
#include "entity_factory.hpp"
#include "lisp_function_struct.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <functional> // std::function
#include <optional>   // std::optional
#include <string>     // std::string

namespace yli::ontology
{
    class Entity;
    class Universe;

    template<typename... Args>
        yli::ontology::GenericLispFunctionOverload* create_lisp_function_overload(
                const std::string& name,
                yli::ontology::Console* const console,
                std::function<std::optional<yli::data::AnyValue>(Args...)> callback)
        {
            if (console == nullptr)
            {
                return nullptr;
            }

            yli::ontology::Universe* const universe = console->get_universe();

            if (universe == nullptr)
            {
                return nullptr;
            }

            yli::ontology::EntityFactory* const entity_factory = universe->get_entity_factory();

            if (entity_factory == nullptr)
            {
                return nullptr;
            }

            yli::ontology::Entity* const lisp_function_entity = universe->get_entity(name);

            yli::ontology::LispFunction* lisp_function = nullptr;

            if (lisp_function_entity == nullptr)
            {
                // There was not any `Entity` with that name.
                yli::ontology::LispFunctionStruct lisp_function_struct;
                lisp_function_struct.parent = console;
                yli::ontology::Entity* const new_lisp_function_entity = entity_factory->create_lisp_function(lisp_function_struct);

                lisp_function = dynamic_cast<yli::ontology::LispFunction*>(new_lisp_function_entity);

                if (lisp_function == nullptr)
                {
                    // Creating `LispFunction` failed.
                    return nullptr;
                }

                // OK, set a name for the newly created `LispFunction`.
                lisp_function->set_global_name(name);
            }
            else
            {
                lisp_function = dynamic_cast<yli::ontology::LispFunction*>(lisp_function_entity);

                if (lisp_function == nullptr)
                {
                    // The name is in use and the `Entity` is not a `LispFunction`.
                    return nullptr;
                }
            }

            yli::ontology::GenericLispFunctionOverload* const generic_lisp_function_overload = new yli::ontology::LispFunctionOverload<Args...>(
                    universe,
                    &lisp_function->parent_of_generic_lisp_function_overloads,
                    callback);
            generic_lisp_function_overload->set_global_name(name);
            return generic_lisp_function_overload;
        }
}

#endif
