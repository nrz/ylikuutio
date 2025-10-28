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

#ifndef HIRVI_HIRVI_EDIT_HPP_INCLUDED
#define HIRVI_HIRVI_EDIT_HPP_INCLUDED

#include "core/hirvi_core.hpp"
#include "data/datatype.hpp"
#include "ontology/cat.hpp"
#include "ontology/police_car.hpp"
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

namespace yli::event
{
    class EventSystem;
}

namespace yli::input
{
    class InputSystem;
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
    class GenericEntityFactory;
    struct UniverseStruct;
}

namespace hirvi
{
    class HirviEditApplication final : public yli::core::Application
    {
        public:
            HirviEditApplication(const int argc, const char* const argv[]);

            ~HirviEditApplication() = default;

            std::string get_name() const override;

            std::vector<std::string> get_valid_keys() const override;

            yli::memory::GenericMemorySystem& get_generic_memory_system() const override;

            yli::memory::MemorySystem<hirvi::Datatype>& get_memory_system() const;

            yli::memory::GenericMemoryAllocator& get_generic_memory_allocator(const int type) const override;

            bool has_memory_allocator(const int type) const
            {
                return this->core.memory_system.has_allocator(type);
            }

            template<typename Type>
                yli::memory::MemoryAllocator<Type>& get_memory_allocator(const int type) const
            {
                return this->core.memory_system.get_allocator<Type>(type);
            }

            yli::ontology::GenericEntityFactory& get_generic_entity_factory() const override;

            yli::ontology::EntityFactory<hirvi::Datatype>& get_entity_factory() const
            {
                return this->core.entity_factory.get();
            }

            yli::event::EventSystem* get_event_system() const override;

            yli::input::InputSystem* get_input_system() const override;

            yli::audio::AudioSystem* get_audio_system() const override;

            bool is_universe(yli::ontology::Entity* entity) const override;

            yli::ontology::Universe& get_universe() const override;

            yli::ontology::UniverseStruct get_universe_struct() const;

            bool create_and_start_simulation() override;

            static void customize(HirviCore& hirvi_core);

        private:
            hirvi::HirviCore core;
    };
}

namespace yli::core
{
    std::unique_ptr<yli::core::Application> create_application(const int argc, const char* const argv[]);
}

#endif
