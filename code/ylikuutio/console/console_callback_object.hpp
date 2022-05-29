// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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

#ifndef __YLIKUUTIO_CONSOLE_CONSOLE_CALLBACK_OBJECT_HPP_INCLUDED
#define __YLIKUUTIO_CONSOLE_CONSOLE_CALLBACK_OBJECT_HPP_INCLUDED

#include "input_parameters_to_any_value_callback_with_console.hpp"
#include "code/ylikuutio/callback/callback_object.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/ontology/console.hpp"

// Include standard headers
#include <optional> // std::optional

namespace yli::callback
{
    class CallbackEngine;
    class CallbackParameter;
}

namespace yli::console
{
    class ConsoleCallbackEngine;

    class ConsoleCallbackObject : public yli::callback::CallbackObject
    {
        public:
            // destructor.
            ~ConsoleCallbackObject();

            friend class yli::console::ConsoleCallbackEngine;

        private:
            // constructor.
            ConsoleCallbackObject(InputParametersToAnyValueCallbackWithConsole console_callback,
                    yli::callback::CallbackEngine* parent, yli::ontology::Console* console_pointer)
                : yli::callback::CallbackObject(nullptr, parent)
            {
                // constructor.
                this->callback = nullptr;
                this->console_callback = console_callback;
                this->console_pointer = console_pointer;
            }

            // execute this callback.
            std::optional<yli::data::AnyValue> execute(const yli::data::AnyValue&) override;

            InputParametersToAnyValueCallbackWithConsole console_callback;
            yli::ontology::Console* console_pointer;
    };
}

#endif
