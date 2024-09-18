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

#ifndef YLIKUUTIO_ONTOLOGY_MOVABLE_VARIABLE_READ_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_MOVABLE_VARIABLE_READ_HPP_INCLUDED

#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <optional> // std::optional

namespace yli::ontology
{
    class Entity;

    std::optional<yli::data::AnyValue> read_cartesian_coordinates(Entity& entity);
    std::optional<yli::data::AnyValue> read_x(Entity& entity);
    std::optional<yli::data::AnyValue> read_y(Entity& entity);
    std::optional<yli::data::AnyValue> read_z(Entity& entity);

    std::optional<yli::data::AnyValue> read_up(Entity& entity);
    std::optional<yli::data::AnyValue> read_right(Entity& entity);

    std::optional<yli::data::AnyValue> read_roll(Entity& entity);
    std::optional<yli::data::AnyValue> read_yaw(Entity& entity);
    std::optional<yli::data::AnyValue> read_pitch(Entity& entity);

    std::optional<yli::data::AnyValue> read_azimuth(Entity& entity);
}

#endif
