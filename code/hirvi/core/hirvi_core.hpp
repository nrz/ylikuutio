// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2026 Antti Nuortimo.
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

#ifndef HIRVI_HIRVI_CORE_HPP_INCLUDED
#define HIRVI_HIRVI_CORE_HPP_INCLUDED

#include "hirvi_application_callback.hpp"
#include "code/hirvi/data/datatype.hpp"
#include "code/ylikuutio/core/system_factory.hpp"
#include "code/ylikuutio/memory/memory_system.hpp"
#include "code/ylikuutio/memory/memory_allocator.hpp"
#include "code/ylikuutio/ontology/entity_factory.hpp"

namespace yli::audio
{
    class AudioSystem;
}

namespace yli::core
{
    class Application;
}

namespace yli::event
{
    class EventSystem;
}

namespace yli::input
{
    class InputSystem;
}

namespace yli::ontology
{
    class Universe;
    class Ecosystem;
    class Scene;
    struct UniverseStruct;
}

namespace hirvi
{
    class Cat;
    class PoliceCar;

    // Allocators for custom types.
    using CatMemoryAllocator       = yli::memory::MemoryAllocator<hirvi::Cat, 256>;
    using PoliceCarMemoryAllocator = yli::memory::MemoryAllocator<hirvi::PoliceCar, 256>;

    class HirviCore
    {
        public:
            HirviCore(yli::core::Application& application, const yli::ontology::UniverseStruct& universe_struct);

            yli::ontology::Universe& get_universe() const;

            bool create_and_start_simulation(HirviApplicationCallback hirvi_application_callback);

            yli::ontology::Scene* create_helsinki_scene();
            yli::ontology::Ecosystem* create_earth_ecosystem();

            yli::memory::MemorySystem<hirvi::Datatype> memory_system { hirvi::Datatype::UNIVERSE };
            yli::ontology::EntityFactory<hirvi::Datatype> entity_factory;
            yli::core::SystemFactory<hirvi::Datatype> system_factory;
            yli::ontology::Universe* const universe     { nullptr };
            yli::event::EventSystem* const event_system { nullptr };
            yli::input::InputSystem* const input_system { nullptr };
            yli::audio::AudioSystem* const audio_system { nullptr };
    };
}

#endif
