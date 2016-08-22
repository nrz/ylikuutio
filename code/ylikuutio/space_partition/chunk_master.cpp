#include "chunk_master.hpp"
#include "chunk.hpp"
#include "code/ylikuutio/ontology/render_templates.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"
#include "code/ylikuutio/common/globals.hpp"

namespace space_partition
{
    ChunkMaster::ChunkMaster(InputParametersToAnyValueCallback callback)
    {
        // constructor.
        this->callback = callback;
    }

    ChunkMaster::~ChunkMaster()
    {
        // destructor.

        // destroy all chunks of this material.
        std::cout << "All chunks of this material will be destroyed.\n";
        hierarchy::delete_children<space_partition::Chunk*>(this->chunk_pointer_vector);
    }

    void ChunkMaster::set_chunk_pointer(uint32_t childID, space_partition::Chunk* child_pointer)
    {
        hierarchy::set_child_pointer(childID, child_pointer, this->chunk_pointer_vector, this->free_chunkID_queue);
    }

    void ChunkMaster::render()
    {
        // render `ChunkMaster` by calling `render()` function of each `Chunk`.
        ontology::render_children<space_partition::Chunk*>(this->chunk_pointer_vector);
    }
}
