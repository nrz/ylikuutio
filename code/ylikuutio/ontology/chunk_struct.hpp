#ifndef __CHUNK_STRUCT_HPP_INCLUDED
#define __CHUNK_STRUCT_HPP_INCLUDED

namespace yli
{
    namespace ontology
    {
        class Universe;
        class ChunkMaster;
    }
}

typedef struct ChunkStruct
{
    ChunkStruct()
        : universe(nullptr),
        parent(nullptr),
        vram_buffer_in_use(true)
    {
        // constructor.
    }

    yli::ontology::Universe* universe;  // pointer to the `Universe`.
    yli::ontology::ChunkMaster* parent; // pointer to the `ChunkMaster`.
    bool vram_buffer_in_use;
} ChunkStruct;

#endif
