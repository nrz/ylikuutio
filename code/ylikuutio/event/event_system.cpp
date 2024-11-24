// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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

#include "event_system.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/generic_callback_engine.hpp"
#include "code/ylikuutio/ontology/input_mode.hpp"
#include "code/ylikuutio/ontology/console.hpp"
#include "code/ylikuutio/ontology/callback_magic_numbers.hpp"
#include "code/ylikuutio/sdl/ylikuutio_sdl.hpp"

// Include standard headers
#include <stdint.h> // uint32_t etc.

namespace yli::event
{
    EventSystem::EventSystem(yli::ontology::Universe& universe)
        : universe { universe }
    {
    }

    void EventSystem::poll_events(const yli::ontology::InputMode& input_mode)
    {
        SDL_Event sdl_event;

        while (SDL_PollEvent(&sdl_event))
        {
            if (sdl_event.type == SDL_MOUSEMOTION)
            {
                this->universe.update_mouse_x(sdl_event.motion.xrel);
                this->universe.update_mouse_y(sdl_event.motion.yrel);
            }
            else if (sdl_event.type == SDL_KEYDOWN)
            {
                const uint32_t scancode = static_cast<std::uint32_t>(sdl_event.key.keysym.scancode);

                yli::ontology::GenericCallbackEngine* const generic_callback_engine = input_mode.get_keypress_callback_engine(scancode);

                if (generic_callback_engine != nullptr)
                {
                    const std::optional<yli::data::AnyValue> any_value = generic_callback_engine->execute(yli::data::AnyValue());

                    if (any_value &&
                            std::holds_alternative<uint32_t>(any_value->data) &&
                            std::get<uint32_t>(any_value->data) == yli::ontology::CallbackMagicNumber::EXIT_PROGRAM)
                    {
                        this->universe.request_exit();
                    }
                }

                yli::ontology::Console* const active_console = this->universe.get_active_console();

                if (active_console != nullptr)
                {
                    active_console->process_key_event(sdl_event.key);
                }
            }
            else if (sdl_event.type == SDL_KEYUP)
            {
                const uint32_t scancode = static_cast<std::uint32_t>(sdl_event.key.keysym.scancode);

                yli::ontology::GenericCallbackEngine* const generic_callback_engine = input_mode.get_keyrelease_callback_engine(scancode);

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
            else if (sdl_event.type == SDL_WINDOWEVENT)
            {
                if (sdl_event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
                {
                    this->universe.gain_focus();
                }
                else if (sdl_event.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
                {
                    this->universe.lose_focus();
                }
            }
            else if (sdl_event.type == SDL_QUIT)
            {
                this->universe.request_exit();
            }
        }
    }

    EventSystem& EventSystem::get()
    {
        return *this;
    }
}
