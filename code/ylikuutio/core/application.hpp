// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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

namespace yli::ontology
{
    class Universe;
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

            yli::ontology::Universe* get_universe() const;
            void set_universe(yli::ontology::Universe* const universe);

            virtual std::vector<std::string> get_valid_keys() = 0;
            virtual yli::ontology::UniverseStruct get_universe_struct() = 0;

            // This method can be used e.g. to instantiate different Entities before entering the main loop.
            virtual bool create_simulation() = 0;

            yli::command_line::CommandLineMaster command_line_master;

        private:
            yli::ontology::Universe* universe;
    };

    std::unique_ptr<yli::core::Application> create_application();
}

#endif
