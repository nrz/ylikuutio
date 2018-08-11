#include "chunk.hpp"
#include "chunk_master.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

namespace yli
{
    namespace ontology
    {
        void Chunk::bind_to_parent()
        {
            // get `childID` from the `ChunkMaster` and set pointer to this `Chunk`.
            this->parent->bind_chunk(this);
        }

        Chunk::~Chunk()
        {
            // destructor.

            // set pointer to this `Chunk` to nullptr.
            this->parent->set_chunk_pointer(this->childID, nullptr);
        }

        void Chunk::render()
        {
            if (this->vram_buffer_in_use)
            {
                // Render this `Chunk`.
                // If any vertex of the `Chunk` has changed, the vertex data
                // of the `Chunk` needs to be reconstructed before rendering.
            }
        }
    }
}
