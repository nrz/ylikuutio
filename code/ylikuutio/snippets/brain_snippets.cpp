// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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

#include "brain_snippets.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/data/pi.hpp"
#include "code/ylikuutio/ontology/movable.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/holobiont.hpp"

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <optional> // std::optional
#include <vector>   // std::vector

namespace yli::callback
{
    class CallbackEngine;
    class CallbackObject;
    class CallbackParameter;
}

namespace yli::ontology
{
    class Universe;
}

namespace yli::snippets
{
    std::optional<yli::data::AnyValue> rest(
            yli::ontology::Universe&,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            const yli::data::AnyValue& /* any_value */)
    {
        // Do nothing.
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> go_east(
            yli::ontology::Universe&,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            const yli::data::AnyValue& any_value)
    {
        if (any_value.has_movable_ref())
        {
            yli::ontology::Movable& movable = any_value.get_movable_ref();
            movable.location.xyz.x += movable.speed;
            return std::nullopt;
        }

        std::cerr << "ERROR: `yli::snippets::go_east`: `any_value->type` is not of any valid type!\n";
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> go_west(
            yli::ontology::Universe&,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            const yli::data::AnyValue& any_value)
    {
        if (any_value.has_movable_ref())
        {
            yli::ontology::Movable& movable = any_value.get_movable_ref();
            movable.location.xyz.x -= movable.speed;
            return std::nullopt;
        }

        std::cerr << "ERROR: `yli::snippets::go_west`: `any_value->type` is not of any valid type!\n";
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> go_north(
            yli::ontology::Universe&,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            const yli::data::AnyValue& any_value)
    {
        if (any_value.has_movable_ref())
        {
            yli::ontology::Movable& movable = any_value.get_movable_ref();
            movable.location.xyz.z -= movable.speed;
            return std::nullopt;
        }

        std::cerr << "ERROR: `yli::snippets::go_north`: `any_value->type` is not of any valid type!\n";
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> go_south(
            yli::ontology::Universe&,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            const yli::data::AnyValue& any_value)
    {
        if (any_value.has_movable_ref())
        {
            yli::ontology::Movable& movable = any_value.get_movable_ref();
            movable.location.xyz.z += movable.speed;
            return std::nullopt;
        }

        std::cerr << "ERROR: `yli::snippets::go_south`: `any_value->type` is not of any valid type!\n";
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> orient_to_east(
            yli::ontology::Universe&,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            const yli::data::AnyValue& any_value)
    {
        if (any_value.has_movable_ref())
        {
            yli::ontology::Movable& movable = any_value.get_movable_ref();
            movable.orientation.yaw = 0.0f;
            return std::nullopt;
        }

        std::cerr << "ERROR: `yli::snippets::orient_to_east`: `any_value->type` is not of any valid type!\n";
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> orient_to_west(
            yli::ontology::Universe&,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            const yli::data::AnyValue& any_value)
    {
        if (any_value.has_movable_ref())
        {
            yli::ontology::Movable& movable = any_value.get_movable_ref();
            movable.orientation.yaw = pi;
            return std::nullopt;
        }

        std::cerr << "ERROR: `yli::snippets::orient_to_west`: `any_value->type` is not of any valid type!\n";
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> orient_to_north(
            yli::ontology::Universe&,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            const yli::data::AnyValue& any_value)
    {
        if (any_value.has_movable_ref())
        {
            yli::ontology::Movable& movable = any_value.get_movable_ref();
            movable.orientation.yaw = 0.5f * pi;
            return std::nullopt;
        }

        std::cerr << "ERROR: `yli::snippets::orient_to_north`: `any_value->type` is not of any valid type!\n";
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> orient_to_south(
            yli::ontology::Universe&,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            const yli::data::AnyValue& any_value)
    {
        if (any_value.has_movable_ref())
        {
            yli::ontology::Movable& movable = any_value.get_movable_ref();
            movable.orientation.yaw = -0.5f * pi;
            return std::nullopt;
        }

        std::cerr << "ERROR: `yli::snippets::orient_to_south`: `any_value->type` is not of any valid type!\n";
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> orient_and_go_east(
            yli::ontology::Universe& universe,
            yli::callback::CallbackEngine* callback_engine,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>& callback_parameters,
            const yli::data::AnyValue& any_value)
    {
        if (any_value.has_movable_ref())
        {
            yli::snippets::orient_to_east(universe, callback_engine, callback_object, callback_parameters, any_value);
            yli::snippets::go_east(universe, callback_engine, callback_object, callback_parameters, any_value);
            return std::nullopt;
        }

        std::cerr << "ERROR: `yli::snippets::orient_and_go_east`: `any_value->type` is not of any valid type!\n";
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> orient_and_go_west(
            yli::ontology::Universe& universe,
            yli::callback::CallbackEngine* callback_engine,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>& callback_parameters,
            const yli::data::AnyValue& any_value)
    {
        if (any_value.has_movable_ref())
        {
            yli::snippets::orient_to_west(universe, callback_engine, callback_object, callback_parameters, any_value);
            yli::snippets::go_west(universe, callback_engine, callback_object, callback_parameters, any_value);
            return std::nullopt;
        }

        std::cerr << "ERROR: `yli::snippets::orient_and_go_west`: `any_value->type` is not of any valid type!\n";
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> orient_and_go_north(
            yli::ontology::Universe& universe,
            yli::callback::CallbackEngine* callback_engine,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>& callback_parameters,
            const yli::data::AnyValue& any_value)
    {
        if (any_value.has_movable_ref())
        {
            yli::snippets::orient_to_north(universe, callback_engine, callback_object, callback_parameters, any_value);
            yli::snippets::go_north(universe, callback_engine, callback_object, callback_parameters, any_value);
            return std::nullopt;
        }

        std::cerr << "ERROR: `yli::snippets::orient_and_go_north`: `any_value->type` is not of any valid type!\n";
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> orient_and_go_south(
            yli::ontology::Universe& universe,
            yli::callback::CallbackEngine* callback_engine,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>& callback_parameters,
            const yli::data::AnyValue& any_value)
    {
        if (any_value.has_movable_ref())
        {
            yli::snippets::orient_to_south(universe, callback_engine, callback_object, callback_parameters, any_value);
            yli::snippets::go_south(universe, callback_engine, callback_object, callback_parameters, any_value);
            return std::nullopt;
        }

        std::cerr << "ERROR: `yli::snippets::orient_and_go_south`: `any_value->type` is not of any valid type!\n";
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> rotate_clockwise(
            yli::ontology::Universe&,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            const yli::data::AnyValue& any_value)
    {
        if (any_value.has_movable_ref())
        {
            yli::ontology::Movable& movable = any_value.get_movable_ref();
            movable.orientation.yaw -= 0.1f * pi;
            return std::nullopt;
        }

        std::cerr << "ERROR: `yli::snippets::rotate_clockwise`: `any_value->type` is not of any valid type!\n";
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> rotate_counterclockwise(
            yli::ontology::Universe&,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            const yli::data::AnyValue& any_value)
    {
        if (any_value.has_movable_ref())
        {
            yli::ontology::Movable& movable = any_value.get_movable_ref();
            movable.orientation.yaw += 0.1f * pi;
            return std::nullopt;
        }

        std::cerr << "ERROR: `yli::snippets::rotate_counterclockwise`: `any_value->type` is not of any valid type!\n";
        return std::nullopt;
    }
}
