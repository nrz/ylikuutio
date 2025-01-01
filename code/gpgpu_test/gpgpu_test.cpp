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

#include "gpgpu_test.hpp"
#include "code/ylikuutio/command_line/command_line_master.hpp"
#include "code/ylikuutio/core/application.hpp"
#include "code/ylikuutio/core/entrypoint.hpp"
#include "code/ylikuutio/data/datatype.hpp"
#include "code/ylikuutio/memory/memory_system.hpp"
#include "code/ylikuutio/memory/memory_allocator.hpp"
#include "code/ylikuutio/render/graphics_api_backend.hpp"

// `yli::ontology` files included in the canonical order.
#include "code/ylikuutio/ontology/entity.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/pipeline.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/symbiosis.hpp"
#include "code/ylikuutio/ontology/holobiont.hpp"
#include "code/ylikuutio/ontology/font_2d.hpp"
#include "code/ylikuutio/ontology/text_2d.hpp"
#include "code/ylikuutio/ontology/text_3d.hpp"
#include "code/ylikuutio/ontology/console.hpp"
#include "code/ylikuutio/ontology/universe_struct.hpp"
#include "code/ylikuutio/ontology/mesh_provider_struct.hpp"
#include "code/ylikuutio/ontology/console_struct.hpp"
#include "code/ylikuutio/ontology/font_struct.hpp"
#include "code/ylikuutio/ontology/text_struct.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.
#include "code/ylikuutio/sdl/ylikuutio_sdl.hpp"

#define SDL_main main

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
    class Entity;
    class GenericEntityFactory;
}

namespace gpgpu_test
{
    static constexpr yli::data::Datatype universe_enum_value = yli::data::Datatype::UNIVERSE;

    GpgpuTestApplication::GpgpuTestApplication(const int argc, const char* const argv[])
        : yli::core::Application(argc, argv),
        memory_system(universe_enum_value),
        entity_factory(*this, this->memory_system),
        universe { this->entity_factory.create_universe(this->get_universe_struct()) }
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

    yli::memory::GenericMemorySystem& GpgpuTestApplication::get_generic_memory_system() const
    {
        return this->memory_system.get();
    }

    yli::memory::GenericMemoryAllocator& GpgpuTestApplication::get_generic_memory_allocator(const int type) const
    {
        return this->memory_system.get_generic_allocator(type);
    }

    yli::ontology::GenericEntityFactory& GpgpuTestApplication::get_generic_entity_factory() const
    {
        return this->entity_factory.get();
    }

    bool GpgpuTestApplication::is_universe(yli::ontology::Entity* entity) const
    {
        return static_cast<yli::ontology::Entity*>(this->universe) == entity;
    }

    yli::ontology::Universe& GpgpuTestApplication::get_universe() const
    {
        if (this->universe == nullptr) [[unlikely]]
        {
            throw std::logic_error("ERROR: `GpgpuTestApplication::get_universe`: `this->universe` is `nullptr`!");
        }

        return *this->universe;
    }

    yli::ontology::UniverseStruct GpgpuTestApplication::get_universe_struct() const
    {
        yli::ontology::UniverseStruct universe_struct(yli::render::GraphicsApiBackend::OPENGL);
        universe_struct.application_name = "GPGPU test";
        universe_struct.window_title = "GPGPU test " + yli::ontology::Universe::version + ", powered by Ylikuutio " + yli::ontology::Universe::version;
        universe_struct.window_width = 2048;
        universe_struct.window_height = 2048;

        return universe_struct;
    }

    bool GpgpuTestApplication::create_simulation()
    {
        this->get_universe().set_global_name("universe");

        if (!this->get_universe().get_is_headless() && this->get_universe().get_window() == nullptr)
        {
            std::cerr << "Failed to open SDL window.\n";
            return false;
        }

        // Create the `Scene`s.

        // GPGPU test `Scene` begins here.

        std::cout << "Creating yli::ontology::Scene* gpgpu_test_scene ...\n";
        yli::ontology::Scene* const gpgpu_test_scene = this->create_gpgpu_test_scene();

        if (gpgpu_test_scene == nullptr)
        {
            return false;
        }

        // Set `gpgpu_test_scene` to be the currently active `Scene`.
        std::cout << "Setting gpgpu_test_scene as the active scene ...\n";
        this->get_universe().set_active_scene(gpgpu_test_scene);

        // GPGPU test `Scene` ends here.

        // Render the `Universe`.
        this->get_universe().render();
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
