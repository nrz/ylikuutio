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

#include "code/ylikuutio/callback/callback_engine.hpp"
#include "input_parameters_to_any_value_callback_with_console.hpp"

#ifndef __CONSOLE_CALLBACK_ENGINE_HPP_INCLUDED
#define __CONSOLE_CALLBACK_ENGINE_HPP_INCLUDED

namespace yli::console
{
    class ConsoleCallbackObject;

    class ConsoleCallbackEngine : public yli::callback::CallbackEngine
    {
        public:
            // constructor.
            ConsoleCallbackEngine();

            // destructor.
            ~ConsoleCallbackEngine();

            yli::console::ConsoleCallbackObject* create_ConsoleCallbackObject(const InputParametersToAnyValueCallbackWithConsole callback, yli::ontology::Console* console_pointer);
    };
}

#endif
