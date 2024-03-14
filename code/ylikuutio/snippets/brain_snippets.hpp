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

#ifndef YLIKUUTIO_SNIPPETS_BRAIN_SNIPPETS_HPP_INCLUDED
#define YLIKUUTIO_SNIPPETS_BRAIN_SNIPPETS_HPP_INCLUDED

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
    std::optional<yli::data::AnyValue> rest(
            yli::ontology::Universe&,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject*,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&);

    std::optional<yli::data::AnyValue> go_east(
            yli::ontology::Universe&,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject*,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&);

    std::optional<yli::data::AnyValue> go_west(
            yli::ontology::Universe&,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject*,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&);

    std::optional<yli::data::AnyValue> go_north(
            yli::ontology::Universe&,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject*,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&);

    std::optional<yli::data::AnyValue> go_south(
            yli::ontology::Universe&,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject*,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&);

    std::optional<yli::data::AnyValue> orient_to_east(
            yli::ontology::Universe&,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject*,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&);

    std::optional<yli::data::AnyValue> orient_to_west(
            yli::ontology::Universe&,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject*,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&);

    std::optional<yli::data::AnyValue> orient_to_north(
            yli::ontology::Universe&,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject*,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&);

    std::optional<yli::data::AnyValue> orient_to_south(
            yli::ontology::Universe&,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject*,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&);

    std::optional<yli::data::AnyValue> orient_and_go_east(
            yli::ontology::Universe&,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject*,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&);

    std::optional<yli::data::AnyValue> orient_and_go_west(
            yli::ontology::Universe&,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject*,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&);

    std::optional<yli::data::AnyValue> orient_and_go_north(
            yli::ontology::Universe&,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject*,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&);

    std::optional<yli::data::AnyValue> orient_and_go_south(
            yli::ontology::Universe&,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject*,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&);

    std::optional<yli::data::AnyValue> rotate_clockwise(
            yli::ontology::Universe&,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject*,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&);

    std::optional<yli::data::AnyValue> rotate_counterclockwise(
            yli::ontology::Universe&,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject*,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&);
}

#endif
