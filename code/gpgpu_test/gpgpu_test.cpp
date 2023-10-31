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
#include "code/ylikuutio/ontology/variable.hpp"
#include "code/ylikuutio/ontology/ecosystem.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/pipeline.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/symbiosis.hpp"
#include "code/ylikuutio/ontology/holobiont.hpp"
#include "code/ylikuutio/ontology/shapeshifter_transformation.hpp"
#include "code/ylikuutio/ontology/font_2d.hpp"
#include "code/ylikuutio/ontology/text_2d.hpp"
#include "code/ylikuutio/ontology/text_3d.hpp"
#include "code/ylikuutio/ontology/console.hpp"
#include "code/ylikuutio/ontology/variable_struct.hpp"
#include "code/ylikuutio/ontology/universe_struct.hpp"
#include "code/ylikuutio/ontology/ecosystem_struct.hpp"
#include "code/ylikuutio/ontology/model_struct.hpp"
#include "code/ylikuutio/ontology/console_struct.hpp"
#include "code/ylikuutio/ontology/font_struct.hpp"
#include "code/ylikuutio/ontology/text_struct.hpp"
#include "code/ylikuutio/opengl/ylikuutio_glew.hpp" // GLfloat, GLuint etc.
#include "code/ylikuutio/sdl/ylikuutio_sdl.hpp"

#define SDL_main main

// Include standard headers
#include <iostream>      // std::cout, std::cin, std::cerr
#include <memory>        // std::make_unique, std::unique_ptr
#include <sstream>       // std::istringstream, std::ostringstream, std::stringstream
#include <stdexcept>     // std::runtime_error

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
        memory_system(this, universe_enum_value),
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

    yli::memory::GenericMemorySystem& GpgpuTestApplication::get_memory_system() const
    {
        return this->memory_system.get();
    }

    void GpgpuTestApplication::create_memory_allocators()
    {
        this->memory_system.create_allocator<UniverseMemoryAllocator>(yli::data::Datatype::UNIVERSE);
        this->memory_system.create_allocator<VariableMemoryAllocator>(yli::data::Datatype::VARIABLE);
        this->memory_system.create_allocator<CallbackEngineMemoryAllocator>(yli::data::Datatype::CALLBACK_ENGINE);
        this->memory_system.create_allocator<CallbackObjectMemoryAllocator>(yli::data::Datatype::CALLBACK_OBJECT);
        this->memory_system.create_allocator<CallbackParameterMemoryAllocator>(yli::data::Datatype::CALLBACK_PARAMETER);
        this->memory_system.create_allocator<CameraMemoryAllocator>(yli::data::Datatype::CAMERA);
        this->memory_system.create_allocator<BrainMemoryAllocator>(yli::data::Datatype::BRAIN);
        this->memory_system.create_allocator<EcosystemMemoryAllocator>(yli::data::Datatype::ECOSYSTEM);
        this->memory_system.create_allocator<SceneMemoryAllocator>(yli::data::Datatype::SCENE);
        this->memory_system.create_allocator<PipelineMemoryAllocator>(yli::data::Datatype::PIPELINE);
        this->memory_system.create_allocator<MaterialMemoryAllocator>(yli::data::Datatype::MATERIAL);
        this->memory_system.create_allocator<SpeciesMemoryAllocator>(yli::data::Datatype::SPECIES);
        this->memory_system.create_allocator<ObjectMemoryAllocator>(yli::data::Datatype::OBJECT);
        this->memory_system.create_allocator<SymbiosisMemoryAllocator>(yli::data::Datatype::SYMBIOSIS);
        this->memory_system.create_allocator<SymbiontMaterialMemoryAllocator>(yli::data::Datatype::SYMBIONT_MATERIAL);
        this->memory_system.create_allocator<SymbiontSpeciesMemoryAllocator>(yli::data::Datatype::SYMBIONT_SPECIES);
        this->memory_system.create_allocator<HolobiontMemoryAllocator>(yli::data::Datatype::HOLOBIONT);
        this->memory_system.create_allocator<BiontMemoryAllocator>(yli::data::Datatype::BIONT);
        this->memory_system.create_allocator<ShapeshifterTransformationMemoryAllocator>(yli::data::Datatype::SHAPESHIFTER_TRANSFORMATION);
        this->memory_system.create_allocator<ShapeshifterSequenceMemoryAllocator>(yli::data::Datatype::SHAPESHIFTER_SEQUENCE);
        this->memory_system.create_allocator<ShapeshifterFormMemoryAllocator>(yli::data::Datatype::SHAPESHIFTER_FORM);
        this->memory_system.create_allocator<Font2DMemoryAllocator>(yli::data::Datatype::FONT_2D);
        this->memory_system.create_allocator<Text2DMemoryAllocator>(yli::data::Datatype::TEXT_2D);
        this->memory_system.create_allocator<VectorFontMemoryAllocator>(yli::data::Datatype::VECTOR_FONT);
        this->memory_system.create_allocator<GlyphMemoryAllocator>(yli::data::Datatype::GLYPH);
        this->memory_system.create_allocator<Text3DMemoryAllocator>(yli::data::Datatype::TEXT_3D);
        this->memory_system.create_allocator<InputModeMemoryAllocator>(yli::data::Datatype::INPUT_MODE);
        this->memory_system.create_allocator<ConsoleMemoryAllocator>(yli::data::Datatype::CONSOLE);
        this->memory_system.create_allocator<ComputeTaskMemoryAllocator>(yli::data::Datatype::COMPUTETASK);
        this->memory_system.create_allocator<LispFunctionMemoryAllocator>(yli::data::Datatype::LISP_FUNCTION);
        this->memory_system.create_allocator<GenericLispFunctionOverloadMemoryAllocator>(yli::data::Datatype::GENERIC_LISP_FUNCTION_OVERLOAD);
    }

    yli::memory::GenericMemoryAllocator& GpgpuTestApplication::get_memory_allocator(const int type) const
    {
        return this->memory_system.get_allocator(type);
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
        if (this->universe == nullptr)
        {
            throw std::runtime_error("ERROR: `GpgpuTestApplication::get_universe`: `this->universe` is `nullptr`!");
        }

        return *this->universe;
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
        this->get_universe().set_global_name("universe");

        if (!this->get_universe().get_is_headless() && this->get_universe().get_window() == nullptr)
        {
            std::cerr << "Failed to open SDL window.\n";
            return false;
        }

        // Create the `Scene`s.

        // GPGPU test `Scene` begins here.

        std::cout << "Creating yli::ontology::Entity* gpgpu_test_scene_entity and its contents ...\n";
        yli::ontology::Entity* const gpgpu_test_scene_entity = this->create_gpgpu_test_scene();

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
