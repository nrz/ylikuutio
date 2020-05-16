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

#include "console_command.hpp"
#include "generic_console_command_overload.hpp"
#include "family_templates.hpp"

// Include standard headers
#include <memory>     // std::make_shared, std::shared_ptr
#include <utility>    // std::pair

namespace yli::ontology
{
    ConsoleCommand::~ConsoleCommand()
    {
        // destructor.
    }

    yli::ontology::Entity* ConsoleCommand::get_parent() const
    {
        return this->child_of_console.get_parent();
    }

    std::size_t ConsoleCommand::get_number_of_children() const
    {
        return this->parent_of_generic_console_command_overloads.get_number_of_children();
    }

    std::size_t ConsoleCommand::get_number_of_descendants() const
    {
        return yli::ontology::get_number_of_descendants(this->parent_of_generic_console_command_overloads.child_pointer_vector);
    }

    std::shared_ptr<yli::data::AnyValue> ConsoleCommand::execute(const std::vector<std::string>& parameter_vector)
    {
        // The execution of a `ConsoleCommand` proceeds as follows:
        // The execution of `GenericConsoleCommandOverload` children of
        // this `ConsoleCommand` is attempted in ID order, in
        // the order of the child pointer vector.
        //
        // If the variable binding succeeds, then that
        // `GenericConsoleCommandOverload` is called and its return value
        // is returned.
        //
        // If the variable binding fails, then next 
        // `GenericConsoleCommandOverload` in attempted etc.
        //
        // If variable binding fails for all `GenericConsoleCommandOverload`s,
        // then 'nullptr` is returned.
        //
        // If there is no `GenericConsoleCommandOverload`s,
        // then `nullptr` is returned as well.

        for (std::vector<yli::ontology::Entity*>::const_iterator it = this->parent_of_generic_console_command_overloads.child_pointer_vector.begin();
                it != this->parent_of_generic_console_command_overloads.child_pointer_vector.end();
                it++)
        {
            std::pair<bool, std::shared_ptr<yli::data::AnyValue>> success_and_return_value =
                static_cast<yli::ontology::GenericConsoleCommandOverload*>(*it)->execute(parameter_vector);

            if (success_and_return_value.first == true)
            {
                return success_and_return_value.second; // Return the return value of the callback.
            }
        }

        return nullptr;
    }
}
