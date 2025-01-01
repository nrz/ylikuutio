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

#include "movable_variable_read.hpp"
#include "movable.hpp"
#include "universe.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <numbers>  // std::numbers::pi
#include <optional> // std::optional

namespace yli::ontology
{
    class Entity;

    std::optional<yli::data::AnyValue> read_cartesian_coordinates(Entity& entity)
    {
        Movable* const movable = dynamic_cast<Movable*>(&entity);

        if (movable != nullptr)
        {
            return yli::data::AnyValue(movable->location.xyz);
        }

        Universe* const universe = dynamic_cast<Universe*>(&entity);

        if (universe != nullptr)
        {
            return yli::data::AnyValue(universe->get_xyz());
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> read_x(Entity& entity)
    {
        Movable* const movable = dynamic_cast<Movable*>(&entity);

        if (movable != nullptr)
        {
            return yli::data::AnyValue(movable->location.get_x());
        }

        Universe* const universe = dynamic_cast<Universe*>(&entity);

        if (universe != nullptr)
        {
            return yli::data::AnyValue(universe->get_x());
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> read_y(Entity& entity)
    {
        Movable* const movable = dynamic_cast<Movable*>(&entity);

        if (movable != nullptr)
        {
            return yli::data::AnyValue(movable->location.get_y());
        }

        Universe* const universe = dynamic_cast<Universe*>(&entity);

        if (universe != nullptr)
        {
            return yli::data::AnyValue(universe->get_y());
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> read_z(Entity& entity)
    {
        Movable* const movable = dynamic_cast<Movable*>(&entity);

        if (movable != nullptr)
        {
            return yli::data::AnyValue(movable->location.get_z());
        }

        Universe* const universe = dynamic_cast<Universe*>(&entity);

        if (universe != nullptr)
        {
            return yli::data::AnyValue(universe->get_z());
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> read_up(Entity& entity)
    {
        Movable* const movable = dynamic_cast<Movable*>(&entity);

        if (movable != nullptr)
        {
            return yli::data::AnyValue(movable->up);
        }

        Universe* const universe = dynamic_cast<Universe*>(&entity);

        if (universe != nullptr)
        {
            return yli::data::AnyValue(universe->get_up());
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> read_right(Entity& entity)
    {
        Movable* const movable = dynamic_cast<Movable*>(&entity);

        if (movable != nullptr)
        {
            return yli::data::AnyValue(movable->right);
        }

        Universe* const universe = dynamic_cast<Universe*>(&entity);

        if (universe != nullptr)
        {
            return yli::data::AnyValue(universe->get_right());
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> read_roll(Entity& entity)
    {
        Movable* const movable = dynamic_cast<Movable*>(&entity);

        if (movable != nullptr)
        {
            return yli::data::AnyValue(movable->orientation.roll);
        }

        Universe* const universe = dynamic_cast<Universe*>(&entity);

        if (universe != nullptr)
        {
            return yli::data::AnyValue(universe->get_roll());
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> read_yaw(Entity& entity)
    {
        Movable* const movable = dynamic_cast<Movable*>(&entity);

        if (movable != nullptr)
        {
            return yli::data::AnyValue(movable->orientation.yaw);
        }

        Universe* const universe = dynamic_cast<Universe*>(&entity);

        if (universe != nullptr)
        {
            return yli::data::AnyValue(universe->get_yaw());
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> read_pitch(Entity& entity)
    {
        Movable* const movable = dynamic_cast<Movable*>(&entity);

        if (movable != nullptr)
        {
            return yli::data::AnyValue(movable->orientation.pitch);
        }

        Universe* const universe = dynamic_cast<Universe*>(&entity);

        if (universe != nullptr)
        {
            return yli::data::AnyValue(universe->get_pitch());
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> read_azimuth(Entity& entity)
    {
        Movable* const movable = dynamic_cast<Movable*>(&entity);

        if (movable != nullptr)
        {
            const float azimuth = 0.5f * static_cast<float>(std::numbers::pi) - movable->orientation.yaw;
            return yli::data::AnyValue(azimuth);
        }

        Universe* const universe = dynamic_cast<Universe*>(&entity);

        if (universe != nullptr)
        {
            const float azimuth = 0.5f * static_cast<float>(std::numbers::pi) - universe->get_yaw();
            return yli::data::AnyValue(azimuth);
        }

        return std::nullopt;
    }
}
