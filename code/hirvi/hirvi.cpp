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

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif

#include "hirvi.hpp"
#include "lisp/hirvi_console_callbacks.hpp"
#include "data/datatype.hpp"
#include "code/ylikuutio/audio/audio_system.hpp"
#include "code/ylikuutio/command_line/command_line_master.hpp"
#include "code/ylikuutio/core/application.hpp"
#include "code/ylikuutio/event/event_system.hpp"
#include "code/ylikuutio/input/input_system.hpp"

#ifndef GOOGLE_TEST
// Google Test provides its own `main` entrypoint.
#include "code/ylikuutio/core/entrypoint.hpp"
#endif

#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/render/graphics_api_backend.hpp"

// `yli::ontology` files included in the canonical order.
#include "code/ylikuutio/ontology/entity.hpp"
#include "code/ylikuutio/ontology/movable.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/variable.hpp"
#include "code/ylikuutio/ontology/callback_engine.hpp"
#include "code/ylikuutio/ontology/ecosystem.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/holobiont.hpp"
#include "code/ylikuutio/ontology/shapeshifter_transformation.hpp"
#include "code/ylikuutio/ontology/font_2d.hpp"
#include "code/ylikuutio/ontology/text_2d.hpp"
#include "code/ylikuutio/ontology/input_mode.hpp"
#include "code/ylikuutio/ontology/console.hpp"
#include "code/ylikuutio/ontology/console_callback_engine.hpp"
#include "code/ylikuutio/ontology/request.hpp"
#include "code/ylikuutio/ontology/universe_struct.hpp"
#include "code/ylikuutio/ontology/callback_engine_struct.hpp"
#include "code/ylikuutio/ontology/font_struct.hpp"
#include "code/ylikuutio/ontology/text_struct.hpp"
#include "code/ylikuutio/ontology/input_mode_struct.hpp"
#include "code/ylikuutio/ontology/console_struct.hpp"
#include "code/ylikuutio/ontology/console_callback_engine_struct.hpp"
#include "code/ylikuutio/opengl/vboindexer.hpp"
#include "code/ylikuutio/sdl/ylikuutio_sdl.hpp"
#include "code/ylikuutio/snippets/framebuffer_snippets.hpp"
#include "code/ylikuutio/snippets/background_color_snippets.hpp"
#include "code/ylikuutio/snippets/console_callback_snippets.hpp"
#include "code/ylikuutio/snippets/keyboard_callback_snippets.hpp"
#include "code/ylikuutio/snippets/debug_snippets.hpp"
#include "code/ylikuutio/snippets/movement_snippets.hpp"
#include "code/ylikuutio/snippets/location_and_orientation_snippets.hpp"
#include "code/ylikuutio/snippets/wireframe_snippets.hpp"
#include "code/ylikuutio/snippets/console_callback_snippets.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cerr
#include <memory>   // std::make_unique, std::unique_ptr
#include <stdexcept> // std::logic_error
#include <string>   // std::string
#include <vector>   // std::vector

namespace yli::memory
{
    class GenericMemorySystem;
    class GenericMemoryAllocator;
}

namespace yli::ontology
{
    class GenericEntityFactory;
}

namespace hirvi
{
    using namespace yli::ontology;

    HirviApplication::HirviApplication(const int argc, const char* const argv[])
        : yli::core::Application(argc, argv),
        entity_factory(*this, this->memory_system),
        system_factory(this->memory_system),
        universe { this->entity_factory.create_universe(this->get_universe_struct()) },
        event_system { this->system_factory.create_event_system(this->get_universe()) },
        input_system { this->system_factory.create_input_system(this->get_universe()) },
        audio_system { this->system_factory.create_audio_system(this->get_universe()) }
    {
        std::cout << "HirviApplication initialized!\n";
    }

    std::string HirviApplication::get_name() const
    {
        return "Hirvi";
    }

    std::vector<std::string> HirviApplication::get_valid_keys() const
    {
        return {
            "help",
                "version",
                "silent",
                "fullscreen",
                "headless",
                "window_width",
                "window_height",
                "framebuffer_width",
                "framebuffer_height",
                "speed",
                "turbo_factor",
                "twin_turbo_factor",
                "mouse_speed"
        };
    }

    yli::memory::GenericMemorySystem& HirviApplication::get_generic_memory_system() const
    {
        return this->memory_system.get();
    }

    yli::memory::MemorySystem<hirvi::Datatype>& HirviApplication::get_memory_system() const
    {
        return this->memory_system.get();
    }

    yli::memory::GenericMemoryAllocator& HirviApplication::get_generic_memory_allocator(const int type) const
    {
        return this->memory_system.get_generic_allocator(type);
    }

    GenericEntityFactory& HirviApplication::get_generic_entity_factory() const
    {
        return this->entity_factory.get();
    }

    yli::event::EventSystem* HirviApplication::get_event_system() const
    {
        return this->event_system;
    }

    yli::input::InputSystem* HirviApplication::get_input_system() const
    {
        return this->input_system;
    }

    yli::audio::AudioSystem* HirviApplication::get_audio_system() const
    {
        return this->audio_system;
    }

    bool HirviApplication::is_universe(Entity* entity) const
    {
        return static_cast<Entity*>(this->universe) == entity;
    }

    Universe& HirviApplication::get_universe() const
    {
        if (this->universe == nullptr) [[unlikely]]
        {
            throw std::logic_error("ERROR: `HirviApplication::get_universe`: `this->universe` is `nullptr`!");
        }

        return *this->universe;
    }

