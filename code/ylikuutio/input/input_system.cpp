// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2026 Antti Nuortimo.
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

#include "input_system.hpp"
#include "input.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/sdl/ylikuutio_sdl.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/generic_callback_engine.hpp"
#include "code/ylikuutio/ontology/input_mode.hpp"
#include "code/ylikuutio/ontology/callback_magic_numbers.hpp"

// Include standard headers
#include <iostream> // std::cerr
#include <vector>   // std::vector

namespace yli::input
{
    InputSystem::InputSystem(yli::ontology::Universe& universe)
        : universe { universe }
    {
    }

    void InputSystem::process_keys(const InputMethod& input_method, const yli::ontology::InputMode& input_mode)
    {
        int array_size;
        const bool* const current_key_states = SDL_GetKeyboardState(&array_size);
        const std::vector<yli::ontology::GenericCallbackEngine*>* const continuous_keypress_callback_engines = input_mode.get_continuous_keypress_callback_engines();
        if (continuous_keypress_callback_engines == nullptr)
        {
            return;
        }

        // Check for keypresses and call corresponding callbacks.
        for (std::size_t i = 0; i < continuous_keypress_callback_engines->size(); i++)
        {
            bool is_pressed = false;

            if (input_method == yli::input::InputMethod::KEYBOARD)
            {
                if (current_key_states[i]) // `true` = pressed, `false` = not pressed.
                {
                    is_pressed = true;
                }
            }
            else if (input_method == yli::input::InputMethod::INPUT_FILE)
            {
                // TODO: implement optionally loading keyreleases from a file (do not execute `SDL_GetKeyboardState` in that case).
                if (false)
                {
                    is_pressed = true;
                }
            }
            else
            {
                std::cerr << "ERROR: unsupported input method.\n";
            }

            if (is_pressed)
            {
                yli::ontology::GenericCallbackEngine* const generic_callback_engine = continuous_keypress_callback_engines->at(i);

                if (generic_callback_engine == nullptr)
                {
                    continue;
                }

                const std::optional<yli::data::AnyValue> any_value = generic_callback_engine->execute(yli::data::AnyValue());

                if (any_value &&
                        std::holds_alternative<uint32_t>(any_value->data) &&
                        std::get<uint32_t>(any_value->data) == yli::ontology::CallbackMagicNumber::EXIT_PROGRAM)
                {
                    this->universe.request_exit();
                }
            }
        }
    }

    InputSystem& InputSystem::get()
    {
        return *this;
    }
}
