// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2025 Antti Nuortimo.
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

#ifndef YLIKUUTIO_ONTOLOGY_REGISTRY_HPP_INCLUDED
#define YLIKUUTIO_ONTOLOGY_REGISTRY_HPP_INCLUDED

#include "code/ylikuutio/string/string_set.hpp"

// Include standard headers
#include <cstddef>       // std::size_t
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector

namespace yli::ontology
{
    class Indexable;
    class Completable;
    class Entity;

    class Registry final
    {
        public:
            Registry() = default;

            Registry(const Registry&) = delete;            // Delete copy constructor.
            Registry& operator=(const Registry&) = delete; // Delete copy assignment.

            ~Registry() = default;

            bool is_name(const std::string& name) const;
            bool is_indexable(const std::string& name) const;
            bool is_entity(const std::string& name) const;

            void add_indexable(Indexable& indexable, const std::string& name);
            void add_entity(Entity& entity, const std::string& name);

            void erase_entity(const std::string& name);

            std::size_t get_number_of_completions(const std::string& input) const;
            std::string complete(const std::string& input) const;
            std::vector<std::string> get_completions(const std::string& input) const;

            Entity* get_indexed_entity(const std::string& indexable_name, std::size_t index) const;
            Entity* get_entity(const std::string& name) const;

            std::string get_entity_name(const Entity& entity) const;
            std::string get_entity_names() const;

            const std::unordered_map<std::string, Indexable*>& get_indexable_map() const;
            const std::unordered_map<std::string, Entity*>& get_entity_map() const;

        private:
            // Completable modules are stored here.
            // Everything stored in `indexable_map` or `entity_map` can be completed.
            yli::string::StringSet completable_string_set;

            // Indexable modules are stored here.
            std::unordered_map<std::string, Indexable*> indexable_map;

            // Named entities are stored here so that they can be recalled, if needed.
            std::unordered_map<std::string, Entity*> entity_map;
    };
}

#endif
