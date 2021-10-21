// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2021 Antti Nuortimo.
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

#ifndef __YLIKUUTIO_ONTOLOGY_VARIABLE_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_VARIABLE_HPP_INCLUDED

#include "entity.hpp"
#include "activate_callback.hpp"
#include "read_callback.hpp"
#include "variable_struct.hpp"
#include "code/ylikuutio/data/any_value.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <optional> // std::optional
#include <string>   // std::string

// `yli::ontology::Variable` provides variable-related functionality.
// `Variable`s must be bound to an `Entity`.
//
// Each `Variable` may have `activate_callback` and `read_callback`.
//
// If `activate_callback` is defined, then it is used to activate the
// new value of a `Variable` after defining it.
//
// If `read_callback` is defined, then it is used to read the value
// instead of reading it from `variable_value` member variable, that
// stores the value as `std::shared_ptr<yli::data::AnyValue>`.
//
// `read_callback` may, of course, compute the returned value
// based on some other variables as well etc.

namespace yli::ontology
{
    class Entity;
    class Universe;
    class Scene;
    class Console;

    class Variable: public yli::ontology::Entity 
    {
        public:
            Variable(yli::ontology::Universe* const universe, const yli::ontology::VariableStruct& variable_struct, const yli::data::AnyValue& any_value)
                : Entity(universe, variable_struct),
                parent            { variable_struct.parent },
                variable_value    { any_value },
                activate_callback { variable_struct.activate_callback },
                read_callback     { variable_struct.read_callback }
            {
                // constructor (to be called from `Entity::create_variable`).

                // Get `childID` from `Entity` and set pointer to this `Variable`.
                this->bind_to_parent();

                // `yli::ontology::Entity` member variables begin here.
                this->type_string = "yli::ontology::Variable*";
                this->can_be_erased = true;
            }

            Variable(const Variable&) = delete;            // Delete copy constructor.
            Variable& operator=(const Variable&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~Variable();

            yli::ontology::Entity* get_parent() const override;

            yli::ontology::Scene* get_scene() const override;
            std::size_t get_number_of_children() const override;
            std::size_t get_number_of_descendants() const override;

            std::string help() const;

            std::optional<yli::data::AnyValue> get();
            void set(const yli::data::AnyValue& new_value);
            void set(const std::string& new_value);

            // Public callbacks.

            static std::optional<yli::data::AnyValue> set_variable_const_std_string(
                    yli::ontology::Variable* const variable,
                    const std::string& new_value);

            static std::optional<yli::data::AnyValue> set_variable_variable(
                    yli::ontology::Variable* const dest_variable,
                    yli::ontology::Universe* const /* context */, // A context is needed so that correct `Variable` is bound to the function call.
                    yli::ontology::Variable* const src_variable);

            static std::optional<yli::data::AnyValue> print_value1(
                    yli::ontology::Console* const console,
                    yli::ontology::Universe* const /* context */, // A context is needed so that correct `Variable` is bound to the function call.
                    yli::ontology::Variable* const variable);

            static std::optional<yli::data::AnyValue> activate_planet_radius(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable);

            static std::optional<yli::data::AnyValue> activate_window_width(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable);
            static std::optional<yli::data::AnyValue> activate_window_height(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable);
            static std::optional<yli::data::AnyValue> activate_framebuffer_width(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable);
            static std::optional<yli::data::AnyValue> activate_framebuffer_height(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable);
            static std::optional<yli::data::AnyValue> activate_background_color(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable);

            static std::optional<yli::data::AnyValue> activate_wireframe(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable);

            static std::optional<yli::data::AnyValue> activate_speed(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable);
            static std::optional<yli::data::AnyValue> activate_turbo_factor(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable);
            static std::optional<yli::data::AnyValue> activate_twin_turbo_factor(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable);
            static std::optional<yli::data::AnyValue> activate_mouse_speed(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable);

            static std::optional<yli::data::AnyValue> activate_is_flight_mode_in_use(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable);
            static std::optional<yli::data::AnyValue> activate_console_top_y(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable);
            static std::optional<yli::data::AnyValue> activate_console_bottom_y(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable);
            static std::optional<yli::data::AnyValue> activate_console_left_x(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable);
            static std::optional<yli::data::AnyValue> activate_console_right_x(yli::ontology::Entity* const entity, yli::ontology::Variable* const variable);

            static std::optional<yli::data::AnyValue> read_is_flight_mode_in_use(yli::ontology::Entity* const entity);

            // Public callbacks and here.

        private:
            void bind_to_parent();

            void activate() override;

            yli::ontology::Entity* parent;

        public:
            // The variable value (may be a pointer a some datatype).
            yli::data::AnyValue variable_value;

        private:
            // pointer to `ActivateCallback` used to activate the new value after variable it.
            ActivateCallback activate_callback;

            // pointer to `ReadCallback` used to read the value. Leave to `nullptr` to read the value from `variable_value` of `class Variable`.
            ReadCallback read_callback;
    };
}

#endif
