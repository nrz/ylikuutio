#include "chunk.hpp"
#include "chunk_master.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

namespace space_partition
{
    void Chunk::bind_to_parent()
    {
        // get `childID` from the `ChunkMaster` and set pointer to this `Chunk`.
        hierarchy::bind_child_to_parent<space_partition::Chunk*>(this, this->parent_pointer->chunk_pointer_vector, this->parent_pointer->free_chunkID_queue, &this->parent_pointer->number_of_chunks);
    }

    Chunk::~Chunk()
    {
        // destructor.

        // set pointer to this `Chunk` to nullptr.
        this->parent_pointer->set_chunk_pointer(this->childID, nullptr);
    }

    void Chunk::render()
    {
        // Render this `Chunk`.
        // If any vertex of the `Chunk` has changed, the vertex data
        // of the `Chunk` needs to be reconstructed before rendering.
    }
}
