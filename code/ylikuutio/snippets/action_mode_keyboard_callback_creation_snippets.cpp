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

#include "action_mode_keyboard_callback_creation_snippets.hpp"
#include "keyboard_callback_snippets.hpp"
#include "code/ylikuutio/console/console_logic_module.hpp"
#include "code/ylikuutio/ontology/callback_engine.hpp"
#include "code/ylikuutio/ontology/input_mode.hpp"
#include "code/ylikuutio/ontology/generic_entity_factory.hpp"
#include "code/ylikuutio/ontology/request.hpp"
#include "code/ylikuutio/ontology/callback_engine_struct.hpp"
#include "code/ylikuutio/sdl/ylikuutio_sdl.hpp"

namespace yli::ontology
{
    class GenericCallbackEngine;
}

namespace yli::snippets
{
    using yli::console::ConsoleLogicModule;
    using yli::ontology::GenericCallbackEngine;
    using yli::ontology::CallbackEngine;
    using yli::ontology::Request;
    using yli::ontology::CallbackEngineStruct;

    void create_action_mode_keypress_callbacks(yli::ontology::GenericEntityFactory& entity_factory)
    {
        // Callback code for `SDL_SCANCODE_GRAVE` (tilde key above Tab, usually used for console).
        CallbackEngineStruct enter_console_callback_engine_struct;
        enter_console_callback_engine_struct.global_name = "enter_console_callback_engine";
        auto enter_console_callback_engine = entity_factory.create_callback_engine(enter_console_callback_engine_struct);
        enter_console_callback_engine->create_callback_object(&ConsoleLogicModule::enter_console);

        // Callback code for esc: exit program.
        CallbackEngineStruct exit_program_callback_engine_struct;
        exit_program_callback_engine_struct.global_name = "exit_program_callback_engine";
        auto exit_program_callback_engine = entity_factory.create_callback_engine(exit_program_callback_engine_struct);
        exit_program_callback_engine->create_callback_object(&yli::snippets::exit_program);

        // Callback code for left Control: first turbo.
        CallbackEngineStruct first_turbo_callback_engine_struct;
        first_turbo_callback_engine_struct.global_name = "first_turbo_callback_engine";
        auto first_turbo_callback_engine = entity_factory.create_callback_engine(first_turbo_callback_engine_struct);
        first_turbo_callback_engine->create_callback_object(&yli::snippets::press_first_turbo);

        // Callback code for right Control: second turbo.
        CallbackEngineStruct second_turbo_callback_engine_struct;
        second_turbo_callback_engine_struct.global_name = "second_turbo_callback_engine";
        auto second_turbo_callback_engine = entity_factory.create_callback_engine(second_turbo_callback_engine_struct);
        second_turbo_callback_engine->create_callback_object(&yli::snippets::press_second_turbo);

        // Callback code for key up: move forward.
        CallbackEngineStruct move_forward_callback_engine_struct;
        move_forward_callback_engine_struct.global_name = "move_forward_callback_engine";
        auto move_forward_callback_engine = entity_factory.create_callback_engine(move_forward_callback_engine_struct);
        move_forward_callback_engine->create_callback_object(&yli::snippets::move_forward);

        // Callback code for key down: move backward.
        CallbackEngineStruct move_backward_callback_engine_struct;
        move_backward_callback_engine_struct.global_name = "move_backward_callback_engine";
        auto move_backward_callback_engine = entity_factory.create_callback_engine(move_backward_callback_engine_struct);
        move_backward_callback_engine->create_callback_object(&yli::snippets::move_backward);

        // Callback code for key left: strafe left.
        CallbackEngineStruct strafe_left_callback_engine_struct;
        strafe_left_callback_engine_struct.global_name = "strafe_left_callback_engine";
        auto strafe_left_callback_engine = entity_factory.create_callback_engine(strafe_left_callback_engine_struct);
        strafe_left_callback_engine->create_callback_object(&yli::snippets::strafe_left);

        // Callback code for key right: strafe right.
        CallbackEngineStruct strafe_right_callback_engine_struct;
        strafe_right_callback_engine_struct.global_name = "strafe_right_callback_engine";
        auto strafe_right_callback_engine = entity_factory.create_callback_engine(strafe_right_callback_engine_struct);
        strafe_right_callback_engine->create_callback_object(&yli::snippets::strafe_right);

        // Callback code for space: ascent.
        CallbackEngineStruct ascent_callback_engine_struct;
        ascent_callback_engine_struct.global_name = "ascent_callback_engine";
        auto ascent_callback_engine = entity_factory.create_callback_engine(ascent_callback_engine_struct);
        ascent_callback_engine->create_callback_object(&yli::snippets::ascent);

        // Callback code for enter: descent.
        CallbackEngineStruct descent_callback_engine_struct;
        descent_callback_engine_struct.global_name = "descent_callback_engine";
        auto descent_callback_engine = entity_factory.create_callback_engine(descent_callback_engine_struct);
        descent_callback_engine->create_callback_object(&yli::snippets::descent);

        // Callback code for I: toggle invert mouse.
        CallbackEngineStruct toggle_invert_mouse_callback_engine_struct;
        toggle_invert_mouse_callback_engine_struct.global_name = "toggle_invert_mouse_callback_engine";
        auto toggle_invert_mouse_callback_engine = entity_factory.create_callback_engine(toggle_invert_mouse_callback_engine_struct);
        toggle_invert_mouse_callback_engine->create_callback_object(&yli::snippets::toggle_invert_mouse);

        // Callback code for F: toggle flight mode.
        CallbackEngineStruct toggle_flight_mode_callback_engine_struct;
        toggle_flight_mode_callback_engine_struct.global_name = "toggle_flight_mode_callback_engine";
        auto toggle_flight_mode_callback_engine = entity_factory.create_callback_engine(toggle_flight_mode_callback_engine_struct);
        toggle_flight_mode_callback_engine->create_callback_object(&yli::snippets::toggle_flight_mode);

        // Callback code for F1: toggle help mode.
        CallbackEngineStruct toggle_help_mode_callback_engine_struct;
        toggle_help_mode_callback_engine_struct.global_name = "toggle_help_mode_callback_engine";
        auto toggle_help_mode_callback_engine = entity_factory.create_callback_engine(toggle_help_mode_callback_engine_struct);
        toggle_help_mode_callback_engine->create_callback_object(&yli::snippets::toggle_help_mode);
    }

