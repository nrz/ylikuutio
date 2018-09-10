#ifndef __CHUNK_MASTER_HPP_INCLUDED
#define __CHUNK_MASTER_HPP_INCLUDED

#include "entity.hpp"
#include "material.hpp"
#include "render_templates.hpp"
#include "code/ylikuutio/common/globals.hpp"

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
                void bind_chunk(yli::ontology::Chunk* const chunk);
                void unbind_chunk(const std::size_t childID);

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
                void render();

                // this method sets `Chunk` pointer.
                void set_chunk_pointer(std::size_t childID, yli::ontology::Chunk* child_pointer);

                std::size_t childID;              // `ChunkMaster` ID, returned by `yli::ontology::Material->get_chunk_masterID()`.

                // Callback used to get the content based on x, y, z.
                GetContentCallback get_content_callback;

                yli::ontology::Material* parent;  // pointer to `Material`.

                std::vector<ontology::Chunk*> chunk_pointer_vector;
                std::queue<std::size_t> free_chunkID_queue;
                std::size_t number_of_chunks;
        };
    };
}

#endif
