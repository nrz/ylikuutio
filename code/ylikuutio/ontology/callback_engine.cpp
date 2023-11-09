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

#include "callback_engine.hpp"
#include "callback_object.hpp"
#include "generic_entity_factory.hpp"
#include "generic_callback_engine_struct.hpp"
#include "callback_object_struct.hpp"
#include "family_templates.hpp"
#include "input_parameters_and_any_value_to_any_value_callback_with_universe.hpp"
#include "code/ylikuutio/core/application.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/data/datatype.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <optional> // std::optional

namespace yli::ontology
{
    class Universe;

    CallbackEngine::CallbackEngine(
            yli::core::Application& application,
            yli::ontology::Universe& universe,
            yli::ontology::GenericParentModule* const parent)
        : GenericCallbackEngine(application, universe, GenericCallbackEngineStruct()),
        child_of_entity(parent, *this),
        parent_of_callback_objects(
                *this,
                this->registry,
                application.get_memory_allocator(yli::data::Datatype::CALLBACK_OBJECT),
                "callback_objects")
    {
        // `yli::ontology::Entity` member variables begin here.
        this->type_string = "yli::ontology::CallbackEngine*";
    }

    yli::ontology::CallbackObject* CallbackEngine::create_callback_object()
    {
        yli::ontology::GenericEntityFactory& entity_factory = this->application.get_generic_entity_factory();

        yli::ontology::CallbackObjectStruct callback_object_struct;
        callback_object_struct.parent = this;
        return entity_factory.create_callback_object(callback_object_struct);
    }

    yli::ontology::CallbackObject* CallbackEngine::create_callback_object(
            const InputParametersAndAnyValueToAnyValueCallbackWithUniverse callback)
    {
        yli::ontology::GenericEntityFactory& entity_factory = this->application.get_generic_entity_factory();

        yli::ontology::CallbackObjectStruct callback_object_struct;
        callback_object_struct.parent = this;
        auto callback_object = entity_factory.create_callback_object(callback_object_struct);
        callback_object->set_new_callback(callback);
        return callback_object;
    }

    std::optional<yli::data::AnyValue> CallbackEngine::execute(const yli::data::AnyValue& any_value)
    {
        std::optional<yli::data::AnyValue> return_any_value;
        bool is_any_callback_object_executed { false };

        // execute all callbacks.
        for (std::size_t child_i = 0; child_i < this->parent_of_callback_objects.child_pointer_vector.size(); child_i++)
        {
            yli::ontology::CallbackObject* callback_object_pointer = static_cast<yli::ontology::CallbackObject*>(
                    this->parent_of_callback_objects.child_pointer_vector.at(child_i));

            if (callback_object_pointer != nullptr)
            {
                return_any_value = callback_object_pointer->execute(any_value);
                is_any_callback_object_executed = true;
                this->return_values.emplace_back(return_any_value);
            }
            else
            {
                this->return_values.emplace_back(std::nullopt);
            }
        }

        this->return_values.clear();

        if (is_any_callback_object_executed)
        {
            return return_any_value;
        }

        return std::nullopt;
    }

    std::size_t CallbackEngine::get_n_of_return_values() const
    {
        return this->return_values.size();
    }

    std::optional<yli::data::AnyValue> CallbackEngine::get_nth_return_value(const std::size_t n) const
    {
        // note: indexing of `n` begins from 0.

        std::size_t n_of_return_values = this->get_n_of_return_values();

        if (n_of_return_values <= n)
        {
            return std::nullopt;
        }

        return this->return_values.at(n_of_return_values - 1);
    }

    std::optional<yli::data::AnyValue> CallbackEngine::get_previous_return_value() const
    {
        std::size_t n_of_return_values = this->get_n_of_return_values();

        if (n_of_return_values == 0)
        {
            return std::nullopt;
        }

        return this->return_values.back();
    }

    yli::ontology::Entity* CallbackEngine::get_parent() const
    {
        return this->child_of_entity.get_parent();
    }

    yli::ontology::Scene* CallbackEngine::get_scene() const
    {
        return this->child_of_entity.get_scene();
    }

    std::size_t CallbackEngine::get_number_of_children() const
    {
        return this->parent_of_callback_objects.get_number_of_children();
    }

    std::size_t CallbackEngine::get_number_of_descendants() const
    {
        return yli::ontology::get_number_of_descendants(this->parent_of_callback_objects.child_pointer_vector);
    }
}
