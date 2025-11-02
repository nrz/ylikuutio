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

#include "ajokki.hpp"
#include "lisp/ajokki_console_callbacks.hpp"
#include "code/ylikuutio/audio/audio_system.hpp"
#include "code/ylikuutio/command_line/command_line_master.hpp"
#include "code/ylikuutio/core/application.hpp"
#include "code/ylikuutio/core/entrypoint.hpp"
#include "code/ylikuutio/event/event_system.hpp"
#include "code/ylikuutio/input/input_system.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/render/graphics_api_backend.hpp"

// `yli::ontology` files included in the canonical order.
#include "code/ylikuutio/ontology/entity.hpp"
#include "code/ylikuutio/ontology/movable.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/callback_engine.hpp"
#include "code/ylikuutio/ontology/callback_object.hpp"
#include "code/ylikuutio/ontology/callback_parameter.hpp"
#include "code/ylikuutio/ontology/console_callback_object.hpp"
#include "code/ylikuutio/ontology/ecosystem.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/pipeline.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/font_2d.hpp"
#include "code/ylikuutio/ontology/input_mode.hpp"
#include "code/ylikuutio/ontology/console.hpp"
#include "code/ylikuutio/ontology/request.hpp"
#include "code/ylikuutio/ontology/texture_file_format.hpp"
#include "code/ylikuutio/ontology/universe_struct.hpp"
#include "code/ylikuutio/ontology/callback_engine_struct.hpp"
#include "code/ylikuutio/ontology/ecosystem_struct.hpp"
#include "code/ylikuutio/ontology/input_mode_struct.hpp"
#include "code/ylikuutio/ontology/console_struct.hpp"
#include "code/ylikuutio/ontology/font_struct.hpp"
#include "code/ylikuutio/sdl/ylikuutio_sdl.hpp"
#include "code/ylikuutio/snippets/framebuffer_snippets.hpp"
#include "code/ylikuutio/snippets/background_color_snippets.hpp"
#include "code/ylikuutio/snippets/keyboard_callback_snippets.hpp"
#include "code/ylikuutio/snippets/debug_snippets.hpp"
#include "code/ylikuutio/snippets/movement_snippets.hpp"
#include "code/ylikuutio/snippets/location_and_orientation_snippets.hpp"
#include "code/ylikuutio/snippets/wireframe_snippets.hpp"
#include "code/ylikuutio/snippets/action_mode_keyboard_callback_creation_snippets.hpp"
#include "code/ylikuutio/snippets/console_mode_keyboard_callback_creation_snippets.hpp"
#include "code/ylikuutio/snippets/lisp_function_overload_creation_snippets.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
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

namespace ajokki
{
    using namespace yli::console;
    using namespace yli::ontology;

    AjokkiApplication::AjokkiApplication(const int argc, const char* const argv[])
        : yli::core::Application(argc, argv),
        core(*this, this->get_universe_struct())
    {
        std::cout << "AjokkiApplication initialized!\n";
    }

    std::string AjokkiApplication::get_name() const
    {
        return "Ajokki";
    }

    yli::memory::GenericMemorySystem& AjokkiApplication::get_generic_memory_system() const
    {
        return this->core.memory_system.get();
    }

    yli::memory::GenericMemoryAllocator& AjokkiApplication::get_generic_memory_allocator(const int type) const
    {
        return this->core.memory_system.get_generic_allocator(type);
    }

    GenericEntityFactory& AjokkiApplication::get_generic_entity_factory() const
    {
        return this->core.entity_factory.get();
    }

    yli::event::EventSystem* AjokkiApplication::get_event_system() const
    {
        return this->core.event_system;
    }

    yli::input::InputSystem* AjokkiApplication::get_input_system() const
    {
        return this->core.input_system;
    }

    yli::audio::AudioSystem* AjokkiApplication::get_audio_system() const
    {
        return this->core.audio_system;
    }

