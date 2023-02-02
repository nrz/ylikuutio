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

#include "application.hpp"

// Include standard headers
#include <string>   // std::string

namespace yli::ontology
{
    class Universe;
}

namespace yli::core
{
    Application::Application(const int argc, const char* const argv[])
        : command_line_master(argc, argv),
        universe(nullptr)
    {
        // constructor.
    }

    std::string Application::get_name() const
    {
        return ""; // `override` this in the inherited class.
    }

    std::string Application::get_version() const
    {
        return ""; // `override` this in the inherited class.
    }

    yli::ontology::Universe* Application::get_universe() const
    {
        return this->universe;
    }

    void Application::set_universe(yli::ontology::Universe* const universe)
    {
        this->universe = universe;
    }
}
