// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2026 Antti Nuortimo.
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

#include "movable_controller_snippets.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/ontology/movable.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/holobiont.hpp"

// Include standard headers
#include <iostream> // std::cout, std::cerr
#include <numbers>  // std::numbers::pi
#include <optional> // std::optional

namespace yli::ontology
{
    class GenericParentModule;
    class Universe;
    class CallbackEngine;
    class CallbackObject;
}

namespace yli::snippets
{
    std::optional<data::AnyValue> rest(
            ontology::Universe&,
            ontology::CallbackEngine*,
            ontology::CallbackObject*,
            ontology::GenericParentModule&,
            const data::AnyValue& /* any_value */)
    {
        // Do nothing.
        return std::nullopt;
    }

    std::optional<data::AnyValue> go_east(
            ontology::Universe&,
            ontology::CallbackEngine*,
            ontology::CallbackObject*,
            ontology::GenericParentModule&,
            const data::AnyValue& any_value)
    {
        if (any_value.has_movable_ref())
        {
            ontology::Movable& movable = any_value.get_movable_ref();
            movable.location.xyz.x += movable.speed;
            return std::nullopt;
        }

        std::cerr << "ERROR: `yli::snippets::go_east`: `any_value->type` is not of any valid type!\n";
        return std::nullopt;
    }

    std::optional<data::AnyValue> go_west(
            ontology::Universe&,
            ontology::CallbackEngine*,
            ontology::CallbackObject*,
            ontology::GenericParentModule&,
            const data::AnyValue& any_value)
    {
        if (any_value.has_movable_ref())
        {
            ontology::Movable& movable = any_value.get_movable_ref();
            movable.location.xyz.x -= movable.speed;
            return std::nullopt;
        }

        std::cerr << "ERROR: `yli::snippets::go_west`: `any_value->type` is not of any valid type!\n";
        return std::nullopt;
    }

    std::optional<data::AnyValue> go_north(
            ontology::Universe&,
            ontology::CallbackEngine*,
            ontology::CallbackObject*,
            ontology::GenericParentModule&,
            const data::AnyValue& any_value)
    {
        if (any_value.has_movable_ref())
        {
            ontology::Movable& movable = any_value.get_movable_ref();
            movable.location.xyz.y += movable.speed;
            return std::nullopt;
        }

        std::cerr << "ERROR: `yli::snippets::go_north`: `any_value->type` is not of any valid type!\n";
        return std::nullopt;
    }

    std::optional<data::AnyValue> go_south(
            ontology::Universe&,
            ontology::CallbackEngine*,
            ontology::CallbackObject*,
            ontology::GenericParentModule&,
            const data::AnyValue& any_value)
    {
        if (any_value.has_movable_ref())
        {
            ontology::Movable& movable = any_value.get_movable_ref();
            movable.location.xyz.y -= movable.speed;
            return std::nullopt;
        }

        std::cerr << "ERROR: `yli::snippets::go_south`: `any_value->type` is not of any valid type!\n";
        return std::nullopt;
    }

    std::optional<data::AnyValue> orient_to_east(
            ontology::Universe&,
            ontology::CallbackEngine*,
            ontology::CallbackObject*,
            ontology::GenericParentModule&,
            const data::AnyValue& any_value)
    {
        if (any_value.has_movable_ref())
        {
            ontology::Movable& movable = any_value.get_movable_ref();
            movable.orientation.yaw = 0.0f;
            return std::nullopt;
        }

        std::cerr << "ERROR: `yli::snippets::orient_to_east`: `any_value->type` is not of any valid type!\n";
        return std::nullopt;
    }

    std::optional<data::AnyValue> orient_to_west(
            ontology::Universe&,
            ontology::CallbackEngine*,
            ontology::CallbackObject*,
            ontology::GenericParentModule&,
            const data::AnyValue& any_value)
    {
        if (any_value.has_movable_ref())
        {
            ontology::Movable& movable = any_value.get_movable_ref();
            movable.orientation.yaw = static_cast<float>(std::numbers::pi);
            return std::nullopt;
        }

        std::cerr << "ERROR: `yli::snippets::orient_to_west`: `any_value->type` is not of any valid type!\n";
        return std::nullopt;
    }

    std::optional<data::AnyValue> orient_to_north(
            ontology::Universe&,
            ontology::CallbackEngine*,
            ontology::CallbackObject*,
            ontology::GenericParentModule&,
            const data::AnyValue& any_value)
    {
        if (any_value.has_movable_ref())
        {
            ontology::Movable& movable = any_value.get_movable_ref();
            movable.orientation.yaw = 0.5f * static_cast<float>(std::numbers::pi);
            return std::nullopt;
        }

        std::cerr << "ERROR: `yli::snippets::orient_to_north`: `any_value->type` is not of any valid type!\n";
        return std::nullopt;
    }

