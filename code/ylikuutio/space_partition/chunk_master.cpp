#include "chunk_master.hpp"
#include "chunk.hpp"
#include "code/ylikuutio/ontology/material.hpp"
#include "code/ylikuutio/ontology/render_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/common/globals.hpp"

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr

namespace space_partition
{
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
        hierarchy::delete_children<space_partition::Chunk*>(this->chunk_pointer_vector, &this->number_of_chunks);

        // set pointer to this `ChunkMaster` to nullptr.
        this->parent->set_chunk_master_pointer(this->childID, nullptr);
    }

    void ChunkMaster::set_chunk_pointer(int32_t childID, space_partition::Chunk* child_pointer)
    {
        hierarchy::set_child_pointer(childID, child_pointer, this->chunk_pointer_vector, this->free_chunkID_queue, &this->number_of_chunks);
    }

    void ChunkMaster::render()
    {
        // render `ChunkMaster` by calling `render()` function of each `Chunk`.
        yli::ontology::render_children<space_partition::Chunk*>(this->chunk_pointer_vector);
    }
}
