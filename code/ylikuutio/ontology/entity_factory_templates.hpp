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

#include "console.hpp"
#include "console_command_overload.hpp"
#include "generic_console_command.hpp"

// Include standard headers
#include <functional> // std::function
#include <memory>     // std::make_shared, std::shared_ptr
#include <string>     // std::string

namespace yli::common
{
    class AnyValue;
}

namespace yli::ontology
{
    class Entity;
    class Universe;
    class ParentModule;

    template<class... Args>
        yli::ontology::GenericConsoleCommand* create_console_command(
                const std::string& name,
                yli::ontology::Universe* const universe,
                yli::ontology::Console* const console,
                std::function<std::shared_ptr<yli::common::AnyValue>(Args...)> callback)
        {
            yli::ontology::GenericConsoleCommand* const generic_console_command = new yli::ontology::ConsoleCommandOverload<Args...>(
                    universe,
                    (console == nullptr ? nullptr : &console->parent_of_console_commands),
                    callback);
            generic_console_command->set_name(name);
            return generic_console_command;
        }
}

#endif
