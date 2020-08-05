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

#ifndef __YLIKUUTIO_ONTOLOGY_ENTITY_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_ENTITY_HPP_INCLUDED

#include "parent_module.hpp"
#include "pre_render_callback.hpp"
#include "post_render_callback.hpp"

// Include standard headers
#include <cstddef>       // std::size_t
#include <memory>        // std::make_shared, std::shared_ptr
#include <queue>         // std::priority_queue, std::queue
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

namespace yli::data
{
    class AnyValue;
}

namespace yli::ontology
{
    class Universe;
    class Console;
    class Variable;
    class EntityFactory;
    struct EntityStruct;
    struct VariableStruct;

    class Entity
    {
        public:
            void bind_variable(yli::ontology::Variable* const variable);

            void unbind_variable(const std::size_t childID, const std::string& local_name);

            // Each class that supports binding to a new parent needs to `override` this function.
            virtual void bind_to_new_parent(yli::ontology::Entity* const new_entity_parent);

            void bind_to_universe();

            // constructor.
            Entity(yli::ontology::Universe* const universe, const yli::ontology::EntityStruct& entity_struct);

            Entity(const Entity&) = delete;            // Delete copy constructor.
            Entity &operator=(const Entity&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~Entity();

            virtual void activate();
            virtual void render();

            std::size_t get_childID() const;
            std::string get_type() const;

            bool get_can_be_erased() const;

            yli::ontology::Universe* get_universe() const;
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

            void create_variable(const yli::ontology::VariableStruct& variable_struct);
            bool has_variable(const std::string& variable_name) const;
            yli::ontology::Variable* get(const std::string& variable_name) const;
            bool set(const std::string& variable_name, std::shared_ptr<yli::data::AnyValue> variable_new_any_value);

            std::string help() const;                                // this function returns general help string.
            std::string help(const std::string& variable_name) const; // this function returns the help string for the `Variable`.

            // Public callbacks.

            // Public `Entity` creation callbacks.

            static std::shared_ptr<yli::data::AnyValue> create_variable_with_parent_name_type_value(
                    yli::ontology::Entity* const parent,
                    std::shared_ptr<std::string> variable_name,
                    std::shared_ptr<std::string> variable_type,
                    std::shared_ptr<std::string> variable_value);

            // Public data printing callbacks.

            static std::shared_ptr<yli::data::AnyValue> print_children(
                    yli::ontology::Console* const console,
                    yli::ontology::Entity* const entity);

            static std::shared_ptr<yli::data::AnyValue> print_variables0(
                    yli::ontology::Universe* const universe,
                    yli::ontology::Console* const console);

            static std::shared_ptr<yli::data::AnyValue> print_variables1(
                    yli::ontology::Universe* const universe,
                    yli::ontology::Console* const console,
                    yli::ontology::Entity* const entity);

            // Public callbacks end here.

            bool should_be_rendered;

            friend yli::ontology::Universe;
            friend yli::ontology::ParentModule;

            std::size_t childID; // TODO: add checks for `std::numeric_limits<std::size_t>::max();` (invalid value).

            yli::ontology::ParentModule parent_of_any_struct_entities;

        protected:
            void prerender() const;
            void postrender() const;

            yli::ontology::Universe* universe; // pointer to the `Universe`.
            std::size_t entityID;

            std::string type_string;

            std::string global_name; // global name of this `Entity`.
            std::string local_name;  // local name of this `Entity`.

            bool can_be_erased;

            PreRenderCallback prerender_callback;
            PostRenderCallback postrender_callback;

            // Named entities are stored here so that they can be recalled, if needed.
            std::unordered_map<std::string, yli::ontology::Entity*> entity_map;

        private:
            std::vector<yli::ontology::Variable*> variable_pointer_vector;
            std::queue<std::size_t> free_variableID_queue;
            std::size_t number_of_variables;

            virtual std::size_t get_number_of_children() const = 0;
            virtual std::size_t get_number_of_descendants() const = 0;

            bool is_application;
            bool is_variable;
    };
}

#endif
