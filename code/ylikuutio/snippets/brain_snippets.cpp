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

#include "brain_snippets.hpp"
#include "code/ylikuutio/common/datatype.hpp"
#include "code/ylikuutio/common/any_value.hpp"
#include "code/ylikuutio/config/setting_master.hpp"
#include "code/ylikuutio/ontology/movable.hpp"

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr
#include <memory>   // std::make_shared, std::shared_ptr
#include <variant>  // std::variant
#include <vector>   // std::vector

namespace yli
{
    namespace callback
    {
        class CallbackEngine;
        class CallbackObject;
        class CallbackParameter;
    }

    namespace common
    {
        class AnyValue;
    }

    namespace ontology
    {
        class Universe;
    }
}

namespace yli::snippets
{
    std::shared_ptr<yli::common::AnyValue> rest(
            yli::ontology::Universe*,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>& input_parameters,
            std::shared_ptr<yli::common::AnyValue> any_value)
    {
        // Do nothing.
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> go_east(
            yli::ontology::Universe*,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>& input_parameters,
            std::shared_ptr<yli::common::AnyValue> any_value)
    {
        if (any_value->type != yli::common::Datatype::MOVABLE_POINTER)
        {
            std::cerr << "ERROR: `yli::snippets::go_east`: `any_value->type` is not `yli::common::Datatype::MOVABLE_POINTER`.\n";
            return nullptr;
        }

        yli::ontology::Movable* const movable = std::get<yli::ontology::Movable*>(any_value->data);

        if (movable == nullptr)
        {
            return nullptr;
        }

        movable->cartesian_coordinates.x += 1.0f;
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> go_west(
            yli::ontology::Universe*,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>& input_parameters,
            std::shared_ptr<yli::common::AnyValue> any_value)
    {
        if (any_value->type != yli::common::Datatype::MOVABLE_POINTER)
        {
            std::cerr << "ERROR: `yli::snippets::go_west`: `any_value->type` is not `yli::common::Datatype::MOVABLE_POINTER`.\n";
            return nullptr;
        }

        yli::ontology::Movable* const movable = std::get<yli::ontology::Movable*>(any_value->data);

        if (movable == nullptr)
        {
            return nullptr;
        }

        movable->cartesian_coordinates.x -= 1.0f;
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> go_north(
            yli::ontology::Universe*,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>& input_parameters,
            std::shared_ptr<yli::common::AnyValue> any_value)
    {
        if (any_value->type != yli::common::Datatype::MOVABLE_POINTER)
        {
            std::cerr << "ERROR: `yli::snippets::go_north`: `any_value->type` is not `yli::common::Datatype::MOVABLE_POINTER`.\n";
            return nullptr;
        }

        yli::ontology::Movable* const movable = std::get<yli::ontology::Movable*>(any_value->data);

        if (movable == nullptr)
        {
            return nullptr;
        }

        movable->cartesian_coordinates.z -= 1.0f;
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> go_south(
            yli::ontology::Universe*,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>& input_parameters,
            std::shared_ptr<yli::common::AnyValue> any_value)
    {
        if (any_value->type != yli::common::Datatype::MOVABLE_POINTER)
        {
            std::cerr << "ERROR: `yli::snippets::go_south`: `any_value->type` is not `yli::common::Datatype::MOVABLE_POINTER`.\n";
            return nullptr;
        }

        yli::ontology::Movable* const movable = std::get<yli::ontology::Movable*>(any_value->data);

        if (movable == nullptr)
        {
            return nullptr;
        }

        movable->cartesian_coordinates.z += 1.0f;
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> orient_to_east(
            yli::ontology::Universe*,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>& input_parameters,
            std::shared_ptr<yli::common::AnyValue> any_value)
    {
        if (any_value->type != yli::common::Datatype::MOVABLE_POINTER)
        {
            std::cerr << "ERROR: `yli::snippets::orient_to_east`: `any_value->type` is not `yli::common::Datatype::MOVABLE_POINTER`.\n";
            return nullptr;
        }

        yli::ontology::Movable* const movable = std::get<yli::ontology::Movable*>(any_value->data);

        if (movable == nullptr)
        {
            return nullptr;
        }

        movable->horizontal_angle = 1.5f * PI;
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> orient_to_west(
            yli::ontology::Universe*,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>& input_parameters,
            std::shared_ptr<yli::common::AnyValue> any_value)
    {
        if (any_value->type != yli::common::Datatype::MOVABLE_POINTER)
        {
            std::cerr << "ERROR: `yli::snippets::orient_to_west`: `any_value->type` is not `yli::common::Datatype::MOVABLE_POINTER`.\n";
            return nullptr;
        }

        yli::ontology::Movable* const movable = std::get<yli::ontology::Movable*>(any_value->data);

        if (movable == nullptr)
        {
            return nullptr;
        }

        movable->horizontal_angle = 0.5f * PI;
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> orient_to_north(
            yli::ontology::Universe*,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>& input_parameters,
            std::shared_ptr<yli::common::AnyValue> any_value)
    {
        if (any_value->type != yli::common::Datatype::MOVABLE_POINTER)
        {
            std::cerr << "ERROR: `yli::snippets::orient_to_north`: `any_value->type` is not `yli::common::Datatype::MOVABLE_POINTER`.\n";
            return nullptr;
        }

        yli::ontology::Movable* const movable = std::get<yli::ontology::Movable*>(any_value->data);

        if (movable == nullptr)
        {
            return nullptr;
        }

        movable->horizontal_angle = 0.0f;
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> orient_to_south(
            yli::ontology::Universe*,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>& input_parameters,
            std::shared_ptr<yli::common::AnyValue> any_value)
    {
        if (any_value->type != yli::common::Datatype::MOVABLE_POINTER)
        {
            std::cerr << "ERROR: `yli::snippets::orient_to_south`: `any_value->type` is not `yli::common::Datatype::MOVABLE_POINTER`.\n";
            return nullptr;
        }

        yli::ontology::Movable* const movable = std::get<yli::ontology::Movable*>(any_value->data);

        if (movable == nullptr)
        {
            return nullptr;
        }

        movable->horizontal_angle = 1.0f * PI;
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> orient_and_go_east(
            yli::ontology::Universe*,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>& input_parameters,
            std::shared_ptr<yli::common::AnyValue> any_value)
    {
        if (any_value->type != yli::common::Datatype::MOVABLE_POINTER)
        {
            std::cerr << "ERROR: `yli::snippets::orient_and_go_east`: `any_value->type` is not `yli::common::Datatype::MOVABLE_POINTER`.\n";
            return nullptr;
        }

        yli::ontology::Movable* const movable = std::get<yli::ontology::Movable*>(any_value->data);

        if (movable == nullptr)
        {
            return nullptr;
        }

        movable->horizontal_angle = 1.5f * PI;
        movable->cartesian_coordinates.x += 1.0f;
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> orient_and_go_west(
            yli::ontology::Universe*,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>& input_parameters,
            std::shared_ptr<yli::common::AnyValue> any_value)
    {
        if (any_value->type != yli::common::Datatype::MOVABLE_POINTER)
        {
            std::cerr << "ERROR: `yli::snippets::orient_and_go_west`: `any_value->type` is not `yli::common::Datatype::MOVABLE_POINTER`.\n";
            return nullptr;
        }

        yli::ontology::Movable* const movable = std::get<yli::ontology::Movable*>(any_value->data);

        if (movable == nullptr)
        {
            return nullptr;
        }

        movable->horizontal_angle = 0.5f * PI;
        movable->cartesian_coordinates.x -= 1.0f;
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> orient_and_go_north(
            yli::ontology::Universe*,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>& input_parameters,
            std::shared_ptr<yli::common::AnyValue> any_value)
    {
        if (any_value->type != yli::common::Datatype::MOVABLE_POINTER)
        {
            std::cerr << "ERROR: `yli::snippets::orient_and_go_north`: `any_value->type` is not `yli::common::Datatype::MOVABLE_POINTER`.\n";
            return nullptr;
        }

        yli::ontology::Movable* const movable = std::get<yli::ontology::Movable*>(any_value->data);

        if (movable == nullptr)
        {
            return nullptr;
        }

        movable->horizontal_angle = 0.0f;
        movable->cartesian_coordinates.z -= 1.0f;
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> orient_and_go_south(
            yli::ontology::Universe*,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>& input_parameters,
            std::shared_ptr<yli::common::AnyValue> any_value)
    {
        if (any_value->type != yli::common::Datatype::MOVABLE_POINTER)
        {
            std::cerr << "ERROR: `yli::snippets::orient_and_go_south`: `any_value->type` is not `yli::common::Datatype::MOVABLE_POINTER`.\n";
            return nullptr;
        }

        yli::ontology::Movable* const movable = std::get<yli::ontology::Movable*>(any_value->data);

        if (movable == nullptr)
        {
            return nullptr;
        }

        movable->horizontal_angle = 1.0f * PI;
        movable->cartesian_coordinates.z += 1.0f;
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> rotate_clockwise(
            yli::ontology::Universe*,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>& input_parameters,
            std::shared_ptr<yli::common::AnyValue> any_value)
    {
        if (any_value->type != yli::common::Datatype::MOVABLE_POINTER)
        {
            std::cerr << "ERROR: `yli::snippets::rotate_clockwise`: `any_value->type` is not `yli::common::Datatype::MOVABLE_POINTER`.\n";
            return nullptr;
        }

        yli::ontology::Movable* const movable = std::get<yli::ontology::Movable*>(any_value->data);

        if (movable == nullptr)
        {
            return nullptr;
        }

        movable->horizontal_angle -= 0.1f * PI;
        return nullptr;
    }

    std::shared_ptr<yli::common::AnyValue> rotate_counterclockwise(
            yli::ontology::Universe*,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>& input_parameters,
            std::shared_ptr<yli::common::AnyValue> any_value)
    {
        if (any_value->type != yli::common::Datatype::MOVABLE_POINTER)
        {
            std::cerr << "ERROR: `yli::snippets::rotate_counterclockwise`: `any_value->type` is not `yli::common::Datatype::MOVABLE_POINTER`.\n";
            return nullptr;
        }

        yli::ontology::Movable* const movable = std::get<yli::ontology::Movable*>(any_value->data);

        if (movable == nullptr)
        {
            return nullptr;
        }

        movable->horizontal_angle += 0.1f * PI;
        return nullptr;
    }
}
