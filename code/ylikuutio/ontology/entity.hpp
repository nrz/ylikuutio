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

#ifndef YLIKUUTIO_ONTOLOGY_ENTITY_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_ENTITY_HPP_INCLUDED

#include "registry.hpp"
#include "generic_parent_module.hpp"
#include "code/ylikuutio/data/any_value.hpp"
#include "code/ylikuutio/memory/constructible_module.hpp"

// Include standard headers
#include <cstddef>       // std::size_t
#include <limits>        // std::numeric_limits
#include <optional>      // std::optional
#include <string>        // std::string

namespace yli::core
{
    class Application;
}

namespace yli::memory
{
    template<typename T1, std::size_t DataSize>
        class MemoryAllocator;

    template<typename T1, std::size_t DataSize>
        class MemoryStorage;
}

namespace yli::ontology
{
    class Universe;
    class Variable;
    class Scene;
    class Console;
    class GenericEntityFactory;
    struct EntityStruct;
    struct VariableStruct;

    class Entity
    {
        public:
            bool operator==(const Entity& rhs) const noexcept;
            bool operator!=(const Entity& rhs) const = default;

            yli::core::Application& get_application() const;

            void bind_to_universe() noexcept;

        protected:
            Entity(
                    yli::core::Application& application,
                    Universe& universe,
                    const EntityStruct& entity_struct);

        public:
            virtual ~Entity();

            Entity(const Entity&) = delete;            // Delete copy constructor.
            Entity& operator=(const Entity&) = delete; // Delete copy assignment.

            virtual void activate();                   // Activation functions should be idempotent.

            void terminate();
            yli::memory::ConstructibleModule get_constructible_module() const;

            void set_childID(const std::size_t childID);
            std::size_t get_childID() const;
            void release();
            std::string get_type() const;

            bool get_can_be_erased() const;

            Universe& get_universe() const;

            // Different classes are bound to `Scene` in different ways,
            // so they need to `override` this to provide the functionality.
            // Note: not all classes have any relation to a specific `Scene`.
            // E.g. `Universe` may have many `Scene`s, but is descendant of none.
            virtual Scene* get_scene() const = 0;

            virtual Entity* get_parent() const = 0;
            std::size_t get_number_of_all_children() const;
            std::size_t get_number_of_all_descendants() const;
            std::size_t get_number_of_variables() const;
            std::size_t get_number_of_non_variable_children() const;

            std::string get_global_name() const;
            std::string get_local_name() const;
            void set_global_name(const std::string& global_name);
            void set_local_name(const std::string& local_name);

            bool has_child(const std::string& name) const;
            Entity* get_entity(const std::string& name) const;
            std::string get_entity_names() const;
            std::string complete(const std::string& input) const;
            void add_entity(const std::string& name, Entity& entity);
            void erase_entity(const std::string& name);

            void create_variable(const VariableStruct& variable_struct, yli::data::AnyValue&& any_value);
            bool has_variable(const std::string& variable_name) const;
            Variable* get_variable(const std::string& variable_name) const;
            bool set_variable(const std::string& variable_name, const yli::data::AnyValue& variable_new_any_value);

            virtual std::string help() const;                         // this function returns general help string.
            virtual std::string help_for_variable(const std::string& variable_name) const; // this function returns the help string for the `Variable`.

            // Public callbacks.

            // Public `Entity` creation callbacks.

            static std::optional<yli::data::AnyValue> create_variable_with_parent_name_type_value(
                    Entity& parent,
                    const std::string& variable_name,
                    const std::string& variable_type,
                    const std::string& variable_value);

            // Public data printing callbacks.

            static std::optional<yli::data::AnyValue> print_children(
                    Console& console,
                    const Entity& entity);

            static std::optional<yli::data::AnyValue> print_variables0(
                    const Universe& universe,
                    Console& console);

            static std::optional<yli::data::AnyValue> print_variables1(
                    const Universe&,
                    Console& console,
                    const Entity& entity);

            // Public callbacks end here.

            bool should_render { false };

            friend class GenericParentModule;
            friend class Universe;

            template<typename T1, std::size_t DataSize>
                friend class yli::memory::MemoryAllocator;

            template<typename T1, std::size_t DataSize>
                friend class yli::memory::MemoryStorage;

        private:
            yli::memory::ConstructibleModule constructible_module;

            yli::core::Application& application;

            std::size_t childID { std::numeric_limits<std::size_t>::max() };

        public:
            // Named entities are stored here so that they can be recalled, if needed.
            Registry registry;
            GenericParentModule parent_of_variables;
            GenericParentModule parent_of_callback_engines;

        protected:
            Universe& universe;
            std::size_t entityID { std::numeric_limits<std::size_t>::max() };

            std::string type_string;

            std::string global_name; // global name of this `Entity`.
            std::string local_name;  // local name of this `Entity`.

            bool can_be_erased { false };
            const bool is_universe;

        private:
            virtual std::size_t get_number_of_children() const = 0;
            virtual std::size_t get_number_of_descendants() const = 0;
    };
}

#endif
