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

#include "console_callback_object.hpp"
#include "console_callback_engine.hpp"
#include "console_callback_object_struct.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/data/datatype.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <optional> // std::optional

namespace yli::core
{
    class Application;
}

namespace yli::ontology
{
    class GenericParentModule;
    class Entity;
    class Universe;

    ConsoleCallbackObject::ConsoleCallbackObject(
            yli::core::Application& application,
            Universe& universe,
            const ConsoleCallbackObjectStruct& console_callback_object_struct,
            GenericParentModule* const console_callback_engine_parent_module)
        : Entity(application, universe, console_callback_object_struct),
        child_of_console_callback_engine(console_callback_engine_parent_module, *this),
        parent_of_console_callback_parameters(
                *this,
                this->registry,
                "console_callback_parameters"),
        console_callback { console_callback_object_struct.console_callback },
        console_pointer { console_callback_object_struct.console_pointer }
    {
        // `Entity` member variables begin here.
        this->type_string = "yli::ontology::ConsoleCallbackObject*";
    }

    Entity* ConsoleCallbackObject::get_parent() const
    {
        return this->child_of_console_callback_engine.get_parent();
    }

    Scene* ConsoleCallbackObject::get_scene() const
    {
        // `ConsoleCallbackObject` does not belong in any `Scene`.
        return nullptr;
    }

    std::size_t ConsoleCallbackObject::get_number_of_children() const
    {
        return this->parent_of_console_callback_parameters.get_number_of_children();
    }

    std::size_t ConsoleCallbackObject::get_number_of_descendants() const
    {
        return yli::ontology::get_number_of_descendants(this->parent_of_console_callback_parameters.child_pointer_vector);
    }

    std::optional<yli::data::AnyValue> ConsoleCallbackObject::execute(const yli::data::AnyValue&)
    {
        if (this->get_parent() != nullptr && this->console_callback != nullptr && this->console_pointer != nullptr)
        {
            return yli::data::AnyValue(
                    this->console_callback(
                        static_cast<ConsoleCallbackEngine*>(this->get_parent()),
                        this,
                        this->parent_of_console_callback_parameters,
                        *this->console_pointer));
        }

        return std::nullopt;
    }

    GenericParentModule* ConsoleCallbackObject::get_generic_parent_module(const int type)
    {
        if (type == yli::data::Datatype::CONSOLE_CALLBACK_PARAMETER)
        {
            return &this->parent_of_console_callback_parameters;
        }

        return nullptr;
    }
}
