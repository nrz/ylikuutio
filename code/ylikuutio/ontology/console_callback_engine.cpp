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

#include "console_callback_engine.hpp"
#include "console.hpp"
#include "console_callback_object.hpp"
#include "request.hpp"
#include "console_callback_object_struct.hpp"
#include "generic_entity_factory.hpp"
#include "generic_callback_engine_struct.hpp"
#include "input_parameters_to_any_value_callback_with_console.hpp"
#include "family_templates.hpp"
#include "code/ylikuutio/core/application.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/data/datatype.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <optional> // std::optional

namespace yli::ontology
{
    class GenericParentModule;
    class Universe;
    struct ConsoleCallbackEngineStruct;

    ConsoleCallbackEngine::ConsoleCallbackEngine(
            yli::core::Application& application,
            Universe& universe,
            const ConsoleCallbackEngineStruct&,
            GenericParentModule* const console_parent_module)
        : GenericCallbackEngine(application, universe, GenericCallbackEngineStruct()),
        child_of_console(console_parent_module, *this),
        parent_of_console_callback_objects(
                *this,
                this->registry,
                "console_callback_objects")
    {
        // `Entity` member variables begin here.
        this->type_string = "yli::ontology::ConsoleCallbackEngine*";
    }

    Scene* ConsoleCallbackEngine::get_scene() const
    {
        // `ConsoleCallbackEngine` does not belong in any `Scene`.
        return nullptr;
    }

    Console* ConsoleCallbackEngine::get_console() const
    {
        return static_cast<Console*>(this->get_parent());
    }

    Entity* ConsoleCallbackEngine::get_parent() const
    {
        return this->child_of_console.get_parent();
    }

    std::size_t ConsoleCallbackEngine::get_number_of_children() const
    {
        return this->parent_of_console_callback_objects.get_number_of_children();
    }

    std::size_t ConsoleCallbackEngine::get_number_of_descendants() const
    {
        return yli::ontology::get_number_of_descendants(this->parent_of_console_callback_objects.child_pointer_vector);
    }

    ConsoleCallbackObject* ConsoleCallbackEngine::create_console_callback_object(
            const InputParametersToAnyValueCallbackWithConsole callback)
    {
        GenericEntityFactory& entity_factory = this->get_application().get_generic_entity_factory();

        ConsoleCallbackObjectStruct console_callback_object_struct { yli::ontology::Request(this) };
        console_callback_object_struct.console_callback = callback;
        return entity_factory.create_console_callback_object(console_callback_object_struct);
    }

    std::optional<yli::data::AnyValue> ConsoleCallbackEngine::execute(const yli::data::AnyValue& any_value)
    {
        std::optional<yli::data::AnyValue> return_any_value;
        bool is_any_console_callback_object_executed { false };

        // execute all callbacks.
        for (std::size_t child_i = 0; child_i < this->parent_of_console_callback_objects.child_pointer_vector.size(); child_i++)
        {
            ConsoleCallbackObject* console_callback_object_pointer = static_cast<ConsoleCallbackObject*>(
                    this->parent_of_console_callback_objects.child_pointer_vector.at(child_i));

            if (console_callback_object_pointer != nullptr)
            {
                return_any_value = console_callback_object_pointer->execute(any_value);
                is_any_console_callback_object_executed = true;
                this->return_values.emplace_back(return_any_value);
            }
            else
            {
                this->return_values.emplace_back(std::nullopt);
            }
        }

        this->return_values.clear();

        if (is_any_console_callback_object_executed)
        {
            return return_any_value;
        }

        return std::nullopt;
    }

    GenericParentModule* ConsoleCallbackEngine::get_generic_parent_module(const int type)
    {
        if (type == yli::data::Datatype::CONSOLE_CALLBACK_OBJECT)
        {
            return &this->parent_of_console_callback_objects;
        }

        return nullptr;
    }
}