    void create_action_mode_keyrelease_callbacks(yli::ontology::GenericEntityFactory& entity_factory)
    {
        // Callback code for left Control release: release first turbo.
        CallbackEngineStruct release_first_turbo_callback_engine_struct;
        release_first_turbo_callback_engine_struct.global_name = "release_first_turbo_callback_engine";
        auto release_first_turbo_callback_engine = entity_factory.create_callback_engine(release_first_turbo_callback_engine_struct);
        release_first_turbo_callback_engine->create_callback_object(&yli::snippets::release_first_turbo);

        // Callback code for right Control release: release second turbo.
        CallbackEngineStruct release_second_turbo_callback_engine_struct;
        release_second_turbo_callback_engine_struct.global_name = "release_second_turbo_callback_engine";
        auto release_second_turbo_callback_engine = entity_factory.create_callback_engine(release_second_turbo_callback_engine_struct);
        release_second_turbo_callback_engine->create_callback_object(&yli::snippets::release_second_turbo);

        // Callback code for I release: enable_toggle invert mouse.
        CallbackEngineStruct enable_toggle_invert_mouse_callback_engine_struct;
        enable_toggle_invert_mouse_callback_engine_struct.global_name = "enable_toggle_invert_mouse_callback_engine";
        auto enable_toggle_invert_mouse_callback_engine = entity_factory.create_callback_engine(enable_toggle_invert_mouse_callback_engine_struct);
        enable_toggle_invert_mouse_callback_engine->create_callback_object(&yli::snippets::enable_toggle_invert_mouse);

        // Callback code for F release: enable_toggle flight mode.
        CallbackEngineStruct enable_toggle_flight_mode_callback_engine_struct;
        enable_toggle_flight_mode_callback_engine_struct.global_name = "enable_toggle_flight_mode_callback_engine";
        auto enable_toggle_flight_mode_callback_engine = entity_factory.create_callback_engine(enable_toggle_flight_mode_callback_engine_struct);
        enable_toggle_flight_mode_callback_engine->create_callback_object(&yli::snippets::enable_toggle_flight_mode);

        // Callback code for F1 release: enable toggle help mode.
        CallbackEngineStruct enable_toggle_help_mode_callback_engine_struct;
        enable_toggle_help_mode_callback_engine_struct.global_name = "enable_toggle_help_mode_callback_engine";
        auto enable_toggle_help_mode_callback_engine = entity_factory.create_callback_engine(enable_toggle_help_mode_callback_engine_struct);
        enable_toggle_help_mode_callback_engine->create_callback_object(&yli::snippets::enable_toggle_help_mode);
    }

