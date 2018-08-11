#include "chunk_master.hpp"
#include "material.hpp"
#include "chunk.hpp"
#include "material.hpp"
#include "render_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/common/globals.hpp"

// Include standard headers
#include <cstddef>  // std::size_t
#include <iostream> // std::cout, std::cin, std::cerr

namespace yli
{
    namespace ontology
    {
        void ChunkMaster::bind_chunk(yli::ontology::Chunk* const chunk)
        {
            // get `childID` from `ChunkMaster` and set pointer to `chunk`.
            yli::hierarchy::bind_child_to_parent<yli::ontology::Chunk*>(
                    chunk,
                    this->chunk_pointer_vector,
                    this->free_chunkID_queue,
                    this->number_of_chunks);
        }

        void ChunkMaster::unbind_chunk(const std::size_t childID)
        {
            yli::hierarchy::unbind_child_from_parent(
                    childID,
                    this->chunk_pointer_vector,
                    this->free_chunkID_queue,
                    this->number_of_chunks);
        }

        void ChunkMaster::bind_to_parent()
        {
            // get `childID` from `Material` and set pointer to this `ChunkMaster`.
            this->parent->bind_chunk_master(this);
        }

        ChunkMaster::~ChunkMaster()
        {
            // destructor.

            // destroy all chunks of this material.
            std::cout << "All chunks of this material will be destroyed.\n";
            yli::hierarchy::delete_children<ontology::Chunk*>(this->chunk_pointer_vector, this->number_of_chunks);

            // set pointer to this `ChunkMaster` to nullptr.
            this->parent->set_chunk_master_pointer(this->childID, nullptr);
        }

        void ChunkMaster::set_chunk_pointer(std::size_t childID, yli::ontology::Chunk* child_pointer)
        {
            yli::hierarchy::set_child_pointer(childID, child_pointer, this->chunk_pointer_vector, this->free_chunkID_queue, this->number_of_chunks);
        }

        void ChunkMaster::render()
        {
            // render `ChunkMaster` by calling `render()` function of each `Chunk`.
            yli::ontology::render_children<ontology::Chunk*>(this->chunk_pointer_vector);
        }
    }
}
