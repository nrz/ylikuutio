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

#include "yli_edit.hpp"
#include "yli_edit_console_callbacks.hpp"
#include "code/ylikuutio/audio/audio_system.hpp"
#include "code/ylikuutio/console/console_logic_module.hpp"
#include "code/ylikuutio/command_line/command_line_master.hpp"
#include "code/ylikuutio/core/application.hpp"
#include "code/ylikuutio/core/entrypoint.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/event/event_system.hpp"
#include "code/ylikuutio/input/input_system.hpp"
#include "code/ylikuutio/memory/memory_system.hpp"
#include "code/ylikuutio/memory/memory_allocator.hpp"
#include "code/ylikuutio/render/graphics_api_backend.hpp"

// `yli::ontology` files included in the canonical order.
#include "code/ylikuutio/ontology/entity.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/variable.hpp"
#include "code/ylikuutio/ontology/callback_engine.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/holobiont.hpp"
#include "code/ylikuutio/ontology/font_2d.hpp"
#include "code/ylikuutio/ontology/text_2d.hpp"
#include "code/ylikuutio/ontology/input_mode.hpp"
#include "code/ylikuutio/ontology/console.hpp"
#include "code/ylikuutio/ontology/console_callback_engine.hpp"
#include "code/ylikuutio/ontology/request.hpp"
#include "code/ylikuutio/ontology/universe_struct.hpp"
#include "code/ylikuutio/ontology/callback_engine_struct.hpp"
#include "code/ylikuutio/ontology/texture_file_format.hpp"
#include "code/ylikuutio/ontology/font_struct.hpp"
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
#include "code/ylikuutio/snippets/action_mode_keyboard_callback_creation_snippets.hpp"
#include "code/ylikuutio/snippets/console_mode_keyboard_callback_creation_snippets.hpp"
#include "code/ylikuutio/snippets/console_callback_snippets.hpp"
#include "code/ylikuutio/snippets/lisp_function_overload_creation_snippets.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cstddef>   // std::size_t
#include <iostream>  // std::cout, std::cerr
#include <memory>    // std::make_unique, std::unique_ptr
#include <stdexcept> // std::logic_error
#include <string>    // std::string
#include <vector>    // std::vector

namespace yli::memory
{
    class GenericMemorySystem;
    class GenericMemoryAllocator;
}

namespace yli::ontology
{
    class GenericEntityFactory;
}

namespace yli_edit
{
    using namespace yli::ontology;

    YliEditApplication::YliEditApplication(const int argc, const char* const argv[])
        : yli::core::Application(argc, argv),
        entity_factory(*this, this->memory_system),
        system_factory(this->memory_system),
        universe { this->entity_factory.create_universe(this->get_universe_struct()) },
        event_system { this->system_factory.create_event_system(this->get_universe()) },
        input_system { this->system_factory.create_input_system(this->get_universe()) },
        audio_system { this->system_factory.create_audio_system(this->get_universe()) }
    {
        std::cout << "YliEditApplication initialized!\n";
    }

    std::string YliEditApplication::get_name() const
    {
        return "YliEdit";
    }

    yli::event::EventSystem* YliEditApplication::get_event_system() const
    {
        return this->event_system;
    }

    yli::input::InputSystem* YliEditApplication::get_input_system() const
    {
        return this->input_system;
    }

    yli::audio::AudioSystem* YliEditApplication::get_audio_system() const
    {
        return this->audio_system;
    }

    std::vector<std::string> YliEditApplication::get_valid_keys() const
    {
        return {
            "help",
                "version",
                "silent",
                "fullscreen",
                "headless",
                "window-width",
                "window-height",
                "framebuffer-width",
                "framebuffer-height",
                "speed",
                "turbo-factor",
                "twin-turbo-factor",
                "mouse-speed"
        };
    }

    yli::memory::GenericMemorySystem& YliEditApplication::get_generic_memory_system() const
    {
        return this->memory_system.get();
    }

