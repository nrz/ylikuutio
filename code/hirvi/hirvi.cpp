// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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

#ifndef PI
#define PI 3.14159265359f
#endif

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#define DEGREES_TO_RADIANS(x) (x * PI / 180.0f)
#endif

#ifndef RADIANS_TO_DEGREES
#define RADIANS_TO_DEGREES(x) (x * 180.0f / PI)
#endif

#include "hirvi_console_callbacks.hpp"
#include "code/ajokki/ajokki_helsinki_east_downtown_scene.hpp"
#include "code/ajokki/ajokki_joensuu_center_west_scene.hpp"
#include "code/ylikuutio/audio/audio_master.hpp"
#include "code/ylikuutio/callback/callback_parameter.hpp"
#include "code/ylikuutio/callback/callback_object.hpp"
#include "code/ylikuutio/callback/callback_engine.hpp"
#include "code/ylikuutio/callback/callback_magic_numbers.hpp"
#include "code/ylikuutio/command_line/command_line_master.hpp"
#include "code/ylikuutio/console/console_callback_engine.hpp"
#include "code/ylikuutio/console/console_callback_object.hpp"
#include "code/ylikuutio/core/application.hpp"
#include "code/ylikuutio/core/entrypoint.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/data/pi.hpp"
#include "code/ylikuutio/input/input_master.hpp"
#include "code/ylikuutio/input/input_mode.hpp"
#include "code/ylikuutio/render/graphics_api_backend.hpp"

// `yli::ontology` files included in the canonical order.
#include "code/ylikuutio/ontology/entity.hpp"
#include "code/ylikuutio/ontology/variable.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/holobiont.hpp"
#include "code/ylikuutio/ontology/font_2d.hpp"
#include "code/ylikuutio/ontology/text_2d.hpp"
#include "code/ylikuutio/ontology/console.hpp"
#include "code/ylikuutio/ontology/variable_struct.hpp"
#include "code/ylikuutio/ontology/universe_struct.hpp"
#include "code/ylikuutio/ontology/console_struct.hpp"
#include "code/ylikuutio/ontology/font_struct.hpp"
#include "code/ylikuutio/ontology/text_struct.hpp"
#include "code/ylikuutio/ontology/entity_factory.hpp"
#include "code/ylikuutio/ontology/entity_factory_templates.hpp"
#include "code/ylikuutio/opengl/vboindexer.hpp"
#include "code/ylikuutio/sdl/ylikuutio_sdl.hpp"
#include "code/ylikuutio/snippets/window_snippets.hpp"
#include "code/ylikuutio/snippets/framebuffer_snippets.hpp"
#include "code/ylikuutio/snippets/background_color_snippets.hpp"
#include "code/ylikuutio/snippets/console_callback_snippets.hpp"
#include "code/ylikuutio/snippets/keyboard_callback_snippets.hpp"
#include "code/ylikuutio/snippets/debug_snippets.hpp"
#include "code/ylikuutio/snippets/console_snippets.hpp"
#include "code/ylikuutio/snippets/movement_snippets.hpp"
#include "code/ylikuutio/snippets/location_and_orientation_snippets.hpp"
#include "code/ylikuutio/snippets/wireframe_snippets.hpp"
#include "code/ylikuutio/snippets/console_callback_snippets.hpp"
#include "code/ylikuutio/string/ylikuutio_string.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <cmath>         // abs, cos, NAN, remainder, sin, std::isnan, std::pow
#include <cstddef>       // std::size_t
#include <exception>     // try, catch, std::exception
#include <functional>    // std::function
#include <iomanip>       // std::setfill, std::setprecision, std::setw
#include <ios>           // std::defaultfloat, std::dec, std::fixed, std::hex, std::ios
#include <iostream>      // std::cout, std::cin, std::cerr
#include <memory>        // std::make_shared, std::shared_ptr
#include <sstream>       // std::istringstream, std::ostringstream, std::stringstream
#include <stdint.h>      // uint32_t etc.
#include <string>        // std::string
#include <utility>       // std::pair
#include <vector>        // std::vector

namespace hirvi
{
    class HirviApplication: public yli::core::Application
    {
        public:
            HirviApplication(const int argc, const char* const argv[])
                : yli::core::Application(argc, argv)
            {
                // constructor.
            }

            ~HirviApplication()
            {
                // destructor.
            }

            std::string get_name() const override
            {
                return "Hirvi";
            }

            std::vector<std::string> get_valid_keys() override
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

