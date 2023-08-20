// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2023 Antti Nuortimo.
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

#include "keyboard_callback_snippets.hpp"
#include "code/ylikuutio/ontology/callback_object.hpp"
#include "code/ylikuutio/ontology/callback_magic_numbers.hpp"
#include "code/ylikuutio/ontology/object.hpp"
#include "code/ylikuutio/ontology/species.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/universe.hpp"
#include "code/ylikuutio/ontology/scene.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include GLM
#ifndef __GLM_GLM_HPP_INCLUDED
#define __GLM_GLM_HPP_INCLUDED
#include <glm/glm.hpp> // glm
#endif

// Include standard headers
#include <functional> // std::reference_wrapper
#include <iostream> // std::cout, std::cin, std::cerr
#include <optional> // std::optional
#include <stdint.h> // uint32_t etc.
#include <string>   // std::string
#include <variant>  // std::holds_alternative, std::variant

// Callbacks' input parameters can be accessed either through
// `yli::ontology::CallbackObject* callback_object`or
// `yli::ontology::GenericParentModule& input parameters`.
//
// To access a name input variable:
// `std::optional<yli::data::AnyValue> some_any_value = callback_object->get_any_value("foo");`
// where `"foo"` is the variable name.
//
// Using a numeric index is more efficient and should be used
// in cases where the input variable order is known beforehand.
// However, the difference may be small.
//
// To access an input variable using a numeric index (this works for named input variables too):
// `std::optional<yli::data::AnyValue> some_any_value = callback_object->get_arg(0);`
//
// `get_arg` takes the zero-based index of the variable as function parameter.
// First `CallbackParameter` of a `CallbackObject` gets index 0,
// second `CallbackParameter` gets index 1, etc.

namespace yli::ontology
{
    class GenericParentModule;
    class CallbackEngine;
}

namespace yli::snippets
{
    /*********************************************************************\
     * Helper functions for callbacks begin here.                        *
    \*********************************************************************/

    bool move_to_direction(yli::ontology::Universe& universe, const yli::ontology::CallbackObject* const /* callback_object */, const glm::vec3& moving_direction)
    {
        // Movement changes location and orientation variables stored in `yli::ontology::Universe`.
        // This way there is no need to dereference pointer to the current `yli::ontology::Camera`.
        // When the current `Camera` is changed, then the location and orientation data is copied
        // from `Universe` to the previous `Camera`.
        //
        // Also, location and orientation variables' read callbacks need to check if the referred
        // `Scene` is the current `Scene`. If true, then get and return the location or orientation
        // variable in question from the `Universe`, otherwise return the location or orientation
        // variable from the `Scene`'s own member variable.

        const yli::ontology::Scene* const scene = universe.get_active_scene();

        if (scene == nullptr)
        {
            // No active scene.
            return false;
        }

        float temp_speed;

        if (universe.is_first_turbo_pressed && universe.is_second_turbo_pressed)
        {
            temp_speed = universe.twin_turbo_factor * universe.speed;
        }
        else if (universe.is_first_turbo_pressed || universe.is_second_turbo_pressed)
        {
            temp_speed = universe.turbo_factor * universe.speed;
        }
        else
        {
            temp_speed = universe.speed;
        }
        universe.current_camera_location.xyz += temp_speed * static_cast<float>(universe.get_delta_time()) * moving_direction;

        return true;
    }

    /*********************************************************************\
     *  Callback engines for action mode keyreleases begin here.         *
    \*********************************************************************/

