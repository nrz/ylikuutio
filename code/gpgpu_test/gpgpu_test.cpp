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

#include "gpgpu_test_scene.hpp"
#include "code/ylikuutio/snippets/keyboard_callback_snippets.hpp"
#include "code/ylikuutio/input/input.hpp"
#include "code/ylikuutio/callback/callback_object.hpp"
#include "code/ylikuutio/callback/callback_engine.hpp"
#include "code/ylikuutio/callback/callback_magic_numbers.hpp"
#include "code/ylikuutio/command_line/command_line_master.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/font2D.hpp"
#include "code/ylikuutio/ontology/world.hpp"
#include "code/ylikuutio/ontology/world_struct.hpp"
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
#include <exception>     // try, catch, std::exception
#include <iostream>      // std::cout, std::cin, std::cerr
#include <sstream>       // std::istringstream, std::ostringstream, std::stringstream

int main(const int argc, const char* const argv[]) try
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
    my_universe->set_global_name("universe");

    yli::ontology::EntityFactory* const entity_factory = my_universe->get_entity_factory();

    std::cout << "Creating yli::callback::CallbackEngine cleanup_callback_engine ...\n";
    yli::callback::CallbackEngine cleanup_callback_engine = yli::callback::CallbackEngine();
    cleanup_callback_engine.create_callback_object(nullptr);

    if (my_universe->get_window() == nullptr)
    {
        std::cerr << "Failed to open SDL window.\n";
        return -1;
    }

    my_universe->create_context_and_make_it_current();

    // Initialize GLEW.
    if (!yli::opengl::init_glew())
    {
        cleanup_callback_engine.execute(nullptr);
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

    yli::ontology::WorldStruct world_struct;

    std::cout << "Creating yli::ontology::Entity* gpgpu_test_world_entity ...\n";
    yli::ontology::Entity* const gpgpu_test_world_entity = entity_factory->create_world(world_struct);
    std::cout << "Creating yli::ontology::World* gpgpu_test_world ...\n";
    yli::ontology::World* const gpgpu_test_world = dynamic_cast<yli::ontology::World*>(gpgpu_test_world_entity);

    if (gpgpu_test_world == nullptr)
    {
        return -1;
    }

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

    if (gpgpu_test_scene == nullptr)
    {
        cleanup_callback_engine.execute(nullptr);
        return -1;
    }

    // Set `gpgpu_test_scene` to be the currently active `Scene`.
    std::cout << "Setting gpgpu_test_scene as the active scene ...\n";
    my_universe->set_active_scene(gpgpu_test_scene);

    // GPGPU test `Scene` ends here.

    // Clear the screen.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render the `Universe`.
    my_universe->render();

    // do cleanup.
    cleanup_callback_engine.execute(nullptr);

    return 0;
}
catch (const std::exception& exception)
{
    std::cerr << "ERROR: exception: " << exception.what() << "\n";
}
