// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2019 Antti Nuortimo.
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

#include "gpgpu_test_scene.hpp"
#include "code/app/app_keyboard_callbacks.hpp"
#include "code/ylikuutio/input/input.hpp"
#include "code/ylikuutio/input/input_master.hpp"
#include "code/ylikuutio/input/input_mode.hpp"
#include "code/ylikuutio/callback/callback_object.hpp"
#include "code/ylikuutio/callback/callback_engine.hpp"
#include "code/ylikuutio/callback/callback_magic_numbers.hpp"
#include "code/ylikuutio/command_line/command_line_master.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/font2D.hpp"
#include "code/ylikuutio/ontology/world.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/shader.hpp"
#include "code/ylikuutio/ontology/shader_struct.hpp"
#include "code/ylikuutio/ontology/entity_factory.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"
#include "code/ylikuutio/time/time.hpp"

// Include GLEW
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.

#define SDL_main main

#include "SDL.h"

// Include standard headers
#include <cstddef>       // std::size_t
#include <iomanip>       // std::setfill, std::setprecision, std::setw
#include <iostream>      // std::cout, std::cin, std::cerr
#include <memory>        // std::make_shared, std::shared_ptr
#include <sstream>       // std::istringstream, std::ostringstream, std::stringstream
#include <stdint.h>      // uint32_t etc.
#include <string>        // std::string
#include <vector>        // std::vector

