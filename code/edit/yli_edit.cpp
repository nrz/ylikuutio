// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
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

#include "yli_edit_console_callbacks.hpp"
#include "code/ylikuutio/audio/audio_master.hpp"
#include "code/ylikuutio/callback/callback_parameter.hpp"
#include "code/ylikuutio/callback/callback_object.hpp"
#include "code/ylikuutio/callback/callback_engine.hpp"
#include "code/ylikuutio/callback/callback_magic_numbers.hpp"
#include "code/ylikuutio/command_line/command_line_master.hpp"
#include "code/ylikuutio/console/console_callback_engine.hpp"
#include "code/ylikuutio/console/console_callback_object.hpp"
#include "code/ylikuutio/core/entrypoint.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/data/pi.hpp"
#include "code/ylikuutio/input/input.hpp"
#include "code/ylikuutio/input/input_master.hpp"
#include "code/ylikuutio/input/input_mode.hpp"

// `yli::ontology` files included in the canonical order.
#include "code/ylikuutio/ontology/entity.hpp"
#include "code/ylikuutio/ontology/application.hpp"
#include "code/ylikuutio/ontology/variable.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/world.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/font2D.hpp"
#include "code/ylikuutio/ontology/text2D.hpp"
#include "code/ylikuutio/ontology/console.hpp"
#include "code/ylikuutio/ontology/variable_struct.hpp"
#include "code/ylikuutio/ontology/universe_struct.hpp"
#include "code/ylikuutio/ontology/world_struct.hpp"
#include "code/ylikuutio/ontology/console_struct.hpp"
#include "code/ylikuutio/ontology/font_struct.hpp"
#include "code/ylikuutio/ontology/text_struct.hpp"
#include "code/ylikuutio/ontology/entity_factory.hpp"
#include "code/ylikuutio/ontology/entity_factory_templates.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"
#include "code/ylikuutio/opengl/vboindexer.hpp"
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

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

#include "SDL.h"

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
#include <iostream>      // std::cout, std::cin, std::cerr
#include <memory>        // std::make_shared, std::shared_ptr
#include <sstream>       // std::istringstream, std::ostringstream, std::stringstream
#include <stdint.h>      // uint32_t etc.
#include <string>        // std::string
#include <utility>       // std::pair
#include <vector>        // std::vector

namespace yli_edit
{
    class YliEditApplication: public yli::ontology::Application
    {
        public:
            YliEditApplication(const int argc, const char* const argv[])
                : yli::ontology::Application(argc, argv)
            {
                // constructor.

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli_edit::YliEditApplication*";
            }

            ~YliEditApplication()
            {
                // destructor.
            }

