// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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

#include "completion_module.hpp"
#include "text_input.hpp"
#include "code/ylikuutio/lisp/parser.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/console.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <string>  // std::string
#include <vector>  // std::vector

namespace yli::console
{
    CompletionModule::CompletionModule(yli::ontology::Console& console)
        : console { console }
    {
    }

    void CompletionModule::complete()
    {
        yli::ontology::Universe& universe = this->console.get_universe();

        if (this->console.console_logic_module.get_active_in_console() && this->console.console_logic_module.get_can_tab())
        {
            yli::console::TextInput* const active_input = this->console.console_logic_module.edit_input();

            if (active_input == nullptr)
            {
                return;
            }

            // Copy active input into a `std::string`.
            std::string input_string(active_input->data());

            std::vector<std::string> parameter_vector;
            std::string command;

            yli::lisp::parse(input_string, command, parameter_vector);

            if (command.empty() ||
                    (parameter_vector.empty() && input_string.back() != ' '))
            {
                // If `input_string` is empty, then complete the command.
                // Also if there are no parameters and `input_string` does not end with a space, then complete the command.

                this->console.print_completions(universe.registry, command);

                const std::string completion = universe.complete(command);
                active_input->clear();
                active_input->add_characters(completion);
            }
            else if (parameter_vector.empty())
            {
                // If `input_string` has no parameters,
                // then complete the parameter using the empty string.

                // If `input_string` is empty, then complete the parameter.

                this->console.print_completions(universe.registry, "");

                const std::string completion = universe.complete("");

                if (!completion.empty())
                {
                    active_input->add_characters(completion);
                }
            }
            else if (input_string.back() != ' ')
            {
                // If `input_string` does not end with a space,
                // then complete the current parameter.

                this->console.print_completions(universe.registry, parameter_vector.back());

                const std::string completion = universe.complete(parameter_vector.back());
                active_input->clear();
                active_input->add_characters(command);
                active_input->add_character(' ');

                // Copy the old parameters except the last.

                for (std::size_t i = 0; i + 1 < parameter_vector.size(); i++)
                {
                    active_input->add_characters(parameter_vector.at(i));
                    this->console.move_cursor_to_end_of_line();
                    active_input->add_character(' ');
                }

                // Copy the completed parameter.
                active_input->add_characters(completion);
            }
            else
            {
                // Complete the next parameter.

                const std::string completion = universe.complete("");

                if (!completion.empty())
                {
                    // Copy the completed parameter.
                    active_input->add_characters(completion);
                }
            }

            this->console.move_cursor_to_end_of_line();

            this->console.console_logic_module.set_can_tab(false);
        }
    }
}
