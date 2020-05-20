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

#include "setting.hpp"
#include "setting_master.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/ontology/entity.hpp"
#include "code/ylikuutio/ontology/movable.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/holobiont.hpp"
#include "code/ylikuutio/ontology/console.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"
#include "code/ylikuutio/sdl/ylikuutio_sdl.hpp"

// Include standard headers
#include <stdint.h>      // uint32_t etc.
#include <limits>        // std::numeric_limits
#include <memory>        // std::make_shared, std::shared_ptr
#include <variant>       // std::variant

namespace yli::data
{
    class SphericalCoordinatesStruct;
}

namespace yli::config
{
    std::shared_ptr<yli::data::AnyValue> Setting::activate_planet_radius(yli::ontology::Entity* const entity, yli::config::Setting* const setting)
    {
        if (entity == nullptr || setting == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Species* const species = dynamic_cast<yli::ontology::Species*>(entity);

        if (species == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> planet_radius_any_value = setting->setting_value;

        if (planet_radius_any_value == nullptr || !std::holds_alternative<float>(planet_radius_any_value->data))
        {
            return nullptr;
        }

        species->planet_radius = std::get<float>(planet_radius_any_value->data);

        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Setting::activate_window_size(yli::ontology::Entity* const entity, yli::config::Setting* const setting)
    {
        if (entity == nullptr || setting == nullptr)
        {
            return nullptr;
        }

        // window width.
        std::shared_ptr<yli::data::AnyValue> window_width_any_value = setting->setting_value;

        if (window_width_any_value == nullptr || !std::holds_alternative<uint32_t>(window_width_any_value->data))
        {
            return nullptr;
        }

        uint32_t window_width = std::get<uint32_t>(window_width_any_value->data);

        // window height.
        std::shared_ptr<yli::data::AnyValue> window_height_any_value = setting->setting_value;

        if (window_height_any_value == nullptr || !std::holds_alternative<uint32_t>(window_height_any_value->data))
        {
            return nullptr;
        }

        uint32_t window_height = std::get<uint32_t>(window_height_any_value->data);

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        if (window_width <= std::numeric_limits<int>::max() &&
                window_height <= std::numeric_limits<int>::max())
        {
            yli::sdl::set_window_size(universe->get_window(), static_cast<int>(window_width), static_cast<int>(window_height));
        }

        universe->set_window_width(window_width);
        universe->set_window_height(window_height);

        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Setting::activate_framebuffer_size(yli::ontology::Entity* const entity, yli::config::Setting* const setting)
    {
        if (entity == nullptr || setting == nullptr)
        {
            return nullptr;
        }

        // framebuffer width.
        std::shared_ptr<yli::data::AnyValue> framebuffer_width_any_value = setting->setting_value;

        if (framebuffer_width_any_value == nullptr || !std::holds_alternative<uint32_t>(framebuffer_width_any_value->data))
        {
            return nullptr;
        }

        uint32_t framebuffer_width = std::get<uint32_t>(framebuffer_width_any_value->data);

        // framebuffer height.
        std::shared_ptr<yli::data::AnyValue> framebuffer_height_any_value = setting->setting_value;

        if (framebuffer_height_any_value == nullptr || !std::holds_alternative<uint32_t>(framebuffer_height_any_value->data))
        {
            return nullptr;
        }

        uint32_t framebuffer_height = std::get<uint32_t>(framebuffer_height_any_value->data);

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        universe->set_framebuffer_width(framebuffer_width);
        universe->set_framebuffer_height(framebuffer_height);

        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Setting::activate_background_color(yli::ontology::Entity* const entity, yli::config::Setting* const setting)
    {
        if (entity == nullptr || setting == nullptr)
        {
            return nullptr;
        }

        yli::config::SettingMaster* setting_master = setting->parent;

        if (setting_master == nullptr)
        {
            return nullptr;
        }

        if (setting_master->setting_pointer_map.count("red") != 1 ||
                setting_master->setting_pointer_map.count("green") != 1 ||
                setting_master->setting_pointer_map.count("blue") != 1 ||
                setting_master->setting_pointer_map.count("alpha") != 1)
        {
            return nullptr;
        }

        // red.
        std::shared_ptr<yli::data::AnyValue> red_any_value = setting_master->setting_pointer_map["red"]->get();

        if (red_any_value == nullptr || !std::holds_alternative<float>(red_any_value->data))
        {
            return nullptr;
        }

        float red = std::get<float>(red_any_value->data);

        // green.
        std::shared_ptr<yli::data::AnyValue> green_any_value = setting_master->setting_pointer_map["green"]->get();

        if (green_any_value == nullptr || !std::holds_alternative<float>(green_any_value->data))
        {
            return nullptr;
        }

        float green = std::get<float>(green_any_value->data);

        // blue.
        std::shared_ptr<yli::data::AnyValue> blue_any_value = setting_master->setting_pointer_map["blue"]->get();

        if (blue_any_value == nullptr || !std::holds_alternative<float>(blue_any_value->data))
        {
            return nullptr;
        }

        float blue = std::get<float>(blue_any_value->data);

        // alpha.
        std::shared_ptr<yli::data::AnyValue> alpha_any_value = setting_master->setting_pointer_map["alpha"]->get();

        if (alpha_any_value == nullptr || !std::holds_alternative<float>(alpha_any_value->data))
        {
            return nullptr;
        }

        float alpha = std::get<float>(alpha_any_value->data);

        yli::opengl::set_background_color(red, green, blue, alpha);

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        universe->background_red = red;
        universe->background_green = green;
        universe->background_blue = blue;
        universe->background_alpha = alpha;

        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Setting::activate_wireframe(yli::ontology::Entity* const entity, yli::config::Setting* const setting)
    {
        if (entity == nullptr || setting == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> wireframe_any_value = setting->setting_value;

        if (wireframe_any_value == nullptr || !std::holds_alternative<bool>(wireframe_any_value->data))
        {
            return nullptr;
        }

        yli::opengl::set_wireframe(std::get<bool>(wireframe_any_value->data));
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Setting::activate_should_be_rendered(yli::ontology::Entity* const entity, yli::config::Setting* const setting)
    {
        if (entity == nullptr || setting == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> should_be_rendered_any_value = setting->setting_value;

        if (should_be_rendered_any_value == nullptr || !std::holds_alternative<bool>(should_be_rendered_any_value->data))
        {
            return nullptr;
        }

        entity->should_be_rendered = std::get<bool>(should_be_rendered_any_value->data);
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Setting::activate_spherical_coordinates(yli::ontology::Entity* const entity, yli::config::Setting* const setting)
    {
        if (entity == nullptr || setting == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            std::shared_ptr<yli::data::AnyValue> spherical_coordinates_any_value = setting->setting_value;

            if (spherical_coordinates_any_value == nullptr || !std::holds_alternative<yli::data::SphericalCoordinatesStruct*>(spherical_coordinates_any_value->data))
            {
                return nullptr;
            }

            movable->spherical_coordinates = *(std::get<yli::data::SphericalCoordinatesStruct*>(spherical_coordinates_any_value->data));
            return nullptr;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        std::shared_ptr<yli::data::AnyValue> spherical_coordinates_any_value = setting->setting_value;

        if (spherical_coordinates_any_value == nullptr || !std::holds_alternative<yli::data::SphericalCoordinatesStruct*>(spherical_coordinates_any_value->data))
        {
            return nullptr;
        }

        universe->current_camera_spherical_coordinates = *(std::get<yli::data::SphericalCoordinatesStruct*>(spherical_coordinates_any_value->data));
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Setting::activate_rho(yli::ontology::Entity* const entity, yli::config::Setting* const setting)
    {
        if (entity == nullptr || setting == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            std::shared_ptr<yli::data::AnyValue> rho_any_value = setting->setting_value;

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

        std::shared_ptr<yli::data::AnyValue> rho_any_value = setting->setting_value;

        if (rho_any_value == nullptr || !std::holds_alternative<float>(rho_any_value->data))
        {
            return nullptr;
        }

        universe->current_camera_spherical_coordinates.rho = std::get<float>(rho_any_value->data);
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Setting::activate_theta(yli::ontology::Entity* const entity, yli::config::Setting* const setting)
    {
        if (entity == nullptr || setting == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            std::shared_ptr<yli::data::AnyValue> theta_any_value = setting->setting_value;

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

        std::shared_ptr<yli::data::AnyValue> theta_any_value = setting->setting_value;

        if (theta_any_value == nullptr || !std::holds_alternative<float>(theta_any_value->data))
        {
            return nullptr;
        }

        universe->current_camera_spherical_coordinates.theta = std::get<float>(theta_any_value->data);
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Setting::activate_phi(yli::ontology::Entity* const entity, yli::config::Setting* const setting)
    {
        if (entity == nullptr || setting == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            std::shared_ptr<yli::data::AnyValue> phi_any_value = setting->setting_value;

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

        std::shared_ptr<yli::data::AnyValue> phi_any_value = setting->setting_value;

        if (phi_any_value == nullptr || !std::holds_alternative<float>(phi_any_value->data))
        {
            return nullptr;
        }

        universe->current_camera_spherical_coordinates.phi = std::get<float>(phi_any_value->data);
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Setting::activate_cartesian_coordinates(yli::ontology::Entity* const entity, yli::config::Setting* const setting)
    {
        if (entity == nullptr || setting == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            std::shared_ptr<yli::data::AnyValue> cartesian_coordinates_any_value = setting->setting_value;

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

        std::shared_ptr<yli::data::AnyValue> cartesian_coordinates_any_value = setting->setting_value;

        if (cartesian_coordinates_any_value == nullptr || !std::holds_alternative<std::shared_ptr<glm::vec3>>(cartesian_coordinates_any_value->data))
        {
            return nullptr;
        }

        universe->current_camera_cartesian_coordinates = *(std::get<std::shared_ptr<glm::vec3>>(cartesian_coordinates_any_value->data));
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Setting::activate_x(yli::ontology::Entity* const entity, yli::config::Setting* const setting)
    {
        if (entity == nullptr || setting == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            std::shared_ptr<yli::data::AnyValue> x_any_value = setting->setting_value;

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

        std::shared_ptr<yli::data::AnyValue> x_any_value = setting->setting_value;

        if (x_any_value == nullptr || !std::holds_alternative<float>(x_any_value->data))
        {
            return nullptr;
        }

        universe->current_camera_cartesian_coordinates.x = std::get<float>(x_any_value->data);
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Setting::activate_y(yli::ontology::Entity* const entity, yli::config::Setting* const setting)
    {
        if (entity == nullptr || setting == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            std::shared_ptr<yli::data::AnyValue> y_any_value = setting->setting_value;

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

        std::shared_ptr<yli::data::AnyValue> y_any_value = setting->setting_value;

        if (y_any_value == nullptr || !std::holds_alternative<float>(y_any_value->data))
        {
            return nullptr;
        }

        universe->current_camera_cartesian_coordinates.y = std::get<float>(y_any_value->data);
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Setting::activate_z(yli::ontology::Entity* const entity, yli::config::Setting* const setting)
    {
        if (entity == nullptr || setting == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            std::shared_ptr<yli::data::AnyValue> z_any_value = setting->setting_value;

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

        std::shared_ptr<yli::data::AnyValue> z_any_value = setting->setting_value;

        if (z_any_value == nullptr || !std::holds_alternative<float>(z_any_value->data))
        {
            return nullptr;
        }

        universe->current_camera_cartesian_coordinates.z = std::get<float>(z_any_value->data);
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Setting::activate_horizontal_angle(yli::ontology::Entity* const entity, yli::config::Setting* const setting)
    {
        if (entity == nullptr || setting == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            std::shared_ptr<yli::data::AnyValue> horizontal_angle_any_value = setting->setting_value;

            if (horizontal_angle_any_value == nullptr || !std::holds_alternative<double>(horizontal_angle_any_value->data))
            {
                return nullptr;
            }

            movable->horizontal_angle = std::get<double>(horizontal_angle_any_value->data);
            return nullptr;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> horizontal_angle_any_value = setting->setting_value;

        if (horizontal_angle_any_value == nullptr || !std::holds_alternative<double>(horizontal_angle_any_value->data))
        {
            return nullptr;
        }

        universe->current_camera_horizontal_angle = std::get<double>(horizontal_angle_any_value->data);
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Setting::activate_vertical_angle(yli::ontology::Entity* const entity, yli::config::Setting* const setting)
    {
        if (entity == nullptr || setting == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            std::shared_ptr<yli::data::AnyValue> vertical_angle_any_value = setting->setting_value;

            if (vertical_angle_any_value == nullptr || !std::holds_alternative<double>(vertical_angle_any_value->data))
            {
                return nullptr;
            }

            movable->vertical_angle = std::get<double>(vertical_angle_any_value->data);
            return nullptr;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> vertical_angle_any_value = setting->setting_value;

        if (vertical_angle_any_value == nullptr || !std::holds_alternative<double>(vertical_angle_any_value->data))
        {
            return nullptr;
        }

        universe->current_camera_vertical_angle = std::get<double>(vertical_angle_any_value->data);
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Setting::activate_speed(yli::ontology::Entity* const entity, yli::config::Setting* const setting)
    {
        if (entity == nullptr || setting == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> speed_any_value = setting->setting_value;

        if (speed_any_value == nullptr || !std::holds_alternative<float>(speed_any_value->data))
        {
            return nullptr;
        }

        universe->speed = std::get<float>(speed_any_value->data);
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Setting::activate_turbo_factor(yli::ontology::Entity* const entity, yli::config::Setting* const setting)
    {
        if (entity == nullptr || setting == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> turbo_factor_any_value = setting->setting_value;

        if (turbo_factor_any_value == nullptr || !std::holds_alternative<float>(turbo_factor_any_value->data))
        {
            return nullptr;
        }

        universe->turbo_factor = std::get<float>(turbo_factor_any_value->data);
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Setting::activate_twin_turbo_factor(yli::ontology::Entity* const entity, yli::config::Setting* const setting)
    {
        if (entity == nullptr || setting == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> twin_turbo_factor_any_value = setting->setting_value;

        if (twin_turbo_factor_any_value == nullptr || !std::holds_alternative<float>(twin_turbo_factor_any_value->data))
        {
            return nullptr;
        }

        universe->twin_turbo_factor = std::get<float>(twin_turbo_factor_any_value->data);
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Setting::activate_mouse_speed(yli::ontology::Entity* const entity, yli::config::Setting* const setting)
    {
        if (entity == nullptr || setting == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> mouse_speed_any_value = setting->setting_value;

        if (mouse_speed_any_value == nullptr || !std::holds_alternative<float>(mouse_speed_any_value->data))
        {
            return nullptr;
        }

        universe->mouse_speed = std::get<float>(mouse_speed_any_value->data);
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Setting::activate_is_flight_mode_in_use(yli::ontology::Entity* const entity, yli::config::Setting* const setting)
    {
        if (entity == nullptr || setting == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Scene* const scene = dynamic_cast<yli::ontology::Scene*>(entity);

        if (scene == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> is_flight_mode_in_use_any_value = setting->setting_value;

        if (is_flight_mode_in_use_any_value == nullptr || !std::holds_alternative<bool>(is_flight_mode_in_use_any_value->data))
        {
            return nullptr;
        }

        scene->set_is_flight_mode_in_use(std::get<bool>(is_flight_mode_in_use_any_value->data));
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Setting::activate_console_top_y(yli::ontology::Entity* const entity, yli::config::Setting* const setting)
    {
        if (entity == nullptr || setting == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> console_top_y_any_value = setting->setting_value;

        if (console_top_y_any_value == nullptr || !std::holds_alternative<uint32_t>(console_top_y_any_value->data))
        {
            return nullptr;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Console* const console = universe->get_active_console();

        if (console == nullptr)
        {
            return nullptr;
        }

        console->set_console_top_y(std::get<uint32_t>(console_top_y_any_value->data));
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Setting::activate_console_bottom_y(yli::ontology::Entity* const entity, yli::config::Setting* const setting)
    {
        if (entity == nullptr || setting == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> console_bottom_y_any_value = setting->setting_value;

        if (console_bottom_y_any_value == nullptr || !std::holds_alternative<uint32_t>(console_bottom_y_any_value->data))
        {
            return nullptr;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Console* const console = universe->get_active_console();

        if (console == nullptr)
        {
            return nullptr;
        }

        console->set_console_bottom_y(std::get<uint32_t>(console_bottom_y_any_value->data));
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Setting::activate_console_left_x(yli::ontology::Entity* const entity, yli::config::Setting* const setting)
    {
        if (entity == nullptr || setting == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> console_left_x_any_value = setting->setting_value;

        if (console_left_x_any_value == nullptr || !std::holds_alternative<uint32_t>(console_left_x_any_value->data))
        {
            return nullptr;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Console* const console = universe->get_active_console();

        if (console == nullptr)
        {
            return nullptr;
        }

        console->set_console_left_x(std::get<uint32_t>(console_left_x_any_value->data));
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Setting::activate_console_right_x(yli::ontology::Entity* const entity, yli::config::Setting* const setting)
    {
        if (entity == nullptr || setting == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> console_right_x_any_value = setting->setting_value;

        if (console_right_x_any_value == nullptr || !std::holds_alternative<uint32_t>(console_right_x_any_value->data))
        {
            return nullptr;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Console* const console = universe->get_active_console();

        if (console == nullptr)
        {
            return nullptr;
        }

        console->set_console_right_x(std::get<uint32_t>(console_right_x_any_value->data));
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Setting::read_should_be_rendered(yli::ontology::Entity* const entity)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        return std::make_shared<yli::data::AnyValue>(entity->should_be_rendered);
    }

    std::shared_ptr<yli::data::AnyValue> Setting::read_cartesian_coordinates(yli::ontology::Entity* const entity)
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

    std::shared_ptr<yli::data::AnyValue> Setting::read_x(yli::ontology::Entity* const entity)
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

    std::shared_ptr<yli::data::AnyValue> Setting::read_y(yli::ontology::Entity* const entity)
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

    std::shared_ptr<yli::data::AnyValue> Setting::read_z(yli::ontology::Entity* const entity)
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

    std::shared_ptr<yli::data::AnyValue> Setting::read_rho(yli::ontology::Entity* const entity)
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

    std::shared_ptr<yli::data::AnyValue> Setting::read_theta(yli::ontology::Entity* const entity)
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

    std::shared_ptr<yli::data::AnyValue> Setting::read_phi(yli::ontology::Entity* const entity)
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

    std::shared_ptr<yli::data::AnyValue> Setting::read_up(yli::ontology::Entity* const entity)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        return std::make_shared<yli::data::AnyValue>(&universe->current_camera_up);
    }

    std::shared_ptr<yli::data::AnyValue> Setting::read_right(yli::ontology::Entity* const entity)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        return std::make_shared<yli::data::AnyValue>(&universe->current_camera_right);
    }

    std::shared_ptr<yli::data::AnyValue> Setting::read_horizontal_angle(yli::ontology::Entity* const entity)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            return std::make_shared<yli::data::AnyValue>(movable->horizontal_angle);
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        return std::make_shared<yli::data::AnyValue>(universe->current_camera_horizontal_angle);
    }

    std::shared_ptr<yli::data::AnyValue> Setting::read_vertical_angle(yli::ontology::Entity* const entity)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            return std::make_shared<yli::data::AnyValue>(movable->vertical_angle);
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        return std::make_shared<yli::data::AnyValue>(universe->current_camera_vertical_angle);
    }

    std::shared_ptr<yli::data::AnyValue> Setting::read_is_flight_mode_in_use(yli::ontology::Entity* const entity)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Scene* const scene = dynamic_cast<yli::ontology::Scene*>(entity);

        if (scene == nullptr)
        {
            return nullptr;
        }

        return std::make_shared<yli::data::AnyValue>(scene->get_is_flight_mode_in_use());
    }
}
