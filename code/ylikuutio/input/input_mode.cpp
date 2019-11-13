// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2019 Antti Nuortimo.
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

#include "input_mode.hpp"
#include "input_master.hpp"

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
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
        void InputMode::bind_to_parent()
        {
            // requirements:
            // `this->parent` must not be `nullptr`.
            yli::input::InputMaster* const input_master = this->parent;

            if (input_master == nullptr)
            {
                std::cerr << "ERROR: `InputMode::bind_to_parent`: `input_master` is `nullptr`!\n";
                return;
            }

            // get `childID` from the `InputMaster` and set pointer to this `InputMode`.
            input_master->bind_InputMode(this);
        }
        InputMode::InputMode(yli::input::InputMaster* const input_master)
        {
            // constructor.
            this->parent = input_master;

            // get `childID` from `InputMaster` and set pointer to this `InputMode`.
            this->bind_to_parent();
        }

        InputMode::~InputMode()
        {
            // destructor.
        }

        void InputMode::activate()
        {
            if (this->parent != nullptr)
            {
                this->parent->set_active_input_mode(this);
            }
        }

        void InputMode::deactivate()
        {
            if (this->parent != nullptr)
            {
                // Only the active input mode may deactivate itself.

                if (this->parent->get_active_input_mode() == this)
                {
                    this->parent->pop_input_mode();
                }
            }
        }

        yli::callback::CallbackEngine* InputMode::get_keypress_callback_engine(uint32_t keycode) const
        {
            if (keycode < this->keypress_callback_engines.size())
            {
                return this->keypress_callback_engines[keycode];
            }

            return nullptr;
        }

        yli::callback::CallbackEngine* InputMode::get_keyrelease_callback_engine(uint32_t keycode) const
        {
            if (keycode < this->keyrelease_callback_engines.size())
            {
                return this->keyrelease_callback_engines[keycode];
            }

            return nullptr;
        }

        yli::callback::CallbackEngine* InputMode::get_continuous_keypress_callback_engine(uint32_t keycode) const
        {
            if (keycode < this->continuous_keypress_callback_engines.size())
            {
                return this->continuous_keypress_callback_engines[keycode];
            }

            return nullptr;
        }

        void InputMode::set_keypress_callback_engine(uint32_t keycode, yli::callback::CallbackEngine* callback_engine)
        {
            if (keycode >= this->keypress_callback_engines.size())
            {
                this->keypress_callback_engines.resize(keycode + 1, nullptr);
            }

            this->keypress_callback_engines[keycode] = callback_engine;
        }

        void InputMode::set_keyrelease_callback_engine(uint32_t keycode, yli::callback::CallbackEngine* callback_engine)
        {
            if (keycode >= this->keyrelease_callback_engines.size())
            {
                this->keyrelease_callback_engines.resize(keycode + 1, nullptr);
            }

            this->keyrelease_callback_engines[keycode] = callback_engine;
        }

        void InputMode::set_continuous_keypress_callback_engine(uint32_t keycode, yli::callback::CallbackEngine* callback_engine)
        {
            if (keycode >= this->continuous_keypress_callback_engines.size())
            {
                this->continuous_keypress_callback_engines.resize(keycode + 1, nullptr);
            }

            this->continuous_keypress_callback_engines[keycode] = callback_engine;
        }

        const std::vector<yli::callback::CallbackEngine*>* InputMode::get_keypress_callback_engines() const
        {
            return &this->keypress_callback_engines;
        }

        const std::vector<yli::callback::CallbackEngine*>* InputMode::get_keyrelease_callback_engines() const
        {
            return &this->keyrelease_callback_engines;
        }

        const std::vector<yli::callback::CallbackEngine*>* InputMode::get_continuous_keypress_callback_engines() const
        {
            return &this->continuous_keypress_callback_engines;
        }
    }
}
