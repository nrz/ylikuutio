// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2024 Antti Nuortimo.
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

#include "console_callback_parameter.hpp"
#include "console_callback_object.hpp"
#include "console_callback_parameter_struct.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <string>   // std::string

namespace yli::core
{
    class Application;
}

namespace yli::data
{
    class AnyValue;
}

namespace yli::ontology
{
    class Entity;
    class Universe;
    class Scene;
    struct EntityStruct;

    ConsoleCallbackParameter::ConsoleCallbackParameter(
            yli::core::Application& application,
            yli::ontology::Universe& universe,
            const yli::ontology::ConsoleCallbackParameterStruct& callback_parameter_struct,
            const yli::data::AnyValue& any_value,
            yli::ontology::GenericParentModule* const console_callback_object_parent_module)
        : Entity(application, universe, callback_parameter_struct),
        child_of_console_callback_object(console_callback_object_parent_module, *this),
        any_value { any_value }
    {
        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "yli::ontology::ConsoleCallbackParameter*";
    }

    const yli::data::AnyValue& ConsoleCallbackParameter::get_any_value() const
    {
        return this->any_value;
    }

    yli::ontology::Entity* ConsoleCallbackParameter::get_parent() const
    {
        return this->child_of_console_callback_object.get_parent();
    }

    yli::ontology::Scene* ConsoleCallbackParameter::get_scene() const
    {
        return this->child_of_console_callback_object.get_scene();
    }

    std::size_t ConsoleCallbackParameter::get_number_of_children() const
    {
        return 0; // `ConsoleCallbackParameter` has no children.
    }

    std::size_t ConsoleCallbackParameter::get_number_of_descendants() const
    {
        return 0; // `ConsoleCallbackParameter` has no children.
    }
}
