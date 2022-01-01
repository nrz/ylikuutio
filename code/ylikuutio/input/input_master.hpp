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

#ifndef __YLIKUUTIO_INPUT_INPUT_MASTER_HPP_INCLUDED
#define __YLIKUUTIO_INPUT_INPUT_MASTER_HPP_INCLUDED

#include "input.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <queue>   // std::queue
#include <stack>   // std::stack
#include <vector>  // std::vector

namespace yli::ontology
{
    class Universe;
}

namespace yli::input
{
    class InputMode;

    class InputMaster
    {
        public:
            void bind_input_mode(yli::input::InputMode* const input_mode);

            // constructor.
            explicit InputMaster(yli::ontology::Universe* const universe);

            InputMaster(const InputMaster&) = delete;            // Delete copy constructor.
            InputMaster& operator=(const InputMaster&) = delete; // Delete copy assignment.

            // destructor.
            ~InputMaster();

            yli::input::InputMode* create_input_mode();

            void set_active_input_mode(yli::input::InputMode* const input_mode);
            yli::input::InputMode* get_active_input_mode() const;

            void pop_input_mode();

            yli::input::InputMethod get_input_method() const;

        private:
            yli::ontology::Universe* const universe { nullptr };

            yli::input::InputMode* active_input_mode { nullptr };

            std::stack<yli::input::InputMode*> input_mode_stack;

            std::vector<yli::input::InputMode*> input_mode_pointer_vector;
            std::queue<std::size_t> free_input_modeID_queue;
            std::size_t number_of_input_modes { 0 };

            yli::input::InputMethod input_method;
    };
}

#endif
