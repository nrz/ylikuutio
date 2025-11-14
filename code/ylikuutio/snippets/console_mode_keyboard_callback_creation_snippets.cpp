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

#include "console_mode_keyboard_callback_creation_snippets.hpp"
#include "code/ylikuutio/console/console_logic_module.hpp"
#include "code/ylikuutio/ontology/input_mode.hpp"
#include "code/ylikuutio/ontology/console_callback_engine.hpp"
#include "code/ylikuutio/ontology/generic_entity_factory.hpp"
#include "code/ylikuutio/ontology/request.hpp"
#include "code/ylikuutio/ontology/console_callback_engine_struct.hpp"
#include "code/ylikuutio/sdl/ylikuutio_sdl.hpp"

// Include standard headers
#include <string> // std::string

namespace yli::ontology
{
    class GenericCallbackEngine;
}

namespace yli::snippets
{
    using yli::console::ConsoleLogicModule;
    using yli::ontology::InputMode;
    using yli::ontology::Console;
    using yli::ontology::ConsoleCallbackEngineStruct;
    using yli::ontology::GenericCallbackEngine;
    using yli::ontology::Request;
    using yli::ontology::GenericEntityFactory;

    void create_console_mode_keypress_callbacks(GenericEntityFactory& entity_factory, const std::string& console_global_name)
    {
        {
            // Callback code for `SDL_SCANCODE_GRAVE` (tilde key above Tab, usually used for console).
            ConsoleCallbackEngineStruct exit_console_callback_engine_struct { Request<Console>(console_global_name) };
            exit_console_callback_engine_struct.global_name = console_global_name + "_exit_console";
            auto exit_console_callback_engine = entity_factory.create_console_callback_engine(exit_console_callback_engine_struct);
            exit_console_callback_engine->create_console_callback_object(&ConsoleLogicModule::exit_console);
        }
        {
            // Callback code for left Control press.
            ConsoleCallbackEngineStruct press_left_control_in_console_callback_engine_struct { Request<Console>(console_global_name) };
            press_left_control_in_console_callback_engine_struct.global_name = console_global_name + "_press_left_control";
            auto press_left_control_in_console_callback_engine = entity_factory.create_console_callback_engine(press_left_control_in_console_callback_engine_struct);
            press_left_control_in_console_callback_engine->create_console_callback_object(&ConsoleLogicModule::press_left_control_in_console);
        }
        {
            // Callback code for right Control press.
            ConsoleCallbackEngineStruct press_right_control_in_console_callback_engine_struct { Request<Console>(console_global_name) };
            press_right_control_in_console_callback_engine_struct.global_name = console_global_name + "_press_right_control";
            auto press_right_control_in_console_callback_engine = entity_factory.create_console_callback_engine(press_right_control_in_console_callback_engine_struct);
            press_right_control_in_console_callback_engine->create_console_callback_object(&ConsoleLogicModule::press_right_control_in_console);
        }
        {
            // Callback code for left Alt press.
            ConsoleCallbackEngineStruct press_left_alt_in_console_callback_engine_struct { Request<Console>(console_global_name) };
            press_left_alt_in_console_callback_engine_struct.global_name = console_global_name + "_press_left_alt";
            auto press_left_alt_in_console_callback_engine = entity_factory.create_console_callback_engine(press_left_alt_in_console_callback_engine_struct);
            press_left_alt_in_console_callback_engine->create_console_callback_object(&ConsoleLogicModule::press_left_alt_in_console);
        }
        {
            // Callback code for right Alt press.
            ConsoleCallbackEngineStruct press_right_alt_in_console_callback_engine_struct { Request<Console>(console_global_name) };
            press_right_alt_in_console_callback_engine_struct.global_name = console_global_name + "_press_right_alt";
            auto press_right_alt_in_console_callback_engine = entity_factory.create_console_callback_engine(press_right_alt_in_console_callback_engine_struct);
            press_right_alt_in_console_callback_engine->create_console_callback_object(&ConsoleLogicModule::press_right_alt_in_console);
        }
        {
            // Callback code for left Shift press.
            ConsoleCallbackEngineStruct press_left_shift_in_console_callback_engine_struct { Request<Console>(console_global_name) };
            press_left_shift_in_console_callback_engine_struct.global_name = console_global_name + "_press_left_shift";
            auto press_left_shift_in_console_callback_engine = entity_factory.create_console_callback_engine(press_left_shift_in_console_callback_engine_struct);
            press_left_shift_in_console_callback_engine->create_console_callback_object(&ConsoleLogicModule::press_left_shift_in_console);
        }
        {
            // Callback code for right Shift press.
            ConsoleCallbackEngineStruct press_right_shift_in_console_callback_engine_struct { Request<Console>(console_global_name) };
            press_right_shift_in_console_callback_engine_struct.global_name = console_global_name + "_press_right_shift";
            auto press_right_shift_in_console_callback_engine = entity_factory.create_console_callback_engine(press_right_shift_in_console_callback_engine_struct);
            press_right_shift_in_console_callback_engine->create_console_callback_object(&ConsoleLogicModule::press_right_shift_in_console);
        }
        {
            // Callback code for key up: move to previous input.
            ConsoleCallbackEngineStruct move_to_previous_input_callback_engine_struct { Request<Console>(console_global_name) };
            move_to_previous_input_callback_engine_struct.global_name = console_global_name + "_move_to_previous_input";
            auto move_to_previous_input_callback_engine = entity_factory.create_console_callback_engine(move_to_previous_input_callback_engine_struct);
            move_to_previous_input_callback_engine->create_console_callback_object(&ConsoleLogicModule::move_to_previous_input);
        }
        {
            // Callback code for key down: move to next input.
            ConsoleCallbackEngineStruct move_to_next_input_callback_engine_struct { Request<Console>(console_global_name) };
            move_to_next_input_callback_engine_struct.global_name = console_global_name + "_move_to_next_input";
            auto move_to_next_input_callback_engine = entity_factory.create_console_callback_engine(move_to_next_input_callback_engine_struct);
            move_to_next_input_callback_engine->create_console_callback_object(&ConsoleLogicModule::move_to_next_input);
        }
        {
            // Callback code for backspace: delete character left of cursor from current input in console.
            ConsoleCallbackEngineStruct backspace_callback_engine_struct { Request<Console>(console_global_name) };
            backspace_callback_engine_struct.global_name = console_global_name + "_backspace";
            auto backspace_callback_engine = entity_factory.create_console_callback_engine(backspace_callback_engine_struct);
            backspace_callback_engine->create_console_callback_object(&ConsoleLogicModule::backspace);
        }
        {
            // Callback code for Tab.
            ConsoleCallbackEngineStruct tab_callback_engine_struct { Request<Console>(console_global_name) };
            tab_callback_engine_struct.global_name = console_global_name + "_tab";
            auto tab_callback_engine = entity_factory.create_console_callback_engine(tab_callback_engine_struct);
            tab_callback_engine->create_console_callback_object(&ConsoleLogicModule::tab);
        }
        {
            // Callback code for Enter key.
            ConsoleCallbackEngineStruct enter_callback_engine_struct { Request<Console>(console_global_name) };
            enter_callback_engine_struct.global_name = console_global_name + "_enter";
            auto enter_callback_engine = entity_factory.create_console_callback_engine(enter_callback_engine_struct);
            enter_callback_engine->create_console_callback_object(&ConsoleLogicModule::enter_key);
        }
        {
            // Callback code for C: Control-C.
            ConsoleCallbackEngineStruct ctrl_c_callback_engine_struct { Request<Console>(console_global_name) };
            ctrl_c_callback_engine_struct.global_name = console_global_name + "_ctrl_c";
            auto ctrl_c_callback_engine = entity_factory.create_console_callback_engine(ctrl_c_callback_engine_struct);
            ctrl_c_callback_engine->create_console_callback_object(&ConsoleLogicModule::ctrl_c);
        }
        {
            // Callback code for W: Control-W.
            ConsoleCallbackEngineStruct ctrl_w_callback_engine_struct { Request<Console>(console_global_name) };
            ctrl_w_callback_engine_struct.global_name = console_global_name + "_ctrl_w";
            auto ctrl_w_callback_engine = entity_factory.create_console_callback_engine(ctrl_w_callback_engine_struct);
            ctrl_w_callback_engine->create_console_callback_object(&ConsoleLogicModule::ctrl_w);
        }
        {
            // Callback code for PgUp.
            ConsoleCallbackEngineStruct page_up_callback_engine_struct { Request<Console>(console_global_name) };
            page_up_callback_engine_struct.global_name = console_global_name + "_page_up";
            auto page_up_callback_engine = entity_factory.create_console_callback_engine(page_up_callback_engine_struct);
            page_up_callback_engine->create_console_callback_object(&ConsoleLogicModule::page_up);
        }
        {
            // Callback code for PgDn.
            ConsoleCallbackEngineStruct page_down_callback_engine_struct { Request<Console>(console_global_name) };
            page_down_callback_engine_struct.global_name = console_global_name + "_page_down";
            auto page_down_callback_engine = entity_factory.create_console_callback_engine(page_down_callback_engine_struct);
            page_down_callback_engine->create_console_callback_object(&ConsoleLogicModule::page_down);
        }
        {
            // Callback code for Home.
            ConsoleCallbackEngineStruct home_callback_engine_struct { Request<Console>(console_global_name) };
            home_callback_engine_struct.global_name = console_global_name + "_home";
            auto home_callback_engine = entity_factory.create_console_callback_engine(home_callback_engine_struct);
            home_callback_engine->create_console_callback_object(&ConsoleLogicModule::home);
        }
        {
            // Callback code for End.
            ConsoleCallbackEngineStruct end_callback_engine_struct { Request<Console>(console_global_name) };
            end_callback_engine_struct.global_name = console_global_name + "_end";
            auto end_callback_engine = entity_factory.create_console_callback_engine(end_callback_engine_struct);
            end_callback_engine->create_console_callback_object(&ConsoleLogicModule::end);
        }
    }

