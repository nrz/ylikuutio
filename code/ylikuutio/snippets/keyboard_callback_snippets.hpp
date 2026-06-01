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

    std::optional<data::AnyValue> release_first_turbo(
            ontology::Universe& universe,
            ontology::CallbackEngine*,
            ontology::CallbackObject* callback_object,
            ontology::GenericParentModule&,
            const data::AnyValue&);

    std::optional<data::AnyValue> release_second_turbo(
            ontology::Universe& universe,
            ontology::CallbackEngine*,
            ontology::CallbackObject* callback_object,
            ontology::GenericParentModule&,
            const data::AnyValue&);

    std::optional<data::AnyValue> enable_toggle_invert_mouse(
            ontology::Universe& universe,
            ontology::CallbackEngine*,
            ontology::CallbackObject* callback_object,
            ontology::GenericParentModule&,
            const data::AnyValue&);

    std::optional<data::AnyValue> enable_toggle_flight_mode(
            ontology::Universe& universe,
            ontology::CallbackEngine*,
            ontology::CallbackObject* callback_object,
            ontology::GenericParentModule&,
            const data::AnyValue&);

    std::optional<data::AnyValue> enable_toggle_help_mode(
            ontology::Universe& universe,
            ontology::CallbackEngine*,
            ontology::CallbackObject* callback_object,
            ontology::GenericParentModule&,
            const data::AnyValue&);

    /*********************************************************************\
     *  Callback engines for action mode keypresses begin here.          *
    \*********************************************************************/

    std::optional<data::AnyValue> exit_program(
            ontology::Universe&,
            ontology::CallbackEngine*,
            ontology::CallbackObject*,
            ontology::GenericParentModule&,
            const data::AnyValue&);

    std::optional<data::AnyValue> press_first_turbo(
            ontology::Universe& universe,
            ontology::CallbackEngine*,
            ontology::CallbackObject* callback_object,
            ontology::GenericParentModule&,
            const data::AnyValue&);

    std::optional<data::AnyValue> press_second_turbo(
            ontology::Universe& universe,
            ontology::CallbackEngine*,
            ontology::CallbackObject* callback_object,
            ontology::GenericParentModule&,
            const data::AnyValue&);

    std::optional<data::AnyValue> move_forward(
            ontology::Universe& universe,
            ontology::CallbackEngine*,
            ontology::CallbackObject* callback_object,
            ontology::GenericParentModule&,
            const data::AnyValue&);

    std::optional<data::AnyValue> move_backward(
            ontology::Universe& universe,
            ontology::CallbackEngine*,
            ontology::CallbackObject* callback_object,
            ontology::GenericParentModule&,
            const data::AnyValue&);

    std::optional<data::AnyValue> strafe_left(
            ontology::Universe& universe,
            ontology::CallbackEngine*,
            ontology::CallbackObject* callback_object,
            ontology::GenericParentModule&,
            const data::AnyValue&);

    std::optional<data::AnyValue> strafe_right(
            ontology::Universe& universe,
            ontology::CallbackEngine*,
            ontology::CallbackObject* callback_object,
            ontology::GenericParentModule&,
            const data::AnyValue&);

    std::optional<data::AnyValue> ascent(
            ontology::Universe& universe,
            ontology::CallbackEngine*,
            ontology::CallbackObject* callback_object,
            ontology::GenericParentModule&,
            const data::AnyValue&);

    std::optional<data::AnyValue> descent(
            ontology::Universe& universe,
            ontology::CallbackEngine*,
            ontology::CallbackObject* callback_object,
            ontology::GenericParentModule&,
            const data::AnyValue&);

    std::optional<data::AnyValue> toggle_invert_mouse(
            ontology::Universe& universe,
            ontology::CallbackEngine*,
            ontology::CallbackObject* callback_object,
            ontology::GenericParentModule&,
            const data::AnyValue&);

    std::optional<data::AnyValue> toggle_flight_mode(
            ontology::Universe& universe,
            ontology::CallbackEngine*,
            ontology::CallbackObject* callback_object,
            ontology::GenericParentModule&,
            const data::AnyValue&);

    std::optional<data::AnyValue> toggle_help_mode(
            ontology::Universe& universe,
            ontology::CallbackEngine*,
            ontology::CallbackObject* callback_object,
            ontology::GenericParentModule&,
            const data::AnyValue&);

    std::optional<data::AnyValue> delete_entity(
            ontology::Universe& universe,
            ontology::CallbackEngine*,
            ontology::CallbackObject* callback_object,
            ontology::GenericParentModule&,
            const data::AnyValue&);

    std::optional<data::AnyValue> switch_to_new_material(
            ontology::Universe& universe,
            ontology::CallbackEngine*,
            ontology::CallbackObject* callback_object,
            ontology::GenericParentModule&,
            const data::AnyValue&);

    std::optional<data::AnyValue> transform_into_new_species(
            ontology::Universe& universe,
            ontology::CallbackEngine*,
            ontology::CallbackObject* callback_object,
            ontology::GenericParentModule&,
            const data::AnyValue&);
}

#endif
