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

#ifndef YLIKUUTIO_ONTOLOGY_MOVABLE_VARIABLE_ACTIVATION_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_MOVABLE_VARIABLE_ACTIVATION_HPP_INCLUDED

#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <optional> // std::optional

namespace yli::ontology
{
    class Entity;
    class Variable;

    std::optional<yli::data::AnyValue> activate_cartesian_coordinates(Entity& entity, Variable& variable);
    std::optional<yli::data::AnyValue> activate_x(Entity& entity, Variable& variable);
    std::optional<yli::data::AnyValue> activate_y(Entity& entity, Variable& variable);
    std::optional<yli::data::AnyValue> activate_z(Entity& entity, Variable& variable);

    std::optional<yli::data::AnyValue> activate_roll(Entity& entity, Variable& variable);
    std::optional<yli::data::AnyValue> activate_yaw(Entity& entity, Variable& variable);
    std::optional<yli::data::AnyValue> activate_pitch(Entity& entity, Variable& variable);

    std::optional<yli::data::AnyValue> activate_azimuth(Entity& entity, Variable& variable);

    std::optional<yli::data::AnyValue> activate_scale(Entity& entity, Variable& variable);
}

#endif
