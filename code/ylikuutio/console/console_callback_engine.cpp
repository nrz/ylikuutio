// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
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

#include "console_callback_engine.hpp"
#include "console_callback_object.hpp"
#include "input_parameters_to_any_value_callback_with_console.hpp"

namespace yli::console
{
    ConsoleCallbackEngine::ConsoleCallbackEngine()
    {
        // constructor.
    }

    ConsoleCallbackEngine::~ConsoleCallbackEngine()
    {
        // destructor.
    }

    yli::console::ConsoleCallbackObject* ConsoleCallbackEngine::create_console_callback_object(const InputParametersToAnyValueCallbackWithConsole callback, yli::ontology::Console* console_pointer)
    {
        return new yli::console::ConsoleCallbackObject(callback, this, console_pointer);
    }
}
