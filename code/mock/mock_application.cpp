// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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

    yli::memory::GenericMemorySystem& MockApplication::get_generic_memory_system() const
    {
        return this->memory_system.get();
    }

    yli::memory::GenericMemoryAllocator& MockApplication::get_generic_memory_allocator(const int type) const
    {
        return this->memory_system.get_generic_allocator(type);
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
        if (this->universe == nullptr) [[unlikely]]
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
