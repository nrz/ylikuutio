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

#include "setting_master.hpp"
#include "setting.hpp"
#include "code/ylikuutio/ontology/console.hpp"
#include "code/ylikuutio/ontology/entity.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/holobiont.hpp"
#include "code/ylikuutio/ontology/movable.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"
#include "code/ylikuutio/map/ylikuutio_map.hpp"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/sdl/ylikuutio_sdl.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <iostream>      // std::cout, std::cin, std::cerr
#include <limits>        // std::numeric_limits
#include <memory>        // std::make_shared, std::shared_ptr
#include <stdint.h>      // uint32_t etc.
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <variant>       // std::variant
#include <vector>        // std::vector

namespace yli::ontology
{
    class Entity;
}

namespace yli::config
{
    struct SettingStruct;

    SettingMaster::SettingMaster(yli::ontology::Entity* const entity)
    {
        // constructor.
        this->parent = entity;
        this->number_of_settings = 0;
    }

    SettingMaster::~SettingMaster()
    {
        // destructor.

        // destroy all `Setting`s of this `SettingMaster`.
        std::cout << "All `Setting`s of this `SettingMaster` will be destroyed.\n";
        yli::hierarchy::delete_children<yli::config::Setting*>(this->setting_pointer_vector, this->number_of_settings);
    }

    void SettingMaster::create_setting(const yli::config::SettingStruct& setting_struct)
    {
        new yli::config::Setting(this, setting_struct);
    }

    bool SettingMaster::is_setting(const std::string& setting_name) const
    {
        return this->setting_pointer_map.count(setting_name) == 1;
    }

    std::string SettingMaster::help() const
    {
        std::string help_string = "TODO: create general helptext";
        return help_string;
    }

    std::string SettingMaster::help(const std::string& setting_name) const
    {
        if (this->is_setting(setting_name))
        {
            yli::config::Setting* setting = this->setting_pointer_map.at(setting_name);

            if (setting != nullptr)
            {
                return setting->help();
            }
        }
        return this->help();
    }

    bool SettingMaster::set(const std::string& setting_name, std::shared_ptr<yli::common::AnyValue> setting_new_any_value)
    {
        if (!this->is_setting(setting_name))
        {
            return false;
        }

        // OK, this is a valid variable name.
        // Set the variable value and activate it by
        // calling the corresponding activate callback.
        yli::config::Setting* setting = this->setting_pointer_map[setting_name];

        setting->setting_value = setting_new_any_value;
        setting->activate_callback(this->parent, this);
        return true;
    }

    yli::config::Setting* SettingMaster::get(const std::string& setting_name) const
    {
        if (this->setting_pointer_map.count(setting_name) != 1)
        {
            return nullptr;
        }

        return this->setting_pointer_map.at(setting_name);
    }

    // public callbacks.