    yli::memory::GenericMemoryAllocator& YliEditApplication::get_generic_memory_allocator(const int type) const
    {
        return this->memory_system.get_generic_allocator(type);
    }

    yli::ontology::GenericEntityFactory& YliEditApplication::get_generic_entity_factory() const
    {
        return this->entity_factory.get();
    }

    bool YliEditApplication::is_universe(yli::ontology::Entity* entity) const
    {
        return static_cast<yli::ontology::Entity*>(this->universe) == entity;
    }

    yli::ontology::Universe& YliEditApplication::get_universe() const
    {
        if (this->universe == nullptr) [[unlikely]]
        {
            throw std::logic_error("ERROR: `YliEditApplication::get_universe`: `this->universe` is `nullptr`!");
        }

        return *this->universe;
    }

    yli::ontology::UniverseStruct YliEditApplication::get_universe_struct() const
    {
        yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::OPENGL);
        universe_struct.application_name = "YliEdit";
        universe_struct.window_title = "YliEdit " + yli::ontology::Universe::version + ", powered by Ylikuutio " + yli::ontology::Universe::version;

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

        if (this->command_line_master.is_key("window-width") &&
                yli::string::check_if_unsigned_integer_string<char>(this->command_line_master.get_value("window-width")))
        {
            universe_struct.window_width = this->command_line_master.get_value_or_throw<uint32_t>("window-width");
        }

        if (this->command_line_master.is_key("window-height") &&
                yli::string::check_if_unsigned_integer_string<char>(this->command_line_master.get_value("window-height")))
        {
            universe_struct.window_height = this->command_line_master.get_value_or_throw<uint32_t>("window-height");
        }

        if (this->command_line_master.is_key("framebuffer-width") &&
                yli::string::check_if_unsigned_integer_string<char>(this->command_line_master.get_value("framebuffer-width")))
        {
            universe_struct.framebuffer_module_struct.texture_width = this->command_line_master.get_value_or_throw<uint32_t>("framebuffer-width");
        }

        if (this->command_line_master.is_key("framebuffer-height") &&
                yli::string::check_if_unsigned_integer_string<char>(this->command_line_master.get_value("framebuffer-height")))
        {
            universe_struct.framebuffer_module_struct.texture_height = this->command_line_master.get_value_or_throw<uint32_t>("framebuffer-height");
        }

        if (this->command_line_master.is_key("speed") &&
                yli::string::check_if_float_string<char>(this->command_line_master.get_value("speed")))
        {
            universe_struct.speed = this->command_line_master.get_value_or_throw<float>("speed");
        }

        if (this->command_line_master.is_key("turbo-factor") &&
                yli::string::check_if_float_string<char>(this->command_line_master.get_value("turbo-factor")))
        {
            universe_struct.turbo_factor = this->command_line_master.get_value_or_throw<float>("turbo-factor");
        }

        if (this->command_line_master.is_key("twin-turbo_factor") &&
                yli::string::check_if_float_string<char>(this->command_line_master.get_value("twin-turbo-factor")))
        {
            universe_struct.twin_turbo_factor = this->command_line_master.get_value_or_throw<float>("twin-turbo-factor");
        }

        if (this->command_line_master.is_key("mouse-speed") &&
                yli::string::check_if_float_string<char>(this->command_line_master.get_value("mouse-speed")))
        {
            universe_struct.mouse_speed = this->command_line_master.get_value_or_throw<float>("mouse-speed");
        }

