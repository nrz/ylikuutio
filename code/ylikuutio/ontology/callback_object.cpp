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

#include "callback_object.hpp"
#include "generic_parent_module.hpp"
#include "callback_engine.hpp"
#include "callback_parameter.hpp"
#include "generic_entity_factory.hpp"
#include "request.hpp"
#include "callback_object_struct.hpp"
#include "callback_parameter_struct.hpp"
#include "family_templates.hpp"
#include "input_parameters_and_any_value_to_any_value_callback_with_universe.hpp"
#include "code/ylikuutio/core/application.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/data/datatype.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cerr
#include <optional> // std::optional
#include <string>   // std::string
#include <utility>  // std::move

namespace yli::ontology
{
    class Universe;

    CallbackObject::CallbackObject(
            yli::core::Application& application,
            Universe& universe,
            const CallbackObjectStruct& callback_object_struct,
            GenericParentModule* const callback_engine_parent_module)
        : Entity(application, universe, callback_object_struct),
        child_of_callback_engine(callback_engine_parent_module, *this),
        parent_of_callback_parameters(
                *this,
                this->registry,
                "callback_parameters")
    {
        // `Entity` member variables begin here.
        this->type_string = "yli::ontology::CallbackObject*";
    }

    CallbackObject::CallbackObject(
            yli::core::Application& application,
            Universe& universe,
            const CallbackObjectStruct& callback_object_struct,
            const InputParametersAndAnyValueToAnyValueCallbackWithUniverse callback,
            GenericParentModule* const callback_engine_parent_module)
        : Entity(application, universe, callback_object_struct),
        child_of_callback_engine(callback_engine_parent_module, *this),
        parent_of_callback_parameters(
                *this,
                this->registry,
                "callback_parameters"),
        callback { callback }
    {
        // `Entity` member variables begin here.
        this->type_string = "yli::ontology::CallbackObject*";
    }

    CallbackParameter* CallbackObject::create_callback_parameter(
            const std::string& name,
            yli::data::AnyValue&& any_value)
    {
        const GenericEntityFactory& entity_factory = this->get_application().get_generic_entity_factory();

        CallbackParameterStruct callback_parameter_struct { Request(this) };
        callback_parameter_struct.local_name = name;
        return static_cast<CallbackParameter*>(
                entity_factory.create_callback_parameter(callback_parameter_struct, std::move(any_value)));
    }

    // getter function for callbacks and callback objects.
    std::optional<yli::data::AnyValue> CallbackObject::get_any_value(const std::string& name) const
    {
        Entity* const named_entity = this->registry.get_entity(name);

        if (named_entity == nullptr)
        {
            return std::nullopt;
        }

        const CallbackParameter* const callback_parameter = dynamic_cast<CallbackParameter*>(named_entity);

        if (callback_parameter == nullptr)
        {
            return std::nullopt;
        }

        return yli::data::AnyValue(callback_parameter->get_any_value());
    }

    std::optional<yli::data::AnyValue> CallbackObject::get_arg(const std::size_t arg_i) const
    {
        if (arg_i >= this->parent_of_callback_parameters.child_pointer_vector.size())
        {
            std::cerr << "error #1 in CallbackObject code.\n";
            return std::nullopt;
        }

        const auto callback_parameter = static_cast<CallbackParameter*>(
                this->parent_of_callback_parameters.child_pointer_vector.at(arg_i));

        if (callback_parameter == nullptr)
        {
            std::cerr << "error #2 in CallbackObject code.\n";
            return std::nullopt;
        }

        return yli::data::AnyValue(callback_parameter->any_value);
    }

    void CallbackObject::set_new_callback(const InputParametersAndAnyValueToAnyValueCallbackWithUniverse callback)
    {
        this->callback = callback;
    }

    std::optional<yli::data::AnyValue> CallbackObject::execute(const yli::data::AnyValue& any_value)
    {
        if (this->get_parent() != nullptr && this->callback != nullptr)
        {
            return this->callback(
                    this->universe,
                    static_cast<CallbackEngine*>(this->get_parent()),
                    this,
                    this->parent_of_callback_parameters, any_value);
        }

        return std::nullopt;
    }

    GenericParentModule* CallbackObject::get_generic_parent_module(const int type)
    {
        if (type == yli::data::Datatype::CALLBACK_PARAMETER)
        {
            return &this->parent_of_callback_parameters;
        }

        return nullptr;
    }

    Entity* CallbackObject::get_parent() const
    {
        return this->child_of_callback_engine.get_parent();
    }

    Scene* CallbackObject::get_scene() const
    {
        return this->child_of_callback_engine.get_scene();
    }

    std::size_t CallbackObject::get_number_of_children() const
    {
        return this->parent_of_callback_parameters.get_number_of_children();
    }

    std::size_t CallbackObject::get_number_of_descendants() const
    {
        return yli::ontology::get_number_of_descendants(this->parent_of_callback_parameters.child_pointer_vector);
    }
}