    std::shared_ptr<yli::common::AnyValue> SettingMaster::print_settings0(
            yli::ontology::Universe* const universe,
            yli::ontology::Console* const console)
    {
        if (universe == nullptr || console == nullptr)
        {
            return nullptr;
        }

        // Print global variable names.
        yli::config::SettingMaster* setting_master = universe->get_setting_master();

        if (setting_master == nullptr)
        {
            return nullptr;
        }

        yli::map::print_keys_to_console<yli::config::Setting*>(setting_master->setting_pointer_map, console);

        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> SettingMaster::print_settings1(
            yli::ontology::Universe* const universe,
            yli::ontology::Console* const console,
            yli::ontology::Entity* const entity)
    {
        if (universe == nullptr || console == nullptr || entity == nullptr)
        {
            return nullptr;
        }

        // Print the variable names of the `Entity`.

        yli::config::SettingMaster* const setting_master = entity->get_setting_master();

        if (setting_master == nullptr)
        {
            return nullptr;
        }

        yli::map::print_keys_to_console<yli::config::Setting*>(setting_master->setting_pointer_map, console);

        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> SettingMaster::activate_planet_radius(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Species* const species = dynamic_cast<yli::ontology::Species*>(entity);

        if (species == nullptr)
        {
            return nullptr;
        }

        if (setting_master->setting_pointer_map.count("planet_radius") != 1)
        {
            return nullptr;
        }

        std::shared_ptr<yli::common::AnyValue> planet_radius_any_value = setting_master->setting_pointer_map["planet_radius"]->setting_value;

        if (planet_radius_any_value == nullptr || !std::holds_alternative<float>(planet_radius_any_value->data))
        {
            return nullptr;
        }

        species->planet_radius = std::get<float>(planet_radius_any_value->data);

        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> SettingMaster::activate_window_size(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        if (setting_master->setting_pointer_map.count("window_width") != 1 ||
                setting_master->setting_pointer_map.count("window_height") != 1)
        {
            return nullptr;
        }

        // window width.
        std::shared_ptr<yli::common::AnyValue> window_width_any_value = setting_master->setting_pointer_map["window_width"]->setting_value;

        if (window_width_any_value == nullptr || !std::holds_alternative<uint32_t>(window_width_any_value->data))
        {
            return nullptr;
        }

        uint32_t window_width = std::get<uint32_t>(window_width_any_value->data);

        // window height.
        std::shared_ptr<yli::common::AnyValue> window_height_any_value = setting_master->setting_pointer_map["window_height"]->setting_value;

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

    std::shared_ptr<yli::common::AnyValue> SettingMaster::activate_framebuffer_size(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        if (setting_master->setting_pointer_map.count("framebuffer_width") != 1 ||
                setting_master->setting_pointer_map.count("framebuffer_height") != 1)
        {
            return nullptr;
        }

        // framebuffer width.
        std::shared_ptr<yli::common::AnyValue> framebuffer_width_any_value = setting_master->setting_pointer_map["framebuffer_width"]->setting_value;

        if (framebuffer_width_any_value == nullptr || !std::holds_alternative<uint32_t>(framebuffer_width_any_value->data))
        {
            return nullptr;
        }

        uint32_t framebuffer_width = std::get<uint32_t>(framebuffer_width_any_value->data);

        // framebuffer height.
        std::shared_ptr<yli::common::AnyValue> framebuffer_height_any_value = setting_master->setting_pointer_map["framebuffer_height"]->setting_value;

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

    std::shared_ptr<yli::common::AnyValue> SettingMaster::activate_background_color(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
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
        std::shared_ptr<yli::common::AnyValue> red_any_value = setting_master->setting_pointer_map["red"]->setting_value;

        if (red_any_value == nullptr || !std::holds_alternative<float>(red_any_value->data))
        {
            return nullptr;
        }

        float red = std::get<float>(red_any_value->data);

        // green.
        std::shared_ptr<yli::common::AnyValue> green_any_value = setting_master->setting_pointer_map["green"]->setting_value;

        if (green_any_value == nullptr || !std::holds_alternative<float>(green_any_value->data))
        {
            return nullptr;
        }

        float green = std::get<float>(green_any_value->data);

        // blue.
        std::shared_ptr<yli::common::AnyValue> blue_any_value = setting_master->setting_pointer_map["blue"]->setting_value;

        if (blue_any_value == nullptr || !std::holds_alternative<float>(blue_any_value->data))
        {
            return nullptr;
        }

        float blue = std::get<float>(blue_any_value->data);

        // alpha.
        std::shared_ptr<yli::common::AnyValue> alpha_any_value = setting_master->setting_pointer_map["alpha"]->setting_value;

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

    std::shared_ptr<yli::common::AnyValue> SettingMaster::activate_wireframe(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        if (setting_master->setting_pointer_map.count("wireframe") != 1)
        {
            return nullptr;
        }

        std::shared_ptr<yli::common::AnyValue> wireframe_any_value = setting_master->setting_pointer_map["wireframe"]->setting_value;

        if (wireframe_any_value == nullptr || !std::holds_alternative<bool>(wireframe_any_value->data))
        {
            return nullptr;
        }

        yli::opengl::set_wireframe(std::get<bool>(wireframe_any_value->data));
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> SettingMaster::activate_should_be_rendered(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        if (setting_master->setting_pointer_map.count("should_be_rendered") != 1)
        {
            return nullptr;
        }

        std::shared_ptr<yli::common::AnyValue> should_be_rendered_any_value = setting_master->setting_pointer_map["should_be_rendered"]->setting_value;

        if (should_be_rendered_any_value == nullptr || !std::holds_alternative<bool>(should_be_rendered_any_value->data))
        {
            return nullptr;
        }

        entity->should_be_rendered = std::get<bool>(should_be_rendered_any_value->data);
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> SettingMaster::activate_spherical_coordinates(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            if (setting_master->setting_pointer_map.count("spherical_coordinates") != 1)
            {
                return nullptr;
            }

            std::shared_ptr<yli::common::AnyValue> spherical_coordinates_any_value = setting_master->setting_pointer_map["spherical_coordinates"]->setting_value;

            if (spherical_coordinates_any_value == nullptr || !std::holds_alternative<yli::common::SphericalCoordinatesStruct*>(spherical_coordinates_any_value->data))
            {
                return nullptr;
            }

            movable->spherical_coordinates = *(std::get<yli::common::SphericalCoordinatesStruct*>(spherical_coordinates_any_value->data));
            return nullptr;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr || setting_master->setting_pointer_map.count("spherical_coordinates") != 1)
        {
            return nullptr;
        }

        std::shared_ptr<yli::common::AnyValue> spherical_coordinates_any_value = setting_master->setting_pointer_map["spherical_coordinates"]->setting_value;

        if (spherical_coordinates_any_value == nullptr || !std::holds_alternative<yli::common::SphericalCoordinatesStruct*>(spherical_coordinates_any_value->data))
        {
            return nullptr;
        }

        universe->current_camera_spherical_coordinates = *(std::get<yli::common::SphericalCoordinatesStruct*>(spherical_coordinates_any_value->data));
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> SettingMaster::activate_rho(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            if (setting_master->setting_pointer_map.count("spherical_coordinates") != 1)
            {
                return nullptr;
            }

            std::shared_ptr<yli::common::AnyValue> rho_any_value = setting_master->setting_pointer_map["rho"]->setting_value;

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

        if (setting_master->setting_pointer_map.count("spherical_coordinates") != 1)
        {
            return nullptr;
        }

        std::shared_ptr<yli::common::AnyValue> rho_any_value = setting_master->setting_pointer_map["rho"]->setting_value;

        if (rho_any_value == nullptr || !std::holds_alternative<float>(rho_any_value->data))
        {
            return nullptr;
        }

        universe->current_camera_spherical_coordinates.rho = std::get<float>(rho_any_value->data);
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> SettingMaster::activate_theta(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            if (setting_master->setting_pointer_map.count("spherical_coordinates") != 1)
            {
                return nullptr;
            }

            std::shared_ptr<yli::common::AnyValue> theta_any_value = setting_master->setting_pointer_map["theta"]->setting_value;

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

        if (setting_master->setting_pointer_map.count("spherical_coordinates") != 1)
        {
            return nullptr;
        }

        std::shared_ptr<yli::common::AnyValue> theta_any_value = setting_master->setting_pointer_map["theta"]->setting_value;

        if (theta_any_value == nullptr || !std::holds_alternative<float>(theta_any_value->data))
        {
            return nullptr;
        }

        universe->current_camera_spherical_coordinates.theta = std::get<float>(theta_any_value->data);
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> SettingMaster::activate_phi(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            if (setting_master->setting_pointer_map.count("spherical_coordinates") != 1)
            {
                return nullptr;
            }

            std::shared_ptr<yli::common::AnyValue> phi_any_value = setting_master->setting_pointer_map["phi"]->setting_value;

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

        if (setting_master->setting_pointer_map.count("spherical_coordinates") != 1)
        {
            return nullptr;
        }

        std::shared_ptr<yli::common::AnyValue> phi_any_value = setting_master->setting_pointer_map["phi"]->setting_value;

        if (phi_any_value == nullptr || !std::holds_alternative<float>(phi_any_value->data))
        {
            return nullptr;
        }

        universe->current_camera_spherical_coordinates.phi = std::get<float>(phi_any_value->data);
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> SettingMaster::activate_cartesian_coordinates(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            if (setting_master->setting_pointer_map.count("cartesian_coordinates") != 1)
            {
                return nullptr;
            }

            std::shared_ptr<yli::common::AnyValue> cartesian_coordinates_any_value = setting_master->setting_pointer_map["cartesian_coordinates"]->setting_value;

            if (cartesian_coordinates_any_value == nullptr || !std::holds_alternative<std::shared_ptr<glm::vec3>>(cartesian_coordinates_any_value->data))
            {
                return nullptr;
            }

            movable->cartesian_coordinates = *(std::get<std::shared_ptr<glm::vec3>>(cartesian_coordinates_any_value->data));
            return nullptr;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr || setting_master->setting_pointer_map.count("cartesian_coordinates") != 1)
        {
            return nullptr;
        }

        std::shared_ptr<yli::common::AnyValue> cartesian_coordinates_any_value = setting_master->setting_pointer_map["cartesian_coordinates"]->setting_value;

        if (cartesian_coordinates_any_value == nullptr || !std::holds_alternative<std::shared_ptr<glm::vec3>>(cartesian_coordinates_any_value->data))
        {
            return nullptr;
        }

        universe->current_camera_cartesian_coordinates = *(std::get<std::shared_ptr<glm::vec3>>(cartesian_coordinates_any_value->data));
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> SettingMaster::activate_x(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            if (setting_master->setting_pointer_map.count("x") != 1)
            {
                return nullptr;
            }

            std::shared_ptr<yli::common::AnyValue> x_any_value = setting_master->setting_pointer_map["x"]->setting_value;

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

        if (setting_master->setting_pointer_map.count("x") != 1)
        {
            return nullptr;
        }

        std::shared_ptr<yli::common::AnyValue> x_any_value = setting_master->setting_pointer_map["x"]->setting_value;

        if (x_any_value == nullptr || !std::holds_alternative<float>(x_any_value->data))
        {
            return nullptr;
        }

        universe->current_camera_cartesian_coordinates.x = std::get<float>(x_any_value->data);
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> SettingMaster::activate_y(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            if (setting_master->setting_pointer_map.count("y") != 1)
            {
                return nullptr;
            }

            std::shared_ptr<yli::common::AnyValue> y_any_value = setting_master->setting_pointer_map["y"]->setting_value;

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

        if (setting_master->setting_pointer_map.count("y") != 1)
        {
            return nullptr;
        }

        std::shared_ptr<yli::common::AnyValue> y_any_value = setting_master->setting_pointer_map["y"]->setting_value;

        if (y_any_value == nullptr || !std::holds_alternative<float>(y_any_value->data))
        {
            return nullptr;
        }

        universe->current_camera_cartesian_coordinates.y = std::get<float>(y_any_value->data);
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> SettingMaster::activate_z(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            if (setting_master->setting_pointer_map.count("z") != 1)
            {
                return nullptr;
            }

            std::shared_ptr<yli::common::AnyValue> z_any_value = setting_master->setting_pointer_map["z"]->setting_value;

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

        if (setting_master->setting_pointer_map.count("z") != 1)
        {
            return nullptr;
        }

        std::shared_ptr<yli::common::AnyValue> z_any_value = setting_master->setting_pointer_map["z"]->setting_value;

        if (z_any_value == nullptr || !std::holds_alternative<float>(z_any_value->data))
        {
            return nullptr;
        }

        universe->current_camera_cartesian_coordinates.z = std::get<float>(z_any_value->data);
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> SettingMaster::activate_horizontal_angle(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            if (setting_master->setting_pointer_map.count("horizontal_angle") != 1)
            {
                return nullptr;
            }

            std::shared_ptr<yli::common::AnyValue> horizontal_angle_any_value = setting_master->setting_pointer_map["horizontal_angle"]->setting_value;

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

        if (setting_master->setting_pointer_map.count("horizontal_angle") != 1)
        {
            return nullptr;
        }

        std::shared_ptr<yli::common::AnyValue> horizontal_angle_any_value = setting_master->setting_pointer_map["horizontal_angle"]->setting_value;

        if (horizontal_angle_any_value == nullptr || !std::holds_alternative<double>(horizontal_angle_any_value->data))
        {
            return nullptr;
        }

        universe->current_camera_horizontal_angle = std::get<double>(horizontal_angle_any_value->data);
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> SettingMaster::activate_vertical_angle(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            if (setting_master->setting_pointer_map.count("vertical_angle") != 1)
            {
                return nullptr;
            }

            std::shared_ptr<yli::common::AnyValue> vertical_angle_any_value = setting_master->setting_pointer_map["vertical_angle"]->setting_value;

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

        if (setting_master->setting_pointer_map.count("vertical_angle") != 1)
        {
            return nullptr;
        }

        std::shared_ptr<yli::common::AnyValue> vertical_angle_any_value = setting_master->setting_pointer_map["vertical_angle"]->setting_value;

        if (vertical_angle_any_value == nullptr || !std::holds_alternative<double>(vertical_angle_any_value->data))
        {
            return nullptr;
        }

        universe->current_camera_vertical_angle = std::get<double>(vertical_angle_any_value->data);
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> SettingMaster::activate_speed(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        if (setting_master->setting_pointer_map.count("speed") != 1)
        {
            return nullptr;
        }

        std::shared_ptr<yli::common::AnyValue> speed_any_value = setting_master->setting_pointer_map["speed"]->setting_value;

        if (speed_any_value == nullptr || !std::holds_alternative<float>(speed_any_value->data))
        {
            return nullptr;
        }

        universe->speed = std::get<float>(speed_any_value->data);
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> SettingMaster::activate_turbo_factor(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        if (setting_master->setting_pointer_map.count("turbo_factor") != 1)
        {
            return nullptr;
        }

        std::shared_ptr<yli::common::AnyValue> turbo_factor_any_value = setting_master->setting_pointer_map["turbo_factor"]->setting_value;

        if (turbo_factor_any_value == nullptr || !std::holds_alternative<float>(turbo_factor_any_value->data))
        {
            return nullptr;
        }

        universe->turbo_factor = std::get<float>(turbo_factor_any_value->data);
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> SettingMaster::activate_twin_turbo_factor(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        if (setting_master->setting_pointer_map.count("twin_turbo_factor") != 1)
        {
            return nullptr;
        }

        std::shared_ptr<yli::common::AnyValue> twin_turbo_factor_any_value = setting_master->setting_pointer_map["twin_turbo_factor"]->setting_value;

        if (twin_turbo_factor_any_value == nullptr || !std::holds_alternative<float>(twin_turbo_factor_any_value->data))
        {
            return nullptr;
        }

        universe->twin_turbo_factor = std::get<float>(twin_turbo_factor_any_value->data);
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> SettingMaster::activate_mouse_speed(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        if (setting_master->setting_pointer_map.count("mouse_speed") != 1)
        {
            return nullptr;
        }

        std::shared_ptr<yli::common::AnyValue> mouse_speed_any_value = setting_master->setting_pointer_map["mouse_speed"]->setting_value;

        if (mouse_speed_any_value == nullptr || !std::holds_alternative<float>(mouse_speed_any_value->data))
        {
            return nullptr;
        }

        universe->mouse_speed = std::get<float>(mouse_speed_any_value->data);
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> SettingMaster::activate_is_flight_mode_in_use(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Scene* const scene = dynamic_cast<yli::ontology::Scene*>(entity);

        if (scene == nullptr)
        {
            return nullptr;
        }

        if (setting_master->setting_pointer_map.count("is_flight_mode_in_use") != 1)
        {
            return nullptr;
        }

        std::shared_ptr<yli::common::AnyValue> is_flight_mode_in_use_any_value = setting_master->setting_pointer_map["is_flight_mode_in_use"]->setting_value;

        if (is_flight_mode_in_use_any_value == nullptr || !std::holds_alternative<bool>(is_flight_mode_in_use_any_value->data))
        {
            return nullptr;
        }

        scene->set_is_flight_mode_in_use(std::get<bool>(is_flight_mode_in_use_any_value->data));
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> SettingMaster::activate_console_top_y(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        if (setting_master->setting_pointer_map.count("console_top_y") != 1)
        {
            return nullptr;
        }

        std::shared_ptr<yli::common::AnyValue> console_top_y_any_value = setting_master->setting_pointer_map["console_top_y"]->setting_value;

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

    std::shared_ptr<yli::common::AnyValue> SettingMaster::activate_console_bottom_y(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        if (setting_master->setting_pointer_map.count("console_bottom_y") != 1)
        {
            return nullptr;
        }

        std::shared_ptr<yli::common::AnyValue> console_bottom_y_any_value = setting_master->setting_pointer_map["console_bottom_y"]->setting_value;

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

    std::shared_ptr<yli::common::AnyValue> SettingMaster::activate_console_left_x(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        if (setting_master->setting_pointer_map.count("console_left_x") != 1)
        {
            return nullptr;
        }

        std::shared_ptr<yli::common::AnyValue> console_left_x_any_value = setting_master->setting_pointer_map["console_left_x"]->setting_value;

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

    std::shared_ptr<yli::common::AnyValue> SettingMaster::activate_console_right_x(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
    {
        if (entity == nullptr || setting_master == nullptr)
        {
            return nullptr;
        }

        if (setting_master->setting_pointer_map.count("console_right_x") != 1)
        {
            return nullptr;
        }

        std::shared_ptr<yli::common::AnyValue> console_right_x_any_value = setting_master->setting_pointer_map["console_right_x"]->setting_value;

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

    std::shared_ptr<yli::common::AnyValue> SettingMaster::read_should_be_rendered(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        return std::make_shared<yli::common::AnyValue>(entity->should_be_rendered);
    }

    std::shared_ptr<yli::common::AnyValue> SettingMaster::read_cartesian_coordinates(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            return std::make_shared<yli::common::AnyValue>(std::make_shared<glm::vec3>(movable->cartesian_coordinates));
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        return std::make_shared<yli::common::AnyValue>(std::make_shared<glm::vec3>(universe->current_camera_cartesian_coordinates));
    }

    std::shared_ptr<yli::common::AnyValue> SettingMaster::read_x(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            return std::make_shared<yli::common::AnyValue>(movable->cartesian_coordinates.x);
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        return std::make_shared<yli::common::AnyValue>(universe->current_camera_cartesian_coordinates.x);
    }

    std::shared_ptr<yli::common::AnyValue> SettingMaster::read_y(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            return std::make_shared<yli::common::AnyValue>(movable->cartesian_coordinates.y);
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        return std::make_shared<yli::common::AnyValue>(universe->current_camera_cartesian_coordinates.y);
    }

    std::shared_ptr<yli::common::AnyValue> SettingMaster::read_z(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            return std::make_shared<yli::common::AnyValue>(movable->cartesian_coordinates.z);
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        return std::make_shared<yli::common::AnyValue>(universe->current_camera_cartesian_coordinates.z);
    }

    std::shared_ptr<yli::common::AnyValue> SettingMaster::read_rho(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            return std::make_shared<yli::common::AnyValue>(movable->spherical_coordinates.rho);
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        return std::make_shared<yli::common::AnyValue>(universe->current_camera_spherical_coordinates.rho);
    }

    std::shared_ptr<yli::common::AnyValue> SettingMaster::read_theta(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            return std::make_shared<yli::common::AnyValue>(movable->spherical_coordinates.theta);
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        return std::make_shared<yli::common::AnyValue>(universe->current_camera_spherical_coordinates.theta);
    }

    std::shared_ptr<yli::common::AnyValue> SettingMaster::read_phi(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            return std::make_shared<yli::common::AnyValue>(movable->spherical_coordinates.phi);
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        return std::make_shared<yli::common::AnyValue>(universe->current_camera_spherical_coordinates.phi);
    }

    std::shared_ptr<yli::common::AnyValue> SettingMaster::read_up(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
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

        return std::make_shared<yli::common::AnyValue>(&universe->current_camera_up);
    }

    std::shared_ptr<yli::common::AnyValue> SettingMaster::read_right(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
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

        return std::make_shared<yli::common::AnyValue>(&universe->current_camera_right);
    }

    std::shared_ptr<yli::common::AnyValue> SettingMaster::read_horizontal_angle(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            return std::make_shared<yli::common::AnyValue>(movable->horizontal_angle);
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        return std::make_shared<yli::common::AnyValue>(universe->current_camera_horizontal_angle);
    }

    std::shared_ptr<yli::common::AnyValue> SettingMaster::read_vertical_angle(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
    {
        if (entity == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            return std::make_shared<yli::common::AnyValue>(movable->vertical_angle);
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        return std::make_shared<yli::common::AnyValue>(universe->current_camera_vertical_angle);
    }

    std::shared_ptr<yli::common::AnyValue> SettingMaster::read_is_flight_mode_in_use(yli::ontology::Entity* const entity, yli::config::SettingMaster* const setting_master)
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

        return std::make_shared<yli::common::AnyValue>(scene->get_is_flight_mode_in_use());
    }
}