            std::pair<bool, std::shared_ptr<yli::ontology::UniverseStruct>> get_universe_struct() override
            {
                if (this->command_line_master.is_key("version"))
                {
                    std::cout << "YliEdit " << yli::ontology::Universe::version << ", powered by Ylikuutio " << yli::ontology::Universe::version << "\n";
                    return std::pair(true, nullptr);
                }

                this->command_line_master.print_keys_and_values();

                if (!this->command_line_master.get_are_arguments_valid())
                {
                    // Some of the arguments do not comply with the Ylikuutio argument syntax.
                    std::cerr << "ERROR: Invalid syntax used in command line parameters.\n";
                    return std::pair(false, nullptr);
                }

                const std::vector<std::string> valid_keys {
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

                const std::vector<std::string> invalid_keys = this->command_line_master.get_invalid_keys(valid_keys);

                if (!this->command_line_master.check_keys(valid_keys))
                {
                    std::cerr << "ERROR: 1 or more invalid command line parameters given.\n";

                    const std::vector<std::string> invalid_keys = this->command_line_master.get_invalid_keys(valid_keys);

                    for (std::vector<std::string>::const_iterator it = invalid_keys.begin(); it != invalid_keys.end(); it++)
                    {
                        std::cerr << "Invalid key: " << *it << "\n";
                    }

                    return std::pair(false, nullptr);
                }

                // Create the `Universe`, store it in `my_universe`.
                std::cout << "Creating yli::ontology::Entity* my_universe_entity ...\n";
                std::shared_ptr<yli::ontology::UniverseStruct> universe_struct_shared_ptr = std::make_shared<yli::ontology::UniverseStruct>();
                std::stringstream window_title_stringstream;
                window_title_stringstream << "YliEdit " << yli::ontology::Universe::version << ", powered by Ylikuutio " << yli::ontology::Universe::version;
                universe_struct_shared_ptr->window_title = window_title_stringstream.str();

                if (this->command_line_master.is_key("silent"))
                {
                    universe_struct_shared_ptr->is_silent = true;
                }

                if (this->command_line_master.is_key("fullscreen"))
                {
                    universe_struct_shared_ptr->is_fullscreen = true;
                }

                if (this->command_line_master.is_key("headless"))
                {
                    universe_struct_shared_ptr->is_headless = true;
                }

                if (this->command_line_master.is_key("window_width") &&
                        yli::string::check_if_unsigned_integer_string(this->command_line_master.get_value("window_width")))
                {
                    const std::string window_width = this->command_line_master.get_value("window_width");
                    std::size_t index = 0;
                    universe_struct_shared_ptr->window_width = yli::string::extract_uint32_t_value_from_string(window_width, index, nullptr, nullptr);
                }

                if (this->command_line_master.is_key("window_height") &&
                        yli::string::check_if_unsigned_integer_string(this->command_line_master.get_value("window_height")))
                {
                    const std::string window_height = this->command_line_master.get_value("window_height");
                    std::size_t index = 0;
                    universe_struct_shared_ptr->window_height = yli::string::extract_uint32_t_value_from_string(window_height, index, nullptr, nullptr);
                }

                if (this->command_line_master.is_key("framebuffer_width") &&
                        yli::string::check_if_unsigned_integer_string(this->command_line_master.get_value("framebuffer_width")))
                {
                    const std::string framebuffer_width = this->command_line_master.get_value("framebuffer_width");
                    std::size_t index = 0;
                    universe_struct_shared_ptr->framebuffer_width = yli::string::extract_uint32_t_value_from_string(framebuffer_width, index, nullptr, nullptr);
                }

                if (this->command_line_master.is_key("framebuffer_height") &&
                        yli::string::check_if_unsigned_integer_string(this->command_line_master.get_value("framebuffer_height")))
                {
                    const std::string framebuffer_height = this->command_line_master.get_value("framebuffer_height");
                    std::size_t index = 0;
                    universe_struct_shared_ptr->framebuffer_height = yli::string::extract_uint32_t_value_from_string(framebuffer_height, index, nullptr, nullptr);
                }

                if (this->command_line_master.is_key("speed") &&
                        yli::string::check_if_float_string(this->command_line_master.get_value("speed")))
                {
                    const std::string speed = this->command_line_master.get_value("speed");
                    std::size_t index = 0;
                    universe_struct_shared_ptr->speed = yli::string::extract_float_value_from_string(speed, index, nullptr, nullptr);
                }

                if (this->command_line_master.is_key("turbo_factor") &&
                        yli::string::check_if_float_string(this->command_line_master.get_value("turbo_factor")))
                {
                    const std::string turbo_factor = this->command_line_master.get_value("turbo_factor");
                    std::size_t index = 0;
                    universe_struct_shared_ptr->turbo_factor = yli::string::extract_float_value_from_string(turbo_factor, index, nullptr, nullptr);
                }

                if (this->command_line_master.is_key("twin_turbo_factor") &&
                        yli::string::check_if_float_string(this->command_line_master.get_value("twin_turbo_factor")))
                {
                    const std::string twin_turbo_factor = this->command_line_master.get_value("twin_turbo_factor");
                    std::size_t index = 0;
                    universe_struct_shared_ptr->twin_turbo_factor = yli::string::extract_float_value_from_string(twin_turbo_factor, index, nullptr, nullptr);
                }

                if (this->command_line_master.is_key("mouse_speed") &&
                        yli::string::check_if_float_string(this->command_line_master.get_value("mouse_speed")))
                {
                    const std::string mouse_speed = this->command_line_master.get_value("mouse_speed");
                    std::size_t index = 0;
                    universe_struct_shared_ptr->mouse_speed = yli::string::extract_float_value_from_string(mouse_speed, index, nullptr, nullptr);
                }

                return std::pair(true, universe_struct_shared_ptr);
            }

            bool create_simulation() override
            {
                yli::ontology::Universe* const my_universe = this->get_universe();

                if (my_universe == nullptr)
                {
                    return false;
                }

                my_universe->set_global_name("universe");

                my_universe->application_name = "YliEdit";
                this->set_global_name("yli_edit_application");

                yli::ontology::EntityFactory* const entity_factory = my_universe->get_entity_factory();

                yli::audio::AudioMaster* const audio_master = my_universe->get_audio_master();

                yli::input::InputMaster* const input_master = my_universe->get_input_master();

                if (!my_universe->get_is_headless() && my_universe->get_window() == nullptr)
                {
                    std::cerr << "Failed to open SDL window.\n";
                    return false;
                }

                if (!my_universe->get_is_headless())
                {
                    my_universe->create_context();

                    // Initialize GLEW.
                    if (!yli::opengl::init_glew())
                    {
                        return false;
                    }

                    yli::input::disable_cursor();
                    yli::input::enable_relative_mouse_mode();

                    // Enable depth test.
                    yli::opengl::enable_depth_test();
                    // Accept fragment if it is closer to the camera than the former one.
                    yli::opengl::set_depth_func_to_less();

                    // Cull triangles whose normal is not towards the camera.
                    yli::opengl::cull_triangles();
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

                // Create the `World`.

                yli::ontology::WorldStruct earth_world_struct;
                earth_world_struct.global_name = "earth_world";

                std::cout << "Creating yli::ontology::Entity* earth_world_entity ...\n";
                yli::ontology::Entity* const earth_world_entity = entity_factory->create_world(earth_world_struct);
                std::cout << "Creating yli::ontology::World* earth_world ...\n";
                yli::ontology::World* const earth_world = dynamic_cast<yli::ontology::World*>(earth_world_entity);

                if (earth_world == nullptr)
                {
                    return false;
                }

                std::cout << "Creating yli::ontology::Entity* my_font2D_entity ...\n";

                yli::ontology::FontStruct font_struct;
                font_struct.texture_filename = "Holstein.bmp";
                font_struct.font_texture_file_format = "bmp";
                font_struct.screen_width = my_universe->get_window_width();
                font_struct.screen_height = my_universe->get_window_height();
                font_struct.text_size = my_universe->get_text_size();
                font_struct.font_size = my_universe->get_font_size();

                yli::ontology::Entity* const my_font2D_entity = entity_factory->create_font2d(font_struct);

                std::cout << "Creating yli::ontology::Font2D* my_font2D ...\n";
                yli::ontology::Font2D* const my_font2D = dynamic_cast<yli::ontology::Font2D*>(my_font2D_entity);

                if (my_font2D == nullptr)
                {
                    std::cerr << "Failed to create Font2D.\n";
                    return false;
                }

                std::cout << "Font2D created successfully.\n";
                my_font2D->set_global_name("my_font2D");

                my_universe->set_active_font2D(my_font2D);
                my_console->print_text("Welcome! Please write \"help\" for more");
                my_console->print_text("information.");

                /*********************************************************************
                 *  Callback engines for action mode keyreleases begin here.         *
                 *********************************************************************/

                std::cout << "Defining action mode keyrelease callback engines.\n";

                // Callback code for left Control release: release first turbo.
                yli::callback::CallbackEngine release_first_turbo_callback_engine(my_universe);
                release_first_turbo_callback_engine.create_callback_object(&yli::snippets::release_first_turbo);

                // Callback code for right Control release: release second turbo.
                yli::callback::CallbackEngine release_second_turbo_callback_engine(my_universe);
                release_second_turbo_callback_engine.create_callback_object(&yli::snippets::release_second_turbo);

                // Callback code for I release: enable_toggle invert mouse.
                yli::callback::CallbackEngine enable_toggle_invert_mouse_callback_engine(my_universe);
                enable_toggle_invert_mouse_callback_engine.create_callback_object(&yli::snippets::enable_toggle_invert_mouse);

                // Callback code for F release: enable_toggle flight mode.
                yli::callback::CallbackEngine enable_toggle_flight_mode_callback_engine(my_universe);
                enable_toggle_flight_mode_callback_engine.create_callback_object(&yli::snippets::enable_toggle_flight_mode);

                // Callback code for F1 release: enable toggle help mode.
                yli::callback::CallbackEngine enable_toggle_help_mode_callback_engine(my_universe);
                enable_toggle_help_mode_callback_engine.create_callback_object(&yli::snippets::enable_toggle_help_mode);

                /*********************************************************************
                 *  Callback engines for action mode keypresses begin here.          *
                 *********************************************************************/

                std::cout << "Defining action mode keypress callback engines.\n";

                // Callback code for `SDL_SCANCODE_GRAVE` (tilde key above Tab, usually used for console).
                yli::callback::CallbackEngine enter_console_callback_engine(my_universe);
                enter_console_callback_engine.create_callback_object(&yli::ontology::Console::enter_console);

                // Callback code for esc: exit program.
                yli::callback::CallbackEngine exit_program_callback_engine;
                exit_program_callback_engine.create_callback_object(&yli::snippets::exit_program);

                // Callback code for left Control: first turbo.
                yli::callback::CallbackEngine first_turbo_callback_engine(my_universe);
                first_turbo_callback_engine.create_callback_object(&yli::snippets::first_turbo);

                // Callback code for right Control: second turbo.
                yli::callback::CallbackEngine second_turbo_callback_engine(my_universe);
                second_turbo_callback_engine.create_callback_object(&yli::snippets::second_turbo);

                // Callback code for key up: move forward.
                yli::callback::CallbackEngine move_forward_callback_engine(my_universe);
                move_forward_callback_engine.create_callback_object(&yli::snippets::move_forward);

                // Callback code for key down: move backward.
                yli::callback::CallbackEngine move_backward_callback_engine(my_universe);
                move_backward_callback_engine.create_callback_object(&yli::snippets::move_backward);

                // Callback code for key left: strafe left.
                yli::callback::CallbackEngine strafe_left_callback_engine(my_universe);
                strafe_left_callback_engine.create_callback_object(&yli::snippets::strafe_left);

                // Callback code for key right: strafe right.
                yli::callback::CallbackEngine strafe_right_callback_engine(my_universe);
                strafe_right_callback_engine.create_callback_object(&yli::snippets::strafe_right);

                // Callback code for space: ascent.
                yli::callback::CallbackEngine ascent_callback_engine(my_universe);
                ascent_callback_engine.create_callback_object(&yli::snippets::ascent);

                // Callback code for enter: descent.
                yli::callback::CallbackEngine descent_callback_engine(my_universe);
                descent_callback_engine.create_callback_object(&yli::snippets::descent);

                // Callback code for I: toggle invert mouse.
                yli::callback::CallbackEngine toggle_invert_mouse_callback_engine(my_universe);
                toggle_invert_mouse_callback_engine.create_callback_object(&yli::snippets::toggle_invert_mouse);

                // Callback code for F: toggle flight mode.
                yli::callback::CallbackEngine toggle_flight_mode_callback_engine(my_universe);
                toggle_flight_mode_callback_engine.create_callback_object(&yli::snippets::toggle_flight_mode);

                // Callback code for F1: toggle help mode.
                yli::callback::CallbackEngine toggle_help_mode_callback_engine(my_universe);
                toggle_help_mode_callback_engine.create_callback_object(&yli::snippets::toggle_help_mode);

                /*********************************************************************
                 *  Callback engines for console keyreleases begin here.             *
                 *********************************************************************/

                std::cout << "Defining console keyrelease callback engines for `my_console`.\n";

                // Callback code for left Control release.
                yli::console::ConsoleCallbackEngine my_release_left_control_in_console_callback_engine;
                my_release_left_control_in_console_callback_engine.create_console_callback_object(&yli::ontology::Console::release_left_control_in_console, my_console);

                // Callback code for right Control release.
                yli::console::ConsoleCallbackEngine my_release_right_control_in_console_callback_engine;
                my_release_right_control_in_console_callback_engine.create_console_callback_object(&yli::ontology::Console::release_right_control_in_console, my_console);

                // Callback code for left Alt release.
                yli::console::ConsoleCallbackEngine my_release_left_alt_in_console_callback_engine;
                my_release_left_alt_in_console_callback_engine.create_console_callback_object(&yli::ontology::Console::release_left_alt_in_console, my_console);

                // Callback code for right Alt release.
                yli::console::ConsoleCallbackEngine my_release_right_alt_in_console_callback_engine;
                my_release_right_alt_in_console_callback_engine.create_console_callback_object(&yli::ontology::Console::release_right_alt_in_console, my_console);

                // Callback code for left Shift release.
                yli::console::ConsoleCallbackEngine my_release_left_shift_in_console_callback_engine;
                my_release_left_shift_in_console_callback_engine.create_console_callback_object(&yli::ontology::Console::release_left_shift_in_console, my_console);

                // Callback code for right Shift release.
                yli::console::ConsoleCallbackEngine my_release_right_shift_in_console_callback_engine;
                my_release_right_shift_in_console_callback_engine.create_console_callback_object(&yli::ontology::Console::release_right_shift_in_console, my_console);

                // Callback code for key up release: enable move to previous input.
                yli::console::ConsoleCallbackEngine my_enable_move_to_previous_input_callback_engine;
                my_enable_move_to_previous_input_callback_engine.create_console_callback_object(&yli::ontology::Console::enable_move_to_previous_input, my_console);

                // Callback code for key down release: enable move to next input.
                yli::console::ConsoleCallbackEngine my_enable_move_to_next_input_callback_engine;
                my_enable_move_to_next_input_callback_engine.create_console_callback_object(&yli::ontology::Console::enable_move_to_next_input, my_console);

                // Callback code for backspace release: enable backspace.
                yli::console::ConsoleCallbackEngine my_enable_backspace_callback_engine;
                my_enable_backspace_callback_engine.create_console_callback_object(&yli::ontology::Console::enable_backspace, my_console);

                // Callback code for enter release: enable Enter key.
                yli::console::ConsoleCallbackEngine my_enable_enter_key_callback_engine;
                my_enable_enter_key_callback_engine.create_console_callback_object(&yli::ontology::Console::enable_enter_key, my_console);

                // Callback code for C release: enable Control-C.
                yli::console::ConsoleCallbackEngine my_enable_ctrl_c_callback_engine;
                my_enable_ctrl_c_callback_engine.create_console_callback_object(&yli::ontology::Console::enable_ctrl_c, my_console);

                // Callback code for W release: enable Control-W.
                yli::console::ConsoleCallbackEngine my_enable_ctrl_w_callback_engine;
                my_enable_ctrl_w_callback_engine.create_console_callback_object(&yli::ontology::Console::enable_ctrl_w, my_console);

                // Callback code for PgUp release: enable PgUp.
                yli::console::ConsoleCallbackEngine my_enable_page_up_callback_engine;
                my_enable_page_up_callback_engine.create_console_callback_object(&yli::ontology::Console::enable_page_up, my_console);

                // Callback code for PgDn release: enable PgDn.
                yli::console::ConsoleCallbackEngine my_enable_page_down_callback_engine;
                my_enable_page_down_callback_engine.create_console_callback_object(&yli::ontology::Console::enable_page_down, my_console);

                // Callback code for Home release: enable Home.
                yli::console::ConsoleCallbackEngine my_enable_home_callback_engine;
                my_enable_home_callback_engine.create_console_callback_object(&yli::ontology::Console::enable_home, my_console);

                // Callback code for End release: enable End.
                yli::console::ConsoleCallbackEngine my_enable_end_callback_engine;
                my_enable_end_callback_engine.create_console_callback_object(&yli::ontology::Console::enable_end, my_console);

                /*********************************************************************
                 *  Callback engines for console keypresses begin here.              *
                 *********************************************************************/

                std::cout << "Defining console keypress callback engines for `my_console`.\n";

                // Callback code for `SDL_SCANCODE_GRAVE` (tilde key above Tab, usually used for console).
                yli::console::ConsoleCallbackEngine my_exit_console_callback_engine;
                my_exit_console_callback_engine.create_console_callback_object(&yli::ontology::Console::exit_console, my_console);

                // Callback code for left Control press.
                yli::console::ConsoleCallbackEngine my_press_left_control_in_console_callback_engine;
                my_press_left_control_in_console_callback_engine.create_console_callback_object(&yli::ontology::Console::press_left_control_in_console, my_console);

                // Callback code for right Control press.
                yli::console::ConsoleCallbackEngine my_press_right_control_in_console_callback_engine;
                my_press_right_control_in_console_callback_engine.create_console_callback_object(&yli::ontology::Console::press_right_control_in_console, my_console);

                // Callback code for left Alt press.
                yli::console::ConsoleCallbackEngine my_press_left_alt_in_console_callback_engine;
                my_press_left_alt_in_console_callback_engine.create_console_callback_object(&yli::ontology::Console::press_left_alt_in_console, my_console);

                // Callback code for right Alt press.
                yli::console::ConsoleCallbackEngine my_press_right_alt_in_console_callback_engine;
                my_press_right_alt_in_console_callback_engine.create_console_callback_object(&yli::ontology::Console::press_right_alt_in_console, my_console);

                // Callback code for left Shift press.
                yli::console::ConsoleCallbackEngine my_press_left_shift_in_console_callback_engine;
                my_press_left_shift_in_console_callback_engine.create_console_callback_object(&yli::ontology::Console::press_left_shift_in_console, my_console);

                // Callback code for right Shift press.
                yli::console::ConsoleCallbackEngine my_press_right_shift_in_console_callback_engine;
                my_press_right_shift_in_console_callback_engine.create_console_callback_object(&yli::ontology::Console::press_right_shift_in_console, my_console);

                // Callback code for key up: move to previous input.
                yli::console::ConsoleCallbackEngine my_move_to_previous_input_callback_engine;
                my_move_to_previous_input_callback_engine.create_console_callback_object(&yli::ontology::Console::move_to_previous_input, my_console);

                // Callback code for key down: move to next input.
                yli::console::ConsoleCallbackEngine my_move_to_next_input_callback_engine;
                my_move_to_next_input_callback_engine.create_console_callback_object(&yli::ontology::Console::move_to_next_input, my_console);

                // Callback code for backspace: delete character left of cursor from current input in console.
                yli::console::ConsoleCallbackEngine my_backspace_callback_engine;
                my_backspace_callback_engine.create_console_callback_object(&yli::ontology::Console::backspace, my_console);

                // Callback code for Enter key.
                yli::console::ConsoleCallbackEngine my_enter_callback_engine;
                my_enter_callback_engine.create_console_callback_object(&yli::ontology::Console::enter_key, my_console);

                // Callback code for C: Control-C.
                yli::console::ConsoleCallbackEngine my_ctrl_c_callback_engine;
                my_ctrl_c_callback_engine.create_console_callback_object(&yli::ontology::Console::ctrl_c, my_console);

                // Callback code for W: Control-W.
                yli::console::ConsoleCallbackEngine my_ctrl_w_callback_engine;
                my_ctrl_w_callback_engine.create_console_callback_object(&yli::ontology::Console::ctrl_w, my_console);

                // Callback code for PgUp.
                yli::console::ConsoleCallbackEngine my_page_up_callback_engine;
                my_page_up_callback_engine.create_console_callback_object(&yli::ontology::Console::page_up, my_console);

                // Callback code for PgDn.
                yli::console::ConsoleCallbackEngine my_page_down_callback_engine;
                my_page_down_callback_engine.create_console_callback_object(&yli::ontology::Console::page_down, my_console);

                // Callback code for Home.
                yli::console::ConsoleCallbackEngine my_home_callback_engine;
                my_home_callback_engine.create_console_callback_object(&yli::ontology::Console::home, my_console);

                // Callback code for End.
                yli::console::ConsoleCallbackEngine my_end_callback_engine;
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
                yli::ontology::create_lisp_function_overload("set", my_console, std::function(&yli::ontology::Variable::set_variable_shared_ptr_string));
                yli::ontology::create_lisp_function_overload("copy", my_console, std::function(&yli::ontology::Variable::set_variable_variable));
                yli::ontology::create_lisp_function_overload("copy-shallow", my_console, std::function(&yli::ontology::Variable::set_shallow_variable_variable));
                yli::ontology::create_lisp_function_overload("print", my_console, std::function(&yli::ontology::Variable::print_value1));

                // Object callbacks.
                yli::ontology::create_lisp_function_overload("create-object", my_console, std::function(&yli::ontology::Object::create_object_with_parent_name_x_y_z));
                yli::ontology::create_lisp_function_overload("create-object", my_console, std::function(&yli::ontology::Object::create_object_with_parent_name_x_y_z_horizontal_angle_vertical_angle));

                // Holobiont callbacks.
                yli::ontology::create_lisp_function_overload("create-holobiont", my_console, std::function(&yli::ontology::Holobiont::create_holobiont_with_parent_name_x_y_z));
                yli::ontology::create_lisp_function_overload("create-holobiont", my_console, std::function(&yli::ontology::Holobiont::create_holobiont_with_parent_name_x_y_z_horizontal_angle_vertical_angle));

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
                yli::ontology::create_lisp_function_overload("version", my_console, std::function(&yli_edit::version));
                yli::ontology::create_lisp_function_overload("clear", my_console, std::function(&yli::ontology::Console::clear));
                yli::ontology::create_lisp_function_overload("screenshot", my_console, std::function(&yli::ontology::Universe::screenshot));

                std::cout << "Setting up window size ...\n";
                yli::snippets::set_window_size(my_universe, my_universe->get_window_width(), my_universe->get_window_height());
                std::cout << "Setting up framebuffer size ...\n";
                yli::snippets::set_framebuffer_size(my_universe, my_universe->get_framebuffer_width(), my_universe->get_framebuffer_height());
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

namespace yli::ontology
{
    yli::ontology::Application* create_application(const int argc, const char* const argv[])
    {
        return new yli_edit::YliEditApplication(argc, argv);
    }
}
