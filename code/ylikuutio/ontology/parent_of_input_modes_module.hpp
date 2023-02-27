// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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

#ifndef YLIKUUTIO_PARENT_OF_INPUT_MODES_MODULE_HPP_INCLUDED
#define YLIKUUTIO_PARENT_OF_INPUT_MODES_MODULE_HPP_INCLUDED

#include "generic_parent_module.hpp"
#include "code/ylikuutio/input/input.hpp"

// Include standard headers
#include <stack> // std::stack

namespace yli::ontology
{
    class Universe;
    class InputMode;

    class ParentOfInputModesModule final : public GenericParentModule
    {
        public:
            ParentOfInputModesModule(
                    yli::ontology::Universe* universe,
                    yli::ontology::Registry* const registry,
                    const std::string& name) noexcept;

            ParentOfInputModesModule(const ParentOfInputModesModule&) = delete;            // Delete copy constructor.
            ParentOfInputModesModule& operator=(const ParentOfInputModesModule&) = delete; // Delete copy assignment.

            ~ParentOfInputModesModule() = default;

            void set_active_input_mode(yli::ontology::InputMode* const input_mode);
            yli::ontology::InputMode* get_active_input_mode() const;

            void pop_input_mode();

            yli::input::InputMethod get_input_method() const;

        private:
            yli::ontology::InputMode* active_input_mode { nullptr };

            std::stack<yli::ontology::InputMode*> input_mode_stack;

            yli::input::InputMethod input_method { yli::input::InputMethod::KEYBOARD };
    };
}

#endif