    void create_console_mode_keyrelease_callbacks(GenericEntityFactory& entity_factory, const std::string& console_global_name)
    {
        {
            // Callback code for left Control release.
            ConsoleCallbackEngineStruct release_left_control_in_console_callback_engine_struct { Request<Console>(console_global_name) };
            release_left_control_in_console_callback_engine_struct.global_name = console_global_name + "_release_left_control";
            auto release_left_control_in_console_callback_engine = entity_factory.create_console_callback_engine(release_left_control_in_console_callback_engine_struct);
            release_left_control_in_console_callback_engine->create_console_callback_object(&ConsoleLogicModule::release_left_control_in_console);
        }
        {
            // Callback code for right Control release.
            ConsoleCallbackEngineStruct release_right_control_in_console_callback_engine_struct { Request<Console>(console_global_name) };
            release_right_control_in_console_callback_engine_struct.global_name = console_global_name + "_release_right_control";
            auto release_right_control_in_console_callback_engine = entity_factory.create_console_callback_engine(release_right_control_in_console_callback_engine_struct);
            release_right_control_in_console_callback_engine->create_console_callback_object(&ConsoleLogicModule::release_right_control_in_console);
        }
        {
            // Callback code for left Alt release.
            ConsoleCallbackEngineStruct release_left_alt_in_console_callback_engine_struct { Request<Console>(console_global_name) };
            release_left_alt_in_console_callback_engine_struct.global_name = console_global_name + "_release_left_alt";
            auto release_left_alt_in_console_callback_engine = entity_factory.create_console_callback_engine(release_left_alt_in_console_callback_engine_struct);
            release_left_alt_in_console_callback_engine->create_console_callback_object(&ConsoleLogicModule::release_left_alt_in_console);
        }
        {
            // Callback code for right Alt release.
            ConsoleCallbackEngineStruct release_right_alt_in_console_callback_engine_struct { Request<Console>(console_global_name) };
            release_right_alt_in_console_callback_engine_struct.global_name = console_global_name + "_release_right_alt";
            auto release_right_alt_in_console_callback_engine = entity_factory.create_console_callback_engine(release_right_alt_in_console_callback_engine_struct);
            release_right_alt_in_console_callback_engine->create_console_callback_object(&ConsoleLogicModule::release_right_alt_in_console);
        }
        {
            // Callback code for left Shift release.
            ConsoleCallbackEngineStruct release_left_shift_in_console_callback_engine_struct { Request<Console>(console_global_name) };
            release_left_shift_in_console_callback_engine_struct.global_name = console_global_name + "_release_left_shift";
            auto release_left_shift_in_console_callback_engine = entity_factory.create_console_callback_engine(release_left_shift_in_console_callback_engine_struct);
            release_left_shift_in_console_callback_engine->create_console_callback_object(&ConsoleLogicModule::release_left_shift_in_console);
        }
        {
            // Callback code for right Shift release.
            ConsoleCallbackEngineStruct release_right_shift_in_console_callback_engine_struct { Request<Console>(console_global_name) };
            release_right_shift_in_console_callback_engine_struct.global_name = console_global_name + "_release_right_shift";
            auto release_right_shift_in_console_callback_engine = entity_factory.create_console_callback_engine(release_right_shift_in_console_callback_engine_struct);
            release_right_shift_in_console_callback_engine->create_console_callback_object(&ConsoleLogicModule::release_right_shift_in_console);
        }
    }

