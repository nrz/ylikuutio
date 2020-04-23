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

#ifndef __APP_KEYBOARD_CALLBACKS_HPP_INCLUDED
#define __APP_KEYBOARD_CALLBACKS_HPP_INCLUDED

// Include standard headers
#include <memory> // std::make_shared, std::shared_ptr
#include <vector> // std::vector

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
    /*********************************************************************\
     *  Callback engines for action mode keyreleases begin here.         *
    \*********************************************************************/

    std::shared_ptr<yli::common::AnyValue> release_first_turbo(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::common::AnyValue>);

    std::shared_ptr<yli::common::AnyValue> release_second_turbo(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::common::AnyValue>);

    std::shared_ptr<yli::common::AnyValue> enable_toggle_invert_mouse(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::common::AnyValue>);

    std::shared_ptr<yli::common::AnyValue> enable_toggle_flight_mode(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::common::AnyValue>);

    std::shared_ptr<yli::common::AnyValue> enable_toggle_help_mode(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::common::AnyValue>);

    /*********************************************************************\
     *  Callback engines for action mode keypresses begin here.          *
    \*********************************************************************/

    std::shared_ptr<yli::common::AnyValue> exit_program(
            yli::ontology::Universe*,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject*,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::common::AnyValue>);

    std::shared_ptr<yli::common::AnyValue> first_turbo(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::common::AnyValue>);

    std::shared_ptr<yli::common::AnyValue> second_turbo(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::common::AnyValue>);

    std::shared_ptr<yli::common::AnyValue> move_forward(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::common::AnyValue>);

    std::shared_ptr<yli::common::AnyValue> move_backward(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::common::AnyValue>);

    std::shared_ptr<yli::common::AnyValue> strafe_left(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::common::AnyValue>);

    std::shared_ptr<yli::common::AnyValue> strafe_right(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::common::AnyValue>);

    std::shared_ptr<yli::common::AnyValue> ascent(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::common::AnyValue>);

    std::shared_ptr<yli::common::AnyValue> descent(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::common::AnyValue>);

    std::shared_ptr<yli::common::AnyValue> toggle_invert_mouse(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::common::AnyValue>);

    std::shared_ptr<yli::common::AnyValue> toggle_flight_mode(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::common::AnyValue>);

    std::shared_ptr<yli::common::AnyValue> toggle_help_mode(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::common::AnyValue>);

    std::shared_ptr<yli::common::AnyValue> delete_entity(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::common::AnyValue>);

    std::shared_ptr<yli::common::AnyValue> switch_to_new_material(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::common::AnyValue>);

    std::shared_ptr<yli::common::AnyValue> transform_into_new_species(
            yli::ontology::Universe* universe,
            yli::callback::CallbackEngine*,
            yli::callback::CallbackObject* callback_object,
            std::vector<yli::callback::CallbackParameter*>&,
            std::shared_ptr<yli::common::AnyValue>);
}

#endif
