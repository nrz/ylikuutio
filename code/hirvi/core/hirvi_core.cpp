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

#include "hirvi_core.hpp"
#include "hirvi_application_callback.hpp"
#include "code/ylikuutio/ontology/console.hpp"
#include "code/ylikuutio/ontology/input_parameters_to_any_value_callback_with_console.hpp"
#include "code/ylikuutio/snippets/framebuffer_snippets.hpp"
#include "code/ylikuutio/snippets/background_color_snippets.hpp"
#include "code/ylikuutio/snippets/debug_snippets.hpp"
#include "code/ylikuutio/snippets/movement_snippets.hpp"
#include "code/ylikuutio/snippets/location_and_orientation_snippets.hpp"
#include "code/ylikuutio/snippets/wireframe_snippets.hpp"
#include "code/ylikuutio/snippets/action_mode_keyboard_callback_creation_snippets.hpp"
#include "code/ylikuutio/snippets/console_mode_keyboard_callback_creation_snippets.hpp"
#include "code/ylikuutio/snippets/lisp_function_overload_creation_snippets.hpp"

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    struct UniverseStruct;
}

namespace hirvi
{
    using namespace yli::console;
    using namespace yli::ontology;

    HirviCore::HirviCore(yli::core::Application& application, const yli::ontology::UniverseStruct& universe_struct)
        : entity_factory(application, this->memory_system),
        system_factory(this->memory_system),
        universe { this->entity_factory.create_universe(universe_struct) },
        event_system { this->system_factory.create_event_system(this->get_universe()) },
        input_system { this->system_factory.create_input_system(this->get_universe()) },
        audio_system { this->system_factory.create_audio_system(this->get_universe()) }
    {
    }

    yli::ontology::Universe& HirviCore::get_universe() const
    {
        if (this->universe == nullptr) [[unlikely]]
        {
            throw std::logic_error("ERROR: `HirviCore::get_universe`: `this->universe` is `nullptr`!");
        }

        return *this->universe;
    }

    bool HirviCore::create_and_start_simulation(HirviApplicationCallback hirvi_application_callback)
    {
        this->get_universe().set_global_name("universe");

        if (!this->get_universe().get_is_headless() && this->get_universe().get_window() == nullptr)
        {
            std::cerr << "Failed to open SDL window.\n";
            return false;
        }

        // Create the main `Console`.
        std::cout << "Creating Entity* my_console_entity ...\n";
        yli::ontology::ConsoleStruct my_console_struct(0, this->get_universe().get_window_width() / this->get_universe().get_font_size(), 15, 0);
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

        yli::ontology::FontStruct font_struct { yli::ontology::TextureFileFormat::PNG };
        font_struct.texture_filename = "Holstein.png";
        font_struct.screen_width = this->get_universe().get_window_width();
        font_struct.screen_height = this->get_universe().get_window_height();
        font_struct.text_size = this->get_universe().get_text_size();

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

        if (hirvi_application_callback != nullptr)
        {
            hirvi_application_callback(*this);
        }

        this->get_universe().start_simulation();
        return true;
    }
}
