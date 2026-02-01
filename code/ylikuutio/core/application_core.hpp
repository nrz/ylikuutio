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

#ifndef YLIKUUTIO_CORE_APPLICATION_CORE_HPP_INCLUDED
#define YLIKUUTIO_CORE_APPLICATION_CORE_HPP_INCLUDED

#include "code/ylikuutio/data/datatype.hpp"
#include "code/ylikuutio/core/system_factory.hpp"
#include "code/ylikuutio/memory/memory_system.hpp"
#include "code/ylikuutio/memory/memory_allocator.hpp"
#include "code/ylikuutio/ontology/entity_factory.hpp"

namespace yli::audio
{
    class AudioSystem;
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
    struct UniverseStruct;
}

namespace yli::core
{
    class Application;

    class ApplicationCore
    {
        public:
            ApplicationCore(Application& application, const yli::ontology::UniverseStruct& universe_struct);

            yli::ontology::Universe& get_universe() const;

            yli::memory::MemorySystem<yli::data::Datatype> memory_system { yli::data::Datatype::UNIVERSE };
            yli::ontology::EntityFactory<yli::data::Datatype> entity_factory;
            SystemFactory<yli::data::Datatype> system_factory;
            yli::ontology::Universe* const universe     { nullptr };
            yli::event::EventSystem* const event_system { nullptr };
            yli::input::InputSystem* const input_system { nullptr };
            yli::audio::AudioSystem* const audio_system { nullptr };
    };
}

#endif
