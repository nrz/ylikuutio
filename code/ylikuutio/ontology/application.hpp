// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
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

#ifndef __YLIKUUTIO_ONTOLOGY_APPLICATION_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_APPLICATION_HPP_INCLUDED

#include "entity.hpp"
#include "entity_struct.hpp"
#include "code/ylikuutio/command_line/command_line_master.hpp"

// Include standard headers
#include <memory> // std::make_shared, std::make_unique, std::shared_ptr, std::unique_ptr

namespace yli::ontology
{
    struct UniverseStruct;

    class Application: public yli::ontology::Entity
    {
        public:
            Application(const int argc, const char* const argv[])
                : Entity(nullptr, yli::ontology::EntityStruct()), // `Application` has no parent yet.
                command_line_master(argc, argv)
            {
                // constructor.
            }

            Application(const Application&) = delete;            // Delete copy constructor.
            Application &operator=(const Application&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~Application();

            virtual std::shared_ptr<yli::ontology::UniverseStruct> get_universe_struct(
                    std::shared_ptr<yli::ontology::UniverseStruct> universe_struct_shared_ptr) = 0;

            // This method can be used e.g. to instantiate different Entities before entering the main loop.
            virtual void create_simulation() = 0;

        private:
            yli::command_line::CommandLineMaster command_line_master;
    };
}

#endif