    UniverseStruct HirviApplication::get_universe_struct() const
    {
        UniverseStruct universe_struct(yli::render::GraphicsApiBackend::OPENGL);
        universe_struct.application_name = "Hirvi";
        universe_struct.window_title = "Hirvi " + Universe::version + ", powered by Ylikuutio " + Universe::version;

        if (this->command_line_master.is_key("silent"))
        {
            universe_struct.is_silent = true;
        }

        if (this->command_line_master.is_key("fullscreen"))
        {
            universe_struct.is_fullscreen = true;
        }

        if (this->command_line_master.is_key("headless"))
        {
            universe_struct.graphics_api_backend = yli::render::GraphicsApiBackend::HEADLESS;
        }

        if (this->command_line_master.is_key("window_width") &&
                yli::string::check_if_unsigned_integer_string(this->command_line_master.get_value("window_width")))
        {
            const std::string window_width = this->command_line_master.get_value("window_width");
            std::size_t index = 0;
            universe_struct.window_width = yli::string::extract_value_or_throw<uint32_t>(window_width, index, "", "");
        }

        if (this->command_line_master.is_key("window_height") &&
                yli::string::check_if_unsigned_integer_string(this->command_line_master.get_value("window_height")))
        {
            const std::string window_height = this->command_line_master.get_value("window_height");
            std::size_t index = 0;
            universe_struct.window_height = yli::string::extract_value_or_throw<uint32_t>(window_height, index, "", "");
        }

        if (this->command_line_master.is_key("framebuffer_width") &&
                yli::string::check_if_unsigned_integer_string(this->command_line_master.get_value("framebuffer_width")))
        {
            const std::string framebuffer_width = this->command_line_master.get_value("framebuffer_width");
            std::size_t index = 0;
            universe_struct.framebuffer_module_struct.texture_width = yli::string::extract_value_or_throw<uint32_t>(framebuffer_width, index, "", "");
        }

        if (this->command_line_master.is_key("framebuffer_height") &&
                yli::string::check_if_unsigned_integer_string(this->command_line_master.get_value("framebuffer_height")))
        {
            const std::string framebuffer_height = this->command_line_master.get_value("framebuffer_height");
            std::size_t index = 0;
            universe_struct.framebuffer_module_struct.texture_height = yli::string::extract_value_or_throw<uint32_t>(framebuffer_height, index, "", "");
        }

        if (this->command_line_master.is_key("speed") &&
                yli::string::check_if_float_string(this->command_line_master.get_value("speed")))
        {
            const std::string speed = this->command_line_master.get_value("speed");
            std::size_t index = 0;
            universe_struct.speed = yli::string::extract_value_or_throw<float>(speed, index, "", "");
        }

        if (this->command_line_master.is_key("turbo_factor") &&
                yli::string::check_if_float_string(this->command_line_master.get_value("turbo_factor")))
        {
            const std::string turbo_factor = this->command_line_master.get_value("turbo_factor");
            std::size_t index = 0;
            universe_struct.turbo_factor = yli::string::extract_value_or_throw<float>(turbo_factor, index, "", "");
        }

        if (this->command_line_master.is_key("twin_turbo_factor") &&
                yli::string::check_if_float_string(this->command_line_master.get_value("twin_turbo_factor")))
        {
            const std::string twin_turbo_factor = this->command_line_master.get_value("twin_turbo_factor");
            std::size_t index = 0;
            universe_struct.twin_turbo_factor = yli::string::extract_value_or_throw<float>(twin_turbo_factor, index, "", "");
        }

        if (this->command_line_master.is_key("mouse_speed") &&
                yli::string::check_if_float_string(this->command_line_master.get_value("mouse_speed")))
        {
            const std::string mouse_speed = this->command_line_master.get_value("mouse_speed");
            std::size_t index = 0;
            universe_struct.mouse_speed = yli::string::extract_value_or_throw<float>(mouse_speed, index, "", "");
        }

        return universe_struct;
    }

