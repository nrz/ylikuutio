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

#ifndef __INPUT_MODE_HPP_INCLUDED
#define __INPUT_MODE_HPP_INCLUDED

#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

namespace yli
{
    namespace callback
    {
        class CallbackEngine;
    }

    namespace input
    {
        class InputMaster;

        class InputMode
        {
            public:
                // destructor.
                ~InputMode();
                void activate();
                void deactivate();

                yli::callback::CallbackEngine* get_keypress_callback_engine(uint32_t keycode) const;
                yli::callback::CallbackEngine* get_keyrelease_callback_engine(uint32_t keycode) const;
                yli::callback::CallbackEngine* get_continuous_keypress_callback_engine(uint32_t keycode) const;

                void set_keypress_callback_engine(uint32_t keycode, yli::callback::CallbackEngine* callback_engine);
                void set_keyrelease_callback_engine(uint32_t keycode, yli::callback::CallbackEngine* callback_engine);
                void set_continuous_keypress_callback_engine(uint32_t keycode, yli::callback::CallbackEngine* callback_engine);

                const std::vector<yli::callback::CallbackEngine*>* get_keypress_callback_engines() const;
                const std::vector<yli::callback::CallbackEngine*>* get_keyrelease_callback_engines() const;
                const std::vector<yli::callback::CallbackEngine*>* get_continuous_keypress_callback_engines() const;

                friend class InputMaster;
                template<class T1>
                    friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);

            private:
                void bind_to_parent();

                // constructor.
                InputMode(yli::input::InputMaster* const input_master);

                InputMode(const InputMode&) = delete;            // Delete copy constructor.
                InputMode &operator=(const InputMode&) = delete; // Delete copy assignment.

                yli::input::InputMaster* parent;
                std::size_t childID;

                std::vector<yli::callback::CallbackEngine*> keypress_callback_engines;
                std::vector<yli::callback::CallbackEngine*> keyrelease_callback_engines;
                std::vector<yli::callback::CallbackEngine*> continuous_keypress_callback_engines;
        };
    }
}

#endif
