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

#include "callback_parameter.hpp"
#include "callback_object.hpp"
#include "entity_struct.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <string>   // std::string

namespace yli::ontology
{
    class Entity;
    class Universe;
    class Scene;

    CallbackParameter::CallbackParameter(
            yli::ontology::Universe& universe,
            const std::string& name,
            const yli::data::AnyValue& any_value,
            const bool is_reference,
            yli::ontology::GenericParentModule* const callback_object_parent)
        : Entity(universe, yli::ontology::EntityStruct("", name)),
        child_of_callback_object(callback_object_parent, this),
        any_value    { any_value },
        is_reference { is_reference }
    {
    }

    const yli::data::AnyValue& CallbackParameter::get_any_value() const
    {
        return this->any_value;
    }

    yli::ontology::Entity* CallbackParameter::get_parent() const
    {
        return this->child_of_callback_object.get_parent();
    }

    yli::ontology::Scene* CallbackParameter::get_scene() const
    {
        return nullptr;
    }

    std::size_t CallbackParameter::get_number_of_children() const
    {
        return 0; // `CallbackParameter` has no children.
    }

    std::size_t CallbackParameter::get_number_of_descendants() const
    {
        return 0; // `CallbackParameter` has no children.
    }
}
