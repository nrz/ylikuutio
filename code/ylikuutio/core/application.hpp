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

#ifndef YLIKUUTIO_CORE_APPLICATION_HPP_INCLUDED
#define YLIKUUTIO_CORE_APPLICATION_HPP_INCLUDED

#include "code/ylikuutio/command_line/command_line_master.hpp"

// Include standard headers
#include <memory>  // std::unique_ptr
#include <string>  // std::string
#include <vector>  // std::vector

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

namespace yli::core
{
    class Application
    {
        public:
            Application(const int argc, const char* const argv[]);

            Application(const Application&) = delete;            // Delete copy constructor.
            yli::core::Application& operator=(const Application&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~Application() = default;

            virtual std::string get_name() const;    // Note: this is not the global name or the local name of the `Application`.
            virtual std::string get_version() const; // `Application` version.

            virtual std::vector<std::string> get_valid_keys() const = 0;

            virtual yli::memory::GenericMemorySystem& get_generic_memory_system() const = 0;

            virtual yli::memory::GenericMemoryAllocator& get_memory_allocator(const int type) const = 0;

            virtual yli::ontology::GenericEntityFactory& get_generic_entity_factory() const = 0;

            virtual bool is_universe(yli::ontology::Entity* entity) const = 0;

            virtual yli::ontology::Universe& get_universe() const = 0;

            // This method can be used e.g. to instantiate different Entities before entering the main loop.
            virtual bool create_simulation() = 0;

            yli::command_line::CommandLineMaster command_line_master;
    };

    std::unique_ptr<yli::core::Application> create_application();
}

#endif
