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

#include "application.hpp"
#include "code/ylikuutio/ontology/universe.hpp"

// Include standard headers
#include <cstdlib>   // EXIT_FAILURE, EXIT_SUCCESS
#include <exception> // try, catch, std::exception
#include <iostream>  // std::cout, std::cin, std::cerr
#include <memory>    // std::make_shared, std::make_unique, std::shared_ptr, std::unique_ptr
#include <utility>   // std::pair

namespace yli::core
{
    // `Application::create_application` is defined by the application!
    extern yli::core::Application* create_application(const int argc, const char* const argv[]);
}

namespace yli::ontology
{
    struct UniverseStruct;
}

int main(const int argc, const char* const argv[]) try
{
    // The program execution starts here.

    // How this works:
    // 1. `yli::core::Application` is created, but it is not
    //    bound to `yli::ontology::Universe`.  `Application`
    //    is defined by the application that uses Ylikuutio.
    // 2. Valid command line argument keys are requested
    //    by calling `Application::get_valid_keys`.
    // 3. `yli::core::Application` creates `UniverseStruct`
    //    appropriately based on the command line arguments and
    //    the tokens and callbacks defined by `Application`
    //    instance, and returns it.
    // 3. If command line arguments were invalid, a help text
    //    is printed and the program exits.
    // 4. `Universe` is created. It receives `UniverseStruct` as an argument.
    // 5. A pointer to the `Universe` is stored in the `Application`.
    // 6. The simulation is created by running `Application::create_simulation`.

    // 1. `yli::core::Application` is created, but it is not
    //    bound to `yli::ontology::Universe`.  `Application`
    //    is defined by the application that uses Ylikuutio.
    yli::core::Application* const application = yli::core::create_application(argc, argv);

    if (application == nullptr)
    {
        std::cerr << "ERROR: error in `yli::core::create_application`!\n";
        return EXIT_FAILURE;
    }

    if (!application->command_line_master.get_are_arguments_valid())
    {
        // Some of the arguments do not comply with the Ylikuutio argument syntax.
        std::cerr << "ERROR: Invalid syntax used in command line parameters.\n";
        application->command_line_master.print_keys_and_values();

        delete application;
        return EXIT_FAILURE;
    }

    if (application->command_line_master.is_key("version"))
    {
        if (!application->get_name().empty() && !application->get_version().empty())
        {
            // Application name and application version present.
            // Print application name and application version normally.
            std::cout << application->get_name() << " " << application->get_version() <<
                ", powered by Ylikuutio " << yli::ontology::Universe::version << "\n";
        }
        else if (!application->get_name().empty())
        {
            // Application name present but application version not present.
            // Print Ylikuutio version as the application version.
            std::cout << application->get_name() << " " << yli::ontology::Universe::version <<
                ", powered by Ylikuutio " << yli::ontology::Universe::version << "\n";
        }
        else
        {
            // No application name present.
            // Print only Ylikuutio version.
            std::cout << "Ylikuutio " << yli::ontology::Universe::version << "\n";
        }

        delete application;
        return EXIT_SUCCESS;
    }

    application->command_line_master.print_keys_and_values();

    // 2. Valid command line argument keys are requested
    //    by calling `Application::get_valid_keys`.
    std::vector<std::string> valid_keys = application->get_valid_keys();

    if (!application->command_line_master.check_keys(valid_keys))
    {
        std::cerr << "ERROR: 1 or more invalid command line parameters given.\n";

        const std::vector<std::string> invalid_keys = application->command_line_master.get_invalid_keys(valid_keys);

        for (std::vector<std::string>::const_iterator it = invalid_keys.begin(); it != invalid_keys.end(); it++)
        {
            std::cerr << "ERROR: Invalid command line parameter: " << *it << "\n";
        }

        delete application;
        return EXIT_FAILURE;
    }

    // 3. `yli::core::Application` creates `UniverseStruct`
    //    appropriately based on the command line arguments and
    //    the tokens and callbacks defined by `Application`
    //    instance, and returns it.
    const auto universe_struct = application->get_universe_struct();

    // 4. `Universe` is created. It receives `UniverseStruct` as an argument.
    yli::ontology::Universe* const universe = new yli::ontology::Universe(universe_struct);

    // 5. A pointer to the `Universe` is stored in the `Application`.
    application->set_universe(universe);

    // 6. The simulation is created by running `Application::create_simulation`.
    if (!application->create_simulation())
    {
        std::cerr << "ERROR: creating the simulation failed!\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
catch (const std::exception& exception)
{
    std::cerr << "ERROR: exception: " << exception.what() << "\n";
    return EXIT_FAILURE;
}

#endif
