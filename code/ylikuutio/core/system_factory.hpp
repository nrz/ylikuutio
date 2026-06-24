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

#ifndef YLIKUUTIO_CORE_SYSTEM_FACTORY_HPP_INCLUDED
#define YLIKUUTIO_CORE_SYSTEM_FACTORY_HPP_INCLUDED

#include "code/ylikuutio/event/event_system.hpp"
#include "code/ylikuutio/input/input_system.hpp"
#include "code/ylikuutio/audio/audio_system.hpp"
#include "code/ylikuutio/memory/memory_system.hpp"

namespace yli::ontology
{
    class Universe;
}

namespace yli::core
{
    template<typename TypeEnumType>
        class SystemFactory
        {
            public:
                explicit SystemFactory(
                        memory::MemorySystem<TypeEnumType>& memory_system)
                    : memory_system { memory_system }
                {
                }

                event::EventSystem* create_event_system(ontology::Universe& universe)
                {
                    using EventSystemMemoryAllocator = memory::MemoryAllocator<event::EventSystem, 1>;

                    memory::GenericMemoryAllocator& generic_allocator =
                        this->memory_system.template get_or_create_allocator<EventSystemMemoryAllocator>(
                                static_cast<int>(data::Datatype::EVENT_SYSTEM));
                    auto& allocator = static_cast<EventSystemMemoryAllocator&>(generic_allocator);

                    return allocator.build_in(universe);
                }

                input::InputSystem* create_input_system(ontology::Universe& universe)
                {
                    using InputSystemMemoryAllocator = memory::MemoryAllocator<input::InputSystem, 1>;

                    memory::GenericMemoryAllocator& generic_allocator =
                        this->memory_system.template get_or_create_allocator<InputSystemMemoryAllocator>(
                                static_cast<int>(data::Datatype::INPUT_SYSTEM));
                    auto& allocator = static_cast<InputSystemMemoryAllocator&>(generic_allocator);

                    return allocator.build_in(universe);
                }

                audio::AudioSystem* create_audio_system(ontology::Universe& universe)
                {
                    using AudioSystemMemoryAllocator = memory::MemoryAllocator<audio::AudioSystem, 1>;

                    memory::GenericMemoryAllocator& generic_allocator =
                        this->memory_system.template get_or_create_allocator<AudioSystemMemoryAllocator>(
                                static_cast<int>(data::Datatype::AUDIO_SYSTEM));
                    auto& allocator = static_cast<AudioSystemMemoryAllocator&>(generic_allocator);

                    return allocator.build_in(universe);
                }

            private:
                memory::MemorySystem<TypeEnumType>& memory_system;
        };
}

#endif
