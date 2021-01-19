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

#ifndef __YLIKUUTIO_ONTOLOGY_PARENT_MODULE_HPP_INCLUDED
#define __YLIKUUTIO_ONTOLOGY_PARENT_MODULE_HPP_INCLUDED

#include "indexable.hpp"

// Include standard headers
#include <cstddef> // std::size_t
#include <queue>   // std::queue
#include <string>  // std::string
#include <vector>  // std::vector

namespace yli::ontology
{
    class Registry;
    class Entity;

    class ParentModule: public yli::ontology::Indexable
    {
        public:
            void bind_child(yli::ontology::Entity* const child);
            void unbind_child(std::size_t childID);

            // constructor.
            ParentModule(yli::ontology::Entity* const entity, yli::ontology::Registry* const registry, const std::string& name);

            ParentModule(const ParentModule&) = delete;            // Delete copy constructor.
            ParentModule& operator=(const ParentModule&) = delete; // Delete copy assignment.

            // destructor.
            virtual ~ParentModule();

            yli::ontology::Entity* get_entity() const;
            std::size_t get_number_of_children() const;
            std::size_t get_number_of_descendants() const;

            yli::ontology::Entity* get(const std::size_t index) const override;

            std::vector<yli::ontology::Entity*> child_pointer_vector;

        private:
            std::queue<std::size_t> free_childID_queue;
            std::size_t number_of_children;

            yli::ontology::Entity* entity; // The `Entity` that owns this `ParentModule`.
    };
}

#endif
