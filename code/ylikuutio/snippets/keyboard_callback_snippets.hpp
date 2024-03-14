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

#ifndef YLIKUUTIO_SNIPPETS_KEYBOARD_CALLBACK_SNIPPETS_HPP_INCLUDED
#define YLIKUUTIO_SNIPPETS_KEYBOARD_CALLBACK_SNIPPETS_HPP_INCLUDED

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
    /*********************************************************************\
     *  Callback engines for action mode keyreleases begin here.         *
    \*********************************************************************/

    std::optional<yli::data::AnyValue> release_first_turbo(
            yli::ontology::Universe& universe,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* callback_object,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&);

    std::optional<yli::data::AnyValue> release_second_turbo(
            yli::ontology::Universe& universe,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* callback_object,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&);

    std::optional<yli::data::AnyValue> enable_toggle_invert_mouse(
            yli::ontology::Universe& universe,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* callback_object,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&);

    std::optional<yli::data::AnyValue> enable_toggle_flight_mode(
            yli::ontology::Universe& universe,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* callback_object,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&);

    std::optional<yli::data::AnyValue> enable_toggle_help_mode(
            yli::ontology::Universe& universe,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* callback_object,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&);

    /*********************************************************************\
     *  Callback engines for action mode keypresses begin here.          *
    \*********************************************************************/

    std::optional<yli::data::AnyValue> exit_program(
            yli::ontology::Universe&,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject*,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&);

    std::optional<yli::data::AnyValue> press_first_turbo(
            yli::ontology::Universe& universe,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* callback_object,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&);

    std::optional<yli::data::AnyValue> press_second_turbo(
            yli::ontology::Universe& universe,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* callback_object,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&);

    std::optional<yli::data::AnyValue> move_forward(
            yli::ontology::Universe& universe,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* callback_object,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&);

    std::optional<yli::data::AnyValue> move_backward(
            yli::ontology::Universe& universe,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* callback_object,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&);

    std::optional<yli::data::AnyValue> strafe_left(
            yli::ontology::Universe& universe,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* callback_object,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&);

    std::optional<yli::data::AnyValue> strafe_right(
            yli::ontology::Universe& universe,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* callback_object,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&);

    std::optional<yli::data::AnyValue> ascent(
            yli::ontology::Universe& universe,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* callback_object,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&);

    std::optional<yli::data::AnyValue> descent(
            yli::ontology::Universe& universe,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* callback_object,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&);

    std::optional<yli::data::AnyValue> toggle_invert_mouse(
            yli::ontology::Universe& universe,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* callback_object,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&);

    std::optional<yli::data::AnyValue> toggle_flight_mode(
            yli::ontology::Universe& universe,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* callback_object,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&);

    std::optional<yli::data::AnyValue> toggle_help_mode(
            yli::ontology::Universe& universe,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* callback_object,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&);

    std::optional<yli::data::AnyValue> delete_entity(
            yli::ontology::Universe& universe,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* callback_object,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&);

    std::optional<yli::data::AnyValue> switch_to_new_material(
            yli::ontology::Universe& universe,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* callback_object,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&);

    std::optional<yli::data::AnyValue> transform_into_new_species(
            yli::ontology::Universe& universe,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* callback_object,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&);
}

#endif