int main(const int argc, const char* const argv[])
{
    yli::command_line::CommandLineMaster command_line_master(argc, argv);

    if (command_line_master.is_key("version"))
    {
        std::cout << "GPGPU test " << yli::ontology::Universe::version << ", powered by Ylikuutio " << yli::ontology::Universe::version << "\n";
        return 0;
    }

    command_line_master.print_keys_and_values();

    // Create the `Universe`, store it in `my_universe`.
    std::cout << "Creating yli::ontology::Entity* my_universe_entity ...\n";
    yli::ontology::UniverseStruct universe_struct;
    std::stringstream window_title_stringstream;
    window_title_stringstream << "GPGPU test " << yli::ontology::Universe::version << ", powered by Ylikuutio " << yli::ontology::Universe::version;
    universe_struct.window_title = window_title_stringstream.str();
    universe_struct.window_width = 512;
    universe_struct.window_height = 512;
    yli::ontology::Universe* const my_universe = new yli::ontology::Universe(universe_struct);
    my_universe->set_name("universe");

    yli::ontology::EntityFactory* const entity_factory = my_universe->get_entity_factory();

    yli::input::InputMaster* const input_master = my_universe->get_input_master();

    std::cout << "Creating yli::callback::CallbackEngine cleanup_callback_engine ...\n";
    yli::callback::CallbackEngine cleanup_callback_engine = yli::callback::CallbackEngine();
    cleanup_callback_engine.create_CallbackObject(nullptr);

    if (my_universe->get_window() == nullptr)
    {
        std::cerr << "Failed to open SDL window.\n";
        return -1;
    }

    my_universe->create_context();

    // Initialize GLEW.
    if (!yli::opengl::init_glew())
    {
        cleanup_callback_engine.execute();
        return -1;
    }

    yli::input::disable_cursor();
    yli::input::enable_relative_mouse_mode();

    // Enable depth test.
    yli::opengl::enable_depth_test();
    // Accept fragment if it closer to the camera than the former one.
    yli::opengl::set_depth_func_to_less();

    // Cull triangles which normal is not towards the camera.
    yli::opengl::cull_triangles();

    // Create the `World`.

    std::cout << "Creating yli::ontology::Entity* gpgpu_test_world_entity ...\n";
    yli::ontology::Entity* const gpgpu_test_world_entity = entity_factory->create_World();
    std::cout << "Creating yli::ontology::World* gpgpu_test_world ...\n";
    yli::ontology::World* const gpgpu_test_world = dynamic_cast<yli::ontology::World*>(gpgpu_test_world_entity);

    if (gpgpu_test_world == nullptr)
    {
        return -1;
    }

    std::cout << "Setting gpgpu_test_world as the active world ...\n";
    my_universe->set_active_world(gpgpu_test_world);

    // Create the `Scene`s.

    // GPGPU test `Scene` begins here.

    std::cout << "Creating yli::ontology::Entity* gpgpu_test_scene_entity and its contents ...\n";
    yli::ontology::Entity* const gpgpu_test_scene_entity = gpgpu_test::create_gpgpu_test_scene(entity_factory, gpgpu_test_world);

    if (gpgpu_test_scene_entity == nullptr)
    {
        return -1;
    }

    std::cout << "Creating yli::ontology::Scene* gpgpu_test_scene ...\n";
    yli::ontology::Scene* const gpgpu_test_scene = dynamic_cast<yli::ontology::Scene*>(gpgpu_test_scene_entity);

    my_universe->is_flight_mode_in_use = true;

    if (gpgpu_test_scene == nullptr)
    {
        cleanup_callback_engine.execute();
        return -1;
    }

    // Set `gpgpu_test_scene` to be the currently active `Scene` in `gpgpu_test_world`.
    std::cout << "Setting gpgpu_test_scene as the active scene ...\n";
    gpgpu_test_world->set_active_scene(gpgpu_test_scene);

    // GPGPU test `Scene` ends here.

    /*********************************************************************
     *  Callback engines for action mode keypresses begin here.          *
     *********************************************************************/

    std::cout << "Defining action mode keypress callback engines.\n";

    // Callback code for esc: exit program.
    yli::callback::CallbackEngine exit_program_callback_engine;
    exit_program_callback_engine.create_CallbackObject(&app::exit_program);

    // Keypress callbacks for action mode.
    // Keypresses are checked in the order of this struct.
    yli::input::InputMode* const action_mode_input_mode = input_master->create_InputMode();
    action_mode_input_mode->set_keypress_callback_engine(SDL_SCANCODE_ESCAPE, &exit_program_callback_engine);

    // For speed computation
    double last_time_to_display_FPS = yli::time::get_time();
    double last_time_for_display_sync = yli::time::get_time();
    int32_t number_of_frames = 0;

    SDL_Event sdl_event;
    std::string ms_frame_text;

    while (!my_universe->get_is_exit_requested())
    {
        const double current_time_in_main_loop = yli::time::get_time();

        if (current_time_in_main_loop - last_time_for_display_sync >= (1.0f / my_universe->get_max_FPS()))
        {
            last_time_for_display_sync = yli::time::get_time();

            number_of_frames++;

            while (current_time_in_main_loop - last_time_to_display_FPS >= 1.0f)
            {
                // If last `std::stringstream` here was more than 1 sec ago,
                // std::stringstream` and reset number of frames.
                if (number_of_frames > 0)
                {
                    std::stringstream ms_frame_text_stringstream;
                    ms_frame_text_stringstream << std::fixed << std::setprecision(2) << 1000.0f / static_cast<double>(number_of_frames) << " ms/frame; " <<
                        number_of_frames << " Hz";
                    ms_frame_text = ms_frame_text_stringstream.str();
                    number_of_frames = 0;
                }

                // `last_time_to_display_FPS` needs to be incremented to avoid infinite loop.
                last_time_to_display_FPS += 1.0f;
            }

            // Clear the screen.
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            my_universe->compute_delta_time();

            const yli::input::InputMode* const input_mode = input_master->get_active_input_mode();

            // poll all SDL events.
            while (SDL_PollEvent(&sdl_event))
            {
                if (sdl_event.type == SDL_KEYDOWN && input_mode != nullptr)
                {
                    const uint32_t scancode = static_cast<std::uint32_t>(sdl_event.key.keysym.scancode);

                    yli::callback::CallbackEngine* const callback_engine = input_mode->get_keypress_callback_engine(scancode);

                    if (callback_engine == nullptr)
                    {
                        continue;
                    }

                    const std::shared_ptr<yli::common::AnyValue> any_value = callback_engine->execute();

                    if (any_value != nullptr &&
                            any_value->type == yli::common::Datatype::UINT32_T)
                    {
                        if (any_value->uint32_t_value == ENTER_CONSOLE_MAGIC_NUMBER)
                        {
                            // Do not display help screen when in console.
                            my_universe->can_display_help_screen = false;
                        }
                        else if (any_value->uint32_t_value == EXIT_CONSOLE_MAGIC_NUMBER)
                        {
                            // Enable display help screen when not in console.
                            my_universe->can_display_help_screen = true;
                        }
                        else if (any_value->uint32_t_value == EXIT_PROGRAM_MAGIC_NUMBER)
                        {
                            my_universe->request_exit();
                        }
                    }
                }
                else if (sdl_event.type == SDL_QUIT)
                {
                    my_universe->request_exit();
                }
            }

            // Render the `Universe`.
            my_universe->render();

            my_universe->finalize_delta_time_loop();
        }
    }

    // do cleanup.
    cleanup_callback_engine.execute();

    return 0;
}