    std::optional<yli::data::AnyValue> release_first_turbo(
            yli::ontology::Universe& universe,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* /* callback_object */,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&)
    {
        universe.is_first_turbo_pressed = false;
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> release_second_turbo(
            yli::ontology::Universe& universe,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* /* callback_object */,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&)
    {
        universe.is_second_turbo_pressed = false;
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> enable_toggle_invert_mouse(
            yli::ontology::Universe& universe,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* /* callback_object */,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&)
    {
        universe.can_toggle_invert_mouse = true;
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> enable_toggle_flight_mode(
            yli::ontology::Universe& universe,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* /* callback_object */,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&)
    {
        universe.can_toggle_flight_mode = true;
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> enable_toggle_help_mode(
            yli::ontology::Universe& universe,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* /* callback_object */,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&)
    {
        universe.can_toggle_help_mode = true;
        return std::nullopt;
    }

    /*********************************************************************\
     *  Callback engines for action mode keypresses begin here.          *
    \*********************************************************************/

    std::optional<yli::data::AnyValue> exit_program(
            yli::ontology::Universe&,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject*,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&)
    {
        const uint32_t exit_program_magic_number = EXIT_PROGRAM_MAGIC_NUMBER;
        return yli::data::AnyValue(exit_program_magic_number);
    }

    std::optional<yli::data::AnyValue> first_turbo(
            yli::ontology::Universe& universe,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* /* callback_object */,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&)
    {
        universe.is_first_turbo_pressed = true;
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> second_turbo(
            yli::ontology::Universe& universe,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* /* callback_object */,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&)
    {
        universe.is_second_turbo_pressed = true;
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> move_forward(
            yli::ontology::Universe& universe,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* callback_object,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&)
    {
        yli::snippets::move_to_direction(universe, callback_object, universe.current_camera_direction);
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> move_backward(
            yli::ontology::Universe& universe,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* callback_object,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&)
    {
        yli::snippets::move_to_direction(universe, callback_object, -universe.current_camera_direction);
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> strafe_left(
            yli::ontology::Universe& universe,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* callback_object,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&)
    {
        yli::snippets::move_to_direction(universe, callback_object, -universe.current_camera_right);
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> strafe_right(
            yli::ontology::Universe& universe,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* callback_object,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&)
    {
        yli::snippets::move_to_direction(universe, callback_object, universe.current_camera_right);
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> ascent(
            yli::ontology::Universe& universe,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* callback_object,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&)
    {
        yli::snippets::move_to_direction(universe, callback_object, universe.current_camera_up);
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> descent(
            yli::ontology::Universe& universe,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* callback_object,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&)
    {
        yli::snippets::move_to_direction(universe, callback_object, -universe.current_camera_up);
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> toggle_invert_mouse(
            yli::ontology::Universe& universe,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* /* callback_object */,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&)
    {
        if (universe.can_toggle_invert_mouse)
        {
            universe.is_invert_mouse_in_use = !universe.is_invert_mouse_in_use;
            universe.can_toggle_invert_mouse = false;
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> toggle_flight_mode(
            yli::ontology::Universe& universe,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* /* callback_object */,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&)
    {
        if (universe.can_toggle_flight_mode)
        {
            yli::ontology::Scene* const scene = universe.get_active_scene();

            if (scene == nullptr)
            {
                return std::nullopt;
            }

            scene->set_is_flight_mode_in_use(!scene->get_is_flight_mode_in_use());
            universe.can_toggle_flight_mode = false;
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> toggle_help_mode(
            yli::ontology::Universe& universe,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* /* callback_object */,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&)
    {
        if (universe.can_toggle_help_mode)
        {
            universe.in_help_mode = !universe.in_help_mode;
            universe.can_toggle_help_mode = false;
        }
        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> delete_entity(
            yli::ontology::Universe& universe,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* callback_object,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&)
    {
        std::optional<yli::data::AnyValue> entity_name_string_any_value = callback_object->get_arg(0);

        if (!entity_name_string_any_value)
        {
            std::cerr << "ERROR: `yli::snippets::delete_entity`: there is no argument 0.\n";
            return std::nullopt;
        }

        if (!std::holds_alternative<std::reference_wrapper<std::string>>((*entity_name_string_any_value).data) &&
                !std::holds_alternative<std::reference_wrapper<const std::string>>((*entity_name_string_any_value).data))
        {
            std::cerr << "ERROR: `yli::snippets::delete_entity`: invalid datatype.\n";
            std::cerr << "Datatype should be `std::reference_wrapper<std::string>` or `std::reference_wrapper<const std::string>`\n";
            return std::nullopt;
        }

        const std::string& entity_name_string_ref = entity_name_string_any_value->get_const_std_string_ref();

        yli::ontology::Entity* const entity = universe.get_entity(entity_name_string_ref);

        if (entity == nullptr)
        {
            std::cerr << "ERROR: `yli::snippets::delete_entity`: `Entity` with name `" << entity_name_string_ref << "` does not exist!\n";
            return std::nullopt;
        }

        delete entity;

        return std::nullopt;
    }

    std::optional<yli::data::AnyValue> switch_to_new_material(
            yli::ontology::Universe& universe,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* callback_object,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&)
    {
        std::optional<yli::data::AnyValue> species_entity_name_string_any_value = callback_object->get_arg(0);

        if (!species_entity_name_string_any_value)
        {
            std::cerr << "ERROR: `yli::snippets::switch_to_new_material`: there is no argument 0.\n";
            return std::nullopt;
        }

        if (!std::holds_alternative<std::reference_wrapper<std::string>>((*species_entity_name_string_any_value).data) &&
                !std::holds_alternative<std::reference_wrapper<const std::string>>((*species_entity_name_string_any_value).data))
        {
            std::cerr << "ERROR: `yli::snippets::switch_to_new_material`: invalid datatype.\n";
            std::cerr << "Datatype should be `std::reference_wrapper<std::string>` or `std::reference_wrapper<const std::string>`\n";
            return std::nullopt;
        }

        const std::string& species_entity_name_string_ref = species_entity_name_string_any_value->get_const_std_string_ref();

        yli::ontology::Entity* const species_entity = universe.get_entity(species_entity_name_string_ref);

        if (species_entity == nullptr)
        {
            std::cerr << "ERROR: `yli::snippets::switch_to_new_material`: `Entity` with name `" << species_entity_name_string_ref << "` (arg 0) does not exist!\n";
            return std::nullopt;
        }

        yli::ontology::Species* const species = dynamic_cast<yli::ontology::Species*>(species_entity);

        if (species == nullptr)
        {
            std::cerr << "ERROR: `yli::snippets::switch_to_new_material`: `Entity` with name `" << species_entity_name_string_ref << "` (arg 0) is not `Species`!\n";
            return std::nullopt;
        }

        std::optional<yli::data::AnyValue> material_name_string_any_value = callback_object->get_arg(1);

        if (!material_name_string_any_value)
        {
            std::cerr << "ERROR: `yli::snippets::switch_to_new_material`: there is no argument 1.\n";
            return std::nullopt;
        }

        if (!std::holds_alternative<std::reference_wrapper<std::string>>((*material_name_string_any_value).data) &&
                !std::holds_alternative<std::reference_wrapper<const std::string>>((*material_name_string_any_value).data))
        {
            std::cerr << "ERROR: `yli::snippets::switch_to_new_material`: invalid datatype.\n";
            std::cerr << "Datatype should be `std::reference_wrapper<std::string>` or `std::reference_wrapper<const std::string>`\n";
            return std::nullopt;
        }

        const std::string& new_material_string_ref = material_name_string_any_value->get_const_std_string_ref();

        yli::ontology::Entity* const new_material_entity = universe.get_entity(new_material_string_ref);

        if (new_material_entity == nullptr)
        {
            std::cerr << "ERROR: `yli::snippets::switch_to_new_material`: `Entity` with name `" << new_material_string_ref << "` (arg 1) does not exist!\n";
            return std::nullopt;
        }

        yli::ontology::Material* const new_material = dynamic_cast<yli::ontology::Material*>(new_material_entity);

        if (new_material == nullptr)
        {
            std::cerr << "ERROR: `yli::snippets::switch_to_new_material`: `Entity` with name `" << new_material_string_ref << "` (arg 1) is not `Material`!\n";
            return std::nullopt;
        }

        return yli::ontology::Species::bind_to_new_material(*species, *new_material);
    }

    std::optional<yli::data::AnyValue> transform_into_new_species(
            yli::ontology::Universe& universe,
            yli::ontology::CallbackEngine*,
            yli::ontology::CallbackObject* callback_object,
            yli::ontology::GenericParentModule&,
            const yli::data::AnyValue&)
    {
        std::optional<yli::data::AnyValue> object_entity_name_string_any_value = callback_object->get_arg(0);

        if (!object_entity_name_string_any_value)
        {
            std::cerr << "ERROR: `yli::snippets::transform_into_new_species`: there is no argument 0.\n";
            return std::nullopt;
        }

        if (!std::holds_alternative<std::reference_wrapper<std::string>>((*object_entity_name_string_any_value).data) &&
                !std::holds_alternative<std::reference_wrapper<const std::string>>((*object_entity_name_string_any_value).data))
        {
            std::cerr << "ERROR: `yli::snippets::transform_into_new_species`: invalid datatype.\n";
            std::cerr << "Datatype should be `std::reference_wrapper<std::string>` or `std::reference_wrapper<const std::string>`\n";
            return std::nullopt;
        }

        const std::string& object_entity_name_string_ref = object_entity_name_string_any_value->get_const_std_string_ref();

        yli::ontology::Entity* const object_entity = universe.get_entity(object_entity_name_string_ref);

        if (object_entity == nullptr)
        {
            std::cerr << "ERROR: `yli::snippets::transform_into_new_species`: `Entity` with name `" << object_entity_name_string_ref << "` (arg 0) does not exist!\n";
            return std::nullopt;
        }

        yli::ontology::Object* const object = dynamic_cast<yli::ontology::Object*>(object_entity);

        if (object == nullptr)
        {
            std::cerr << "ERROR: `yli::snippets::transform_into_new_species`: `Entity` with name `" << object_entity_name_string_ref << "` (arg 0) is not `Object`!\n";
            return std::nullopt;
        }

        std::optional<yli::data::AnyValue> species_name_string_any_value = callback_object->get_arg(1);

        if (!species_name_string_any_value)
        {
            std::cerr << "ERROR: `yli::snippets::transform_into_new_species`: there is no argument 1.\n";
            return std::nullopt;
        }

        if (!std::holds_alternative<std::reference_wrapper<std::string>>((*species_name_string_any_value).data) &&
                !std::holds_alternative<std::reference_wrapper<const std::string>>((*species_name_string_any_value).data))
        {
            std::cerr << "ERROR: `yli::snippets::transform_into_new_species`: arg 1 is of invalid datatype.\n";
            std::cerr << "Datatype should be `std::reference_wrapper<std::string>` or `std::reference_wrapper<const std::string>`\n";
            return std::nullopt;
        }

        const std::string& new_species_string_ref = species_name_string_any_value->get_const_std_string_ref();

        yli::ontology::Entity* const new_species_entity = universe.get_entity(new_species_string_ref);

        if (new_species_entity == nullptr)
        {
            return std::nullopt;
        }

        yli::ontology::Species* const new_species = dynamic_cast<yli::ontology::Species*>(new_species_entity);

        if (new_species == nullptr)
        {
            return std::nullopt;
        }

        return yli::ontology::Object::bind_to_new_species_master(*object, *new_species);
    }
}
