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

#ifndef PI
#define PI 3.14159265359f
#endif

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
#include <memory> // std::make_shared, std::shared_ptr

namespace yli::ontology
{
    class Entity;

    std::shared_ptr<yli::data::AnyValue> read_cartesian_coordinates(yli::ontology::Entity* const entity)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            return std::make_shared<yli::data::AnyValue>(std::make_shared<glm::vec3>(movable->cartesian_coordinates));
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        return std::make_shared<yli::data::AnyValue>(std::make_shared<glm::vec3>(universe->current_camera_cartesian_coordinates));
    }

    std::shared_ptr<yli::data::AnyValue> read_x(yli::ontology::Entity* const entity)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            return std::make_shared<yli::data::AnyValue>(movable->cartesian_coordinates.x);
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        return std::make_shared<yli::data::AnyValue>(universe->current_camera_cartesian_coordinates.x);
    }

    std::shared_ptr<yli::data::AnyValue> read_y(yli::ontology::Entity* const entity)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            return std::make_shared<yli::data::AnyValue>(movable->cartesian_coordinates.y);
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        return std::make_shared<yli::data::AnyValue>(universe->current_camera_cartesian_coordinates.y);
    }

    std::shared_ptr<yli::data::AnyValue> read_z(yli::ontology::Entity* const entity)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            return std::make_shared<yli::data::AnyValue>(movable->cartesian_coordinates.z);
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        return std::make_shared<yli::data::AnyValue>(universe->current_camera_cartesian_coordinates.z);
    }

    std::shared_ptr<yli::data::AnyValue> read_rho(yli::ontology::Entity* const entity)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            return std::make_shared<yli::data::AnyValue>(movable->spherical_coordinates.rho);
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        return std::make_shared<yli::data::AnyValue>(universe->current_camera_spherical_coordinates.rho);
    }

    std::shared_ptr<yli::data::AnyValue> read_theta(yli::ontology::Entity* const entity)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            return std::make_shared<yli::data::AnyValue>(movable->spherical_coordinates.theta);
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        return std::make_shared<yli::data::AnyValue>(universe->current_camera_spherical_coordinates.theta);
    }

    std::shared_ptr<yli::data::AnyValue> read_phi(yli::ontology::Entity* const entity)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            return std::make_shared<yli::data::AnyValue>(movable->spherical_coordinates.phi);
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        return std::make_shared<yli::data::AnyValue>(universe->current_camera_spherical_coordinates.phi);
    }

    std::shared_ptr<yli::data::AnyValue> read_up(yli::ontology::Entity* const entity)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        // TODO: implement `read_up` for `Movable`s!

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        return std::make_shared<yli::data::AnyValue>(&universe->current_camera_up);
    }

    std::shared_ptr<yli::data::AnyValue> read_right(yli::ontology::Entity* const entity)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        // TODO: implement `read_right` for `Movable`s!

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        return std::make_shared<yli::data::AnyValue>(&universe->current_camera_right);
    }

    std::shared_ptr<yli::data::AnyValue> read_yaw(yli::ontology::Entity* const entity)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            return std::make_shared<yli::data::AnyValue>(movable->yaw);
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        return std::make_shared<yli::data::AnyValue>(universe->current_camera_horizontal_angle);
    }

    std::shared_ptr<yli::data::AnyValue> read_pitch(yli::ontology::Entity* const entity)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            return std::make_shared<yli::data::AnyValue>(movable->pitch);
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        return std::make_shared<yli::data::AnyValue>(universe->current_camera_vertical_angle);
    }

    std::shared_ptr<yli::data::AnyValue> read_azimuth(yli::ontology::Entity* const entity)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            const float azimuth = 0.5f * PI - movable->yaw;
            return std::make_shared<yli::data::AnyValue>(azimuth);
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        const float azimuth = 0.5f * PI - universe->current_camera_horizontal_angle;
        return std::make_shared<yli::data::AnyValue>(azimuth);
    }
}