    void set_console_mode_keypress_callback_engines_or_throw(InputMode& console_mode_input_mode, const std::string& console_global_name)
    {
        // Keypress callbacks for `Console`.
        // Keypresses are checked in the order of this struct.
        console_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_GRAVE, Request<GenericCallbackEngine>(console_global_name + "_exit_console"));
        console_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_LCTRL, Request<GenericCallbackEngine>(console_global_name + "_press_left_control"));
        console_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_RCTRL, Request<GenericCallbackEngine>(console_global_name + "_press_right_control"));
        console_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_LALT, Request<GenericCallbackEngine>(console_global_name + "_press_left_alt"));
        console_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_RALT, Request<GenericCallbackEngine>(console_global_name + "_press_right_alt"));
        console_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_LSHIFT, Request<GenericCallbackEngine>(console_global_name + "_press_left_shift"));
        console_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_RSHIFT, Request<GenericCallbackEngine>(console_global_name + "_press_right_shift"));
        console_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_UP, Request<GenericCallbackEngine>(console_global_name + "_move_to_previous_input"));
        console_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_DOWN, Request<GenericCallbackEngine>(console_global_name + "_move_to_next_input"));
        console_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_BACKSPACE, Request<GenericCallbackEngine>(console_global_name + "_backspace"));
        console_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_TAB, Request<GenericCallbackEngine>(console_global_name + "_tab"));
        console_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_RETURN, Request<GenericCallbackEngine>(console_global_name + "_enter"));
        console_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_C, Request<GenericCallbackEngine>(console_global_name + "_ctrl_c"));
        console_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_W, Request<GenericCallbackEngine>(console_global_name + "_ctrl_w"));
        console_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_PAGEUP, Request<GenericCallbackEngine>(console_global_name + "_page_up"));
        console_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_PAGEDOWN, Request<GenericCallbackEngine>(console_global_name + "_page_down"));
        console_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_HOME, Request<GenericCallbackEngine>(console_global_name + "_home"));
        console_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_END, Request<GenericCallbackEngine>(console_global_name + "_end"));
    }

    void set_console_mode_keyrelease_callback_engines_or_throw(InputMode& console_mode_input_mode, const std::string& console_global_name)
    {
        // Keyrelease callbacks for `Console`.
        console_mode_input_mode.set_keyrelease_callback_engine(SDL_SCANCODE_LCTRL, Request<GenericCallbackEngine>(console_global_name + "_release_left_control"));
        console_mode_input_mode.set_keyrelease_callback_engine(SDL_SCANCODE_RCTRL, Request<GenericCallbackEngine>(console_global_name + "_release_right_control"));
        console_mode_input_mode.set_keyrelease_callback_engine(SDL_SCANCODE_LALT, Request<GenericCallbackEngine>(console_global_name + "_release_left_alt"));
        console_mode_input_mode.set_keyrelease_callback_engine(SDL_SCANCODE_RALT, Request<GenericCallbackEngine>(console_global_name + "_release_right_alt"));
        console_mode_input_mode.set_keyrelease_callback_engine(SDL_SCANCODE_LSHIFT, Request<GenericCallbackEngine>(console_global_name + "_release_left_shift"));
        console_mode_input_mode.set_keyrelease_callback_engine(SDL_SCANCODE_RSHIFT, Request<GenericCallbackEngine>(console_global_name + "_release_right_shift"));
    }
}
