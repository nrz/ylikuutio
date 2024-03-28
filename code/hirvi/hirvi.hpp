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

#ifndef HIRVI_HIRVI_HPP_INCLUDED
#define HIRVI_HIRVI_HPP_INCLUDED

#include "datatype.hpp"
#include "cat.hpp"
#include "police_car.hpp"
#include "datatype.hpp"
#include "code/ylikuutio/core/application.hpp"
#include "code/ylikuutio/core/system_factory.hpp"
#include "code/ylikuutio/memory/memory_system.hpp"
#include "code/ylikuutio/memory/memory_allocator.hpp"
#include "code/ylikuutio/ontology/entity_factory.hpp"

// Include standard headers
#include <memory> // std::unique_ptr
#include <string> // std::string
#include <vector> // std::vector

namespace yli::audio
{
    class AudioSystem;
}

namespace yli::memory
{
    class GenericMemorySystem;
    class GenericMemoryAllocator;
}

namespace yli::ontology
{
    class Entity;
    class Universe;
    class Ecosystem;
    class Scene;
    class GenericEntityFactory;
    struct UniverseStruct;
}

namespace hirvi
{
    // Allocators for custom types.
    using CatMemoryAllocator       = yli::memory::MemoryAllocator<hirvi::Cat, 256>;
    using PoliceCarMemoryAllocator = yli::memory::MemoryAllocator<hirvi::PoliceCar, 256>;

    class HirviApplication final : public yli::core::Application
    {
        public:
            HirviApplication(const int argc, const char* const argv[]);

            ~HirviApplication() = default;

            std::string get_name() const override;

            std::vector<std::string> get_valid_keys() const override;

            yli::memory::GenericMemorySystem& get_generic_memory_system() const override;

            yli::memory::MemorySystem<hirvi::Datatype>& get_memory_system() const;

            yli::memory::GenericMemoryAllocator& get_memory_allocator(const int type) const override;

            yli::ontology::GenericEntityFactory& get_generic_entity_factory() const override;

            bool is_universe(yli::ontology::Entity* entity) const override;

            yli::ontology::Universe& get_universe() const override;

            yli::ontology::UniverseStruct get_universe_struct() const;

            bool create_simulation() override;

        private:
            void create_memory_allocators();
            yli::ontology::Ecosystem* create_earth_ecosystem();
            yli::ontology::Scene* create_helsinki_east_downtown_scene();

            yli::memory::MemorySystem<hirvi::Datatype> memory_system;

        public:
            yli::ontology::EntityFactory<hirvi::Datatype> entity_factory;

        private:
            yli::core::SystemFactory<hirvi::Datatype> system_factory;
            yli::ontology::Universe* const universe     { nullptr };
            yli::audio::AudioSystem* const audio_system { nullptr };
    };
}

namespace yli::core
{
    std::unique_ptr<yli::core::Application> create_application(const int argc, const char* const argv[]);
}

#endif
