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

#ifndef __YLIKUUTIO_CORE_ENTRYPOINT_HPP_INCLUDED
#define __YLIKUUTIO_CORE_ENTRYPOINT_HPP_INCLUDED

#define SDL_main main

#include "code/ylikuutio/ontology/application.hpp"
#include "code/ylikuutio/ontology/universe.hpp"

// Include standard headers
#include <cstdlib>   // EXIT_FAILURE, EXIT_SUCCESS
#include <exception> // try, catch, std::exception
#include <iostream>  // std::cout, std::cin, std::cerr
#include <memory>    // std::make_shared, std::make_unique, std::shared_ptr, std::unique_ptr
#include <utility>   // std::pair

namespace yli::ontology
{
    // `Application::create_application` is defined by the application!
    extern yli::ontology::Application* create_application(const int argc, const char* const argv[]);

    struct UniverseStruct;
}

int main(const int argc, const char* const argv[]) try
{
    // The program execution starts here.

    // How this works:
    // 1. `yli::ontology::Application` is created, but it is not
    //    bound to `yli::ontology::Universe` yet.  `Application`
    //    is defined by the application that uses Ylikuutio.
    // 2. `yli::ontology::Application` creates `UniverseStruct`
    //    appropriately based on the command line arguments and
    //    the tokens and callbacks defined by `Application`
    //    instance, and returns a `std::shared_ptr` to it.
    // 3. If command line arguments were invalid, a help text
    //    is printed and the program exits.
    // 4. `Universe` is created. It receives `UniverseStruct` as an argument.
    // 5. `Application` is bound to the newly created `Universe`.
    // 6. The simulation is created by running `Application::create_simulation`.

    // 1. `yli::ontology::Application` is created, but it is not
    //    bound to `yli::ontology::Universe` yet.  `Application`
    //    is defined by the application that uses Ylikuutio.
    yli::ontology::Application* const application = yli::ontology::create_application(argc, argv);

    if (application == nullptr)
    {
        std::cerr << "ERROR: error in `yli::ontology::create_application`!\n";
        return EXIT_FAILURE;
    }

    // 2. `yli::ontology::Application` creates `UniverseStruct`
    //    appropriately based on the command line arguments and
    //    the tokens and callbacks defined by `Application`
    //    instance, and returns a `std::shared_ptr` to it.

    const auto [success, universe_struct_shared_ptr] = application->get_universe_struct();

    if (success && universe_struct_shared_ptr == nullptr)
    {
        // No errors, but do not start the application.
        // This may be due to `--version` or similar.
        delete application;
        return EXIT_SUCCESS;
    }

    if (!success && universe_struct_shared_ptr != nullptr)
    {
        std::cerr << "ERROR: error in `Application::get_universe_struct!\n";

        delete application;
        return EXIT_FAILURE;
    }

    if (universe_struct_shared_ptr == nullptr)
    {
        // 3. If command line arguments were invalid, a help text
        //    is printed and the program exits.

        std::cerr << "ERROR: invalid command line arguments!\n";

        // TODO: print the usage of command line arguments!
        delete application;
        return EXIT_FAILURE;
    }

    // 4. `Universe` is created. It receives `UniverseStruct` as an argument.
    yli::ontology::Universe* const universe = new yli::ontology::Universe(*universe_struct_shared_ptr);

    // 5. `Application` is bound to the newly created `Universe`.
    application->set_universe(universe);
    application->bind_to_universe();
    application->bind_to_parent();

    // 6. The simulation is created by running `Application::create_simulation`.
    if (!application->create_simulation())
    {
        std::cerr << "ERROR: creating the simulation failed!\n";
    }
}
catch (const std::exception& exception)
{
    std::cerr << "ERROR: exception: " << exception.what() << "\n";
}

#endif
