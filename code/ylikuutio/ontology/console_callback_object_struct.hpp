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

#ifndef YLIKUUTIO_ONTOLOGY_CONSOLE_CALLBACK_OBJECT_STRUCT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_CONSOLE_CALLBACK_OBJECT_STRUCT_HPP_INCLUDED

#include "entity_struct.hpp"
#include "input_parameters_to_any_value_callback_with_console.hpp"
#include "request.hpp"

// Include standard headers
#include <utility> // std::move

namespace yli::ontology
{
    class ConsoleCallbackEngine;

    struct ConsoleCallbackObjectStruct final : public EntityStruct
    {
        explicit ConsoleCallbackObjectStruct(Request<ConsoleCallbackEngine>&& console_callback_engine_parent)
            : console_callback_engine_parent { std::move(console_callback_engine_parent) }
        {
        }

        Request<ConsoleCallbackEngine> console_callback_engine_parent {};
        InputParametersToAnyValueCallbackWithConsole console_callback { nullptr };
    };
}

#endif
