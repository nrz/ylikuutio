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

#include "movable_variable_read.hpp"
#include "movable.hpp"
#include "universe.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/data/pi.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <optional> // std::optional

namespace yli::ontology
{
    class Entity;

    std::optional<yli::data::AnyValue> read_cartesian_coordinates(yli::ontology::Entity& entity)
    {
        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(&entity);

        if (movable != nullptr)
        {
            return yli::data::AnyValue(movable->location.xyz);
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(&entity);

        if (universe != nullptr)
        {
            return yli::data::AnyValue(universe->current_camera_location.xyz);
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> read_x(yli::ontology::Entity& entity)
    {
        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(&entity);

        if (movable != nullptr)
        {
            return yli::data::AnyValue(movable->location.get_x());
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(&entity);

        if (universe != nullptr)
        {
            return yli::data::AnyValue(universe->current_camera_location.get_x());
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> read_y(yli::ontology::Entity& entity)
    {
        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(&entity);

        if (movable != nullptr)
        {
            return yli::data::AnyValue(movable->location.get_y());
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(&entity);

        if (universe != nullptr)
        {
            return yli::data::AnyValue(universe->current_camera_location.get_y());
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> read_z(yli::ontology::Entity& entity)
    {
        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(&entity);

        if (movable != nullptr)
        {
            return yli::data::AnyValue(movable->location.get_z());
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(&entity);

        if (universe != nullptr)
        {
            return yli::data::AnyValue(universe->current_camera_location.get_z());
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> read_rho(yli::ontology::Entity& entity)
    {
        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(&entity);

        if (movable != nullptr)
        {
            return yli::data::AnyValue(movable->spherical_coordinates.rho);
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(&entity);

        if (universe != nullptr)
        {
            return yli::data::AnyValue(universe->current_camera_spherical_coordinates.rho);
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> read_theta(yli::ontology::Entity& entity)
    {
        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(&entity);

        if (movable != nullptr)
        {
            return yli::data::AnyValue(movable->spherical_coordinates.theta);
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(&entity);

        if (universe != nullptr)
        {
            return yli::data::AnyValue(universe->current_camera_spherical_coordinates.theta);
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> read_phi(yli::ontology::Entity& entity)
    {
        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(&entity);

        if (movable != nullptr)
        {
            return yli::data::AnyValue(movable->spherical_coordinates.phi);
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(&entity);

        if (universe != nullptr)
        {
            return yli::data::AnyValue(universe->current_camera_spherical_coordinates.phi);
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> read_up(yli::ontology::Entity& entity)
    {
        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(&entity);

        if (movable != nullptr)
        {
            return yli::data::AnyValue(movable->up);
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(&entity);

        if (universe != nullptr)
        {
            return yli::data::AnyValue(universe->current_camera_up);
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> read_right(yli::ontology::Entity& entity)
    {
        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(&entity);

        if (movable != nullptr)
        {
            return yli::data::AnyValue(movable->right);
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(&entity);

        if (universe != nullptr)
        {
            return yli::data::AnyValue(universe->current_camera_right);
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> read_roll(yli::ontology::Entity& entity)
    {
        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(&entity);

        if (movable != nullptr)
        {
            return yli::data::AnyValue(movable->orientation.roll);
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(&entity);

        if (universe != nullptr)
        {
            return yli::data::AnyValue(universe->current_camera_roll);
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> read_yaw(yli::ontology::Entity& entity)
    {
        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(&entity);

        if (movable != nullptr)
        {
            return yli::data::AnyValue(movable->orientation.yaw);
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(&entity);

        if (universe != nullptr)
        {
            return yli::data::AnyValue(universe->current_camera_yaw);
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> read_pitch(yli::ontology::Entity& entity)
    {
        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(&entity);

        if (movable != nullptr)
        {
            return yli::data::AnyValue(movable->orientation.pitch);
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(&entity);

        if (universe != nullptr)
        {
            return yli::data::AnyValue(universe->current_camera_pitch);
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> read_azimuth(yli::ontology::Entity& entity)
    {
        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(&entity);

        if (movable != nullptr)
        {
            const float azimuth = 0.5f * pi - movable->orientation.yaw;
            return yli::data::AnyValue(azimuth);
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(&entity);

        if (universe != nullptr)
        {
            const float azimuth = 0.5f * pi - universe->current_camera_yaw;
            return yli::data::AnyValue(azimuth);
        }

        return std::nullopt;
    }
}
