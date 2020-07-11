// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2020 Antti Nuortimo.
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

#include "entity_variable_activation.hpp"
#include "entity.hpp"
#include "variable.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <memory>  // std::make_shared, std::shared_ptr
#include <variant> // std::holds_alternative, std::variant

namespace yli::ontology
{
    std::shared_ptr<yli::data::AnyValue> activate_should_be_rendered(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable)
    {
        if (entity == nullptr || variable == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> should_be_rendered_any_value = variable->variable_value;

        if (should_be_rendered_any_value == nullptr || !std::holds_alternative<bool>(should_be_rendered_any_value->data))
        {
            return nullptr;
        }

        entity->should_be_rendered = std::get<bool>(should_be_rendered_any_value->data);
        return nullptr;
    }
}
