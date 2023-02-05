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

#include "callback_parameter.hpp"
#include "console_callback_engine.hpp"
#include "console_callback_object.hpp"
#include "console_callback_object_struct.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <optional> // std::optional

namespace yli::ontology
{
    ConsoleCallbackObject::ConsoleCallbackObject(
            yli::ontology::Universe& universe,
            const yli::ontology::ConsoleCallbackObjectStruct& console_callback_object_struct,
            yli::ontology::GenericParentModule* const console_callback_engine_parent)
        : yli::ontology::CallbackObject(universe, console_callback_object_struct, console_callback_engine_parent),
        console_callback { console_callback_object_struct.console_callback },
        console_pointer { console_callback_object_struct.console_pointer }
    {
    }

    std::optional<yli::data::AnyValue> ConsoleCallbackObject::execute(const yli::data::AnyValue&)
    {
        if (this->get_parent() != nullptr && this->console_callback != nullptr && this->console_pointer != nullptr)
        {
            return yli::data::AnyValue(
                    this->console_callback(
                        static_cast<yli::ontology::ConsoleCallbackEngine*>(this->get_parent()),
                        this,
                        this->parent_of_callback_parameters,
                        *this->console_pointer));
        }

        return std::nullopt;
    }
}
