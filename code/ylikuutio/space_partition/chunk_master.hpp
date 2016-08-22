#ifndef __CHUNK_MASTER_HPP_INCLUDED
#define __CHUNK_MASTER_HPP_INCLUDED

#include "code/ylikuutio/common/globals.hpp"

// Include standard headers
#include <queue>    // std::queue
#include <stdint.h> // uint32_t etc.
#include <vector>   // std::vector

// `ChunkMaster` takes care of acquiring vertices (through `callback`),
// organizing vertices into `Chunk` objects, reconstructing `Chunk`
// objects (if vertices have been modified) and deactivating (by
// unbinding) and possibly deleting `Chunk` objects (if needed).

namespace space_partition
{
    class Chunk;

    class ChunkMaster
    {
        public:
            // constructor.
            ChunkMaster(InputParametersToAnyValueCallback callback);

            // destructor.
            ~ChunkMaster();

        private:
            // Callback used to get the content based on x, y, z.
            InputParametersToAnyValueCallback callback;

            std::vector<space_partition::Chunk*> chunk_pointer_vector;
            std::queue<uint32_t> free_chunkID_queue;
    };
};

#endif
