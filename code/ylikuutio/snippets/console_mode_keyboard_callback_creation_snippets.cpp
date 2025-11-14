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

    void create_console_mode_keypress_callbacks(GenericEntityFactory& entity_factory)
    {
        {
            // Callback code for `SDL_SCANCODE_GRAVE` (tilde key above Tab, usually used for console).
            ConsoleCallbackEngineStruct my_exit_console_callback_engine_struct { Request<Console>("my_console") };
            my_exit_console_callback_engine_struct.global_name = "my_exit_console_callback_engine";
            auto my_exit_console_callback_engine = entity_factory.create_console_callback_engine(my_exit_console_callback_engine_struct);
            my_exit_console_callback_engine->create_console_callback_object(&ConsoleLogicModule::exit_console);
        }
        {
            // Callback code for left Control press.
            ConsoleCallbackEngineStruct my_press_left_control_in_console_callback_engine_struct { Request<Console>("my_console") };
            my_press_left_control_in_console_callback_engine_struct.global_name = "my_press_left_control_in_console_callback_engine";
            auto my_press_left_control_in_console_callback_engine = entity_factory.create_console_callback_engine(my_press_left_control_in_console_callback_engine_struct);
            my_press_left_control_in_console_callback_engine->create_console_callback_object(&ConsoleLogicModule::press_left_control_in_console);
        }
        {
            // Callback code for right Control press.
            ConsoleCallbackEngineStruct my_press_right_control_in_console_callback_engine_struct { Request<Console>("my_console") };
            my_press_right_control_in_console_callback_engine_struct.global_name = "my_press_right_control_in_console_callback_engine";
            auto my_press_right_control_in_console_callback_engine = entity_factory.create_console_callback_engine(my_press_right_control_in_console_callback_engine_struct);
            my_press_right_control_in_console_callback_engine->create_console_callback_object(&ConsoleLogicModule::press_right_control_in_console);
        }
        {
            // Callback code for left Alt press.
            ConsoleCallbackEngineStruct my_press_left_alt_in_console_callback_engine_struct { Request<Console>("my_console") };
            my_press_left_alt_in_console_callback_engine_struct.global_name = "my_press_left_alt_in_console_callback_engine";
            auto my_press_left_alt_in_console_callback_engine = entity_factory.create_console_callback_engine(my_press_left_alt_in_console_callback_engine_struct);
            my_press_left_alt_in_console_callback_engine->create_console_callback_object(&ConsoleLogicModule::press_left_alt_in_console);
        }
        {
            // Callback code for right Alt press.
            ConsoleCallbackEngineStruct my_press_right_alt_in_console_callback_engine_struct { Request<Console>("my_console") };
            my_press_right_alt_in_console_callback_engine_struct.global_name = "my_press_right_alt_in_console_callback_engine";
            auto my_press_right_alt_in_console_callback_engine = entity_factory.create_console_callback_engine(my_press_right_alt_in_console_callback_engine_struct);
            my_press_right_alt_in_console_callback_engine->create_console_callback_object(&ConsoleLogicModule::press_right_alt_in_console);
        }
        {
            // Callback code for left Shift press.
            ConsoleCallbackEngineStruct my_press_left_shift_in_console_callback_engine_struct { Request<Console>("my_console") };
            my_press_left_shift_in_console_callback_engine_struct.global_name = "my_press_left_shift_in_console_callback_engine";
            auto my_press_left_shift_in_console_callback_engine = entity_factory.create_console_callback_engine(my_press_left_shift_in_console_callback_engine_struct);
            my_press_left_shift_in_console_callback_engine->create_console_callback_object(&ConsoleLogicModule::press_left_shift_in_console);
        }
        {
            // Callback code for right Shift press.
            ConsoleCallbackEngineStruct my_press_right_shift_in_console_callback_engine_struct { Request<Console>("my_console") };
            my_press_right_shift_in_console_callback_engine_struct.global_name = "my_press_right_shift_in_console_callback_engine";
            auto my_press_right_shift_in_console_callback_engine = entity_factory.create_console_callback_engine(my_press_right_shift_in_console_callback_engine_struct);
            my_press_right_shift_in_console_callback_engine->create_console_callback_object(&ConsoleLogicModule::press_right_shift_in_console);
        }
        {
            // Callback code for key up: move to previous input.
            ConsoleCallbackEngineStruct my_move_to_previous_input_callback_engine_struct { Request<Console>("my_console") };
            my_move_to_previous_input_callback_engine_struct.global_name = "my_move_to_previous_input_callback_engine";
            auto my_move_to_previous_input_callback_engine = entity_factory.create_console_callback_engine(my_move_to_previous_input_callback_engine_struct);
            my_move_to_previous_input_callback_engine->create_console_callback_object(&ConsoleLogicModule::move_to_previous_input);
        }
        {
            // Callback code for key down: move to next input.
            ConsoleCallbackEngineStruct my_move_to_next_input_callback_engine_struct { Request<Console>("my_console") };
            my_move_to_next_input_callback_engine_struct.global_name = "my_move_to_next_input_callback_engine";
            auto my_move_to_next_input_callback_engine = entity_factory.create_console_callback_engine(my_move_to_next_input_callback_engine_struct);
            my_move_to_next_input_callback_engine->create_console_callback_object(&ConsoleLogicModule::move_to_next_input);
        }
        {
            // Callback code for backspace: delete character left of cursor from current input in console.
            ConsoleCallbackEngineStruct my_backspace_callback_engine_struct { Request<Console>("my_console") };
            my_backspace_callback_engine_struct.global_name = "my_backspace_callback_engine";
            auto my_backspace_callback_engine = entity_factory.create_console_callback_engine(my_backspace_callback_engine_struct);
            my_backspace_callback_engine->create_console_callback_object(&ConsoleLogicModule::backspace);
        }
        {
            // Callback code for Tab.
            ConsoleCallbackEngineStruct my_tab_callback_engine_struct { Request<Console>("my_console") };
            my_tab_callback_engine_struct.global_name = "my_tab_callback_engine";
            auto my_tab_callback_engine = entity_factory.create_console_callback_engine(my_tab_callback_engine_struct);
            my_tab_callback_engine->create_console_callback_object(&ConsoleLogicModule::tab);
        }
        {
            // Callback code for Enter key.
            ConsoleCallbackEngineStruct my_enter_callback_engine_struct { Request<Console>("my_console") };
            my_enter_callback_engine_struct.global_name = "my_enter_callback_engine";
            auto my_enter_callback_engine = entity_factory.create_console_callback_engine(my_enter_callback_engine_struct);
            my_enter_callback_engine->create_console_callback_object(&ConsoleLogicModule::enter_key);
        }
        {
            // Callback code for C: Control-C.
            ConsoleCallbackEngineStruct my_ctrl_c_callback_engine_struct { Request<Console>("my_console") };
            my_ctrl_c_callback_engine_struct.global_name = "my_ctrl_c_callback_engine";
            auto my_ctrl_c_callback_engine = entity_factory.create_console_callback_engine(my_ctrl_c_callback_engine_struct);
            my_ctrl_c_callback_engine->create_console_callback_object(&ConsoleLogicModule::ctrl_c);
        }
        {
            // Callback code for W: Control-W.
            ConsoleCallbackEngineStruct my_ctrl_w_callback_engine_struct { Request<Console>("my_console") };
            my_ctrl_w_callback_engine_struct.global_name = "my_ctrl_w_callback_engine";
            auto my_ctrl_w_callback_engine = entity_factory.create_console_callback_engine(my_ctrl_w_callback_engine_struct);
            my_ctrl_w_callback_engine->create_console_callback_object(&ConsoleLogicModule::ctrl_w);
        }
        {
            // Callback code for PgUp.
            ConsoleCallbackEngineStruct my_page_up_callback_engine_struct { Request<Console>("my_console") };
            my_page_up_callback_engine_struct.global_name = "my_page_up_callback_engine";
            auto my_page_up_callback_engine = entity_factory.create_console_callback_engine(my_page_up_callback_engine_struct);
            my_page_up_callback_engine->create_console_callback_object(&ConsoleLogicModule::page_up);
        }
        {
            // Callback code for PgDn.
            ConsoleCallbackEngineStruct my_page_down_callback_engine_struct { Request<Console>("my_console") };
            my_page_down_callback_engine_struct.global_name = "my_page_down_callback_engine";
            auto my_page_down_callback_engine = entity_factory.create_console_callback_engine(my_page_down_callback_engine_struct);
            my_page_down_callback_engine->create_console_callback_object(&ConsoleLogicModule::page_down);
        }
        {
            // Callback code for Home.
            ConsoleCallbackEngineStruct my_home_callback_engine_struct { Request<Console>("my_console") };
            my_home_callback_engine_struct.global_name = "my_home_callback_engine";
            auto my_home_callback_engine = entity_factory.create_console_callback_engine(my_home_callback_engine_struct);
            my_home_callback_engine->create_console_callback_object(&ConsoleLogicModule::home);
        }
        {
            // Callback code for End.
            ConsoleCallbackEngineStruct my_end_callback_engine_struct { Request<Console>("my_console") };
            my_end_callback_engine_struct.global_name = "my_end_callback_engine";
            auto my_end_callback_engine = entity_factory.create_console_callback_engine(my_end_callback_engine_struct);
            my_end_callback_engine->create_console_callback_object(&ConsoleLogicModule::end);
        }
    }

    void create_console_mode_keyrelease_callbacks(GenericEntityFactory& entity_factory)
    {
        {
            // Callback code for left Control release.
            ConsoleCallbackEngineStruct my_release_left_control_in_console_callback_engine_struct { Request<Console>("my_console") };
            my_release_left_control_in_console_callback_engine_struct.global_name = "my_release_left_control_in_console_callback_engine";
            auto my_release_left_control_in_console_callback_engine = entity_factory.create_console_callback_engine(my_release_left_control_in_console_callback_engine_struct);
            my_release_left_control_in_console_callback_engine->create_console_callback_object(&ConsoleLogicModule::release_left_control_in_console);
        }
        {
            // Callback code for right Control release.
            ConsoleCallbackEngineStruct my_release_right_control_in_console_callback_engine_struct { Request<Console>("my_console") };
            my_release_right_control_in_console_callback_engine_struct.global_name = "my_release_right_control_in_console_callback_engine";
            auto my_release_right_control_in_console_callback_engine = entity_factory.create_console_callback_engine(my_release_right_control_in_console_callback_engine_struct);
            my_release_right_control_in_console_callback_engine->create_console_callback_object(&ConsoleLogicModule::release_right_control_in_console);
        }
        {
            // Callback code for left Alt release.
            ConsoleCallbackEngineStruct my_release_left_alt_in_console_callback_engine_struct { Request<Console>("my_console") };
            my_release_left_alt_in_console_callback_engine_struct.global_name = "my_release_left_alt_in_console_callback_engine";
            auto my_release_left_alt_in_console_callback_engine = entity_factory.create_console_callback_engine(my_release_left_alt_in_console_callback_engine_struct);
            my_release_left_alt_in_console_callback_engine->create_console_callback_object(&ConsoleLogicModule::release_left_alt_in_console);
        }
        {
            // Callback code for right Alt release.
            ConsoleCallbackEngineStruct my_release_right_alt_in_console_callback_engine_struct { Request<Console>("my_console") };
            my_release_right_alt_in_console_callback_engine_struct.global_name = "my_release_right_alt_in_console_callback_engine";
            auto my_release_right_alt_in_console_callback_engine = entity_factory.create_console_callback_engine(my_release_right_alt_in_console_callback_engine_struct);
            my_release_right_alt_in_console_callback_engine->create_console_callback_object(&ConsoleLogicModule::release_right_alt_in_console);
        }
        {
            // Callback code for left Shift release.
            ConsoleCallbackEngineStruct my_release_left_shift_in_console_callback_engine_struct { Request<Console>("my_console") };
            my_release_left_shift_in_console_callback_engine_struct.global_name = "my_release_left_shift_in_console_callback_engine";
            auto my_release_left_shift_in_console_callback_engine = entity_factory.create_console_callback_engine(my_release_left_shift_in_console_callback_engine_struct);
            my_release_left_shift_in_console_callback_engine->create_console_callback_object(&ConsoleLogicModule::release_left_shift_in_console);
        }
        {
            // Callback code for right Shift release.
            ConsoleCallbackEngineStruct my_release_right_shift_in_console_callback_engine_struct { Request<Console>("my_console") };
            my_release_right_shift_in_console_callback_engine_struct.global_name = "my_release_right_shift_in_console_callback_engine";
            auto my_release_right_shift_in_console_callback_engine = entity_factory.create_console_callback_engine(my_release_right_shift_in_console_callback_engine_struct);
            my_release_right_shift_in_console_callback_engine->create_console_callback_object(&ConsoleLogicModule::release_right_shift_in_console);
        }
    }

    void set_console_mode_keypress_callback_engines_or_throw(InputMode& console_mode_input_mode)
    {
        // Keypress callbacks for `my_console`.
        // Keypresses are checked in the order of this struct.
        console_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_GRAVE, Request<GenericCallbackEngine>("my_exit_console_callback_engine"));
        console_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_LCTRL, Request<GenericCallbackEngine>("my_press_left_control_in_console_callback_engine"));
        console_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_RCTRL, Request<GenericCallbackEngine>("my_press_right_control_in_console_callback_engine"));
        console_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_LALT, Request<GenericCallbackEngine>("my_press_left_alt_in_console_callback_engine"));
        console_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_RALT, Request<GenericCallbackEngine>("my_press_right_alt_in_console_callback_engine"));
        console_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_LSHIFT, Request<GenericCallbackEngine>("my_press_left_shift_in_console_callback_engine"));
        console_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_RSHIFT, Request<GenericCallbackEngine>("my_press_right_shift_in_console_callback_engine"));
        console_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_UP, Request<GenericCallbackEngine>("my_move_to_previous_input_callback_engine"));
        console_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_DOWN, Request<GenericCallbackEngine>("my_move_to_next_input_callback_engine"));
        console_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_BACKSPACE, Request<GenericCallbackEngine>("my_backspace_callback_engine"));
        console_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_TAB, Request<GenericCallbackEngine>("my_tab_callback_engine"));
        console_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_RETURN, Request<GenericCallbackEngine>("my_enter_callback_engine"));
        console_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_C, Request<GenericCallbackEngine>("my_ctrl_c_callback_engine"));
        console_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_W, Request<GenericCallbackEngine>("my_ctrl_w_callback_engine"));
        console_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_PAGEUP, Request<GenericCallbackEngine>("my_page_up_callback_engine"));
        console_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_PAGEDOWN, Request<GenericCallbackEngine>("my_page_down_callback_engine"));
        console_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_HOME, Request<GenericCallbackEngine>("my_home_callback_engine"));
        console_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_END, Request<GenericCallbackEngine>("my_end_callback_engine"));
    }

    void set_console_mode_keyrelease_callback_engines_or_throw(InputMode& console_mode_input_mode)
    {
        // Keyrelease callbacks for `my_console`.
        console_mode_input_mode.set_keyrelease_callback_engine(SDL_SCANCODE_LCTRL, Request<GenericCallbackEngine>("my_release_left_control_in_console_callback_engine"));
        console_mode_input_mode.set_keyrelease_callback_engine(SDL_SCANCODE_RCTRL, Request<GenericCallbackEngine>("my_release_right_control_in_console_callback_engine"));
        console_mode_input_mode.set_keyrelease_callback_engine(SDL_SCANCODE_LALT, Request<GenericCallbackEngine>("my_release_left_alt_in_console_callback_engine"));
        console_mode_input_mode.set_keyrelease_callback_engine(SDL_SCANCODE_RALT, Request<GenericCallbackEngine>("my_release_right_alt_in_console_callback_engine"));
        console_mode_input_mode.set_keyrelease_callback_engine(SDL_SCANCODE_LSHIFT, Request<GenericCallbackEngine>("my_release_left_shift_in_console_callback_engine"));
        console_mode_input_mode.set_keyrelease_callback_engine(SDL_SCANCODE_RSHIFT, Request<GenericCallbackEngine>("my_release_right_shift_in_console_callback_engine"));
    }
}
