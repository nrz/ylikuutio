// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
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

#include "mesh_module.hpp"
#include "entity.hpp"
#include "variable.hpp"
#include "movable.hpp"
#include "universe.hpp"
#include "scene.hpp"
#include "species.hpp"
#include "holobiont.hpp"
#include "console.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"
#include "code/ylikuutio/sdl/ylikuutio_sdl.hpp"

// Include standard headers
#include <stdint.h>      // uint32_t etc.
#include <limits>        // std::numeric_limits
#include <memory>        // std::make_shared, std::shared_ptr
#include <variant>       // std::holds_alternative, std::variant

namespace yli::data
{
    struct SphericalCoordinatesStruct;
}

namespace yli::ontology
{
    std::shared_ptr<yli::data::AnyValue> Variable::activate_planet_radius(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable)
    {
        if (entity == nullptr || variable == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Species* const species = dynamic_cast<yli::ontology::Species*>(entity);

        if (species == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> planet_radius_any_value = variable->variable_value;

        if (planet_radius_any_value == nullptr || !std::holds_alternative<float>(planet_radius_any_value->data))
        {
            return nullptr;
        }

        species->mesh.planet_radius = std::get<float>(planet_radius_any_value->data);

        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Variable::activate_window_width(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable)
    {
        if (entity == nullptr || variable == nullptr)
        {
            return nullptr;
        }

        // window width.
        std::shared_ptr<yli::data::AnyValue> window_width_any_value = variable->variable_value;

        if (window_width_any_value == nullptr || !std::holds_alternative<uint32_t>(window_width_any_value->data))
        {
            return nullptr;
        }

        const uint32_t window_width = std::get<uint32_t>(window_width_any_value->data);

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        universe->set_window_width(window_width);

        const uint32_t window_height = universe->get_window_height();

        if (window_width <= std::numeric_limits<int>::max() &&
                window_height <= std::numeric_limits<int>::max())
        {
            yli::sdl::set_window_size(universe->get_window(), static_cast<int>(window_width), static_cast<int>(window_height));
        }

        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Variable::activate_window_height(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable)
    {
        if (entity == nullptr || variable == nullptr)
        {
            return nullptr;
        }

        // window height.
        std::shared_ptr<yli::data::AnyValue> window_height_any_value = variable->variable_value;

        if (window_height_any_value == nullptr || !std::holds_alternative<uint32_t>(window_height_any_value->data))
        {
            return nullptr;
        }

        const uint32_t window_height = std::get<uint32_t>(window_height_any_value->data);

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        universe->set_window_height(window_height);

        const uint32_t window_width = universe->get_window_width();

        if (window_width <= std::numeric_limits<int>::max() &&
                window_height <= std::numeric_limits<int>::max())
        {
            yli::sdl::set_window_size(universe->get_window(), static_cast<int>(window_width), static_cast<int>(window_height));
        }

        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Variable::activate_framebuffer_width(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable)
    {
        if (entity == nullptr || variable == nullptr)
        {
            return nullptr;
        }

        // framebuffer width.
        std::shared_ptr<yli::data::AnyValue> framebuffer_width_any_value = variable->variable_value;

        if (framebuffer_width_any_value == nullptr || !std::holds_alternative<uint32_t>(framebuffer_width_any_value->data))
        {
            return nullptr;
        }

        const uint32_t framebuffer_width = std::get<uint32_t>(framebuffer_width_any_value->data);

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        universe->framebuffer_module.set_texture_width(framebuffer_width);

        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Variable::activate_framebuffer_height(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable)
    {
        if (entity == nullptr || variable == nullptr)
        {
            return nullptr;
        }

        // framebuffer height.
        std::shared_ptr<yli::data::AnyValue> framebuffer_height_any_value = variable->variable_value;

        if (framebuffer_height_any_value == nullptr || !std::holds_alternative<uint32_t>(framebuffer_height_any_value->data))
        {
            return nullptr;
        }

        const uint32_t framebuffer_height = std::get<uint32_t>(framebuffer_height_any_value->data);

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        universe->framebuffer_module.set_texture_height(framebuffer_height);

        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Variable::activate_background_color(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable)
    {
        if (entity == nullptr || variable == nullptr)
        {
            return nullptr;
        }

        if (!entity->has_variable("red") ||
                !entity->has_variable("green") ||
                !entity->has_variable("blue") ||
                !entity->has_variable("alpha"))
        {
            return nullptr;
        }

        // red.
        std::shared_ptr<yli::data::AnyValue> red_any_value = entity->get("red")->variable_value;

        if (red_any_value == nullptr || !std::holds_alternative<float>(red_any_value->data))
        {
            return nullptr;
        }

        const float red = std::get<float>(red_any_value->data);

        // green.
        std::shared_ptr<yli::data::AnyValue> green_any_value = entity->get("green")->variable_value;

        if (green_any_value == nullptr || !std::holds_alternative<float>(green_any_value->data))
        {
            return nullptr;
        }

        const float green = std::get<float>(green_any_value->data);

        // blue.
        std::shared_ptr<yli::data::AnyValue> blue_any_value = entity->get("blue")->variable_value;

        if (blue_any_value == nullptr || !std::holds_alternative<float>(blue_any_value->data))
        {
            return nullptr;
        }

        const float blue = std::get<float>(blue_any_value->data);

        // alpha.
        std::shared_ptr<yli::data::AnyValue> alpha_any_value = entity->get("alpha")->variable_value;

        if (alpha_any_value == nullptr || !std::holds_alternative<float>(alpha_any_value->data))
        {
            return nullptr;
        }

        const float alpha = std::get<float>(alpha_any_value->data);

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

    std::shared_ptr<yli::data::AnyValue> Variable::activate_wireframe(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable)
    {
        if (entity == nullptr || variable == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> wireframe_any_value = variable->variable_value;

        if (wireframe_any_value == nullptr || !std::holds_alternative<bool>(wireframe_any_value->data))
        {
            return nullptr;
        }

        yli::opengl::set_wireframe(std::get<bool>(wireframe_any_value->data));
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Variable::activate_speed(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable)
    {
        if (entity == nullptr || variable == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Movable* const movable = dynamic_cast<yli::ontology::Movable*>(entity);

        if (movable != nullptr)
        {
            std::shared_ptr<yli::data::AnyValue> speed_any_value = variable->variable_value;

            if (speed_any_value == nullptr || !std::holds_alternative<float>(speed_any_value->data))
            {
                return nullptr;
            }

            movable->speed = std::get<float>(speed_any_value->data);
            return nullptr;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> speed_any_value = variable->variable_value;

        if (speed_any_value == nullptr || !std::holds_alternative<float>(speed_any_value->data))
        {
            return nullptr;
        }

        universe->speed = std::get<float>(speed_any_value->data);
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Variable::activate_turbo_factor(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable)
    {
        if (entity == nullptr || variable == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> turbo_factor_any_value = variable->variable_value;

        if (turbo_factor_any_value == nullptr || !std::holds_alternative<float>(turbo_factor_any_value->data))
        {
            return nullptr;
        }

        universe->turbo_factor = std::get<float>(turbo_factor_any_value->data);
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Variable::activate_twin_turbo_factor(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable)
    {
        if (entity == nullptr || variable == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> twin_turbo_factor_any_value = variable->variable_value;

        if (twin_turbo_factor_any_value == nullptr || !std::holds_alternative<float>(twin_turbo_factor_any_value->data))
        {
            return nullptr;
        }

        universe->twin_turbo_factor = std::get<float>(twin_turbo_factor_any_value->data);
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Variable::activate_mouse_speed(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable)
    {
        if (entity == nullptr || variable == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Universe* const universe = dynamic_cast<yli::ontology::Universe*>(entity);

        if (universe == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> mouse_speed_any_value = variable->variable_value;

        if (mouse_speed_any_value == nullptr || !std::holds_alternative<float>(mouse_speed_any_value->data))
        {
            return nullptr;
        }

        universe->mouse_speed = std::get<float>(mouse_speed_any_value->data);
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Variable::activate_is_flight_mode_in_use(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable)
    {
        if (entity == nullptr || variable == nullptr)
        {
            return nullptr;
        }

        yli::ontology::Scene* const scene = dynamic_cast<yli::ontology::Scene*>(entity);

        if (scene == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> is_flight_mode_in_use_any_value = variable->variable_value;

        if (is_flight_mode_in_use_any_value == nullptr || !std::holds_alternative<bool>(is_flight_mode_in_use_any_value->data))
        {
            return nullptr;
        }

        scene->set_is_flight_mode_in_use(std::get<bool>(is_flight_mode_in_use_any_value->data));
        return nullptr;
    }

    std::shared_ptr<yli::data::AnyValue> Variable::activate_console_top_y(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable)
    {
        if (entity == nullptr || variable == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> console_top_y_any_value = variable->variable_value;

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

    std::shared_ptr<yli::data::AnyValue> Variable::activate_console_bottom_y(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable)
    {
        if (entity == nullptr || variable == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> console_bottom_y_any_value = variable->variable_value;

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

    std::shared_ptr<yli::data::AnyValue> Variable::activate_console_left_x(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable)
    {
        if (entity == nullptr || variable == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> console_left_x_any_value = variable->variable_value;

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

    std::shared_ptr<yli::data::AnyValue> Variable::activate_console_right_x(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable)
    {
        if (entity == nullptr || variable == nullptr)
        {
            return nullptr;
        }

        std::shared_ptr<yli::data::AnyValue> console_right_x_any_value = variable->variable_value;

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

    std::shared_ptr<yli::data::AnyValue> Variable::read_is_flight_mode_in_use(yli::ontology::Entity* const entity)
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
