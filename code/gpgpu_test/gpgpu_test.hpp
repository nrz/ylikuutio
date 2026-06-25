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

#ifndef GPGPU_TEST_GPGPU_TEST_HPP_INCLUDED
#define GPGPU_TEST_GPGPU_TEST_HPP_INCLUDED

#include "code/ylikuutio/core/application.hpp"
#include "code/ylikuutio/core/application_core.hpp"

// Include standard headers
#include <memory> // std::unique_ptr
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
    class Universe;
    class GenericEntityFactory;
    struct UniverseStruct;
}

namespace gpgpu_test
{
    class GpgpuTestApplication final : public yli::core::Application
    {
        public:
            GpgpuTestApplication(int argc, const char* const argv[]);

            std::string get_name() const override;

            std::vector<std::string> get_valid_keys() const override;

            yli::memory::GenericMemorySystem& get_generic_memory_system() const override;

            yli::ontology::GenericEntityFactory& get_generic_entity_factory() const override;

            bool is_universe(yli::ontology::Entity* entity) const override;

            yli::ontology::Universe& get_universe() const override;

            static yli::ontology::UniverseStruct get_universe_struct();

            bool create_and_start_simulation() override;

        private:
            yli::ontology::Scene* create_gpgpu_test_scene() const;

            yli::core::ApplicationCore core;
    };
}

namespace yli::core
{
    std::unique_ptr<Application> create_application(int argc, const char* const argv[]);
}

#endif
