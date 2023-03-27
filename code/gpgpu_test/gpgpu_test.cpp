// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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

#include "gpgpu_test.hpp"
#include "gpgpu_test_scene.hpp"
#include "code/ylikuutio/command_line/command_line_master.hpp"
#include "code/ylikuutio/core/application.hpp"
#include "code/ylikuutio/core/entrypoint.hpp"
#include "code/ylikuutio/render/graphics_api_backend.hpp"

// `yli::ontology` files included in the canonical order.
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/entity_factory.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.
#include "code/ylikuutio/sdl/ylikuutio_sdl.hpp"

#define SDL_main main

// Include standard headers
#include <exception>     // try, catch, std::exception
#include <iostream>      // std::cout, std::cin, std::cerr
#include <memory>        // std::make_unique, std::unique_ptr
#include <sstream>       // std::istringstream, std::ostringstream, std::stringstream

namespace yli::ontology
{
    class Entity;
}

namespace gpgpu_test
{
    GpgpuTestApplication::GpgpuTestApplication(const int argc, const char* const argv[])
        : yli::core::Application(argc, argv)
    {
        std::cout << "GpgpuTestApplication initialized!\n";
    }

    std::string GpgpuTestApplication::get_name() const
    {
        return "GPGPU test";
    }

    std::vector<std::string> GpgpuTestApplication::get_valid_keys() const
    {
        return { "help", "version" };
    }

    yli::ontology::UniverseStruct GpgpuTestApplication::get_universe_struct() const
    {
        yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::OPENGL);
        std::stringstream window_title_stringstream;
        window_title_stringstream << "GPGPU test " << yli::ontology::Universe::version << ", powered by Ylikuutio " << yli::ontology::Universe::version;
        universe_struct.application_name = "GPGPU test";
        universe_struct.window_title = window_title_stringstream.str();
        universe_struct.window_width = 512;
        universe_struct.window_height = 512;

        return universe_struct;
    }

    bool GpgpuTestApplication::create_simulation()
    {
        yli::ontology::Universe* const my_universe = this->get_universe();

        if (my_universe == nullptr)
        {
            return false;
        }

        my_universe->set_global_name("universe");

        yli::ontology::EntityFactory& entity_factory = my_universe->get_entity_factory();

        if (!my_universe->get_is_headless() && my_universe->get_window() == nullptr)
        {
            std::cerr << "Failed to open SDL window.\n";
            return false;
        }

        // Create the `Scene`s.

        // GPGPU test `Scene` begins here.

        std::cout << "Creating yli::ontology::Entity* gpgpu_test_scene_entity and its contents ...\n";
        yli::ontology::Entity* const gpgpu_test_scene_entity = gpgpu_test::create_gpgpu_test_scene(&entity_factory);

        if (gpgpu_test_scene_entity == nullptr)
        {
            return false;
        }

        std::cout << "Creating yli::ontology::Scene* gpgpu_test_scene ...\n";
        yli::ontology::Scene* const gpgpu_test_scene = dynamic_cast<yli::ontology::Scene*>(gpgpu_test_scene_entity);

        if (gpgpu_test_scene == nullptr)
        {
            return false;
        }

        // Set `gpgpu_test_scene` to be the currently active `Scene`.
        std::cout << "Setting gpgpu_test_scene as the active scene ...\n";
        my_universe->set_active_scene(gpgpu_test_scene);

        // GPGPU test `Scene` ends here.

        // Render the `Universe`.
        my_universe->render();
        return true;
    }
}

namespace yli::core
{
    std::unique_ptr<yli::core::Application> create_application(const int argc, const char* const argv[])
    {
        return std::make_unique<gpgpu_test::GpgpuTestApplication>(argc, argv);
    }
}
