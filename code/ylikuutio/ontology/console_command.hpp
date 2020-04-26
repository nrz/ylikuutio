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

#ifndef __CONSOLE_COMMAND_HPP_INCLUDED
#define __CONSOLE_COMMAND_HPP_INCLUDED

#include "entity.hpp"
#include "child_module.hpp"
#include "console_command_struct.hpp"

// Include standard headers
#include <cstddef> // std::size_t

namespace yli::ontology
{
    class Universe;
    class ParentModule;

    class ConsoleCommand: public yli::ontology::Entity
    {
        public:
            ConsoleCommand(
                    yli::ontology::Universe* const universe,
                    const yli::ontology::ConsoleCommandStruct& console_command_struct,
                    yli::ontology::ParentModule* const parent_module)
                : Entity(universe),
                child_of_console(parent_module, this)
            {
                // constructor.
                this->parent = console_command_struct.parent;
            }

            ConsoleCommand(const ConsoleCommand&) = delete;            // Delete copy constructor.
            ConsoleCommand &operator=(const ConsoleCommand&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~ConsoleCommand();

            yli::ontology::Entity* get_parent() const override;
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            yli::ontology::ChildModule child_of_console;

        private:
            yli::ontology::Console* parent;
    };
}

#endif
