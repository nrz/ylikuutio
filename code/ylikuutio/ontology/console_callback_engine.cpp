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

#include "console_callback_engine.hpp"
#include "callback_engine.hpp"
#include "console_callback_object.hpp"
#include "console_callback_object_struct.hpp"
#include "generic_entity_factory.hpp"
#include "input_parameters_to_any_value_callback_with_console.hpp"
#include "code/ylikuutio/core/application.hpp"
#include "code/ylikuutio/data/datatype.hpp"

namespace yli::ontology
{
    class GenericParentModule;
    class Universe;

    ConsoleCallbackEngine::ConsoleCallbackEngine(
            yli::core::Application& application,
            yli::ontology::Universe& universe,
            yli::ontology::GenericParentModule* const universe_parent)
        : yli::ontology::CallbackEngine(application, universe, universe_parent)
    {
    }

    yli::ontology::ConsoleCallbackObject* ConsoleCallbackEngine::create_console_callback_object(
            const InputParametersToAnyValueCallbackWithConsole callback,
            yli::ontology::Console* const console_pointer)
    {
        yli::ontology::GenericEntityFactory& entity_factory = this->application.get_entity_factory();

        yli::ontology::ConsoleCallbackObjectStruct console_callback_object_struct;
        console_callback_object_struct.parent = this;
        console_callback_object_struct.console_callback = callback;
        console_callback_object_struct.console_pointer = console_pointer;
        return entity_factory.create_console_callback_object(console_callback_object_struct);
    }
}