            yli::ontology::UniverseStruct get_universe_struct() override
            {
                yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::OPENGL);
                std::stringstream window_title_stringstream;
                window_title_stringstream << "Hirvi " << yli::ontology::Universe::version << ", powered by Ylikuutio " << yli::ontology::Universe::version;
                universe_struct.application_name = "Hirvi";
                universe_struct.window_title = window_title_stringstream.str();

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
                    universe_struct.window_width = yli::string::extract_uint32_t_value_from_string(window_width, index, nullptr, nullptr);
                }

                if (this->command_line_master.is_key("window_height") &&
                        yli::string::check_if_unsigned_integer_string(this->command_line_master.get_value("window_height")))
                {
                    const std::string window_height = this->command_line_master.get_value("window_height");
                    std::size_t index = 0;
                    universe_struct.window_height = yli::string::extract_uint32_t_value_from_string(window_height, index, nullptr, nullptr);
                }

                if (this->command_line_master.is_key("framebuffer_width") &&
                        yli::string::check_if_unsigned_integer_string(this->command_line_master.get_value("framebuffer_width")))
                {
                    const std::string framebuffer_width = this->command_line_master.get_value("framebuffer_width");
                    std::size_t index = 0;
                    universe_struct.framebuffer_module_struct.texture_width = yli::string::extract_uint32_t_value_from_string(framebuffer_width, index, nullptr, nullptr);
                }

                if (this->command_line_master.is_key("framebuffer_height") &&
                        yli::string::check_if_unsigned_integer_string(this->command_line_master.get_value("framebuffer_height")))
                {
                    const std::string framebuffer_height = this->command_line_master.get_value("framebuffer_height");
                    std::size_t index = 0;
                    universe_struct.framebuffer_module_struct.texture_height = yli::string::extract_uint32_t_value_from_string(framebuffer_height, index, nullptr, nullptr);
                }

                if (this->command_line_master.is_key("speed") &&
                        yli::string::check_if_float_string(this->command_line_master.get_value("speed")))
                {
                    const std::string speed = this->command_line_master.get_value("speed");
                    std::size_t index = 0;
                    universe_struct.speed = yli::string::extract_float_value_from_string(speed, index, nullptr, nullptr);
                }

                if (this->command_line_master.is_key("turbo_factor") &&
                        yli::string::check_if_float_string(this->command_line_master.get_value("turbo_factor")))
                {
                    const std::string turbo_factor = this->command_line_master.get_value("turbo_factor");
                    std::size_t index = 0;
                    universe_struct.turbo_factor = yli::string::extract_float_value_from_string(turbo_factor, index, nullptr, nullptr);
                }

                if (this->command_line_master.is_key("twin_turbo_factor") &&
                        yli::string::check_if_float_string(this->command_line_master.get_value("twin_turbo_factor")))
                {
                    const std::string twin_turbo_factor = this->command_line_master.get_value("twin_turbo_factor");
                    std::size_t index = 0;
                    universe_struct.twin_turbo_factor = yli::string::extract_float_value_from_string(twin_turbo_factor, index, nullptr, nullptr);
                }

                if (this->command_line_master.is_key("mouse_speed") &&
                        yli::string::check_if_float_string(this->command_line_master.get_value("mouse_speed")))
                {
                    const std::string mouse_speed = this->command_line_master.get_value("mouse_speed");
                    std::size_t index = 0;
                    universe_struct.mouse_speed = yli::string::extract_float_value_from_string(mouse_speed, index, nullptr, nullptr);
                }

