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
#include <functional> // std::reference_wrapper
#include <iostream>   // std::cerr
#include <numbers>    // std::numbers::pi
#include <optional>   // std::optional
#include <stdexcept>  // std::runtime_error
#include <utility>    // std::move
#include <variant>    // std::holds_alternative

namespace yli::ontology
{
    class Entity;

    std::optional<yli::data::AnyValue> activate_cartesian_coordinates(
            yli::ontology::Entity& entity,
            yli::ontology::Variable& variable)
    {
        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(&entity);

        if (movable != nullptr)
        {
            const yli::data::AnyValue& cartesian_coordinates_any_value = variable.variable_value;

            if (std::holds_alternative<std::reference_wrapper<glm::vec3>>(cartesian_coordinates_any_value.data))
            {
                const glm::vec3& cartesian_coordinates =
                    std::get<std::reference_wrapper<glm::vec3>>(cartesian_coordinates_any_value.data);
                movable->location.xyz = cartesian_coordinates;
            }
            else if (std::holds_alternative<std::reference_wrapper<const glm::vec3>>(cartesian_coordinates_any_value.data))
            {
                const glm::vec3& cartesian_coordinates =
                    std::get<std::reference_wrapper<const glm::vec3>>(cartesian_coordinates_any_value.data);
                movable->location.xyz = cartesian_coordinates;
            }
            else
            {
                std::cerr << "ERROR: `yli::ontology::activate_cartesian_coordinates`: data is of invalid type!\n";
            }

            return std::nullopt;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(&entity);

        if (universe == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `yli::ontology::activate_cartesian_coordinates`: `universe` is `nullptr`!");
        }

        const yli::data::AnyValue& cartesian_coordinates_any_value = variable.variable_value;

        if (std::holds_alternative<std::reference_wrapper<glm::vec3>>(cartesian_coordinates_any_value.data))
        {
            glm::vec3 cartesian_coordinates =
                std::get<std::reference_wrapper<glm::vec3>>(cartesian_coordinates_any_value.data);
            universe->set_xyz(std::move(cartesian_coordinates));
        }
        else if (std::holds_alternative<std::reference_wrapper<const glm::vec3>>(cartesian_coordinates_any_value.data))
        {
            glm::vec3 cartesian_coordinates =
                std::get<std::reference_wrapper<const glm::vec3>>(cartesian_coordinates_any_value.data);
            universe->set_xyz(std::move(cartesian_coordinates));
        }
        else
        {
            std::cerr << "ERROR: `yli::ontology::activate_cartesian_coordinates`: data is of invalid type!\n";
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> activate_x(
            yli::ontology::Entity& entity,
            yli::ontology::Variable& variable)
    {
        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(&entity);

        if (movable != nullptr)
        {
            const yli::data::AnyValue& x_any_value = variable.variable_value;

            if (!std::holds_alternative<float>(x_any_value.data))
            {
                std::cerr << "ERROR: `yli::ontology::activate_x`: data is of invalid type!\n";
                return std::nullopt;
            }

            movable->location.set_x(std::get<float>(x_any_value.data));
            movable->model_matrix[3][0] = std::get<float>(x_any_value.data);

            yli::ontology::Holobiont* const holobiont = dynamic_cast<yli::ontology::Holobiont*>(movable);

            if (holobiont != nullptr)
            {
                holobiont->update_x(std::get<float>(x_any_value.data));
            }

            return std::nullopt;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(&entity);

        if (universe == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `yli::ontology::activate_x`: `universe` is `nullptr`!");
        }

        const yli::data::AnyValue& x_any_value = variable.variable_value;

        if (!std::holds_alternative<float>(x_any_value.data))
        {
            std::cerr << "ERROR: `yli::ontology::activate_x`: data is of invalid type!\n";
            return std::nullopt;
        }

        universe->set_x(std::get<float>(x_any_value.data));
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> activate_y(
            yli::ontology::Entity& entity,
            yli::ontology::Variable& variable)
    {
        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(&entity);

        if (movable != nullptr)
        {
            const yli::data::AnyValue& y_any_value = variable.variable_value;

            if (!std::holds_alternative<float>(y_any_value.data))
            {
                std::cerr << "ERROR: `yli::ontology::activate_y`: data is of invalid type!\n";
                return std::nullopt;
            }

            movable->location.set_y(std::get<float>(y_any_value.data));
            movable->model_matrix[3][1] = std::get<float>(y_any_value.data);

            yli::ontology::Holobiont* const holobiont = dynamic_cast<yli::ontology::Holobiont*>(movable);

            if (holobiont != nullptr)
            {
                holobiont->update_y(std::get<float>(y_any_value.data));
            }

            return std::nullopt;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(&entity);

        if (universe == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `yli::ontology::activate_y`: `universe` is `nullptr`!");
        }

        const yli::data::AnyValue& y_any_value = variable.variable_value;

        if (!std::holds_alternative<float>(y_any_value.data))
        {
            std::cerr << "ERROR: `yli::ontology::activate_y`: data is of invalid type!\n";
            return std::nullopt;
        }

        universe->set_y(std::get<float>(y_any_value.data));
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> activate_z(
            yli::ontology::Entity& entity,
            yli::ontology::Variable& variable)
    {
        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(&entity);

        if (movable != nullptr)
        {
            const yli::data::AnyValue& z_any_value = variable.variable_value;

            if (!std::holds_alternative<float>(z_any_value.data))
            {
                std::cerr << "ERROR: `yli::ontology::activate_z`: data is of invalid type!\n";
                return std::nullopt;
            }

            movable->location.set_z(std::get<float>(z_any_value.data));
            movable->model_matrix[3][2] = std::get<float>(z_any_value.data);

            yli::ontology::Holobiont* const holobiont = dynamic_cast<yli::ontology::Holobiont*>(movable);

            if (holobiont != nullptr)
            {
                holobiont->update_z(std::get<float>(z_any_value.data));
            }

            return std::nullopt;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(&entity);

        if (universe == nullptr) [[unlikely]]
        {
            throw std::runtime_error("ERROR: `yli::ontology::activate_z`: `universe` is `nullptr`!");
        }

        const yli::data::AnyValue& z_any_value = variable.variable_value;

        if (!std::holds_alternative<float>(z_any_value.data))
        {
            std::cerr << "ERROR: `yli::ontology::activate_z`: data is of invalid type!\n";
            return std::nullopt;
        }

        universe->set_z(std::get<float>(z_any_value.data));
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> activate_roll(
            yli::ontology::Entity& entity,
            yli::ontology::Variable& variable)
    {
        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(&entity);

        if (movable != nullptr)
        {
            const yli::data::AnyValue& roll_any_value = variable.variable_value;

            if (!std::holds_alternative<float>(roll_any_value.data))
            {
                return std::nullopt;
            }

            movable->orientation.roll = std::get<float>(roll_any_value.data);
            return std::nullopt;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(&entity);

        if (universe == nullptr)
        {
            return std::nullopt;
        }

        const yli::data::AnyValue& roll_any_value = variable.variable_value;

        if (!std::holds_alternative<float>(roll_any_value.data))
        {
            return std::nullopt;
        }

        universe->set_roll(std::get<float>(roll_any_value.data));
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> activate_yaw(
            yli::ontology::Entity& entity,
            yli::ontology::Variable& variable)
    {
        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(&entity);

        if (movable != nullptr)
        {
            const yli::data::AnyValue& yaw_any_value = variable.variable_value;

            if (!std::holds_alternative<float>(yaw_any_value.data))
            {
                return std::nullopt;
            }

            movable->orientation.yaw = std::get<float>(yaw_any_value.data);
            return std::nullopt;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(&entity);

        if (universe == nullptr)
        {
            return std::nullopt;
        }

        const yli::data::AnyValue& yaw_any_value = variable.variable_value;

        if (!std::holds_alternative<float>(yaw_any_value.data))
        {
            return std::nullopt;
        }

        universe->set_yaw(std::get<float>(yaw_any_value.data));
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> activate_pitch(
            yli::ontology::Entity& entity,
            yli::ontology::Variable& variable)
    {
        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(&entity);

        if (movable != nullptr)
        {
            const yli::data::AnyValue& pitch_any_value = variable.variable_value;

            if (!std::holds_alternative<float>(pitch_any_value.data))
            {
                return std::nullopt;
            }

            movable->orientation.pitch = std::get<float>(pitch_any_value.data);
            return std::nullopt;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(&entity);

        if (universe == nullptr)
        {
            return std::nullopt;
        }

        const yli::data::AnyValue& pitch_any_value = variable.variable_value;

        if (!std::holds_alternative<float>(pitch_any_value.data))
        {
            return std::nullopt;
        }

        universe->set_pitch(std::get<float>(pitch_any_value.data));
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> activate_azimuth(
            yli::ontology::Entity& entity,
            yli::ontology::Variable& variable)
    {
        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(&entity);

        if (movable != nullptr)
        {
            const yli::data::AnyValue& azimuth_any_value = variable.variable_value;

            if (!std::holds_alternative<float>(azimuth_any_value.data))
            {
                return std::nullopt;
            }

            movable->orientation.yaw = 0.5f * static_cast<float>(std::numbers::pi) - std::get<float>(azimuth_any_value.data);
            return std::nullopt;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(&entity);

        if (universe == nullptr)
        {
            return std::nullopt;
        }

        const yli::data::AnyValue& azimuth_any_value = variable.variable_value;

        if (!std::holds_alternative<float>(azimuth_any_value.data))
        {
            return std::nullopt;
        }

        universe->set_yaw(0.5f * static_cast<float>(std::numbers::pi) - std::get<float>(azimuth_any_value.data));
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> activate_scale(
            yli::ontology::Entity& entity,
            yli::ontology::Variable& variable)
    {
        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(&entity);

        if (movable != nullptr)
        {
            const yli::data::AnyValue& scale_any_value = variable.variable_value;

            if (std::holds_alternative<float>(scale_any_value.data))
            {
                movable->scale = std::get<float>(scale_any_value.data);
            }
        }

        return std::nullopt;
    }
}
