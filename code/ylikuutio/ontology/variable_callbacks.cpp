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

#include "entity.hpp"
#include "variable.hpp"
#include "movable.hpp"
#include "universe.hpp"
#include "scene.hpp"
#include "console.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/opengl/opengl.hpp"
#include "code/ylikuutio/sdl/ylikuutio_sdl.hpp"

// Include standard headers
#include <stdint.h>      // uint32_t etc.
#include <limits>        // std::numeric_limits
#include <variant>       // std::holds_alternative

namespace yli::ontology
{
    std::optional<yli::data::AnyValue> Variable::activate_window_width(
            Entity& entity,
            Variable& variable)
    {
        // window width.
        const yli::data::AnyValue& window_width_any_value = variable.variable_value;

        if (!std::holds_alternative<uint32_t>(window_width_any_value.data))
        {
            return std::nullopt;
        }

        const uint32_t window_width = std::get<uint32_t>(window_width_any_value.data);

        Universe* const universe = dynamic_cast<Universe*>(&entity);

        if (universe == nullptr)
        {
            return std::nullopt;
        }

        universe->set_window_width(window_width);

        const uint32_t window_height = universe->get_window_height();

        if (window_width <= std::numeric_limits<int>::max() &&
                window_height <= std::numeric_limits<int>::max())
        {
            yli::sdl::set_window_size(universe->get_window(), static_cast<int>(window_width), static_cast<int>(window_height));
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Variable::activate_window_height(
            Entity& entity,
            Variable& variable)
    {
        // window height.
        const yli::data::AnyValue& window_height_any_value = variable.variable_value;

        if (!std::holds_alternative<uint32_t>(window_height_any_value.data))
        {
            return std::nullopt;
        }

        const uint32_t window_height = std::get<uint32_t>(window_height_any_value.data);

        Universe* const universe = dynamic_cast<Universe*>(&entity);

        if (universe == nullptr)
        {
            return std::nullopt;
        }

        universe->set_window_height(window_height);

        const uint32_t window_width = universe->get_window_width();

        if (window_width <= std::numeric_limits<int>::max() &&
                window_height <= std::numeric_limits<int>::max())
        {
            yli::sdl::set_window_size(universe->get_window(), static_cast<int>(window_width), static_cast<int>(window_height));
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Variable::activate_framebuffer_width(
            Entity& entity,
            Variable& variable)
    {
        // framebuffer width.
        const yli::data::AnyValue& framebuffer_width_any_value = variable.variable_value;

        if (!std::holds_alternative<uint32_t>(framebuffer_width_any_value.data))
        {
            return std::nullopt;
        }

        const uint32_t framebuffer_width = std::get<uint32_t>(framebuffer_width_any_value.data);

        Universe* const universe = dynamic_cast<Universe*>(&entity);

        if (universe == nullptr)
        {
            return std::nullopt;
        }

        universe->framebuffer_module.set_texture_width(framebuffer_width);

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Variable::activate_framebuffer_height(
            Entity& entity,
            Variable& variable)
    {
        // framebuffer height.
        const yli::data::AnyValue& framebuffer_height_any_value = variable.variable_value;

        if (!std::holds_alternative<uint32_t>(framebuffer_height_any_value.data))
        {
            return std::nullopt;
        }

        const uint32_t framebuffer_height = std::get<uint32_t>(framebuffer_height_any_value.data);

        Universe* universe = dynamic_cast<Universe*>(&entity);

        if (universe == nullptr)
        {
            return std::nullopt;
        }

        universe->framebuffer_module.set_texture_height(framebuffer_height);

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Variable::activate_background_color(
            Entity& entity,
            Variable& /* variable */)
    {
        if (!entity.has_variable("red") ||
                !entity.has_variable("green") ||
                !entity.has_variable("blue") ||
                !entity.has_variable("alpha"))
        {
            return std::nullopt;
        }

        // red.
        const yli::data::AnyValue& red_any_value = entity.get_variable("red")->variable_value;

        if (!std::holds_alternative<float>(red_any_value.data))
        {
            return std::nullopt;
        }

        const float red = std::get<float>(red_any_value.data);

        // green.
        const yli::data::AnyValue& green_any_value = entity.get_variable("green")->variable_value;

        if (!std::holds_alternative<float>(green_any_value.data))
        {
            return std::nullopt;
        }

        const float green = std::get<float>(green_any_value.data);

        // blue.
        const yli::data::AnyValue& blue_any_value = entity.get_variable("blue")->variable_value;

        if (!std::holds_alternative<float>(blue_any_value.data))
        {
            return std::nullopt;
        }

        const float blue = std::get<float>(blue_any_value.data);

        // alpha.
        const yli::data::AnyValue& alpha_any_value = entity.get_variable("alpha")->variable_value;

        if (!std::holds_alternative<float>(alpha_any_value.data))
        {
            return std::nullopt;
        }

        const float alpha = std::get<float>(alpha_any_value.data);

        yli::opengl::set_background_color(red, green, blue, alpha);

        Universe* const universe = dynamic_cast<Universe*>(&entity);

        if (universe != nullptr)
        {
            universe->background_red = red;
            universe->background_green = green;
            universe->background_blue = blue;
            universe->background_alpha = alpha;
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Variable::activate_wireframe(
            Entity& /* entity */,
            Variable& variable)
    {
        const yli::data::AnyValue& wireframe_any_value = variable.variable_value;

        if (std::holds_alternative<bool>(wireframe_any_value.data))
        {
            yli::opengl::set_wireframe(std::get<bool>(wireframe_any_value.data));
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Variable::activate_speed(
            Entity& entity,
            Variable& variable)
    {
        Movable* const movable = dynamic_cast<Movable*>(&entity);

        if (movable != nullptr)
        {
            const yli::data::AnyValue& speed_any_value = variable.variable_value;

            if (!std::holds_alternative<float>(speed_any_value.data))
            {
                return std::nullopt;
            }

            movable->speed = std::get<float>(speed_any_value.data);
            return std::nullopt;
        }

        Universe* const universe = dynamic_cast<Universe*>(&entity);

        if (universe == nullptr)
        {
            return std::nullopt;
        }

        const yli::data::AnyValue& speed_any_value = variable.variable_value;

        if (std::holds_alternative<float>(speed_any_value.data))
        {
            universe->speed = std::get<float>(speed_any_value.data);
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Variable::activate_turbo_factor(
            Entity& entity,
            Variable& variable)
    {
        Universe* const universe = dynamic_cast<Universe*>(&entity);

        if (universe == nullptr)
        {
            return std::nullopt;
        }

        const yli::data::AnyValue& turbo_factor_any_value = variable.variable_value;

        if (std::holds_alternative<float>(turbo_factor_any_value.data))
        {
            universe->turbo_factor = std::get<float>(turbo_factor_any_value.data);
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Variable::activate_twin_turbo_factor(
            Entity& entity,
            Variable& variable)
    {
        Universe* const universe = dynamic_cast<Universe*>(&entity);

        if (universe == nullptr)
        {
            return std::nullopt;
        }

        const yli::data::AnyValue& twin_turbo_factor_any_value = variable.variable_value;

        if (std::holds_alternative<float>(twin_turbo_factor_any_value.data))
        {
            universe->twin_turbo_factor = std::get<float>(twin_turbo_factor_any_value.data);
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Variable::activate_mouse_speed(
            Entity& entity,
            Variable& variable)
    {
        Universe* const universe = dynamic_cast<Universe*>(&entity);

        if (universe == nullptr)
        {
            return std::nullopt;
        }

        const yli::data::AnyValue& mouse_speed_any_value = variable.variable_value;

        if (std::holds_alternative<float>(mouse_speed_any_value.data))
        {
            universe->mouse_speed = std::get<float>(mouse_speed_any_value.data);
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Variable::activate_is_flight_mode_in_use(
            Entity& entity,
            Variable& variable)
    {
        Scene* const scene = dynamic_cast<Scene*>(&entity);

        if (scene == nullptr)
        {
            return std::nullopt;
        }

        const yli::data::AnyValue& is_flight_mode_in_use_any_value = variable.variable_value;

        if (std::holds_alternative<bool>(is_flight_mode_in_use_any_value.data))
        {
            scene->set_is_flight_mode_in_use(std::get<bool>(is_flight_mode_in_use_any_value.data));
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Variable::activate_console_top_y(
            Entity& entity,
            Variable& variable)
    {
        const yli::data::AnyValue& console_top_y_any_value = variable.variable_value;

        if (!std::holds_alternative<uint32_t>(console_top_y_any_value.data))
        {
            return std::nullopt;
        }

        Universe* const universe = dynamic_cast<Universe*>(&entity);

        if (universe == nullptr)
        {
            return std::nullopt;
        }

        Console* const console = universe->get_active_console();

        if (console != nullptr)
        {
            console->set_console_top_y(std::get<uint32_t>(console_top_y_any_value.data));
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Variable::activate_console_bottom_y(
            Entity& entity,
            Variable& variable)
    {
        const yli::data::AnyValue& console_bottom_y_any_value = variable.variable_value;

        if (!std::holds_alternative<uint32_t>(console_bottom_y_any_value.data))
        {
            return std::nullopt;
        }

        Universe* const universe = dynamic_cast<Universe*>(&entity);

        if (universe == nullptr)
        {
            return std::nullopt;
        }

        Console* const console = universe->get_active_console();

        if (console != nullptr)
        {
            console->set_console_bottom_y(std::get<uint32_t>(console_bottom_y_any_value.data));
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Variable::activate_console_left_x(
            Entity& entity,
            Variable& variable)
    {
        const yli::data::AnyValue& console_left_x_any_value = variable.variable_value;

        if (!std::holds_alternative<uint32_t>(console_left_x_any_value.data))
        {
            return std::nullopt;
        }

        Universe* const universe = dynamic_cast<Universe*>(&entity);

        if (universe == nullptr)
        {
            return std::nullopt;
        }

        Console* const console = universe->get_active_console();

        if (console != nullptr)
        {
            console->set_console_left_x(std::get<uint32_t>(console_left_x_any_value.data));
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Variable::activate_console_right_x(
            Entity& entity,
            Variable& variable)
    {
        const yli::data::AnyValue& console_right_x_any_value = variable.variable_value;

        if (!std::holds_alternative<uint32_t>(console_right_x_any_value.data))
        {
            return std::nullopt;
        }

        Universe* const universe = dynamic_cast<Universe*>(&entity);

        if (universe == nullptr)
        {
            return std::nullopt;
        }

        Console* const console = universe->get_active_console();

        if (console != nullptr)
        {
            console->set_console_right_x(std::get<uint32_t>(console_right_x_any_value.data));
        }

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> Variable::read_is_flight_mode_in_use(Entity& entity)
    {
        Scene* const scene = dynamic_cast<Scene*>(&entity);

        if (scene != nullptr)
        {
            return yli::data::AnyValue(scene->get_is_flight_mode_in_use());
        }

        return std::nullopt;
    }
}