    bool HirviApplication::create_simulation()
    {
        this->get_universe().set_global_name("universe");

        if (!this->get_universe().get_is_headless() && this->get_universe().get_window() == nullptr)
        {
            std::cerr << "Failed to open SDL window.\n";
            return false;
        }

        // Create the main `Console`.
        std::cout << "Creating Entity* my_console_entity ...\n";
        yli::ontology::ConsoleStruct my_console_struct(15, 0, 0, 39);
        my_console_struct.global_name = "my_console";
        std::cout << "Creating Console* my_console ...\n";
        Console* const my_console = this->entity_factory.create_console(my_console_struct);

        if (my_console == nullptr)
        {
            return false;
        }

        this->get_universe().set_active_console(my_console);

        // Create an Earth `Ecosystem`.

        this->create_earth_ecosystem();

        // Create the `Scene`s.
        // The `Scene`s will be created in the following order:
        // 1. Helsinki

        // Helsinki `Scene` begins here.

        std::cout << "Creating Scene* helsinki_scene ...\n";
        Scene* const helsinki_scene = this->create_helsinki_scene();

        if (helsinki_scene == nullptr)
        {
            return false;
        }

        // Set `helsinki_scene` to be the currently active `Scene`.
        std::cout << "Setting helsinki_scene as the active scene ...\n";
        this->get_universe().set_active_scene(helsinki_scene);

        // Helsinki `Scene` ends here.

        std::cout << "Creating Entity* my_font_2d_entity ...\n";

        FontStruct font_struct;
        font_struct.texture_filename = "Holstein.png";
        font_struct.font_texture_file_format = "png";
        font_struct.screen_width = this->get_universe().get_window_width();
        font_struct.screen_height = this->get_universe().get_window_height();
        font_struct.text_size = this->get_universe().get_text_size();
        font_struct.font_size = this->get_universe().get_font_size();

        std::cout << "Creating Font2d* my_font_2d ...\n";
        Font2d* const my_font_2d = this->entity_factory.create_font_2d(font_struct);

        if (my_font_2d == nullptr)
        {
            std::cerr << "Failed to create Font2d.\n";
            return false;
        }

        std::cout << "Font2d created successfully.\n";
        my_font_2d->set_global_name("my_font_2d");

        Console::bind_to_new_font_2d(*my_console, *my_font_2d);
        my_console->print_text("Welcome! Please write \"help\" for more");
        my_console->print_text("information.");

        /*********************************************************************
         *  Callback engines for action mode keyreleases begin here.         *
         *********************************************************************/

        std::cout << "Defining action mode keyrelease callback engines.\n";

        // Callback code for left Control release: release first turbo.
        CallbackEngineStruct release_first_turbo_callback_engine_struct;
        auto release_first_turbo_callback_engine = this->entity_factory.create_callback_engine(release_first_turbo_callback_engine_struct);
        release_first_turbo_callback_engine->create_callback_object(&yli::snippets::release_first_turbo);

        // Callback code for right Control release: release second turbo.
        CallbackEngineStruct release_second_turbo_callback_engine_struct;
        auto release_second_turbo_callback_engine = this->entity_factory.create_callback_engine(release_second_turbo_callback_engine_struct);
        release_second_turbo_callback_engine->create_callback_object(&yli::snippets::release_second_turbo);

        // Callback code for I release: enable_toggle invert mouse.
        CallbackEngineStruct enable_toggle_invert_mouse_callback_engine_struct;
        auto enable_toggle_invert_mouse_callback_engine = this->entity_factory.create_callback_engine(enable_toggle_invert_mouse_callback_engine_struct);
        enable_toggle_invert_mouse_callback_engine->create_callback_object(&yli::snippets::enable_toggle_invert_mouse);

        // Callback code for F release: enable_toggle flight mode.
        CallbackEngineStruct enable_toggle_flight_mode_callback_engine_struct;
        auto enable_toggle_flight_mode_callback_engine = this->entity_factory.create_callback_engine(enable_toggle_flight_mode_callback_engine_struct);
        enable_toggle_flight_mode_callback_engine->create_callback_object(&yli::snippets::enable_toggle_flight_mode);

        // Callback code for F1 release: enable toggle help mode.
        CallbackEngineStruct enable_toggle_help_mode_callback_engine_struct;
        auto enable_toggle_help_mode_callback_engine = this->entity_factory.create_callback_engine(enable_toggle_help_mode_callback_engine_struct);
        enable_toggle_help_mode_callback_engine->create_callback_object(&yli::snippets::enable_toggle_help_mode);

        /*********************************************************************
         *  Callback engines for action mode keypresses begin here.          *
         *********************************************************************/

        std::cout << "Defining action mode keypress callback engines.\n";

        // Callback code for `SDL_SCANCODE_GRAVE` (tilde key above Tab, usually used for console).
        CallbackEngineStruct enter_console_callback_engine_struct;
        auto enter_console_callback_engine = this->entity_factory.create_callback_engine(enter_console_callback_engine_struct);
        enter_console_callback_engine->create_callback_object(&Console::enter_console);

        // Callback code for esc: exit program.
        CallbackEngineStruct exit_program_callback_engine_struct;
        auto exit_program_callback_engine = this->entity_factory.create_callback_engine(exit_program_callback_engine_struct);
        exit_program_callback_engine->create_callback_object(&yli::snippets::exit_program);

        // Callback code for left Control: first turbo.
        CallbackEngineStruct first_turbo_callback_engine_struct;
        auto first_turbo_callback_engine = this->entity_factory.create_callback_engine(first_turbo_callback_engine_struct);
        first_turbo_callback_engine->create_callback_object(&yli::snippets::press_first_turbo);

        // Callback code for right Control: second turbo.
        CallbackEngineStruct second_turbo_callback_engine_struct;
        auto second_turbo_callback_engine = this->entity_factory.create_callback_engine(second_turbo_callback_engine_struct);
        second_turbo_callback_engine->create_callback_object(&yli::snippets::press_second_turbo);

        // Callback code for key up: move forward.
        CallbackEngineStruct move_forward_callback_engine_struct;
        auto move_forward_callback_engine = this->entity_factory.create_callback_engine(move_forward_callback_engine_struct);
        move_forward_callback_engine->create_callback_object(&yli::snippets::move_forward);

        // Callback code for key down: move backward.
        CallbackEngineStruct move_backward_callback_engine_struct;
        auto move_backward_callback_engine = this->entity_factory.create_callback_engine(move_backward_callback_engine_struct);
        move_backward_callback_engine->create_callback_object(&yli::snippets::move_backward);

        // Callback code for key left: strafe left.
        CallbackEngineStruct strafe_left_callback_engine_struct;
        auto strafe_left_callback_engine = this->entity_factory.create_callback_engine(strafe_left_callback_engine_struct);
        strafe_left_callback_engine->create_callback_object(&yli::snippets::strafe_left);

        // Callback code for key right: strafe right.
        CallbackEngineStruct strafe_right_callback_engine_struct;
        auto strafe_right_callback_engine = this->entity_factory.create_callback_engine(strafe_right_callback_engine_struct);
        strafe_right_callback_engine->create_callback_object(&yli::snippets::strafe_right);

        // Callback code for space: ascent.
        CallbackEngineStruct ascent_callback_engine_struct;
        auto ascent_callback_engine = this->entity_factory.create_callback_engine(ascent_callback_engine_struct);
        ascent_callback_engine->create_callback_object(&yli::snippets::ascent);

        // Callback code for enter: descent.
        CallbackEngineStruct descent_callback_engine_struct;
        auto descent_callback_engine = this->entity_factory.create_callback_engine(descent_callback_engine_struct);
        descent_callback_engine->create_callback_object(&yli::snippets::descent);

        // Callback code for I: toggle invert mouse.
        CallbackEngineStruct toggle_invert_mouse_callback_engine_struct;
        auto toggle_invert_mouse_callback_engine = this->entity_factory.create_callback_engine(toggle_invert_mouse_callback_engine_struct);
        toggle_invert_mouse_callback_engine->create_callback_object(&yli::snippets::toggle_invert_mouse);

        // Callback code for F: toggle flight mode.
        CallbackEngineStruct toggle_flight_mode_callback_engine_struct;
        auto toggle_flight_mode_callback_engine = this->entity_factory.create_callback_engine(toggle_flight_mode_callback_engine_struct);
        toggle_flight_mode_callback_engine->create_callback_object(&yli::snippets::toggle_flight_mode);

        // Callback code for F1: toggle help mode.
        CallbackEngineStruct toggle_help_mode_callback_engine_struct;
        auto toggle_help_mode_callback_engine = this->entity_factory.create_callback_engine(toggle_help_mode_callback_engine_struct);
        toggle_help_mode_callback_engine->create_callback_object(&yli::snippets::toggle_help_mode);

        /*********************************************************************
         *  Callback engines for console keyreleases begin here.             *
         *********************************************************************/

        std::cout << "Defining console keyrelease callback engines for `my_console`.\n";

        // Callback code for left Control release.
        ConsoleCallbackEngineStruct my_release_left_control_in_console_callback_engine_struct { Request<Console>("my_console") };
        auto my_release_left_control_in_console_callback_engine = this->entity_factory.create_console_callback_engine(my_release_left_control_in_console_callback_engine_struct);
        my_release_left_control_in_console_callback_engine->create_console_callback_object(&Console::release_left_control_in_console);

        // Callback code for right Control release.
        ConsoleCallbackEngineStruct my_release_right_control_in_console_callback_engine_struct { Request<Console>("my_console") };
        auto my_release_right_control_in_console_callback_engine = this->entity_factory.create_console_callback_engine(my_release_right_control_in_console_callback_engine_struct);
        my_release_right_control_in_console_callback_engine->create_console_callback_object(&Console::release_right_control_in_console);

        // Callback code for left Alt release.
        ConsoleCallbackEngineStruct my_release_left_alt_in_console_callback_engine_struct { Request<Console>("my_console") };
        auto my_release_left_alt_in_console_callback_engine = this->entity_factory.create_console_callback_engine(my_release_left_alt_in_console_callback_engine_struct);
        my_release_left_alt_in_console_callback_engine->create_console_callback_object(&Console::release_left_alt_in_console);

        // Callback code for right Alt release.
        ConsoleCallbackEngineStruct my_release_right_alt_in_console_callback_engine_struct { Request<Console>("my_console") };
        auto my_release_right_alt_in_console_callback_engine = this->entity_factory.create_console_callback_engine(my_release_right_alt_in_console_callback_engine_struct);
        my_release_right_alt_in_console_callback_engine->create_console_callback_object(&Console::release_right_alt_in_console);

        // Callback code for left Shift release.
        ConsoleCallbackEngineStruct my_release_left_shift_in_console_callback_engine_struct { Request<Console>("my_console") };
        auto my_release_left_shift_in_console_callback_engine = this->entity_factory.create_console_callback_engine(my_release_left_shift_in_console_callback_engine_struct);
        my_release_left_shift_in_console_callback_engine->create_console_callback_object(&Console::release_left_shift_in_console);

        // Callback code for right Shift release.
        ConsoleCallbackEngineStruct my_release_right_shift_in_console_callback_engine_struct { Request<Console>("my_console") };
        auto my_release_right_shift_in_console_callback_engine = this->entity_factory.create_console_callback_engine(my_release_right_shift_in_console_callback_engine_struct);
        my_release_right_shift_in_console_callback_engine->create_console_callback_object(&Console::release_right_shift_in_console);

        // Callback code for key up release: enable move to previous input.
        ConsoleCallbackEngineStruct my_enable_move_to_previous_input_callback_engine_struct { Request<Console>("my_console") };
        auto my_enable_move_to_previous_input_callback_engine = this->entity_factory.create_console_callback_engine(my_enable_move_to_previous_input_callback_engine_struct);
        my_enable_move_to_previous_input_callback_engine->create_console_callback_object(&Console::enable_move_to_previous_input);

        // Callback code for key down release: enable move to next input.
        ConsoleCallbackEngineStruct my_enable_move_to_next_input_callback_engine_struct { Request<Console>("my_console") };
        auto my_enable_move_to_next_input_callback_engine = this->entity_factory.create_console_callback_engine(my_enable_move_to_next_input_callback_engine_struct);
        my_enable_move_to_next_input_callback_engine->create_console_callback_object(&Console::enable_move_to_next_input);

        // Callback code for backspace release: enable backspace.
        ConsoleCallbackEngineStruct my_enable_backspace_callback_engine_struct { Request<Console>("my_console") };
        auto my_enable_backspace_callback_engine = this->entity_factory.create_console_callback_engine(my_enable_backspace_callback_engine_struct);
        my_enable_backspace_callback_engine->create_console_callback_object(&Console::enable_backspace);

        // Callback code for Tab release: enable Tab.
        ConsoleCallbackEngineStruct my_enable_tab_callback_engine_struct { Request<Console>("my_console") };
        auto my_enable_tab_callback_engine = this->entity_factory.create_console_callback_engine(my_enable_tab_callback_engine_struct);
        my_enable_tab_callback_engine->create_console_callback_object(&Console::enable_tab);

        // Callback code for enter release: enable Enter key.
        ConsoleCallbackEngineStruct my_enable_enter_key_callback_engine_struct { Request<Console>("my_console") };
        auto my_enable_enter_key_callback_engine = this->entity_factory.create_console_callback_engine(my_enable_enter_key_callback_engine_struct);
        my_enable_enter_key_callback_engine->create_console_callback_object(&Console::enable_enter_key);

        // Callback code for C release: enable Control-C.
        ConsoleCallbackEngineStruct my_enable_ctrl_c_callback_engine_struct { Request<Console>("my_console") };
        auto my_enable_ctrl_c_callback_engine = this->entity_factory.create_console_callback_engine(my_enable_ctrl_c_callback_engine_struct);
        my_enable_ctrl_c_callback_engine->create_console_callback_object(&Console::enable_ctrl_c);

        // Callback code for W release: enable Control-W.
        ConsoleCallbackEngineStruct my_enable_ctrl_w_callback_engine_struct { Request<Console>("my_console") };
        auto my_enable_ctrl_w_callback_engine = this->entity_factory.create_console_callback_engine(my_enable_ctrl_w_callback_engine_struct);
        my_enable_ctrl_w_callback_engine->create_console_callback_object(&Console::enable_ctrl_w);

        // Callback code for PgUp release: enable PgUp.
        ConsoleCallbackEngineStruct my_enable_page_up_callback_engine_struct { Request<Console>("my_console") };
        auto my_enable_page_up_callback_engine = this->entity_factory.create_console_callback_engine(my_enable_page_up_callback_engine_struct);
        my_enable_page_up_callback_engine->create_console_callback_object(&Console::enable_page_up);

        // Callback code for PgDn release: enable PgDn.
        ConsoleCallbackEngineStruct my_enable_page_down_callback_engine_struct { Request<Console>("my_console") };
        auto my_enable_page_down_callback_engine = this->entity_factory.create_console_callback_engine(my_enable_page_down_callback_engine_struct);
        my_enable_page_down_callback_engine->create_console_callback_object(&Console::enable_page_down);

        // Callback code for Home release: enable Home.
        ConsoleCallbackEngineStruct my_enable_home_callback_engine_struct { Request<Console>("my_console") };
        auto my_enable_home_callback_engine = this->entity_factory.create_console_callback_engine(my_enable_home_callback_engine_struct);
        my_enable_home_callback_engine->create_console_callback_object(&Console::enable_home);

        // Callback code for End release: enable End.
        ConsoleCallbackEngineStruct my_enable_end_callback_engine_struct { Request<Console>("my_console") };
        auto my_enable_end_callback_engine = this->entity_factory.create_console_callback_engine(my_enable_end_callback_engine_struct);
        my_enable_end_callback_engine->create_console_callback_object(&Console::enable_end);

        /*********************************************************************
         *  Callback engines for console keypresses begin here.              *
         *********************************************************************/

        std::cout << "Defining console keypress callback engines for `my_console`.\n";

        // Callback code for `SDL_SCANCODE_GRAVE` (tilde key above Tab, usually used for console).
        ConsoleCallbackEngineStruct my_exit_console_callback_engine_struct { Request<Console>("my_console") };
        auto my_exit_console_callback_engine = this->entity_factory.create_console_callback_engine(my_exit_console_callback_engine_struct);
        my_exit_console_callback_engine->create_console_callback_object(&Console::exit_console);

        // Callback code for left Control press.
        ConsoleCallbackEngineStruct my_press_left_control_in_console_callback_engine_struct { Request<Console>("my_console") };
        auto my_press_left_control_in_console_callback_engine = this->entity_factory.create_console_callback_engine(my_press_left_control_in_console_callback_engine_struct);
        my_press_left_control_in_console_callback_engine->create_console_callback_object(&Console::press_left_control_in_console);

        // Callback code for right Control press.
        ConsoleCallbackEngineStruct my_press_right_control_in_console_callback_engine_struct { Request<Console>("my_console") };
        auto my_press_right_control_in_console_callback_engine = this->entity_factory.create_console_callback_engine(my_press_right_control_in_console_callback_engine_struct);
        my_press_right_control_in_console_callback_engine->create_console_callback_object(&Console::press_right_control_in_console);

        // Callback code for left Alt press.
        ConsoleCallbackEngineStruct my_press_left_alt_in_console_callback_engine_struct { Request<Console>("my_console") };
        auto my_press_left_alt_in_console_callback_engine = this->entity_factory.create_console_callback_engine(my_press_left_alt_in_console_callback_engine_struct);
        my_press_left_alt_in_console_callback_engine->create_console_callback_object(&Console::press_left_alt_in_console);

        // Callback code for right Alt press.
        ConsoleCallbackEngineStruct my_press_right_alt_in_console_callback_engine_struct { Request<Console>("my_console") };
        auto my_press_right_alt_in_console_callback_engine = this->entity_factory.create_console_callback_engine(my_press_right_alt_in_console_callback_engine_struct);
        my_press_right_alt_in_console_callback_engine->create_console_callback_object(&Console::press_right_alt_in_console);

        // Callback code for left Shift press.
        ConsoleCallbackEngineStruct my_press_left_shift_in_console_callback_engine_struct { Request<Console>("my_console") };
        auto my_press_left_shift_in_console_callback_engine = this->entity_factory.create_console_callback_engine(my_press_left_shift_in_console_callback_engine_struct);
        my_press_left_shift_in_console_callback_engine->create_console_callback_object(&Console::press_left_shift_in_console);

        // Callback code for right Shift press.
        ConsoleCallbackEngineStruct my_press_right_shift_in_console_callback_engine_struct { Request<Console>("my_console") };
        auto my_press_right_shift_in_console_callback_engine = this->entity_factory.create_console_callback_engine(my_press_right_shift_in_console_callback_engine_struct);
        my_press_right_shift_in_console_callback_engine->create_console_callback_object(&Console::press_right_shift_in_console);

        // Callback code for key up: move to previous input.
        ConsoleCallbackEngineStruct my_move_to_previous_input_callback_engine_struct { Request<Console>("my_console") };
        auto my_move_to_previous_input_callback_engine = this->entity_factory.create_console_callback_engine(my_move_to_previous_input_callback_engine_struct);
        my_move_to_previous_input_callback_engine->create_console_callback_object(&Console::move_to_previous_input);

        // Callback code for key down: move to next input.
        ConsoleCallbackEngineStruct my_move_to_next_input_callback_engine_struct { Request<Console>("my_console") };
        auto my_move_to_next_input_callback_engine = this->entity_factory.create_console_callback_engine(my_move_to_next_input_callback_engine_struct);
        my_move_to_next_input_callback_engine->create_console_callback_object(&Console::move_to_next_input);

        // Callback code for backspace: delete character left of cursor from current input in console.
        ConsoleCallbackEngineStruct my_backspace_callback_engine_struct { Request<Console>("my_console") };
        auto my_backspace_callback_engine = this->entity_factory.create_console_callback_engine(my_backspace_callback_engine_struct);
        my_backspace_callback_engine->create_console_callback_object(&Console::backspace);

        // Callback code for Tab.
        ConsoleCallbackEngineStruct my_tab_callback_engine_struct { Request<Console>("my_console") };
        auto my_tab_callback_engine = this->entity_factory.create_console_callback_engine(my_tab_callback_engine_struct);
        my_tab_callback_engine->create_console_callback_object(&Console::tab);

        // Callback code for Enter key.
        ConsoleCallbackEngineStruct my_enter_callback_engine_struct { Request<Console>("my_console") };
        auto my_enter_callback_engine = this->entity_factory.create_console_callback_engine(my_enter_callback_engine_struct);
        my_enter_callback_engine->create_console_callback_object(&Console::enter_key);

        // Callback code for C: Control-C.
        ConsoleCallbackEngineStruct my_ctrl_c_callback_engine_struct { Request<Console>("my_console") };
        auto my_ctrl_c_callback_engine = this->entity_factory.create_console_callback_engine(my_ctrl_c_callback_engine_struct);
        my_ctrl_c_callback_engine->create_console_callback_object(&Console::ctrl_c);

        // Callback code for W: Control-W.
        ConsoleCallbackEngineStruct my_ctrl_w_callback_engine_struct { Request<Console>("my_console") };
        auto my_ctrl_w_callback_engine = this->entity_factory.create_console_callback_engine(my_ctrl_w_callback_engine_struct);
        my_ctrl_w_callback_engine->create_console_callback_object(&Console::ctrl_w);

        // Callback code for PgUp.
        ConsoleCallbackEngineStruct my_page_up_callback_engine_struct { Request<Console>("my_console") };
        auto my_page_up_callback_engine = this->entity_factory.create_console_callback_engine(my_page_up_callback_engine_struct);
        my_page_up_callback_engine->create_console_callback_object(&Console::page_up);

        // Callback code for PgDn.
        ConsoleCallbackEngineStruct my_page_down_callback_engine_struct { Request<Console>("my_console") };
        auto my_page_down_callback_engine = this->entity_factory.create_console_callback_engine(my_page_down_callback_engine_struct);
        my_page_down_callback_engine->create_console_callback_object(&Console::page_down);

        // Callback code for Home.
        ConsoleCallbackEngineStruct my_home_callback_engine_struct { Request<Console>("my_console") };
        auto my_home_callback_engine = this->entity_factory.create_console_callback_engine(my_home_callback_engine_struct);
        my_home_callback_engine->create_console_callback_object(&Console::home);

        // Callback code for End.
        ConsoleCallbackEngineStruct my_end_callback_engine_struct { Request<Console>("my_console") };
        auto my_end_callback_engine = this->entity_factory.create_console_callback_engine(my_end_callback_engine_struct);
        my_end_callback_engine->create_console_callback_object(&Console::end);

        // Keyrelease callbacks for action mode.
        // Key releases are checked in the order of this struct.
        const InputModeStruct action_mode_input_mode_struct;
        InputMode* const action_mode_input_mode = this->entity_factory.create_input_mode(action_mode_input_mode_struct);
        action_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_LCTRL, release_first_turbo_callback_engine);
        action_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_RCTRL, release_second_turbo_callback_engine);
        action_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_I, enable_toggle_invert_mouse_callback_engine);
        action_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_F, enable_toggle_flight_mode_callback_engine);
        action_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_F1, enable_toggle_help_mode_callback_engine);

        // Keypress callbacks for action mode.
        // Keypresses are checked in the order of this struct.
        action_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_GRAVE, enter_console_callback_engine);
        action_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_ESCAPE, exit_program_callback_engine);
        action_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_LCTRL, first_turbo_callback_engine);
        action_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_RCTRL, second_turbo_callback_engine);
        action_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_I, toggle_invert_mouse_callback_engine);
        action_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_F, toggle_flight_mode_callback_engine);
        action_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_F1, toggle_help_mode_callback_engine);

        // Continuous keypress callbacks for action mode.
        // Keypresses are checked in the order of this struct.
        action_mode_input_mode->set_continuous_keypress_callback_engine(SDL_SCANCODE_UP, move_forward_callback_engine);
        action_mode_input_mode->set_continuous_keypress_callback_engine(SDL_SCANCODE_DOWN, move_backward_callback_engine);
        action_mode_input_mode->set_continuous_keypress_callback_engine(SDL_SCANCODE_LEFT, strafe_left_callback_engine);
        action_mode_input_mode->set_continuous_keypress_callback_engine(SDL_SCANCODE_RIGHT, strafe_right_callback_engine);
        action_mode_input_mode->set_continuous_keypress_callback_engine(SDL_SCANCODE_SPACE, ascent_callback_engine);
        action_mode_input_mode->set_continuous_keypress_callback_engine(SDL_SCANCODE_RETURN, descent_callback_engine);
        action_mode_input_mode->activate();

        // Keyrelease callbacks for `my_console`.
        // Key releases are checked in the order of this struct.
        InputModeStruct my_console_mode_input_mode_struct;
        my_console_mode_input_mode_struct.console_master = Request<Console>("my_console");
        InputMode* const my_console_mode_input_mode = this->entity_factory.create_input_mode(my_console_mode_input_mode_struct);
        my_console_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_LCTRL, my_release_left_control_in_console_callback_engine);
        my_console_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_RCTRL, my_release_right_control_in_console_callback_engine);
        my_console_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_LALT, my_release_left_alt_in_console_callback_engine);
        my_console_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_RALT, my_release_right_alt_in_console_callback_engine);
        my_console_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_LSHIFT, my_release_left_shift_in_console_callback_engine);
        my_console_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_RSHIFT, my_release_right_shift_in_console_callback_engine);
        my_console_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_UP, my_enable_move_to_previous_input_callback_engine);
        my_console_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_DOWN, my_enable_move_to_next_input_callback_engine);
        my_console_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_BACKSPACE, my_enable_backspace_callback_engine);
        my_console_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_TAB, my_enable_tab_callback_engine);
        my_console_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_RETURN, my_enable_enter_key_callback_engine);
        my_console_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_C, my_enable_ctrl_c_callback_engine);
        my_console_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_W, my_enable_ctrl_w_callback_engine);
        my_console_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_PAGEUP, my_enable_page_up_callback_engine);
        my_console_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_PAGEDOWN, my_enable_page_down_callback_engine);
        my_console_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_HOME, my_enable_home_callback_engine);
        my_console_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_END, my_enable_end_callback_engine);

        // Keypress callbacks for `my_console`.
        // Keypresses are checked in the order of this struct.
        my_console_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_GRAVE, my_exit_console_callback_engine);
        my_console_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_LCTRL, my_press_left_control_in_console_callback_engine);
        my_console_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_RCTRL, my_press_right_control_in_console_callback_engine);
        my_console_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_LALT, my_press_left_alt_in_console_callback_engine);
        my_console_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_RALT, my_press_right_alt_in_console_callback_engine);
        my_console_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_LSHIFT, my_press_left_shift_in_console_callback_engine);
        my_console_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_RSHIFT, my_press_right_shift_in_console_callback_engine);
        my_console_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_UP, my_move_to_previous_input_callback_engine);
        my_console_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_DOWN, my_move_to_next_input_callback_engine);
        my_console_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_BACKSPACE, my_backspace_callback_engine);
        my_console_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_TAB, my_tab_callback_engine);
        my_console_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_RETURN, my_enter_callback_engine);
        my_console_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_C, my_ctrl_c_callback_engine);
        my_console_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_W, my_ctrl_w_callback_engine);
        my_console_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_PAGEUP, my_page_up_callback_engine);
        my_console_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_PAGEDOWN, my_page_down_callback_engine);
        my_console_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_HOME, my_home_callback_engine);
        my_console_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_END, my_end_callback_engine);

        /*********************************************************************
         * Callback engines for console commands begin here.                 *
         * These define what commands there are available in the console     *
         * and what each command does.                                       *
         *********************************************************************/

        std::cout << "Defining console command callback engines.\n";

        // Variable callbacks.
        this->entity_factory.create_lisp_function_overload("variables", *my_console, &Entity::print_variables0);
        this->entity_factory.create_lisp_function_overload("variables", *my_console, &Entity::print_variables1);
        this->entity_factory.create_lisp_function_overload("create-variable", *my_console, &Entity::create_variable_with_parent_name_type_value);
        this->entity_factory.create_lisp_function_overload("set", *my_console, &Variable::set_variable_const_std_string);
        this->entity_factory.create_lisp_function_overload("copy", *my_console, &Variable::set_variable_variable);
        this->entity_factory.create_lisp_function_overload("print", *my_console, &Variable::print_value1);

        // Object callbacks.
        this->entity_factory.create_lisp_function_overload("create-object", *my_console, &Object::with_parent_name_x_y_z);
        this->entity_factory.create_lisp_function_overload("create-object", *my_console, &Object::with_parent_name_x_y_z_yaw_pitch);
        this->entity_factory.create_lisp_function_overload("create-object", *my_console, &Object::with_parent_name_x_y_z_roll_yaw_pitch);

        // Holobiont callbacks.
        this->entity_factory.create_lisp_function_overload("create-holobiont", *my_console, &Holobiont::create_holobiont_with_parent_name_x_y_z);
        this->entity_factory.create_lisp_function_overload("create-holobiont", *my_console, &Holobiont::create_holobiont_with_parent_name_x_y_z_yaw_pitch);
        this->entity_factory.create_lisp_function_overload("create-holobiont", *my_console, &Holobiont::create_holobiont_with_parent_name_x_y_z_roll_yaw_pitch);

        // `Entity` handling callbacks.
        this->entity_factory.create_lisp_function_overload("entities", *my_console, &Universe::print_entities);
        this->entity_factory.create_lisp_function_overload("parent", *my_console, &Universe::print_parent);
        this->entity_factory.create_lisp_function_overload("children", *my_console, &Entity::print_children);
        this->entity_factory.create_lisp_function_overload("activate", *my_console, &Universe::activate_entity);
        this->entity_factory.create_lisp_function_overload("delete", *my_console, &Universe::delete_entity);
        this->entity_factory.create_lisp_function_overload("info", *my_console, &Universe::info0);
        this->entity_factory.create_lisp_function_overload("info", *my_console, &Universe::info1);

        // `Entity` binding callbacks, `Movable`.
        this->entity_factory.create_lisp_function_overload("bind", *my_console, &Movable::bind_to_new_brain);
        this->entity_factory.create_lisp_function_overload("unbind-from-brain", *my_console, &Movable::unbind_from_brain);

        // `Entity` binding callbacks, `Pipeline`.
        this->entity_factory.create_lisp_function_overload("bind", *my_console, &Pipeline::bind_to_new_ecosystem_parent);
        this->entity_factory.create_lisp_function_overload("bind", *my_console, &Pipeline::bind_to_new_scene_parent);

        // `Entity` binding callbacks, `Material`.
        this->entity_factory.create_lisp_function_overload("bind", *my_console, &Material::bind_to_new_ecosystem_parent);
        this->entity_factory.create_lisp_function_overload("bind", *my_console, &Material::bind_to_new_scene_parent);
        this->entity_factory.create_lisp_function_overload("bind", *my_console, &Material::bind_to_new_pipeline);

        // `Entity` binding callbacks, `Species`.
        this->entity_factory.create_lisp_function_overload("bind", *my_console, &Species::bind_to_new_ecosystem_parent);
        this->entity_factory.create_lisp_function_overload("bind", *my_console, &Species::bind_to_new_scene_parent);
        this->entity_factory.create_lisp_function_overload("bind", *my_console, &Species::bind_to_new_material);

        // `Entity` binding callbacks, `Object`.
        this->entity_factory.create_lisp_function_overload("bind", *my_console, &Object::bind_to_new_scene_parent);
        this->entity_factory.create_lisp_function_overload("bind", *my_console, &Object::bind_to_new_species_master);

        // `Entity` binding callbacks, `Symbiosis`.
        this->entity_factory.create_lisp_function_overload("bind", *my_console, &Symbiosis::bind_to_new_ecosystem_parent);
        this->entity_factory.create_lisp_function_overload("bind", *my_console, &Symbiosis::bind_to_new_scene_parent);
        this->entity_factory.create_lisp_function_overload("bind", *my_console, &Symbiosis::bind_to_new_pipeline);

        // `Entity` binding callbacks, `ShapeshifterTransformation`.
        this->entity_factory.create_lisp_function_overload("bind", *my_console, &ShapeshifterTransformation::bind_to_new_material_parent);

        // `Entity` binding callbacks, `Text2d`.
        this->entity_factory.create_lisp_function_overload("bind", *my_console, &Text2d::bind_to_new_font_2d_parent);

        // `Entity` binding callbacks, `Text3d`.
        this->entity_factory.create_lisp_function_overload("bind", *my_console, &Text3d::bind_to_new_scene_parent);
        this->entity_factory.create_lisp_function_overload("bind", *my_console, &Text3d::bind_to_new_vector_font_master);

        // `Entity` binding callbacks, `Console`.
        this->entity_factory.create_lisp_function_overload("bind", *my_console, &Console::bind_to_new_font_2d);

        // `Entity` naming callbacks.
        this->entity_factory.create_lisp_function_overload("set-global-name", *my_console, &Universe::set_global_name_for_entity);
        this->entity_factory.create_lisp_function_overload("set-local-name", *my_console, &Universe::set_local_name_for_entity);

        // Exit program callbacks.
        this->entity_factory.create_lisp_function_overload("bye", *my_console, &yli::snippets::quit);
        this->entity_factory.create_lisp_function_overload("chau", *my_console, &yli::snippets::quit);
        this->entity_factory.create_lisp_function_overload("ciao", *my_console, &yli::snippets::quit);
        this->entity_factory.create_lisp_function_overload("heippa", *my_console, &yli::snippets::quit);
        this->entity_factory.create_lisp_function_overload("quit", *my_console, &yli::snippets::quit);
        this->entity_factory.create_lisp_function_overload("sayonara", *my_console, &yli::snippets::quit);

        // Other callbacks.
        this->entity_factory.create_lisp_function_overload("help", *my_console, &yli::snippets::help);
        this->entity_factory.create_lisp_function_overload("version", *my_console, &hirvi::version);
        this->entity_factory.create_lisp_function_overload("clear", *my_console, &Console::clear);
        this->entity_factory.create_lisp_function_overload("screenshot", *my_console, &Universe::screenshot);

        if (this->audio_system != nullptr)
        {
            this->audio_system->add_to_playlist("Hirvi_playlist", "414257__sss-samples__chipland-loop-120-bpm-a-major.wav");
            this->audio_system->add_to_playlist("Hirvi_playlist", "414270__greek555__sample-97-bpm.wav");
            this->audio_system->play_playlist("Hirvi_playlist");
        }

        std::cout << "Setting up framebuffer size ...\n";
        yli::snippets::set_framebuffer_size(&this->get_universe(), this->get_universe().framebuffer_module.get_texture_width(), this->get_universe().framebuffer_module.get_texture_height());
        std::cout << "Setting up background colors ...\n";
        yli::snippets::set_background_colors(&this->get_universe(), 0.0f, 0.0f, 1.0f, 0.0f);
        std::cout << "Setting up wireframe state ...\n";
        yli::snippets::set_wireframe(&this->get_universe(), false);
        std::cout << "Setting up movement ...\n";
        yli::snippets::set_movement(&this->get_universe(), this->get_universe().speed, this->get_universe().turbo_factor, this->get_universe().twin_turbo_factor, this->get_universe().mouse_speed);
        std::cout << "Setting up location and orientation ...\n";
        yli::snippets::set_location_and_orientation(&this->get_universe(), 100.0f, 100.0f, 100.0f);
        std::cout << "Setting up debug variables ...\n";
        yli::snippets::set_flight_mode(&this->get_universe(), true);

        this->get_universe().start_simulation();
        return true;
    }
}

namespace yli::core
{
    std::unique_ptr<yli::core::Application> create_application(const int argc, const char* const argv[])
    {
        return std::make_unique<hirvi::HirviApplication>(argc, argv);
    }
}
