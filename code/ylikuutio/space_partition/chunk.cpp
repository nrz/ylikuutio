#include "chunk.hpp"
#include "chunk_master.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

namespace space_partition
{
    void Chunk::bind_to_parent()
    {
        // get `childID` from the `ChunkMaster` and set pointer to this `Chunk`.
        yli::hierarchy::bind_child_to_parent<space_partition::Chunk*>(this, this->parent->chunk_pointer_vector, this->parent->free_chunkID_queue, &this->parent->number_of_chunks);
    }

    Chunk::~Chunk()
    {
        // destructor.

        // set pointer to this `Chunk` to nullptr.
        this->parent->set_chunk_pointer(this->childID, nullptr);
    }

    void Chunk::render()
    {
        // Render this `Chunk`.
        // If any vertex of the `Chunk` has changed, the vertex data
        // of the `Chunk` needs to be reconstructed before rendering.
    }
}