    std::optional<data::AnyValue> orient_to_south(
            ontology::Universe&,
            ontology::CallbackEngine*,
            ontology::CallbackObject*,
            ontology::GenericParentModule&,
            const data::AnyValue& any_value)
    {
        if (any_value.has_movable_ref())
        {
            ontology::Movable& movable = any_value.get_movable_ref();
            movable.orientation.yaw = -0.5f * static_cast<float>(std::numbers::pi);
            return std::nullopt;
        }

        std::cerr << "ERROR: `yli::snippets::orient_to_south`: `any_value->type` is not of any valid type!\n";
        return std::nullopt;
    }

    std::optional<data::AnyValue> orient_and_go_east(
            ontology::Universe& universe,
            ontology::CallbackEngine* callback_engine,
            ontology::CallbackObject* callback_object,
            ontology::GenericParentModule& callback_parameters,
            const data::AnyValue& any_value)
    {
        if (any_value.has_movable_ref())
        {
            orient_to_east(universe, callback_engine, callback_object, callback_parameters, any_value);
            go_east(universe, callback_engine, callback_object, callback_parameters, any_value);
            return std::nullopt;
        }

        std::cerr << "ERROR: `yli::snippets::orient_and_go_east`: `any_value->type` is not of any valid type!\n";
        return std::nullopt;
    }

    std::optional<data::AnyValue> orient_and_go_west(
            ontology::Universe& universe,
            ontology::CallbackEngine* callback_engine,
            ontology::CallbackObject* callback_object,
            ontology::GenericParentModule& callback_parameters,
            const data::AnyValue& any_value)
    {
        if (any_value.has_movable_ref())
        {
            orient_to_west(universe, callback_engine, callback_object, callback_parameters, any_value);
            go_west(universe, callback_engine, callback_object, callback_parameters, any_value);
            return std::nullopt;
        }

        std::cerr << "ERROR: `yli::snippets::orient_and_go_west`: `any_value->type` is not of any valid type!\n";
        return std::nullopt;
    }

    std::optional<data::AnyValue> orient_and_go_north(
            ontology::Universe& universe,
            ontology::CallbackEngine* callback_engine,
            ontology::CallbackObject* callback_object,
            ontology::GenericParentModule& callback_parameters,
            const data::AnyValue& any_value)
    {
        if (any_value.has_movable_ref())
        {
            orient_to_north(universe, callback_engine, callback_object, callback_parameters, any_value);
            go_north(universe, callback_engine, callback_object, callback_parameters, any_value);
            return std::nullopt;
        }

        std::cerr << "ERROR: `yli::snippets::orient_and_go_north`: `any_value->type` is not of any valid type!\n";
        return std::nullopt;
    }

    std::optional<data::AnyValue> orient_and_go_south(
            ontology::Universe& universe,
            ontology::CallbackEngine* callback_engine,
            ontology::CallbackObject* callback_object,
            ontology::GenericParentModule& callback_parameters,
            const data::AnyValue& any_value)
    {
        if (any_value.has_movable_ref())
        {
            orient_to_south(universe, callback_engine, callback_object, callback_parameters, any_value);
            go_south(universe, callback_engine, callback_object, callback_parameters, any_value);
            return std::nullopt;
        }

        std::cerr << "ERROR: `yli::snippets::orient_and_go_south`: `any_value->type` is not of any valid type!\n";
        return std::nullopt;
    }

    std::optional<data::AnyValue> rotate_clockwise(
            ontology::Universe&,
            ontology::CallbackEngine*,
            ontology::CallbackObject*,
            ontology::GenericParentModule&,
            const data::AnyValue& any_value)
    {
        if (any_value.has_movable_ref())
        {
            ontology::Movable& movable = any_value.get_movable_ref();
            movable.orientation.yaw -= 0.1f * static_cast<float>(std::numbers::pi);
            return std::nullopt;
        }

        std::cerr << "ERROR: `yli::snippets::rotate_clockwise`: `any_value->type` is not of any valid type!\n";
        return std::nullopt;
    }

    std::optional<data::AnyValue> rotate_counterclockwise(
            ontology::Universe&,
            ontology::CallbackEngine*,
            ontology::CallbackObject*,
            ontology::GenericParentModule&,
            const data::AnyValue& any_value)
    {
        if (any_value.has_movable_ref())
        {
            ontology::Movable& movable = any_value.get_movable_ref();
            movable.orientation.yaw += 0.1f * static_cast<float>(std::numbers::pi);
            return std::nullopt;
        }

        std::cerr << "ERROR: `yli::snippets::rotate_counterclockwise`: `any_value->type` is not of any valid type!\n";
        return std::nullopt;
    }
}
