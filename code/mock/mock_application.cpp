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

#include "mock_application.hpp"
#include "code/ylikuutio/core/application.hpp"

#ifndef GOOGLE_TEST
// Google Test provides its own `main` entrypoint.
#include "code/ylikuutio/core/entrypoint.hpp"
#endif

#include "code/ylikuutio/data/datatype.hpp"
#include "code/ylikuutio/memory/memory_system.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/universe_struct.hpp"
#include "code/ylikuutio/render/graphics_api_backend.hpp"

// Include standard headers
#include <memory> // std::make_unique, std::unique_ptr
#include <stdexcept> // std::runtime_error
#include <string> // std::string
#include <vector> // std::vector

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

namespace mock
{
    static constexpr yli::data::Datatype universe_enum_value = yli::data::Datatype::UNIVERSE;

    MockApplication::MockApplication()
        : yli::core::Application(0, nullptr),
        memory_system(this, universe_enum_value),
        entity_factory(*this, this->memory_system),
        universe { this->entity_factory.create_universe(this->get_universe_struct()) }
    {
        std::cout << "MockApplication initialized!\n";
    }

    std::vector<std::string> MockApplication::get_valid_keys() const
    {
        return std::vector<std::string>();
    }

    yli::memory::GenericMemorySystem& MockApplication::get_memory_system() const
    {
        return this->memory_system.get();
    }

    void MockApplication::create_memory_allocators()
    {
        this->memory_system.create_allocator<UniverseMemoryAllocator>(yli::data::Datatype::UNIVERSE);
        this->memory_system.create_allocator<CallbackEngineMemoryAllocator>(yli::data::Datatype::CALLBACK_ENGINE);
        this->memory_system.create_allocator<CallbackObjectMemoryAllocator>(yli::data::Datatype::CALLBACK_OBJECT);
        this->memory_system.create_allocator<CallbackParameterMemoryAllocator>(yli::data::Datatype::CALLBACK_PARAMETER);
        this->memory_system.create_allocator<VariableMemoryAllocator>(yli::data::Datatype::VARIABLE);
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
        this->memory_system.create_allocator<ConsoleCallbackEngineMemoryAllocator>(yli::data::Datatype::CONSOLE_CALLBACK_ENGINE);
        this->memory_system.create_allocator<ConsoleCallbackObjectMemoryAllocator>(yli::data::Datatype::CONSOLE_CALLBACK_OBJECT);
        this->memory_system.create_allocator<ComputeTaskMemoryAllocator>(yli::data::Datatype::COMPUTETASK);
        this->memory_system.create_allocator<LispFunctionMemoryAllocator>(yli::data::Datatype::LISP_FUNCTION);
        this->memory_system.create_allocator<GenericLispFunctionOverloadMemoryAllocator>(yli::data::Datatype::GENERIC_LISP_FUNCTION_OVERLOAD);
    }

    yli::memory::GenericMemoryAllocator& MockApplication::get_memory_allocator(const int type) const
    {
        return this->memory_system.get_allocator(type);
    }

    yli::ontology::GenericEntityFactory& MockApplication::get_generic_entity_factory() const
    {
        return this->entity_factory.get();
    }

    bool MockApplication::is_universe(yli::ontology::Entity* entity) const
    {
        return this->universe == entity;
    }

    yli::ontology::Universe& MockApplication::get_universe() const
    {
        if (this->universe == nullptr)
        {
            throw std::runtime_error("ERROR: `MockApplication::get_universe`: `this->universe` is `nullptr`!");
        }

        return *this->universe;
    }

    yli::ontology::UniverseStruct MockApplication::get_universe_struct() const
    {
        return yli::ontology::UniverseStruct(yli::render::GraphicsApiBackend::HEADLESS);
    }

    bool MockApplication::create_simulation()
    {
        // Do nothing.
        return true;
    }
}

namespace yli::core
{
    std::unique_ptr<yli::core::Application> create_application(const int /* argc */, const char* const /* argv */ [])
    {
        return std::make_unique<mock::MockApplication>();
    }
}
