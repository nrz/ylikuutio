#include "chunk.hpp"
#include "chunk_master.hpp"
#include "code/ylikuutio/hierarchy/hierarchy_templates.hpp"

// Include standard headers
#include <iostream> // std::cout, std::cin, std::cerr

namespace yli
{
    namespace ontology
    {
        void Chunk::bind_to_parent()
        {
            // requirements:
            // `this->parent` must not be `nullptr`.
            yli::ontology::ChunkMaster* const chunk_master = this->parent;

            if (chunk_master == nullptr)
            {
                std::cerr << "ERROR: `Chunk::bind_to_parent`: `chunk_master` is `nullptr`!\n";
                return;
            }

            // get `childID` from the `ChunkMaster` and set pointer to this `Chunk`.
            chunk_master->bind_chunk(this);
        }

        Chunk::~Chunk()
        {
            // destructor.
            //
            // requirements:
            // `this->parent` must not be `nullptr`.
            yli::ontology::ChunkMaster* const chunk_master = this->parent;

            if (chunk_master == nullptr)
            {
                std::cerr << "ERROR: `Chunk::~Chunk`: `chunk_master` is `nullptr`!\n";
                return;
            }

            chunk_master->unbind_chunk(this->childID);
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
