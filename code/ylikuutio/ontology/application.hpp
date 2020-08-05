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
#include <cstddef> // std::size_t
#include <memory>  // std::make_shared, std::make_unique, std::shared_ptr, std::unique_ptr
#include <utility> // std::pair

namespace yli::ontology
{
    class Universe;
    struct UniverseStruct;

    class Application: public yli::ontology::Entity
    {
        public:
            void bind_to_parent();

            Application(const int argc, const char* const argv[])
                : Entity(nullptr, yli::ontology::EntityStruct()), // `Application` has no parent yet.
                command_line_master(argc, argv)
            {
                // constructor.

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::Application*";
            }

            Application(const Application&) = delete;            // Delete copy constructor.
            Application &operator=(const Application&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~Application();

            void set_universe(yli::ontology::Universe* const universe);

            virtual std::pair<bool, std::shared_ptr<yli::ontology::UniverseStruct>> get_universe_struct() = 0;

            // This method can be used e.g. to instantiate different Entities before entering the main loop.
            virtual bool create_simulation() = 0;

        protected:
            yli::command_line::CommandLineMaster command_line_master;

        private:
            yli::ontology::Entity* get_parent() const override final;
            std::size_t get_number_of_children() const override final;
            std::size_t get_number_of_descendants() const override final;
    };

    yli::ontology::Application* create_application();
}

#endif