    void set_action_mode_keypress_callback_engines_or_throw(yli::ontology::InputMode& action_mode_input_mode)
    {
        // Keypress callbacks for action mode.
        action_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_GRAVE, Request<GenericCallbackEngine>("enter_console_callback_engine"));
        action_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_ESCAPE, Request<GenericCallbackEngine>("exit_program_callback_engine"));
        action_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_LCTRL, Request<GenericCallbackEngine>("first_turbo_callback_engine"));
        action_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_RCTRL, Request<GenericCallbackEngine>("second_turbo_callback_engine"));
        action_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_I, Request<GenericCallbackEngine>("toggle_invert_mouse_callback_engine"));
        action_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_F, Request<GenericCallbackEngine>("toggle_flight_mode_callback_engine"));
        action_mode_input_mode.set_keypress_callback_engine(SDL_SCANCODE_F1, Request<GenericCallbackEngine>("toggle_help_mode_callback_engine"));
    }

    void set_action_mode_keyrelease_callback_engines_or_throw(yli::ontology::InputMode& action_mode_input_mode)
    {
        // Keyrelease callbacks for action mode.
        action_mode_input_mode.set_keyrelease_callback_engine(SDL_SCANCODE_LCTRL, Request<GenericCallbackEngine>("release_first_turbo_callback_engine"));
        action_mode_input_mode.set_keyrelease_callback_engine(SDL_SCANCODE_RCTRL, Request<GenericCallbackEngine>("release_second_turbo_callback_engine"));
        action_mode_input_mode.set_keyrelease_callback_engine(SDL_SCANCODE_I, Request<GenericCallbackEngine>("enable_toggle_invert_mouse_callback_engine"));
        action_mode_input_mode.set_keyrelease_callback_engine(SDL_SCANCODE_F, Request<GenericCallbackEngine>("enable_toggle_flight_mode_callback_engine"));
        action_mode_input_mode.set_keyrelease_callback_engine(SDL_SCANCODE_F1, Request<GenericCallbackEngine>("enable_toggle_help_mode_callback_engine"));
    }

    void set_action_mode_continuous_keypress_callback_engines_or_throw(yli::ontology::InputMode& action_mode_input_mode)
    {
        // Continuous keypress callbacks for action mode.
        action_mode_input_mode.set_continuous_keypress_callback_engine(SDL_SCANCODE_UP, Request<GenericCallbackEngine>("move_forward_callback_engine"));
        action_mode_input_mode.set_continuous_keypress_callback_engine(SDL_SCANCODE_DOWN, Request<GenericCallbackEngine>("move_backward_callback_engine"));
        action_mode_input_mode.set_continuous_keypress_callback_engine(SDL_SCANCODE_LEFT, Request<GenericCallbackEngine>("strafe_left_callback_engine"));
        action_mode_input_mode.set_continuous_keypress_callback_engine(SDL_SCANCODE_RIGHT, Request<GenericCallbackEngine>("strafe_right_callback_engine"));
        action_mode_input_mode.set_continuous_keypress_callback_engine(SDL_SCANCODE_SPACE, Request<GenericCallbackEngine>("ascent_callback_engine"));
        action_mode_input_mode.set_continuous_keypress_callback_engine(SDL_SCANCODE_RETURN, Request<GenericCallbackEngine>("descent_callback_engine"));
    }
}
