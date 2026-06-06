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

#ifndef YLIKUUTIO_SNIPPETS_MOVABLE_CONTROLLER_SNIPPETS_HPP_INCLUDED
#define YLIKUUTIO_SNIPPETS_MOVABLE_CONTROLLER_SNIPPETS_HPP_INCLUDED

#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
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
            const data::AnyValue&);

    std::optional<data::AnyValue> go_east(
            ontology::Universe&,
            ontology::CallbackEngine*,
            ontology::CallbackObject*,
            ontology::GenericParentModule&,
            const data::AnyValue&);

    std::optional<data::AnyValue> go_west(
            ontology::Universe&,
            ontology::CallbackEngine*,
            ontology::CallbackObject*,
            ontology::GenericParentModule&,
            const data::AnyValue&);

    std::optional<data::AnyValue> go_north(
            ontology::Universe&,
            ontology::CallbackEngine*,
            ontology::CallbackObject*,
            ontology::GenericParentModule&,
            const data::AnyValue&);

    std::optional<data::AnyValue> go_south(
            ontology::Universe&,
            ontology::CallbackEngine*,
            ontology::CallbackObject*,
            ontology::GenericParentModule&,
            const data::AnyValue&);

    std::optional<data::AnyValue> orient_to_east(
            ontology::Universe&,
            ontology::CallbackEngine*,
            ontology::CallbackObject*,
            ontology::GenericParentModule&,
            const data::AnyValue&);

    std::optional<data::AnyValue> orient_to_west(
            ontology::Universe&,
            ontology::CallbackEngine*,
            ontology::CallbackObject*,
            ontology::GenericParentModule&,
            const data::AnyValue&);

    std::optional<data::AnyValue> orient_to_north(
            ontology::Universe&,
            ontology::CallbackEngine*,
            ontology::CallbackObject*,
            ontology::GenericParentModule&,
            const data::AnyValue&);

    std::optional<data::AnyValue> orient_to_south(
            ontology::Universe&,
            ontology::CallbackEngine*,
            ontology::CallbackObject*,
            ontology::GenericParentModule&,
            const data::AnyValue&);

    std::optional<data::AnyValue> orient_and_go_east(
            ontology::Universe&,
            ontology::CallbackEngine*,
            ontology::CallbackObject*,
            ontology::GenericParentModule&,
            const data::AnyValue&);

    std::optional<data::AnyValue> orient_and_go_west(
            ontology::Universe&,
            ontology::CallbackEngine*,
            ontology::CallbackObject*,
            ontology::GenericParentModule&,
            const data::AnyValue&);

    std::optional<data::AnyValue> orient_and_go_north(
            ontology::Universe&,
            ontology::CallbackEngine*,
            ontology::CallbackObject*,
            ontology::GenericParentModule&,
            const data::AnyValue&);

    std::optional<data::AnyValue> orient_and_go_south(
            ontology::Universe&,
            ontology::CallbackEngine*,
            ontology::CallbackObject*,
            ontology::GenericParentModule&,
            const data::AnyValue&);

    std::optional<data::AnyValue> rotate_clockwise(
            ontology::Universe&,
            ontology::CallbackEngine*,
            ontology::CallbackObject*,
            ontology::GenericParentModule&,
            const data::AnyValue&);

    std::optional<data::AnyValue> rotate_counterclockwise(
            ontology::Universe&,
            ontology::CallbackEngine*,
            ontology::CallbackObject*,
            ontology::GenericParentModule&,
            const data::AnyValue&);
}

#endif
