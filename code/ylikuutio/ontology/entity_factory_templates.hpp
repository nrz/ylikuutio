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

#ifndef __ENTITY_FACTORY_TEMPLATES_HPP_INCLUDED
#define __ENTITY_FACTORY_TEMPLATES_HPP_INCLUDED

#include "universe.hpp"
#include "console.hpp"
#include "console_command.hpp"
#include "lisp_function_overload.hpp"
#include "generic_console_command_overload.hpp"
#include "entity_factory.hpp"
#include "console_command_struct.hpp"

// Include standard headers
#include <functional> // std::function
#include <memory>     // std::make_shared, std::shared_ptr
#include <string>     // std::string

namespace yli::data
{
    class AnyValue;
}

namespace yli::ontology
{
    class Entity;
    class Universe;
    class ParentModule;

    template<class... Args>
        yli::ontology::GenericConsoleCommandOverload* create_console_command_overload(
                const std::string& name,
                yli::ontology::Console* const console,
                std::function<std::shared_ptr<yli::data::AnyValue>(Args...)> callback)
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

            yli::ontology::Entity* const console_command_entity = universe->get_entity(name);

            yli::ontology::ConsoleCommand* console_command = nullptr;

            if (console_command_entity == nullptr)
            {
                // There was not any `Entity` with that name.
                yli::ontology::ConsoleCommandStruct console_command_struct;
                console_command_struct.parent = console;
                yli::ontology::Entity* const new_console_command_entity = entity_factory->create_console_command(console_command_struct);

                console_command = dynamic_cast<yli::ontology::ConsoleCommand*>(new_console_command_entity);

                if (console_command == nullptr)
                {
                    // Creating `ConsoleCommand` failed.
                    return nullptr;
                }

                // OK, set a name for the newly created `ConsoleCommand`.
                console_command->set_name(name);
            }
            else
            {
                console_command = dynamic_cast<yli::ontology::ConsoleCommand*>(console_command_entity);

                if (console_command == nullptr)
                {
                    // The name is in use and the `Entity` is not a `ConsoleCommand`.
                    return nullptr;
                }
            }

            yli::ontology::GenericConsoleCommandOverload* const generic_console_command_overload = new yli::ontology::LispFunctionOverload<Args...>(
                    universe,
                    &console_command->parent_of_generic_console_command_overloads,
                    callback);
            generic_console_command_overload->set_name(name);
            return generic_console_command_overload;
        }
}

#endif
