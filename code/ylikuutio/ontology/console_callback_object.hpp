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

#ifndef YLIKUUTIO_ONTOLOGY_CONSOLE_CALLBACK_OBJECT_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_CONSOLE_CALLBACK_OBJECT_HPP_INCLUDED

#include "callback_object.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <optional> // std::optional

namespace yli::ontology
{
    class GenericParentModule;
    class Universe;
    class CallbackEngine;
    class CallbackParameter;
    class ConsoleCallbackEngine;
    class Console;
    struct ConsoleCallbackObjectStruct;

    class ConsoleCallbackObject final : public yli::ontology::CallbackObject
    {
        public:
            ~ConsoleCallbackObject() = default;

            friend class ConsoleCallbackEngine;

            ConsoleCallbackObject(
                    yli::ontology::Universe& universe,
                    const yli::ontology::ConsoleCallbackObjectStruct& console_callback_object_struct,
                    yli::ontology::GenericParentModule* const console_callback_engine_parent);

        private:
            // execute this callback.
            std::optional<yli::data::AnyValue> execute(const yli::data::AnyValue&) override;

            InputParametersToAnyValueCallbackWithConsole console_callback;
            yli::ontology::Console* console_pointer;
    };
}

#endif