    std::vector<std::string> AjokkiApplication::get_valid_keys() const
    {
        return {
            "help",
                "version",
                "silent",
                "fullscreen",
                "desktop-fullscreen",
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

    bool AjokkiApplication::is_universe(Entity* entity) const
    {
        return static_cast<Entity*>(this->core.universe) == entity;
    }

    Universe& AjokkiApplication::get_universe() const
    {
        if (this->core.universe == nullptr) [[unlikely]]
        {
            throw std::logic_error("ERROR: `AjokkiApplication::get_universe`: `this->core.universe` is `nullptr`!");
        }

        return *this->core.universe;
    }

    UniverseStruct AjokkiApplication::get_universe_struct() const
    {
        UniverseStruct universe_struct(yli::render::GraphicsApiBackend::OPENGL);
        universe_struct.application_name = "Ajokki";
        universe_struct.window_title = "Ajokki " + Universe::version + ", powered by Ylikuutio " + Universe::version;

        if (this->command_line_master.is_key("silent"))
        {
            universe_struct.is_silent = true;
        }

        if (this->command_line_master.is_key("fullscreen"))
        {
            universe_struct.is_fullscreen = true;
        }

        if (this->command_line_master.is_key("desktop-fullscreen"))
        {
            universe_struct.is_desktop_fullscreen = true;
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

    bool AjokkiApplication::create_and_start_simulation()
    {
        this->get_universe().set_global_name("universe");

        if (!this->get_universe().get_is_headless() && this->get_universe().get_window() == nullptr)
        {
            std::cerr << "Failed to open SDL window.\n";
            return false;
        }

        // Create the main `Console`.
        std::cout << "Creating Entity* my_console_entity ...\n";
        yli::ontology::ConsoleStruct my_console_struct(0, 39, 15, 0);
        my_console_struct.global_name = "my_console";
        std::cout << "Creating Console* my_console ...\n";
        Console* const my_console = this->core.entity_factory.create_console(my_console_struct);

        if (my_console == nullptr)
        {
            return false;
        }

        this->get_universe().set_active_console(my_console);

        // Create the 'mini' `Console`.
        std::cout << "Creating Entity* mini_console_entity ...\n";
        ConsoleStruct mini_console_struct(0, 39, 15, 0);
        mini_console_struct.global_name = "mini_console";
        std::cout << "Creating Console* mini_console ...\n";
        Console* const mini_console = this->core.entity_factory.create_console(mini_console_struct);

        if (mini_console == nullptr)
        {
            return false;
        }

        this->get_universe().set_active_console(mini_console);

        this->get_universe().set_active_console(my_console);

        // Create an Earth `Ecosystem`.

        this->create_earth_ecosystem();

        // Create a Mars `Ecosystem`.

        std::cout << "Creating Entity* mars_ecosystem and its contents ...\n";
        EcosystemStruct mars_ecosystem_struct;
        mars_ecosystem_struct.global_name = "mars_ecosystem";
        std::cout << "Creating Ecosystem* mars_ecosystem ...\n";
        if (this->core.entity_factory.create_ecosystem(mars_ecosystem_struct) == nullptr)
        {
            return false;
        }

        // Create the `Scene`s.
        // The `Scene`s will be created in the following order:
        // 1. Helsinki
        // 2. Joensuu

        // Helsinki `Scene` begins here.

        std::cout << "Creating Scene* helsinki_east_downtown_scene ...\n";
        Scene* const helsinki_east_downtown_scene = this->create_helsinki_east_downtown_scene();

        if (helsinki_east_downtown_scene == nullptr)
        {
            return false;
        }

        // Set `helsinki_east_downtown_scene` to be the currently active `Scene`.
        std::cout << "Setting helsinki_east_downtown_scene as the active scene ...\n";
        this->get_universe().set_active_scene(helsinki_east_downtown_scene);

        // Helsinki `Scene` ends here.

        // Joensuu `Scene` begins here.

        std::cout << "Creating Scene* joensuu_center_west_scene and its contents ...\n";
        if (this->create_joensuu_center_west_scene() == nullptr)
        {
            return false;
        }

        // Joensuu `Scene` ends here.

        std::cout << "Creating Entity* my_font_2d_entity ...\n";

        yli::ontology::FontStruct font_struct { yli::ontology::TextureFileFormat::PNG };
        font_struct.texture_filename = "Holstein.png";
        font_struct.screen_width = this->get_universe().get_window_width();
        font_struct.screen_height = this->get_universe().get_window_height();
        font_struct.text_size = this->get_universe().get_text_size();

        std::cout << "Creating Font2d* my_font_2d ...\n";
        Font2d* const my_font_2d = this->core.entity_factory.create_font_2d(font_struct);

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

        Console::bind_to_new_font_2d(*mini_console, *my_font_2d);
        mini_console->print_text("Welcome to mini_console!");
        mini_console->print_text("Please write \"miniactivate my_console\"");
        mini_console->print_text("to get back to \"my_console\".");

        /*********************************************************************
         *  Callback engines for action mode keypresses begin here.          *
         *********************************************************************/
        yli::snippets::create_action_mode_keypress_callbacks(this->core.entity_factory);

        /*********************************************************************
         *  Callback engines for action mode keyreleases begin here.         *
         *********************************************************************/
        yli::snippets::create_action_mode_keyrelease_callbacks(this->core.entity_factory);

        // Callback code for D: delete cat species.
        const std::string cat_species_string = "cat_species";
        CallbackEngineStruct delete_cat_species_callback_engine_struct;
        auto delete_cat_species_callback_engine = this->core.entity_factory.create_callback_engine(delete_cat_species_callback_engine_struct);
        auto delete_cat_species_callback_object = delete_cat_species_callback_engine->create_callback_object(
                &yli::snippets::delete_entity);
        delete_cat_species_callback_object->create_callback_parameter("", yli::data::AnyValue(cat_species_string));

        // Callback code for G: switch to grass material.
        const std::string grass_material_string = "helsinki_east_downtown_grass_material";
        CallbackEngineStruct switch_to_grass_material_callback_engine_struct;
        auto switch_to_grass_material_callback_engine = this->core.entity_factory.create_callback_engine(switch_to_grass_material_callback_engine_struct);
        auto switch_to_grass_material_callback_object = switch_to_grass_material_callback_engine->create_callback_object(
                &yli::snippets::switch_to_new_material);
        switch_to_grass_material_callback_object->create_callback_parameter(
                "",
                yli::data::AnyValue(cat_species_string));
        switch_to_grass_material_callback_object->create_callback_parameter(
                "",
                yli::data::AnyValue(grass_material_string));

        // Callback code for O: switch to orange fur material.
        const std::string orange_fur_material_string = "helsinki_east_downtown_orange_fur_material";
        CallbackEngineStruct switch_to_orange_fur_material_callback_engine_struct;
        auto switch_to_orange_fur_material_callback_engine = this->core.entity_factory.create_callback_engine(switch_to_orange_fur_material_callback_engine_struct);
        auto switch_to_orange_fur_material_callback_object = switch_to_orange_fur_material_callback_engine->create_callback_object(
                &yli::snippets::switch_to_new_material);
        switch_to_orange_fur_material_callback_object->create_callback_parameter(
                "",
                yli::data::AnyValue(cat_species_string));
        switch_to_orange_fur_material_callback_object->create_callback_parameter(
                "",
                yli::data::AnyValue(orange_fur_material_string));

        // Callback code for P: switch to pink_geometric_tiles_material.
        const std::string pink_geometric_tiles_material_string = "helsinki_east_downtown_pink_geometric_tiles_material";
        CallbackEngineStruct switch_to_pink_geometric_tiles_material_callback_engine_struct;
        auto switch_to_pink_geometric_tiles_material_callback_engine = this->core.entity_factory.create_callback_engine(switch_to_pink_geometric_tiles_material_callback_engine_struct);
        auto switch_to_pink_geometric_tiles_material_callback_object = switch_to_pink_geometric_tiles_material_callback_engine->create_callback_object(
                &yli::snippets::switch_to_new_material);
        switch_to_pink_geometric_tiles_material_callback_object->create_callback_parameter(
                "",
                yli::data::AnyValue(cat_species_string));
        switch_to_pink_geometric_tiles_material_callback_object->create_callback_parameter(
                "",
                yli::data::AnyValue(pink_geometric_tiles_material_string));

        // Callback code for T: transform `cat1` into terrain.
        const std::string helsinki_species_string = "helsinki_east_downtown_terrain_species";
        const std::string cat1_string = "cat1";
        CallbackEngineStruct transform_into_terrain_callback_engine_struct;
        auto transform_into_terrain_callback_engine = this->core.entity_factory.create_callback_engine(transform_into_terrain_callback_engine_struct);
        auto transform_into_terrain_callback_object = transform_into_terrain_callback_engine->create_callback_object(
                &yli::snippets::transform_into_new_species);
        transform_into_terrain_callback_object->create_callback_parameter("", yli::data::AnyValue(cat1_string));
        transform_into_terrain_callback_object->create_callback_parameter("", yli::data::AnyValue(helsinki_species_string));

        // Callback code for A: transform `cat1` back into monkey.
        CallbackEngineStruct transform_into_monkey_callback_engine_struct;
        auto transform_into_monkey_callback_engine = this->core.entity_factory.create_callback_engine(transform_into_monkey_callback_engine_struct);
        auto transform_into_monkey_callback_object = transform_into_monkey_callback_engine->create_callback_object(
                &yli::snippets::transform_into_new_species);
        transform_into_monkey_callback_object->create_callback_parameter("", yli::data::AnyValue(cat1_string));
        transform_into_monkey_callback_object->create_callback_parameter("", yli::data::AnyValue(cat_species_string));

        /*********************************************************************
         *  Callback engines for console keypresses begin here.              *
         *********************************************************************/
        yli::snippets::create_console_mode_keypress_callbacks(this->core.entity_factory);

        /*********************************************************************
         *  Callback engines for console keyreleases begin here.             *
         *********************************************************************/
        yli::snippets::create_console_mode_keyrelease_callbacks(this->core.entity_factory);

        // Action mode input mode.
        InputModeStruct action_mode_input_mode_struct;
        action_mode_input_mode_struct.global_name = "action_mode_input_mode";
        InputMode* const action_mode_input_mode = this->core.entity_factory.create_input_mode(action_mode_input_mode_struct);

        // Keypress callbacks for action mode.
        yli::snippets::set_action_mode_keypress_callback_engines_or_throw(*action_mode_input_mode);

        // Ajokki-specific keypress callbacks for action mode.
        action_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_D, Request<GenericCallbackEngine>(delete_cat_species_callback_engine));
        action_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_G, Request<GenericCallbackEngine>(switch_to_grass_material_callback_engine));
        action_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_O, Request<GenericCallbackEngine>(switch_to_orange_fur_material_callback_engine));
        action_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_P, Request<GenericCallbackEngine>(switch_to_pink_geometric_tiles_material_callback_engine));
        action_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_T, Request<GenericCallbackEngine>(transform_into_terrain_callback_engine));
        action_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_A, Request<GenericCallbackEngine>(transform_into_monkey_callback_engine));

        // Keyrelease callbacks for action mode.
        yli::snippets::set_action_mode_keyrelease_callback_engines_or_throw(*action_mode_input_mode);

        // Continuous keypress callbacks for action mode.
        yli::snippets::set_action_mode_continuous_keypress_callback_engines_or_throw(*action_mode_input_mode);

        action_mode_input_mode->activate();

        InputModeStruct my_console_mode_input_mode_struct;
        my_console_mode_input_mode_struct.console_master = Request(my_console);
        my_console_mode_input_mode_struct.global_name = "my_console_mode_input_mode";
        InputMode* const my_console_mode_input_mode = this->core.entity_factory.create_input_mode(my_console_mode_input_mode_struct);

        // Keypress callbacks for `my_console`.
        yli::snippets::set_console_mode_keypress_callback_engines_or_throw(*my_console_mode_input_mode);

        // Keyrelease callbacks for `my_console`.
        yli::snippets::set_console_mode_keyrelease_callback_engines_or_throw(*my_console_mode_input_mode);

        // Keyrelease callbacks for `mini_console`.
        // Key releases are checked in the order of this struct.
        InputModeStruct mini_console_mode_input_mode_struct;
        mini_console_mode_input_mode_struct.console_master = Request(mini_console);
        mini_console_mode_input_mode_struct.global_name = "mini_console_mode_input_mode";
        InputMode* const mini_console_mode_input_mode = this->core.entity_factory.create_input_mode(mini_console_mode_input_mode_struct);

        // Keypress callbacks for `mini_console`.
        yli::snippets::set_console_mode_keypress_callback_engines_or_throw(*mini_console_mode_input_mode);

        // Keyrelease callbacks for `mini_console`.
        yli::snippets::set_console_mode_keyrelease_callback_engines_or_throw(*mini_console_mode_input_mode);

        /*********************************************************************
         * Callback engines for console commands begin here.                 *
         * These define what commands there are available in the console     *
         * and what each command does.                                       *
         *********************************************************************/

        std::cout << "Defining console command callback engines.\n";

        // Lisp function overloads.
        yli::snippets::create_all_lisp_function_builtin_overloads(this->core.entity_factory, *my_console);

        // Ajokki-specific callbacks.
        this->core.entity_factory.create_lisp_function_overload("version", Request(my_console), &ajokki::version);

        // mini-console callbacks.
        this->core.entity_factory.create_lisp_function_overload("miniactivate", Request(mini_console), &Universe::activate_entity);
        this->core.entity_factory.create_lisp_function_overload("miniinfo", Request(mini_console), &Universe::info0);
        this->core.entity_factory.create_lisp_function_overload("miniinfo", Request(mini_console), &Universe::info1);

        if (this->core.audio_system != nullptr)
        {
            this->core.audio_system->add_to_playlist("Ajokki_playlist", "414257__sss-samples__chipland-loop-120-bpm-a-major.wav");
            this->core.audio_system->add_to_playlist("Ajokki_playlist", "414270__greek555__sample-97-bpm.wav");
            this->core.audio_system->play_playlist("Ajokki_playlist");
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
        yli::snippets::set_location_and_orientation(&this->get_universe(), 100.0f, 100.0f, 300.0f);
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
        return std::make_unique<ajokki::AjokkiApplication>(argc, argv);
    }
}
