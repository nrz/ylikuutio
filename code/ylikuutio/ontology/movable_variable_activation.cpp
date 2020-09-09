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

#include "movable_variable_activation.hpp"
#include "variable.hpp"
#include "movable.hpp"
#include "universe.hpp"
#include "holobiont.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <memory>  // std::make_shared, std::shared_ptr
#include <variant> // std::holds_alternative, std::variant

namespace yli::ontology
{
    class Entity;

    std::shared_ptr<yli::data::AnyValue> activate_cartesian_coordinates(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable)
    {
        if (entity == nullptr || variable == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            std::shared_ptr<yli::data::AnyValue> cartesian_coordinates_any_value = variable->variable_value;

            if (cartesian_coordinates_any_value == nullptr || !std::holds_alternative<std::shared_ptr<glm::vec3>>(cartesian_coordinates_any_value->data))
            {
                return nullptr;
            }

            movable->cartesian_coordinates = *(std::get<std::shared_ptr<glm::vec3>>(cartesian_coordinates_any_value->data));
            return nullptr;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> cartesian_coordinates_any_value = variable->variable_value;

        if (cartesian_coordinates_any_value == nullptr || !std::holds_alternative<std::shared_ptr<glm::vec3>>(cartesian_coordinates_any_value->data))
        {
            return nullptr;
        }

        universe->current_camera_cartesian_coordinates = *(std::get<std::shared_ptr<glm::vec3>>(cartesian_coordinates_any_value->data));
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> activate_x(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable)
    {
        if (entity == nullptr || variable == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            std::shared_ptr<yli::data::AnyValue> x_any_value = variable->variable_value;

            if (x_any_value == nullptr || !std::holds_alternative<float>(x_any_value->data))
            {
                return nullptr;
            }

            movable->cartesian_coordinates.x = std::get<float>(x_any_value->data);
            movable->model_matrix[3][0] = std::get<float>(x_any_value->data);

            yli::ontology::Holobiont* const holobiont = dynamic_cast<yli::ontology::Holobiont*>(movable);

            if (holobiont != nullptr)
            {
                holobiont->update_x(std::get<float>(x_any_value->data));
            }

            return nullptr;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> x_any_value = variable->variable_value;

        if (x_any_value == nullptr || !std::holds_alternative<float>(x_any_value->data))
        {
            return nullptr;
        }

        universe->current_camera_cartesian_coordinates.x = std::get<float>(x_any_value->data);
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> activate_y(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable)
    {
        if (entity == nullptr || variable == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            std::shared_ptr<yli::data::AnyValue> y_any_value = variable->variable_value;

            if (y_any_value == nullptr || !std::holds_alternative<float>(y_any_value->data))
            {
                return nullptr;
            }

            movable->cartesian_coordinates.y = std::get<float>(y_any_value->data);
            movable->model_matrix[3][1] = std::get<float>(y_any_value->data);

            yli::ontology::Holobiont* const holobiont = dynamic_cast<yli::ontology::Holobiont*>(movable);

            if (holobiont != nullptr)
            {
                holobiont->update_y(std::get<float>(y_any_value->data));
            }

            return nullptr;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> y_any_value = variable->variable_value;

        if (y_any_value == nullptr || !std::holds_alternative<float>(y_any_value->data))
        {
            return nullptr;
        }

        universe->current_camera_cartesian_coordinates.y = std::get<float>(y_any_value->data);
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> activate_z(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable)
    {
        if (entity == nullptr || variable == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            std::shared_ptr<yli::data::AnyValue> z_any_value = variable->variable_value;

            if (z_any_value == nullptr || !std::holds_alternative<float>(z_any_value->data))
            {
                return nullptr;
            }

            movable->cartesian_coordinates.z = std::get<float>(z_any_value->data);
            movable->model_matrix[3][2] = std::get<float>(z_any_value->data);

            yli::ontology::Holobiont* const holobiont = dynamic_cast<yli::ontology::Holobiont*>(movable);

            if (holobiont != nullptr)
            {
                holobiont->update_z(std::get<float>(z_any_value->data));
            }

            return nullptr;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> z_any_value = variable->variable_value;

        if (z_any_value == nullptr || !std::holds_alternative<float>(z_any_value->data))
        {
            return nullptr;
        }

        universe->current_camera_cartesian_coordinates.z = std::get<float>(z_any_value->data);
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> activate_spherical_coordinates(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable)
    {
        if (entity == nullptr || variable == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            std::shared_ptr<yli::data::AnyValue> spherical_coordinates_any_value = variable->variable_value;

            if (spherical_coordinates_any_value == nullptr || !std::holds_alternative<yli::data::SphericalCoordinatesStruct*>(spherical_coordinates_any_value->data))
            {
                return nullptr;
            }

            movable->spherical_coordinates = *(std::get<yli::data::SphericalCoordinatesStruct*>(spherical_coordinates_any_value->data));
            return nullptr;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        std::shared_ptr<yli::data::AnyValue> spherical_coordinates_any_value = variable->variable_value;

        if (spherical_coordinates_any_value == nullptr || !std::holds_alternative<yli::data::SphericalCoordinatesStruct*>(spherical_coordinates_any_value->data))
        {
            return nullptr;
        }

        universe->current_camera_spherical_coordinates = *(std::get<yli::data::SphericalCoordinatesStruct*>(spherical_coordinates_any_value->data));
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> activate_rho(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable)
    {
        if (entity == nullptr || variable == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            std::shared_ptr<yli::data::AnyValue> rho_any_value = variable->variable_value;

            if (rho_any_value == nullptr || !std::holds_alternative<float>(rho_any_value->data))
            {
                return nullptr;
            }

            movable->spherical_coordinates.rho = std::get<float>(rho_any_value->data);
            return nullptr;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> rho_any_value = variable->variable_value;

        if (rho_any_value == nullptr || !std::holds_alternative<float>(rho_any_value->data))
        {
            return nullptr;
        }

        universe->current_camera_spherical_coordinates.rho = std::get<float>(rho_any_value->data);
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> activate_theta(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable)
    {
        if (entity == nullptr || variable == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            std::shared_ptr<yli::data::AnyValue> theta_any_value = variable->variable_value;

            if (theta_any_value == nullptr || !std::holds_alternative<float>(theta_any_value->data))
            {
                return nullptr;
            }

            movable->spherical_coordinates.theta = std::get<float>(theta_any_value->data);
            return nullptr;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> theta_any_value = variable->variable_value;

        if (theta_any_value == nullptr || !std::holds_alternative<float>(theta_any_value->data))
        {
            return nullptr;
        }

        universe->current_camera_spherical_coordinates.theta = std::get<float>(theta_any_value->data);
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> activate_phi(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable)
    {
        if (entity == nullptr || variable == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            std::shared_ptr<yli::data::AnyValue> phi_any_value = variable->variable_value;

            if (phi_any_value == nullptr || !std::holds_alternative<float>(phi_any_value->data))
            {
                return nullptr;
            }

            movable->spherical_coordinates.phi = std::get<float>(phi_any_value->data);
            return nullptr;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> phi_any_value = variable->variable_value;

        if (phi_any_value == nullptr || !std::holds_alternative<float>(phi_any_value->data))
        {
            return nullptr;
        }

        universe->current_camera_spherical_coordinates.phi = std::get<float>(phi_any_value->data);
        return nullptr;
    }


    std::shared_ptr<yli::data::AnyValue> activate_yaw(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable)
    {
        if (entity == nullptr || variable == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            std::shared_ptr<yli::data::AnyValue> horizontal_angle_any_value = variable->variable_value;

            if (horizontal_angle_any_value == nullptr || !std::holds_alternative<float>(horizontal_angle_any_value->data))
            {
                return nullptr;
            }

            movable->yaw = std::get<float>(horizontal_angle_any_value->data);
            return nullptr;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> horizontal_angle_any_value = variable->variable_value;

        if (horizontal_angle_any_value == nullptr || !std::holds_alternative<float>(horizontal_angle_any_value->data))
        {
            return nullptr;
        }

        universe->current_camera_horizontal_angle = std::get<float>(horizontal_angle_any_value->data);
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> activate_vertical_angle(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable)
    {
        if (entity == nullptr || variable == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            std::shared_ptr<yli::data::AnyValue> vertical_angle_any_value = variable->variable_value;

            if (vertical_angle_any_value == nullptr || !std::holds_alternative<float>(vertical_angle_any_value->data))
            {
                return nullptr;
            }

            movable->pitch = std::get<float>(vertical_angle_any_value->data);
            return nullptr;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> vertical_angle_any_value = variable->variable_value;

        if (vertical_angle_any_value == nullptr || !std::holds_alternative<float>(vertical_angle_any_value->data))
        {
            return nullptr;
        }

        universe->current_camera_vertical_angle = std::get<float>(vertical_angle_any_value->data);
        return nullptr;
    }
}
