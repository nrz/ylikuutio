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

#ifndef __CHUNK_MASTER_HPP_INCLUDED
#define __CHUNK_MASTER_HPP_INCLUDED

#include "entity.hpp"
#include "material.hpp"
#include "get_content_callback.hpp"
#include "render_templates.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <queue>    // std::queue
#include <vector>   // std::vector

// `ChunkMaster` takes care of acquiring vertices (through `get_content_callback`),
// organizing vertices into `Chunk` objects, reconstructing `Chunk`
// objects (if vertices have been modified) and deactivating (by
// unbinding) and possibly deleting `Chunk` objects (if needed).

namespace yli
{
    namespace ontology
    {
        class Chunk;

        class ChunkMaster: public yli::ontology::Entity
        {
            public:
                void bind_Chunk(yli::ontology::Chunk* const chunk);
                void unbind_Chunk(const std::size_t childID);

                // constructor.
                ChunkMaster(yli::ontology::Universe* universe, yli::ontology::Material* const parent, GetContentCallback get_content_callback)
                    : yli::ontology::Entity(universe)
                {
                    // constructor.
                    this->get_content_callback = get_content_callback;
                    this->number_of_chunks     = 0;
                    this->parent               = parent;

                    // get `childID` from `Material` and set pointer to this `ChunkMaster`.
                    this->bind_to_parent();

                    // `yli::ontology::Entity` member variables begin here.
                    this->type_string = "ontology::ChunkMaster*";
                }

                ChunkMaster(const ChunkMaster&) = delete;            // Delete copy constructor.
                ChunkMaster &operator=(const ChunkMaster&) = delete; // Delete copy assignment.

                // destructor.
                virtual ~ChunkMaster();

                friend class Chunk;
                template<class T1>
                    friend void yli::hierarchy::bind_child_to_parent(T1 child_pointer, std::vector<T1>& child_pointer_vector, std::queue<std::size_t>& free_childID_queue, std::size_t& number_of_children);
                template<class T1>
                    friend void yli::ontology::render_children(const std::vector<T1>& child_pointer_vector);

            private:
                void bind_to_parent();

                // this method renders all `Chunk`s bound to this `ChunkMaster`.
                void render() override;

                // this method sets `Chunk` pointer.
                void set_chunk_pointer(std::size_t childID, yli::ontology::Chunk* child_pointer);

                std::size_t childID;              // `ChunkMaster` ID, returned by `yli::ontology::Material->get_chunk_masterID()`.

                // Callback used to get the content based on x, y, z.
                GetContentCallback get_content_callback;

                yli::ontology::Material* parent;  // pointer to the `Material`.

                std::vector<ontology::Chunk*> chunk_pointer_vector;
                std::queue<std::size_t> free_chunkID_queue;
                std::size_t number_of_chunks;
        };
    };
}

#endif