                return universe_struct;
            }

            bool create_simulation() override
            {
                yli::ontology::Universe* const my_universe = this->get_universe();

                if (my_universe == nullptr)
                {
                    return false;
                }

                my_universe->set_global_name("universe");

                yli::ontology::EntityFactory* const entity_factory = my_universe->get_entity_factory();

                yli::audio::AudioMaster* const audio_master = my_universe->get_audio_master();

                yli::input::InputMaster* const input_master = my_universe->get_input_master();

                if (!my_universe->get_is_headless() && my_universe->get_window() == nullptr)
                {
                    std::cerr << "Failed to open SDL window.\n";
                    return false;
                }

                // Create the main `Console`.
                std::cout << "Creating yli::ontology::Entity* my_console_entity ...\n";
                yli::ontology::ConsoleStruct my_console_struct;
                my_console_struct.global_name = "my_console";
                yli::ontology::Entity* const my_console_entity = entity_factory->create_console(my_console_struct);
                std::cout << "Creating yli::ontology::Console* my_console ...\n";
                yli::ontology::Console* const my_console = dynamic_cast<yli::ontology::Console*>(my_console_entity);

                if (my_console == nullptr)
                {
                    return false;
                }

                my_universe->set_active_console(my_console);

                std::cout << "Setting up console ...\n";
                yli::snippets::set_console(my_universe, 15, 0, 0, 39);

                // Create the `Scene`s.
                // The `Scene`s will be created in the following order:
                // 1. Helsinki

                // Helsinki `Scene` begins here.

                std::cout << "Creating yli::ontology::Entity* helsinki_east_downtown_scene_entity and its contents ...\n";
                yli::ontology::Entity* const helsinki_east_downtown_scene_entity = ajokki::create_helsinki_east_downtown_scene(*my_universe, entity_factory);

                if (helsinki_east_downtown_scene_entity == nullptr)
                {
                    return false;
                }

                std::cout << "Creating yli::ontology::Scene* helsinki_east_downtown_scene ...\n";
                yli::ontology::Scene* const helsinki_east_downtown_scene = dynamic_cast<yli::ontology::Scene*>(helsinki_east_downtown_scene_entity);

                if (helsinki_east_downtown_scene == nullptr)
                {
                    return false;
                }

                // Set `helsinki_east_downtown_scene` to be the currently active `Scene`.
                std::cout << "Setting helsinki_east_downtown_scene as the active scene ...\n";
                my_universe->set_active_scene(helsinki_east_downtown_scene);

                // Helsinki `Scene` ends here.

                std::cout << "Creating yli::ontology::Entity* my_font_2d_entity ...\n";

                yli::ontology::FontStruct font_struct;
                font_struct.texture_filename = "Holstein.png";
                font_struct.font_texture_file_format = "png";
                font_struct.screen_width = my_universe->get_window_width();
                font_struct.screen_height = my_universe->get_window_height();
                font_struct.text_size = my_universe->get_text_size();
                font_struct.font_size = my_universe->get_font_size();

                yli::ontology::Entity* const my_font_2d_entity = entity_factory->create_font2d(font_struct);

                std::cout << "Creating yli::ontology::Font2D* my_font_2d ...\n";
                yli::ontology::Font2D* const my_font_2d = dynamic_cast<yli::ontology::Font2D*>(my_font_2d_entity);

                if (my_font_2d == nullptr)
                {
                    std::cerr << "Failed to create Font2D.\n";
                    return false;
                }

                std::cout << "Font2D created successfully.\n";
                my_font_2d->set_global_name("my_font_2d");

                my_console->bind_to_new_font_2d(my_font_2d);
                my_console->print_text("Welcome! Please write \"help\" for more");
                my_console->print_text("information.");

                /*********************************************************************
                 *  Callback engines for action mode keyreleases begin here.         *
                 *********************************************************************/

                std::cout << "Defining action mode keyrelease callback engines.\n";

                // Callback code for left Control release: release first turbo.
                yli::callback::CallbackEngine release_first_turbo_callback_engine(*my_universe);
                release_first_turbo_callback_engine.create_callback_object(&yli::snippets::release_first_turbo);

                // Callback code for right Control release: release second turbo.
                yli::callback::CallbackEngine release_second_turbo_callback_engine(*my_universe);
                release_second_turbo_callback_engine.create_callback_object(&yli::snippets::release_second_turbo);

                // Callback code for I release: enable_toggle invert mouse.
                yli::callback::CallbackEngine enable_toggle_invert_mouse_callback_engine(*my_universe);
                enable_toggle_invert_mouse_callback_engine.create_callback_object(&yli::snippets::enable_toggle_invert_mouse);

                // Callback code for F release: enable_toggle flight mode.
                yli::callback::CallbackEngine enable_toggle_flight_mode_callback_engine(*my_universe);
                enable_toggle_flight_mode_callback_engine.create_callback_object(&yli::snippets::enable_toggle_flight_mode);

                // Callback code for F1 release: enable toggle help mode.
                yli::callback::CallbackEngine enable_toggle_help_mode_callback_engine(*my_universe);
                enable_toggle_help_mode_callback_engine.create_callback_object(&yli::snippets::enable_toggle_help_mode);

                /*********************************************************************
                 *  Callback engines for action mode keypresses begin here.          *
                 *********************************************************************/

                std::cout << "Defining action mode keypress callback engines.\n";

                // Callback code for `SDL_SCANCODE_GRAVE` (tilde key above Tab, usually used for console).
                yli::callback::CallbackEngine enter_console_callback_engine(*my_universe);
                enter_console_callback_engine.create_callback_object(&yli::ontology::Console::enter_console);

                // Callback code for esc: exit program.
                yli::callback::CallbackEngine exit_program_callback_engine(*my_universe);
                exit_program_callback_engine.create_callback_object(&yli::snippets::exit_program);

                // Callback code for left Control: first turbo.
                yli::callback::CallbackEngine first_turbo_callback_engine(*my_universe);
                first_turbo_callback_engine.create_callback_object(&yli::snippets::first_turbo);

                // Callback code for right Control: second turbo.
                yli::callback::CallbackEngine second_turbo_callback_engine(*my_universe);
                second_turbo_callback_engine.create_callback_object(&yli::snippets::second_turbo);

                // Callback code for key up: move forward.
                yli::callback::CallbackEngine move_forward_callback_engine(*my_universe);
                move_forward_callback_engine.create_callback_object(&yli::snippets::move_forward);

                // Callback code for key down: move backward.
                yli::callback::CallbackEngine move_backward_callback_engine(*my_universe);
                move_backward_callback_engine.create_callback_object(&yli::snippets::move_backward);

                // Callback code for key left: strafe left.
                yli::callback::CallbackEngine strafe_left_callback_engine(*my_universe);
                strafe_left_callback_engine.create_callback_object(&yli::snippets::strafe_left);

                // Callback code for key right: strafe right.
                yli::callback::CallbackEngine strafe_right_callback_engine(*my_universe);
                strafe_right_callback_engine.create_callback_object(&yli::snippets::strafe_right);

                // Callback code for space: ascent.
                yli::callback::CallbackEngine ascent_callback_engine(*my_universe);
                ascent_callback_engine.create_callback_object(&yli::snippets::ascent);

                // Callback code for enter: descent.
                yli::callback::CallbackEngine descent_callback_engine(*my_universe);
                descent_callback_engine.create_callback_object(&yli::snippets::descent);

                // Callback code for I: toggle invert mouse.
                yli::callback::CallbackEngine toggle_invert_mouse_callback_engine(*my_universe);
                toggle_invert_mouse_callback_engine.create_callback_object(&yli::snippets::toggle_invert_mouse);

                // Callback code for F: toggle flight mode.
                yli::callback::CallbackEngine toggle_flight_mode_callback_engine(*my_universe);
                toggle_flight_mode_callback_engine.create_callback_object(&yli::snippets::toggle_flight_mode);

                // Callback code for F1: toggle help mode.
                yli::callback::CallbackEngine toggle_help_mode_callback_engine(*my_universe);
                toggle_help_mode_callback_engine.create_callback_object(&yli::snippets::toggle_help_mode);

                /*********************************************************************
                 *  Callback engines for console keyreleases begin here.             *
                 *********************************************************************/

                std::cout << "Defining console keyrelease callback engines for `my_console`.\n";

                // Callback code for left Control release.
                yli::console::ConsoleCallbackEngine my_release_left_control_in_console_callback_engine(*my_universe);
                my_release_left_control_in_console_callback_engine.create_console_callback_object(&yli::ontology::Console::release_left_control_in_console, my_console);

                // Callback code for right Control release.
                yli::console::ConsoleCallbackEngine my_release_right_control_in_console_callback_engine(*my_universe);
                my_release_right_control_in_console_callback_engine.create_console_callback_object(&yli::ontology::Console::release_right_control_in_console, my_console);

                // Callback code for left Alt release.
                yli::console::ConsoleCallbackEngine my_release_left_alt_in_console_callback_engine(*my_universe);
                my_release_left_alt_in_console_callback_engine.create_console_callback_object(&yli::ontology::Console::release_left_alt_in_console, my_console);

                // Callback code for right Alt release.
                yli::console::ConsoleCallbackEngine my_release_right_alt_in_console_callback_engine(*my_universe);
                my_release_right_alt_in_console_callback_engine.create_console_callback_object(&yli::ontology::Console::release_right_alt_in_console, my_console);

                // Callback code for left Shift release.
                yli::console::ConsoleCallbackEngine my_release_left_shift_in_console_callback_engine(*my_universe);
                my_release_left_shift_in_console_callback_engine.create_console_callback_object(&yli::ontology::Console::release_left_shift_in_console, my_console);

                // Callback code for right Shift release.
                yli::console::ConsoleCallbackEngine my_release_right_shift_in_console_callback_engine(*my_universe);
                my_release_right_shift_in_console_callback_engine.create_console_callback_object(&yli::ontology::Console::release_right_shift_in_console, my_console);

                // Callback code for key up release: enable move to previous input.
                yli::console::ConsoleCallbackEngine my_enable_move_to_previous_input_callback_engine(*my_universe);
                my_enable_move_to_previous_input_callback_engine.create_console_callback_object(&yli::ontology::Console::enable_move_to_previous_input, my_console);

                // Callback code for key down release: enable move to next input.
                yli::console::ConsoleCallbackEngine my_enable_move_to_next_input_callback_engine(*my_universe);
                my_enable_move_to_next_input_callback_engine.create_console_callback_object(&yli::ontology::Console::enable_move_to_next_input, my_console);

                // Callback code for backspace release: enable backspace.
                yli::console::ConsoleCallbackEngine my_enable_backspace_callback_engine(*my_universe);
                my_enable_backspace_callback_engine.create_console_callback_object(&yli::ontology::Console::enable_backspace, my_console);

                // Callback code for Tab release: enable Tab.
                yli::console::ConsoleCallbackEngine my_enable_tab_callback_engine(*my_universe);
                my_enable_tab_callback_engine.create_console_callback_object(&yli::ontology::Console::enable_tab, my_console);

                // Callback code for enter release: enable Enter key.
                yli::console::ConsoleCallbackEngine my_enable_enter_key_callback_engine(*my_universe);
                my_enable_enter_key_callback_engine.create_console_callback_object(&yli::ontology::Console::enable_enter_key, my_console);

                // Callback code for C release: enable Control-C.
                yli::console::ConsoleCallbackEngine my_enable_ctrl_c_callback_engine(*my_universe);
                my_enable_ctrl_c_callback_engine.create_console_callback_object(&yli::ontology::Console::enable_ctrl_c, my_console);

                // Callback code for W release: enable Control-W.
                yli::console::ConsoleCallbackEngine my_enable_ctrl_w_callback_engine(*my_universe);
                my_enable_ctrl_w_callback_engine.create_console_callback_object(&yli::ontology::Console::enable_ctrl_w, my_console);

                // Callback code for PgUp release: enable PgUp.
                yli::console::ConsoleCallbackEngine my_enable_page_up_callback_engine(*my_universe);
                my_enable_page_up_callback_engine.create_console_callback_object(&yli::ontology::Console::enable_page_up, my_console);

                // Callback code for PgDn release: enable PgDn.
                yli::console::ConsoleCallbackEngine my_enable_page_down_callback_engine(*my_universe);
                my_enable_page_down_callback_engine.create_console_callback_object(&yli::ontology::Console::enable_page_down, my_console);

                // Callback code for Home release: enable Home.
                yli::console::ConsoleCallbackEngine my_enable_home_callback_engine(*my_universe);
                my_enable_home_callback_engine.create_console_callback_object(&yli::ontology::Console::enable_home, my_console);

                // Callback code for End release: enable End.
                yli::console::ConsoleCallbackEngine my_enable_end_callback_engine(*my_universe);
                my_enable_end_callback_engine.create_console_callback_object(&yli::ontology::Console::enable_end, my_console);

                /*********************************************************************
                 *  Callback engines for console keypresses begin here.              *
                 *********************************************************************/

                std::cout << "Defining console keypress callback engines for `my_console`.\n";

                // Callback code for `SDL_SCANCODE_GRAVE` (tilde key above Tab, usually used for console).
                yli::console::ConsoleCallbackEngine my_exit_console_callback_engine(*my_universe);
                my_exit_console_callback_engine.create_console_callback_object(&yli::ontology::Console::exit_console, my_console);

                // Callback code for left Control press.
                yli::console::ConsoleCallbackEngine my_press_left_control_in_console_callback_engine(*my_universe);
                my_press_left_control_in_console_callback_engine.create_console_callback_object(&yli::ontology::Console::press_left_control_in_console, my_console);

                // Callback code for right Control press.
                yli::console::ConsoleCallbackEngine my_press_right_control_in_console_callback_engine(*my_universe);
                my_press_right_control_in_console_callback_engine.create_console_callback_object(&yli::ontology::Console::press_right_control_in_console, my_console);

                // Callback code for left Alt press.
                yli::console::ConsoleCallbackEngine my_press_left_alt_in_console_callback_engine(*my_universe);
                my_press_left_alt_in_console_callback_engine.create_console_callback_object(&yli::ontology::Console::press_left_alt_in_console, my_console);

                // Callback code for right Alt press.
                yli::console::ConsoleCallbackEngine my_press_right_alt_in_console_callback_engine(*my_universe);
                my_press_right_alt_in_console_callback_engine.create_console_callback_object(&yli::ontology::Console::press_right_alt_in_console, my_console);

                // Callback code for left Shift press.
                yli::console::ConsoleCallbackEngine my_press_left_shift_in_console_callback_engine(*my_universe);
                my_press_left_shift_in_console_callback_engine.create_console_callback_object(&yli::ontology::Console::press_left_shift_in_console, my_console);

                // Callback code for right Shift press.
                yli::console::ConsoleCallbackEngine my_press_right_shift_in_console_callback_engine(*my_universe);
                my_press_right_shift_in_console_callback_engine.create_console_callback_object(&yli::ontology::Console::press_right_shift_in_console, my_console);

                // Callback code for key up: move to previous input.
                yli::console::ConsoleCallbackEngine my_move_to_previous_input_callback_engine(*my_universe);
                my_move_to_previous_input_callback_engine.create_console_callback_object(&yli::ontology::Console::move_to_previous_input, my_console);

                // Callback code for key down: move to next input.
                yli::console::ConsoleCallbackEngine my_move_to_next_input_callback_engine(*my_universe);
                my_move_to_next_input_callback_engine.create_console_callback_object(&yli::ontology::Console::move_to_next_input, my_console);

                // Callback code for backspace: delete character left of cursor from current input in console.
                yli::console::ConsoleCallbackEngine my_backspace_callback_engine(*my_universe);
                my_backspace_callback_engine.create_console_callback_object(&yli::ontology::Console::backspace, my_console);

                // Callback code for Tab.
                yli::console::ConsoleCallbackEngine my_tab_callback_engine(*my_universe);
                my_tab_callback_engine.create_console_callback_object(&yli::ontology::Console::tab, my_console);

                // Callback code for Enter key.
                yli::console::ConsoleCallbackEngine my_enter_callback_engine(*my_universe);
                my_enter_callback_engine.create_console_callback_object(&yli::ontology::Console::enter_key, my_console);

                // Callback code for C: Control-C.
                yli::console::ConsoleCallbackEngine my_ctrl_c_callback_engine(*my_universe);
                my_ctrl_c_callback_engine.create_console_callback_object(&yli::ontology::Console::ctrl_c, my_console);

                // Callback code for W: Control-W.
                yli::console::ConsoleCallbackEngine my_ctrl_w_callback_engine(*my_universe);
                my_ctrl_w_callback_engine.create_console_callback_object(&yli::ontology::Console::ctrl_w, my_console);

                // Callback code for PgUp.
                yli::console::ConsoleCallbackEngine my_page_up_callback_engine(*my_universe);
                my_page_up_callback_engine.create_console_callback_object(&yli::ontology::Console::page_up, my_console);

                // Callback code for PgDn.
                yli::console::ConsoleCallbackEngine my_page_down_callback_engine(*my_universe);
                my_page_down_callback_engine.create_console_callback_object(&yli::ontology::Console::page_down, my_console);

                // Callback code for Home.
                yli::console::ConsoleCallbackEngine my_home_callback_engine(*my_universe);
                my_home_callback_engine.create_console_callback_object(&yli::ontology::Console::home, my_console);

                // Callback code for End.
                yli::console::ConsoleCallbackEngine my_end_callback_engine(*my_universe);
                my_end_callback_engine.create_console_callback_object(&yli::ontology::Console::end, my_console);

                // Keyrelease callbacks for action mode.
                // Key releases are checked in the order of this struct.
                yli::input::InputMode* const action_mode_input_mode = input_master->create_input_mode();
                action_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_LCTRL, &release_first_turbo_callback_engine);
                action_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_RCTRL, &release_second_turbo_callback_engine);
                action_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_I, &enable_toggle_invert_mouse_callback_engine);
                action_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_F, &enable_toggle_flight_mode_callback_engine);
                action_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_F1, &enable_toggle_help_mode_callback_engine);

                // Keypress callbacks for action mode.
                // Keypresses are checked in the order of this struct.
                action_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_GRAVE, &enter_console_callback_engine);
                action_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_ESCAPE, &exit_program_callback_engine);
                action_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_LCTRL, &first_turbo_callback_engine);
                action_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_RCTRL, &second_turbo_callback_engine);
                action_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_I, &toggle_invert_mouse_callback_engine);
                action_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_F, &toggle_flight_mode_callback_engine);
                action_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_F1, &toggle_help_mode_callback_engine);

                // Continuous keypress callbacks for action mode.
                // Keypresses are checked in the order of this struct.
                action_mode_input_mode->set_continuous_keypress_callback_engine(SDL_SCANCODE_UP, &move_forward_callback_engine);
                action_mode_input_mode->set_continuous_keypress_callback_engine(SDL_SCANCODE_DOWN, &move_backward_callback_engine);
                action_mode_input_mode->set_continuous_keypress_callback_engine(SDL_SCANCODE_LEFT, &strafe_left_callback_engine);
                action_mode_input_mode->set_continuous_keypress_callback_engine(SDL_SCANCODE_RIGHT, &strafe_right_callback_engine);
                action_mode_input_mode->set_continuous_keypress_callback_engine(SDL_SCANCODE_SPACE, &ascent_callback_engine);
                action_mode_input_mode->set_continuous_keypress_callback_engine(SDL_SCANCODE_RETURN, &descent_callback_engine);
                action_mode_input_mode->activate();

                // Keyrelease callbacks for `my_console`.
                // Key releases are checked in the order of this struct.
                yli::input::InputMode* const my_console_mode_input_mode = input_master->create_input_mode();
                my_console_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_LCTRL, &my_release_left_control_in_console_callback_engine);
                my_console_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_RCTRL, &my_release_right_control_in_console_callback_engine);
                my_console_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_LALT, &my_release_left_alt_in_console_callback_engine);
                my_console_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_RALT, &my_release_right_alt_in_console_callback_engine);
                my_console_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_LSHIFT, &my_release_left_shift_in_console_callback_engine);
                my_console_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_RSHIFT, &my_release_right_shift_in_console_callback_engine);
                my_console_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_UP, &my_enable_move_to_previous_input_callback_engine);
                my_console_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_DOWN, &my_enable_move_to_next_input_callback_engine);
                my_console_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_BACKSPACE, &my_enable_backspace_callback_engine);
                my_console_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_TAB, &my_enable_tab_callback_engine);
                my_console_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_RETURN, &my_enable_enter_key_callback_engine);
                my_console_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_C, &my_enable_ctrl_c_callback_engine);
                my_console_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_W, &my_enable_ctrl_w_callback_engine);
                my_console_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_PAGEUP, &my_enable_page_up_callback_engine);
                my_console_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_PAGEDOWN, &my_enable_page_down_callback_engine);
                my_console_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_HOME, &my_enable_home_callback_engine);
                my_console_mode_input_mode->set_keyrelease_callback_engine(SDL_SCANCODE_END, &my_enable_end_callback_engine);

                // Keypress callbacks for `my_console`.
                // Keypresses are checked in the order of this struct.
                my_console_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_GRAVE, &my_exit_console_callback_engine);
                my_console_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_LCTRL, &my_press_left_control_in_console_callback_engine);
                my_console_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_RCTRL, &my_press_right_control_in_console_callback_engine);
                my_console_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_LALT, &my_press_left_alt_in_console_callback_engine);
                my_console_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_RALT, &my_press_right_alt_in_console_callback_engine);
                my_console_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_LSHIFT, &my_press_left_shift_in_console_callback_engine);
                my_console_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_RSHIFT, &my_press_right_shift_in_console_callback_engine);
                my_console_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_UP, &my_move_to_previous_input_callback_engine);
                my_console_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_DOWN, &my_move_to_next_input_callback_engine);
                my_console_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_BACKSPACE, &my_backspace_callback_engine);
                my_console_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_TAB, &my_tab_callback_engine);
                my_console_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_RETURN, &my_enter_callback_engine);
                my_console_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_C, &my_ctrl_c_callback_engine);
                my_console_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_W, &my_ctrl_w_callback_engine);
                my_console_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_PAGEUP, &my_page_up_callback_engine);
                my_console_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_PAGEDOWN, &my_page_down_callback_engine);
                my_console_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_HOME, &my_home_callback_engine);
                my_console_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_END, &my_end_callback_engine);
                my_console->set_input_mode(my_console_mode_input_mode);

                /*********************************************************************
                 * Callback engines for console commands begin here.                 *
                 * These define what commands there are available in the console     *
                 * and what each command does.                                       *
                 *********************************************************************/

                std::cout << "Defining console command callback engines.\n";

                // Variable callbacks.
                yli::ontology::create_lisp_function_overload("variables", my_console, std::function(&yli::ontology::Entity::print_variables0));
                yli::ontology::create_lisp_function_overload("variables", my_console, std::function(&yli::ontology::Entity::print_variables1));
                yli::ontology::create_lisp_function_overload("create-variable", my_console, std::function(&yli::ontology::Entity::create_variable_with_parent_name_type_value));
                yli::ontology::create_lisp_function_overload("set", my_console, std::function(&yli::ontology::Variable::set_variable_const_std_string));
                yli::ontology::create_lisp_function_overload("copy", my_console, std::function(&yli::ontology::Variable::set_variable_variable));
                yli::ontology::create_lisp_function_overload("print", my_console, std::function(&yli::ontology::Variable::print_value1));

                // Object callbacks.
                yli::ontology::create_lisp_function_overload("create-object", my_console, std::function(&yli::ontology::Object::create_object_with_parent_name_x_y_z));
                yli::ontology::create_lisp_function_overload("create-object", my_console, std::function(&yli::ontology::Object::create_object_with_parent_name_x_y_z_yaw_pitch));
                yli::ontology::create_lisp_function_overload("create-object", my_console, std::function(&yli::ontology::Object::create_object_with_parent_name_x_y_z_roll_yaw_pitch));

                // Holobiont callbacks.
                yli::ontology::create_lisp_function_overload("create-holobiont", my_console, std::function(&yli::ontology::Holobiont::create_holobiont_with_parent_name_x_y_z));
                yli::ontology::create_lisp_function_overload("create-holobiont", my_console, std::function(&yli::ontology::Holobiont::create_holobiont_with_parent_name_x_y_z_yaw_pitch));
                yli::ontology::create_lisp_function_overload("create-holobiont", my_console, std::function(&yli::ontology::Holobiont::create_holobiont_with_parent_name_x_y_z_roll_yaw_pitch));

                // `Entity` handling callbacks.
                yli::ontology::create_lisp_function_overload("entities", my_console, std::function(&yli::ontology::Universe::print_entities));
                yli::ontology::create_lisp_function_overload("parent", my_console, std::function(&yli::ontology::Universe::print_parent));
                yli::ontology::create_lisp_function_overload("children", my_console, std::function(&yli::ontology::Entity::print_children));
                yli::ontology::create_lisp_function_overload("activate", my_console, std::function(&yli::ontology::Universe::activate_entity));
                yli::ontology::create_lisp_function_overload("delete", my_console, std::function(&yli::ontology::Universe::delete_entity));
                yli::ontology::create_lisp_function_overload("info", my_console, std::function(&yli::ontology::Universe::info0));
                yli::ontology::create_lisp_function_overload("info", my_console, std::function(&yli::ontology::Universe::info1));
                yli::ontology::create_lisp_function_overload("bind", my_console, std::function(&yli::ontology::Universe::bind));
                yli::ontology::create_lisp_function_overload("set-global-name", my_console, std::function(&yli::ontology::Universe::set_global_name_for_entity));
                yli::ontology::create_lisp_function_overload("set-local-name", my_console, std::function(&yli::ontology::Universe::set_local_name_for_entity));

                // Exit program callbacks.
                yli::ontology::create_lisp_function_overload("bye", my_console, std::function(&yli::snippets::quit));
                yli::ontology::create_lisp_function_overload("chau", my_console, std::function(&yli::snippets::quit));
                yli::ontology::create_lisp_function_overload("ciao", my_console, std::function(&yli::snippets::quit));
                yli::ontology::create_lisp_function_overload("heippa", my_console, std::function(&yli::snippets::quit));
                yli::ontology::create_lisp_function_overload("quit", my_console, std::function(&yli::snippets::quit));
                yli::ontology::create_lisp_function_overload("sayonara", my_console, std::function(&yli::snippets::quit));

                // Other callbacks.
                // my_console->add_command_callback("eval", &yli::ontology::Universe::eval);
                yli::ontology::create_lisp_function_overload("help", my_console, std::function(&yli::snippets::help));
                yli::ontology::create_lisp_function_overload("version", my_console, std::function(&hirvi::version));
                yli::ontology::create_lisp_function_overload("clear", my_console, std::function(&yli::ontology::Console::clear));
                yli::ontology::create_lisp_function_overload("screenshot", my_console, std::function(&yli::ontology::Universe::screenshot));

                if (audio_master != nullptr)
                {
                    audio_master->add_to_playlist("Hirvi_playlist", "414257__sss-samples__chipland-loop-120-bpm-a-major.wav");
                    audio_master->add_to_playlist("Hirvi_playlist", "414270__greek555__sample-97-bpm.wav");
                    audio_master->play_playlist("Hirvi_playlist");
                }

                std::cout << "Setting up window size ...\n";
                yli::snippets::set_window_size(my_universe, my_universe->get_window_width(), my_universe->get_window_height());
                std::cout << "Setting up framebuffer size ...\n";
                yli::snippets::set_framebuffer_size(my_universe, my_universe->framebuffer_module.get_texture_width(), my_universe->framebuffer_module.get_texture_height());
                std::cout << "Setting up background colors ...\n";
                yli::snippets::set_background_colors(my_universe, 0.0f, 0.0f, 1.0f, 0.0f);
                std::cout << "Setting up wireframe state ...\n";
                yli::snippets::set_wireframe(my_universe, false);
                std::cout << "Setting up movement ...\n";
                yli::snippets::set_movement(my_universe, my_universe->speed, my_universe->turbo_factor, my_universe->twin_turbo_factor, my_universe->mouse_speed);
                std::cout << "Setting up location and orientation ...\n";
                yli::snippets::set_location_and_orientation(my_universe, -5682.32f, -1641.20f, 2376.45f, 100.0f, 100.0f, 100.0f);
                std::cout << "Setting up debug variables ...\n";
                yli::snippets::set_flight_mode(my_universe, true);

                my_universe->start_simulation();
                return true;
            }
    };
}

namespace yli::core
{
    yli::core::Application* create_application(const int argc, const char* const argv[])
    {
        return new hirvi::HirviApplication(argc, argv);
    }
}
