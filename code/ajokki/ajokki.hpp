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

#ifndef AJOKKI_AJOKKI_HPP_INCLUDED
#define AJOKKI_AJOKKI_HPP_INCLUDED

#include "code/ylikuutio/core/application.hpp"
#include "code/ylikuutio/core/system_factory.hpp"
#include "code/ylikuutio/data/datatype.hpp"
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
    class Ecosystem;
    class Scene;
    class GenericEntityFactory;
    struct UniverseStruct;
}

namespace ajokki
{
    class AjokkiApplication final : public yli::core::Application
    {
        public:
            AjokkiApplication(const int argc, const char* const argv[]);

            ~AjokkiApplication() = default;

            std::string get_name() const override;

            std::vector<std::string> get_valid_keys() const override;

            yli::memory::GenericMemorySystem& get_generic_memory_system() const override;

            yli::memory::GenericMemoryAllocator& get_generic_memory_allocator(const int type) const override;

            yli::ontology::GenericEntityFactory& get_generic_entity_factory() const override;

            yli::event::EventSystem* get_event_system() const override;

            yli::input::InputSystem* get_input_system() const override;

            yli::audio::AudioSystem* get_audio_system() const override;

            bool is_universe(yli::ontology::Entity* entity) const override;

            yli::ontology::Universe& get_universe() const override;

            yli::ontology::UniverseStruct get_universe_struct() const;

            bool create_simulation() override;

        private:
            yli::ontology::Ecosystem* create_earth_ecosystem();
            yli::ontology::Scene* create_helsinki_east_downtown_scene();
            yli::ontology::Scene* create_joensuu_center_west_scene();

            yli::memory::MemorySystem<yli::data::Datatype> memory_system;
            yli::ontology::EntityFactory<yli::data::Datatype> entity_factory;
            yli::core::SystemFactory<yli::data::Datatype> system_factory;
            yli::ontology::Universe* const universe     { nullptr };
            yli::event::EventSystem* const event_system { nullptr };
            yli::input::InputSystem* const input_system { nullptr };
            yli::audio::AudioSystem* const audio_system { nullptr };
    };
}

namespace yli::core
{
    std::unique_ptr<yli::core::Application> create_application(const int argc, const char* const argv[]);
}

#endif
