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

#include "entity_variable_activation.hpp"
#include "entity.hpp"
#include "variable.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <optional> // std::optional
#include <variant>  // std::holds_alternative

namespace yli::ontology
{
    std::optional<yli::data::AnyValue> activate_should_render(
            Entity& entity,
            Variable& variable)
    {
        const yli::data::AnyValue& should_render_any_value = variable.variable_value;

        if (std::holds_alternative<bool>(should_render_any_value.data))
        {
            entity.should_render = std::get<bool>(should_render_any_value.data);
        }

        return std::nullopt;
    }
}
