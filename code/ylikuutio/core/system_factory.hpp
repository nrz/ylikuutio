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
                        yli::memory::MemorySystem<TypeEnumType>& memory_system)
                    : memory_system { memory_system }
                {
                }

                yli::event::EventSystem* create_event_system(yli::ontology::Universe& universe)
                {
                    using EventSystemMemoryAllocator = yli::memory::MemoryAllocator<yli::event::EventSystem, 1>;

                    yli::memory::GenericMemoryAllocator& generic_allocator =
                        this->memory_system.template get_or_create_allocator<EventSystemMemoryAllocator>(
                                static_cast<int>(yli::data::Datatype::EVENT_SYSTEM));
                    EventSystemMemoryAllocator& allocator = static_cast<EventSystemMemoryAllocator&>(generic_allocator);

                    return allocator.build_in(universe);
                }

                yli::input::InputSystem* create_input_system(yli::ontology::Universe& universe)
                {
                    using InputSystemMemoryAllocator = yli::memory::MemoryAllocator<yli::input::InputSystem, 1>;

                    yli::memory::GenericMemoryAllocator& generic_allocator =
                        this->memory_system.template get_or_create_allocator<InputSystemMemoryAllocator>(
                                static_cast<int>(yli::data::Datatype::INPUT_SYSTEM));
                    InputSystemMemoryAllocator& allocator = static_cast<InputSystemMemoryAllocator&>(generic_allocator);

                    return allocator.build_in(universe);
                }

                yli::audio::AudioSystem* create_audio_system(yli::ontology::Universe& universe)
                {
                    using AudioSystemMemoryAllocator = yli::memory::MemoryAllocator<yli::audio::AudioSystem, 1>;

                    yli::memory::GenericMemoryAllocator& generic_allocator =
                        this->memory_system.template get_or_create_allocator<AudioSystemMemoryAllocator>(
                                static_cast<int>(yli::data::Datatype::AUDIO_SYSTEM));
                    AudioSystemMemoryAllocator& allocator = static_cast<AudioSystemMemoryAllocator&>(generic_allocator);

                    return allocator.build_in(universe);
                }

            private:
                yli::memory::MemorySystem<TypeEnumType>& memory_system;
        };
}

#endif
