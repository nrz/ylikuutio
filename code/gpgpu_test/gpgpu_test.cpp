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
#include "code/ajokki/ajokki_keyboard_callbacks.hpp"
#include "code/ylikuutio/input/input.hpp"
#include "code/ylikuutio/callback_system/callback_object.hpp"
#include "code/ylikuutio/callback_system/callback_engine.hpp"
#include "code/ylikuutio/callback_system/callback_magic_numbers.hpp"
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

int main(void)
{
    // keypress callbacks.
    std::vector<KeyAndCallbackStruct> action_mode_keypress_callback_engines = std::vector<KeyAndCallbackStruct>();

    // This vector points to current keypress callback engines vector.
    std::vector<KeyAndCallbackStruct>* current_keypress_callback_engine_vector_pointer = &action_mode_keypress_callback_engines;

    // Create the `Universe`, store it in `my_universe`.
    std::cout << "Creating yli::ontology::Entity* my_universe_entity ...\n";
    UniverseStruct universe_struct;
    universe_struct.window_title = "GPGPU test 0.0.1, powered by Ylikuutio 0.0.3";
    universe_struct.current_keypress_callback_engine_vector_pointer_pointer = &current_keypress_callback_engine_vector_pointer;
    universe_struct.window_width = 512;
    universe_struct.window_height = 512;
    yli::ontology::Universe* const my_universe = new yli::ontology::Universe(universe_struct);
    my_universe->set_name("universe");

    yli::ontology::EntityFactory* const entity_factory = my_universe->get_entity_factory();

    std::cout << "Creating yli::callback_system::CallbackEngine* cleanup_callback_engine ...\n";
    yli::callback_system::CallbackEngine cleanup_callback_engine = yli::callback_system::CallbackEngine();
    new yli::callback_system::CallbackObject(nullptr, &cleanup_callback_engine);

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
    yli::callback_system::CallbackEngine* const exit_program_callback_engine = new yli::callback_system::CallbackEngine();
    new yli::callback_system::CallbackObject(&ajokki::exit_program, exit_program_callback_engine);

    // Keypress callbacks for action mode.
    // Keypresses are checked in the order of this struct.
    action_mode_keypress_callback_engines.push_back(KeyAndCallbackStruct { SDL_SCANCODE_ESCAPE, exit_program_callback_engine });

    // For speed computation
    double last_time_to_display_FPS = yli::time::get_time();
    double last_time_for_display_sync = yli::time::get_time();
    int32_t number_of_frames = 0;

    bool is_exit_requested = false;

    SDL_Event sdl_event;
    std::string ms_frame_text;

    while (!is_exit_requested)
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

            // poll all SDL events.
            while (SDL_PollEvent(&sdl_event))
            {
                if (sdl_event.type == SDL_KEYDOWN)
                {
                    uint32_t scancode = static_cast<std::uint32_t>(sdl_event.key.keysym.scancode);

                    for (std::size_t i = 0; i < current_keypress_callback_engine_vector_pointer->size(); i++)
                    {
                        if (current_keypress_callback_engine_vector_pointer->at(i).keycode == scancode)
                        {
                            yli::callback_system::CallbackEngine* const callback_engine = current_keypress_callback_engine_vector_pointer->at(i).callback_engine;
                            const std::shared_ptr<yli::datatypes::AnyValue> any_value = callback_engine->execute();

                            if (any_value != nullptr &&
                                    any_value->type == yli::datatypes::UINT32_T)
                            {
                                if (any_value->uint32_t_value == EXIT_PROGRAM_MAGIC_NUMBER)
                                {
                                    is_exit_requested = true;
                                }

                                // process no more than 1 callback for each keypress.
                                break;
                            }
                        }
                    }
                }
                else if (sdl_event.type == SDL_QUIT)
                {
                    is_exit_requested = true;
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
