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

#ifndef __YLIKUUTIO_ONTOLOGY_ENTITY_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_ENTITY_HPP_INCLUDED

#include "registry.hpp"
#include "generic_parent_module.hpp"
#include "pre_render_callback.hpp"
#include "post_render_callback.hpp"

// Include standard headers
#include <cstddef>       // std::size_t
#include <limits>        // std::numeric_limits
#include <optional>      // std::optional
#include <string>        // std::string

namespace yli::data
{
    class AnyValue;
}

namespace yli::ontology
{
    class Universe;
    class Variable;
    class Scene;
    class Console;
    class EntityFactory;
    struct EntityStruct;
    struct VariableStruct;

    class Entity
    {
        public:
            void bind_variable(yli::ontology::Variable* const variable);

            void unbind_variable(const std::size_t childID);

            // Each class that supports binding to a new parent needs to `override` this function.
            virtual void bind_to_new_parent(yli::ontology::Entity* const /* new_parent */);

            void bind_to_universe();

            // constructor.
            Entity(yli::ontology::Universe* const universe, const yli::ontology::EntityStruct& entity_struct);

            Entity(const Entity&) = delete;            // Delete copy constructor.
            Entity& operator=(const Entity&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~Entity();

            virtual void activate();

            std::size_t get_childID() const;
            std::string get_type() const;

            bool get_can_be_erased() const;

            yli::ontology::Universe* get_universe() const;

            // Different classes are bound to `Scene` in different ways,
            // so they need to `override` this to provide the functionality.
            // Note: not all classes have any relation to a specific `Scene`.
            // E.g. `Universe` may have many `Scene`s, but is descendant of none.
            virtual yli::ontology::Scene* get_scene() const = 0;

            virtual yli::ontology::EntityFactory* get_entity_factory() const;

            virtual yli::ontology::Entity* get_parent() const = 0;
            std::size_t get_number_of_all_children() const;
            std::size_t get_number_of_all_descendants() const;
            std::size_t get_number_of_variables() const;
            std::size_t get_number_of_non_variable_children() const;

            std::string get_global_name() const;
            std::string get_local_name() const;
            void set_global_name(const std::string& global_name);
            void set_local_name(const std::string& local_name);

            bool has_child(const std::string& name) const;
            yli::ontology::Entity* get_entity(const std::string& name) const;
            std::string get_entity_names() const;
            void add_entity(const std::string& name, yli::ontology::Entity* const entity);
            void erase_entity(const std::string& name);

            void create_variable(const yli::ontology::VariableStruct& variable_struct, const yli::data::AnyValue& any_value);
            bool has_variable(const std::string& variable_name) const;
            yli::ontology::Variable* get(const std::string& variable_name) const;
            bool set(const std::string& variable_name, const yli::data::AnyValue& variable_new_any_value);

            std::string help() const;                                // this function returns general help string.
            std::string help(const std::string& variable_name) const; // this function returns the help string for the `Variable`.

            // Public callbacks.

            // Public `Entity` creation callbacks.

            static std::optional<yli::data::AnyValue> create_variable_with_parent_name_type_value(
                    yli::ontology::Entity& parent,
                    const std::string& variable_name,
                    const std::string& variable_type,
                    const std::string& variable_value);

            // Public data printing callbacks.

            static std::optional<yli::data::AnyValue> print_children(
                    yli::ontology::Console& console,
                    const yli::ontology::Entity& entity);

            static std::optional<yli::data::AnyValue> print_variables0(
                    const yli::ontology::Universe& universe,
                    yli::ontology::Console& console);

            static std::optional<yli::data::AnyValue> print_variables1(
                    const yli::ontology::Universe&,
                    yli::ontology::Console& console,
                    const yli::ontology::Entity& entity);

            // Public callbacks end here.

            bool should_be_rendered { false };

            friend class yli::ontology::GenericParentModule;
            friend class yli::ontology::Universe;

            std::size_t childID { std::numeric_limits<std::size_t>::max() };

            // Named entities are stored here so that they can be recalled, if needed.
            yli::ontology::Registry registry;
            yli::ontology::GenericParentModule parent_of_variables;
            yli::ontology::GenericParentModule parent_of_any_struct_entities;

        protected:
            void prerender() const;
            void postrender() const;

            yli::ontology::Universe* universe { nullptr }; // pointer to the `Universe`.
            std::size_t entityID { std::numeric_limits<std::size_t>::max() };

            std::string type_string;

            std::string global_name; // global name of this `Entity`.
            std::string local_name;  // local name of this `Entity`.

            bool can_be_erased { false };

            PreRenderCallback prerender_callback { nullptr };
            PostRenderCallback postrender_callback { nullptr };

        private:
            virtual std::size_t get_number_of_children() const = 0;
            virtual std::size_t get_number_of_descendants() const = 0;

            bool is_variable;
    };
}

#endif
