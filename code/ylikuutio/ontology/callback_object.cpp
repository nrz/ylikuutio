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

#include "callback_object.hpp"
#include "callback_engine.hpp"
#include "callback_parameter.hpp"
#include "entity_struct.hpp"
#include "family_templates.hpp"
#include "input_parameters_and_any_value_to_any_value_callback_with_universe.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr
#include <optional> // std::optional
#include <string>   // std::string

namespace yli::ontology
{
    class Universe;

    CallbackObject::CallbackObject(
            yli::ontology::Universe& universe,
            yli::ontology::GenericParentModule* const callback_engine_parent)
        : Entity(universe, yli::ontology::EntityStruct()),
        child_of_callback_engine(callback_engine_parent, this),
        parent_of_callback_parameters(this, &this->registry, "callback_parameters")
    {
    }

    CallbackObject::CallbackObject(
            yli::ontology::Universe& universe,
            const InputParametersAndAnyValueToAnyValueCallbackWithUniverse callback,
            yli::ontology::GenericParentModule* const callback_engine_parent)
        : Entity(universe, yli::ontology::EntityStruct()),
        child_of_callback_engine(callback_engine_parent, this),
        parent_of_callback_parameters(this, &this->registry, "callback_parameters"),
        callback { callback }
    {
    }

    yli::ontology::CallbackParameter* CallbackObject::create_callback_parameter(
            const std::string& name,
            const yli::data::AnyValue& any_value,
            const bool is_reference)
    {
        return new yli::ontology::CallbackParameter(this->universe, name, any_value, is_reference, &this->parent_of_callback_parameters);
    }

    // getter function for callbacks and callback objects.
    std::optional<yli::data::AnyValue> CallbackObject::get_any_value(const std::string& name) const
    {
        if (this->anyvalue_hashmap.count(name) != 1)
        {
            return std::nullopt;
        }

        return yli::data::AnyValue(this->anyvalue_hashmap.at(name));
    }

    std::optional<yli::data::AnyValue> CallbackObject::get_arg(const std::size_t arg_i) const
    {
        if (arg_i >= this->parent_of_callback_parameters.child_pointer_vector.size())
        {
            std::cerr << "error #1 in CallbackObject code.\n";
            return std::nullopt;
        }

        auto callback_parameter = static_cast<yli::ontology::CallbackParameter*>(
                this->parent_of_callback_parameters.child_pointer_vector.at(arg_i));

        if (callback_parameter == nullptr)
        {
            std::cerr << "error #2 in CallbackObject code.\n";
            return std::nullopt;
        }

        return yli::data::AnyValue(callback_parameter->any_value);
    }

    // setter function for callbacks and callback objects.
    void CallbackObject::set_any_value(const std::string& name, const yli::data::AnyValue& any_value)
    {
        this->anyvalue_hashmap[name] = yli::data::AnyValue(any_value);
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
                    static_cast<yli::ontology::CallbackEngine*>(this->get_parent()),
                    this,
                    this->parent_of_callback_parameters, any_value);
        }

        return std::nullopt;
    }

    yli::ontology::Entity* CallbackObject::get_parent() const
    {
        return this->child_of_callback_engine.get_parent();
    }

    yli::ontology::Scene* CallbackObject::get_scene() const
    {
        return nullptr;
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
