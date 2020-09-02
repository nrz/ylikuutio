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

#include "application.hpp"
#include "universe.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <string>   // std::string

namespace yli::ontology
{
    void Application::bind_to_parent()
    {
        // Requirements:
        // `this->parent` must not be `nullptr`.
        yli::ontology::Universe* const universe = this->universe;

        if (universe == nullptr)
        {
            std::cerr << "ERROR: `Application::bind_to_parent`: `universe` is `nullptr`!\n";
            return;
        }

        // Get `childID` from the `Universe` and set pointer to this `Application`.
        universe->bind_application(this);
    }

    Application::~Application()
    {
        // destructor.
    }

    std::string Application::get_name() const
    {
        return ""; // `override` this in the inherited class.
    }

    std::string Application::get_version() const
    {
        return ""; // `override` this in the inherited class.
    }

    void Application::set_universe(yli::ontology::Universe* const universe)
    {
        this->universe = universe;
    }

    yli::ontology::Entity* Application::get_parent() const
    {
        return this->universe;
    }

    std::size_t Application::get_number_of_children() const
    {
        return 0; // `Application` has no children.
    }

    std::size_t Application::get_number_of_descendants() const
    {
        return 0; // `Application` has no children.
    }
}
