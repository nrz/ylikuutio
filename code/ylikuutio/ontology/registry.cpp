// Ylikuutio - A 3D game and simulation engine.
//
// Copyright (C) 2015-2022 Antti Nuortimo.
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

#include "registry.hpp"
#include "indexable.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <string>  // std::string
#include <vector>  // std::vector

namespace yli::ontology
{
    class Entity;

    Registry::Registry()
    {
        // constructor.
    }

    Registry::~Registry()
    {
        // destructor.
    }

    bool Registry::is_name(const std::string& name) const
    {
        return (this->is_indexable(name) || this->is_entity(name));
    }

    bool Registry::is_indexable(const std::string& name) const
    {
        return this->indexable_map.count(name) == 1;
    }

    bool Registry::is_entity(const std::string& name) const
    {
        return this->entity_map.count(name) == 1;
    }

    void Registry::add_indexable(yli::ontology::Indexable* const indexable, const std::string& name)
    {
        if (!name.empty() && !this->is_name(name))
        {
            this->indexable_map[name] = indexable;
            this->completable_string_set.add_string(name);
        }
    }

    void Registry::add_entity(yli::ontology::Entity* const entity, const std::string& name)
    {
        if (!name.empty() && !this->is_name(name))
        {
            this->entity_map[name] = entity;
            this->completable_string_set.add_string(name);
        }
    }

    void Registry::erase_entity(const std::string& name)
    {
        if (!name.empty() && this->is_entity(name))
        {
            this->completable_string_set.erase_string(name);
            this->entity_map.erase(name);
        }
    }

    std::size_t Registry::get_number_of_completions(const std::string& input) const
    {
        return this->completable_string_set.get_number_of_completions(input);
    }

    std::string Registry::complete(const std::string& input) const
    {
        return this->completable_string_set.complete(input);
    }

    std::vector<std::string> Registry::get_completions(const std::string& input) const
    {
        return this->completable_string_set.get_completions(input);
    }

    yli::ontology::Entity* Registry::get_indexed_entity(const std::string& indexable_name, std::size_t index) const
    {
        if (this->indexable_map.count(indexable_name) == 1)
        {
            yli::ontology::Indexable* const indexable = this->indexable_map.at(indexable_name);

            if (indexable != nullptr)
            {
                return indexable->get(index);
            }
        }

        return nullptr;
    }

    yli::ontology::Entity* Registry::get_entity(const std::string& name) const
    {
        if (this->entity_map.count(name) == 1)
        {
            return this->entity_map.at(name);
        }

        return nullptr;
    }

    std::string Registry::get_entity_names() const
    {
        std::string entity_names = "";

        std::vector<std::string> keys;
        keys.reserve(this->entity_map.size());

        for (auto& key_and_value : this->entity_map)
        {
            if (!entity_names.empty())
            {
                entity_names += " ";
            }

            std::string key = static_cast<std::string>(key_and_value.first);
            entity_names += key;
        }

        return entity_names;
    }

    const std::unordered_map<std::string, yli::ontology::Indexable*>& Registry::get_indexable_map() const
    {
        return this->indexable_map;
    }

    const std::unordered_map<std::string, yli::ontology::Entity*>& Registry::get_entity_map() const
    {
        return this->entity_map;
    }
}