        return universe_struct;
    }

    bool YliEditApplication::create_simulation()
    {
        this->get_universe().set_global_name("universe");

        if (!this->get_universe().get_is_headless() && this->get_universe().get_window() == nullptr)
        {
            std::cerr << "Failed to open SDL window.\n";
            return false;
        }

        // Create the main `Console`.
        std::cout << "Creating yli::ontology::Entity* my_console_entity ...\n";
        yli::ontology::ConsoleStruct my_console_struct(0, 39, 15, 0);
        my_console_struct.global_name = "my_console";
        std::cout << "Creating yli::ontology::Console* my_console ...\n";
        yli::ontology::Console* const my_console = this->entity_factory.create_console(my_console_struct);

        if (my_console == nullptr)
        {
            return false;
        }

        this->get_universe().set_active_console(my_console);

        std::cout << "Creating yli::ontology::Entity* my_font_2d_entity ...\n";

        yli::ontology::FontStruct font_struct { yli::ontology::TextureFileFormat::PNG };
        font_struct.texture_filename = "Holstein.png";
        font_struct.screen_width = this->get_universe().get_window_width();
        font_struct.screen_height = this->get_universe().get_window_height();
        font_struct.text_size = this->get_universe().get_text_size();

        std::cout << "Creating yli::ontology::Font2d* my_font_2d ...\n";
        yli::ontology::Font2d* const my_font_2d = this->entity_factory.create_font_2d(font_struct);

        if (my_font_2d == nullptr)
        {
            std::cerr << "Failed to create Font2d.\n";
            return false;
        }

        std::cout << "Font2d created successfully.\n";
        my_font_2d->set_global_name("my_font_2d");

        yli::ontology::Console::bind_to_new_font_2d(*my_console, *my_font_2d);
        my_console->print_text("Welcome! Please write \"help\" for more");
        my_console->print_text("information.");

        /*********************************************************************
         *  Callback engines for action mode keypresses begin here.          *
         *********************************************************************/
        yli::snippets::create_action_mode_keypress_callbacks(this->entity_factory);

        /*********************************************************************
         *  Callback engines for action mode keyreleases begin here.         *
         *********************************************************************/
        yli::snippets::create_action_mode_keyrelease_callbacks(this->entity_factory);

        /*********************************************************************
         *  Callback engines for console keypresses begin here.              *
         *********************************************************************/
        yli::snippets::create_console_mode_keypress_callbacks(this->entity_factory);

        /*********************************************************************
         *  Callback engines for console keyreleases begin here.             *
         *********************************************************************/
        yli::snippets::create_console_mode_keyrelease_callbacks(this->entity_factory);

        // Action mode input mode.
        InputModeStruct action_mode_input_mode_struct;
        action_mode_input_mode_struct.global_name = "action_mode_input_mode";
        InputMode* const action_mode_input_mode = this->entity_factory.create_input_mode(action_mode_input_mode_struct);

        // Keypress callbacks for action mode.
        yli::snippets::set_action_mode_keypress_callback_engines_or_throw(*action_mode_input_mode);

        // Keyrelease callbacks for action mode.
        yli::snippets::set_action_mode_keyrelease_callback_engines_or_throw(*action_mode_input_mode);

        // Continuous keypress callbacks for action mode.
        yli::snippets::set_action_mode_continuous_keypress_callback_engines_or_throw(*action_mode_input_mode);

        action_mode_input_mode->activate();

        InputModeStruct my_console_mode_input_mode_struct;
        my_console_mode_input_mode_struct.global_name = "my_console_mode_input_mode";
        my_console_mode_input_mode_struct.console_master = Request<Console>("my_console");
        InputMode* const my_console_mode_input_mode = this->entity_factory.create_input_mode(my_console_mode_input_mode_struct);

        // Keypress callbacks for `my_console`.
        yli::snippets::set_console_mode_keypress_callback_engines_or_throw(*my_console_mode_input_mode);

        // Keyrelease callbacks for `my_console`.
        yli::snippets::set_console_mode_keyrelease_callback_engines_or_throw(*my_console_mode_input_mode);

        /*********************************************************************
         * Callback engines for console commands begin here.                 *
         * These define what commands there are available in the console     *
         * and what each command does.                                       *
         *********************************************************************/

        std::cout << "Defining console command callback engines.\n";

        // Lisp function overloads.
        yli::snippets::create_all_lisp_function_builtin_overloads(this->entity_factory, *my_console);

        // YliEdit-specific callbacks.
        this->entity_factory.create_lisp_function_overload("version", *my_console, &yli_edit::version);

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
        return std::make_unique<yli_edit::YliEditApplication>(argc, argv);
    }
}
